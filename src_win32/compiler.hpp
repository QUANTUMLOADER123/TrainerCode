#pragma once
#include <windows.h>
#include <string>
#include <sstream>
#include <vector>

struct CompilerConfig {
    std::wstring compiler_type = L"MSVC / Visual Studio";
    std::wstring compiler_path = L"C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.38.33130\\bin\\Hostx64\\x64\\cl.exe";
    std::wstring custom_flags = L"-Wall -Wextra -O2";
    std::wstring c_std = L"c11";
    std::wstring cpp_std = L"c++20";
    bool auto_run = true;
};

inline void load_config(CompilerConfig &cfg, const std::wstring &ini_path, std::wstring &username, std::wstring &user_level) {
    wchar_t buf[512];
    GetPrivateProfileStringW(L"User", L"Name", L"", buf, 512, ini_path.c_str());
    username = buf;
    GetPrivateProfileStringW(L"User", L"Level", L"Новичок", buf, 512, ini_path.c_str());
    user_level = buf;

    GetPrivateProfileStringW(L"Compiler", L"Type", cfg.compiler_type.c_str(), buf, 512, ini_path.c_str());
    cfg.compiler_type = buf;
    GetPrivateProfileStringW(L"Compiler", L"Path", cfg.compiler_path.c_str(), buf, 512, ini_path.c_str());
    cfg.compiler_path = buf;
    GetPrivateProfileStringW(L"Compiler", L"Flags", cfg.custom_flags.c_str(), buf, 512, ini_path.c_str());
    cfg.custom_flags = buf;
    GetPrivateProfileStringW(L"Compiler", L"CStd", cfg.c_std.c_str(), buf, 512, ini_path.c_str());
    cfg.c_std = buf;
    GetPrivateProfileStringW(L"Compiler", L"CppStd", cfg.cpp_std.c_str(), buf, 512, ini_path.c_str());
    cfg.cpp_std = buf;
}

inline void save_config(const CompilerConfig &cfg, const std::wstring &ini_path, const std::wstring &username, const std::wstring &user_level) {
    WritePrivateProfileStringW(L"User", L"Name", username.c_str(), ini_path.c_str());
    WritePrivateProfileStringW(L"User", L"Level", user_level.c_str(), ini_path.c_str());
    WritePrivateProfileStringW(L"Compiler", L"Type", cfg.compiler_type.c_str(), ini_path.c_str());
    WritePrivateProfileStringW(L"Compiler", L"Path", cfg.compiler_path.c_str(), ini_path.c_str());
    WritePrivateProfileStringW(L"Compiler", L"Flags", cfg.custom_flags.c_str(), ini_path.c_str());
    WritePrivateProfileStringW(L"Compiler", L"CStd", cfg.c_std.c_str(), ini_path.c_str());
    WritePrivateProfileStringW(L"Compiler", L"CppStd", cfg.cpp_std.c_str(), ini_path.c_str());
}

inline std::wstring run_process_capture(const std::wstring &cmd) {
    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.bInheritHandle = TRUE;
    sa.lpSecurityDescriptor = NULL;

    HANDLE hRead, hWrite;
    if (!CreatePipe(&hRead, &hWrite, &sa, 0)) return L"Ошибка создания пайпа процесса.\r\n";
    SetHandleInformation(hRead, HANDLE_FLAG_INHERIT, 0);

    STARTUPINFOW si = {0};
    si.cb = sizeof(si);
    si.hStdOutput = hWrite;
    si.hStdError = hWrite;
    si.dwFlags |= STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;

    PROCESS_INFORMATION pi = {0};
    std::vector<wchar_t> cmd_buf(cmd.begin(), cmd.end());
    cmd_buf.push_back(0);

    if (!CreateProcessW(NULL, cmd_buf.data(), NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) {
        CloseHandle(hWrite);
        CloseHandle(hRead);
        return L"Не удалось запустить процесс: " + cmd + L"\r\nУбедитесь, что путь к компилятору указан верно в Настройках.\r\n";
    }

    CloseHandle(hWrite);

    std::string out;
    char buffer[1024];
    DWORD bytesRead;
    while (ReadFile(hRead, buffer, sizeof(buffer) - 1, &bytesRead, NULL) && bytesRead > 0) {
        buffer[bytesRead] = 0;
        out += buffer;
    }

    WaitForSingleObject(pi.hProcess, 10000);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    CloseHandle(hRead);

    int wlen = MultiByteToWideChar(CP_UTF8, 0, out.c_str(), -1, NULL, 0);
    if (wlen <= 0) {
        wlen = MultiByteToWideChar(CP_ACP, 0, out.c_str(), -1, NULL, 0);
    }
    std::wstring wout(wlen, 0);
    MultiByteToWideChar(CP_UTF8, 0, out.c_str(), -1, &wout[0], wlen);
    return wout;
}
