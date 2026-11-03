#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <shellapi.h>
#include <string>
#include <vector>
#include <thread>
#include <atomic>
#include "embedded_web.hpp"
#include "real_compiler.hpp"

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "shell32.lib")

static std::atomic<bool> g_running(true);
static int g_port = 23377;

static std::string extract_json_field(const std::string& json, const std::string& field) {
    std::string needle = "\"" + field + "\"";
    size_t pos = json.find(needle);
    if (pos == std::string::npos) return "";
    pos = json.find(':', pos);
    if (pos == std::string::npos) return "";
    pos = json.find_first_not_of(" \t\r\n", pos + 1);
    if (pos == std::string::npos) return "";

    if (json[pos] == '"') {
        size_t end = pos + 1;
        while (end < json.length()) {
            if (json[end] == '\\' && end + 1 < json.length()) {
                end += 2;
                continue;
            }
            if (json[end] == '"') break;
            end++;
        }
        std::string raw = json.substr(pos + 1, end - pos - 1);
        std::string unescaped = "";
        for (size_t i = 0; i < raw.length(); ++i) {
            if (raw[i] == '\\' && i + 1 < raw.length()) {
                char next = raw[i + 1];
                if (next == 'n') unescaped += '\n';
                else if (next == 'r') unescaped += '\r';
                else if (next == 't') unescaped += '\t';
                else if (next == '"') unescaped += '"';
                else if (next == '\\') unescaped += '\\';
                else unescaped += next;
                i++;
            } else {
                unescaped += raw[i];
            }
        }
        return unescaped;
    } else {
        size_t end = json.find_first_of(",}\r\n ", pos);
        if (end == std::string::npos) end = json.length();
        return json.substr(pos, end - pos);
    }
}

static std::string json_escape(const std::string& s) {
    std::string out = "";
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

static void handle_client(SOCKET client) {
    char buf[65536];
    int recvd = recv(client, buf, sizeof(buf) - 1, 0);
    if (recvd <= 0) {
        closesocket(client);
        return;
    }
    buf[recvd] = '\0';
    std::string req(buf, recvd);

    size_t first_line_end = req.find("\r\n");
    if (first_line_end == std::string::npos) {
        closesocket(client);
        return;
    }
    std::string first_line = req.substr(0, first_line_end);
    size_t sp1 = first_line.find(' ');
    size_t sp2 = first_line.find(' ', sp1 + 1);
    if (sp1 == std::string::npos || sp2 == std::string::npos) {
        closesocket(client);
        return;
    }

    std::string method = first_line.substr(0, sp1);
    std::string path = first_line.substr(sp1 + 1, sp2 - sp1 - 1);

    size_t body_pos = req.find("\r\n\r\n");
    std::string body = (body_pos != std::string::npos) ? req.substr(body_pos + 4) : "";

    if (method == "GET" && (path == "/" || path == "/index.html")) {
        std::string html((const char*)EMBEDDED_HTML, EMBEDDED_HTML_LEN);
        std::string resp = "HTTP/1.1 200 OK\r\n"
                           "Content-Type: text/html; charset=utf-8\r\n"
                           "Cache-Control: no-cache, no-store, must-revalidate\r\n"
                           "Content-Length: " + std::to_string(html.length()) + "\r\n\r\n" + html;
        send(client, resp.c_str(), (int)resp.length(), 0);
    }
    else if (method == "GET" && path == "/api/lessons") {
        std::string json((const char*)EMBEDDED_LESSONS, EMBEDDED_LESSONS_LEN);
        std::string resp = "HTTP/1.1 200 OK\r\n"
                           "Content-Type: application/json; charset=utf-8\r\n"
                           "Cache-Control: no-cache, no-store, must-revalidate\r\n"
                           "Content-Length: " + std::to_string(json.length()) + "\r\n\r\n" + json;
        send(client, resp.c_str(), (int)resp.length(), 0);
    }
    else if (method == "GET" && path == "/api/types") {
        std::string json = "[\n"
            "{\"name\":\"char\",\"x86\":\"1\",\"x64\":\"1\",\"spec\":\"%c\",\"range\":\"-128 .. 127\",\"desc\":\"Символ ASCII (1 байт)\"},\n"
            "{\"name\":\"unsigned char\",\"x86\":\"1\",\"x64\":\"1\",\"spec\":\"%u\",\"range\":\"0 .. 255\",\"desc\":\"Сырой байт данных (uint8_t)\"},\n"
            "{\"name\":\"short\",\"x86\":\"2\",\"x64\":\"2\",\"spec\":\"%d\",\"range\":\"-32,768 .. 32,767\",\"desc\":\"Короткое целое (16 бит)\"},\n"
            "{\"name\":\"int\",\"x86\":\"4\",\"x64\":\"4\",\"spec\":\"%d\",\"range\":\"-2,147,483,648 .. 2,147,483,647\",\"desc\":\"Стандартное целое число (32 бита)\"},\n"
            "{\"name\":\"unsigned int\",\"x86\":\"4\",\"x64\":\"4\",\"spec\":\"%u\",\"range\":\"0 .. 4,294,967,295\",\"desc\":\"Беззнаковое 32-битное число\"},\n"
            "{\"name\":\"long long\",\"x86\":\"8\",\"x64\":\"8\",\"spec\":\"%lld\",\"range\":\"до ±9*10^18\",\"desc\":\"64-битное целое число\"},\n"
            "{\"name\":\"float\",\"x86\":\"4\",\"x64\":\"4\",\"spec\":\"%f\",\"range\":\"±3.4*10^38\",\"desc\":\"С плавающей точкой (~7 знаков)\"},\n"
            "{\"name\":\"double\",\"x86\":\"8\",\"x64\":\"8\",\"spec\":\"%lf\",\"range\":\"±1.7*10^308\",\"desc\":\"Двойная точность (~15 знаков)\"},\n"
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

        std::string exp = "";
        if (lessonId == 1) exp = "Hello, QuantumCode!\nCPU Architecture: x86_64\n";
        else if (lessonId == 2) exp = "Target Library: kernel32.dll\nLength: 12 chars\n";
        else if (lessonId == 3) exp = "Health: 100 (4 bytes)\nArmor: 45.50 (8 bytes)\nLevel: 5 (1 bytes)\n";

        // REAL COMPILATION & EXECUTION VALIDATION
        CompileResult cres = real_validate_and_run(code, lang, lessonId, exp);

        std::string json_resp = "{\n"
            "\"success\": " + std::string(cres.success ? "true" : "false") + ",\n"
            "\"stage\": \"" + cres.stage + "\",\n"
            "\"stdout\": \"" + json_escape(cres.stdout_str) + "\",\n"
            "\"stderr\": \"" + json_escape(cres.stderr_str) + "\",\n"
            "\"exitCode\": " + std::to_string(cres.exit_code) + ",\n"
            "\"taskCompleted\": " + std::string(cres.task_completed ? "true" : "false") + ",\n"
            "\"timeMs\": " + std::to_string(cres.time_ms) + "\n"
            "}";

        std::string resp = "HTTP/1.1 200 OK\r\n"
                           "Content-Type: application/json; charset=utf-8\r\n"
                           "Content-Length: " + std::to_string(json_resp.length()) + "\r\n\r\n" + json_resp;
        send(client, resp.c_str(), (int)resp.length(), 0);
    }
    else if (method == "POST" && path == "/api/ai/ask") {
        std::string prompt = extract_json_field(body, "prompt");
        std::string code = extract_json_field(body, "code");

        std::string ai_answer;
        if (code.find("printf") == std::string::npos && code.find("main") != std::string::npos) {
            ai_answer = "В вашей функции main пока нет вызовов вывода. Используйте printf(\"...\\n\"); для вывода данных на консоль.";
        } else if (code.find(';') == std::string::npos) {
            ai_answer = "Обратите внимание: в языке Си каждая инструкция должна завершаться точкой с запятой ';'!";
        } else {
            ai_answer = "Код корректно структурирован. Функция main является точкой входа. Проверьте совпадение вывода с заданием урока и запускайте через F5.";
        }

        std::string json_resp = "{\"response\": \"" + json_escape(ai_answer) + "\"}";
        std::string resp = "HTTP/1.1 200 OK\r\n"
                           "Content-Type: application/json; charset=utf-8\r\n"
                           "Content-Length: " + std::to_string(json_resp.length()) + "\r\n\r\n" + json_resp;
        send(client, resp.c_str(), (int)resp.length(), 0);
    }
    else {
        std::string not_found = "HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n";
        send(client, not_found.c_str(), (int)not_found.length(), 0);
    }

    closesocket(client);
}

static void server_thread() {
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) return;

    SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listen_sock == INVALID_SOCKET) {
        WSACleanup();
        return;
    }

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    addr.sin_port = htons(g_port);

    if (bind(listen_sock, (sockaddr*)&addr, sizeof(addr)) != 0) {
        addr.sin_port = htons(0);
        bind(listen_sock, (sockaddr*)&addr, sizeof(addr));
        int len = sizeof(addr);
        getsockname(listen_sock, (sockaddr*)&addr, &len);
        g_port = ntohs(addr.sin_port);
    }

    listen(listen_sock, 16);

    while (g_running) {
        SOCKET client = accept(listen_sock, NULL, NULL);
        if (client == INVALID_SOCKET) break;
        std::thread(handle_client, client).detach();
    }

    closesocket(listen_sock);
    WSACleanup();
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    (void)hInstance; (void)hPrevInstance; (void)lpCmdLine; (void)nCmdShow;

    std::thread th(server_thread);
    th.detach();

    Sleep(200);

    std::string url = "http://127.0.0.1:" + std::to_string(g_port) + "/index.html";
    std::string edge_cmd = "--app=" + url + " --window-size=1280,820";

    HINSTANCE res = ShellExecuteA(NULL, "open", "msedge.exe", edge_cmd.c_str(), NULL, SW_SHOWNORMAL);
    if ((INT_PTR)res <= 32) {
        ShellExecuteA(NULL, "open", url.c_str(), NULL, NULL, SW_SHOWNORMAL);
    }

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    g_running = false;
    return 0;
}
