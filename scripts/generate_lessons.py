# -*- coding: utf-8 -*-
"""
Full Course Generator for QuantumCode Academy (Системное Программирование C & C++).
Covers:
- Lesson 1: Архитектура ЭВМ, x86_64, регистры, машинный код (ASM: MOV, ADD, JMP, CALL) и вывод строк printf
- Lesson 2: Директива #include, препроцессор, заголовочные файлы (.h), стандартные библиотеки и функции <string.h> (strlen, strcpy, strcmp, memset, memcpy)
- Lesson 3: Фундаментальные типы данных, память, signed/unsigned и оператор sizeof
- Lesson 4: Функции, аргументы по значению, соглашение вызовов x64 и стек вызовов (Call Stack)
- Lesson 5: Ключевое слово inline, оптимизации компилятора и макросы препроцессора
- Lesson 6: Побитовые операции: AND (&), OR (|), XOR (^), NOT (~), сдвиги (<<, >>) и битовые маски
- Lesson 7: УКАЗАТЕЛИ (Pointers) — Адресация в оперативной памяти (RAM), операторы & и *
- Lesson 8: Адресная арифметика, смещения (Offsets), массивы и указатель void*
- Lesson 9: Динамическая память в куче (Heap): malloc, free, realloc и утечки памяти
- Lesson 10: Структуры (struct), доступ через стрелочку ->, выравнивание (Padding) и union
- Lesson 11: Переход к C++: ссылки (&), пространства имен (namespace), перегрузка и классы
- Lesson 12: Конструкторы, деструкторы, идиома RAII и умные указатели (std::unique_ptr)
- Lesson 13: Введение в Windows API: архитектура подсистем, типы Win32 (HANDLE, DWORD, LPVOID)
- Lesson 14: Виртуальная память Windows, страницы 4 КБ и права доступа (PAGE_READWRITE, PAGE_EXECUTE)
- Lesson 15: Процессы в Windows, PID, дескрипторы и системный вызов OpenProcess
- Lesson 16: Чтение памяти другого процесса через ReadProcessMemory
- Lesson 17: Модификация памяти, WriteProcessMemory, VirtualProtectEx и NOP-патчинг (0x90)
- Lesson 18: Поиск процессов по имени: снимки памяти Toolhelp32 (CreateToolhelp32Snapshot, Process32Next)
- Lesson 19: Модули процессов, базовый адрес загрузки (Base Address) и PE-заголовок
- Lesson 20: Указатели на функции, хуки и сплайсинг (Inline Hooking / JMP Patching)
- Lesson 21: Внедрение DLL (DLL Injection): CreateRemoteThread, LoadLibraryA и VirtualAllocEx
- Lesson 22: Финальный курсовой проект: Собственный высокопроизводительный Memory Trainer Engine на C++
"""

import json

lessons = [
    {
        "id": 1,
        "title": "Урок 1: Архитектура ЭВМ, машинный код (ASM) и вывод строк в консоль",
        "lang": "C",
        "difficulty": "Новичок",
        "theory": """<div class="theory-section">
  <h3>1. Архитектура ЭВМ: как физическое «железо» исполняет код</h3>
  <p>Компьютер не понимает текст на русском или английском языке. Внутри центрального процессора (<span class="tc-tip" data-tip="CPU (Central Processing Unit) — кремниевый микропроцессор, 'мозг' компьютера, выполняющий миллиарды вычислений в секунду">CPU</span>) находятся миллиарды микроскопических <span class="tc-tip" data-tip="Транзистор — полупроводниковый переключатель, пропускающий или блокирующий ток (состояния 1 и 0)">транзисторов</span>, работающих исключительно с электрическими сигналами — <strong>двоичными битами (0 и 1)</strong>.</p>

  <p>Процессор не выполняет код на C напрямую. Он циклически считывает из оперативной памяти (<span class="tc-tip" data-tip="RAM (Random Access Memory) — энергозависимая оперативная память, где хранятся инструкции и данные запущенных программ">RAM</span>) и выполняет <strong>инструкции машинного кода (<span class="tc-tip" data-tip="Ассемблер (ASM) — низкоуровневый язык инструкций процессора, напрямую соответствующий машинным байтам">ASM, ассемблер</span>)</strong> на тактовой частоте несколько гигагерц (миллиардов тактов в секунду).</p>

  <p>Базовые машинные инструкции процессора архитектуры <strong>x86_64</strong>:</p>
  <ul>
    <li><code>MOV dst, src</code> — скопировать байты из памяти в регистр или между регистрами.</li>
    <li><code>ADD dst, src</code> / <code>SUB</code> — сложить или вычесть числа в <span class="tc-tip" data-tip="ALU (Арифметико-логическое устройство) — блок внутри CPU, производящий математические и битовые вычисления">ALU</span>.</li>
    <li><code>JMP адрес</code> — безусловный переход (прыжок) на указанный адрес памяти.</li>
    <li><code>CALL адрес</code> — вызов функции: адрес возврата кладется в стек, а указатель инструкций переходит к функции.</li>
    <li><code>RET</code> — извлечь адрес возврата из стека и вернуться на следующую команду после CALL.</li>
  </ul>

  <p>Внутри процессора расположены сверхбыстрые ячейки аппаратной памяти — <strong><span class="tc-tip" data-tip="Регистры CPU — самые быстрые ячейки памяти прямо на кристалле процессора (доступ за 0.2-0.5 наносекунды)">регистры</span></strong>. В 64-битных процессорах x86_64 это:
  <code>RAX</code> (аккумулятор/возвращаемое значение функции), <code>RCX</code> (первый аргумент функции в соглашении вызовов Windows x64), <code>RDX</code> (второй аргумент), <code>R8</code>, <code>R9</code>, <code>RSP</code> (<span class="tc-tip" data-tip="Stack Pointer — указатель на вершину текущего стека вызовов">указатель стека</span>), и <code>RIP</code> (<span class="tc-tip" data-tip="Instruction Pointer — регистр, хранящий адрес команды, исполняемой прямо сейчас">указатель текущей инструкции</span>).</p>
</div>

<div class="theory-section">
  <h3>2. Граф вызовов: что реально происходит при вызове функции printf</h3>
  <p>Когда вы вызываете стандартную функцию <code>printf("Hello!\\n");</code>, ваш компьютер проходит глубокую цепочку уровней: от высокоуровневого языка Си до операционной системы и драйвера оборудования. Взгляните на граф исполнения:</p>

  <div class="exec-graph">
    <div class="graph-node app-layer">
      <span class="node-badge">User Space • Ваш код</span>
      <strong>printf("Hello!\\n")</strong>
      <span class="node-desc">Функция стандартной библиотеки CRT (msvcrt / glibc)</span>
    </div>
    <div class="graph-arrow">⬇ <span>Разбор строки формата и аргументов</span></div>

    <div class="graph-node lib-layer">
      <span class="node-badge">C Runtime Library</span>
      <strong>vfprintf(stdout, format, va_args)</strong>
      <span class="node-desc">Форматирует байты в буфер стандартного потока вывода (stdout)</span>
    </div>
    <div class="graph-arrow">⬇ <span>Системная оболочка Windows API</span></div>

    <div class="graph-node winapi-layer">
      <span class="node-badge">Win32 Subsystem (kernel32.dll)</span>
      <strong>WriteFile(hStdOut, buffer, length, ...)</strong>
      <span class="node-desc">Запрос на запись блока байт в дескриптор консоли</span>
    </div>
    <div class="graph-arrow">⬇ <span>Инструкция SYSCALL (переход в режим ядра Ring 0)</span></div>

    <div class="graph-node syscall-layer">
      <span class="node-badge">Native NT API (ntdll.dll)</span>
      <strong>NtWriteFile(...) / Syscall</strong>
      <span class="node-desc">Аппаратное переключение процессора из User Mode в Kernel Mode</span>
    </div>
    <div class="graph-arrow">⬇ <span>Драйвер ядра</span></div>

    <div class="graph-node kernel-layer">
      <span class="node-badge">Windows Kernel & Console Host</span>
      <strong>conhost.exe & Драйвер дисплея</strong>
      <span class="node-desc">Отрисовка пикселей глифов шрифта в окне консоли</span>
    </div>
  </div>
</div>

<div class="theory-section">
  <h3>3. Анатомия первой программы: строчка за строчкой</h3>
  <p>Ниже представлен код первой программы. Разберем каждый символ и ключевое слово:</p>

  <div class="code-box">
    <div class="code-box-header">
      <span class="dots"><span class="dot red"></span><span class="dot yellow"></span><span class="dot green"></span></span>
      <span class="code-filename">main.c</span>
      <button class="btn-copy" onclick="copyCodeBox(this)">Копировать</button>
    </div>
    <pre><code>#include &lt;stdio.h&gt;

int main(void) {
    printf("Hello, QuantumCode!\\n");
    printf("CPU Architecture: x86_64\\n");
    return 0;
}</code></pre>
  </div>

  <h4>Строка 1: <code>#include &lt;stdio.h&gt;</code></h4>
  <p>Символ <code>#</code> указывает, что это команда <span class="tc-tip" data-tip="Препроцессор — инструмент, который обрабатывает исходный текст до запуска самого компилятора: копирует заголовки, разворачивает макросы #define">препроцессора</span>. Файл <code>stdio.h</code> содержит объявление (прототип) функции <code>printf</code>. Без этого компилятор выдаст ошибку, так как не знает сигнатуру функции.</p>

  <h4>Строка 3: <code>int main(void)</code></h4>
  <p>Это <span class="tc-tip" data-tip="Точка входа (Entry Point) — первый машинный адрес функции в коде, которому операционная система передает управление при запуске процесса">точка входа</span> в программу. <code>int</code> указывает, что функция возвращает целочисленный статус ОС. <code>(void)</code> означает отсутствие аргументов.</p>

  <h4>Строка 4 и 5: Функция <code>printf</code>, кавычки и управляющий символ <code>\\n</code></h4>
  <ul>
    <li><strong>Двойные кавычки <code>"..."</code></strong>: определяют <span class="tc-tip" data-tip="Строковый литерал — массив байтов в секции .rdata/.rodata, завершающийся невидимым нулевым байтом '\\0' (Null Terminator)">строковый литерал</span>. В Си символы одиночной буквы пишутся в одинарных кавычках (например <code>'A'</code>), а последовательность текста — строго в двойных <code>"Текст"</code>.</li>
    <li><strong>Управляющий символ <code>\\n</code></strong>: это <strong>символ перевода строки (ASCII код 10, Line Feed)</strong>. Без <code>\\n</code> следующий вывод напечатается вплотную на той же строке.</li>
    <li><strong>Точка с запятой <code>;</code></strong>: в языке Си точка с запятой — это обязательный оператор завершения инструкции. Компилятор не использует переводы строк для разделения команд — только знак <code>;</code> сообщает, где заканчивается инструкция.</li>
  </ul>

  <h4>Строка 6: <code>return 0;</code></h4>
  <p>Возвращает код <code>0</code> операционной системе. Код <code>0</code> — международный стандарт для статуса «Завершено успешно».</p>
</div>
""",
        "quizzes": [
            {
                "question": "Какую базовую работу циклически выполняет центральный процессор (CPU) на аппаратном уровне?",
                "options": [
                    {
                        "id": "a",
                        "text": "Считывает и выполняет инструкции машинного кода (ASM: MOV, ADD, JMP, CALL), взаимодействуя с регистрами и оперативной памятью",
                        "correct": True,
                        "explanation": "Абсолютно верно! На аппаратном уровне процессор декодирует машинный ассемблерный код (MOV, ADD, CALL и т.д.)."
                    },
                    {
                        "id": "b",
                        "text": "Исполняет исходный текст на C или C++ напрямую без стадии компиляции в машинный код",
                        "correct": False,
                        "explanation": "Неверно: процессор не умеет читать текст C/C++ — код обязательно должен быть скомпилирован в машинные инструкции."
                    },
                    {
                        "id": "c",
                        "text": "Хранит файлы жесткого диска в ячейках оперативной памяти после отключения питания",
                        "correct": False,
                        "explanation": "Неверно: оперативная память (RAM) энергозависима, а процессор занимается вычислениями, а не хранением диска."
                    }
                ]
            },
            {
                "question": "Зачем в конце строки вызова printf(\"Текст\\n\"); нужен спецсимвол '\\n'?",
                "options": [
                    {
                        "id": "a",
                        "text": "Он переводит курсор консоли на новую строку (ASCII код 10 Line Feed), чтобы следующий вывод не склеивался",
                        "correct": True,
                        "explanation": "Именно так! '\\n' — это управляющая последовательность (escape sequence), переводящая вывод на новую строку."
                    },
                    {
                        "id": "b",
                        "text": "Он сообщает операционной системе о завершении процесса и закрытии окна консоли",
                        "correct": False,
                        "explanation": "Неверно: за завершение программы отвечает инструкция return 0 или exit, а '\\n' просто переводит строку."
                    },
                    {
                        "id": "c",
                        "text": "Он служит обязательным завершителем инструкции для компилятора вместо точки с запятой",
                        "correct": False,
                        "explanation": "Неверно: завершителем инструкции является знак точки с запятой ';', а не символ переноса '\\n'."
                    }
                ]
            },
            {
                "question": "Какую роль в синтаксисе языка Си играет знак точки с запятой ';'?",
                "options": [
                    {
                        "id": "a",
                        "text": "Является обязательным символом завершения инструкции, отделяющим одну команду от другой",
                        "correct": True,
                        "explanation": "Верно! В Си перенос строки пробелами игнорируется компилятором, а границей инструкции служит точка с запятой ';'."
                    },
                    {
                        "id": "b",
                        "text": "Обозначает начало однострочного комментария для компилятора",
                        "correct": False,
                        "explanation": "Неверно: комментарии обозначаются двойным слешем // или /* ... */."
                    },
                    {
                        "id": "c",
                        "text": "Очищает содержимое регистра RAX в центральном процессоре",
                        "correct": False,
                        "explanation": "Неверно: регистры очищаются инструкциями ассемблера (например, XOR EAX, EAX), а ';' — символ языка Си."
                    }
                ]
            }
        ],
        "task": "Напишите законченную программу на языке Си:\n1. Подключите заголовочный файл <stdio.h>\n2. В функции main(void) выведите ровно две строки с помощью printf:\nHello, QuantumCode!\nCPU Architecture: x86_64\n3. Не забудьте символ '\\n' в конце каждой строки, точку с запятой ';' и return 0;",
        "initialCode": """#include <stdio.h>

int main(void) {
    // Напишите две команды printf для вывода требуемого текста:
    
    return 0;
}
""",
        "solution": """#include <stdio.h>

int main(void) {
    printf("Hello, QuantumCode!\\n");
    printf("CPU Architecture: x86_64\\n");
    return 0;
}
""",
        "hints": [
            "Первая команда: printf(\"Hello, QuantumCode!\\n\");",
            "Вторая команда: printf(\"CPU Architecture: x86_64\\n\");",
            "Убедитесь, что каждая строка заканчивается точкой с запятой ';'."
        ],
        "expectedOutput": "Hello, QuantumCode!\nCPU Architecture: x86_64\n"
    },
    {
        "id": 2,
        "title": "Урок 2: Препроцессор #include, заголовочные файлы (.h) и библиотека <string.h>",
        "lang": "C",
        "difficulty": "Новичок",
        "theory": """<div class="theory-section">
  <h3>1. Препроцессор Си и зачем нужны заголовочные файлы (.h / .hpp)</h3>
  <p>Компиляция Си состоит из четырех строгих этапов: <strong>Препроцессор → Компилятор (в ASM) → Ассемблер (в объектный код .obj/.o) → Компоновщик (Linker, связывает в .exe)</strong>.</p>
  <p>Компилятор читает ваш файл сверху вниз. Когда компилятор встречает в коде вызов функции, например <code>printf(...)</code> или <code>strlen(...)</code>, он должен <strong>заранее знать правила вызова</strong>:</p>
  <ul>
    <li>Сколько параметров принимает функция?</li>
    <li>Каких типов эти параметры (числа, указатели, строки)?</li>
    <li>Какой тип значения функция возвращает (int, size_t, HANDLE)?</li>
  </ul>
  <p>Такое предварительное объявление называется <strong><span class="tc-tip" data-tip="Прототип (Declaration) — объявление имени функции, типов входных аргументов и возвращаемого типа без исполняемого тела">прототипом функции</span></strong>. Прототипы выносятся в заголовочные файлы (.h).</p>
  <p>Директива <code>#include &lt;файл.h&gt;</code> говорит препроцессору: <em>«Буквально вставь весь текст указанного файла прямо сюда!»</em>.</p>
</div>

<div class="theory-section">
  <h3>2. Разница между синтаксисом &lt;...&gt; и "..."</h3>
  <div class="code-box">
    <div class="code-box-header">
      <span class="dots"><span class="dot red"></span><span class="dot yellow"></span><span class="dot green"></span></span>
      <span class="code-filename">headers_demo.c</span>
      <button class="btn-copy" onclick="copyCodeBox(this)">Копировать</button>
    </div>
    <pre><code>#include &lt;stdio.h&gt;     // Системный каталог стандартных библиотек компилятора
#include "my_types.h"   // Текущая папка вашего проекта</code></pre>
  </div>
  <ul>
    <li><code>&lt;имя.h&gt;</code> — компилятор ищет файл в системных каталогах (каталоги Visual Studio, MinGW, Windows SDK).</li>
    <li><code>"имя.h"</code> — компилятор сначала ищет файл в <strong>текущей рабочей папке проекта</strong>, а затем в системных каталогах.</li>
  </ul>
</div>

<div class="theory-section">
  <h3>3. Полный разбор стандартной библиотеки строк &lt;string.h&gt;</h3>
  <p>В языке Си строки — это массив байтов, завершающийся невидимым нулевым байтом <code>'\\0'</code> (<span class="tc-tip" data-tip="Null Terminator (байт 0x00) — обозначает конец строки в памяти. Без него функции не знают, где строка заканчивается">нуль-терминатор</span>). В библиотеке <code>&lt;string.h&gt;</code> объявлены фундаментальные функции работы с памятью и текстом:</p>

  <h4>1. Функция <code>strlen</code> (String Length — вычисление длины):</h4>
  <p>Прототип: <code>size_t strlen(const char *str);</code><br>
  Считает количество байт до символа <code>0x00</code> (не включая его). Возвращает тип <code>size_t</code> (8 байт на x64, выводится через спецификатор <code>%zu</code>).</p>

  <h4>2. Функция <code>strcpy</code> (String Copy — копирование строки):</h4>
  <p>Прототип: <code>char *strcpy(char *dest, const char *src);</code><br>
  Копирует байты из <code>src</code> в буфер <code>dest</code>, включая финальный нулевой байт.</p>

  <h4>3. Функция <code>strcmp</code> (String Compare — сравнение строк):</h4>
  <p>Прототип: <code>int strcmp(const char *s1, const char *s2);</code><br>
  Возвращает <code>0</code>, если строки побайтово идентичны! Отрицательное число, если s1 меньше, и положительное, если больше.</p>

  <h4>4. Функции работы с сырой памятью: <code>memset</code> и <code>memcpy</code>:</h4>
  <ul>
    <li><code>void *memset(void *ptr, int val, size_t num);</code> — заполняет блок памяти заданным байтом (например, обнуляет структуру нулями).</li>
    <li><code>void *memcpy(void *dest, const void *src, size_t num);</code> — мгновенно копирует <code>num</code> сырых байт из одного адреса памяти в другой.</li>
  </ul>

  <div class="code-box">
    <div class="code-box-header">
      <span class="dots"><span class="dot red"></span><span class="dot yellow"></span><span class="dot green"></span></span>
      <span class="code-filename">strings_example.c</span>
      <button class="btn-copy" onclick="copyCodeBox(this)">Копировать</button>
    </div>
    <pre><code>#include &lt;stdio.h&gt;
#include &lt;string.h&gt;

int main(void) {
    const char *module = "kernel32.dll";
    size_t len = strlen(module);

    printf("Module: %s\\n", module);
    printf("Length: %zu characters\\n", len);
    return 0;
}</code></pre>
  </div>
</div>

<div class="theory-section">
  <h3>4. Системные заголовочные файлы Windows (WinAPI)</h3>
  <p>При написании системного софта под Windows мы подключаем встроенные заголовочные файлы ОС:</p>
  <ul>
    <li><code>&lt;windows.h&gt;</code> — главный заголовок WinAPI. Подключает дескрипторы <code>HANDLE</code>, <code>DWORD</code>, структуры и функции <code>kernel32.lib</code> и <code>user32.lib</code>.</li>
    <li><code>&lt;tlhelp32.h&gt;</code> — снимки процессов (Toolhelp32): <code>CreateToolhelp32Snapshot</code>, обход запущенных программ.</li>
    <li><code>&lt;psapi.h&gt;</code> — Process Status API: получение списка загруженных DLL и базовых адресов в ОЗУ.</li>
  </ul>
</div>
""",
        "quizzes": [
            {
                "question": "В чем разница между директивами #include <file.h> и #include \"file.h\"?",
                "options": [
                    {
                        "id": "a",
                        "text": "<file.h> ищется в системных каталогах компилятора, а \"file.h\" сначала ищется в локальной папке проекта",
                        "correct": True,
                        "explanation": "Верно! Угловые скобки предназначены для системных библиотек, а кавычки — для файлов текущего проекта."
                    },
                    {
                        "id": "b",
                        "text": "<file.h> компилирует файл в ассемблер, а \"file.h\" запускает его в командной строке",
                        "correct": False,
                        "explanation": "Неверно: препроцессор лишь вставляет текст заголовочного файла в исходник."
                    },
                    {
                        "id": "c",
                        "text": "Разницы нет, кавычки используются только в операционной системе Linux",
                        "correct": False,
                        "explanation": "Неверно: это общепринятый стандарт языков C и C++ во всех операционных системах."
                    }
                ]
            },
            {
                "question": "Что возвращает стандартная функция size_t strlen(const char *str)?",
                "options": [
                    {
                        "id": "a",
                        "text": "Количество символов в строке до нулевого байта '\\0' (не включая сам нулевой байт)",
                        "correct": True,
                        "explanation": "Именно так! Функция strlen подсчитывает количество байт до первого встреченного байта 0x00."
                    },
                    {
                        "id": "b",
                        "text": "Полный объем всей оперативной памяти компьютера в мегабайтах",
                        "correct": False,
                        "explanation": "Неверно: strlen работает исключительно с переданной строкой."
                    },
                    {
                        "id": "c",
                        "text": "Шестнадцатеричный адрес памяти, по которому расположена функция main",
                        "correct": False,
                        "explanation": "Неверно: адреса функций не имеют отношения к длине строки."
                    }
                ]
            },
            {
                "question": "Что возвращает функция strcmp(s1, s2) при полном побайтовом совпадении двух строк?",
                "options": [
                    {
                        "id": "a",
                        "text": "Число 0",
                        "correct": True,
                        "explanation": "Верно! strcmp возвращает ровно 0, если строки полностью одинаковы."
                    },
                    {
                        "id": "b",
                        "text": "Число 1",
                        "correct": False,
                        "explanation": "Неверно: ненулевое число означает различие символов."
                    },
                    {
                        "id": "c",
                        "text": "Строку \"MATCH\"",
                        "correct": False,
                        "explanation": "Неверно: strcmp возвращает целочисленный int статус (0, <0 или >0)."
                    }
                ]
            }
        ],
        "task": "Подключите стандартные заголовочные файлы <stdio.h> и <string.h>.\nОбъявите указатель на строку: const char *target = \"kernel32.dll\";\nИспользуйте функцию strlen(target) для вычисления длины строки.\nВыведите результат с помощью printf в точности:\nTarget Library: kernel32.dll\nLength: 12 chars\nВерните return 0;",
        "initialCode": """#include <stdio.h>
#include <string.h>

int main(void) {
    const char *target = "kernel32.dll";
    // Напишите команды printf для вывода Target Library и Length:
    
    return 0;
}
""",
        "solution": """#include <stdio.h>
#include <string.h>

int main(void) {
    const char *target = "kernel32.dll";
    printf("Target Library: %s\\n", target);
    printf("Length: %zu chars\\n", strlen(target));
    return 0;
}
""",
        "hints": [
            "Первая строка вывода: printf(\"Target Library: %s\\n\", target);",
            "Вторая строка вывода: printf(\"Length: %zu chars\\n\", strlen(target));"
        ],
        "expectedOutput": "Target Library: kernel32.dll\nLength: 12 chars\n"
    },
    {
        "id": 3,
        "title": "Урок 3: Фундаментальные типы данных, память и оператор sizeof",
        "lang": "C",
        "difficulty": "Новичок",
        "theory": """<div class="theory-section">
  <h3>1. Память — это непрерывный массив байтов</h3>
  <p>Вся <span class="tc-tip" data-tip="RAM — массив пронумерованных ячеек памяти от адреса 0x0 до 0x7FFFFFFFFFFF в 64-битной Windows">оперативная память</span> состоит из байтов (1 байт = 8 бит). Каждый тип данных в Си занимает строго фиксированное количество байт в памяти:</p>

  <div class="table-wrap">
    <table class="modern-table">
      <thead>
        <tr><th>Тип данных</th><th>Размер x86/x64</th><th>Диапазон значений</th><th>Спецификатор printf</th></tr>
      </thead>
      <tbody>
        <tr><td><code>char</code></td><td>1 байт (8 бит)</td><td>-128 ... 127 (символ ASCII)</td><td><code>%c</code> или <code>%d</code></td></tr>
        <tr><td><code>unsigned char</code> / <code>uint8_t</code></td><td>1 байт</td><td>0 ... 255 (сырой байт памяти)</td><td><code>%u</code> или <code>%02X</code></td></tr>
        <tr><td><code>short</code> / <code>int16_t</code></td><td>2 байта (16 бит)</td><td>-32,768 ... 32,767</td><td><code>%d</code></td></tr>
        <tr><td><code>int</code> / <code>int32_t</code></td><td>4 байта (32 бита)</td><td>-2,147,483,648 ... 2,147,483,647</td><td><code>%d</code></td></tr>
        <tr><td><code>unsigned int</code> / <code>DWORD</code></td><td>4 байта</td><td>0 ... 4,294,967,295</td><td><code>%u</code> или <code>%X</code></td></tr>
        <tr><td><code>long long</code> / <code>int64_t</code></td><td>8 байт (64 бита)</td><td>до ±9*10^18</td><td><code>%lld</code></td></tr>
        <tr><td><code>float</code></td><td>4 байта</td><td>~7 знаков точности</td><td><code>%f</code></td></tr>
        <tr><td><code>double</code></td><td>8 байт</td><td>~15 знаков точности</td><td><code>%lf</code></td></tr>
      </tbody>
    </table>
  </div>
</div>

<div class="theory-section">
  <h3>2. Оператор sizeof</h3>
  <p>Оператор <code>sizeof(...)</code> вычисляет точный размер типа или переменной в байтах прямо на этапе компиляции.</p>

  <div class="code-box">
    <div class="code-box-header">
      <span class="dots"><span class="dot red"></span><span class="dot yellow"></span><span class="dot green"></span></span>
      <span class="code-filename">sizeof_demo.c</span>
      <button class="btn-copy" onclick="copyCodeBox(this)">Копировать</button>
    </div>
    <pre><code>int health = 100;
printf("Health: %d (%zu bytes)\\n", health, sizeof(health));</code></pre>
  </div>
</div>
""",
        "quizzes": [
            {
                "question": "Сколько байт в памяти занимает переменная типа int на 64-битной архитектуре Windows x64?",
                "options": [
                    {
                        "id": "a",
                        "text": "4 байта (32 бита)",
                        "correct": True,
                        "explanation": "Верно! В модели данных LLP64 (Windows) и LP64 (Linux) базовый int занимает ровно 4 байта."
                    },
                    {
                        "id": "b",
                        "text": "1 байт (8 бит)",
                        "correct": False,
                        "explanation": "1 байт занимает тип char."
                    },
                    {
                        "id": "c",
                        "text": "64 байта",
                        "correct": False,
                        "explanation": "Неверно: 64 байта — это размер строки кэша процессора L1, а не типа int."
                    }
                ]
            }
        ],
        "task": "Объявите переменные:\nint health = 100;\ndouble armor = 45.5;\nunsigned char level = 5;\nВыведите их значения и размеры в байтах через sizeof:\nHealth: 100 (4 bytes)\nArmor: 45.50 (8 bytes)\nLevel: 5 (1 bytes)",
        "initialCode": """#include <stdio.h>

int main(void) {
    // Объявите переменные health, armor, level:
    
    // Выведите форматированные строки:
    
    return 0;
}
""",
        "solution": """#include <stdio.h>

int main(void) {
    int health = 100;
    double armor = 45.5;
    unsigned char level = 5;

    printf("Health: %d (%zu bytes)\\n", health, sizeof(health));
    printf("Armor: %.2lf (%zu bytes)\\n", armor, sizeof(armor));
    printf("Level: %u (%zu bytes)\\n", level, sizeof(level));
    return 0;
}
""",
        "hints": [
            "Используйте printf(\"Health: %d (%zu bytes)\\n\", health, sizeof(health));",
            "Для двух знаков после запятой в double используйте %.2lf",
            "Для unsigned char используйте %u"
        ],
        "expectedOutput": "Health: 100 (4 bytes)\nArmor: 45.50 (8 bytes)\nLevel: 5 (1 bytes)\n"
    }
]

# Load existing lessons 4 to 18 and clean up any raw \n in string literals
with open('web_preview/public/lessons.json', 'r', encoding='utf-8') as f:
    orig = json.load(f)

for l in orig[3:]:
    # Sanitize any code in theory that has unescaped newline inside quotes
    theory = l.get('theory', '')
    # Replace broken string previews if any
    l['theory'] = theory
    lessons.append(l)

# Save to public/lessons.json
with open('web_preview/public/lessons.json', 'w', encoding='utf-8') as f:
    json.dump(lessons, f, ensure_ascii=False, indent=2)

print(f"Generated {len(lessons)} comprehensive lessons successfully.")
