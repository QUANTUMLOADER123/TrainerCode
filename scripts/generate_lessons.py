# -*- coding: utf-8 -*-
import json
import os

lessons = [
    {
        "id": 1,
        "title": "Урок 1: Архитектура ЭВМ, машинный код (ASM) и вывод строк в консоль",
        "lang": "C",
        "difficulty": "Новичок",
        "theory": """<div class="theory-section">
  <h3>1. Как процессор и компьютер выполняют ваш код</h3>
  <p>Компьютер не понимает текст на английском или русском языке. Внутри процессора (CPU) находятся миллиарды микроскопических транзисторов, которые работают исключительно с электрическими сигналами — <strong>двоичным кодом (0 и 1)</strong>.</p>
  <p>Процессор умеет делать только одну вещь: циклически считывать из оперативной памяти (RAM) и выполнять <strong>инструкции машинного кода (ASM, ассемблер)</strong> на тактовой частоте несколько миллиардов раз в секунду. Примеры таких базовых инструкций процессора:</p>
  <ul>
    <li><code>MOV</code> — переместить байты данных из памяти в регистр или наоборот.</li>
    <li><code>ADD</code> / <code>SUB</code> — сложить или вычесть числа в арифметико-логическом устройстве (ALU).</li>
    <li><code>JMP</code> — безусловный прыжок к другому адресу памяти (ветвление).</li>
    <li><code>CALL</code> — вызов функции с сохранением адреса возврата на стеке.</li>
    <li><code>RET</code> — возврат из функции в место, откуда она была вызвана.</li>
  </ul>
  <p>Внутри процессора есть сверхбыстрые ячейки памяти — <strong>регистры</strong> (в 64-битных процессорах x86_64 это <code>RAX</code>, <code>RBX</code>, <code>RCX</code>, <code>RDX</code>, <code>RSP</code>, <code>RIP</code>). Регистр <code>RIP</code> хранит адрес инструкции, которая выполняется прямо сейчас.</p>
</div>

<div class="theory-section">
  <h3>2. Зачем нужен язык Си (C)</h3>
  <p>Писать программы прямо в машинных кодах (шестнадцатеричных байтах) невероятно сложно. Язык Си был создан Деннисом Ритчи как высокоуровневый язык, который компилируется <strong>напрямую в машинный ассемблерный код</strong> без виртуальных машин и сборщиков мусора. Си даёт вам полный контроль над каждым байтом памяти.</p>
</div>

<div class="theory-section">
  <h3>3. Разбор первой программы: каждая строчка и каждый символ</h3>
  <p>Давайте подробно разберем самую первую программу до мельчайших деталей:</p>

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
  <p>Символ решётки <code>#</code> указывает, что это команда <strong>препроцессора</strong>. Препроцессор работает ДО компилятора. Он находит системный файл <code>stdio.h</code> (Standard Input / Output) и вставляет его содержимое в начало нашей программы. Именно в <code>stdio.h</code> написано объявление функции <code>printf</code>. Без этой строчки компилятор выдаст ошибку: <em>«Я не знаю, что такое printf!»</em>.</p>

  <h4>Строка 3: <code>int main(void)</code></h4>
  <p>Это главная функция — <strong>точка входа</strong>. Когда операционная система (Windows) запускает ваш <code>.exe</code> файл, она передает управление процессора именно на функцию <code>main</code>.</p>
  <ul>
    <li><code>int</code> перед словом <code>main</code> означает: по завершении функция вернет целое число (код возврата ОС).</li>
    <li><code>(void)</code> в скобках означает: функция не принимает входных параметров при запуске.</li>
    <li>Фигурная скобка <code>{</code> открывает тело функции (начало инструкций), а закрывающая скобка <code>}</code> в конце — закрывает тело функции.</li>
  </ul>

  <h4>Строка 4: <code>printf("Hello, TrainerCode!\n");</code></h4>
  <p>Функция <code>printf</code> (сокращение от <em>print formatted</em> — форматированная печать) берет переданные байты строки и передает их в стандартный поток вывода консоли (stdout).</p>
  <ul>
    <li>Круглые скобки <code>( ... )</code> — внутри них передаются аргументы функции.</li>
    <li>Двойные кавычки <code>" ... "</code> — обозначают строковый литерал (последовательность символов в памяти).</li>
    <li>Спецсимвол <code>\n</code> — это <strong>перевод строки (Newline)</strong>. Символ слэша <code>\</code> называется экранированием. Без <code>\n</code> следующий текст прилипнет к текущему на той же строчке!</li>
    <li>Точка с запятой <code>;</code> — <strong>ОБЯЗАТЕЛЬНЫЙ символ конца инструкции в Си</strong>. Каждая команда в Си должна заканчиваться точкой с запятой, иначе компилятор не поймет, где кончается текущая инструкция.</li>
  </ul>

  <h4>Строка 6: <code>return 0;</code></h4>
  <p>Инструкция <code>return</code> завершает работу функции <code>main</code> и передает число <code>0</code> обратно операционной системе Windows. Код <code>0</code> — это общепринятый стандарт, означающий: <em>«Программа выполнена успешно, сбоев не произошло»</em>. Любое ненулевое число (например, <code>-1</code> или <code>1</code>) сигнализирует об ошибке.</p>
</div>
""",
        "quizzes": [
            {
                "question": "Что выполняет центральный процессор (CPU) на аппаратном уровне?",
                "options": [
                    {
                        "id": "a",
                        "text": "Инструкции машинного кода (ASM, ассемблер), такие как MOV, ADD, JMP, CALL, оперируя регистрами и памятью RAM",
                        "correct": True,
                        "explanation": "Абсолютно верно! На аппаратном уровне процессор декодирует и исполняет поток ассемблерных машинных инструкций (MOV, ADD, CALL и т.д.)."
                    },
                    {
                        "id": "b",
                        "text": "Напрямую исполняет текст на русском или английском языке без компиляции",
                        "correct": False,
                        "explanation": "Неверно. Компьютер не понимает человеческий язык напрямую; код всегда компилируется в машинные инструкции."
                    },
                    {
                        "id": "c",
                        "text": "Исключительно рисует графику на экране монитора",
                        "correct": False,
                        "explanation": "Неверно. Вычислениями и командами занимается центральный процессор (CPU)."
                    }
                ]
            },
            {
                "question": "Зачем в вызове printf(\"Текст\\n\"); нужен символ '\\n' и точка с запятой ';' в конце?",
                "options": [
                    {
                        "id": "a",
                        "text": "'\\n' переводит курсор на новую строку, а ';' завершает инструкцию языка Си",
                        "correct": True,
                        "explanation": "Именно так! '\\n' означает символ перевода строки (Newline), а точка с запятой сообщает компилятору об окончании текущей инструкции."
                    },
                    {
                        "id": "b",
                        "text": "'\\n' удаляет текст из консоли, а ';' перезапускает программу",
                        "correct": False,
                        "explanation": "Неверно. '\\n' не удаляет текст, а осуществляет перенос строки."
                    }
                ]
            }
        ],
        "task": "Напишите законченную программу на языке Си:\n1. Подключите заголовочный файл <stdio.h>\n2. В функции main выведите ровно две строки с помощью printf:\nHello, TrainerCode!\nCPU Architecture: x86_64\n3. Не забудьте символ '\\n' в конце каждой строки, точку с запятой ';' и return 0;",
        "initialCode": """#include <stdio.h>

int main(void) {
    // Напишите две команды printf для вывода текста:
    
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
            "Используйте: printf(\"Hello, TrainerCode!\\n\");",
            "На следующей строке: printf(\"CPU Architecture: x86_64\\n\");",
            "Убедитесь, что каждая строка заканчивается символом '\\n' и точкой с запятой ';'."
        ],
        "expectedOutput": "Hello, TrainerCode!\nCPU Architecture: x86_64\n"
    },
    {
        "id": 2,
        "title": "Урок 2: Директива #include: заголовочные файлы (.h) и библиотеки Windows",
        "lang": "C",
        "difficulty": "Новичок",
        "theory": """<div class="theory-section">
  <h3>1. Что такое заголовочные файлы (.h / .hpp) и зачем нужен #include</h3>
  <p>Компилятор Си читает ваш файл сверху вниз. Когда компилятор встречает в коде вызов функции, например <code>printf(...)</code> или вызов WinAPI <code>OpenProcess(...)</code>, он должен <strong>заранее знать</strong>:</p>
  <ul>
    <li>Сколько параметров принимает эта функция?</li>
    <li>Каких типов эти параметры (числа, указатели, строки)?</li>
    <li>Какой тип значения функция возвращает (int, void, HANDLE)?</li>
  </ul>
  <p>Всю эту информацию называют <strong>прототипом функции</strong> (декларацией). Прототипы функций, структуры и константы выносятся в специальные <strong>заголовочные файлы (Header files) с расширением .h</strong> (или .hpp для C++).</p>
  <p>Директива <code>#include</code> говорит препроцессору: <em>«Возьми весь текст из указанного .h файла и буквально вставь его прямо сюда!»</em>.</p>
</div>

<div class="theory-section">
  <h3>2. Разница между кавычками "..." и угловыми скобками &lt;...&gt;</h3>
  <div class="code-box">
    <div class="code-box-header">
      <span class="dots"><span class="dot red"></span><span class="dot yellow"></span><span class="dot green"></span></span>
      <span class="code-filename">headers_example.c</span>
      <button class="btn-copy" onclick="copyCodeBox(this)">Копировать</button>
    </div>
    <pre><code><span class="tok-pp">#include</span> <span class="tok-str">&lt;stdio.h&gt;</span>     <span class="tok-com">// Системный заголовок из стандартной библиотеки компилятора</span>
<span class="tok-pp">#include</span> <span class="tok-str">"my_cheat.h"</span>   <span class="tok-com">// Локальный заголовок из текущей папки вашего проекта</span></code></pre>
  </div>
  <ul>
    <li><code>&lt;имя.h&gt;</code> — компилятор ищет файл в системных каталогах стандартной библиотеки (например, в папке Visual Studio или MinGW).</li>
    <li><code>"имя.h"</code> — компилятор сначала ищет файл в текущей папке проекта, и только если не найдет — идет в системные каталоги.</li>
  </ul>
</div>

<div class="theory-section">
  <h3>3. Главные стандартные библиотеки языка Си</h3>
  <ul>
    <li><code>&lt;stdio.h&gt;</code> — Standard I/O: функции <code>printf</code>, <code>scanf</code>, работа с файлами (<code>fopen</code>, <code>fclose</code>, <code>fread</code>).</li>
    <li><code>&lt;stdlib.h&gt;</code> — Standard Library: управление динамической памятью в куче (<code>malloc</code>, <code>free</code>), завершение процесса (<code>exit</code>), генерация случайных чисел (<code>rand</code>).</li>
    <li><code>&lt;string.h&gt;</code> — String operations: работа со строками и сырой памятью (<code>strlen</code>, <code>strcpy</code>, <code>memcpy</code>, <code>memset</code>).</li>
    <li><code>&lt;stdint.h&gt;</code> — Fixed width integers: типы с точным размером (<code>uint8_t</code>, <code>uint32_t</code>, <code>uint64_t</code>, <code>uintptr_t</code>).</li>
    <li><code>&lt;math.h&gt;</code> — Math library: математические функции (<code>sqrt</code>, <code>sin</code>, <code>cos</code>, <code>pow</code>).</li>
  </ul>
</div>

<div class="theory-section">
  <h3>4. Системные заголовочные файлы Windows (WinAPI)</h3>
  <p>При написании системного ПО под Windows мы подключаем встроенные заголовочные файлы операционной системы:</p>
  <ul>
    <li><code>&lt;windows.h&gt;</code> — <strong>Главный заголовочный файл WinAPI</strong>. Подключает типы <code>HANDLE</code>, <code>DWORD</code>, <code>HWND</code>, функции управления памятью, окнами, процессами. Связан с системной библиотекой <code>kernel32.lib</code> и <code>user32.lib</code>.</li>
    <li><code>&lt;tlhelp32.h&gt;</code> — Toolhelp32: снимки процессов, обход списка запущенных программ через <code>CreateToolhelp32Snapshot</code>, <code>Process32First</code>, <code>Process32Next</code>.</li>
    <li><code>&lt;psapi.h&gt;</code> — Process Status API: получение модулей процессов, базовых адресов загрузки DLL в ОЗУ.</li>
  </ul>
</div>
""",
        "quizzes": [
            {
                "question": "В чем разница между #include <stdio.h> и #include \"my_module.h\"?",
                "options": [
                    {
                        "id": "a",
                        "text": "<stdio.h> ищется в системных каталогах библиотек компилятора, а \"my_module.h\" сначала ищется в локальной папке проекта",
                        "correct": True,
                        "explanation": "Верно! Угловые скобки предназначены для системных/стандартных библиотек, а кавычки — для локальных файлов вашего проекта."
                    },
                    {
                        "id": "b",
                        "text": "В кавычках подключаются картинки, а в скобках — музыка",
                        "correct": False,
                        "explanation": "Неверно. Обе формы подключают заголовочные файлы C/C++."
                    }
                ]
            },
            {
                "question": "Какой главный заголовочный файл необходимо подключить для работы с Windows API (дескрипторы HANDLE, память, процессы)?",
                "options": [
                    {
                        "id": "a",
                        "text": "<windows.h>",
                        "correct": True,
                        "explanation": "Абсолютно верно! <windows.h> подключает все базовые типы (HANDLE, DWORD, LPVOID) и функции ядра Windows."
                    },
                    {
                        "id": "b",
                        "text": "<games.h>",
                        "correct": False,
                        "explanation": "Такого стандартного заголовка WinAPI не существует."
                    }
                ]
            }
        ],
        "task": "Подключите стандартные заголовочные файлы <stdio.h> и <string.h>.\nИспользуйте функцию strlen(\"WinAPI\") для вычисления длины строки.\nВыведите результат в формате:\nHeader stdio.h and string.h loaded!\nString WinAPI length: 6",
        "initialCode": """// Подключите необходимые заголовочные файлы:
#include <stdio.h>

int main(void) {
    const char *text = "WinAPI";
    // Используйте strlen для вывода:
    
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
            "Добавьте #include <string.h> на второй строчке.",
            "Используйте printf(\"Header stdio.h and string.h loaded!\\n\");",
            "Затем printf(\"String WinAPI length: %zu\\n\", strlen(text));"
        ],
        "expectedOutput": "Header stdio.h and string.h loaded!\nString WinAPI length: 6\n"
    },
    {
        "id": 3,
        "title": "Урок 3: Фундаментальные типы данных, память и оператор sizeof",
        "lang": "C",
        "difficulty": "Новичок",
        "theory": """<div class="theory-section">
  <h3>1. Память — это массив байтов</h3>
  <p>Вся оперативная память компьютера состоит из байтов (1 байт = 8 бит). Каждый тип данных в Си занимает фиксированное количество байт:</p>
  <ul>
    <li><code>char</code> (1 байт = 8 бит): от -128 до 127 (символ ASCII).</li>
    <li><code>unsigned char</code> (1 байт): от 0 до 255.</li>
    <li><code>short</code> (2 байта = 16 бит): от -32,768 до 32,767.</li>
    <li><code>int</code> (4 байта = 32 бита): от -2,147,483,648 до 2,147,483,647 (~2 миллиарда).</li>
    <li><code>unsigned int</code> (4 байта): от 0 до 4,294,967,295 (~4 миллиарда).</li>
    <li><code>long long</code> (8 байт = 64 бита): сверхбольшие целые числа до 9*10^18.</li>
    <li><code>float</code> (4 байта): вещественное число с плавающей точкой (~7 знаков точности).</li>
    <li><code>double</code> (8 байт): вещественное число двойной точности (~15 знаков точности).</li>
  </ul>
</div>

<div class="theory-section">
  <h3>2. Оператор sizeof</h3>
  <p>Чтобы узнать, сколько байт переменная или тип занимает в оперативной памяти прямо сейчас, используется оператор <code>sizeof</code>:</p>
  <div class="code-box">
    <div class="code-box-header">
      <span class="dots"><span class="dot red"></span><span class="dot yellow"></span><span class="dot green"></span></span>
      <span class="code-filename">types.c</span>
      <button class="btn-copy" onclick="copyCodeBox(this)">Копировать</button>
    </div>
    <pre><code><span class="tok-type">int</span> hp = <span class="tok-num">100</span>;
<span class="tok-fn">printf</span>(<span class="tok-str">"Size of int: %zu bytes\n"</span>, <span class="tok-kw">sizeof</span>(hp)); <span class="tok-com">// Напечатает: 4 bytes</span></code></pre>
  </div>
  <p>Спецификатор формата для вывода <code>sizeof</code> в printf — <code>%zu</code>.</p>
</div>
""",
        "quizzes": [
            {
                "question": "Сколько байт в памяти занимает переменная типа int на 64-битной архитектуре x86_64?",
                "options": [
                    {
                        "id": "a",
                        "text": "4 байта (32 бита)",
                        "correct": True,
                        "explanation": "Верно! Стандартный размер int в моделях данных Windows и Linux составляет ровно 4 байта."
                    },
                    {
                        "id": "b",
                        "text": "1 байт",
                        "correct": False,
                        "explanation": "1 байт занимает тип char."
                    }
                ]
            }
        ],
        "task": "Объявите переменные:\nint health = 100;\ndouble armor = 45.5;\nunsigned char level = 5;\nВыведите их значения и размеры в байтах через sizeof:\nHealth: 100 (4 bytes)\nArmor: 45.50 (8 bytes)\nLevel: 5 (1 bytes)",
        "initialCode": """#include <stdio.h>

int main(void) {
    // Объявите health, armor, level и напечатайте результат:
    
    return 0;
}
""",
        "solution": """#include <stdio.h>

int main(void) {
    int health = 100;
    double armor = 45.5;
    unsigned char level = 5;

    printf("Health: %d (%zu bytes)\\n", health, sizeof(health));
    printf("Armor: %.2f (%zu bytes)\\n", armor, sizeof(armor));
    printf("Level: %u (%zu bytes)\\n", level, sizeof(level));
    return 0;
}
""",
        "hints": [
            "Используйте %.2f для armor.",
            "Используйте %zu для вывода результата sizeof."
        ],
        "expectedOutput": "Health: 100 (4 bytes)\nArmor: 45.50 (8 bytes)\nLevel: 5 (1 bytes)\n"
    },
    {
        "id": 4,
        "title": "Урок 4: Функции, аргументы по значению и стек вызовов (Call Stack)",
        "lang": "C",
        "difficulty": "Новичок",
        "theory": """<div class="theory-section">
  <h3>1. Передача аргументов по значению (Pass by Value)</h3>
  <p>В языке Си все аргументы передаются в функцию <strong>ПО ЗНАЧЕНИЮ</strong>. Это значит, что функция получает <strong>копию</strong> переменной на вершине стека вызовов (Call Stack).</p>
  <div class="code-box">
    <div class="code-box-header">
      <span class="dots"><span class="dot red"></span><span class="dot yellow"></span><span class="dot green"></span></span>
      <span class="code-filename">stack.c</span>
      <button class="btn-copy" onclick="copyCodeBox(this)">Копировать</button>
    </div>
    <pre><code><span class="tok-type">void</span> <span class="tok-fn">try_modify</span>(<span class="tok-type">int</span> x) {
    x = <span class="tok-num">999</span>; <span class="tok-com">// Изменяется только копия на стеке!</span>
}

<span class="tok-type">int</span> <span class="tok-fn">main</span>(<span class="tok-type">void</span>) {
    <span class="tok-type">int</span> a = <span class="tok-num">10</span>;
    <span class="tok-fn">try_modify</span>(a);
    <span class="tok-com">// 'a' здесь останется равным 10!</span>
    <span class="tok-kw">return</span> <span class="tok-num">0</span>;
}</code></pre>
  </div>
  <p>Чтобы функция могла изменить оригинал переменной, требуется передать <strong>адрес в памяти (указатель)</strong>, который мы подробно изучим далее.</p>
</div>
""",
        "quizzes": [
            {
                "question": "Что произойдет с переменной 'a' в функции main, если передать ее в обычную функцию foo(int a) и внутри присвоить a = 50?",
                "options": [
                    {
                        "id": "a",
                        "text": "Переменная 'a' в main НЕ изменится, так как функция работает со своей локальной копией на стеке",
                        "correct": True,
                        "explanation": "Верно! В C аргументы копируются в стек функции. Чтобы изменить оригинал, нужен указатель."
                    },
                    {
                        "id": "b",
                        "text": "Переменная 'a' изменится на 50",
                        "correct": False,
                        "explanation": "Неверно. Без указателя изменить оригинал переменной невозможно."
                    }
                ]
            }
        ],
        "task": "Напишите функцию int apply_bonus(int score, int multiplier), которая возвращает score * multiplier.\nВ main вызовите ее для score = 150 и multiplier = 3 и выведите:\nFinal Score: 450",
        "initialCode": """#include <stdio.h>

// Напишите функцию apply_bonus:

int main(void) {
    int score = 150;
    int multiplier = 3;

    // Вызовите функцию и выведите результат:
    
    return 0;
}
""",
        "solution": """#include <stdio.h>

int apply_bonus(int score, int multiplier) {
    return score * multiplier;
}

int main(void) {
    int score = 150;
    int multiplier = 3;
    int total = apply_bonus(score, multiplier);
    printf("Final Score: %d\\n", total);
    return 0;
}
""",
        "hints": [
            "int apply_bonus(int score, int multiplier) { return score * multiplier; }"
        ],
        "expectedOutput": "Final Score: 450\n"
    },
    {
        "id": 5,
        "title": "Урок 5: Ключевое слово inline, оптимизации и макросы",
        "lang": "C",
        "difficulty": "Средний",
        "theory": """<div class="theory-section">
  <h3>1. Зачем нужен inline</h3>
  <p>При вызове обычной функции процессор выполняет машинные команды <code>CALL</code> и <code>RET</code>, сдвигает регистр стека <code>RSP</code> и сохраняет адреса возврата. Для микро-функций из одной строки это напрасная трата тактов.</p>
  <p>Спецификатор <code>inline</code> указывает компилятору вставить машинный код функции прямо в место вызова:</p>
  <div class="code-box">
    <div class="code-box-header">
      <span class="dots"><span class="dot red"></span><span class="dot yellow"></span><span class="dot green"></span></span>
      <span class="code-filename">inline_math.c</span>
      <button class="btn-copy" onclick="copyCodeBox(this)">Копировать</button>
    </div>
    <pre><code><span class="tok-kw">static</span> <span class="tok-kw">inline</span> <span class="tok-type">int</span> <span class="tok-fn">clamp</span>(<span class="tok-type">int</span> val, <span class="tok-type">int</span> min, <span class="tok-type">int</span> max) {
    <span class="tok-kw">if</span> (val &lt; min) <span class="tok-kw">return</span> min;
    <span class="tok-kw">if</span> (val &gt; max) <span class="tok-kw">return</span> max;
    <span class="tok-kw">return</span> val;
}</code></pre>
  </div>
</div>
""",
        "quizzes": [
            {
                "question": "В чем главное преимущество спецификатора inline?",
                "options": [
                    {
                        "id": "a",
                        "text": "Экономия тактов процессора за счет подстановки кода функции на месте вызова без инструкций CALL/RET",
                        "correct": True,
                        "explanation": "Верно! Тело функции инлайнится в код, устраняя накладные расходы на работу со стеком."
                    },
                    {
                        "id": "b",
                        "text": "Ограничение доступа к переменной",
                        "correct": False,
                        "explanation": "Неверно. За ограничение доступа отвечает static."
                    }
                ]
            }
        ],
        "task": "Напишите static inline функцию clamp(int val, int min, int max).\nВ main проверьте: clamp(150, 0, 100) и clamp(-20, 0, 100):\nClamped 1: 100\nClamped 2: 0",
        "initialCode": """#include <stdio.h>

// Объявите static inline функцию clamp:

int main(void) {
    printf("Clamped 1: %d\\n", clamp(150, 0, 100));
    printf("Clamped 2: %d\\n", clamp(-20, 0, 100));
    return 0;
}
""",
        "solution": """#include <stdio.h>

static inline int clamp(int val, int min, int max) {
    if (val < min) return min;
    if (val > max) return max;
    return val;
}

int main(void) {
    printf("Clamped 1: %d\\n", clamp(150, 0, 100));
    printf("Clamped 2: %d\\n", clamp(-20, 0, 100));
    return 0;
}
""",
        "hints": [
            "static inline int clamp(int val, int min, int max) { ... }"
        ],
        "expectedOutput": "Clamped 1: 100\nClamped 2: 0\n"
    },
    {
        "id": 6,
        "title": "Урок 6: Побитовые операции: AND, OR, XOR и битовые маски",
        "lang": "C",
        "difficulty": "Средний",
        "theory": """<div class="theory-section">
  <h3>1. Побитовая магия</h3>
  <p>Побитовые операции работают непосредственно с регистрами процессора за 1 такт:</p>
  <ul>
    <li><code>&amp;</code> (AND): 1 &amp; 1 = 1, иначе 0 (проверка и маскирование).</li>
    <li><code>|</code> (OR): установка бита в 1.</li>
    <li><code>^</code> (XOR): инвертирование бита (1 ^ 1 = 0, 1 ^ 0 = 1).</li>
    <li><code>&lt;&lt;</code> и <code>&gt;&gt;</code>: сдвиги влево и вправо (умножение/деление на 2^n).</li>
  </ul>
  <div class="code-box">
    <div class="code-box-header">
      <span class="dots"><span class="dot red"></span><span class="dot yellow"></span><span class="dot green"></span></span>
      <span class="code-filename">bitflags.c</span>
      <button class="btn-copy" onclick="copyCodeBox(this)">Копировать</button>
    </div>
    <pre><code>flags |= (<span class="tok-num">1</span> &lt;&lt; <span class="tok-num">2</span>);  <span class="tok-com">// Установить 2-й бит в 1</span>
flags &amp;= ~(<span class="tok-num">1</span> &lt;&lt; <span class="tok-num">2</span>); <span class="tok-com">// Сбросить 2-й бит в 0</span></code></pre>
  </div>
</div>
""",
        "quizzes": [
            {
                "question": "Какое выражение устанавливает 4-й бит переменной flags в единицу?",
                "options": [
                    {
                        "id": "a",
                        "text": "flags |= (1 << 4);",
                        "correct": True,
                        "explanation": "Верно! Побитовое ИЛИ (|) со сдвигом 1 << 4 устанавливает 4-й бит."
                    },
                    {
                        "id": "b",
                        "text": "flags &= ~(1 << 4);",
                        "correct": False,
                        "explanation": "Это выражение сбрасывает бит."
                    }
                ]
            }
        ],
        "task": "Дана unsigned int flags = 0;\nУстановите бит 2 и бит 4.\nВыведите значение.\nЗатем сбросьте бит 2 и выведите результат:\nFlags with bits 2 and 4: 20\nFlags after clearing bit 2: 16",
        "initialCode": """#include <stdio.h>

int main(void) {
    unsigned int flags = 0;
    // Установите биты 2 и 4:
    
    printf("Flags with bits 2 and 4: %u\\n", flags);

    // Сбросьте бит 2:
    
    printf("Flags after clearing bit 2: %u\\n", flags);
    return 0;
}
""",
        "solution": """#include <stdio.h>

int main(void) {
    unsigned int flags = 0;
    flags |= (1 << 2);
    flags |= (1 << 4);
    printf("Flags with bits 2 and 4: %u\\n", flags);

    flags &= ~(1 << 2);
    printf("Flags after clearing bit 2: %u\\n", flags);
    return 0;
}
""",
        "hints": [
            "flags |= (1 << 2); flags |= (1 << 4);",
            "flags &= ~(1 << 2);"
        ],
        "expectedOutput": "Flags with bits 2 and 4: 20\nFlags after clearing bit 2: 16\n"
    },
    {
        "id": 7,
        "title": "Урок 7: УКАЗАТЕЛИ (Pointers) — Адресация в оперативной памяти (RAM)",
        "lang": "C",
        "difficulty": "Средний",
        "theory": """<div class="theory-section">
  <h3>1. Что такое указатель</h3>
  <p>Указатель — это переменная, значением которой является <strong>АДРЕС в оперативной памяти</strong> другого объекта!</p>
  <ul>
    <li>Оператор <code>&amp;</code> (взятие адреса): <code>int *ptr = &amp;health;</code> — записывает адрес переменной в ptr.</li>
    <li>Оператор <code>*</code> (разыменование): <code>*ptr = 250;</code> — идет по адресу и перезаписывает значение health!</li>
  </ul>
  <p>На 64-битных системах x86_64 любой указатель занимает ровно <strong>8 байт</strong>.</p>
</div>
""",
        "quizzes": [
            {
                "question": "Если int x = 42; int *p = &x; что сделает инструкция *p = 99;?",
                "options": [
                    {
                        "id": "a",
                        "text": "Изменит значение переменной x на 99, обратившись к ней по адресу",
                        "correct": True,
                        "explanation": "Верно! Оператор * разыменовывает адрес и записывает 99 в исходную ячейку памяти."
                    },
                    {
                        "id": "b",
                        "text": "Создаст новую переменную x2",
                        "correct": False,
                        "explanation": "Неверно. Разыменование меняет данные по существующему адресу."
                    }
                ]
            }
        ],
        "task": "Напишите функцию void add_gold(int *player_gold, int amount), которая через указатель увеличивает золото игрока.\nВ main создайте int gold = 500;, вызовите add_gold(&gold, 250) и выведите:\nPlayer Gold: 750",
        "initialCode": """#include <stdio.h>

// Напишите add_gold:

int main(void) {
    int gold = 500;
    // Вызовите add_gold(&gold, 250):
    
    printf("Player Gold: %d\\n", gold);
    return 0;
}
""",
        "solution": """#include <stdio.h>

void add_gold(int *player_gold, int amount) {
    if (player_gold != NULL) {
        *player_gold += amount;
    }
}

int main(void) {
    int gold = 500;
    add_gold(&gold, 250);
    printf("Player Gold: %d\\n", gold);
    return 0;
}
""",
        "hints": [
            "void add_gold(int *player_gold, int amount) { *player_gold += amount; }",
            "add_gold(&gold, 250);"
        ],
        "expectedOutput": "Player Gold: 750\n"
    },
    {
        "id": 8,
        "title": "Урок 8: Адресная арифметика, смещения (Offsets) и указатель void*",
        "lang": "C",
        "difficulty": "Средний",
        "theory": """<div class="theory-section">
  <h3>1. Адресная арифметика</h3>
  <p>Прибавив 1 к указателю на int (<code>ptr + 1</code>), адрес увеличится на <code>sizeof(int)</code> (то есть на 4 байта!).</p>
  <p>Указатель <code>void*</code> — это универсальный сырой адрес на память. Чтобы прочитать из него данные, его приводят к конкретному типу: <code>*(int*)raw_ptr</code>.</p>
</div>
""",
        "quizzes": [
            {
                "question": "Если int *ptr равен адресу 0x2000, чему равен ptr + 2 при sizeof(int) = 4?",
                "options": [
                    {
                        "id": "a",
                        "text": "0x2008 (сместится на 2 * 4 = 8 байт)",
                        "correct": True,
                        "explanation": "Верно! Адрес умножается на размер базового типа (2 * 4 = 8 байт)."
                    },
                    {
                        "id": "b",
                        "text": "0x2002",
                        "correct": False,
                        "explanation": "Неверно. Это правило применимо только к char*."
                    }
                ]
            }
        ],
        "task": "Дан массив int numbers[4] = {11, 22, 33, 44};\nЧерез указатель int *ptr = numbers; и смещение *(ptr + 2) выведите третий элемент:\nThird element via pointer: 33",
        "initialCode": """#include <stdio.h>

int main(void) {
    int numbers[4] = {11, 22, 33, 44};
    int *ptr = numbers;
    int val = 0;

    // Получите третий элемент через *(ptr + 2):
    
    printf("Third element via pointer: %d\\n", val);
    return 0;
}
""",
        "solution": """#include <stdio.h>

int main(void) {
    int numbers[4] = {11, 22, 33, 44};
    int *ptr = numbers;
    int val = *(ptr + 2);

    printf("Third element via pointer: %d\\n", val);
    return 0;
}
""",
        "hints": [
            "val = *(ptr + 2);"
        ],
        "expectedOutput": "Third element via pointer: 33\n"
    },
    {
        "id": 9,
        "title": "Урок 9: Динамическая память в куче (Heap): malloc, free и утечки",
        "lang": "C",
        "difficulty": "Средний",
        "theory": """<div class="theory-section">
  <h3>1. Куча (Heap)</h3>
  <p>Память в куче выделяется во время работы программы через <code>malloc</code> и обязана освобождаться через <code>free</code>. Забытый <code>free</code> ведет к утечке памяти (Memory Leak).</p>
</div>
""",
        "quizzes": [
            {
                "question": "Что произойдет, если вызывать malloc() без free()?",
                "options": [
                    {
                        "id": "a",
                        "text": "Утечка памяти (Memory Leak) — процесс будет бесконечно накапливать занятую RAM",
                        "correct": True,
                        "explanation": "Верно. Без free память кучи не очищается."
                    },
                    {
                        "id": "b",
                        "text": "Память очистится автоматически",
                        "correct": False,
                        "explanation": "В языке Си сборщика мусора нет."
                    }
                ]
            }
        ],
        "task": "Выделите в куче 3 числа int через malloc, запишите 10, 20, 30, сложите и напечатайте:\nAllocated sum: 60\nЗатем освободите через free().",
        "initialCode": """#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // Выделите память, посчитайте сумму и вызовите free:
    
    return 0;
}
""",
        "solution": """#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *arr = (int*)malloc(3 * sizeof(int));
    if (arr == NULL) return 1;

    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;

    int sum = arr[0] + arr[1] + arr[2];
    printf("Allocated sum: %d\\n", sum);

    free(arr);
    return 0;
}
""",
        "hints": [
            "int *arr = (int*)malloc(3 * sizeof(int));",
            "free(arr);"
        ],
        "expectedOutput": "Allocated sum: 60\n"
    },
    {
        "id": 10,
        "title": "Урок 10: Структуры (struct), доступ через стрелочку -> и выравнивание (Padding)",
        "lang": "C",
        "difficulty": "Средний",
        "theory": """<div class="theory-section">
  <h3>1. Структуры в памяти</h3>
  <p>Структура объединяет переменные разных типов. Доступ к полям по указателю осуществляется через оператор стрелочки: <code>p-&gt;health</code>.</p>
</div>
""",
        "quizzes": [
            {
                "question": "Как обратиться к полю health структуры через указатель Player *p?",
                "options": [
                    {
                        "id": "a",
                        "text": "p->health",
                        "correct": True,
                        "explanation": "Верно! Стрелочка разыменовывает указатель и обращается к полю."
                    },
                    {
                        "id": "b",
                        "text": "p.health",
                        "correct": False,
                        "explanation": "Точка используется для самого объекта, а не указателя."
                    }
                ]
            }
        ],
        "task": "Создайте структуру PlayerData с полями int id, int hp, int ammo.\nНапишите heal(PlayerData *p, int amount), увеличивающую hp.\nВ main для p = {1, 50, 30} увеличьте hp на 50 и напечатайте:\nPlayer ID 1 HP: 100",
        "initialCode": """#include <stdio.h>

// Объявите структуру и функцию:

int main(void) {
    // Проверьте работу:
    
    return 0;
}
""",
        "solution": """#include <stdio.h>

typedef struct {
    int id;
    int hp;
    int ammo;
} PlayerData;

void heal(PlayerData *p, int amount) {
    if (p != NULL) {
        p->hp += amount;
    }
}

int main(void) {
    PlayerData p = {1, 50, 30};
    heal(&p, 50);
    printf("Player ID %d HP: %d\\n", p.id, p.hp);
    return 0;
}
""",
        "hints": [
            "p->hp += amount;"
        ],
        "expectedOutput": "Player ID 1 HP: 100\n"
    },
    {
        "id": 11,
        "title": "Урок 11: Переход к C++: ссылки (&), классы и деструкторы",
        "lang": "C++",
        "difficulty": "Средний",
        "theory": """<div class="theory-section">
  <h3>1. Ссылки и ООП</h3>
  <p>Ссылка (<code>int &amp;ref</code>) — это безопасный синтаксический псевдоним переменной. Классы объединяют приватные поля и публичные методы с конструкторами и деструкторами.</p>
</div>
""",
        "quizzes": [
            {
                "question": "В чем отличие ссылки int &ref от указателя?",
                "options": [
                    {
                        "id": "a",
                        "text": "Ссылка не может быть nullptr и не требует разыменования через *",
                        "correct": True,
                        "explanation": "Верно! Ссылка всегда гарантирует наличие объекта."
                    },
                    {
                        "id": "b",
                        "text": "Ссылка работает только на Windows 98",
                        "correct": False,
                        "explanation": "Неверно."
                    }
                ]
            }
        ],
        "task": "Создайте класс SafeBox с private полем int secret_.\nКонструктор SafeBox(int code) и метод int getSecret() const.\nВ main создайте SafeBox box(777); и выведите:\nSecret Code: 777",
        "initialCode": """#include <iostream>

// Создайте класс SafeBox:

int main() {
    SafeBox box(777);
    std::cout << "Secret Code: " << box.getSecret() << std::endl;
    return 0;
}
""",
        "solution": """#include <iostream>

class SafeBox {
private:
    int secret_;

public:
    SafeBox(int code) : secret_(code) {}

    int getSecret() const {
        return secret_;
    }
};

int main() {
    SafeBox box(777);
    std::cout << "Secret Code: " << box.getSecret() << std::endl;
    return 0;
}
""",
        "hints": [
            "private: int secret_; public: SafeBox(int code) : secret_(code) {}"
        ],
        "expectedOutput": "Secret Code: 777\n"
    },
    {
        "id": 12,
        "title": "Урок 12: Умные указатели (std::unique_ptr) и идиома RAII",
        "lang": "C++",
        "difficulty": "Продвинутый",
        "theory": """<div class="theory-section">
  <h3>1. RAII и std::unique_ptr</h3>
  <p><code>std::unique_ptr</code> единолично владеет объектом в куче и автоматически вызывает <code>delete</code> в деструкторе, исключая утечки памяти.</p>
</div>
""",
        "quizzes": [
            {
                "question": "Почему std::unique_ptr безопаснее сырого указателя с new/delete?",
                "options": [
                    {
                        "id": "a",
                        "text": "Он автоматически освобождает память при выходе из области видимости благодаря RAII",
                        "correct": True,
                        "explanation": "Верно! Деструктор гарантирует вызов delete."
                    },
                    {
                        "id": "b",
                        "text": "Он запрещает компилятору компилировать код",
                        "correct": False,
                        "explanation": "Неверно."
                    }
                ]
            }
        ],
        "task": "Используя std::make_unique, выделите int со значением 4096 и выведите:\nUnique value: 4096",
        "initialCode": """#include <iostream>
#include <memory>

int main() {
    // Создайте unique_ptr:
    
    return 0;
}
""",
        "solution": """#include <iostream>
#include <memory>

int main() {
    auto ptr = std::make_unique<int>(4096);
    std::cout << "Unique value: " << *ptr << std::endl;
    return 0;
}
""",
        "hints": [
            "auto ptr = std::make_unique<int>(4096); std::cout << \"Unique value: \" << *ptr << std::endl;"
        ],
        "expectedOutput": "Unique value: 4096\n"
    },
    {
        "id": 13,
        "title": "Урок 13: Введение в Windows API: типы Win32 (HANDLE, DWORD, LPVOID)",
        "lang": "C++",
        "difficulty": "Продвинутый",
        "theory": """<div class="theory-section">
  <h3>1. Типы Windows API</h3>
  <p>При подключении <code>&lt;windows.h&gt;</code> становятся доступны системные типы:</p>
  <ul>
    <li><code>HANDLE</code> — дескриптор объекта ядра ОС (процесса, файла, потока).</li>
    <li><code>DWORD</code> — 32-битное число без знака (unsigned long).</li>
    <li><code>LPVOID</code> — указатель <code>void*</code>.</li>
    <li><code>BOOL</code> — логический тип Win32 (TRUE/FALSE).</li>
  </ul>
</div>
""",
        "quizzes": [
            {
                "question": "Что представляет собой HANDLE в Windows API?",
                "options": [
                    {
                        "id": "a",
                        "text": "Системный дескриптор ядра операционной системы для управления процессами, файлами или потоками",
                        "correct": True,
                        "explanation": "Верно! HANDLE — это индекс в таблице объектов ядра Windows."
                    },
                    {
                        "id": "b",
                        "text": "Обычная строка текста",
                        "correct": False,
                        "explanation": "Неверно."
                    }
                ]
            }
        ],
        "task": "Объявите DWORD pid = 1337; BOOL is_running = 1; и выведите:\nProcess ID: 1337, Status: Active",
        "initialCode": """#include <stdio.h>

typedef unsigned long DWORD;
typedef int BOOL;

int main(void) {
    DWORD pid = 1337;
    BOOL is_running = 1;

    // Выведите строку:
    
    return 0;
}
""",
        "solution": """#include <stdio.h>

typedef unsigned long DWORD;
typedef int BOOL;

int main(void) {
    DWORD pid = 1337;
    BOOL is_running = 1;

    if (is_running) {
        printf("Process ID: %lu, Status: Active\\n", pid);
    }
    return 0;
}
""",
        "hints": [
            "printf(\"Process ID: %lu, Status: Active\\n\", pid);"
        ],
        "expectedOutput": "Process ID: 1337, Status: Active\n"
    },
    {
        "id": 14,
        "title": "Урок 14: Виртуальная память Windows, страницы 4 КБ и права доступа",
        "lang": "C++",
        "difficulty": "Эксперт",
        "theory": """<div class="theory-section">
  <h3>1. Виртуальная память</h3>
  <p>Каждый процесс живет в изолированном виртуальном пространстве. Память делится на страницы по <strong>4096 байт (4 КБ)</strong> с правами доступа (<code>PAGE_READWRITE</code>, <code>PAGE_EXECUTE_READWRITE</code>).</p>
</div>
""",
        "quizzes": [
            {
                "question": "Какой стандартный размер страницы памяти в архитектуре x86/x64 Windows?",
                "options": [
                    {
                        "id": "a",
                        "text": "4096 байт (4 КБ)",
                        "correct": True,
                        "explanation": "Верно! Стандартная страница равна 4 КБ."
                    },
                    {
                        "id": "b",
                        "text": "16 байт",
                        "correct": False,
                        "explanation": "Неверно."
                    }
                ]
            }
        ],
        "task": "Вычислите, сколько целых чисел int (по 4 байта) помещается в страницу 4096 байт и выведите:\nIntegers in 4KB page: 1024",
        "initialCode": """#include <stdio.h>

int main(void) {
    size_t page_size = 4096;
    size_t int_size = sizeof(int);

    // Посчитайте:
    size_t count = 0;
    
    printf("Integers in 4KB page: %zu\\n", count);
    return 0;
}
""",
        "solution": """#include <stdio.h>

int main(void) {
    size_t page_size = 4096;
    size_t int_size = sizeof(int);
    size_t count = page_size / int_size;

    printf("Integers in 4KB page: %zu\\n", count);
    return 0;
}
""",
        "hints": [
            "count = page_size / int_size;"
        ],
        "expectedOutput": "Integers in 4KB page: 1024\n"
    },
    {
        "id": 15,
        "title": "Урок 15: Процессы в Windows, PID и системный вызов OpenProcess",
        "lang": "C++",
        "difficulty": "Эксперт",
        "theory": """<div class="theory-section">
  <h3>1. OpenProcess</h3>
  <p>Функция <code>OpenProcess(dwDesiredAccess, FALSE, pid)</code> открывает дескриптор целевого процесса с флагами доступа (<code>PROCESS_VM_READ</code>, <code>PROCESS_VM_WRITE</code>). После работы дескриптор обязательно закрывается через <code>CloseHandle</code>.</p>
</div>
""",
        "quizzes": [
            {
                "question": "Какую функцию необходимо вызвать для закрытия HANDLE процесса?",
                "options": [
                    {
                        "id": "a",
                        "text": "CloseHandle(hProcess);",
                        "correct": True,
                        "explanation": "Верно! CloseHandle освобождает дескриптор ядра."
                    },
                    {
                        "id": "b",
                        "text": "free(hProcess);",
                        "correct": False,
                        "explanation": "free работает с памятью кучи, а не с объектами ядра."
                    }
                ]
            }
        ],
        "task": "Смоделируйте открытие процесса для target_pid = 2048 и desired_access = 0x0010:\nTarget PID: 2048, DesiredAccess: 0x0010, Status: Handle Acquired",
        "initialCode": """#include <stdio.h>

int main(void) {
    unsigned long target_pid = 2048;
    unsigned long desired_access = 0x0010;

    // Выведите статус:
    
    return 0;
}
""",
        "solution": """#include <stdio.h>

int main(void) {
    unsigned long target_pid = 2048;
    unsigned long desired_access = 0x0010;

    printf("Target PID: %lu, DesiredAccess: 0x%04lX, Status: Handle Acquired\\n", target_pid, desired_access);
    return 0;
}
""",
        "hints": [
            "printf(\"Target PID: %lu, DesiredAccess: 0x%04lX, Status: Handle Acquired\\n\", target_pid, desired_access);"
        ],
        "expectedOutput": "Target PID: 2048, DesiredAccess: 0x0010, Status: Handle Acquired\n"
    },
    {
        "id": 16,
        "title": "Урок 16: Чтение памяти другого процесса через ReadProcessMemory",
        "lang": "C++",
        "difficulty": "Эксперт",
        "theory": """<div class="theory-section">
  <h3>1. ReadProcessMemory</h3>
  <p>Функция <code>ReadProcessMemory(hProcess, lpBaseAddress, lpBuffer, nSize, NULL)</code> копирует указанное количество байт из чужого адресного пространства в буфер нашей программы.</p>
</div>
""",
        "quizzes": [
            {
                "question": "Что передается вторым аргументом (lpBaseAddress) в ReadProcessMemory?",
                "options": [
                    {
                        "id": "a",
                        "text": "Адрес в виртуальной памяти целевого процесса, откуда читать данные",
                        "correct": True,
                        "explanation": "Верно! Это адрес целевой ячейки памяти в чужом процессе."
                    },
                    {
                        "id": "b",
                        "text": "Номер кредитной карты",
                        "correct": False,
                        "explanation": "Неверно."
                    }
                ]
            }
        ],
        "task": "Смоделируйте чтение памяти: из target_ram[4] = {10, 20, 999, 40} по смещению offset = 2 прочитайте значение и выведите:\nReadProcessMemory Result: 999 HP (bytes read: 4)",
        "initialCode": """#include <stdio.h>

int main(void) {
    int target_ram[4] = {10, 20, 999, 40};
    size_t offset = 2;
    int read_buffer = 0;
    size_t bytes_read = sizeof(int);

    // Прочитайте значение:
    
    printf("ReadProcessMemory Result: %d HP (bytes read: %zu)\\n", read_buffer, bytes_read);
    return 0;
}
""",
        "solution": """#include <stdio.h>

int main(void) {
    int target_ram[4] = {10, 20, 999, 40};
    size_t offset = 2;
    int read_buffer = target_ram[offset];
    size_t bytes_read = sizeof(int);

    printf("ReadProcessMemory Result: %d HP (bytes read: %zu)\\n", read_buffer, bytes_read);
    return 0;
}
""",
        "hints": [
            "read_buffer = target_ram[offset];"
        ],
        "expectedOutput": "ReadProcessMemory Result: 999 HP (bytes read: 4)\n"
    },
    {
        "id": 17,
        "title": "Урок 17: Модификация памяти, WriteProcessMemory и NOP-патчинг (0x90)",
        "lang": "C++",
        "difficulty": "Эксперт",
        "theory": """<div class="theory-section">
  <h3>1. Патчинг опкодов и WriteProcessMemory</h3>
  <p>Функция <code>WriteProcessMemory</code> перезаписывает байты в памяти чужого процесса. Чтобы отключить вычитание патронов или здоровья (инструкцию SUB), системные реверсеры заменяют её на инструкцию <code>NOP</code> (No Operation), опкод которой равен <code>0x90</code>.</p>
</div>
""",
        "quizzes": [
            {
                "question": "Какой опкод в архитектуре x86/x64 соответствует инструкции NOP (пустая операция)?",
                "options": [
                    {
                        "id": "a",
                        "text": "0x90",
                        "correct": True,
                        "explanation": "Верно! Байт 0x90 — это инструкция NOP в процессорах Intel/AMD."
                    },
                    {
                        "id": "b",
                        "text": "0x00",
                        "correct": False,
                        "explanation": "Неверно."
                    }
                ]
            }
        ],
        "task": "Замените в массиве unsigned char code[3] = {0x29, 0x50, 0x10}; все 3 байта на опкод 0x90 (NOP) и напечатайте:\nPatched bytes: 0x90 0x90 0x90 (NOP applied)",
        "initialCode": """#include <stdio.h>

int main(void) {
    unsigned char code[3] = {0x29, 0x50, 0x10};

    // Замените байты на 0x90:
    
    printf("Patched bytes: 0x%02X 0x%02X 0x%02X (NOP applied)\\n", code[0], code[1], code[2]);
    return 0;
}
""",
        "solution": """#include <stdio.h>

int main(void) {
    unsigned char code[3] = {0x29, 0x50, 0x10};
    code[0] = 0x90;
    code[1] = 0x90;
    code[2] = 0x90;

    printf("Patched bytes: 0x%02X 0x%02X 0x%02X (NOP applied)\\n", code[0], code[1], code[2]);
    return 0;
}
""",
        "hints": [
            "code[0] = 0x90; code[1] = 0x90; code[2] = 0x90;"
        ],
        "expectedOutput": "Patched bytes: 0x90 0x90 0x90 (NOP applied)\n"
    },
    {
        "id": 18,
        "title": "Урок 18: Финальный курсовой проект: Собственный Memory Trainer Engine на C++",
        "lang": "C++",
        "difficulty": "Эксперт",
        "theory": """<div class="theory-section">
  <h3>1. Архитектура Memory Trainer Engine</h3>
  <p>Объединив все знания, мы строим класс <code>TrainerMemory</code> с автоматическим управлением дескриптором (RAII), методами чтения и записи в память.</p>
</div>
""",
        "quizzes": [
            {
                "question": "Почему оформление работы с памятью в C++ класс с RAII деструктором является лучшей системной практикой?",
                "options": [
                    {
                        "id": "a",
                        "text": "Деструктор класса гарантированно закроет CloseHandle(hProcess), предотвращая утечки ресурсов ОС при любом выходе",
                        "correct": True,
                        "explanation": "Верно! Это фундаментальный принцип надежности C++ софта."
                    },
                    {
                        "id": "b",
                        "text": "Это не имеет значения",
                        "correct": False,
                        "explanation": "Неверно."
                    }
                ]
            }
        ],
        "task": "Используя класс TrainerMemory, запишите значение 9999 по смещению 4 и выведите:\n[TrainerCode Engine] Target Health: 9999 (Freeze Active)",
        "initialCode": """#include <iostream>
#include <cstdint>

class TrainerMemory {
private:
    int ram_[16];
public:
    TrainerMemory() {
        for (int i = 0; i < 16; i++) ram_[i] = 0;
        ram_[4] = 100;
    }
    int readInt(uintptr_t addr) { return ram_[addr]; }
    void writeInt(uintptr_t addr, int val) { ram_[addr] = val; }
};

int main() {
    TrainerMemory trainer;
    // Запишите 9999 по адресу 4 и выведите строку:
    
    return 0;
}
""",
        "solution": """#include <iostream>
#include <cstdint>

class TrainerMemory {
private:
    int ram_[16];
public:
    TrainerMemory() {
        for (int i = 0; i < 16; i++) ram_[i] = 0;
        ram_[4] = 100;
    }
    int readInt(uintptr_t addr) { return ram_[addr]; }
    void writeInt(uintptr_t addr, int val) { ram_[addr] = val; }
};

int main() {
    TrainerMemory trainer;
    trainer.writeInt(4, 9999);
    int current_hp = trainer.readInt(4);
    std::cout << "[TrainerCode Engine] Target Health: " << current_hp << " (Freeze Active)" << std::endl;
    return 0;
}
""",
        "hints": [
            "trainer.writeInt(4, 9999);",
            "std::cout << \"[TrainerCode Engine] Target Health: \" << current_hp << \" (Freeze Active)\" << std::endl;"
        ],
        "expectedOutput": "[TrainerCode Engine] Target Health: 9999 (Freeze Active)\n"
    }
]

# Write JSON
json_path = "/home/user/TrainerCode/web_preview/public/lessons.json"
with open(json_path, "w", encoding="utf-8") as f:
    json.dump(lessons, f, ensure_ascii=False, indent=2)

print(f"Generated {len(lessons)} rich lessons into {json_path}")
