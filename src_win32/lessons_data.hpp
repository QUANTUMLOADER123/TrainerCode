#pragma once
#include <string>
#include <vector>

struct Lesson {
    int id;
    std::wstring module_name;
    std::wstring title;
    std::wstring lang;
    std::wstring difficulty;
    std::wstring theory;
    std::wstring task;
    std::wstring initial_code;
    std::wstring solution;
    std::vector<std::wstring> hints;
    std::wstring expected_output;
};

inline std::vector<Lesson> get_all_lessons() {
    std::vector<Lesson> list;
    {
        Lesson l;
        l.id = 1;
        l.module_name = L"Модуль 1: Фундамент языка C и архитектура";
        l.title = L"Урок 1: Архитектура ЭВМ и первая программа Hello World";
        l.lang = L"C";
        l.difficulty = L"Новичок";
        l.theory = L"Добро пожаловать в мир системного программирования!\n"
    "\n"
    "Язык C (Си) был создан Деннисом Ритчи в лабораториях Bell Labs в 1972 году для написания операционной системы UNIX. В отличие от Python или JavaScript, Си находится максимально близко к 'железу'. Здесь нет виртуальных машин, сборщиков мусора и скрытых накладных расходов.\n"
    "\n"
    "Как устроена программа на Си:\n"
    "1. Препроцессор: директива #include <stdio.h> подключает заголовочный файл со стандартными функциями ввода/вывода (Standard Input/Output).\n"
    "2. Функция main: точка входа в программу. Операционная система вызывает именно ее.\n"
    "   Синтаксис: int main(void) или int main(int argc, char *argv[])\n"
    "3. Тело функции заключено в фигурные скобки { }.\n"
    "4. Функция printf(\"...\"): выводит форматированную строку в стандартный поток вывода stdout. Символ '\\n' обозначает перевод строки.\n"
    "5. return 0; сообщает операционной системе, что программа завершилась успешно (код выхода 0). Код, отличный от 0 (например, -1 или 1), сигнализирует об ошибке.\n"
    "\n"
    "Этапы сборки программы:\n"
    "- Препроцессинг (расширение макросов, вставка #include)\n"
    "- Компиляция (преобразование Си кода в язык ассемблера)\n"
    "- Ассемблирование (преобразование в машинный объектный код .obj / .o)\n"
    "- Линковка (связывание объектных файлов и системных библиотек в .exe)";
        l.task = L"Напишите программу, которая выводит приветствие:\n"
    "Hello, TrainerCode!\n"
    "Architecture: x86_64\n"
    "и возвращает код 0.";
        l.initial_code = L"#include <stdio.h>\n"
    "\n"
    "int main(void) {\n"
    "    // Напишите вывод приветствия здесь:\n"
    "    \n"
    "    return 0;\n"
    "}\n"
    "";
        l.solution = L"#include <stdio.h>\n"
    "\n"
    "int main(void) {\n"
    "    printf(\"Hello, TrainerCode!\\n\");\n"
    "    printf(\"Architecture: x86_64\\n\");\n"
    "    return 0;\n"
    "}\n"
    "";
        l.expected_output = L"Hello, TrainerCode!\n"
    "Architecture: x86_64\n"
    "";
        l.hints.push_back(L"Используйте функцию printf для вывода текста.");
        l.hints.push_back(L"Не забудьте символ '\\n' в конце каждой строки.");
        l.hints.push_back(L"Убедитесь в точности символов: Hello, TrainerCode!");
        list.push_back(l);
    }
    {
        Lesson l;
        l.id = 2;
        l.module_name = L"Модуль 1: Фундамент языка C и архитектура";
        l.title = L"Урок 2: Фундаментальные типы данных и память";
        l.lang = L"C";
        l.difficulty = L"Новичок";
        l.theory = L"В языке Си каждый тип данных имеет строго определенный размер в байтах в зависимости от архитектуры (x86 vs x64).\n"
    "\n"
    "Основные типы данных:\n"
    "- char (1 байт = 8 бит): хранит один символ ASCII или число от -128 до 127.\n"
    "- int (обычно 4 байта = 32 бита): целое число со знаком (-2,147,483,648 .. 2,147,483,647).\n"
    "- short (2 байта = 16 бит): короткое целое (-32,768 .. 32,767).\n"
    "- long (4 байта на Windows x64, 8 байт на Linux x64).\n"
    "- long long (8 байт = 64 бита): сверхбольшое целое число.\n"
    "- float (4 байта): вещественное число с плавающей точкой одинарной точности (IEEE 754, ~7 знаков точности).\n"
    "- double (8 байт): вещественное число двойной точности (~15 знаков точности).\n"
    "\n"
    "Модификаторы:\n"
    "- signed: со знаком (по умолчанию для int).\n"
    "- unsigned: без знака (только неотрицательные числа, удваивает положительный диапазон! Например, unsigned char: 0 .. 255).\n"
    "\n"
    "Оператор sizeof:\n"
    "Оператор sizeof(тип) возвращает размер типа или переменной в байтах (тип возвращаемого значения — size_t, печатается через %zu).\n"
    "\n"
    "Спецификаторы формата printf:\n"
    "%d или %i — знаковый int\n"
    "%u — беззнаковый unsigned int\n"
    "%ld — long\n"
    "%lld — long long\n"
    "%f — float\n"
    "%lf — double\n"
    "%c — char (символ)\n"
    "%p — указатель (адрес в памяти)\n"
    "%zu — size_t";
        l.task = L"Объявите переменные:\n"
    "- int a = 42;\n"
    "- double pi = 3.14159;\n"
    "- unsigned char flags = 255;\n"
    "Выведите их значения и размеры в байтах, используя sizeof, строго в формате:\n"
    "a = 42 (size: 4)\n"
    "pi = 3.141590 (size: 8)\n"
    "flags = 255 (size: 1)";
        l.initial_code = L"#include <stdio.h>\n"
    "\n"
    "int main(void) {\n"
    "    // Объявите переменные a, pi, flags:\n"
    "    \n"
    "    // Выведите значения и размеры с помощью sizeof:\n"
    "    \n"
    "    return 0;\n"
    "}\n"
    "";
        l.solution = L"#include <stdio.h>\n"
    "\n"
    "int main(void) {\n"
    "    int a = 42;\n"
    "    double pi = 3.14159;\n"
    "    unsigned char flags = 255;\n"
    "\n"
    "    printf(\"a = %d (size: %zu)\\n\", a, sizeof(a));\n"
    "    printf(\"pi = %f (size: %zu)\\n\", pi, sizeof(pi));\n"
    "    printf(\"flags = %u (size: %zu)\\n\", flags, sizeof(flags));\n"
    "    return 0;\n"
    "}\n"
    "";
        l.expected_output = L"a = 42 (size: 4)\n"
    "pi = 3.141590 (size: 8)\n"
    "flags = 255 (size: 1)\n"
    "";
        l.hints.push_back(L"Используйте %zu для вывода результата sizeof.");
        l.hints.push_back(L"Используйте %u для unsigned char.");
        l.hints.push_back(L"Используйте %f для double в printf.");
        list.push_back(l);
    }
    {
        Lesson l;
        l.id = 3;
        l.module_name = L"Модуль 1: Фундамент языка C и архитектура";
        l.title = L"Урок 3: Ввод данных, scanf и ветвления if / else";
        l.lang = L"C";
        l.difficulty = L"Новичок";
        l.theory = L"Функция scanf():\n"
    "Для чтения данных из консоли используется функция scanf:\n"
    "int x;\n"
    "scanf(\"%d\", &x);\n"
    "\n"
    "ВАЖНО: Обратите внимание на амперсанд (&)! Оператор & берет адрес переменной x в оперативной памяти. Функция scanf должна знать, куда именно записать прочитанные байты.\n"
    "\n"
    "Условный оператор if / else:\n"
    "if (условие) {\n"
    "    // выполняется если условие истинно (!= 0)\n"
    "} else if (другое_условие) {\n"
    "    // ...\n"
    "} else {\n"
    "    // выполняется во всех остальных случаях\n"
    "}\n"
    "\n"
    "Операторы сравнения:\n"
    "== (равно), != (не равно), <, >, <=, >=\n"
    "\n"
    "Логические операторы:\n"
    "&& (логическое И, AND)\n"
    "|| (логическое ИЛИ, OR)\n"
    "!  (логическое НЕ, NOT)\n"
    "\n"
    "Тернарный оператор:\n"
    "результат = (условие) ? значение_если_истина : значение_если_ложь;";
        l.task = L"Напишите программу проверки четности и знака числа:\n"
    "Пусть дано число int n = -8;\n"
    "Если число отрицательное, выведите 'Negative', если 0 — 'Zero', если положительное — 'Positive'.\n"
    "Затем с новой строки выведите 'Even' для четного или 'Odd' для нечетного числа.\n"
    "Пример для -8:\n"
    "Negative\n"
    "Even";
        l.initial_code = L"#include <stdio.h>\n"
    "\n"
    "int main(void) {\n"
    "    int n = -8;\n"
    "    // Проверьте знак и четность числа:\n"
    "    \n"
    "    return 0;\n"
    "}\n"
    "";
        l.solution = L"#include <stdio.h>\n"
    "\n"
    "int main(void) {\n"
    "    int n = -8;\n"
    "    if (n < 0) {\n"
    "        printf(\"Negative\\n\");\n"
    "    } else if (n > 0) {\n"
    "        printf(\"Positive\\n\");\n"
    "    } else {\n"
    "        printf(\"Zero\\n\");\n"
    "    }\n"
    "\n"
    "    if (n % 2 == 0) {\n"
    "        printf(\"Even\\n\");\n"
    "    } else {\n"
    "        printf(\"Odd\\n\");\n"
    "    }\n"
    "    return 0;\n"
    "}\n"
    "";
        l.expected_output = L"Negative\n"
    "Even\n"
    "";
        l.hints.push_back(L"Используйте оператор остатка от деления %: n % 2 == 0 означает четное число.");
        l.hints.push_back(L"Сначала выведите Negative/Positive/Zero, затем Even/Odd.");
        list.push_back(l);
    }
    {
        Lesson l;
        l.id = 4;
        l.module_name = L"Модуль 1: Фундамент языка C и архитектура";
        l.title = L"Урок 4: Циклы for, while, do-while и операторы break / continue";
        l.lang = L"C";
        l.difficulty = L"Новичок";
        l.theory = L"Циклы позволяют многократно выполнять блок инструкций. В Си существуют три основных вида циклов:\n"
    "\n"
    "1. Цикл for:\n"
    "for (инициализация; условие_продолжения; инкремент) {\n"
    "    // тело цикла\n"
    "}\n"
    "Пример:\n"
    "for (int i = 0; i < 5; i++) {\n"
    "    printf(\"%d \", i);\n"
    "}\n"
    "\n"
    "2. Цикл while (цикл с предусловием):\n"
    "while (условие) {\n"
    "    // проверяет условие ДО выполнения тела\n"
    "}\n"
    "\n"
    "3. Цикл do-while (цикл с постусловием):\n"
    "do {\n"
    "    // тело цикла ВСЕГДА выполнится хотя бы один раз!\n"
    "} while (условие);\n"
    "\n"
    "Управление циклом:\n"
    "- break: немедленный досрочный выход из цикла.\n"
    "- continue: переход к следующей итерации цикла (пропуская оставшийся код в текущем шаге).";
        l.task = L"Напишите цикл for, вычисляющий сумму всех нечетных чисел от 1 до 20 включительно. Выведите результат в формате:\n"
    "Sum: 100";
        l.initial_code = L"#include <stdio.h>\n"
    "\n"
    "int main(void) {\n"
    "    int sum = 0;\n"
    "    // Напишите цикл здесь:\n"
    "    \n"
    "    printf(\"Sum: %d\\n\", sum);\n"
    "    return 0;\n"
    "}\n"
    "";
        l.solution = L"#include <stdio.h>\n"
    "\n"
    "int main(void) {\n"
    "    int sum = 0;\n"
    "    for (int i = 1; i <= 20; i++) {\n"
    "        if (i % 2 != 0) {\n"
    "            sum += i;\n"
    "        }\n"
    "    }\n"
    "    printf(\"Sum: %d\\n\", sum);\n"
    "    return 0;\n"
    "}\n"
    "";
        l.expected_output = L"Sum: 100\n"
    "";
        l.hints.push_back(L"Используйте цикл от 1 до 20 включительно (i <= 20).");
        l.hints.push_back(L"Для проверки нечетности: i % 2 != 0.");
        l.hints.push_back(L"Сумма нечетных чисел от 1 до 19 равна 100.");
        list.push_back(l);
    }
    {
        Lesson l;
        l.id = 5;
        l.module_name = L"Модуль 1: Фундамент языка C и архитектура";
        l.title = L"Урок 5: Побитовые операции и битовые маски";
        l.lang = L"C";
        l.difficulty = L"Средний";
        l.theory = L"Побитовые операции работают непосредственно с двоичными битами чисел в регистрах процессора. Это ключевой навык для низкоуровневого программирования, драйверов и встроенных систем.\n"
    "\n"
    "Операторы:\n"
    "&  (Побитовое И / AND): 1 & 1 = 1, иначе 0. Применяется для выделения бита (маскирования).\n"
    "|  (Побитовое ИЛИ / OR): 1 | 0 = 1, 0 | 0 = 0. Применяется для установки бита в 1.\n"
    "^  (Побитовое исключающее ИЛИ / XOR): 1 ^ 1 = 0, 1 ^ 0 = 1. Инвертирует бит или шифрует.\n"
    "~  (Побитовое НЕ / NOT): инвертирует все биты (~00001111 = 11110000).\n"
    "<< (Побитовый сдвиг влево): x << n умножает x на 2^n.\n"
    ">> (Побитовый сдвиг вправо): x >> n делит x на 2^n.\n"
    "\n"
    "Основные идиомы битовых масок:\n"
    "1. Установить n-й бит в 1:\n"
    "   flags |= (1U << n);\n"
    "2. Сбросить n-й бит в 0:\n"
    "   flags &= ~(1U << n);\n"
    "3. Проверить n-й бит:\n"
    "   bool is_set = (flags & (1U << n)) != 0;\n"
    "4. Переключить n-й бит (toggle):\n"
    "   flags ^= (1U << n);";
        l.task = L"Пусть дано число unsigned char val = 0b00001010 (десятичное 10).\n"
    "1. Установите нулевой бит (бит 0) в единицу.\n"
    "2. Сбросьте первый бит (бит 1) в ноль.\n"
    "Выведите итоговое десятичное число в формате:\n"
    "Result: 9";
        l.initial_code = L"#include <stdio.h>\n"
    "\n"
    "int main(void) {\n"
    "    unsigned char val = 10; // Двоичное: 00001010\n"
    "    // Установите бит 0:\n"
    "    \n"
    "    // Сбросьте бит 1:\n"
    "    \n"
    "    printf(\"Result: %u\\n\", val);\n"
    "    return 0;\n"
    "}\n"
    "";
        l.solution = L"#include <stdio.h>\n"
    "\n"
    "int main(void) {\n"
    "    unsigned char val = 10; // Двоичное: 00001010\n"
    "    val |= (1 << 0);        // Стало 00001011 (11)\n"
    "    val &= ~(1 << 1);       // Сбросили бит 1 -> 00001001 (9)\n"
    "\n"
    "    printf(\"Result: %u\\n\", val);\n"
    "    return 0;\n"
    "}\n"
    "";
        l.expected_output = L"Result: 9\n"
    "";
        l.hints.push_back(L"Для установки бита: val |= (1 << 0)");
        l.hints.push_back(L"Для сброса бита: val &= ~(1 << 1)");
        l.hints.push_back(L"10 в двоичной системе это 00001010. После изменений получается 00001001 (9).");
        list.push_back(l);
    }
    {
        Lesson l;
        l.id = 6;
        l.module_name = L"Модуль 2: Функции, Стек и Память";
        l.title = L"Урок 6: Функции, стек вызовов (Call Stack) и области видимости";
        l.lang = L"C";
        l.difficulty = L"Новичок";
        l.theory = L"Функции в Си разделяют программу на повторно используемые модули.\n"
    "\n"
    "Прототип функции:\n"
    "Компилятор Си читает исходный файл сверху вниз. Если функция вызывается до своего определения, компилятору необходимо объявить прототип:\n"
    "int add(int a, int b); // Прототип (декларация)\n"
    "\n"
    "Передача аргументов:\n"
    "В языке Си ВСЕ аргументы передаются ПО ЗНАЧЕНИЮ (by value). Это значит, что создается копия аргумента. Если вы измените переменную внутри функции, оригинальная переменная в main НЕ изменится!\n"
    "\n"
    "Стек вызовов (Call Stack):\n"
    "При каждом вызове функции на вершине стека выделяется так называемый 'стековый фрейм' (Stack Frame). Он содержит:\n"
    "- Адрес возврата (куда вернуться в коде после return)\n"
    "- Локальные переменные\n"
    "- Параметры функции\n"
    "Когда функция завершается, ее фрейм мгновенно освобождается (регистр указателя стека ESP/RSP сдвигается).\n"
    "\n"
    "Ключевые слова:\n"
    "- static переменная внутри функции сохраняет свое значение между вызовами! Она живет в сегменте данных .data, а не на стеке.\n"
    "- inline — подсказка компилятору встроить код функции прямо в место вызова для экономии тактов процессора.";
        l.task = L"Напишите функцию int counter(void), внутри которой находится статическая переменная (static int count = 0), увеличивающаяся на 1 при каждом вызове и возвращающая текущее значение.\n"
    "Вызовите counter() три раза и выведите:\n"
    "Call 1: 1\n"
    "Call 2: 2\n"
    "Call 3: 3";
        l.initial_code = L"#include <stdio.h>\n"
    "\n"
    "// Напишите функцию counter здесь:\n"
    "\n"
    "int main(void) {\n"
    "    printf(\"Call 1: %d\\n\", counter());\n"
    "    printf(\"Call 2: %d\\n\", counter());\n"
    "    printf(\"Call 3: %d\\n\", counter());\n"
    "    return 0;\n"
    "}\n"
    "";
        l.solution = L"#include <stdio.h>\n"
    "\n"
    "int counter(void) {\n"
    "    static int count = 0;\n"
    "    count++;\n"
    "    return count;\n"
    "}\n"
    "\n"
    "int main(void) {\n"
    "    printf(\"Call 1: %d\\n\", counter());\n"
    "    printf(\"Call 2: %d\\n\", counter());\n"
    "    printf(\"Call 3: %d\\n\", counter());\n"
    "    return 0;\n"
    "}\n"
    "";
        l.expected_output = L"Call 1: 1\n"
    "Call 2: 2\n"
    "Call 3: 3\n"
    "";
        l.hints.push_back(L"Используйте static int count = 0 внутри counter().");
        l.hints.push_back(L"Статические локальные переменные инициализируются только один раз.");
        list.push_back(l);
    }
    {
        Lesson l;
        l.id = 7;
        l.module_name = L"Модуль 2: Функции, Стек и Память";
        l.title = L"Урок 7: Рекурсия и предотвращение Stack Overflow";
        l.lang = L"C";
        l.difficulty = L"Средний";
        l.theory = L"Рекурсия — это процесс, когда функция вызывает саму себя.\n"
    "\n"
    "Каждая рекурсивная функция обязана иметь базовый случай (Base Case) — условие останова. Если базовый случай отсутствует или некорректен, рекурсия становится бесконечной.\n"
    "\n"
    "Что происходит при бесконечной рекурсии?\n"
    "Каждый вызов функции аллоцирует новый фрейм на стеке (обычно размер стека в Windows составляет 1 МБ или 2 МБ). Когда фреймы переполняют выделенную память стека, операционная система немедленно завершает процесс с критической ошибкой: Stack Overflow (Код исключения EXCEPTION_STACK_OVERFLOW 0xC00000FD).\n"
    "\n"
    "Классический пример: Факториал N!\n"
    "N! = N * (N - 1)!\n"
    "0! = 1\n"
    "1! = 1\n"
    "\n"
    "Хвостовая рекурсия (Tail Recursion):\n"
    "Если рекурсивный вызов является самым последним действием перед return, умный компилятор (с флагом -O2 или /O2) способен оптимизировать его в обычный цикл jmp, не тратя стек!";
        l.task = L"Напишите рекурсивную функцию long long factorial(int n), корректно обрабатывающую базовый случай n <= 1.\n"
    "Вычислите factorial(6) и выведите:\n"
    "Factorial(6) = 720";
        l.initial_code = L"#include <stdio.h>\n"
    "\n"
    "long long factorial(int n) {\n"
    "    // Реализуйте базовый случай и рекурсивный шаг:\n"
    "}\n"
    "\n"
    "int main(void) {\n"
    "    printf(\"Factorial(6) = %lld\\n\", factorial(6));\n"
    "    return 0;\n"
    "}\n"
    "";
        l.solution = L"#include <stdio.h>\n"
    "\n"
    "long long factorial(int n) {\n"
    "    if (n <= 1) {\n"
    "        return 1;\n"
    "    }\n"
    "    return n * factorial(n - 1);\n"
    "}\n"
    "\n"
    "int main(void) {\n"
    "    printf(\"Factorial(6) = %lld\\n\", factorial(6));\n"
    "    return 0;\n"
    "}\n"
    "";
        l.expected_output = L"Factorial(6) = 720\n"
    "";
        l.hints.push_back(L"Базовый случай: if (n <= 1) return 1;");
        l.hints.push_back(L"Рекурсивный вызов: return n * factorial(n - 1);");
        l.hints.push_back(L"Для long long спецификатор формата — %lld.");
        list.push_back(l);
    }
    {
        Lesson l;
        l.id = 8;
        l.module_name = L"Модуль 3: Массивы, Строки и Указатели";
        l.title = L"Урок 8: Массивы в Си и непрерывная память";
        l.lang = L"C";
        l.difficulty = L"Новичок";
        l.theory = L"Массив — это непрерывная область памяти, хранящая элементы одного типа друг за другом.\n"
    "\n"
    "Объявление и инициализация:\n"
    "int arr[5] = {10, 20, 30, 40, 50};\n"
    "\n"
    "Индексация:\n"
    "Индексы в Си начинаются строго с 0!\n"
    "arr[0] — первый элемент (смещение 0 байт)\n"
    "arr[4] — последний элемент\n"
    "Размер массива в байтах: sizeof(arr) = 5 * sizeof(int) = 20 байт.\n"
    "Количество элементов в массиве:\n"
    "size_t count = sizeof(arr) / sizeof(arr[0]);\n"
    "\n"
    "ВНИМАНИЕ — ВЫХОД ЗА ПРЕДЕЛЫ МАССИВА (Buffer Overflow):\n"
    "Язык Си не выполняет проверку границ массивов во время выполнения (Bounds Checking)!\n"
    "Если вы обратитесь к arr[10], Си прочитает чужую память. Если вы запишете туда данные, вы затрете другие переменные или адрес возврата функции — это критическая уязвимость безопасности!";
        l.task = L"Дан массив int numbers[] = {12, 45, 7, 89, 23, 56};\n"
    "Найдите максимальное число в массиве с помощью цикла for и выведите:\n"
    "Max: 89";
        l.initial_code = L"#include <stdio.h>\n"
    "\n"
    "int main(void) {\n"
    "    int numbers[] = {12, 45, 7, 89, 23, 56};\n"
    "    size_t count = sizeof(numbers) / sizeof(numbers[0]);\n"
    "    int max = numbers[0];\n"
    "\n"
    "    // Найдите максимум:\n"
    "    \n"
    "    printf(\"Max: %d\\n\", max);\n"
    "    return 0;\n"
    "}\n"
    "";
        l.solution = L"#include <stdio.h>\n"
    "\n"
    "int main(void) {\n"
    "    int numbers[] = {12, 45, 7, 89, 23, 56};\n"
    "    size_t count = sizeof(numbers) / sizeof(numbers[0]);\n"
    "    int max = numbers[0];\n"
    "\n"
    "    for (size_t i = 1; i < count; i++) {\n"
    "        if (numbers[i] > max) {\n"
    "            max = numbers[i];\n"
    "        }\n"
    "    }\n"
    "\n"
    "    printf(\"Max: %d\\n\", max);\n"
    "    return 0;\n"
    "}\n"
    "";
        l.expected_output = L"Max: 89\n"
    "";
        l.hints.push_back(L"Итерируйтесь по массиву от i = 1 до i < count.");
        l.hints.push_back(L"Если numbers[i] > max, обновляйте max = numbers[i].");
        list.push_back(l);
    }
    {
        Lesson l;
        l.id = 9;
        l.module_name = L"Модуль 3: Массивы, Строки и Указатели";
        l.title = L"Урок 9: Строки в Си, нуль-терминатор '\\0' и строковые функции";
        l.lang = L"C";
        l.difficulty = L"Новичок";
        l.theory = L"В языке Си нет встроенного типа 'string'!\n"
    "Строка в Си — это обычный массив символов char, заканчивающийся специальным байтом — нуль-терминатором '\\0' (байт со значением 0).\n"
    "\n"
    "Пример:\n"
    "char msg[] = \"C2000\";\n"
    "В памяти это массив из 6 байтов:\n"
    "['C', '2', '0', '0', '0', '\\0']\n"
    "Если нуль-терминатор отсутствует, функции вроде printf(\"%s\") будут бежать по памяти дальше, печатая мусор, пока случайно не встретят нулевой байт или не упадут с Segmentation Fault!\n"
    "\n"
    "Стандартная библиотека <string.h>:\n"
    "- strlen(str): возвращает длину строки без учета '\\0'.\n"
    "- strcpy(dest, src): копирует строку (ОПАСНО, нет проверки размера!).\n"
    "- strncpy(dest, src, n): копирует не более n символов.\n"
    "- strcat(dest, src): конкатенация строк.\n"
    "- strcmp(s1, s2): сравнивает строки лексикографически. Возвращает 0, если строки абсолютно равны!\n"
    "- snprintf(buffer, sizeof(buffer), \"format\", ...): самый безопасный способ форматирования строк в Си.";
        l.task = L"Дана строка char greeting[32] = \"Hello\";\n"
    "Используйте snprintf или strcat, чтобы добавить к ней \", C Developer!\"\n"
    "Выведите полученную строку и ее длину:\n"
    "Greeting: Hello, C Developer!\n"
    "Length: 20";
        l.initial_code = L"#include <stdio.h>\n"
    "#include <string.h>\n"
    "\n"
    "int main(void) {\n"
    "    char greeting[32] = \"Hello\";\n"
    "    \n"
    "    // Добавьте \", C Developer!\" и вычислите длину:\n"
    "    \n"
    "    printf(\"Greeting: %s\\n\", greeting);\n"
    "    printf(\"Length: %zu\\n\", strlen(greeting));\n"
    "    return 0;\n"
    "}\n"
    "";
        l.solution = L"#include <stdio.h>\n"
    "#include <string.h>\n"
    "\n"
    "int main(void) {\n"
    "    char greeting[32] = \"Hello\";\n"
    "    strcat(greeting, \", C Developer!\");\n"
    "    \n"
    "    printf(\"Greeting: %s\\n\", greeting);\n"
    "    printf(\"Length: %zu\\n\", strlen(greeting));\n"
    "    return 0;\n"
    "}\n"
    "";
        l.expected_output = L"Greeting: Hello, C Developer!\n"
    "Length: 20\n"
    "";
        l.hints.push_back(L"Используйте strcat(greeting, \", C Developer!\");");
        l.hints.push_back(L"strlen возвращает длину строки (20 символов).");
        list.push_back(l);
    }
    {
        Lesson l;
        l.id = 10;
        l.module_name = L"Модуль 3: Массивы, Строки и Указатели";
        l.title = L"Урок 10: УКАЗАТЕЛИ (Pointers) — Сердце и Мощь Си";
        l.lang = L"C";
        l.difficulty = L"Средний";
        l.theory = L"Указатель — это переменная, значением которой является АДРЕС в оперативной памяти другого объекта.\n"
    "\n"
    "Операторы:\n"
    "1. & (Address-of) — взятие адреса переменной:\n"
    "   int val = 100;\n"
    "   int *ptr = &val; // ptr теперь хранит адрес памяти переменной val!\n"
    "\n"
    "2. * (Dereference) — разыменование указателя:\n"
    "   *ptr = 200; // мы идем по адресу ptr и меняем значение val на 200!\n"
    "\n"
    "Размер указателя:\n"
    "На 32-битных системах указатель занимает 4 байта.\n"
    "На 64-битных системах (x86_64) указатель занимает 8 байт (может адресовать до 16 эксабайт памяти!).\n"
    "\n"
    "Адресная арифметика:\n"
    "Когда вы прибавляете 1 к указателю на int:\n"
    "ptr + 1\n"
    "Адрес увеличивается не на 1 байт, а на sizeof(int) (то есть на 4 байта)! Указатель автоматически учитывает размер целевого типа.\n"
    "\n"
    "NULL указатель:\n"
    "Указатель, который никуда не указывает:\n"
    "int *p = NULL; (в C это ((void*)0)). Разыменование NULL (*p) гарантированно крашит программу с Access Violation / Segfault!";
        l.task = L"Напишите функцию swap, которая меняет местами значения двух целых чисел через указатели:\n"
    "void swap(int *a, int *b);\n"
    "В main продемонстрируйте обмен переменных x = 10 и y = 20 и выведите:\n"
    "x = 20, y = 10";
        l.initial_code = L"#include <stdio.h>\n"
    "\n"
    "void swap(int *a, int *b) {\n"
    "    // Поменяйте значения переменных по адресам a и b:\n"
    "}\n"
    "\n"
    "int main(void) {\n"
    "    int x = 10;\n"
    "    int y = 20;\n"
    "    swap(&x, &y);\n"
    "    printf(\"x = %d, y = %d\\n\", x, y);\n"
    "    return 0;\n"
    "}\n"
    "";
        l.solution = L"#include <stdio.h>\n"
    "\n"
    "void swap(int *a, int *b) {\n"
    "    int temp = *a;\n"
    "    *a = *b;\n"
    "    *b = temp;\n"
    "}\n"
    "\n"
    "int main(void) {\n"
    "    int x = 10;\n"
    "    int y = 20;\n"
    "    swap(&x, &y);\n"
    "    printf(\"x = %d, y = %d\\n\", x, y);\n"
    "    return 0;\n"
    "}\n"
    "";
        l.expected_output = L"x = 20, y = 10\n"
    "";
        l.hints.push_back(L"Используйте временную переменную: int temp = *a;");
        l.hints.push_back(L"Присвойте *a = *b; затем *b = temp;");
        l.hints.push_back(L"В main передавайте адреса: swap(&x, &y).");
        list.push_back(l);
    }
    {
        Lesson l;
        l.id = 11;
        l.module_name = L"Модуль 3: Массивы, Строки и Указатели";
        l.title = L"Урок 11: Указатели на функции и Callbacks";
        l.lang = L"C";
        l.difficulty = L"Продвинутый";
        l.theory = L"В Си даже исполняемый машинный код функций находится в оперативной памяти (в сегменте .text). Это означает, что у каждой функции есть свой адрес, и мы можем создавать указатели на функции!\n"
    "\n"
    "Синтаксис указателя на функцию:\n"
    "возвращаемый_тип (*имя_указателя)(типы_параметров);\n"
    "\n"
    "Пример:\n"
    "int add(int a, int b) { return a + b; }\n"
    "int multiply(int a, int b) { return a * b; }\n"
    "\n"
    "// Объявляем указатель op:\n"
    "int (*op)(int, int) = add;\n"
    "int res1 = op(5, 3); // вызовет add -> 8\n"
    "\n"
    "op = multiply;\n"
    "int res2 = op(5, 3); // вызовет multiply -> 15\n"
    "\n"
    "Зачем это нужно?\n"
    "1. Callback-функции (функции обратного вызова при событиях GUI, кликах мыши, сетевых пакетах).\n"
    "2. Стандартная сортировка qsort из <stdlib.h>, которая принимает компаратор:\n"
    "   int compare(const void *a, const void *b);\n"
    "3. Таблицы виртуальных методов (на этом основан полиморфизм в C++ и COM в Windows!).";
        l.task = L"Напишите функцию higher-order:\n"
    "int compute(int x, int y, int (*operation)(int, int))\n"
    "которая вызывает переданную функцию.\n"
    "Объявите две простые функции add и sub, вызовите их через compute и выведите:\n"
    "Add: 15\n"
    "Sub: 5";
        l.initial_code = L"#include <stdio.h>\n"
    "\n"
    "int add(int a, int b) { return a + b; }\n"
    "int sub(int a, int b) { return a - b; }\n"
    "\n"
    "// Реализуйте compute:\n"
    "\n"
    "int main(void) {\n"
    "    printf(\"Add: %d\\n\", compute(10, 5, add));\n"
    "    printf(\"Sub: %d\\n\", compute(10, 5, sub));\n"
    "    return 0;\n"
    "}\n"
    "";
        l.solution = L"#include <stdio.h>\n"
    "\n"
    "int add(int a, int b) { return a + b; }\n"
    "int sub(int a, int b) { return a - b; }\n"
    "\n"
    "int compute(int x, int y, int (*operation)(int, int)) {\n"
    "    return operation(x, y);\n"
    "}\n"
    "\n"
    "int main(void) {\n"
    "    printf(\"Add: %d\\n\", compute(10, 5, add));\n"
    "    printf(\"Sub: %d\\n\", compute(10, 5, sub));\n"
    "    return 0;\n"
    "}\n"
    "";
        l.expected_output = L"Add: 15\n"
    "Sub: 5\n"
    "";
        l.hints.push_back(L"Сигнатура: int compute(int x, int y, int (*operation)(int, int))");
        l.hints.push_back(L"Тело функции: return operation(x, y);");
        list.push_back(l);
    }
    {
        Lesson l;
        l.id = 12;
        l.module_name = L"Модуль 4: Динамическая Память и Пользовательские Типы";
        l.title = L"Урок 12: Динамическая память в куче (Heap): malloc, calloc, free";
        l.lang = L"C";
        l.difficulty = L"Средний";
        l.theory = L"В отличие от стека (размер которого фиксирован и память освобождается автоматически при выходе из функции), память в КУЧЕ (Heap) управляется программистом вручную во время выполнения программы (Runtime).\n"
    "\n"
    "Функции из <stdlib.h>:\n"
    "1. malloc(size_t size):\n"
    "   Выделяет блок памяти размером size байтов. Внимание: память НЕ инициализируется (содержит случайный 'мусор')!\n"
    "   int *arr = (int*)malloc(10 * sizeof(int));\n"
    "\n"
    "2. calloc(size_t num, size_t size):\n"
    "   Выделяет память под num элементов и зануляет каждый байт нулями!\n"
    "   \n"
    "3. realloc(void *ptr, size_t new_size):\n"
    "   Изменяет размер ранее выделенного блока памяти.\n"
    "\n"
    "4. free(void *ptr):\n"
    "   Освобождает ранее выделенную память. После free указатель становится висячим (Dangling Pointer) — хорошим тоном является обнулить его: ptr = NULL;\n"
    "\n"
    "Смертные грехи C-программиста:\n"
    "- Утечка памяти (Memory Leak): забыли вызвать free(). Программа пожирает RAM до истощения системы.\n"
    "- Двойное освобождение (Double Free): дважды вызвали free(ptr) для одного блока памяти (краш кучи).\n"
    "- Разыменование после освобождения (Use-After-Free): чтение или запись по освобожденному адресу.";
        l.task = L"Выделите в куче динамический массив из 3 целых чисел с помощью malloc.\n"
    "Заполните его числами 100, 200, 300.\n"
    "Выведите сумму элементов: Sum: 600\n"
    "Не забудьте освободить память вызовом free().";
        l.initial_code = L"#include <stdio.h>\n"
    "#include <stdlib.h>\n"
    "\n"
    "int main(void) {\n"
    "    // 1. Выделите память на 3 элемента int\n"
    "    \n"
    "    // 2. Проверьте на NULL\n"
    "    \n"
    "    // 3. Заполните массив и посчитайте сумму\n"
    "    \n"
    "    // 4. Освободите память\n"
    "    \n"
    "    return 0;\n"
    "}\n"
    "";
        l.solution = L"#include <stdio.h>\n"
    "#include <stdlib.h>\n"
    "\n"
    "int main(void) {\n"
    "    int *arr = (int*)malloc(3 * sizeof(int));\n"
    "    if (arr == NULL) {\n"
    "        return 1;\n"
    "    }\n"
    "\n"
    "    arr[0] = 100;\n"
    "    arr[1] = 200;\n"
    "    arr[2] = 300;\n"
    "\n"
    "    int sum = arr[0] + arr[1] + arr[2];\n"
    "    printf(\"Sum: %d\\n\", sum);\n"
    "\n"
    "    free(arr);\n"
    "    arr = NULL;\n"
    "    return 0;\n"
    "}\n"
    "";
        l.expected_output = L"Sum: 600\n"
    "";
        l.hints.push_back(L"Выделите: int *arr = malloc(3 * sizeof(int));");
        l.hints.push_back(L"Проверьте if (arr == NULL)");
        l.hints.push_back(L"В конце обязательно вызовите free(arr);");
        list.push_back(l);
    }
    {
        Lesson l;
        l.id = 13;
        l.module_name = L"Модуль 4: Динамическая Память и Пользовательские Типы";
        l.title = L"Урок 13: Структуры (struct), typedef и выравнивание (Padding)";
        l.lang = L"C";
        l.difficulty = L"Средний";
        l.theory = L"Структура (struct) объединяет переменные разных типов под одним именем.\n"
    "\n"
    "Синтаксис:\n"
    "struct Point {\n"
    "    int x;\n"
    "    int y;\n"
    "};\n"
    "\n"
    "Использование typedef для сокращения записи:\n"
    "typedef struct {\n"
    "    char name[32];\n"
    "    int age;\n"
    "    float gpa;\n"
    "} Student;\n"
    "\n"
    "Доступ к полям:\n"
    "1. Через точку (.), если у нас сам объект:\n"
    "   Student s1;\n"
    "   s1.age = 20;\n"
    "\n"
    "2. Через стрелочку (->), если у нас УКАЗАТЕЛЬ на структуру:\n"
    "   Student *ptr = &s1;\n"
    "   ptr->age = 21; // Эквивалентно (*ptr).age = 21\n"
    "\n"
    "Выравнивание данных в памяти (Structure Padding):\n"
    "Процессоры x86/x64 читают память порциями по 4 или 8 байт (слова). Поэтому компилятор автоматически вставляет пустые байты (Padding) между полями структуры, чтобы они лежали по адресам, кратным своему размеру!\n"
    "Пример:\n"
    "struct Example {\n"
    "    char a; // 1 байт + 3 байта padding!\n"
    "    int b;  // 4 байта\n"
    "};\n"
    "Размер sizeof(struct Example) будет равен 8 байтам, а не 5!";
        l.task = L"Создайте структуру Vector2D с полями double x и double y.\n"
    "Напишите функцию:\n"
    "void scale(Vector2D *v, double factor)\n"
    "которая умножает поля x и y на factor через указатель.\n"
    "В main создайте вектор {3.0, 4.0}, масштабируйте его в 2 раза и выведите:\n"
    "Vector: (6.00, 8.00)";
        l.initial_code = L"#include <stdio.h>\n"
    "\n"
    "typedef struct {\n"
    "    double x;\n"
    "    double y;\n"
    "} Vector2D;\n"
    "\n"
    "void scale(Vector2D *v, double factor) {\n"
    "    // Реализуйте масштабирование через указатель:\n"
    "}\n"
    "\n"
    "int main(void) {\n"
    "    Vector2D vec = {3.0, 4.0};\n"
    "    scale(&vec, 2.0);\n"
    "    printf(\"Vector: (%.2f, %.2f)\\n\", vec.x, vec.y);\n"
    "    return 0;\n"
    "}\n"
    "";
        l.solution = L"#include <stdio.h>\n"
    "\n"
    "typedef struct {\n"
    "    double x;\n"
    "    double y;\n"
    "} Vector2D;\n"
    "\n"
    "void scale(Vector2D *v, double factor) {\n"
    "    v->x *= factor;\n"
    "    v->y *= factor;\n"
    "}\n"
    "\n"
    "int main(void) {\n"
    "    Vector2D vec = {3.0, 4.0};\n"
    "    scale(&vec, 2.0);\n"
    "    printf(\"Vector: (%.2f, %.2f)\\n\", vec.x, vec.y);\n"
    "    return 0;\n"
    "}\n"
    "";
        l.expected_output = L"Vector: (6.00, 8.00)\n"
    "";
        l.hints.push_back(L"Используйте оператор стрелки: v->x *= factor;");
        l.hints.push_back(L"v->y *= factor;");
        list.push_back(l);
    }
    {
        Lesson l;
        l.id = 14;
        l.module_name = L"Модуль 4: Динамическая Память и Пользовательские Типы";
        l.title = L"Урок 14: Файловый ввод-вывод и дескриптор FILE*";
        l.lang = L"C";
        l.difficulty = L"Средний";
        l.theory = L"Для работы с файлами стандартная библиотека Си предоставляет тип дескриптора FILE* (поток).\n"
    "\n"
    "Основные функции:\n"
    "- fopen(const char *filename, const char *mode):\n"
    "  Открывает файл. Режимы:\n"
    "  \"r\" — чтение\n"
    "  \"w\" — запись (создает новый или перезаписывает существующий)\n"
    "  \"a\" — добавление в конец (append)\n"
    "  \"rb\", \"wb\" — бинарный режим (критично для Windows!)\n"
    "  Если файл не удалось открыть, возвращает NULL.\n"
    "- fclose(FILE *stream): закрывает файл и сбрасывает буферы на диск.\n"
    "- fprintf(file, \"format\", ...): форматированная запись в файл.\n"
    "- fscanf(file, \"format\", ...): чтение из файла.\n"
    "- fgets(char *str, int n, FILE *stream): безопасное построчное чтение текста.\n"
    "- fwrite(buf, size, count, file): бинарная запись сырых байтов.\n"
    "- fread(buf, size, count, file): бинарное чтение сырых байтов.\n"
    "\n"
    "Стандартные потоки (уже открыты при старте программы):\n"
    "- stdin (клавиатура / ввод)\n"
    "- stdout (консоль / вывод)\n"
    "- stderr (поток ошибок, не буферизуется)";
        l.task = L"Используйте временный файл, чтобы записать в него строку \"TrainerCode_2000\", а затем прочитайте ее обратно и выведите в stdout:\n"
    "Loaded from file: TrainerCode_2000";
        l.initial_code = L"#include <stdio.h>\n"
    "\n"
    "int main(void) {\n"
    "    const char *fname = \"temp_lesson.txt\";\n"
    "    // 1. Откройте файл на запись (\"w\"), запишите строку с помощью fprintf, закройте.\n"
    "    \n"
    "    // 2. Откройте на чтение (\"r\"), прочитайте с помощью fgets или fscanf, выведите.\n"
    "    \n"
    "    return 0;\n"
    "}\n"
    "";
        l.solution = L"#include <stdio.h>\n"
    "\n"
    "int main(void) {\n"
    "    const char *fname = \"temp_lesson.txt\";\n"
    "    FILE *fout = fopen(fname, \"w\");\n"
    "    if (fout) {\n"
    "        fprintf(fout, \"TrainerCode_2000\\n\");\n"
    "        fclose(fout);\n"
    "    }\n"
    "\n"
    "    FILE *fin = fopen(fname, \"r\");\n"
    "    char buffer[64] = {0};\n"
    "    if (fin) {\n"
    "        if (fscanf(fin, \"%63s\", buffer) == 1) {\n"
    "            printf(\"Loaded from file: %s\\n\", buffer);\n"
    "        }\n"
    "        fclose(fin);\n"
    "    }\n"
    "    return 0;\n"
    "}\n"
    "";
        l.expected_output = L"Loaded from file: TrainerCode_2000\n"
    "";
        l.hints.push_back(L"Всегда проверяйте результат fopen на равенство NULL.");
        l.hints.push_back(L"Не забывайте вызывать fclose для закрытия файла.");
        list.push_back(l);
    }
    {
        Lesson l;
        l.id = 15;
        l.module_name = L"Модуль 5: Переход к C++ и Основы ООП";
        l.title = L"Урок 15: Переход к C++: потоки cin/cout, ссылки & и перегрузка";
        l.lang = L"C++";
        l.difficulty = L"Новичок";
        l.theory = L"Язык C++ был разработан Бьёрном Страуструпом как 'Си с классами'. C++ обратно совместим с большинством конструкций Си, но вводит мощнейшие высокоуровневые абстракции с нулевой стоимостью (Zero-Cost Abstractions).\n"
    "\n"
    "1. Потоки ввода-вывода <iostream>:\n"
    "Вместо printf и scanf в C++ используются типизированные потоки std::cout (вывод) и std::cin (ввод):\n"
    "#include <iostream>\n"
    "std::cout << \"Hello C++!\" << std::endl;\n"
    "\n"
    "2. Ссылки (References) vs Указатели:\n"
    "Ссылка — это псевдоним (alias) уже существующей переменной.\n"
    "В отличие от указателя:\n"
    "- Ссылку НЕЛЬЗЯ сделать NULL (она всегда ссылается на реальный объект).\n"
    "- Ссылку нельзя перепривязать к другой переменной после инициализации.\n"
    "- Доступ осуществляется без разыменования (*):\n"
    "  void increment(int &val) {\n"
    "      val++; // изменяет оригинальную переменную напрямую!\n"
    "  }\n"
    "\n"
    "3. Перегрузка функций (Function Overloading):\n"
    "В C++ функции могут иметь одинаковое имя, если у них разные типы или количество параметров! Компилятор выполняет Name Mangling и выбирает нужную версию.\n"
    "\n"
    "4. nullptr:\n"
    "В C++11 вместо макроса NULL (который был числом 0) введен строго типизированный nullptr типа std::nullptr_t.";
        l.task = L"Напишите две перегруженные функции printDouble:\n"
    "void printDouble(int x) -> печатает удвоенный int: \"Double int: \" << x * 2\n"
    "void printDouble(double x) -> печатает удвоенный double: \"Double double: \" << x * 2.0\n"
    "В main вызовите printDouble(21) и printDouble(3.5):\n"
    "Double int: 42\n"
    "Double double: 7";
        l.initial_code = L"#include <iostream>\n"
    "\n"
    "// Напишите перегруженные функции printDouble:\n"
    "\n"
    "int main() {\n"
    "    printDouble(21);\n"
    "    printDouble(3.5);\n"
    "    return 0;\n"
    "}\n"
    "";
        l.solution = L"#include <iostream>\n"
    "\n"
    "void printDouble(int x) {\n"
    "    std::cout << \"Double int: \" << x * 2 << std::endl;\n"
    "}\n"
    "\n"
    "void printDouble(double x) {\n"
    "    std::cout << \"Double double: \" << x * 2.0 << std::endl;\n"
    "}\n"
    "\n"
    "int main() {\n"
    "    printDouble(21);\n"
    "    printDouble(3.5);\n"
    "    return 0;\n"
    "}\n"
    "";
        l.expected_output = L"Double int: 42\n"
    "Double double: 7\n"
    "";
        l.hints.push_back(L"Объявите одну функцию с параметром (int x), а вторую с (double x).");
        l.hints.push_back(L"Используйте std::cout << ... << std::endl;");
        list.push_back(l);
    }
    {
        Lesson l;
        l.id = 16;
        l.module_name = L"Модуль 5: Переход к C++ и Основы ООП";
        l.title = L"Урок 16: Классы, Инкапсуляция, Конструкторы и Деструкторы";
        l.lang = L"C++";
        l.difficulty = L"Средний";
        l.theory = L"Класс в C++ — это пользовательский тип, объединяющий данные (поля) и функции для работы с ними (методы).\n"
    "\n"
    "Спецификаторы доступа (Инкапсуляция):\n"
    "- private: поля и методы доступны только внутри самого класса (скрытая реализация).\n"
    "- public: интерфейс, доступный снаружи.\n"
    "- protected: доступно внутри класса и его классов-наследников.\n"
    "\n"
    "Жизненный цикл объекта:\n"
    "1. Конструктор (Constructor):\n"
    "   Вызывается автоматически в момент создания объекта в памяти. Имеет то же имя, что и класс, не возвращает значение.\n"
    "   Список инициализации (Member Initializer List) — предпочтительный способ инициализации полей:\n"
    "   Player(std::string name, int hp) : name_(name), hp_(hp) {}\n"
    "\n"
    "2. Деструктор (Destructor):\n"
    "   Вызывается автоматически, когда объект уничтожается (выходит из области видимости { } или при delete). Начинается с тильды (~):\n"
    "   ~Player() {\n"
    "       // освобождение ресурсов\n"
    "   }\n"
    "\n"
    "Ключевое слово this:\n"
    "Указатель this хранит адрес текущего экземпляра класса внутри его нестатических методов.";
        l.task = L"Создайте класс Hero с private полями std::string name_ и int health_.\n"
    "Сделайте public конструктор с параметрами Hero(std::string name, int health).\n"
    "Сделайте public метод void takeDamage(int amount), уменьшающий здоровье, и метод int getHealth() const.\n"
    "В main создайте героя с именем \"Knight\" и 100 HP, нанесите 35 урона и выведите:\n"
    "Knight HP: 65";
        l.initial_code = L"#include <iostream>\n"
    "#include <string>\n"
    "\n"
    "class Hero {\n"
    "    // Реализуйте поля и методы класса Hero:\n"
    "};\n"
    "\n"
    "int main() {\n"
    "    Hero hero(\"Knight\", 100);\n"
    "    hero.takeDamage(35);\n"
    "    std::cout << \"Knight HP: \" << hero.getHealth() << std::endl;\n"
    "    return 0;\n"
    "}\n"
    "";
        l.solution = L"#include <iostream>\n"
    "#include <string>\n"
    "\n"
    "class Hero {\n"
    "private:\n"
    "    std::string name_;\n"
    "    int health_;\n"
    "\n"
    "public:\n"
    "    Hero(std::string name, int health) : name_(name), health_(health) {}\n"
    "\n"
    "    void takeDamage(int amount) {\n"
    "        health_ -= amount;\n"
    "        if (health_ < 0) health_ = 0;\n"
    "    }\n"
    "\n"
    "    int getHealth() const {\n"
    "        return health_;\n"
    "    }\n"
    "};\n"
    "\n"
    "int main() {\n"
    "    Hero hero(\"Knight\", 100);\n"
    "    hero.takeDamage(35);\n"
    "    std::cout << \"Knight HP: \" << hero.getHealth() << std::endl;\n"
    "    return 0;\n"
    "}\n"
    "";
        l.expected_output = L"Knight HP: 65\n"
    "";
        l.hints.push_back(L"Используйте список инициализации: Hero(std::string name, int health) : name_(name), health_(health) {}");
        l.hints.push_back(L"Не забудьте спецификатор public: перед методами.");
        list.push_back(l);
    }
    {
        Lesson l;
        l.id = 17;
        l.module_name = L"Модуль 5: Переход к C++ и Основы ООП";
        l.title = L"Урок 17: Наследование, Полиморфизм и Таблица vtable";
        l.lang = L"C++";
        l.difficulty = L"Продвинутый";
        l.theory = L"Полиморфизм — это способность обрабатывать объекты разных классов через общий базовый интерфейс во время выполнения.\n"
    "\n"
    "Ключевое слово virtual:\n"
    "Если метод базового класса помечен как virtual, вызов через указатель или ссылку на базовый класс будет вызывать ПЕРЕОПРЕДЕЛЕННУЮ реализацию наследника!\n"
    "class Shape {\n"
    "public:\n"
    "    virtual void draw() const { std::cout << \"Shape\"; }\n"
    "    virtual ~Shape() {} // Деструктор базового класса ОБЯЗАН быть виртуальным!\n"
    "};\n"
    "\n"
    "class Circle : public Shape {\n"
    "public:\n"
    "    void draw() const override { std::cout << \"Circle\"; }\n"
    "};\n"
    "\n"
    "Как устроен полиморфизм 'под капотом' (vtable):\n"
    "При компиляции для каждого класса с виртуальными методами компилятор генерирует статическую массив указателей на функции — Таблицу виртуальных функций (Virtual Method Table / vtable).\n"
    "В каждый объект такого класса скрыто добавляется 8-байтный указатель __vptr, указывающий на vtable его класса. При вызове shape->draw() процессор читает адрес из vtable и делает косвенный переход (call [rax+offset]).\n"
    "\n"
    "Чисто виртуальные функции и абстрактные классы:\n"
    "virtual void draw() const = 0; // Чисто виртуальный метод\n"
    "Класс, содержащий хотя бы один чисто виртуальный метод, называется абстрактным (нельзя создать объект напрямую).";
        l.task = L"Создайте базовый абстрактный класс Device с чисто виртуальным методом virtual void powerOn() = 0 и виртуальным деструктором.\n"
    "Создайте класс-наследник Laptop, переопределяющий powerOn() с выводом \"Laptop is booting...\"\n"
    "В main создайте Laptop через указатель на Device* и вызовите powerOn():\n"
    "Laptop is booting...";
        l.initial_code = L"#include <iostream>\n"
    "\n"
    "// 1. Создайте абстрактный класс Device:\n"
    "\n"
    "// 2. Создайте класс Laptop : public Device:\n"
    "\n"
    "int main() {\n"
    "    Device *d = new Laptop();\n"
    "    d->powerOn();\n"
    "    delete d;\n"
    "    return 0;\n"
    "}\n"
    "";
        l.solution = L"#include <iostream>\n"
    "\n"
    "class Device {\n"
    "public:\n"
    "    virtual ~Device() {}\n"
    "    virtual void powerOn() = 0;\n"
    "};\n"
    "\n"
    "class Laptop : public Device {\n"
    "public:\n"
    "    void powerOn() override {\n"
    "        std::cout << \"Laptop is booting...\" << std::endl;\n"
    "    }\n"
    "};\n"
    "\n"
    "int main() {\n"
    "    Device *d = new Laptop();\n"
    "    d->powerOn();\n"
    "    delete d;\n"
    "    return 0;\n"
    "}\n"
    "";
        l.expected_output = L"Laptop is booting...\n"
    "";
        l.hints.push_back(L"virtual void powerOn() = 0; объявляет чисто виртуальный метод.");
        l.hints.push_back(L"Используйте override в производном классе Laptop.");
        l.hints.push_back(L"Всегда объявляйте virtual ~Device() {}");
        list.push_back(l);
    }
    {
        Lesson l;
        l.id = 18;
        l.module_name = L"Модуль 6: Modern C++ и STL";
        l.title = L"Урок 18: Управление ресурсами: RAII и Семантика перемещения";
        l.lang = L"C++";
        l.difficulty = L"Продвинутый";
        l.theory = L"RAII (Resource Acquisition Is Initialization — Захват ресурса есть инициализация) — краеугольный камень Modern C++!\n"
    "Идея: Любой ресурс (динамическая память, файловый дескриптор, мьютекс, сетевой сокет) захватывается в конструкторе объекта и гарантированно освобождается в деструкторе, когда объект покидает область видимости (scope). Это гарантирует отсутствие утечек даже при возникновении исключений!\n"
    "\n"
    "Семантика перемещения (Move Semantics, C++11):\n"
    "До C++11 при возврате больших объектов (например, строк или векторов) происходило дорогое глубокое копирование миллионов байтов.\n"
    "C++11 ввел rvalue-ссылки (обозначаются как &&):\n"
    "- lvalue: объект, у которого есть имя и адрес в памяти (например, int x).\n"
    "- rvalue: временное значение без имени (например, x + 5, или временный объект в return).\n"
    "\n"
    "std::move(obj):\n"
    "Не перемещает ничего сам по себе! Он выполняет static_cast к rvalue-ссылке (T&&), сигнализируя компилятору: 'У этого объекта можно отобрать его внутренний буфер (указатель), оставив его в пустом валидном состоянии!'. Это операция O(1) вместо копирования O(N).";
        l.task = L"Изучите работу std::move со строками:\n"
    "std::string original = \"Valuable Data\";\n"
    "std::string moved = std::move(original);\n"
    "Выведите:\n"
    "Moved: Valuable Data\n"
    "Original empty: 1 (проверьте original.empty())";
        l.initial_code = L"#include <iostream>\n"
    "#include <string>\n"
    "#include <utility>\n"
    "\n"
    "int main() {\n"
    "    std::string original = \"Valuable Data\";\n"
    "    // Переместите original в moved с помощью std::move:\n"
    "    \n"
    "    std::cout << \"Moved: \" << moved << std::endl;\n"
    "    std::cout << \"Original empty: \" << original.empty() << std::endl;\n"
    "    return 0;\n"
    "}\n"
    "";
        l.solution = L"#include <iostream>\n"
    "#include <string>\n"
    "#include <utility>\n"
    "\n"
    "int main() {\n"
    "    std::string original = \"Valuable Data\";\n"
    "    std::string moved = std::move(original);\n"
    "\n"
    "    std::cout << \"Moved: \" << moved << std::endl;\n"
    "    std::cout << \"Original empty: \" << original.empty() << std::endl;\n"
    "    return 0;\n"
    "}\n"
    "";
        l.expected_output = L"Moved: Valuable Data\n"
    "Original empty: 1\n"
    "";
        l.hints.push_back(L"Используйте std::string moved = std::move(original);");
        l.hints.push_back(L"После перемещения буфер строки перешел в moved, а original опустел.");
        list.push_back(l);
    }
    {
        Lesson l;
        l.id = 19;
        l.module_name = L"Модуль 6: Modern C++ и STL";
        l.title = L"Урок 19: Умные указатели: std::unique_ptr и std::shared_ptr";
        l.lang = L"C++";
        l.difficulty = L"Продвинутый";
        l.theory = L"В современном C++ сырые указатели (raw pointers) со словами new и delete использовать категорически не рекомендуется! Вместо них используются умные указатели из заголовка <memory>.\n"
    "\n"
    "1. std::unique_ptr:\n"
    "- Владеет объектом единолично (Exclusive Ownership).\n"
    "- Нулевые накладные расходы по памяти и скорости (ровно размер одного сырого указателя).\n"
    "- Нельзя скопировать (copy constructor удален), можно только перемещать (std::move)!\n"
    "- Создается через std::make_unique<T>(args...):\n"
    "  auto ptr = std::make_unique<MyClass>(42);\n"
    "\n"
    "2. std::shared_ptr:\n"
    "- Разделяемое владение (Shared Ownership).\n"
    "- Содержит счетчик ссылок (Reference Counter) в отдельном блоке управления (Control Block).\n"
    "- Когда счетчик ссылок достигает 0, объект автоматически уничтожается.\n"
    "- Создается через std::make_shared<T>(args...).\n"
    "\n"
    "3. std::weak_ptr:\n"
    "- 'Слабый' указатель, не увеличивающий счетчик ссылок shared_ptr.\n"
    "- Предотвращает циклические ссылки (когда объект A держит shared_ptr на B, а B держит на A — они никогда не удалились бы!).";
        l.task = L"Используйте std::unique_ptr для выделения объекта int со значением 777 с помощью std::make_unique.\n"
    "Выведите значение через разыменование *ptr:\n"
    "Value: 777";
        l.initial_code = L"#include <iostream>\n"
    "#include <memory>\n"
    "\n"
    "int main() {\n"
    "    // Создайте unique_ptr на int со значением 777:\n"
    "    \n"
    "    // Выведите *ptr:\n"
    "    \n"
    "    return 0;\n"
    "}\n"
    "";
        l.solution = L"#include <iostream>\n"
    "#include <memory>\n"
    "\n"
    "int main() {\n"
    "    std::unique_ptr<int> ptr = std::make_unique<int>(777);\n"
    "    std::cout << \"Value: \" << *ptr << std::endl;\n"
    "    return 0;\n"
    "}\n"
    "";
        l.expected_output = L"Value: 777\n"
    "";
        l.hints.push_back(L"Используйте auto ptr = std::make_unique<int>(777);");
        l.hints.push_back(L"Разыменуйте: *ptr.");
        list.push_back(l);
    }
    {
        Lesson l;
        l.id = 20;
        l.module_name = L"Модуль 6: Modern C++ и STL";
        l.title = L"Урок 20: Шаблоны (Templates) и обобщенное программирование";
        l.lang = L"C++";
        l.difficulty = L"Продвинутый";
        l.theory = L"Шаблоны (Templates) позволяют писать код, не привязанный к конкретному типу данных. Компилятор сам генерирует нужную реализацию во время сборки для каждого типа (инстанцирование шаблона).\n"
    "\n"
    "1. Шаблоны функций:\n"
    "template <typename T>\n"
    "T getMin(T a, T b) {\n"
    "    return (a < b) ? a : b;\n"
    "}\n"
    "Вызов:\n"
    "getMin<int>(5, 10); // вернет 5\n"
    "getMin(3.14, 2.71); // компилятор автоматически выведет тип double!\n"
    "\n"
    "2. Шаблоны классов:\n"
    "template <typename T>\n"
    "class Stack {\n"
    "    std::vector<T> elements;\n"
    "public:\n"
    "    void push(const T &item) { elements.push_back(item); }\n"
    "    T pop() { ... }\n"
    "};\n"
    "\n"
    "3. constexpr (C++11/14/17):\n"
    "Ключевое слово constexpr сообщает, что функция или переменная может быть вычислена прямо во время компиляции программы, до ее запуска!";
        l.task = L"Напишите шаблонную функцию template <typename T> T clamp(T val, T low, T high), которая ограничивает значение val диапазоном [low, high].\n"
    "Проверьте ее работу для clamp(15, 0, 10) и clamp(-5, 0, 10):\n"
    "Clamped: 10\n"
    "Clamped: 0";
        l.initial_code = L"#include <iostream>\n"
    "\n"
    "// Напишите шаблон функции clamp:\n"
    "\n"
    "int main() {\n"
    "    std::cout << \"Clamped: \" << clamp(15, 0, 10) << std::endl;\n"
    "    std::cout << \"Clamped: \" << clamp(-5, 0, 10) << std::endl;\n"
    "    return 0;\n"
    "}\n"
    "";
        l.solution = L"#include <iostream>\n"
    "\n"
    "template <typename T>\n"
    "T clamp(T val, T low, T high) {\n"
    "    if (val < low) return low;\n"
    "    if (val > high) return high;\n"
    "    return val;\n"
    "}\n"
    "\n"
    "int main() {\n"
    "    std::cout << \"Clamped: \" << clamp(15, 0, 10) << std::endl;\n"
    "    std::cout << \"Clamped: \" << clamp(-5, 0, 10) << std::endl;\n"
    "    return 0;\n"
    "}\n"
    "";
        l.expected_output = L"Clamped: 10\n"
    "Clamped: 0\n"
    "";
        l.hints.push_back(L"Синтаксис: template <typename T> T clamp(T val, T low, T high)");
        l.hints.push_back(L"Если val < low верните low, если val > high верните high, иначе val.");
        list.push_back(l);
    }
    {
        Lesson l;
        l.id = 21;
        l.module_name = L"Модуль 6: Modern C++ и STL";
        l.title = L"Урок 21: Контейнеры STL: std::vector, std::map и std::unordered_map";
        l.lang = L"C++";
        l.difficulty = L"Средний";
        l.theory = L"Стандартная библиотека шаблонов (STL) предоставляет готовые, высокооптимизированные структуры данных:\n"
    "\n"
    "1. std::vector<T>:\n"
    "- Динамический массив непрерывной памяти.\n"
    "- Быстрый произвольный доступ по индексу: O(1).\n"
    "- Вставка в конец: амортизированное O(1).\n"
    "- Методы: push_back, emplace_back, size, empty, clear, capacity, reserve.\n"
    "\n"
    "2. std::map<Key, Value>:\n"
    "- Ассоциативный массив, упорядоченный по ключам.\n"
    "- Внутри реализован как самобалансирующееся Красно-Черное дерево (Red-Black Tree).\n"
    "- Поиск, вставка и удаление: O(log N).\n"
    "\n"
    "3. std::unordered_map<Key, Value>:\n"
    "- Хеш-таблица. Ключи не упорядочены.\n"
    "- Поиск в среднем за константное время: O(1)!\n"
    "\n"
    "Сравнение асимптотики:\n"
    "Контейнер       | Поиск    | Вставка в конец | Память\n"
    "std::vector     | O(N)     | O(1)            | Минимальная непрерывная\n"
    "std::map        | O(log N) | O(log N)        | Узлы дерева + указатели\n"
    "std::unordered_map | O(1)  | O(1)            | Таблица бакетов";
        l.task = L"Создайте std::vector<int> v = {5, 2, 8, 1, 9};\n"
    "Добавьте в конец число 42 с помощью push_back.\n"
    "Отсортируйте вектор по возрастанию с помощью std::sort из <algorithm>.\n"
    "Выведите отсортированные элементы через пробел:\n"
    "1 2 5 8 9 42";
        l.initial_code = L"#include <iostream>\n"
    "#include <vector>\n"
    "#include <algorithm>\n"
    "\n"
    "int main() {\n"
    "    std::vector<int> v = {5, 2, 8, 1, 9};\n"
    "    // 1. Добавьте 42 в конец вектора\n"
    "    \n"
    "    // 2. Отсортируйте вектор std::sort\n"
    "    \n"
    "    // 3. Выведите элементы через пробел:\n"
    "    \n"
    "    std::cout << std::endl;\n"
    "    return 0;\n"
    "}\n"
    "";
        l.solution = L"#include <iostream>\n"
    "#include <vector>\n"
    "#include <algorithm>\n"
    "\n"
    "int main() {\n"
    "    std::vector<int> v = {5, 2, 8, 1, 9};\n"
    "    v.push_back(42);\n"
    "    std::sort(v.begin(), v.end());\n"
    "\n"
    "    for (size_t i = 0; i < v.size(); i++) {\n"
    "        if (i > 0) std::cout << \" \";\n"
    "        std::cout << v[i];\n"
    "    }\n"
    "    std::cout << std::endl;\n"
    "    return 0;\n"
    "}\n"
    "";
        l.expected_output = L"1 2 5 8 9 42\n"
    "";
        l.hints.push_back(L"v.push_back(42);");
        l.hints.push_back(L"std::sort(v.begin(), v.end());");
        l.hints.push_back(L"Используйте цикл по вектору для вывода.");
        list.push_back(l);
    }
    {
        Lesson l;
        l.id = 22;
        l.module_name = L"Модуль 6: Modern C++ и STL";
        l.title = L"Урок 22: Лямбда-выражения и алгоритмы STL";
        l.lang = L"C++";
        l.difficulty = L"Продвинутый";
        l.theory = L"Лямбда-выражение (Lambda) — это анонимная функция, которую можно определить прямо по месту вызова.\n"
    "\n"
    "Синтаксис лямбды в C++:\n"
    "[захват](параметры) -> возвращаемый_тип { тело }\n"
    "\n"
    "Список захвата (Capture List):\n"
    "[] — ничего не захватывать из внешней области видимости.\n"
    "[&] — захватить все внешние переменные по ссылке.\n"
    "[=] — захватить все внешние переменные по значению (копии).\n"
    "[x, &y] — x по значению, y по ссылке.\n"
    "\n"
    "Использование с алгоритмами <algorithm>:\n"
    "- std::count_if(begin, end, predicate): подсчитывает элементы, удовлетворяющие условию.\n"
    "- std::for_each(begin, end, function): применяет функцию к каждому элементу.\n"
    "- std::transform: преобразует элементы из одного диапазона в другой.\n"
    "- std::all_of / std::any_of / std::none_of: проверка условий на диапазоне.";
        l.task = L"Дан вектор std::vector<int> nums = {10, -5, 20, 0, -15, 30};\n"
    "Используйте std::count_if и лямбда-выражение, чтобы посчитать количество положительных чисел (> 0).\n"
    "Выведите:\n"
    "Positive count: 3";
        l.initial_code = L"#include <iostream>\n"
    "#include <vector>\n"
    "#include <algorithm>\n"
    "\n"
    "int main() {\n"
    "    std::vector<int> nums = {10, -5, 20, 0, -15, 30};\n"
    "    \n"
    "    // Подсчитайте количество чисел > 0 с помощью std::count_if и лямбды:\n"
    "    int count = 0;\n"
    "    \n"
    "    std::cout << \"Positive count: \" << count << std::endl;\n"
    "    return 0;\n"
    "}\n"
    "";
        l.solution = L"#include <iostream>\n"
    "#include <vector>\n"
    "#include <algorithm>\n"
    "\n"
    "int main() {\n"
    "    std::vector<int> nums = {10, -5, 20, 0, -15, 30};\n"
    "    int count = std::count_if(nums.begin(), nums.end(), [](int n) {\n"
    "        return n > 0;\n"
    "    });\n"
    "\n"
    "    std::cout << \"Positive count: \" << count << std::endl;\n"
    "    return 0;\n"
    "}\n"
    "";
        l.expected_output = L"Positive count: 3\n"
    "";
        l.hints.push_back(L"Лямбда: [](int n) { return n > 0; }");
        l.hints.push_back(L"count = std::count_if(nums.begin(), nums.end(), ...);");
        list.push_back(l);
    }
    {
        Lesson l;
        l.id = 23;
        l.module_name = L"Модуль 6: Modern C++ и STL";
        l.title = L"Урок 23: Обработка исключений (try, catch, throw)";
        l.lang = L"C++";
        l.difficulty = L"Средний";
        l.theory = L"Исключения (Exceptions) — механизм сообщений об ошибках во время выполнения программы без использования кодов возврата.\n"
    "\n"
    "Синтаксис:\n"
    "try {\n"
    "    // Код, который может сгенерировать исключение\n"
    "    if (divisor == 0) {\n"
    "        throw std::runtime_error(\"Division by zero!\");\n"
    "    }\n"
    "} catch (const std::runtime_error &e) {\n"
    "    // Обработка конкретного типа ошибки\n"
    "    std::cout << \"Error: \" << e.what() << std::endl;\n"
    "} catch (const std::exception &e) {\n"
    "    // Обработка любых стандартных исключений\n"
    "} catch (...) {\n"
    "    // Перехват абсолютно любого необработанного исключения\n"
    "}\n"
    "\n"
    "Раскрутка стека (Stack Unwinding):\n"
    "Когда выбрасывается исключение, среда выполнения C++ начинает раскручивать стек вверх до ближайшего подходящего блока catch.\n"
    "В процессе раскрутки стека для ВСЕХ локальных объектов на пройденных стековых фреймах вызываются их деструкторы! Благодаря RAII это гарантирует, что память и ресурсы не утекут даже при критическом сбое!\n"
    "\n"
    "noexcept:\n"
    "Ключевое слово noexcept указывает компилятору, что функция гарантированно не выбрасывает исключений (позволяет компилятору генерировать более быстрый машинный код).";
        l.task = L"Напишите функцию double safeDivide(double a, double b), которая выбрасывает std::invalid_argument(\"Zero division\"), если b == 0.\n"
    "В main вызовите safeDivide(10, 0) внутри блока try-catch и напечатайте:\n"
    "Caught exception: Zero division";
        l.initial_code = L"#include <iostream>\n"
    "#include <stdexcept>\n"
    "\n"
    "double safeDivide(double a, double b) {\n"
    "    // Выбросьте std::invalid_argument если b == 0:\n"
    "    return a / b;\n"
    "}\n"
    "\n"
    "int main() {\n"
    "    try {\n"
    "        safeDivide(10.0, 0.0);\n"
    "    } catch (const std::invalid_argument &e) {\n"
    "        std::cout << \"Caught exception: \" << e.what() << std::endl;\n"
    "    }\n"
    "    return 0;\n"
    "}\n"
    "";
        l.solution = L"#include <iostream>\n"
    "#include <stdexcept>\n"
    "\n"
    "double safeDivide(double a, double b) {\n"
    "    if (b == 0.0) {\n"
    "        throw std::invalid_argument(\"Zero division\");\n"
    "    }\n"
    "    return a / b;\n"
    "}\n"
    "\n"
    "int main() {\n"
    "    try {\n"
    "        safeDivide(10.0, 0.0);\n"
    "    } catch (const std::invalid_argument &e) {\n"
    "        std::cout << \"Caught exception: \" << e.what() << std::endl;\n"
    "    }\n"
    "    return 0;\n"
    "}\n"
    "";
        l.expected_output = L"Caught exception: Zero division\n"
    "";
        l.hints.push_back(L"if (b == 0.0) throw std::invalid_argument(\"Zero division\");");
        l.hints.push_back(L"Метод e.what() возвращает текст переданной ошибки.");
        list.push_back(l);
    }
    {
        Lesson l;
        l.id = 24;
        l.module_name = L"Модуль 6: Modern C++ и STL";
        l.title = L"Урок 24: Многопоточность: std::thread, std::mutex и race conditions";
        l.lang = L"C++";
        l.difficulty = L"Эксперт";
        l.theory = L"Современные процессоры содержат десятки физических ядер. Заголовок <thread> в C++11 принес стандартную кроссплатформенную модель работы с потоками.\n"
    "\n"
    "Создание потока:\n"
    "std::thread t(function_name, arg1, arg2);\n"
    "t.join(); // Ждем завершения работы потока!\n"
    "Если объект потока t будет уничтожен без вызова t.join() или t.detach(), среда C++ немедленно вызовет std::terminate() и аварийно завершит программу!\n"
    "\n"
    "Состояние гонки (Race Condition) и Мьютексы (Mutex):\n"
    "Если два потока одновременно читают и записывают одну и ту же переменную памяти без синхронизации, возникает Неопределенное Поведение (Undefined Behavior).\n"
    "Для защиты критических секций используется std::mutex:\n"
    "std::mutex mtx;\n"
    "mtx.lock();\n"
    "// критическая секция\n"
    "mtx.unlock();\n"
    "\n"
    "RAII-обертка std::lock_guard:\n"
    "Вместо ручного вызова lock/unlock (где можно забыть unlock при исключении):\n"
    "{\n"
    "    std::lock_guard<std::mutex> lock(mtx); // захватывает мьютекс\n"
    "    // мьютекс автоматически освободится при выходе из скобок!\n"
    "}\n"
    "\n"
    "Атомики std::atomic:\n"
    "Для простых счетчиков и флагов заголовок <atomic> предоставляет lock-free атомарные типы:\n"
    "std::atomic<int> counter(0);\n"
    "counter++; // атомарная инструкция процессора (LOCK XADD на x86)!";
        l.task = L"Изучите работу std::atomic<int>.\n"
    "Создайте std::atomic<int> counter(0);\n"
    "Выполните инкремент counter++ 5 раз.\n"
    "Выведите значение счетчика:\n"
    "Atomic counter: 5";
        l.initial_code = L"#include <iostream>\n"
    "#include <atomic>\n"
    "\n"
    "int main() {\n"
    "    std::atomic<int> counter(0);\n"
    "    // Выполните 5 инкрементов:\n"
    "    \n"
    "    std::cout << \"Atomic counter: \" << counter.load() << std::endl;\n"
    "    return 0;\n"
    "}\n"
    "";
        l.solution = L"#include <iostream>\n"
    "#include <atomic>\n"
    "\n"
    "int main() {\n"
    "    std::atomic<int> counter(0);\n"
    "    for (int i = 0; i < 5; i++) {\n"
    "        counter++;\n"
    "    }\n"
    "\n"
    "    std::cout << \"Atomic counter: \" << counter.load() << std::endl;\n"
    "    return 0;\n"
    "}\n"
    "";
        l.expected_output = L"Atomic counter: 5\n"
    "";
        l.hints.push_back(L"Используйте цикл for от 0 до 5 и counter++;");
        l.hints.push_back(L"counter.load() читает значение атомарно.");
        list.push_back(l);
    }
    {
        Lesson l;
        l.id = 25;
        l.module_name = L"Модуль 6: Modern C++ и STL";
        l.title = L"Урок 25: Финальный курсовой проект: Реализация кастомного Vector";
        l.lang = L"C++";
        l.difficulty = L"Эксперт";
        l.theory = L"Поздравляем! Вы добрались до выпускного испытания.\n"
    "Настоящее мастерство программиста на C/C++ проверяется умением реализовать фундаментальные структуры данных с нуля, без помощи STL.\n"
    "\n"
    "Архитектура динамического массива (Custom Vector):\n"
    "1. Три ключевых поля:\n"
    "   - T *data_: указатель на непрерывную область памяти в куче.\n"
    "   - size_t size_: текущее количество реально хранящихся элементов.\n"
    "   - size_t capacity_: максимальная вместимость выделенного буфера.\n"
    "2. Стратегия реаллокации (Geometric Expansion):\n"
    "   Когда size_ == capacity_, мы выделяем новый буфер ВДВОЕ большего размера (new_cap = capacity_ * 2), перемещаем старые элементы и освобождаем старый буфер. Это дает амортизированную стоимость вставки O(1)!\n"
    "3. Деструктор:\n"
    "   Обязан освобождать delete[] data_.\n"
    "4. Правило пяти (Rule of 5):\n"
    "   Поскольку класс владеет сырым ресурсом памяти, необходимо явно реализовать или запретить копирование, чтобы избежать Double Free!";
        l.task = L"Реализуйте упрощенный класс SimpleVector:\n"
    "- конструктор по умолчанию (size_ = 0, capacity_ = 2, data_ = new int[2])\n"
    "- деструктор delete[] data_\n"
    "- метод void push_back(int val) с автоматическим удвоением capacity при заполнении\n"
    "- метод int at(size_t index) const\n"
    "В main добавьте числа 10, 20, 30 и выведите:\n"
    "Vector size: 3, at(2) = 30";
        l.initial_code = L"#include <iostream>\n"
    "\n"
    "class SimpleVector {\n"
    "private:\n"
    "    int *data_;\n"
    "    size_t size_;\n"
    "    size_t capacity_;\n"
    "\n"
    "public:\n"
    "    SimpleVector() : size_(0), capacity_(2), data_(new int[2]) {}\n"
    "    ~SimpleVector() { delete[] data_; }\n"
    "\n"
    "    void push_back(int val) {\n"
    "        // Если size_ == capacity_, увеличьте capacity в 2 раза,\n"
    "        // выделите новый массив, скопируйте данные, удалите старый.\n"
    "        // Затем добавьте val и увеличьте size_.\n"
    "    }\n"
    "\n"
    "    int at(size_t index) const {\n"
    "        return data_[index];\n"
    "    }\n"
    "\n"
    "    size_t size() const { return size_; }\n"
    "};\n"
    "\n"
    "int main() {\n"
    "    SimpleVector v;\n"
    "    v.push_back(10);\n"
    "    v.push_back(20);\n"
    "    v.push_back(30);\n"
    "\n"
    "    std::cout << \"Vector size: \" << v.size() << \", at(2) = \" << v.at(2) << std::endl;\n"
    "    return 0;\n"
    "}\n"
    "";
        l.solution = L"#include <iostream>\n"
    "\n"
    "class SimpleVector {\n"
    "private:\n"
    "    int *data_;\n"
    "    size_t size_;\n"
    "    size_t capacity_;\n"
    "\n"
    "public:\n"
    "    SimpleVector() : size_(0), capacity_(2), data_(new int[2]) {}\n"
    "    ~SimpleVector() { delete[] data_; }\n"
    "\n"
    "    void push_back(int val) {\n"
    "        if (size_ == capacity_) {\n"
    "            size_t new_cap = capacity_ * 2;\n"
    "            int *new_data = new int[new_cap];\n"
    "            for (size_t i = 0; i < size_; i++) {\n"
    "                new_data[i] = data_[i];\n"
    "            }\n"
    "            delete[] data_;\n"
    "            data_ = new_data;\n"
    "            capacity_ = new_cap;\n"
    "        }\n"
    "        data_[size_++] = val;\n"
    "    }\n"
    "\n"
    "    int at(size_t index) const {\n"
    "        return data_[index];\n"
    "    }\n"
    "\n"
    "    size_t size() const { return size_; }\n"
    "};\n"
    "\n"
    "int main() {\n"
    "    SimpleVector v;\n"
    "    v.push_back(10);\n"
    "    v.push_back(20);\n"
    "    v.push_back(30);\n"
    "\n"
    "    std::cout << \"Vector size: \" << v.size() << \", at(2) = \" << v.at(2) << std::endl;\n"
    "    return 0;\n"
    "}\n"
    "";
        l.expected_output = L"Vector size: 3, at(2) = 30\n"
    "";
        l.hints.push_back(L"При size_ == capacity_ выделите new int[capacity_ * 2];");
        l.hints.push_back(L"Скопируйте старые элементы, вызовите delete[] data_; и обновите указатель.");
        l.hints.push_back(L"data_[size_++] = val;");
        list.push_back(l);
    }
    return list;
}
