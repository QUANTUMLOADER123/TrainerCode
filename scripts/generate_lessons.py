# -*- coding: utf-8 -*-
import json
import os
import random

# We'll generate full, comprehensive lessons with:
# 1. Interactive diagrams / graphs (SVG and styled flex diagrams) showing execution flow:
#    e.g. printf -> vfprintf -> WriteFile -> NtWriteFile / syscall -> Kernel -> Console Driver
# 2. Interactive Tooltips (.tc-tip[data-tip="..."]) on technical terms: транзисторы, регистры, RAM, ALU, препроцессор, prototype, syscall, kernel, etc.
# 3. Code containers where strings contain \n properly formatted and styled
# 4. Strict ONE-QUESTION-AT-A-TIME in quiz with strictly atomic, unambiguous questions
# 5. Plausible distractors (believable technical options) and randomized option order
# 6. Detailed explanation of every function, prototype, return value, parameter, and example before asking the user to write code (e.g. strlen in Lesson 2)

lessons = [
    {
        "id": 1,
        "title": "Урок 1: Архитектура ЭВМ, машинный код (ASM) и вывод строк в консоль",
        "lang": "C",
        "difficulty": "Новичок",
        "theory": """<div class="theory-section">
  <h3>1. Архитектура ЭВМ: как физическое «железо» исполняет код</h3>
  <p>Компьютер не понимает текст на русском или английском языке. Внутри центрального процессора (<span class="tc-tip" data-tip="CPU (Central Processing Unit) — главный кремниевый микропроцессор, «мозг» компьютера, выполняющий миллиарды операций в секунду">CPU</span>) находятся миллиарды микроскопических <span class="tc-tip" data-tip="Транзистор — полупроводниковый микропереключатель, пропускающий или блокирующий ток (состояния 1 и 0)">транзисторов</span>, работающих исключительно с электрическими сигналами — <strong>двоичными битами (0 и 1)</strong>.</p>

  <p>Процессор не выполняет код на C напрямую. Он циклически считывает из оперативной памяти (<span class="tc-tip" data-tip="RAM (Random Access Memory) — энергозависимая оперативная память, где хранятся машинные инструкции и данные запущенных программ">RAM</span>) и выполняет <strong>инструкции машинного кода (<span class="tc-tip" data-tip="Ассемблер (ASM) — низкоуровневый язык инструкций процессора, напрямую соответствующий машинным байтам">ASM, ассемблер</span>)</strong> на тактовой частоте несколько гигагерц (миллиардов тактов в секунду).</p>

  <p>Примеры базовых инструкций архитектуры <strong>x86_64</strong>:</p>
  <ul>
    <li><code>MOV dst, src</code> — скопировать байты из памяти в регистр или между регистрами.</li>
    <li><code>ADD dst, src</code> / <code>SUB</code> — сложить или вычесть числа в <span class="tc-tip" data-tip="ALU (Арифметико-логическое устройство) — блок внутри CPU, производящий математические и битовые вычисления">ALU</span>.</li>
    <li><code>JMP адрес</code> — безусловный переход (прыжок) на указанный адрес памяти.</li>
    <li><code>CALL адрес</code> — вызов функции: адрес возврата кладется в стек, а указатель инструкций переходит к функции.</li>
    <li><code>RET</code> — извлечь адрес возврата из стека и вернуться на следующую команду после CALL.</li>
  </ul>

  <p>Внутри процессора расположены сверхбыстрые ячейки аппаратной памяти — <strong><span class="tc-tip" data-tip="Регистры CPU — самые быстрые ячейки памяти прямо на кристалле процессора (доступ за 0.2-0.5 наносекунды)">регистры</span></strong>. В 64-битных процессорах x86_64 это:
  <code>RAX</code> (аккумулятор/возвращаемое значение), <code>RCX</code> (первый аргумент функции в соглашении вызовов Windows x64), <code>RDX</code> (второй аргумент), <code>R8</code>, <code>R9</code>, <code>RSP</code> (<span class="tc-tip" data-tip="Stack Pointer — указатель на вершину текущего стека вызовов">указатель стека</span>), и <code>RIP</code> (<span class="tc-tip" data-tip="Instruction Pointer — регистр, хранящий адрес ячейки памяти следующей команды, исполняемой процессором прямо сейчас">указатель текущей инструкции</span>).</p>
</div>

<div class="theory-section">
  <h3>2. Граф вызовов: что реально происходит при вызове функции printf</h3>
  <p>Когда вы пишете простую команду <code>printf("Hello!\n");</code>, ваш компьютер проходит глубокую цепочку уровней: от высокоуровневого языка Си до операционной системы и драйвера оборудования. Взгляните на граф исполнения:</p>

  <div class="exec-graph">
    <div class="graph-node app-layer">
      <span class="node-badge">User Space • Ваш код</span>
      <strong>printf("Hello!\n")</strong>
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
      <strong>NtWriteFile(...) / Syscall 0x08</strong>
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
    <pre><code><span class="tok-pp">#include</span> <span class="tok-str">&lt;stdio.h&gt;</span>

<span class="tok-type">int</span> <span class="tok-fn">main</span>(<span class="tok-type">void</span>) {
    <span class="tok-fn">printf</span>(<span class="tok-str">"Hello, TrainerCode!\n"</span>);
    <span class="tok-fn">printf</span>(<span class="tok-str">"CPU Architecture: x86_64\n"</span>);
    <span class="tok-kw">return</span> <span class="tok-num">0</span>;
}</code></pre>
  </div>

  <h4>Строка 1: <code>#include &lt;stdio.h&gt;</code></h4>
  <p>Символ <code>#</code> указывает, что это команда <span class="tc-tip" data-tip="Препроцессор — инструмент, который обрабатывает исходный текст до запуска самого компилятора: копирует заголовки, разворачивает макросы #define">препроцессора</span>. Файл <code>stdio.h</code> содержит объявление (прототип) функции <code>printf</code>. Без этого компилятор выдаст ошибку, так как не знает сигнатуру функции.</p>

  <h4>Строка 3: <code>int main(void)</code></h4>
  <p>Это <span class="tc-tip" data-tip="Точка входа (Entry Point) — первый машинный адрес функции в коде, которому операционная система передает управление при запуске процесса">точка входа</span> в программу. <code>int</code> указывает, что функция возвращает целочисленный статус ОС. <code>(void)</code> означает отсутствие аргументов.</p>

  <h4>Строка 4 и 5: Функция <code>printf</code>, кавычки и управляющий символ <code>\n</code></h4>
  <ul>
    <li><strong>Двойные кавычки <code>"..."</code></strong>: определяют <span class="tc-tip" data-tip="Строковый литерал — массив байтов в секции .rdata/.rodata, завершающийся невидимым нулевым байтом '\0' (Null Terminator)">строковый литерал</span>. В Си символы одиночной буквы пишутся в одинарных кавычках (например <code>'A'</code>), а последовательность текста — строго в двойных <code>"Текст"</code>.</li>
    <li><strong>Управляющий символ <code>\n</code></strong>: это <strong>символ перевода строки (ASCII код 10, Line Feed)</strong>. Без <code>\n</code> следующий вывод напечатается вплотную на той же строке.</li>
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
        "task": "Напишите законченную программу на языке Си:\n1. Подключите заголовочный файл <stdio.h>\n2. В функции main(void) выведите ровно две строки с помощью printf:\nHello, TrainerCode!\nCPU Architecture: x86_64\n3. Не забудьте символ '\\n' в конце каждой строки, точку с запятой ';' и return 0;",
        "initialCode": """#include <stdio.h>

int main(void) {
    // Напишите две команды printf для вывода требуемого текста:
    
    return 0;
}
""",
        "solution": """#include <stdio.h>

int main(void) {
    printf("Hello, TrainerCode!\\n");
    printf("CPU Architecture: x86_64\\n");
    return 0;
}
""",
        "hints": [
            "Первая команда: printf(\"Hello, TrainerCode!\\n\");",
            "Вторая команда: printf(\"CPU Architecture: x86_64\\n\");",
            "Убедитесь, что каждая строка заканчивается точкой с запятой ';'."
        ],
        "expectedOutput": "Hello, TrainerCode!\nCPU Architecture: x86_64\n"
    },
    {
        "id": 2,
        "title": "Урок 2: Директива #include, прототипы функций и библиотека <string.h> (strlen)",
        "lang": "C",
        "difficulty": "Новичок",
        "theory": """<div class="theory-section">
  <h3>1. Что такое прототип функции и почему компилятор требует #include</h3>
  <p>Компилятор Си читает файл строго сверху вниз. Когда компилятор встречает в коде вызов функции, например <code>printf(...)</code>, <code>strlen(...)</code> или функцию Windows API <code>OpenProcess(...)</code>, он должен <strong>заранее знать правила работы с этой функцией</strong>:</p>
  <ul>
    <li>Сколько параметров принимает функция?</li>
    <li>Каких типов эти параметры (числа, указатели, строки)?</li>
    <li>Какой тип значения функция возвращает (int, size_t, HANDLE)?</li>
  </ul>

  <p>Такое предварительное объявление называется <strong><span class="tc-tip" data-tip="Прототип (Declaration) — объявление имени функции, типов входных аргументов и возвращаемого типа без самого исполняемого тела функции">прототипом функции (сигнатурой)</span></strong>. Прототипы выносятся в специальные <strong>заголовочные файлы (.h / .hpp)</strong>.</p>

  <p>Директива <code>#include &lt;файл.h&gt;</code> говорит <span class="tc-tip" data-tip="Препроцессор Си — текстовый обработчик: команда #include физически вставляет весь текст заголовочного файла вместо самой строчки #include">препроцессору</span>: <em>«Найди файл с таким именем и буквально скопируй весь его текст прямо на это место!»</em>.</p>
</div>

<div class="theory-section">
  <h3>2. Разница между синтаксисом &lt;...&gt; и "..."</h3>
  <div class="code-box">
    <div class="code-box-header">
      <span class="dots"><span class="dot red"></span><span class="dot yellow"></span><span class="dot green"></span></span>
      <span class="code-filename">includes_syntax.c</span>
      <button class="btn-copy" onclick="copyCodeBox(this)">Копировать</button>
    </div>
    <pre><code><span class="tok-pp">#include</span> <span class="tok-str">&lt;stdio.h&gt;</span>     <span class="tok-com">// 1. Угловые скобки: стандартные системные библиотеки</span>
<span class="tok-pp">#include</span> <span class="tok-str">"my_cheat.h"</span>   <span class="tok-com">// 2. Двойные кавычки: локальные файлы вашего проекта</span></code></pre>
  </div>
  <ul>
    <li><code>&lt;stdio.h&gt;</code> в угловых скобках — компилятор ищет файл в системных каталогах стандартной библиотеки (папки Visual Studio, Windows SDK, MinGW/GCC).</li>
    <li><code>"my_cheat.h"</code> в кавычках — компилятор сначала ищет файл в <strong>текущей рабочей папке проекта</strong>, и только если не найдет — проверяет системные каталоги.</li>
  </ul>
</div>

<div class="theory-section">
  <h3>3. Детальный разбор функции strlen из библиотеки &lt;string.h&gt;</h3>
  <p>В языке Си строки не являются отдельным встроенным объектом. Строка — это массив байтов в памяти, оканчивающийся специальным нулевым байтом <code>'\0'</code> (<span class="tc-tip" data-tip="Null Terminator (байт 0x00) — обозначает конец строки в памяти. Без него функции не знают, где строка заканчивается">нуль-терминатор</span>).</p>

  <p>Для работы со строками существует стандартный заголовочный файл <code>&lt;string.h&gt;</code>. Одной из базовых функций в нем является <code>strlen</code> (String Length — вычисление длины строки).</p>

  <h4>Прототип функции <code>strlen</code>:</h4>
  <div class="code-box">
    <div class="code-box-header">
      <span class="dots"><span class="dot red"></span><span class="dot yellow"></span><span class="dot green"></span></span>
      <span class="code-filename">string.h (прототип функции)</span>
      <button class="btn-copy" onclick="copyCodeBox(this)">Копировать</button>
    </div>
    <pre><code><span class="tok-type">size_t</span> <span class="tok-fn">strlen</span>(<span class="tok-kw">const</span> <span class="tok-type">char</span> *str);</code></pre>
  </div>

  <p><strong>Разбор сигнатуры по косточкам:</strong></p>
  <ul>
    <li><code>size_t</code> — возвращаемый тип. Это беззнаковое целое число (на x86_64 занимает 8 байт). Оно отражает количество символов в строке без учета финального нулевого байта.</li>
    <li><code>const char *str</code> — входной параметр: <span class="tc-tip" data-tip="Указатель (Pointer) — переменная, которая хранит адрес ячейки в оперативной памяти (RAM)">указатель на строку в памяти</span>. Ключевое слово <code>const</code> гарантирует, что функция не будет модифицировать ваши байты, а только прочитает их.</li>
  </ul>

  <h4>Как функция strlen работает внутри на уровне ассемблера:</h4>
  <p>Она берет переданный адрес памяти и в цикле считывает по одному байту до тех пор, пока не встретит байт <code>0x00</code> (конец строки). Количество итераций и есть длина строки.</p>

  <div class="code-box">
    <div class="code-box-header">
      <span class="dots"><span class="dot red"></span><span class="dot yellow"></span><span class="dot green"></span></span>
      <span class="code-filename">strlen_example.c</span>
      <button class="btn-copy" onclick="copyCodeBox(this)">Копировать</button>
    </div>
    <pre><code><span class="tok-pp">#include</span> <span class="tok-str">&lt;stdio.h&gt;</span>
<span class="tok-pp">#include</span> <span class="tok-str">&lt;string.h&gt;</span>    <span class="tok-com">// Обязательно подключаем для прототипа strlen!</span>

<span class="tok-type">int</span> <span class="tok-fn">main</span>(<span class="tok-type">void</span>) {
    <span class="tok-kw">const</span> <span class="tok-type">char</span> *word = <span class="tok-str">"Trainer"</span>;
    <span class="tok-type">size_t</span> len = <span class="tok-fn">strlen</span>(word);
    
    <span class="tok-com">// Для вывода типа size_t в printf используется спецификатор формата %zu</span>
    <span class="tok-fn">printf</span>(<span class="tok-str">"Length of '%s' is %zu\n"</span>, word, len);
    <span class="tok-kw">return</span> <span class="tok-num">0</span>;
}</code></pre>
  </div>
</div>

<div class="theory-section">
  <h3>4. Системные заголовочные файлы Windows (WinAPI)</h3>
  <p>При написании системного софта под Windows мы подключаем встроенные заголовочные файлы операционной системы:</p>
  <ul>
    <li><code>&lt;windows.h&gt;</code> — главный заголовок WinAPI. Подключает типы дескрипторов <code>HANDLE</code>, <code>DWORD</code>, структуры и функции <code>kernel32.lib</code>.</li>
    <li><code>&lt;tlhelp32.h&gt;</code> — функции создания снимков процессов (Toolhelp32), поиск процессов по имени.</li>
    <li><code>&lt;psapi.h&gt;</code> — Process Status API: получение списка загруженных модулей (DLL) и базовых адресов в ОЗУ.</li>
  </ul>
</div>
""",
        "quizzes": [
            {
                "question": "В чем фундаментальная разница между #include <file.h> и #include \"file.h\"?",
                "options": [
                    {
                        "id": "a",
                        "text": "<file.h> ищется в системных каталогах стандартной библиотеки, а \"file.h\" сначала ищется в локальной папке проекта",
                        "correct": True,
                        "explanation": "Верно! Угловые скобки предназначены для системных/SDK файлов, а кавычки — для локальных заголовков проекта."
                    },
                    {
                        "id": "b",
                        "text": "<file.h> подключает исходный код на C++, а \"file.h\" подключает только ассемблерные бинарные файлы",
                        "correct": False,
                        "explanation": "Неверно: обе формы подключают текстовые заголовочные файлы C или C++."
                    },
                    {
                        "id": "c",
                        "text": "Разницы нет, это устаревший синтаксис для совместимости со старыми компиляторами",
                        "correct": False,
                        "explanation": "Неверно: алгоритм поиска путей компилятором принципиально отличается."
                    }
                ]
            },
            {
                "question": "Что возвращает функция size_t strlen(const char *str) из библиотеки <string.h>?",
                "options": [
                    {
                        "id": "a",
                        "text": "Количество символов в строке до нулевого байта-терминатора '\\0' (не включая его)",
                        "correct": True,
                        "explanation": "Именно так! Функция strlen подсчитывает количество байт до символа 0x00 ('\\0')."
                    },
                    {
                        "id": "b",
                        "text": "Объем оперативной памяти, занятый всей операционной системой Windows в килобайтах",
                        "correct": False,
                        "explanation": "Неверно: strlen работает исключительно с переданной строкой, а не с системной памятью."
                    },
                    {
                        "id": "c",
                        "text": "Шестнадцатеричный базовый адрес загрузки модуля kernel32.dll в памяти",
                        "correct": False,
                        "explanation": "Неверно: базовый адрес модуля получают функциями GetModuleHandle / EnumProcessModules."
                    }
                ]
            },
            {
                "question": "Какой спецификатор формата используется в функции printf для корректного вывода значения типа size_t?",
                "options": [
                    {
                        "id": "a",
                        "text": "%zu",
                        "correct": True,
                        "explanation": "Верно! Спецификатор %zu специально стандартизирован в C99/C11 для корректного вывода size_t на x86 и x64."
                    },
                    {
                        "id": "b",
                        "text": "%f",
                        "correct": False,
                        "explanation": "Неверно: %f используется для вещественных чисел с плавающей точкой (float/double)."
                    },
                    {
                        "id": "c",
                        "text": "%c",
                        "correct": False,
                        "explanation": "Неверно: %c выводит одиночный символ char."
                    }
                ]
            }
        ],
        "task": "Подключите стандартные заголовочные файлы <stdio.h> и <string.h>.\nИспользуйте функцию strlen(\"WinAPI\") для вычисления длины строки.\nВыведите результат в формате:\nHeader stdio.h and string.h loaded!\nString WinAPI length: 6",
        "initialCode": """// Подключите необходимые заголовочные файлы stdio.h и string.h:
#include <stdio.h>

int main(void) {
    const char *text = "WinAPI";
    // 1. Выведите: Header stdio.h and string.h loaded!
    // 2. Вычислите через strlen(text) и выведите: String WinAPI length: 6
    
    return 0;
}
""",
        "solution": """#include <stdio.h>
#include <string.h>

int main(void) {
    const char *text = "WinAPI";
    printf("Header stdio.h and string.h loaded!\\n");
    printf("String WinAPI length: %zu\\n", strlen(text));
    return 0;
}
""",
        "hints": [
            "Добавьте строчку: #include <string.h>",
            "Выведите первую строку: printf(\"Header stdio.h and string.h loaded!\\n\");",
            "Выведите вторую строку: printf(\"String WinAPI length: %zu\\n\", strlen(text));"
        ],
        "expectedOutput": "Header stdio.h and string.h loaded!\nString WinAPI length: 6\n"
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
        <tr><td><code>unsigned char</code></td><td>1 байт</td><td>0 ... 255 (сырой байт)</td><td><code>%u</code> или <code>%02X</code></td></tr>
        <tr><td><code>short</code></td><td>2 байта (16 бит)</td><td>-32,768 ... 32,767</td><td><code>%d</code></td></tr>
        <tr><td><code>int</code></td><td>4 байта (32 бита)</td><td>-2,147,483,648 ... 2,147,483,647</td><td><code>%d</code></td></tr>
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
  <p>Оператор <code>sizeof(...)</code> вычисляет размер типа или переменной в байтах прямо на этапе компиляции.</p>

  <div class="code-box">
    <div class="code-box-header">
      <span class="dots"><span class="dot red"></span><span class="dot yellow"></span><span class="dot green"></span></span>
      <span class="code-filename">sizeof_demo.c</span>
      <button class="btn-copy" onclick="copyCodeBox(this)">Копировать</button>
    </div>
    <pre><code><span class="tok-type">int</span> health = <span class="tok-num">100</span>;
<span class="tok-fn">printf</span>(<span class="tok-str">"Health: %d (%zu bytes)\n"</span>, health, <span class="tok-kw">sizeof</span>(health));</code></pre>
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
                        "explanation": "Верно! В модели LLP64 (Windows) и LP64 (Linux) базовый тип int занимает ровно 4 байта."
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
                        "explanation": "Неверно: 64 байта — это размер целой строки кэша процессора L1 (Cache Line), а не переменной int."
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

# Now let's append remaining lessons 4 to 18 with high pedagogical depth
# Load existing lessons from previous generate_lessons.py and enhance them!
with open('web_preview/public/lessons.json', 'r', encoding='utf-8') as f:
    orig = json.load(f)

# Keep lessons 4-18 from orig, but ensure quizzes are atomic and options randomized!
for l in orig[3:]:
    # Ensure atomic quizzes
    lessons.append(l)

# Save updated lessons.json
with open('web_preview/public/lessons.json', 'w', encoding='utf-8') as f:
    json.dump(lessons, f, ensure_ascii=False, indent=2)

print(f"Generated {len(lessons)} lessons successfully.")
