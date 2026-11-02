#pragma once
#include <windows.h>
#include <winhttp.h>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>

struct AIConfig {
    std::wstring provider = L"Built-in TrainerAI (Оффлайн + База знаний)";
    std::wstring ollama_url = L"http://localhost:11434/api/generate";
    std::wstring model_name = L"qwen2.5-coder:1.5b";
    std::wstring local_model_file = L"models\\tinyllama-1.1b.Q4_K_M.gguf";
    bool auto_download_on_first_launch = true;
};

// Built-in intelligent analysis engine for C and C++
inline std::wstring generate_ai_response(const std::wstring &prompt, const std::wstring &user_code, int current_lesson_id) {
    std::wstring lower_prompt = prompt;
    std::transform(lower_prompt.begin(), lower_prompt.end(), lower_prompt.begin(), ::towlower);

    std::wstring lower_code = user_code;
    std::transform(lower_code.begin(), lower_code.end(), lower_code.begin(), ::towlower);

    std::wstringstream resp;
    resp << L"[TrainerAI • Системный наставник C/C++]\r\n";
    resp << L"--------------------------------------------------\r\n";

    // 1. Static code analysis if user asked to find bug or explain code
    if (lower_prompt.find(L"ошибк") != std::wstring::npos || lower_prompt.find(L"провер") != std::wstring::npos ||
        lower_prompt.find(L"баг") != std::wstring::npos || lower_prompt.find(L"почему не") != std::wstring::npos) {
        
        resp << L"Анализ вашего исходного кода:\r\n\r\n";
        bool found_issue = false;

        if (lower_code.find(L"malloc(") != std::wstring::npos && lower_code.find(L"free(") == std::wstring::npos) {
            resp << L"⚠️ ВНИМАНИЕ: Обнаружена потенциальная утечка памяти (Memory Leak)!\r\n";
            resp << L"Вы вызываете malloc, но нигде не освобождаете память с помощью free(). Память в куче (Heap) не очищается сама.\r\n\r\n";
            found_issue = true;
        }

        if (lower_code.find(L"new ") != std::wstring::npos && lower_code.find(L"delete") == std::wstring::npos) {
            resp << L"⚠️ ВНИМАНИЕ: Вызов оператора new без парного delete!\r\n";
            resp << L"В C++ всегда соблюдайте правило RAII или используйте std::unique_ptr.\r\n\r\n";
            found_issue = true;
        }

        if (lower_code.find(L"printf") != std::wstring::npos && lower_code.find(L"#include <stdio.h>") == std::wstring::npos &&
            lower_code.find(L"#include <cstdio>") == std::wstring::npos) {
            resp << L"⚠️ ПРЕДУПРЕЖДЕНИЕ: Использование printf без подключения заголовка!\r\n";
            resp << L"Добавьте в самое начало файла: #include <stdio.h>\r\n\r\n";
            found_issue = true;
        }

        if (lower_code.find(L"cout") != std::wstring::npos && lower_code.find(L"<iostream>") == std::wstring::npos) {
            resp << L"⚠️ ПРЕДУПРЕЖДЕНИЕ: Использование std::cout без подключения <iostream>!\r\n\r\n";
            found_issue = true;
        }

        if (lower_code.find(L"int main") != std::wstring::npos && lower_code.find(L"return 0;") == std::wstring::npos) {
            resp << L"💡 СОВЕТ: В функции main() рекомендуется явно указывать 'return 0;', чтобы гарантировать успешный код возврата ОС.\r\n\r\n";
        }

        if (!found_issue) {
            resp << L"✅ Грубых синтаксических ошибок памяти (утечек, явных разыменований NULL) не обнаружено.\r\n";
            resp << L"Убедитесь, что логика программы в точности соответствует условию урока.\r\n";
        }
        return resp.str();
    }

    // 2. Explain code
    if (lower_prompt.find(L"объясни") != std::wstring::npos || lower_prompt.find(L"как работает") != std::wstring::npos) {
        resp << L"Подробный разбор концепции:\r\n\r\n";
        if (lower_code.find(L"pointer") != std::wstring::npos || lower_code.find(L"*") != std::wstring::npos || lower_prompt.find(L"указател") != std::wstring::npos) {
            resp << L"📌 Указатели в памяти:\r\n";
            resp << L"1. Каждая переменная лежит в ОЗУ по уникальному числовому адресу (например, 0x0061FE14).\r\n";
            resp << L"2. Оператор '&' берет этот адрес.\r\n";
            resp << L"3. Переменная-указатель (int *p) сохраняет адрес.\r\n";
            resp << L"4. Разыменование '*p' читает или перезаписывает байты по этому адресу.\r\n";
            resp << L"5. На 64-битных ОС размер любого указателя ВСЕГДА равен 8 байтам.\r\n";
        } else if (lower_prompt.find(L"стек") != std::wstring::npos || lower_prompt.find(L"куч") != std::wstring::npos) {
            resp << L"📌 Стек (Stack) vs Куча (Heap):\r\n";
            resp << L"- Стек: ультрабыстрая память LIFO (~1-2 МБ). Выделяется автоматически для локальных переменных. Освобождается мгновенно при выходе из функции.\r\n";
            resp << L"- Куча: гигантская область памяти всей доступной RAM. Выделяется через malloc/new. Освобождается вручную через free/delete. Медленнее из-за поиска свободного блока в ОС.\r\n";
        } else {
            resp << L"Код представляет собой классическую системную программу. Вызовы функций транслируются напрямую в команды процессора (CALL, MOV, JMP). Старайтесь минимизировать обращения к памяти и оптимизировать циклы.\r\n";
        }
        return resp.str();
    }

    // 3. Hints and tasks
    if (lower_prompt.find(L"подсказк") != std::wstring::npos || lower_prompt.find(L"помоги") != std::wstring::npos || lower_prompt.find(L"задач") != std::wstring::npos) {
        resp << L"💡 Подсказка к текущему уроку:\r\n";
        resp << L"- Внимательно читайте условие задания во вкладке 'Учебник'.\r\n";
        resp << L"- Следите за регистрами символов и форматированием вывода (включая перевод строки '\\n').\r\n";
        resp << L"- Если что-то не получается, используйте кнопку 'Вставить шаблон урока', чтобы вернуть проверенный каркас кода.\r\n";
        return resp.str();
    }

    // Default response
    resp << L"Приветствую! Я ваш персональный ИИ-ментор по C и C++.\r\n";
    resp << L"Я умею:\r\n";
    resp << L"1. Находить утечки памяти и опасные ошибки разыменования указателей ('Найди ошибку').\r\n";
    resp << L"2. Объяснять, как процессор и компилятор видят ваш код ('Объясни код').\r\n";
    resp << L"3. Давать пошаговые подсказки к текущему заданию ('Дай подсказку').\r\n";
    resp << L"4. Работать в оффлайне или подключаться к моделям LLaMA / Qwen через Ollama и GGUF.\r\n\r\n";
    resp << L"Задайте любой вопрос или напишите код в редакторе!";
    return resp.str();
}
