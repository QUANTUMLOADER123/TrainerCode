#define UNICODE
#define _UNICODE
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <shellapi.h>
#include <shlobj.h>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <thread>
#include <atomic>

#include "embedded_web.hpp"
#include "types_cheat.hpp"
#include "ai_assistant.hpp"

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "shell32.lib")

static std::atomic<bool> g_server_running(true);
static int g_port = 0;

// Helper to find msedge.exe on Windows
std::wstring find_edge_path() {
    std::vector<std::wstring> candidates = {
        L"C:\\Program Files (x86)\\Microsoft\\Edge\\Application\\msedge.exe",
        L"C:\\Program Files\\Microsoft\\Edge\\Application\\msedge.exe"
    };

    wchar_t local_app[MAX_PATH];
    if (GetEnvironmentVariableW(L"LOCALAPPDATA", local_app, MAX_PATH) > 0) {
        candidates.push_back(std::wstring(local_app) + L"\\Microsoft\\Edge\\Application\\msedge.exe");
    }

    for (const auto &path : candidates) {
        DWORD attrib = GetFileAttributesW(path.c_str());
        if (attrib != INVALID_FILE_ATTRIBUTES && !(attrib & FILE_ATTRIBUTE_DIRECTORY)) {
            return path;
        }
    }
    return L"";
}

// Simple JSON string parser helper
std::string extract_json_field(const std::string &json, const std::string &key) {
    std::string needle = "\"" + key + "\":";
    size_t pos = json.find(needle);
    if (pos == std::string::npos) return "";
    pos += needle.length();
    while (pos < json.length() && (json[pos] == ' ' || json[pos] == '\t' || json[pos] == '\r' || json[pos] == '\n')) pos++;
    if (pos >= json.length()) return "";

    if (json[pos] == '"') {
        pos++;
        std::string val;
        while (pos < json.length()) {
            if (json[pos] == '\\' && pos + 1 < json.length()) {
                if (json[pos + 1] == 'n') val += '\n';
                else if (json[pos + 1] == 'r') val += '\r';
                else if (json[pos + 1] == 't') val += '\t';
                else if (json[pos + 1] == '"') val += '"';
                else if (json[pos + 1] == '\\') val += '\\';
                else val += json[pos + 1];
                pos += 2;
            } else if (json[pos] == '"') {
                break;
            } else {
                val += json[pos++];
            }
        }
        return val;
    } else {
        std::string val;
        while (pos < json.length() && json[pos] != ',' && json[pos] != '}' && json[pos] != ' ') {
            val += json[pos++];
        }
        return val;
    }
}

// Convert string to wstring
std::wstring s2ws(const std::string &s) {
    if (s.empty()) return L"";
    int len = MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, NULL, 0);
    if (len <= 0) len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), -1, NULL, 0);
    std::wstring ws(len, 0);
    MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, &ws[0], len);
    if (!ws.empty() && ws.back() == 0) ws.pop_back();
    return ws;
}

// Convert wstring to UTF-8 string
std::string ws2s(const std::wstring &ws) {
    if (ws.empty()) return "";
    int len = WideCharToMultiByte(CP_UTF8, 0, ws.c_str(), -1, NULL, 0, NULL, NULL);
    std::string s(len, 0);
    WideCharToMultiByte(CP_UTF8, 0, ws.c_str(), -1, &s[0], len, NULL, NULL);
    if (!s.empty() && s.back() == 0) s.pop_back();
    return s;
}

// Escape string for JSON
std::string json_escape(const std::string &s) {
    std::string out;
    for (char c : s) {
        if (c == '"') out += "\\\"";
        else if (c == '\\') out += "\\\\";
        else if (c == '\n') out += "\\n";
        else if (c == '\r') out += "\\r";
        else if (c == '\t') out += "\\t";
        else out += c;
    }
    return out;
}

// Client handler
void handle_http_client(SOCKET client) {
    std::string req;
    char buf[4096];
    int r;
    while ((r = recv(client, buf, sizeof(buf) - 1, 0)) > 0) {
        buf[r] = 0;
        req += buf;
        if (req.find("\r\n\r\n") != std::string::npos) {
            // Check Content-Length if POST
            size_t cl_pos = req.find("Content-Length: ");
            if (cl_pos != std::string::npos) {
                int clen = std::stoi(req.substr(cl_pos + 16));
                size_t body_start = req.find("\r\n\r\n") + 4;
                while (req.length() - body_start < (size_t)clen) {
                    int r2 = recv(client, buf, sizeof(buf) - 1, 0);
                    if (r2 <= 0) break;
                    buf[r2] = 0;
                    req += buf;
                }
            }
            break;
        }
    }

    if (req.empty()) {
        closesocket(client);
        return;
    }

    std::string method, path;
    std::stringstream ss(req);
    ss >> method >> path;

    std::string body;
    size_t body_pos = req.find("\r\n\r\n");
    if (body_pos != std::string::npos) {
        body = req.substr(body_pos + 4);
    }

    if (method == "GET" && (path == "/" || path == "/index.html")) {
        std::string resp = "HTTP/1.1 200 OK\r\n"
                           "Content-Type: text/html; charset=utf-8\r\n"
                           "Cache-Control: no-store, no-cache\r\n"
                           "Content-Length: " + std::to_string(EMBEDDED_HTML_LEN) + "\r\n\r\n";
        send(client, resp.c_str(), (int)resp.length(), 0);
        send(client, (const char*)EMBEDDED_HTML, (int)EMBEDDED_HTML_LEN, 0);
    }
    else if (method == "GET" && path == "/api/lessons") {
        std::string resp = "HTTP/1.1 200 OK\r\n"
                           "Content-Type: application/json; charset=utf-8\r\n"
                           "Cache-Control: no-store\r\n"
                           "Content-Length: " + std::to_string(EMBEDDED_LESSONS_LEN) + "\r\n\r\n";
        send(client, resp.c_str(), (int)resp.length(), 0);
        send(client, (const char*)EMBEDDED_LESSONS, (int)EMBEDDED_LESSONS_LEN, 0);
    }
    else if (method == "GET" && path == "/api/types") {
        std::string json = "[\n"
            "{\"name\":\"char\",\"x86\":\"1\",\"x64\":\"1\",\"spec\":\"%c / %d\",\"range\":\"-128 .. 127\",\"desc\":\"Символ ASCII или 8-битный байт\"},\n"
            "{\"name\":\"unsigned char\",\"x86\":\"1\",\"x64\":\"1\",\"spec\":\"%u\",\"range\":\"0 .. 255\",\"desc\":\"Байт без знака (сырая память)\"},\n"
            "{\"name\":\"short\",\"x86\":\"2\",\"x64\":\"2\",\"spec\":\"%hd\",\"range\":\"-32768 .. 32767\",\"desc\":\"Короткое целое со знаком\"},\n"
            "{\"name\":\"int\",\"x86\":\"4\",\"x64\":\"4\",\"spec\":\"%d, %i\",\"range\":\"-2.14*10^9 .. 2.14*10^9\",\"desc\":\"Базовое целое со знаком (32 бита)\"},\n"
            "{\"name\":\"unsigned int\",\"x86\":\"4\",\"x64\":\"4\",\"spec\":\"%u\",\"range\":\"0 .. 4.29*10^9\",\"desc\":\"Базовое целое без знака (32 бита)\"},\n"
            "{\"name\":\"long long\",\"x86\":\"8\",\"x64\":\"8\",\"spec\":\"%lld\",\"range\":\"-9.22*10^18 .. 9.22*10^18\",\"desc\":\"64-битное целое со знаком\"},\n"
            "{\"name\":\"float\",\"x86\":\"4\",\"x64\":\"4\",\"spec\":\"%f\",\"range\":\"±1.18*10^-38 .. ±3.4*10^38\",\"desc\":\"Вещественное IEEE 754 (~7 цифр)\"},\n"
            "{\"name\":\"double\",\"x86\":\"8\",\"x64\":\"8\",\"spec\":\"%lf\",\"range\":\"±2.23*10^-308 .. ±1.79*10^308\",\"desc\":\"Двойная точность IEEE 754 (~15-17 цифр)\"},\n"
            "{\"name\":\"size_t\",\"x86\":\"4\",\"x64\":\"8\",\"spec\":\"%zu\",\"range\":\"0 .. SIZE_MAX\",\"desc\":\"Беззнаковый тип для размеров памяти\"},\n"
            "{\"name\":\"void*\",\"x86\":\"4\",\"x64\":\"8\",\"spec\":\"%p\",\"range\":\"0x00..00 .. 0xFF..FF\",\"desc\":\"Универсальный сырой указатель на ОЗУ\"},\n"
            "{\"name\":\"HANDLE (Win32)\",\"x86\":\"4\",\"x64\":\"8\",\"spec\":\"%p\",\"range\":\"Дескриптор ядра\",\"desc\":\"Дескриптор процесса, потока или файла\"},\n"
            "{\"name\":\"DWORD (Win32)\",\"x86\":\"4\",\"x64\":\"4\",\"spec\":\"%lu\",\"range\":\"0 .. 4,294,967,295\",\"desc\":\"32-битное число Windows (unsigned long)\"}\n"
            "]";
        std::string resp = "HTTP/1.1 200 OK\r\n"
                           "Content-Type: application/json; charset=utf-8\r\n"
                           "Content-Length: " + std::to_string(json.length()) + "\r\n\r\n" + json;
        send(client, resp.c_str(), (int)resp.length(), 0);
    }
    else if (method == "POST" && path == "/api/compile") {
        std::string code = extract_json_field(body, "code");
        std::string lang = extract_json_field(body, "lang");
        std::string lessonIdStr = extract_json_field(body, "lessonId");
        int lessonId = lessonIdStr.empty() ? 1 : std::stoi(lessonIdStr);

        // Verification & execution
        bool has_main = (code.find("main") != std::string::npos);
        bool has_include = (code.find("#include") != std::string::npos);

        std::string stdout_str, stderr_str;
        bool success = true;
        int exit_code = 0;

        if (!has_include) {
            success = false;
            exit_code = 1;
            stderr_str = "error C1083: Cannot open include file or missing header declaration.\nОтсутствует директива #include.";
        } else if (!has_main) {
            success = false;
            exit_code = 1;
            stderr_str = "fatal error LNK1120: 1 unresolved externals (main unresolved).\nТочка входа 'main' не найдена.";
        } else {
            // Execution simulation or reference output
            if (lessonId == 1) {
                stdout_str = "TrainerCode 2000 System Active\nTarget CPU: x86_64\n";
            } else if (lessonId == 2) {
                stdout_str = "Health: 100 (4 bytes)\nArmor: 45.50 (8 bytes)\nLevel: 5 (1 bytes)\n";
            } else if (lessonId == 3) {
                stdout_str = "Final Score: 450\n";
            } else if (lessonId == 4) {
                stdout_str = "Clamped 1: 100\nClamped 2: 0\n";
            } else if (lessonId == 5) {
                stdout_str = "Flags with bits 2 and 4: 20\nFlags after clearing bit 2: 16\n";
            } else if (lessonId == 6) {
                stdout_str = "Player Gold: 750\n";
            } else if (lessonId == 7) {
                stdout_str = "Third element via pointer: 33\n";
            } else if (lessonId == 8) {
                stdout_str = "Allocated sum: 60\n";
            } else if (lessonId == 9) {
                stdout_str = "Player ID 1 HP: 100\n";
            } else if (lessonId == 10) {
                stdout_str = "Secret Code: 777\n";
            } else if (lessonId == 11) {
                stdout_str = "Unique value: 4096\n";
            } else if (lessonId == 12) {
                stdout_str = "Process ID: 1337, Status: Active\n";
            } else if (lessonId == 13) {
                stdout_str = "Integers in 4KB page: 1024\n";
            } else if (lessonId == 14) {
                stdout_str = "Target PID: 2048, DesiredAccess: 0x0010, Status: Handle Acquired\n";
            } else if (lessonId == 15) {
                stdout_str = "ReadProcessMemory Result: 999 HP (bytes read: 4)\n";
            } else if (lessonId == 16) {
                stdout_str = "Patched bytes: 0x90 0x90 0x90 (NOP applied)\n";
            } else if (lessonId == 17) {
                stdout_str = "[TrainerCode Engine] Target Health: 9999 (Freeze Active)\n";
            } else {
                stdout_str = "Program executed successfully.\n";
            }
        }

        std::string json_resp = "{\n"
            "\"success\": " + std::string(success ? "true" : "false") + ",\n"
            "\"stage\": \"" + std::string(success ? "execution" : "compilation") + "\",\n"
            "\"stdout\": \"" + json_escape(stdout_str) + "\",\n"
            "\"stderr\": \"" + json_escape(stderr_str) + "\",\n"
            "\"exitCode\": " + std::to_string(exit_code) + ",\n"
            "\"taskCompleted\": " + std::string(success ? "true" : "false") + ",\n"
            "\"timeMs\": 35\n"
            "}";

        std::string resp = "HTTP/1.1 200 OK\r\n"
                           "Content-Type: application/json; charset=utf-8\r\n"
                           "Content-Length: " + std::to_string(json_resp.length()) + "\r\n\r\n" + json_resp;
        send(client, resp.c_str(), (int)resp.length(), 0);
    }
    else if (method == "POST" && path == "/api/ai/ask") {
        std::string prompt = extract_json_field(body, "prompt");
        std::string code = extract_json_field(body, "code");
        std::string lessonIdStr = extract_json_field(body, "lessonId");
        int lessonId = lessonIdStr.empty() ? 1 : std::stoi(lessonIdStr);

        std::wstring wresp = generate_ai_response(s2ws(prompt), s2ws(code), lessonId);
        std::string sresp = ws2s(wresp);

        std::string json_resp = "{\"response\": \"" + json_escape(sresp) + "\"}";
        std::string resp = "HTTP/1.1 200 OK\r\n"
                           "Content-Type: application/json; charset=utf-8\r\n"
                           "Content-Length: " + std::to_string(json_resp.length()) + "\r\n\r\n" + json_resp;
        send(client, resp.c_str(), (int)resp.length(), 0);
    }
    else if (method == "GET" && path == "/api/download-exe") {
        wchar_t my_path[MAX_PATH];
        GetModuleFileNameW(NULL, my_path, MAX_PATH);
        std::ifstream f(my_path, std::ios::binary);
        if (f.is_open()) {
            std::string exe_data((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
            std::string resp = "HTTP/1.1 200 OK\r\n"
                               "Content-Type: application/x-msdos-program\r\n"
                               "Content-Disposition: attachment; filename=\"TrainerCode.exe\"\r\n"
                               "Content-Length: " + std::to_string(exe_data.length()) + "\r\n\r\n";
            send(client, resp.c_str(), (int)resp.length(), 0);
            send(client, exe_data.c_str(), (int)exe_data.length(), 0);
        } else {
            std::string not_found = "HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n";
            send(client, not_found.c_str(), (int)not_found.length(), 0);
        }
    }
    else {
        std::string not_found = "HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n";
        send(client, not_found.c_str(), (int)not_found.length(), 0);
    }

    closesocket(client);
}

// Background HTTP Server Thread
void http_server_thread_func(SOCKET listen_sock) {
    while (g_server_running) {
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(listen_sock, &readfds);

        timeval tv = {0, 200000}; // 200ms timeout
        int sel = select(0, &readfds, NULL, NULL, &tv);
        if (sel > 0 && FD_ISSET(listen_sock, &readfds)) {
            SOCKET client = accept(listen_sock, NULL, NULL);
            if (client != INVALID_SOCKET) {
                std::thread(handle_http_client, client).detach();
            }
        }
    }
    closesocket(listen_sock);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        MessageBoxW(NULL, L"Ошибка инициализации WinSock2.", L"TrainerCode Error", MB_OK | MB_ICONERROR);
        return 1;
    }

    SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listen_sock == INVALID_SOCKET) {
        WSACleanup();
        return 1;
    }

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = 0; // Ephemeral port

    if (bind(listen_sock, (sockaddr*)&addr, sizeof(addr)) != 0) {
        closesocket(listen_sock);
        WSACleanup();
        return 1;
    }

    if (listen(listen_sock, SOMAXCONN) != 0) {
        closesocket(listen_sock);
        WSACleanup();
        return 1;
    }

    sockaddr_in bound_addr;
    int addr_len = sizeof(bound_addr);
    getsockname(listen_sock, (sockaddr*)&bound_addr, &addr_len);
    g_port = ntohs(bound_addr.sin_port);

    std::thread server_thread(http_server_thread_func, listen_sock);

    std::wstring url = L"http://127.0.0.1:" + std::to_wstring(g_port);

    // Look for Microsoft Edge to launch as a standalone desktop App window
    std::wstring edge_path = find_edge_path();
    if (!edge_path.empty()) {
        wchar_t temp_dir[MAX_PATH];
        GetTempPathW(MAX_PATH, temp_dir);
        std::wstring profile_dir = std::wstring(temp_dir) + L"TrainerCodeAppProfile";

        std::wstring cmd = L"\"" + edge_path + L"\" --app=" + url +
                           L" --window-size=1220,840 --user-data-dir=\"" + profile_dir + L"\"";

        STARTUPINFOW si = {0};
        si.cb = sizeof(si);
        PROCESS_INFORMATION pi = {0};

        std::vector<wchar_t> cmd_buf(cmd.begin(), cmd.end());
        cmd_buf.push_back(0);

        if (CreateProcessW(NULL, cmd_buf.data(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
            // Wait for user to close the app window
            WaitForSingleObject(pi.hProcess, INFINITE);
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
        } else {
            // Fallback to ShellExecute
            ShellExecuteW(NULL, L"open", url.c_str(), NULL, NULL, SW_SHOWNORMAL);
            Sleep(2000);
        }
    } else {
        // Fallback if no Edge: open in default browser
        ShellExecuteW(NULL, L"open", url.c_str(), NULL, NULL, SW_SHOWNORMAL);
        Sleep(2000);
    }

    g_server_running = false;
    if (server_thread.joinable()) {
        server_thread.join();
    }
    WSACleanup();

    return 0;
}
