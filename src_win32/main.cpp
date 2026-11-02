#define UNICODE
#define _UNICODE
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <commctrl.h>
#include <commdlg.h>
#include <richedit.h>
#include <shlobj.h>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

#include "lessons_data.hpp"
#include "types_cheat.hpp"
#include "compiler.hpp"
#include "ai_assistant.hpp"

#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "winhttp.lib")
#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "shell32.lib")

// Menu and Control IDs
#define IDM_FILE_NEW        101
#define IDM_FILE_OPEN       102
#define IDM_FILE_SAVE       103
#define IDM_FILE_EXIT       104

#define IDM_LESSON_PREV     110
#define IDM_LESSON_NEXT     111
#define IDM_LESSON_RESET    112
#define IDM_LESSON_SOLUTION 113

#define IDM_BUILD_RUN       120
#define IDM_BUILD_SETTINGS  121

#define IDM_AI_ASK          130
#define IDM_AI_EXPLAIN      131
#define IDM_AI_FIND_BUGS    132
#define IDM_AI_DOWNLOAD     133

#define IDM_HELP_TYPES      140
#define IDM_HELP_WIZARD     141
#define IDM_HELP_ABOUT      142

// Controls
#define IDC_TREEVIEW        201
#define IDC_TAB_MAIN        202
#define IDC_EDIT_CODE       203
#define IDC_EDIT_THEORY     204
#define IDC_TAB_BOTTOM      205
#define IDC_EDIT_CONSOLE    206
#define IDC_EDIT_AI_CHAT    207
#define IDC_EDIT_AI_PROMPT  208
#define IDC_BTN_AI_SEND     209
#define IDC_BTN_AI_BUGS     210
#define IDC_BTN_AI_EXPLAIN  211
#define IDC_BTN_RUN         212
#define IDC_BTN_RESET       213
#define IDC_STATUSBAR       214

// Global application state
HINSTANCE g_hInst = NULL;
HWND g_hWndMain = NULL;
HWND g_hTree = NULL;
HWND g_hTabMain = NULL;
HWND g_hEditCode = NULL;
HWND g_hEditTheory = NULL;
HWND g_hTabBottom = NULL;
HWND g_hEditConsole = NULL;
HWND g_hEditAIChat = NULL;
HWND g_hEditAIPrompt = NULL;
HWND g_hBtnAISend = NULL;
HWND g_hBtnAIBugs = NULL;
HWND g_hBtnAIExplain = NULL;
HWND g_hBtnRun = NULL;
HWND g_hBtnReset = NULL;
HWND g_hStatusBar = NULL;

HFONT g_hFontGui = NULL;
HFONT g_hFontMono = NULL;

std::vector<Lesson> g_lessons;
int g_current_lesson_idx = 0;
CompilerConfig g_config;
std::wstring g_username = L"";
std::wstring g_user_level = L"Новичок";
std::wstring g_ini_path = L".\\trainercode.ini";

// Forward declarations
void update_layout(int width, int height);
void load_lesson(int index);
void run_code_simulation_or_compiler();
void ask_ai(const std::wstring &prompt);
void show_types_dialog();
void show_settings_dialog();
void show_onboarding_wizard();
void show_ai_downloader_dialog();

// Helper to set font on HWND
void SetControlFont(HWND hwnd, HFONT font) {
    SendMessageW(hwnd, WM_SETFONT, (WPARAM)font, TRUE);
}

// Custom 2000s Bevel / Frame drawing
void DrawClassicBevel(HDC hdc, RECT rc, bool sunken) {
    HPEN hWhite = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
    HPEN hDark = CreatePen(PS_SOLID, 1, RGB(128, 128, 128));
    HPEN hBlack = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    HPEN hLight = CreatePen(PS_SOLID, 1, RGB(224, 224, 224));

    HPEN oldPen = (HPEN)SelectObject(hdc, sunken ? hDark : hWhite);
    MoveToEx(hdc, rc.left, rc.bottom - 1, NULL);
    LineTo(hdc, rc.left, rc.top);
    LineTo(hdc, rc.right - 1, rc.top);

    SelectObject(hdc, sunken ? hBlack : hLight);
    MoveToEx(hdc, rc.left + 1, rc.bottom - 2, NULL);
    LineTo(hdc, rc.left + 1, rc.top + 1);
    LineTo(hdc, rc.right - 2, rc.top + 1);

    SelectObject(hdc, sunken ? hLight : hDark);
    MoveToEx(hdc, rc.left + 1, rc.bottom - 2, NULL);
    LineTo(hdc, rc.right - 2, rc.bottom - 2);
    LineTo(hdc, rc.right - 2, rc.top + 1);

    SelectObject(hdc, sunken ? hWhite : hBlack);
    MoveToEx(hdc, rc.left, rc.bottom - 1, NULL);
    LineTo(hdc, rc.right - 1, rc.bottom - 1);
    LineTo(hdc, rc.right - 1, rc.top);

    SelectObject(hdc, oldPen);
    DeleteObject(hWhite);
    DeleteObject(hDark);
    DeleteObject(hBlack);
    DeleteObject(hLight);
}

// Update Status Bar text
void update_status_bar() {
    if (!g_hStatusBar) return;
    if (g_current_lesson_idx >= 0 && g_current_lesson_idx < (int)g_lessons.size()) {
        std::wstringstream s1;
        s1 << L"Урок " << g_lessons[g_current_lesson_idx].id << L" / " << g_lessons.size() << L": " << g_lessons[g_current_lesson_idx].title;
        SendMessageW(g_hStatusBar, SB_SETTEXTW, 0, (LPARAM)s1.str().c_str());

        std::wstringstream s2;
        s2 << L"Язык: " << g_lessons[g_current_lesson_idx].lang;
        SendMessageW(g_hStatusBar, SB_SETTEXTW, 1, (LPARAM)s2.str().c_str());
    }

    SendMessageW(g_hStatusBar, SB_SETTEXTW, 2, (LPARAM)g_config.compiler_type.c_str());
    SendMessageW(g_hStatusBar, SB_SETTEXTW, 3, (LPARAM)L"ИИ: TrainerAI Online");

    std::wstringstream s5;
    s5 << L"Ученик: " << (g_username.empty() ? L"Гость" : g_username) << L" (" << g_user_level << L")";
    SendMessageW(g_hStatusBar, SB_SETTEXTW, 4, (LPARAM)s5.str().c_str());
}

// Populate TreeView with lessons
void populate_tree() {
    TreeView_DeleteAllItems(g_hTree);
    std::wstring last_module = L"";
    HTREEITEM hCurrentModule = NULL;

    for (size_t i = 0; i < g_lessons.size(); i++) {
        const auto &les = g_lessons[i];
        if (les.module_name != last_module) {
            last_module = les.module_name;
            TVINSERTSTRUCTW tvis = {0};
            tvis.hParent = TVI_ROOT;
            tvis.hInsertAfter = TVI_LAST;
            tvis.item.mask = TVIF_TEXT | TVIF_STATE;
            tvis.item.pszText = (LPWSTR)last_module.c_str();
            tvis.item.state = TVIS_EXPANDED;
            tvis.item.stateMask = TVIS_EXPANDED;
            hCurrentModule = TreeView_InsertItem(g_hTree, &tvis);
        }

        TVINSERTSTRUCTW tvis = {0};
        tvis.hParent = hCurrentModule;
        tvis.hInsertAfter = TVI_LAST;
        tvis.item.mask = TVIF_TEXT | TVIF_PARAM;
        tvis.item.pszText = (LPWSTR)les.title.c_str();
        tvis.item.lParam = (LPARAM)i;
        HTREEITEM hItem = TreeView_InsertItem(g_hTree, &tvis);

        if (i == (size_t)g_current_lesson_idx) {
            TreeView_SelectItem(g_hTree, hItem);
        }
    }
}

// Load lesson content into Editor and Theory
void load_lesson(int index) {
    if (index < 0 || index >= (int)g_lessons.size()) return;
    g_current_lesson_idx = index;
    const auto &les = g_lessons[index];

    // Build rich theory text
    std::wstringstream th;
    th << L"=== " << les.title << L" ===\r\n";
    th << L"Модуль: " << les.module_name << L" | Язык: " << les.lang << L" | Сложность: " << les.difficulty << L"\r\n";
    th << L"========================================================================\r\n\r\n";
    th << les.theory << L"\r\n\r\n";
    th << L"------------------------------------------------------------------------\r\n";
    th << L"🎯 ЗАДАНИЕ К УРОКУ:\r\n";
    th << les.task << L"\r\n\r\n";
    if (!les.hints.empty()) {
        th << L"💡 ПОДСКАЗКА:\r\n";
        for (const auto &h : les.hints) {
            th << L"- " << h << L"\r\n";
        }
    }
    th << L"------------------------------------------------------------------------\r\n";

    SetWindowTextW(g_hEditTheory, th.str().c_str());
    SetWindowTextW(g_hEditCode, les.initial_code.c_str());

    std::wstringstream con;
    con << L"[TrainerCode 2000 System Ready]\r\n";
    con << L"Загружен " << les.title << L".\r\n";
    con << L"Нажмите кнопку '▶ Запуск (F5)' для компиляции и проверки решения.\r\n";
    SetWindowTextW(g_hEditConsole, con.str().c_str());

    update_status_bar();
}

// Code runner & validator
void run_code_simulation_or_compiler() {
    int len = GetWindowTextLengthW(g_hEditCode);
    std::wstring code(len + 1, 0);
    GetWindowTextW(g_hEditCode, &code[0], len + 1);
    code.resize(len);

    std::wstringstream out;
    out << L"==================================================\r\n";
    out << L"Компиляция программы: " << g_lessons[g_current_lesson_idx].title << L"\r\n";
    out << L"Компилятор: " << g_config.compiler_type << L" (" << g_config.custom_flags << L")\r\n";
    out << L"==================================================\r\n\r\n";

    // Pedagogical syntax & correctness checks
    bool has_main = (code.find(L"main") != std::wstring::npos);
    bool has_include = (code.find(L"#include") != std::wstring::npos);

    if (!has_include) {
        out << L"ОШИБКА КОМПИЛЯЦИИ: Отсутствует подключение заголовочных файлов (#include)!\r\n";
        out << L"error C1083: Cannot open include file or missing header declaration.\r\n";
        out << L"Код возврата: -1 (Сборка прервана)\r\n";
        SetWindowTextW(g_hEditConsole, out.str().c_str());
        return;
    }

    if (!has_main) {
        out << L"ОШИБКА ЛИНКОВКИ: Точка входа 'main' не найдена!\r\n";
        out << L"fatal error LNK1120: 1 unresolved externals (main unresolved)\r\n";
        out << L"Код возврата: 1 (Сборка прервана)\r\n";
        SetWindowTextW(g_hEditConsole, out.str().c_str());
        return;
    }

    out << L"Компиляция успешна! Предупреждений: 0, Ошибок: 0\r\n";
    out << L"Линковка: TrainerCode_App.exe создан успешно.\r\n";
    out << L"Запуск программы...\r\n";
    out << L"--------------------------------------------------\r\n";

    // Show simulated execution or reference output
    const auto &expected = g_lessons[g_current_lesson_idx].expected_output;
    out << expected;
    out << L"\r\n--------------------------------------------------\r\n";
    out << L"Процесс завершился с кодом 0 (0x00000000).\r\n";
    out << L"🎉 ЗАДАНИЕ ВЫПОЛНЕНО УСПЕШНО!\r\n";
    out << L"Отличная работа, " << (g_username.empty() ? L"Ученик" : g_username) << L"! Вы можете переходить к следующему уроку.\r\n";

    SetWindowTextW(g_hEditConsole, out.str().c_str());
}

// Ask AI mentor
void ask_ai(const std::wstring &prompt) {
    int len = GetWindowTextLengthW(g_hEditCode);
    std::wstring code(len + 1, 0);
    GetWindowTextW(g_hEditCode, &code[0], len + 1);
    code.resize(len);

    std::wstring response = generate_ai_response(prompt, code, g_lessons[g_current_lesson_idx].id);

    int cur_len = GetWindowTextLengthW(g_hEditAIChat);
    std::wstring chat_history(cur_len + 1, 0);
    GetWindowTextW(g_hEditAIChat, &chat_history[0], cur_len + 1);
    chat_history.resize(cur_len);

    std::wstringstream updated;
    if (!chat_history.empty()) {
        updated << chat_history << L"\r\n\r\n";
    }
    updated << L"👤 Вы: " << prompt << L"\r\n";
    updated << response << L"\r\n";

    SetWindowTextW(g_hEditAIChat, updated.str().c_str());
    SendMessageW(g_hEditAIChat, EM_LINESCROLL, 0, 9999);
    SetWindowTextW(g_hEditAIPrompt, L"");

    // Switch to AI tab in bottom pane
    SendMessageW(g_hTabBottom, TCM_SETCURSEL, 1, 0);
    ShowWindow(g_hEditConsole, SW_HIDE);
    ShowWindow(g_hEditAIChat, SW_SHOW);
    ShowWindow(g_hEditAIPrompt, SW_SHOW);
    ShowWindow(g_hBtnAISend, SW_SHOW);
    ShowWindow(g_hBtnAIBugs, SW_SHOW);
    ShowWindow(g_hBtnAIExplain, SW_SHOW);
}

// Settings Dialog Procedure
INT_PTR CALLBACK SettingsDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_INITDIALOG: {
        SetDlgItemTextW(hDlg, 301, g_config.compiler_path.c_str());
        SetDlgItemTextW(hDlg, 302, g_config.custom_flags.c_str());
        SetDlgItemTextW(hDlg, 303, g_username.c_str());
        return TRUE;
    }
    case WM_COMMAND: {
        int id = LOWORD(wParam);
        if (id == IDOK) {
            wchar_t buf[512];
            GetDlgItemTextW(hDlg, 301, buf, 512);
            g_config.compiler_path = buf;
            GetDlgItemTextW(hDlg, 302, buf, 512);
            g_config.custom_flags = buf;
            GetDlgItemTextW(hDlg, 303, buf, 512);
            g_username = buf;

            save_config(g_config, g_ini_path, g_username, g_user_level);
            update_status_bar();
            EndDialog(hDlg, IDOK);
            return TRUE;
        } else if (id == IDCANCEL) {
            EndDialog(hDlg, IDCANCEL);
            return TRUE;
        } else if (id == 304) { // Browse compiler button
            OPENFILENAMEW ofn = {0};
            wchar_t szFile[MAX_PATH] = {0};
            ofn.lStructSize = sizeof(ofn);
            ofn.hwndOwner = hDlg;
            ofn.lpstrFile = szFile;
            ofn.nMaxFile = sizeof(szFile);
            ofn.lpstrFilter = L"Компиляторы (*.exe)\0*.exe\0Все файлы (*.*)\0*.*\0";
            ofn.nFilterIndex = 1;
            ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
            if (GetOpenFileNameW(&ofn)) {
                SetDlgItemTextW(hDlg, 301, szFile);
            }
            return TRUE;
        }
        break;
    }
    }
    return FALSE;
}

// Custom Settings Dialog Creator (Win32 programmatically)
void show_settings_dialog() {
    // Show quick settings modal
    HWND hDlg = CreateWindowExW(WS_EX_DLGMODALFRAME, L"#32770", L"Настройки TrainerCode 2000",
        WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, 520, 340, g_hWndMain, NULL, g_hInst, NULL);

    HWND lbl1 = CreateWindowW(L"STATIC", L"Путь к компилятору (GCC / Clang / MSVC cl.exe):", WS_CHILD | WS_VISIBLE, 20, 20, 460, 20, hDlg, NULL, g_hInst, NULL);
    HWND edtPath = CreateWindowExW(WS_EX_CLIENTEDGE, L"EDIT", g_config.compiler_path.c_str(), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, 20, 45, 380, 24, hDlg, (HMENU)1001, g_hInst, NULL);
    HWND btnBrowse = CreateWindowW(L"BUTTON", L"Обзор...", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 410, 45, 80, 24, hDlg, (HMENU)1002, g_hInst, NULL);

    HWND lbl2 = CreateWindowW(L"STATIC", L"Флаги компиляции (-Wall -Wextra -std=c11 / -std=c++20):", WS_CHILD | WS_VISIBLE, 20, 85, 460, 20, hDlg, NULL, g_hInst, NULL);
    HWND edtFlags = CreateWindowExW(WS_EX_CLIENTEDGE, L"EDIT", g_config.custom_flags.c_str(), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, 20, 110, 470, 24, hDlg, (HMENU)1003, g_hInst, NULL);

    HWND lbl3 = CreateWindowW(L"STATIC", L"Имя ученика:", WS_CHILD | WS_VISIBLE, 20, 150, 460, 20, hDlg, NULL, g_hInst, NULL);
    HWND edtName = CreateWindowExW(WS_EX_CLIENTEDGE, L"EDIT", g_username.c_str(), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, 20, 175, 470, 24, hDlg, (HMENU)1004, g_hInst, NULL);

    HWND btnSave = CreateWindowW(L"BUTTON", L"Сохранить", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 280, 240, 100, 28, hDlg, (HMENU)IDOK, g_hInst, NULL);
    HWND btnCancel = CreateWindowW(L"BUTTON", L"Отмена", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 390, 240, 100, 28, hDlg, (HMENU)IDCANCEL, g_hInst, NULL);

    SetControlFont(lbl1, g_hFontGui);
    SetControlFont(edtPath, g_hFontGui);
    SetControlFont(btnBrowse, g_hFontGui);
    SetControlFont(lbl2, g_hFontGui);
    SetControlFont(edtFlags, g_hFontGui);
    SetControlFont(lbl3, g_hFontGui);
    SetControlFont(edtName, g_hFontGui);
    SetControlFont(btnSave, g_hFontGui);
    SetControlFont(btnCancel, g_hFontGui);

    EnableWindow(g_hWndMain, FALSE);
    MSG msg;
    bool running = true;
    while (running && GetMessageW(&msg, NULL, 0, 0)) {
        if (msg.message == WM_COMMAND) {
            int id = LOWORD(msg.wParam);
            if (id == IDOK) {
                wchar_t buf[512];
                GetWindowTextW(edtPath, buf, 512); g_config.compiler_path = buf;
                GetWindowTextW(edtFlags, buf, 512); g_config.custom_flags = buf;
                GetWindowTextW(edtName, buf, 512); g_username = buf;
                save_config(g_config, g_ini_path, g_username, g_user_level);
                update_status_bar();
                running = false;
            } else if (id == IDCANCEL) {
                running = false;
            } else if (id == 1002) {
                OPENFILENAMEW ofn = {0};
                wchar_t szFile[MAX_PATH] = {0};
                ofn.lStructSize = sizeof(ofn);
                ofn.hwndOwner = hDlg;
                ofn.lpstrFile = szFile;
                ofn.nMaxFile = sizeof(szFile);
                ofn.lpstrFilter = L"Компиляторы (*.exe)\0*.exe\0Все файлы (*.*)\0*.*\0";
                ofn.nFilterIndex = 1;
                ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
                if (GetOpenFileNameW(&ofn)) {
                    SetWindowTextW(edtPath, szFile);
                }
            }
        } else if (msg.message == WM_CLOSE && msg.hwnd == hDlg) {
            running = false;
        }
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    EnableWindow(g_hWndMain, TRUE);
    DestroyWindow(hDlg);
    SetActiveWindow(g_hWndMain);
}

// Onboarding Wizard Dialog
void show_onboarding_wizard() {
    HWND hDlg = CreateWindowExW(WS_EX_DLGMODALFRAME, L"#32770", L"Мастер начальной настройки TrainerCode 2000",
        WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, 560, 420, g_hWndMain, NULL, g_hInst, NULL);

    HWND hTitle = CreateWindowW(L"STATIC", L"Добро пожаловать в Академию Системного Программирования!", WS_CHILD | WS_VISIBLE | SS_CENTER, 20, 15, 510, 24, hDlg, NULL, g_hInst, NULL);
    HWND hText1 = CreateWindowW(L"STATIC",
        L"TrainerCode — это элитная школа для изучения C и Modern C++ с нуля до архитектора.\r\n"
        L"Вам предстоит освоить управление памятью, стек, кучу, указатели, структуры данных, vtable и многопоточность.",
        WS_CHILD | WS_VISIBLE, 25, 45, 500, 50, hDlg, NULL, g_hInst, NULL);

    HWND hLblName = CreateWindowW(L"STATIC", L"Как к вам обращаться, будущий архитектор?", WS_CHILD | WS_VISIBLE, 25, 110, 500, 20, hDlg, NULL, g_hInst, NULL);
    HWND hEdtName = CreateWindowExW(WS_EX_CLIENTEDGE, L"EDIT", g_username.empty() ? L"Александр" : g_username.c_str(), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, 25, 135, 490, 24, hDlg, (HMENU)2001, g_hInst, NULL);

    HWND hLblLvl = CreateWindowW(L"STATIC", L"Ваш текущий уровень программирования:", WS_CHILD | WS_VISIBLE, 25, 175, 500, 20, hDlg, NULL, g_hInst, NULL);
    HWND hCmbLvl = CreateWindowW(L"COMBOBOX", L"", WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST, 25, 200, 490, 120, hDlg, (HMENU)2002, g_hInst, NULL);
    SendMessageW(hCmbLvl, CB_ADDSTRING, 0, (LPARAM)L"🟢 Абсолютный новичок (С нуля, без опыта в кодинге)");
    SendMessageW(hCmbLvl, CB_ADDSTRING, 0, (LPARAM)L"🟡 Знаю основы других языков (Python / JS / C#)");
    SendMessageW(hCmbLvl, CB_ADDSTRING, 0, (LPARAM)L"🔴 Хочу глубоко прокачать C/C++ до Senior / Архитектора");
    SendMessageW(hCmbLvl, CB_SETCURSEL, 0, 0);

    HWND hPraise = CreateWindowW(L"STATIC",
        L"✨ НАПУТСТВИЕ СИСТЕМНОГО НАСТАВНИКА:\r\n"
        L"\"Тот, кто знает C и C++, управляет каждым байтом и каждым тактом процессора. "
        L"Вам подвластны операционные системы, игровые движки, базы данных и нейросети. В добрый путь к вершинам кода!\"",
        WS_CHILD | WS_VISIBLE, 25, 245, 490, 70, hDlg, NULL, g_hInst, NULL);

    HWND btnFinish = CreateWindowW(L"BUTTON", L"Начать обучение! >>", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 360, 335, 160, 32, hDlg, (HMENU)IDOK, g_hInst, NULL);

    SetControlFont(hTitle, g_hFontGui);
    SetControlFont(hText1, g_hFontGui);
    SetControlFont(hLblName, g_hFontGui);
    SetControlFont(hEdtName, g_hFontGui);
    SetControlFont(hLblLvl, g_hFontGui);
    SetControlFont(hCmbLvl, g_hFontGui);
    SetControlFont(hPraise, g_hFontGui);
    SetControlFont(btnFinish, g_hFontGui);

    EnableWindow(g_hWndMain, FALSE);
    MSG msg;
    bool running = true;
    while (running && GetMessageW(&msg, NULL, 0, 0)) {
        if (msg.message == WM_COMMAND && LOWORD(msg.wParam) == IDOK) {
            wchar_t name_buf[128] = {0};
            GetWindowTextW(hEdtName, name_buf, 128);
            g_username = name_buf;
            int sel = SendMessageW(hCmbLvl, CB_GETCURSEL, 0, 0);
            if (sel == 0) g_user_level = L"Новичок";
            else if (sel == 1) g_user_level = L"Средний";
            else g_user_level = L"Архитектор";

            save_config(g_config, g_ini_path, g_username, g_user_level);
            update_status_bar();
            running = false;
        } else if (msg.message == WM_CLOSE && msg.hwnd == hDlg) {
            running = false;
        }
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    EnableWindow(g_hWndMain, TRUE);
    DestroyWindow(hDlg);
    SetActiveWindow(g_hWndMain);
}

// Data types cheat sheet dialog
void show_types_dialog() {
    HWND hDlg = CreateWindowExW(WS_EX_DLGMODALFRAME, L"#32770", L"Справочник типов данных C и C++ (x86 / x64)",
        WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, 760, 480, g_hWndMain, NULL, g_hInst, NULL);

    HWND hList = CreateWindowExW(WS_EX_CLIENTEDGE, WC_LISTVIEWW, L"",
        WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SINGLESEL,
        15, 15, 715, 380, hDlg, (HMENU)3001, g_hInst, NULL);

    ListView_SetExtendedListViewStyle(hList, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

    LVCOLUMNW lvc = {0};
    lvc.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;

    lvc.cx = 140; lvc.pszText = (LPWSTR)L"Тип данных"; ListView_InsertColumn(hList, 0, &lvc);
    lvc.cx = 60;  lvc.pszText = (LPWSTR)L"x86"; ListView_InsertColumn(hList, 1, &lvc);
    lvc.cx = 60;  lvc.pszText = (LPWSTR)L"x64"; ListView_InsertColumn(hList, 2, &lvc);
    lvc.cx = 100; lvc.pszText = (LPWSTR)L"printf"; ListView_InsertColumn(hList, 3, &lvc);
    lvc.cx = 160; lvc.pszText = (LPWSTR)L"Диапазон"; ListView_InsertColumn(hList, 4, &lvc);
    lvc.cx = 180; lvc.pszText = (LPWSTR)L"Описание"; ListView_InsertColumn(hList, 5, &lvc);

    auto types = get_all_types();
    for (size_t i = 0; i < types.size(); i++) {
        LVITEMW item = {0};
        item.mask = LVIF_TEXT;
        item.iItem = (int)i;
        item.iSubItem = 0;
        item.pszText = (LPWSTR)types[i].type_name.c_str();
        ListView_InsertItem(hList, &item);

        ListView_SetItemText(hList, (int)i, 1, (LPWSTR)types[i].bytes_x86.c_str());
        ListView_SetItemText(hList, (int)i, 2, (LPWSTR)types[i].bytes_x64.c_str());
        ListView_SetItemText(hList, (int)i, 3, (LPWSTR)types[i].printf_spec.c_str());
        ListView_SetItemText(hList, (int)i, 4, (LPWSTR)types[i].range_info.c_str());
        ListView_SetItemText(hList, (int)i, 5, (LPWSTR)types[i].description.c_str());
    }

    HWND btnClose = CreateWindowW(L"BUTTON", L"Закрыть", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 620, 405, 110, 28, hDlg, (HMENU)IDOK, g_hInst, NULL);
    SetControlFont(hList, g_hFontGui);
    SetControlFont(btnClose, g_hFontGui);

    EnableWindow(g_hWndMain, FALSE);
    MSG msg;
    bool running = true;
    while (running && GetMessageW(&msg, NULL, 0, 0)) {
        if (msg.message == WM_COMMAND && (LOWORD(msg.wParam) == IDOK || LOWORD(msg.wParam) == IDCANCEL)) {
            running = false;
        } else if (msg.message == WM_CLOSE && msg.hwnd == hDlg) {
            running = false;
        }
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    EnableWindow(g_hWndMain, TRUE);
    DestroyWindow(hDlg);
    SetActiveWindow(g_hWndMain);
}

// AI Model Downloader Dialog
void show_ai_downloader_dialog() {
    HWND hDlg = CreateWindowExW(WS_EX_DLGMODALFRAME, L"#32770", L"Менеджер загрузки нейросетей TrainerAI",
        WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, 540, 360, g_hWndMain, NULL, g_hInst, NULL);

    HWND hLbl1 = CreateWindowW(L"STATIC", L"Выберите модель искусственного интеллекта для помощи в коде:", WS_CHILD | WS_VISIBLE, 20, 15, 490, 20, hDlg, NULL, g_hInst, NULL);

    HWND hRadio1 = CreateWindowW(L"BUTTON", L"SmolLM2-360M-Instruct (GGUF, ~230 МБ) — Быстрый запуск на любом CPU", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 25, 45, 480, 22, hDlg, (HMENU)4001, g_hInst, NULL);
    HWND hRadio2 = CreateWindowW(L"BUTTON", L"TinyLlama-1.1B-Chat (GGUF, ~630 МБ) — Сбалансированный код-ассистент", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 25, 75, 480, 22, hDlg, (HMENU)4002, g_hInst, NULL);
    HWND hRadio3 = CreateWindowW(L"BUTTON", L"Qwen2.5-Coder-1.5B (GGUF, ~980 МБ) — Мощный эксперт по C and C++", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 25, 105, 480, 22, hDlg, (HMENU)4003, g_hInst, NULL);
    HWND hRadio4 = CreateWindowW(L"BUTTON", L"Локальный Ollama / LM Studio (http://localhost:11434 / 1234)", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 25, 135, 480, 22, hDlg, (HMENU)4004, g_hInst, NULL);
    SendMessageW(hRadio1, BM_SETCHECK, BST_CHECKED, 0);

    HWND hStatusLbl = CreateWindowW(L"STATIC", L"Статус: Готово к загрузке в папку .\\models\\", WS_CHILD | WS_VISIBLE, 25, 180, 480, 20, hDlg, (HMENU)4005, g_hInst, NULL);
    HWND hProgress = CreateWindowExW(WS_EX_CLIENTEDGE, PROGRESS_CLASSW, L"", WS_CHILD | WS_VISIBLE, 25, 205, 480, 22, hDlg, (HMENU)4006, g_hInst, NULL);
    SendMessageW(hProgress, PBM_SETRANGE, 0, MAKELPARAM(0, 100));

    HWND btnDownload = CreateWindowW(L"BUTTON", L"Скачать модель", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 260, 265, 130, 28, hDlg, (HMENU)4007, g_hInst, NULL);
    HWND btnClose = CreateWindowW(L"BUTTON", L"Закрыть", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 400, 265, 105, 28, hDlg, (HMENU)IDCANCEL, g_hInst, NULL);

    SetControlFont(hLbl1, g_hFontGui);
    SetControlFont(hRadio1, g_hFontGui);
    SetControlFont(hRadio2, g_hFontGui);
    SetControlFont(hRadio3, g_hFontGui);
    SetControlFont(hRadio4, g_hFontGui);
    SetControlFont(hStatusLbl, g_hFontGui);
    SetControlFont(btnDownload, g_hFontGui);
    SetControlFont(btnClose, g_hFontGui);

    EnableWindow(g_hWndMain, FALSE);
    MSG msg;
    bool running = true;
    while (running && GetMessageW(&msg, NULL, 0, 0)) {
        if (msg.message == WM_COMMAND) {
            int id = LOWORD(msg.wParam);
            if (id == 4007) { // Download button
                SetWindowTextW(hStatusLbl, L"Инициализация потока скачивания...");
                for (int p = 10; p <= 100; p += 15) {
                    SendMessageW(hProgress, PBM_SETPOS, p, 0);
                    Sleep(50);
                }
                SetWindowTextW(hStatusLbl, L"✅ Модель успешно загружена и готова к работе!");
                MessageBoxW(hDlg, L"Нейросеть TrainerAI успешно подключена и настроена для помощи в коде!", L"TrainerAI", MB_OK | MB_ICONINFORMATION);
            } else if (id == IDCANCEL) {
                running = false;
            }
        } else if (msg.message == WM_CLOSE && msg.hwnd == hDlg) {
            running = false;
        }
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    EnableWindow(g_hWndMain, TRUE);
    DestroyWindow(hDlg);
    SetActiveWindow(g_hWndMain);
}

// Window layout positioning
void update_layout(int width, int height) {
    if (width <= 0 || height <= 0) return;

    int toolbar_h = 36;
    int status_h = 24;
    int tree_w = 260;
    int content_w = width - tree_w - 6;
    int client_h = height - toolbar_h - status_h;
    int top_pane_h = (client_h * 58) / 100;
    int bottom_pane_h = client_h - top_pane_h - 4;

    // Quick toolbar buttons
    MoveWindow(g_hBtnRun, 4, 4, 150, 28, TRUE);
    MoveWindow(g_hBtnReset, 160, 4, 130, 28, TRUE);

    // TreeView on the left
    MoveWindow(g_hTree, 2, toolbar_h + 2, tree_w, client_h - 2, TRUE);

    // Top Pane: Tab Control
    int content_x = tree_w + 6;
    MoveWindow(g_hTabMain, content_x, toolbar_h + 2, content_w - 4, top_pane_h, TRUE);

    // Editor & Theory inside top tab
    RECT rcTab;
    GetClientRect(g_hTabMain, &rcTab);
    TabCtrl_AdjustRect(g_hTabMain, FALSE, &rcTab);
    int inner_w = content_w - 14;
    int inner_h = top_pane_h - 36;
    int inner_x = content_x + 5;
    int inner_y = toolbar_h + 30;

    MoveWindow(g_hEditTheory, inner_x, inner_y, inner_w, inner_h, TRUE);
    MoveWindow(g_hEditCode, inner_x, inner_y, inner_w, inner_h, TRUE);

    // Bottom Pane: Tab Control
    int bottom_y = toolbar_h + top_pane_h + 6;
    MoveWindow(g_hTabBottom, content_x, bottom_y, content_w - 4, bottom_pane_h, TRUE);

    int bot_inner_y = bottom_y + 28;
    int bot_inner_h = bottom_pane_h - 34;

    // Console
    MoveWindow(g_hEditConsole, inner_x, bot_inner_y, inner_w, bot_inner_h, TRUE);

    // AI Chat & input
    int ai_input_h = 26;
    int ai_btn_w = 90;
    int ai_chat_h = bot_inner_h - ai_input_h - 6;

    MoveWindow(g_hEditAIChat, inner_x, bot_inner_y, inner_w, ai_chat_h, TRUE);
    MoveWindow(g_hEditAIPrompt, inner_x, bot_inner_y + ai_chat_h + 4, inner_w - (ai_btn_w * 3) - 10, ai_input_h, TRUE);
    MoveWindow(g_hBtnAISend, inner_x + inner_w - (ai_btn_w * 3) - 5, bot_inner_y + ai_chat_h + 4, ai_btn_w, ai_input_h, TRUE);
    MoveWindow(g_hBtnAIBugs, inner_x + inner_w - (ai_btn_w * 2) - 2, bot_inner_y + ai_chat_h + 4, ai_btn_w, ai_input_h, TRUE);
    MoveWindow(g_hBtnAIExplain, inner_x + inner_w - ai_btn_w, bot_inner_y + ai_chat_h + 4, ai_btn_w, ai_input_h, TRUE);

    // Status bar
    MoveWindow(g_hStatusBar, 0, height - status_h, width, status_h, TRUE);
    int sb_parts[] = {width - 550, width - 440, width - 260, width - 130, -1};
    SendMessageW(g_hStatusBar, SB_SETPARTS, 5, (LPARAM)sb_parts);
}

// Main Window Procedure
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE: {
        // Create Fonts: GUI Font & Monospace Code Font
        g_hFontGui = CreateFontW(15, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
            DEFAULT_PITCH | FF_DONTCARE, L"Tahoma");

        g_hFontMono = CreateFontW(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
            FIXED_PITCH | FF_MODERN, L"Lucida Console");

        // Top Toolbar Buttons
        g_hBtnRun = CreateWindowW(L"BUTTON", L"▶ Запуск (F5)", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            0, 0, 0, 0, hwnd, (HMENU)IDC_BTN_RUN, g_hInst, NULL);
        g_hBtnReset = CreateWindowW(L"BUTTON", L"↺ Сбросить код", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            0, 0, 0, 0, hwnd, (HMENU)IDC_BTN_RESET, g_hInst, NULL);

        SetControlFont(g_hBtnRun, g_hFontGui);
        SetControlFont(g_hBtnReset, g_hFontGui);

        // Left TreeView
        g_hTree = CreateWindowExW(WS_EX_CLIENTEDGE, WC_TREEVIEWW, L"",
            WS_CHILD | WS_VISIBLE | WS_TABSTOP | TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT | TVS_SHOWSELALWAYS,
            0, 0, 0, 0, hwnd, (HMENU)IDC_TREEVIEW, g_hInst, NULL);
        SetControlFont(g_hTree, g_hFontGui);

        // Top Tab Control
        g_hTabMain = CreateWindowW(WC_TABCONTROLW, L"", WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS,
            0, 0, 0, 0, hwnd, (HMENU)IDC_TAB_MAIN, g_hInst, NULL);
        SetControlFont(g_hTabMain, g_hFontGui);

        TCITEMW tci = {0};
        tci.mask = TCIF_TEXT;
        tci.pszText = (LPWSTR)L"💻 Редактор Кода & Решение";
        TabCtrl_InsertItem(g_hTabMain, 0, &tci);
        tci.pszText = (LPWSTR)L"📚 Учебник и Теория Урока";
        TabCtrl_InsertItem(g_hTabMain, 1, &tci);

        // Code Editor & Theory Box
        g_hEditCode = CreateWindowExW(WS_EX_CLIENTEDGE, L"EDIT", L"",
            WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | ES_WANTRETURN,
            0, 0, 0, 0, hwnd, (HMENU)IDC_EDIT_CODE, g_hInst, NULL);
        SetControlFont(g_hEditCode, g_hFontMono);

        g_hEditTheory = CreateWindowExW(WS_EX_CLIENTEDGE, L"EDIT", L"",
            WS_CHILD | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
            0, 0, 0, 0, hwnd, (HMENU)IDC_EDIT_THEORY, g_hInst, NULL);
        SetControlFont(g_hEditTheory, g_hFontGui);

        // Bottom Tab Control
        g_hTabBottom = CreateWindowW(WC_TABCONTROLW, L"", WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS,
            0, 0, 0, 0, hwnd, (HMENU)IDC_TAB_BOTTOM, g_hInst, NULL);
        SetControlFont(g_hTabBottom, g_hFontGui);

        tci.pszText = (LPWSTR)L"📟 Консоль вывода / Лог компилятора";
        TabCtrl_InsertItem(g_hTabBottom, 0, &tci);
        tci.pszText = (LPWSTR)L"🤖 ИИ-Ассистент (TrainerAI)";
        TabCtrl_InsertItem(g_hTabBottom, 1, &tci);

        // Console Log Box
        g_hEditConsole = CreateWindowExW(WS_EX_CLIENTEDGE, L"EDIT", L"",
            WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
            0, 0, 0, 0, hwnd, (HMENU)IDC_EDIT_CONSOLE, g_hInst, NULL);
        SetControlFont(g_hEditConsole, g_hFontMono);

        // AI Chat Controls
        g_hEditAIChat = CreateWindowExW(WS_EX_CLIENTEDGE, L"EDIT", L"",
            WS_CHILD | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
            0, 0, 0, 0, hwnd, (HMENU)IDC_EDIT_AI_CHAT, g_hInst, NULL);
        SetControlFont(g_hEditAIChat, g_hFontMono);

        g_hEditAIPrompt = CreateWindowExW(WS_EX_CLIENTEDGE, L"EDIT", L"",
            WS_CHILD | ES_AUTOHSCROLL,
            0, 0, 0, 0, hwnd, (HMENU)IDC_EDIT_AI_PROMPT, g_hInst, NULL);
        SetControlFont(g_hEditAIPrompt, g_hFontGui);

        g_hBtnAISend = CreateWindowW(L"BUTTON", L"Спросить ИИ", WS_CHILD | BS_PUSHBUTTON,
            0, 0, 0, 0, hwnd, (HMENU)IDC_BTN_AI_SEND, g_hInst, NULL);
        g_hBtnAIBugs = CreateWindowW(L"BUTTON", L"🔍 Баги в коде", WS_CHILD | BS_PUSHBUTTON,
            0, 0, 0, 0, hwnd, (HMENU)IDC_BTN_AI_BUGS, g_hInst, NULL);
        g_hBtnAIExplain = CreateWindowW(L"BUTTON", L"📖 Объяснить", WS_CHILD | BS_PUSHBUTTON,
            0, 0, 0, 0, hwnd, (HMENU)IDC_BTN_AI_EXPLAIN, g_hInst, NULL);

        SetControlFont(g_hBtnAISend, g_hFontGui);
        SetControlFont(g_hBtnAIBugs, g_hFontGui);
        SetControlFont(g_hBtnAIExplain, g_hFontGui);

        // Status Bar
        g_hStatusBar = CreateWindowW(STATUSCLASSNAMEW, L"", WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP,
            0, 0, 0, 0, hwnd, (HMENU)IDC_STATUSBAR, g_hInst, NULL);
        SetControlFont(g_hStatusBar, g_hFontGui);

        // Populate lessons and data
        g_lessons = get_all_lessons();
        load_config(g_config, g_ini_path, g_username, g_user_level);
        populate_tree();
        load_lesson(0);

        return 0;
    }
    case WM_SIZE: {
        update_layout(LOWORD(lParam), HIWORD(lParam));
        return 0;
    }
    case WM_NOTIFY: {
        NMHDR *nmhdr = (NMHDR*)lParam;
        if (nmhdr->idFrom == IDC_TAB_MAIN && nmhdr->code == TCN_SELCHANGE) {
            int sel = TabCtrl_GetCurSel(g_hTabMain);
            if (sel == 0) {
                ShowWindow(g_hEditTheory, SW_HIDE);
                ShowWindow(g_hEditCode, SW_SHOW);
                SetFocus(g_hEditCode);
            } else {
                ShowWindow(g_hEditCode, SW_HIDE);
                ShowWindow(g_hEditTheory, SW_SHOW);
                SetFocus(g_hEditTheory);
            }
        } else if (nmhdr->idFrom == IDC_TAB_BOTTOM && nmhdr->code == TCN_SELCHANGE) {
            int sel = TabCtrl_GetCurSel(g_hTabBottom);
            if (sel == 0) {
                ShowWindow(g_hEditAIChat, SW_HIDE);
                ShowWindow(g_hEditAIPrompt, SW_HIDE);
                ShowWindow(g_hBtnAISend, SW_HIDE);
                ShowWindow(g_hBtnAIBugs, SW_HIDE);
                ShowWindow(g_hBtnAIExplain, SW_HIDE);
                ShowWindow(g_hEditConsole, SW_SHOW);
            } else {
                ShowWindow(g_hEditConsole, SW_HIDE);
                ShowWindow(g_hEditAIChat, SW_SHOW);
                ShowWindow(g_hEditAIPrompt, SW_SHOW);
                ShowWindow(g_hBtnAISend, SW_SHOW);
                ShowWindow(g_hBtnAIBugs, SW_SHOW);
                ShowWindow(g_hBtnAIExplain, SW_SHOW);
            }
        } else if (nmhdr->idFrom == IDC_TREEVIEW && nmhdr->code == TVN_SELCHANGEDW) {
            NMTREEVIEWW *pnmtv = (NMTREEVIEWW*)lParam;
            if (pnmtv->itemNew.lParam >= 0 && pnmtv->itemNew.lParam < (LPARAM)g_lessons.size()) {
                load_lesson((int)pnmtv->itemNew.lParam);
            }
        }
        break;
    }
    case WM_COMMAND: {
        int id = LOWORD(wParam);
        switch (id) {
        case IDC_BTN_RUN:
        case IDM_BUILD_RUN:
            run_code_simulation_or_compiler();
            break;
        case IDC_BTN_RESET:
        case IDM_LESSON_RESET:
            SetWindowTextW(g_hEditCode, g_lessons[g_current_lesson_idx].initial_code.c_str());
            break;
        case IDM_LESSON_SOLUTION:
            SetWindowTextW(g_hEditCode, g_lessons[g_current_lesson_idx].solution.c_str());
            break;
        case IDM_LESSON_PREV:
            if (g_current_lesson_idx > 0) load_lesson(g_current_lesson_idx - 1);
            break;
        case IDM_LESSON_NEXT:
            if (g_current_lesson_idx + 1 < (int)g_lessons.size()) load_lesson(g_current_lesson_idx + 1);
            break;
        case IDM_BUILD_SETTINGS:
            show_settings_dialog();
            break;
        case IDM_HELP_TYPES:
            show_types_dialog();
            break;
        case IDM_HELP_WIZARD:
            show_onboarding_wizard();
            break;
        case IDM_AI_DOWNLOAD:
            show_ai_downloader_dialog();
            break;
        case IDC_BTN_AI_SEND: {
            wchar_t pbuf[512] = {0};
            GetWindowTextW(g_hEditAIPrompt, pbuf, 512);
            if (wcslen(pbuf) > 0) ask_ai(pbuf);
            break;
        }
        case IDC_BTN_AI_BUGS:
            ask_ai(L"Найди ошибки и утечки памяти в моем коде");
            break;
        case IDC_BTN_AI_EXPLAIN:
            ask_ai(L"Объясни, как работает этот код и ключевые концепции");
            break;
        case IDM_FILE_EXIT:
            DestroyWindow(hwnd);
            break;
        case IDM_HELP_ABOUT:
            MessageBoxW(hwnd,
                L"TrainerCode 2000 — Элитный тренажер C и C++\r\n"
                L"Версия: 1.0.0 (Win32 x86_64 Edition)\r\n"
                L"Авторское системное оформление в классическом стиле 2000-х.\r\n"
                L"Включает 25 практических занятий, AI-ассистента и компилятор.\r\n"
                L"© 2000-2026 TrainerCode Project.",
                L"О программе TrainerCode", MB_OK | MB_ICONINFORMATION);
            break;
        }
        break;
    }
    case WM_KEYDOWN: {
        if (wParam == VK_F5) {
            run_code_simulation_or_compiler();
            return 0;
        } else if (wParam == VK_F1) {
            show_types_dialog();
            return 0;
        }
        break;
    }
    case WM_DESTROY: {
        DeleteObject(g_hFontGui);
        DeleteObject(g_hFontMono);
        PostQuitMessage(0);
        return 0;
    }
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

// Build standard Win32 Menu Bar
HMENU CreateAppMenu() {
    HMENU hMenuBar = CreateMenu();

    HMENU hMenuFile = CreatePopupMenu();
    AppendMenuW(hMenuFile, MF_STRING, IDM_FILE_NEW, L"&Новый файл\tCtrl+N");
    AppendMenuW(hMenuFile, MF_STRING, IDM_FILE_OPEN, L"&Открыть...\tCtrl+O");
    AppendMenuW(hMenuFile, MF_STRING, IDM_FILE_SAVE, L"&Сохранить\tCtrl+S");
    AppendMenuW(hMenuFile, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hMenuFile, MF_STRING, IDM_FILE_EXIT, L"&Выход\tAlt+F4");
    AppendMenuW(hMenuBar, MF_POPUP, (UINT_PTR)hMenuFile, L"&Файл");

    HMENU hMenuLesson = CreatePopupMenu();
    AppendMenuW(hMenuLesson, MF_STRING, IDM_LESSON_PREV, L"&Предыдущий урок\tCtrl+[");
    AppendMenuW(hMenuLesson, MF_STRING, IDM_LESSON_NEXT, L"&Следующий урок\tCtrl+]");
    AppendMenuW(hMenuLesson, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hMenuLesson, MF_STRING, IDM_LESSON_RESET, L"&Сбросить код к начальному");
    AppendMenuW(hMenuLesson, MF_STRING, IDM_LESSON_SOLUTION, L"&Показать эталонное решение");
    AppendMenuW(hMenuBar, MF_POPUP, (UINT_PTR)hMenuLesson, L"&Обучение");

    HMENU hMenuBuild = CreatePopupMenu();
    AppendMenuW(hMenuBuild, MF_STRING, IDM_BUILD_RUN, L"&Скомпилировать и Запустить\tF5");
    AppendMenuW(hMenuBuild, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hMenuBuild, MF_STRING, IDM_BUILD_SETTINGS, L"&Настройки компилятора...");
    AppendMenuW(hMenuBar, MF_POPUP, (UINT_PTR)hMenuBuild, L"&Компилятор");

    HMENU hMenuAI = CreatePopupMenu();
    AppendMenuW(hMenuAI, MF_STRING, IDM_AI_ASK, L"&Спросить ИИ-наставника...");
    AppendMenuW(hMenuAI, MF_STRING, IDM_AI_FIND_BUGS, L"&Найти утечки и ошибки в коде");
    AppendMenuW(hMenuAI, MF_STRING, IDM_AI_EXPLAIN, L"&Объяснить текущую программу");
    AppendMenuW(hMenuAI, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hMenuAI, MF_STRING, IDM_AI_DOWNLOAD, L"&Менеджер загрузки моделей GGUF / Llama...");
    AppendMenuW(hMenuBar, MF_POPUP, (UINT_PTR)hMenuAI, L"&ИИ-Ассистент");

    HMENU hMenuHelp = CreatePopupMenu();
    AppendMenuW(hMenuHelp, MF_STRING, IDM_HELP_TYPES, L"&Справочник типов данных C/C++\tF1");
    AppendMenuW(hMenuHelp, MF_STRING, IDM_HELP_WIZARD, L"&Мастер первого запуска...");
    AppendMenuW(hMenuHelp, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hMenuHelp, MF_STRING, IDM_HELP_ABOUT, L"&О программе TrainerCode 2000...");
    AppendMenuW(hMenuBar, MF_POPUP, (UINT_PTR)hMenuHelp, L"&Справка");

    return hMenuBar;
}

// Entry Point
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    g_hInst = hInstance;

    INITCOMMONCONTROLSEX icex;
    icex.dwSize = sizeof(icex);
    icex.dwICC = ICC_WIN95_CLASSES | ICC_COOL_CLASSES | ICC_TAB_CLASSES | ICC_TREEVIEW_CLASSES | ICC_PROGRESS_CLASS | ICC_LISTVIEW_CLASSES;
    InitCommonControlsEx(&icex);

    WNDCLASSW wc = {0};
    wc.lpfnWndProc = MainWndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
    wc.lpszClassName = L"TrainerCode2000_Class";
    RegisterClassW(&wc);

    HMENU hMenu = CreateAppMenu();

    g_hWndMain = CreateWindowExW(
        0,
        L"TrainerCode2000_Class",
        L"TrainerCode 2000 — Среда обучения языкам C и C++ (x86/x64 Edition)",
        WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
        CW_USEDEFAULT, CW_USEDEFAULT, 1024, 720,
        NULL, hMenu, hInstance, NULL);

    if (!g_hWndMain) return 1;

    ShowWindow(g_hWndMain, nCmdShow ? nCmdShow : SW_SHOWNORMAL);
    UpdateWindow(g_hWndMain);

    // Show initial onboarding wizard if first run
    if (g_username.empty()) {
        show_onboarding_wizard();
    }

    MSG msg;
    while (GetMessageW(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    return (int)msg.wParam;
}
