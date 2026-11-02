# -*- coding: utf-8 -*-
import json
import os

lessons = [
    {
        "id": 1,
        "module": "Модуль 1: Фундамент языка C и архитектура",
        "title": "Урок 1: Архитектура ЭВМ и первая программа Hello World",
        "lang": "C",
        "difficulty": "Новичок",
        "theory": """Добро пожаловать в мир системного программирования!

Язык C (Си) был создан Деннисом Ритчи в лабораториях Bell Labs в 1972 году для написания операционной системы UNIX. В отличие от Python или JavaScript, Си находится максимально близко к 'железу'. Здесь нет виртуальных машин, сборщиков мусора и скрытых накладных расходов.

Как устроена программа на Си:
1. Препроцессор: директива #include <stdio.h> подключает заголовочный файл со стандартными функциями ввода/вывода (Standard Input/Output).
2. Функция main: точка входа в программу. Операционная система вызывает именно ее.
   Синтаксис: int main(void) или int main(int argc, char *argv[])
3. Тело функции заключено в фигурные скобки { }.
4. Функция printf("..."): выводит форматированную строку в стандартный поток вывода stdout. Символ '\\n' обозначает перевод строки.
5. return 0; сообщает операционной системе, что программа завершилась успешно (код выхода 0). Код, отличный от 0 (например, -1 или 1), сигнализирует об ошибке.

Этапы сборки программы:
- Препроцессинг (расширение макросов, вставка #include)
- Компиляция (преобразование Си кода в язык ассемблера)
- Ассемблирование (преобразование в машинный объектный код .obj / .o)
- Линковка (связывание объектных файлов и системных библиотек в .exe)""",
        "task": "Напишите программу, которая выводит приветствие:\nHello, TrainerCode!\nArchitecture: x86_64\nи возвращает код 0.",
        "initialCode": """#include <stdio.h>

int main(void) {
    // Напишите вывод приветствия здесь:
    
    return 0;
}
""",
        "solution": """#include <stdio.h>

int main(void) {
    printf("Hello, TrainerCode!\\n");
    printf("Architecture: x86_64\\n");
    return 0;
}
""",
        "hints": [
            "Используйте функцию printf для вывода текста.",
            "Не забудьте символ '\\n' в конце каждой строки.",
            "Убедитесь в точности символов: Hello, TrainerCode!"
        ],
        "testInputs": [],
        "expectedOutput": "Hello, TrainerCode!\nArchitecture: x86_64\n"
    },
    {
        "id": 2,
        "module": "Модуль 1: Фундамент языка C и архитектура",
        "title": "Урок 2: Фундаментальные типы данных и память",
        "lang": "C",
        "difficulty": "Новичок",
        "theory": """В языке Си каждый тип данных имеет строго определенный размер в байтах в зависимости от архитектуры (x86 vs x64).

Основные типы данных:
- char (1 байт = 8 бит): хранит один символ ASCII или число от -128 до 127.
- int (обычно 4 байта = 32 бита): целое число со знаком (-2,147,483,648 .. 2,147,483,647).
- short (2 байта = 16 бит): короткое целое (-32,768 .. 32,767).
- long (4 байта на Windows x64, 8 байт на Linux x64).
- long long (8 байт = 64 бита): сверхбольшое целое число.
- float (4 байта): вещественное число с плавающей точкой одинарной точности (IEEE 754, ~7 знаков точности).
- double (8 байт): вещественное число двойной точности (~15 знаков точности).

Модификаторы:
- signed: со знаком (по умолчанию для int).
- unsigned: без знака (только неотрицательные числа, удваивает положительный диапазон! Например, unsigned char: 0 .. 255).

Оператор sizeof:
Оператор sizeof(тип) возвращает размер типа или переменной в байтах (тип возвращаемого значения — size_t, печатается через %zu).

Спецификаторы формата printf:
%d или %i — знаковый int
%u — беззнаковый unsigned int
%ld — long
%lld — long long
%f — float
%lf — double
%c — char (символ)
%p — указатель (адрес в памяти)
%zu — size_t""",
        "task": "Объявите переменные:\n- int a = 42;\n- double pi = 3.14159;\n- unsigned char flags = 255;\nВыведите их значения и размеры в байтах, используя sizeof, строго в формате:\na = 42 (size: 4)\npi = 3.141590 (size: 8)\nflags = 255 (size: 1)",
        "initialCode": """#include <stdio.h>

int main(void) {
    // Объявите переменные a, pi, flags:
    
    // Выведите значения и размеры с помощью sizeof:
    
    return 0;
}
""",
        "solution": """#include <stdio.h>

int main(void) {
    int a = 42;
    double pi = 3.14159;
    unsigned char flags = 255;

    printf("a = %d (size: %zu)\\n", a, sizeof(a));
    printf("pi = %f (size: %zu)\\n", pi, sizeof(pi));
    printf("flags = %u (size: %zu)\\n", flags, sizeof(flags));
    return 0;
}
""",
        "hints": [
            "Используйте %zu для вывода результата sizeof.",
            "Используйте %u для unsigned char.",
            "Используйте %f для double в printf."
        ],
        "testInputs": [],
        "expectedOutput": "a = 42 (size: 4)\npi = 3.141590 (size: 8)\nflags = 255 (size: 1)\n"
    },
    {
        "id": 3,
        "module": "Модуль 1: Фундамент языка C и архитектура",
        "title": "Урок 3: Ввод данных, scanf и ветвления if / else",
        "lang": "C",
        "difficulty": "Новичок",
        "theory": """Функция scanf():
Для чтения данных из консоли используется функция scanf:
int x;
scanf("%d", &x);

ВАЖНО: Обратите внимание на амперсанд (&)! Оператор & берет адрес переменной x в оперативной памяти. Функция scanf должна знать, куда именно записать прочитанные байты.

Условный оператор if / else:
if (условие) {
    // выполняется если условие истинно (!= 0)
} else if (другое_условие) {
    // ...
} else {
    // выполняется во всех остальных случаях
}

Операторы сравнения:
== (равно), != (не равно), <, >, <=, >=

Логические операторы:
&& (логическое И, AND)
|| (логическое ИЛИ, OR)
!  (логическое НЕ, NOT)

Тернарный оператор:
результат = (условие) ? значение_если_истина : значение_если_ложь;""",
        "task": "Напишите программу проверки четности и знака числа:\nПусть дано число int n = -8;\nЕсли число отрицательное, выведите 'Negative', если 0 — 'Zero', если положительное — 'Positive'.\nЗатем с новой строки выведите 'Even' для четного или 'Odd' для нечетного числа.\nПример для -8:\nNegative\nEven",
        "initialCode": """#include <stdio.h>

int main(void) {
    int n = -8;
    // Проверьте знак и четность числа:
    
    return 0;
}
""",
        "solution": """#include <stdio.h>

int main(void) {
    int n = -8;
    if (n < 0) {
        printf("Negative\\n");
    } else if (n > 0) {
        printf("Positive\\n");
    } else {
        printf("Zero\\n");
    }

    if (n % 2 == 0) {
        printf("Even\\n");
    } else {
        printf("Odd\\n");
    }
    return 0;
}
""",
        "hints": [
            "Используйте оператор остатка от деления %: n % 2 == 0 означает четное число.",
            "Сначала выведите Negative/Positive/Zero, затем Even/Odd."
        ],
        "testInputs": [],
        "expectedOutput": "Negative\nEven\n"
    },
    {
        "id": 4,
        "module": "Модуль 1: Фундамент языка C и архитектура",
        "title": "Урок 4: Циклы for, while, do-while и операторы break / continue",
        "lang": "C",
        "difficulty": "Новичок",
        "theory": """Циклы позволяют многократно выполнять блок инструкций. В Си существуют три основных вида циклов:

1. Цикл for:
for (инициализация; условие_продолжения; инкремент) {
    // тело цикла
}
Пример:
for (int i = 0; i < 5; i++) {
    printf("%d ", i);
}

2. Цикл while (цикл с предусловием):
while (условие) {
    // проверяет условие ДО выполнения тела
}

3. Цикл do-while (цикл с постусловием):
do {
    // тело цикла ВСЕГДА выполнится хотя бы один раз!
} while (условие);

Управление циклом:
- break: немедленный досрочный выход из цикла.
- continue: переход к следующей итерации цикла (пропуская оставшийся код в текущем шаге).""",
        "task": "Напишите цикл for, вычисляющий сумму всех нечетных чисел от 1 до 20 включительно. Выведите результат в формате:\nSum: 100",
        "initialCode": """#include <stdio.h>

int main(void) {
    int sum = 0;
    // Напишите цикл здесь:
    
    printf("Sum: %d\\n", sum);
    return 0;
}
""",
        "solution": """#include <stdio.h>

int main(void) {
    int sum = 0;
    for (int i = 1; i <= 20; i++) {
        if (i % 2 != 0) {
            sum += i;
        }
    }
    printf("Sum: %d\\n", sum);
    return 0;
}
""",
        "hints": [
            "Используйте цикл от 1 до 20 включительно (i <= 20).",
            "Для проверки нечетности: i % 2 != 0.",
            "Сумма нечетных чисел от 1 до 19 равна 100."
        ],
        "testInputs": [],
        "expectedOutput": "Sum: 100\n"
    },
    {
        "id": 5,
        "module": "Модуль 1: Фундамент языка C и архитектура",
        "title": "Урок 5: Побитовые операции и битовые маски",
        "lang": "C",
        "difficulty": "Средний",
        "theory": """Побитовые операции работают непосредственно с двоичными битами чисел в регистрах процессора. Это ключевой навык для низкоуровневого программирования, драйверов и встроенных систем.

Операторы:
&  (Побитовое И / AND): 1 & 1 = 1, иначе 0. Применяется для выделения бита (маскирования).
|  (Побитовое ИЛИ / OR): 1 | 0 = 1, 0 | 0 = 0. Применяется для установки бита в 1.
^  (Побитовое исключающее ИЛИ / XOR): 1 ^ 1 = 0, 1 ^ 0 = 1. Инвертирует бит или шифрует.
~  (Побитовое НЕ / NOT): инвертирует все биты (~00001111 = 11110000).
<< (Побитовый сдвиг влево): x << n умножает x на 2^n.
>> (Побитовый сдвиг вправо): x >> n делит x на 2^n.

Основные идиомы битовых масок:
1. Установить n-й бит в 1:
   flags |= (1U << n);
2. Сбросить n-й бит в 0:
   flags &= ~(1U << n);
3. Проверить n-й бит:
   bool is_set = (flags & (1U << n)) != 0;
4. Переключить n-й бит (toggle):
   flags ^= (1U << n);""",
        "task": "Пусть дано число unsigned char val = 0b00001010 (десятичное 10).\n1. Установите нулевой бит (бит 0) в единицу.\n2. Сбросьте первый бит (бит 1) в ноль.\nВыведите итоговое десятичное число в формате:\nResult: 9",
        "initialCode": """#include <stdio.h>

int main(void) {
    unsigned char val = 10; // Двоичное: 00001010
    // Установите бит 0:
    
    // Сбросьте бит 1:
    
    printf("Result: %u\\n", val);
    return 0;
}
""",
        "solution": """#include <stdio.h>

int main(void) {
    unsigned char val = 10; // Двоичное: 00001010
    val |= (1 << 0);        // Стало 00001011 (11)
    val &= ~(1 << 1);       // Сбросили бит 1 -> 00001001 (9)

    printf("Result: %u\\n", val);
    return 0;
}
""",
        "hints": [
            "Для установки бита: val |= (1 << 0)",
            "Для сброса бита: val &= ~(1 << 1)",
            "10 в двоичной системе это 00001010. После изменений получается 00001001 (9)."
        ],
        "testInputs": [],
        "expectedOutput": "Result: 9\n"
    },
    {
        "id": 6,
        "module": "Модуль 2: Функции, Стек и Память",
        "title": "Урок 6: Функции, стек вызовов (Call Stack) и области видимости",
        "lang": "C",
        "difficulty": "Новичок",
        "theory": """Функции в Си разделяют программу на повторно используемые модули.

Прототип функции:
Компилятор Си читает исходный файл сверху вниз. Если функция вызывается до своего определения, компилятору необходимо объявить прототип:
int add(int a, int b); // Прототип (декларация)

Передача аргументов:
В языке Си ВСЕ аргументы передаются ПО ЗНАЧЕНИЮ (by value). Это значит, что создается копия аргумента. Если вы измените переменную внутри функции, оригинальная переменная в main НЕ изменится!

Стек вызовов (Call Stack):
При каждом вызове функции на вершине стека выделяется так называемый 'стековый фрейм' (Stack Frame). Он содержит:
- Адрес возврата (куда вернуться в коде после return)
- Локальные переменные
- Параметры функции
Когда функция завершается, ее фрейм мгновенно освобождается (регистр указателя стека ESP/RSP сдвигается).

Ключевые слова:
- static переменная внутри функции сохраняет свое значение между вызовами! Она живет в сегменте данных .data, а не на стеке.
- inline — подсказка компилятору встроить код функции прямо в место вызова для экономии тактов процессора.""",
        "task": "Напишите функцию int counter(void), внутри которой находится статическая переменная (static int count = 0), увеличивающаяся на 1 при каждом вызове и возвращающая текущее значение.\nВызовите counter() три раза и выведите:\nCall 1: 1\nCall 2: 2\nCall 3: 3",
        "initialCode": """#include <stdio.h>

// Напишите функцию counter здесь:

int main(void) {
    printf("Call 1: %d\\n", counter());
    printf("Call 2: %d\\n", counter());
    printf("Call 3: %d\\n", counter());
    return 0;
}
""",
        "solution": """#include <stdio.h>

int counter(void) {
    static int count = 0;
    count++;
    return count;
}

int main(void) {
    printf("Call 1: %d\\n", counter());
    printf("Call 2: %d\\n", counter());
    printf("Call 3: %d\\n", counter());
    return 0;
}
""",
        "hints": [
            "Используйте static int count = 0 внутри counter().",
            "Статические локальные переменные инициализируются только один раз."
        ],
        "testInputs": [],
        "expectedOutput": "Call 1: 1\nCall 2: 2\nCall 3: 3\n"
    },
    {
        "id": 7,
        "module": "Модуль 2: Функции, Стек и Память",
        "title": "Урок 7: Рекурсия и предотвращение Stack Overflow",
        "lang": "C",
        "difficulty": "Средний",
        "theory": """Рекурсия — это процесс, когда функция вызывает саму себя.

Каждая рекурсивная функция обязана иметь базовый случай (Base Case) — условие останова. Если базовый случай отсутствует или некорректен, рекурсия становится бесконечной.

Что происходит при бесконечной рекурсии?
Каждый вызов функции аллоцирует новый фрейм на стеке (обычно размер стека в Windows составляет 1 МБ или 2 МБ). Когда фреймы переполняют выделенную память стека, операционная система немедленно завершает процесс с критической ошибкой: Stack Overflow (Код исключения EXCEPTION_STACK_OVERFLOW 0xC00000FD).

Классический пример: Факториал N!
N! = N * (N - 1)!
0! = 1
1! = 1

Хвостовая рекурсия (Tail Recursion):
Если рекурсивный вызов является самым последним действием перед return, умный компилятор (с флагом -O2 или /O2) способен оптимизировать его в обычный цикл jmp, не тратя стек!""",
        "task": "Напишите рекурсивную функцию long long factorial(int n), корректно обрабатывающую базовый случай n <= 1.\nВычислите factorial(6) и выведите:\nFactorial(6) = 720",
        "initialCode": """#include <stdio.h>

long long factorial(int n) {
    // Реализуйте базовый случай и рекурсивный шаг:
}

int main(void) {
    printf("Factorial(6) = %lld\\n", factorial(6));
    return 0;
}
""",
        "solution": """#include <stdio.h>

long long factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

int main(void) {
    printf("Factorial(6) = %lld\\n", factorial(6));
    return 0;
}
""",
        "hints": [
            "Базовый случай: if (n <= 1) return 1;",
            "Рекурсивный вызов: return n * factorial(n - 1);",
            "Для long long спецификатор формата — %lld."
        ],
        "testInputs": [],
        "expectedOutput": "Factorial(6) = 720\n"
    },
    {
        "id": 8,
        "module": "Модуль 3: Массивы, Строки и Указатели",
        "title": "Урок 8: Массивы в Си и непрерывная память",
        "lang": "C",
        "difficulty": "Новичок",
        "theory": """Массив — это непрерывная область памяти, хранящая элементы одного типа друг за другом.

Объявление и инициализация:
int arr[5] = {10, 20, 30, 40, 50};

Индексация:
Индексы в Си начинаются строго с 0!
arr[0] — первый элемент (смещение 0 байт)
arr[4] — последний элемент
Размер массива в байтах: sizeof(arr) = 5 * sizeof(int) = 20 байт.
Количество элементов в массиве:
size_t count = sizeof(arr) / sizeof(arr[0]);

ВНИМАНИЕ — ВЫХОД ЗА ПРЕДЕЛЫ МАССИВА (Buffer Overflow):
Язык Си не выполняет проверку границ массивов во время выполнения (Bounds Checking)!
Если вы обратитесь к arr[10], Си прочитает чужую память. Если вы запишете туда данные, вы затрете другие переменные или адрес возврата функции — это критическая уязвимость безопасности!""",
        "task": "Дан массив int numbers[] = {12, 45, 7, 89, 23, 56};\nНайдите максимальное число в массиве с помощью цикла for и выведите:\nMax: 89",
        "initialCode": """#include <stdio.h>

int main(void) {
    int numbers[] = {12, 45, 7, 89, 23, 56};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    int max = numbers[0];

    // Найдите максимум:
    
    printf("Max: %d\\n", max);
    return 0;
}
""",
        "solution": """#include <stdio.h>

int main(void) {
    int numbers[] = {12, 45, 7, 89, 23, 56};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    int max = numbers[0];

    for (size_t i = 1; i < count; i++) {
        if (numbers[i] > max) {
            max = numbers[i];
        }
    }

    printf("Max: %d\\n", max);
    return 0;
}
""",
        "hints": [
            "Итерируйтесь по массиву от i = 1 до i < count.",
            "Если numbers[i] > max, обновляйте max = numbers[i]."
        ],
        "testInputs": [],
        "expectedOutput": "Max: 89\n"
    },
    {
        "id": 9,
        "module": "Модуль 3: Массивы, Строки и Указатели",
        "title": "Урок 9: Строки в Си, нуль-терминатор '\\0' и строковые функции",
        "lang": "C",
        "difficulty": "Новичок",
        "theory": """В языке Си нет встроенного типа 'string'!
Строка в Си — это обычный массив символов char, заканчивающийся специальным байтом — нуль-терминатором '\\0' (байт со значением 0).

Пример:
char msg[] = "C2000";
В памяти это массив из 6 байтов:
['C', '2', '0', '0', '0', '\\0']
Если нуль-терминатор отсутствует, функции вроде printf(\"%s\") будут бежать по памяти дальше, печатая мусор, пока случайно не встретят нулевой байт или не упадут с Segmentation Fault!

Стандартная библиотека <string.h>:
- strlen(str): возвращает длину строки без учета '\\0'.
- strcpy(dest, src): копирует строку (ОПАСНО, нет проверки размера!).
- strncpy(dest, src, n): копирует не более n символов.
- strcat(dest, src): конкатенация строк.
- strcmp(s1, s2): сравнивает строки лексикографически. Возвращает 0, если строки абсолютно равны!
- snprintf(buffer, sizeof(buffer), \"format\", ...): самый безопасный способ форматирования строк в Си.""",
        "task": "Дана строка char greeting[32] = \"Hello\";\nИспользуйте snprintf или strcat, чтобы добавить к ней \", C Developer!\"\nВыведите полученную строку и ее длину:\nGreeting: Hello, C Developer!\nLength: 20",
        "initialCode": """#include <stdio.h>
#include <string.h>

int main(void) {
    char greeting[32] = "Hello";
    
    // Добавьте ", C Developer!" и вычислите длину:
    
    printf("Greeting: %s\\n", greeting);
    printf("Length: %zu\\n", strlen(greeting));
    return 0;
}
""",
        "solution": """#include <stdio.h>
#include <string.h>

int main(void) {
    char greeting[32] = "Hello";
    strcat(greeting, ", C Developer!");
    
    printf("Greeting: %s\\n", greeting);
    printf("Length: %zu\\n", strlen(greeting));
    return 0;
}
""",
        "hints": [
            "Используйте strcat(greeting, \", C Developer!\");",
            "strlen возвращает длину строки (20 символов)."
        ],
        "testInputs": [],
        "expectedOutput": "Greeting: Hello, C Developer!\nLength: 20\n"
    },
    {
        "id": 10,
        "module": "Модуль 3: Массивы, Строки и Указатели",
        "title": "Урок 10: УКАЗАТЕЛИ (Pointers) — Сердце и Мощь Си",
        "lang": "C",
        "difficulty": "Средний",
        "theory": """Указатель — это переменная, значением которой является АДРЕС в оперативной памяти другого объекта.

Операторы:
1. & (Address-of) — взятие адреса переменной:
   int val = 100;
   int *ptr = &val; // ptr теперь хранит адрес памяти переменной val!

2. * (Dereference) — разыменование указателя:
   *ptr = 200; // мы идем по адресу ptr и меняем значение val на 200!

Размер указателя:
На 32-битных системах указатель занимает 4 байта.
На 64-битных системах (x86_64) указатель занимает 8 байт (может адресовать до 16 эксабайт памяти!).

Адресная арифметика:
Когда вы прибавляете 1 к указателю на int:
ptr + 1
Адрес увеличивается не на 1 байт, а на sizeof(int) (то есть на 4 байта)! Указатель автоматически учитывает размер целевого типа.

NULL указатель:
Указатель, который никуда не указывает:
int *p = NULL; (в C это ((void*)0)). Разыменование NULL (*p) гарантированно крашит программу с Access Violation / Segfault!""",
        "task": "Напишите функцию swap, которая меняет местами значения двух целых чисел через указатели:\nvoid swap(int *a, int *b);\nВ main продемонстрируйте обмен переменных x = 10 и y = 20 и выведите:\nx = 20, y = 10",
        "initialCode": """#include <stdio.h>

void swap(int *a, int *b) {
    // Поменяйте значения переменных по адресам a и b:
}

int main(void) {
    int x = 10;
    int y = 20;
    swap(&x, &y);
    printf("x = %d, y = %d\\n", x, y);
    return 0;
}
""",
        "solution": """#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main(void) {
    int x = 10;
    int y = 20;
    swap(&x, &y);
    printf("x = %d, y = %d\\n", x, y);
    return 0;
}
""",
        "hints": [
            "Используйте временную переменную: int temp = *a;",
            "Присвойте *a = *b; затем *b = temp;",
            "В main передавайте адреса: swap(&x, &y)."
        ],
        "testInputs": [],
        "expectedOutput": "x = 20, y = 10\n"
    },
    {
        "id": 11,
        "module": "Модуль 3: Массивы, Строки и Указатели",
        "title": "Урок 11: Указатели на функции и Callbacks",
        "lang": "C",
        "difficulty": "Продвинутый",
        "theory": """В Си даже исполняемый машинный код функций находится в оперативной памяти (в сегменте .text). Это означает, что у каждой функции есть свой адрес, и мы можем создавать указатели на функции!

Синтаксис указателя на функцию:
возвращаемый_тип (*имя_указателя)(типы_параметров);

Пример:
int add(int a, int b) { return a + b; }
int multiply(int a, int b) { return a * b; }

// Объявляем указатель op:
int (*op)(int, int) = add;
int res1 = op(5, 3); // вызовет add -> 8

op = multiply;
int res2 = op(5, 3); // вызовет multiply -> 15

Зачем это нужно?
1. Callback-функции (функции обратного вызова при событиях GUI, кликах мыши, сетевых пакетах).
2. Стандартная сортировка qsort из <stdlib.h>, которая принимает компаратор:
   int compare(const void *a, const void *b);
3. Таблицы виртуальных методов (на этом основан полиморфизм в C++ и COM в Windows!).""",
        "task": "Напишите функцию higher-order:\nint compute(int x, int y, int (*operation)(int, int))\nкоторая вызывает переданную функцию.\nОбъявите две простые функции add и sub, вызовите их через compute и выведите:\nAdd: 15\nSub: 5",
        "initialCode": """#include <stdio.h>

int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }

// Реализуйте compute:

int main(void) {
    printf("Add: %d\\n", compute(10, 5, add));
    printf("Sub: %d\\n", compute(10, 5, sub));
    return 0;
}
""",
        "solution": """#include <stdio.h>

int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }

int compute(int x, int y, int (*operation)(int, int)) {
    return operation(x, y);
}

int main(void) {
    printf("Add: %d\\n", compute(10, 5, add));
    printf("Sub: %d\\n", compute(10, 5, sub));
    return 0;
}
""",
        "hints": [
            "Сигнатура: int compute(int x, int y, int (*operation)(int, int))",
            "Тело функции: return operation(x, y);"
        ],
        "testInputs": [],
        "expectedOutput": "Add: 15\nSub: 5\n"
    },
    {
        "id": 12,
        "module": "Модуль 4: Динамическая Память и Пользовательские Типы",
        "title": "Урок 12: Динамическая память в куче (Heap): malloc, calloc, free",
        "lang": "C",
        "difficulty": "Средний",
        "theory": """В отличие от стека (размер которого фиксирован и память освобождается автоматически при выходе из функции), память в КУЧЕ (Heap) управляется программистом вручную во время выполнения программы (Runtime).

Функции из <stdlib.h>:
1. malloc(size_t size):
   Выделяет блок памяти размером size байтов. Внимание: память НЕ инициализируется (содержит случайный 'мусор')!
   int *arr = (int*)malloc(10 * sizeof(int));

2. calloc(size_t num, size_t size):
   Выделяет память под num элементов и зануляет каждый байт нулями!
   
3. realloc(void *ptr, size_t new_size):
   Изменяет размер ранее выделенного блока памяти.

4. free(void *ptr):
   Освобождает ранее выделенную память. После free указатель становится висячим (Dangling Pointer) — хорошим тоном является обнулить его: ptr = NULL;

Смертные грехи C-программиста:
- Утечка памяти (Memory Leak): забыли вызвать free(). Программа пожирает RAM до истощения системы.
- Двойное освобождение (Double Free): дважды вызвали free(ptr) для одного блока памяти (краш кучи).
- Разыменование после освобождения (Use-After-Free): чтение или запись по освобожденному адресу.""",
        "task": "Выделите в куче динамический массив из 3 целых чисел с помощью malloc.\nЗаполните его числами 100, 200, 300.\nВыведите сумму элементов: Sum: 600\nНе забудьте освободить память вызовом free().",
        "initialCode": """#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // 1. Выделите память на 3 элемента int
    
    // 2. Проверьте на NULL
    
    // 3. Заполните массив и посчитайте сумму
    
    // 4. Освободите память
    
    return 0;
}
""",
        "solution": """#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *arr = (int*)malloc(3 * sizeof(int));
    if (arr == NULL) {
        return 1;
    }

    arr[0] = 100;
    arr[1] = 200;
    arr[2] = 300;

    int sum = arr[0] + arr[1] + arr[2];
    printf("Sum: %d\\n", sum);

    free(arr);
    arr = NULL;
    return 0;
}
""",
        "hints": [
            "Выделите: int *arr = malloc(3 * sizeof(int));",
            "Проверьте if (arr == NULL)",
            "В конце обязательно вызовите free(arr);"
        ],
        "testInputs": [],
        "expectedOutput": "Sum: 600\n"
    },
    {
        "id": 13,
        "module": "Модуль 4: Динамическая Память и Пользовательские Типы",
        "title": "Урок 13: Структуры (struct), typedef и выравнивание (Padding)",
        "lang": "C",
        "difficulty": "Средний",
        "theory": """Структура (struct) объединяет переменные разных типов под одним именем.

Синтаксис:
struct Point {
    int x;
    int y;
};

Использование typedef для сокращения записи:
typedef struct {
    char name[32];
    int age;
    float gpa;
} Student;

Доступ к полям:
1. Через точку (.), если у нас сам объект:
   Student s1;
   s1.age = 20;

2. Через стрелочку (->), если у нас УКАЗАТЕЛЬ на структуру:
   Student *ptr = &s1;
   ptr->age = 21; // Эквивалентно (*ptr).age = 21

Выравнивание данных в памяти (Structure Padding):
Процессоры x86/x64 читают память порциями по 4 или 8 байт (слова). Поэтому компилятор автоматически вставляет пустые байты (Padding) между полями структуры, чтобы они лежали по адресам, кратным своему размеру!
Пример:
struct Example {
    char a; // 1 байт + 3 байта padding!
    int b;  // 4 байта
};
Размер sizeof(struct Example) будет равен 8 байтам, а не 5!""",
        "task": "Создайте структуру Vector2D с полями double x и double y.\nНапишите функцию:\nvoid scale(Vector2D *v, double factor)\nкоторая умножает поля x и y на factor через указатель.\nВ main создайте вектор {3.0, 4.0}, масштабируйте его в 2 раза и выведите:\nVector: (6.00, 8.00)",
        "initialCode": """#include <stdio.h>

typedef struct {
    double x;
    double y;
} Vector2D;

void scale(Vector2D *v, double factor) {
    // Реализуйте масштабирование через указатель:
}

int main(void) {
    Vector2D vec = {3.0, 4.0};
    scale(&vec, 2.0);
    printf("Vector: (%.2f, %.2f)\\n", vec.x, vec.y);
    return 0;
}
""",
        "solution": """#include <stdio.h>

typedef struct {
    double x;
    double y;
} Vector2D;

void scale(Vector2D *v, double factor) {
    v->x *= factor;
    v->y *= factor;
}

int main(void) {
    Vector2D vec = {3.0, 4.0};
    scale(&vec, 2.0);
    printf("Vector: (%.2f, %.2f)\\n", vec.x, vec.y);
    return 0;
}
""",
        "hints": [
            "Используйте оператор стрелки: v->x *= factor;",
            "v->y *= factor;"
        ],
        "testInputs": [],
        "expectedOutput": "Vector: (6.00, 8.00)\n"
    },
    {
        "id": 14,
        "module": "Модуль 4: Динамическая Память и Пользовательские Типы",
        "title": "Урок 14: Файловый ввод-вывод и дескриптор FILE*",
        "lang": "C",
        "difficulty": "Средний",
        "theory": """Для работы с файлами стандартная библиотека Си предоставляет тип дескриптора FILE* (поток).

Основные функции:
- fopen(const char *filename, const char *mode):
  Открывает файл. Режимы:
  \"r\" — чтение
  \"w\" — запись (создает новый или перезаписывает существующий)
  \"a\" — добавление в конец (append)
  \"rb\", \"wb\" — бинарный режим (критично для Windows!)
  Если файл не удалось открыть, возвращает NULL.
- fclose(FILE *stream): закрывает файл и сбрасывает буферы на диск.
- fprintf(file, \"format\", ...): форматированная запись в файл.
- fscanf(file, \"format\", ...): чтение из файла.
- fgets(char *str, int n, FILE *stream): безопасное построчное чтение текста.
- fwrite(buf, size, count, file): бинарная запись сырых байтов.
- fread(buf, size, count, file): бинарное чтение сырых байтов.

Стандартные потоки (уже открыты при старте программы):
- stdin (клавиатура / ввод)
- stdout (консоль / вывод)
- stderr (поток ошибок, не буферизуется)""",
        "task": "Используйте временный файл, чтобы записать в него строку \"TrainerCode_2000\", а затем прочитайте ее обратно и выведите в stdout:\nLoaded from file: TrainerCode_2000",
        "initialCode": """#include <stdio.h>

int main(void) {
    const char *fname = "temp_lesson.txt";
    // 1. Откройте файл на запись ("w"), запишите строку с помощью fprintf, закройте.
    
    // 2. Откройте на чтение ("r"), прочитайте с помощью fgets или fscanf, выведите.
    
    return 0;
}
""",
        "solution": """#include <stdio.h>

int main(void) {
    const char *fname = "temp_lesson.txt";
    FILE *fout = fopen(fname, "w");
    if (fout) {
        fprintf(fout, "TrainerCode_2000\\n");
        fclose(fout);
    }

    FILE *fin = fopen(fname, "r");
    char buffer[64] = {0};
    if (fin) {
        if (fscanf(fin, "%63s", buffer) == 1) {
            printf("Loaded from file: %s\\n", buffer);
        }
        fclose(fin);
    }
    return 0;
}
""",
        "hints": [
            "Всегда проверяйте результат fopen на равенство NULL.",
            "Не забывайте вызывать fclose для закрытия файла."
        ],
        "testInputs": [],
        "expectedOutput": "Loaded from file: TrainerCode_2000\n"
    },
    {
        "id": 15,
        "module": "Модуль 5: Переход к C++ и Основы ООП",
        "title": "Урок 15: Переход к C++: потоки cin/cout, ссылки & и перегрузка",
        "lang": "C++",
        "difficulty": "Новичок",
        "theory": """Язык C++ был разработан Бьёрном Страуструпом как 'Си с классами'. C++ обратно совместим с большинством конструкций Си, но вводит мощнейшие высокоуровневые абстракции с нулевой стоимостью (Zero-Cost Abstractions).

1. Потоки ввода-вывода <iostream>:
Вместо printf и scanf в C++ используются типизированные потоки std::cout (вывод) и std::cin (ввод):
#include <iostream>
std::cout << \"Hello C++!\" << std::endl;

2. Ссылки (References) vs Указатели:
Ссылка — это псевдоним (alias) уже существующей переменной.
В отличие от указателя:
- Ссылку НЕЛЬЗЯ сделать NULL (она всегда ссылается на реальный объект).
- Ссылку нельзя перепривязать к другой переменной после инициализации.
- Доступ осуществляется без разыменования (*):
  void increment(int &val) {
      val++; // изменяет оригинальную переменную напрямую!
  }

3. Перегрузка функций (Function Overloading):
В C++ функции могут иметь одинаковое имя, если у них разные типы или количество параметров! Компилятор выполняет Name Mangling и выбирает нужную версию.

4. nullptr:
В C++11 вместо макроса NULL (который был числом 0) введен строго типизированный nullptr типа std::nullptr_t.""",
        "task": "Напишите две перегруженные функции printDouble:\nvoid printDouble(int x) -> печатает удвоенный int: \"Double int: \" << x * 2\nvoid printDouble(double x) -> печатает удвоенный double: \"Double double: \" << x * 2.0\nВ main вызовите printDouble(21) и printDouble(3.5):\nDouble int: 42\nDouble double: 7",
        "initialCode": """#include <iostream>

// Напишите перегруженные функции printDouble:

int main() {
    printDouble(21);
    printDouble(3.5);
    return 0;
}
""",
        "solution": """#include <iostream>

void printDouble(int x) {
    std::cout << "Double int: " << x * 2 << std::endl;
}

void printDouble(double x) {
    std::cout << "Double double: " << x * 2.0 << std::endl;
}

int main() {
    printDouble(21);
    printDouble(3.5);
    return 0;
}
""",
        "hints": [
            "Объявите одну функцию с параметром (int x), а вторую с (double x).",
            "Используйте std::cout << ... << std::endl;"
        ],
        "testInputs": [],
        "expectedOutput": "Double int: 42\nDouble double: 7\n"
    },
    {
        "id": 16,
        "module": "Модуль 5: Переход к C++ и Основы ООП",
        "title": "Урок 16: Классы, Инкапсуляция, Конструкторы и Деструкторы",
        "lang": "C++",
        "difficulty": "Средний",
        "theory": """Класс в C++ — это пользовательский тип, объединяющий данные (поля) и функции для работы с ними (методы).

Спецификаторы доступа (Инкапсуляция):
- private: поля и методы доступны только внутри самого класса (скрытая реализация).
- public: интерфейс, доступный снаружи.
- protected: доступно внутри класса и его классов-наследников.

Жизненный цикл объекта:
1. Конструктор (Constructor):
   Вызывается автоматически в момент создания объекта в памяти. Имеет то же имя, что и класс, не возвращает значение.
   Список инициализации (Member Initializer List) — предпочтительный способ инициализации полей:
   Player(std::string name, int hp) : name_(name), hp_(hp) {}

2. Деструктор (Destructor):
   Вызывается автоматически, когда объект уничтожается (выходит из области видимости { } или при delete). Начинается с тильды (~):
   ~Player() {
       // освобождение ресурсов
   }

Ключевое слово this:
Указатель this хранит адрес текущего экземпляра класса внутри его нестатических методов.""",
        "task": "Создайте класс Hero с private полями std::string name_ и int health_.\nСделайте public конструктор с параметрами Hero(std::string name, int health).\nСделайте public метод void takeDamage(int amount), уменьшающий здоровье, и метод int getHealth() const.\nВ main создайте героя с именем \"Knight\" и 100 HP, нанесите 35 урона и выведите:\nKnight HP: 65",
        "initialCode": """#include <iostream>
#include <string>

class Hero {
    // Реализуйте поля и методы класса Hero:
};

int main() {
    Hero hero("Knight", 100);
    hero.takeDamage(35);
    std::cout << "Knight HP: " << hero.getHealth() << std::endl;
    return 0;
}
""",
        "solution": """#include <iostream>
#include <string>

class Hero {
private:
    std::string name_;
    int health_;

public:
    Hero(std::string name, int health) : name_(name), health_(health) {}

    void takeDamage(int amount) {
        health_ -= amount;
        if (health_ < 0) health_ = 0;
    }

    int getHealth() const {
        return health_;
    }
};

int main() {
    Hero hero("Knight", 100);
    hero.takeDamage(35);
    std::cout << "Knight HP: " << hero.getHealth() << std::endl;
    return 0;
}
""",
        "hints": [
            "Используйте список инициализации: Hero(std::string name, int health) : name_(name), health_(health) {}",
            "Не забудьте спецификатор public: перед методами."
        ],
        "testInputs": [],
        "expectedOutput": "Knight HP: 65\n"
    },
    {
        "id": 17,
        "module": "Модуль 5: Переход к C++ и Основы ООП",
        "title": "Урок 17: Наследование, Полиморфизм и Таблица vtable",
        "lang": "C++",
        "difficulty": "Продвинутый",
        "theory": """Полиморфизм — это способность обрабатывать объекты разных классов через общий базовый интерфейс во время выполнения.

Ключевое слово virtual:
Если метод базового класса помечен как virtual, вызов через указатель или ссылку на базовый класс будет вызывать ПЕРЕОПРЕДЕЛЕННУЮ реализацию наследника!
class Shape {
public:
    virtual void draw() const { std::cout << \"Shape\"; }
    virtual ~Shape() {} // Деструктор базового класса ОБЯЗАН быть виртуальным!
};

class Circle : public Shape {
public:
    void draw() const override { std::cout << \"Circle\"; }
};

Как устроен полиморфизм 'под капотом' (vtable):
При компиляции для каждого класса с виртуальными методами компилятор генерирует статическую массив указателей на функции — Таблицу виртуальных функций (Virtual Method Table / vtable).
В каждый объект такого класса скрыто добавляется 8-байтный указатель __vptr, указывающий на vtable его класса. При вызове shape->draw() процессор читает адрес из vtable и делает косвенный переход (call [rax+offset]).

Чисто виртуальные функции и абстрактные классы:
virtual void draw() const = 0; // Чисто виртуальный метод
Класс, содержащий хотя бы один чисто виртуальный метод, называется абстрактным (нельзя создать объект напрямую).""",
        "task": "Создайте базовый абстрактный класс Device с чисто виртуальным методом virtual void powerOn() = 0 и виртуальным деструктором.\nСоздайте класс-наследник Laptop, переопределяющий powerOn() с выводом \"Laptop is booting...\"\nВ main создайте Laptop через указатель на Device* и вызовите powerOn():\nLaptop is booting...",
        "initialCode": """#include <iostream>

// 1. Создайте абстрактный класс Device:

// 2. Создайте класс Laptop : public Device:

int main() {
    Device *d = new Laptop();
    d->powerOn();
    delete d;
    return 0;
}
""",
        "solution": """#include <iostream>

class Device {
public:
    virtual ~Device() {}
    virtual void powerOn() = 0;
};

class Laptop : public Device {
public:
    void powerOn() override {
        std::cout << "Laptop is booting..." << std::endl;
    }
};

int main() {
    Device *d = new Laptop();
    d->powerOn();
    delete d;
    return 0;
}
""",
        "hints": [
            "virtual void powerOn() = 0; объявляет чисто виртуальный метод.",
            "Используйте override в производном классе Laptop.",
            "Всегда объявляйте virtual ~Device() {}"
        ],
        "testInputs": [],
        "expectedOutput": "Laptop is booting...\n"
    },
    {
        "id": 18,
        "module": "Модуль 6: Modern C++ и STL",
        "title": "Урок 18: Управление ресурсами: RAII и Семантика перемещения",
        "lang": "C++",
        "difficulty": "Продвинутый",
        "theory": """RAII (Resource Acquisition Is Initialization — Захват ресурса есть инициализация) — краеугольный камень Modern C++!
Идея: Любой ресурс (динамическая память, файловый дескриптор, мьютекс, сетевой сокет) захватывается в конструкторе объекта и гарантированно освобождается в деструкторе, когда объект покидает область видимости (scope). Это гарантирует отсутствие утечек даже при возникновении исключений!

Семантика перемещения (Move Semantics, C++11):
До C++11 при возврате больших объектов (например, строк или векторов) происходило дорогое глубокое копирование миллионов байтов.
C++11 ввел rvalue-ссылки (обозначаются как &&):
- lvalue: объект, у которого есть имя и адрес в памяти (например, int x).
- rvalue: временное значение без имени (например, x + 5, или временный объект в return).

std::move(obj):
Не перемещает ничего сам по себе! Он выполняет static_cast к rvalue-ссылке (T&&), сигнализируя компилятору: 'У этого объекта можно отобрать его внутренний буфер (указатель), оставив его в пустом валидном состоянии!'. Это операция O(1) вместо копирования O(N).""",
        "task": "Изучите работу std::move со строками:\nstd::string original = \"Valuable Data\";\nstd::string moved = std::move(original);\nВыведите:\nMoved: Valuable Data\nOriginal empty: 1 (проверьте original.empty())",
        "initialCode": """#include <iostream>
#include <string>
#include <utility>

int main() {
    std::string original = "Valuable Data";
    // Переместите original в moved с помощью std::move:
    
    std::cout << "Moved: " << moved << std::endl;
    std::cout << "Original empty: " << original.empty() << std::endl;
    return 0;
}
""",
        "solution": """#include <iostream>
#include <string>
#include <utility>

int main() {
    std::string original = "Valuable Data";
    std::string moved = std::move(original);

    std::cout << "Moved: " << moved << std::endl;
    std::cout << "Original empty: " << original.empty() << std::endl;
    return 0;
}
""",
        "hints": [
            "Используйте std::string moved = std::move(original);",
            "После перемещения буфер строки перешел в moved, а original опустел."
        ],
        "testInputs": [],
        "expectedOutput": "Moved: Valuable Data\nOriginal empty: 1\n"
    },
    {
        "id": 19,
        "module": "Модуль 6: Modern C++ и STL",
        "title": "Урок 19: Умные указатели: std::unique_ptr и std::shared_ptr",
        "lang": "C++",
        "difficulty": "Продвинутый",
        "theory": """В современном C++ сырые указатели (raw pointers) со словами new и delete использовать категорически не рекомендуется! Вместо них используются умные указатели из заголовка <memory>.

1. std::unique_ptr:
- Владеет объектом единолично (Exclusive Ownership).
- Нулевые накладные расходы по памяти и скорости (ровно размер одного сырого указателя).
- Нельзя скопировать (copy constructor удален), можно только перемещать (std::move)!
- Создается через std::make_unique<T>(args...):
  auto ptr = std::make_unique<MyClass>(42);

2. std::shared_ptr:
- Разделяемое владение (Shared Ownership).
- Содержит счетчик ссылок (Reference Counter) в отдельном блоке управления (Control Block).
- Когда счетчик ссылок достигает 0, объект автоматически уничтожается.
- Создается через std::make_shared<T>(args...).

3. std::weak_ptr:
- 'Слабый' указатель, не увеличивающий счетчик ссылок shared_ptr.
- Предотвращает циклические ссылки (когда объект A держит shared_ptr на B, а B держит на A — они никогда не удалились бы!).""",
        "task": "Используйте std::unique_ptr для выделения объекта int со значением 777 с помощью std::make_unique.\nВыведите значение через разыменование *ptr:\nValue: 777",
        "initialCode": """#include <iostream>
#include <memory>

int main() {
    // Создайте unique_ptr на int со значением 777:
    
    // Выведите *ptr:
    
    return 0;
}
""",
        "solution": """#include <iostream>
#include <memory>

int main() {
    std::unique_ptr<int> ptr = std::make_unique<int>(777);
    std::cout << "Value: " << *ptr << std::endl;
    return 0;
}
""",
        "hints": [
            "Используйте auto ptr = std::make_unique<int>(777);",
            "Разыменуйте: *ptr."
        ],
        "testInputs": [],
        "expectedOutput": "Value: 777\n"
    },
    {
        "id": 20,
        "module": "Модуль 6: Modern C++ и STL",
        "title": "Урок 20: Шаблоны (Templates) и обобщенное программирование",
        "lang": "C++",
        "difficulty": "Продвинутый",
        "theory": """Шаблоны (Templates) позволяют писать код, не привязанный к конкретному типу данных. Компилятор сам генерирует нужную реализацию во время сборки для каждого типа (инстанцирование шаблона).

1. Шаблоны функций:
template <typename T>
T getMin(T a, T b) {
    return (a < b) ? a : b;
}
Вызов:
getMin<int>(5, 10); // вернет 5
getMin(3.14, 2.71); // компилятор автоматически выведет тип double!

2. Шаблоны классов:
template <typename T>
class Stack {
    std::vector<T> elements;
public:
    void push(const T &item) { elements.push_back(item); }
    T pop() { ... }
};

3. constexpr (C++11/14/17):
Ключевое слово constexpr сообщает, что функция или переменная может быть вычислена прямо во время компиляции программы, до ее запуска!""",
        "task": "Напишите шаблонную функцию template <typename T> T clamp(T val, T low, T high), которая ограничивает значение val диапазоном [low, high].\nПроверьте ее работу для clamp(15, 0, 10) и clamp(-5, 0, 10):\nClamped: 10\nClamped: 0",
        "initialCode": """#include <iostream>

// Напишите шаблон функции clamp:

int main() {
    std::cout << "Clamped: " << clamp(15, 0, 10) << std::endl;
    std::cout << "Clamped: " << clamp(-5, 0, 10) << std::endl;
    return 0;
}
""",
        "solution": """#include <iostream>

template <typename T>
T clamp(T val, T low, T high) {
    if (val < low) return low;
    if (val > high) return high;
    return val;
}

int main() {
    std::cout << "Clamped: " << clamp(15, 0, 10) << std::endl;
    std::cout << "Clamped: " << clamp(-5, 0, 10) << std::endl;
    return 0;
}
""",
        "hints": [
            "Синтаксис: template <typename T> T clamp(T val, T low, T high)",
            "Если val < low верните low, если val > high верните high, иначе val."
        ],
        "testInputs": [],
        "expectedOutput": "Clamped: 10\nClamped: 0\n"
    },
    {
        "id": 21,
        "module": "Модуль 6: Modern C++ и STL",
        "title": "Урок 21: Контейнеры STL: std::vector, std::map и std::unordered_map",
        "lang": "C++",
        "difficulty": "Средний",
        "theory": """Стандартная библиотека шаблонов (STL) предоставляет готовые, высокооптимизированные структуры данных:

1. std::vector<T>:
- Динамический массив непрерывной памяти.
- Быстрый произвольный доступ по индексу: O(1).
- Вставка в конец: амортизированное O(1).
- Методы: push_back, emplace_back, size, empty, clear, capacity, reserve.

2. std::map<Key, Value>:
- Ассоциативный массив, упорядоченный по ключам.
- Внутри реализован как самобалансирующееся Красно-Черное дерево (Red-Black Tree).
- Поиск, вставка и удаление: O(log N).

3. std::unordered_map<Key, Value>:
- Хеш-таблица. Ключи не упорядочены.
- Поиск в среднем за константное время: O(1)!

Сравнение асимптотики:
Контейнер       | Поиск    | Вставка в конец | Память
std::vector     | O(N)     | O(1)            | Минимальная непрерывная
std::map        | O(log N) | O(log N)        | Узлы дерева + указатели
std::unordered_map | O(1)  | O(1)            | Таблица бакетов""",
        "task": "Создайте std::vector<int> v = {5, 2, 8, 1, 9};\nДобавьте в конец число 42 с помощью push_back.\nОтсортируйте вектор по возрастанию с помощью std::sort из <algorithm>.\nВыведите отсортированные элементы через пробел:\n1 2 5 8 9 42",
        "initialCode": """#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> v = {5, 2, 8, 1, 9};
    // 1. Добавьте 42 в конец вектора
    
    // 2. Отсортируйте вектор std::sort
    
    // 3. Выведите элементы через пробел:
    
    std::cout << std::endl;
    return 0;
}
""",
        "solution": """#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> v = {5, 2, 8, 1, 9};
    v.push_back(42);
    std::sort(v.begin(), v.end());

    for (size_t i = 0; i < v.size(); i++) {
        if (i > 0) std::cout << " ";
        std::cout << v[i];
    }
    std::cout << std::endl;
    return 0;
}
""",
        "hints": [
            "v.push_back(42);",
            "std::sort(v.begin(), v.end());",
            "Используйте цикл по вектору для вывода."
        ],
        "testInputs": [],
        "expectedOutput": "1 2 5 8 9 42\n"
    },
    {
        "id": 22,
        "module": "Модуль 6: Modern C++ и STL",
        "title": "Урок 22: Лямбда-выражения и алгоритмы STL",
        "lang": "C++",
        "difficulty": "Продвинутый",
        "theory": """Лямбда-выражение (Lambda) — это анонимная функция, которую можно определить прямо по месту вызова.

Синтаксис лямбды в C++:
[захват](параметры) -> возвращаемый_тип { тело }

Список захвата (Capture List):
[] — ничего не захватывать из внешней области видимости.
[&] — захватить все внешние переменные по ссылке.
[=] — захватить все внешние переменные по значению (копии).
[x, &y] — x по значению, y по ссылке.

Использование с алгоритмами <algorithm>:
- std::count_if(begin, end, predicate): подсчитывает элементы, удовлетворяющие условию.
- std::for_each(begin, end, function): применяет функцию к каждому элементу.
- std::transform: преобразует элементы из одного диапазона в другой.
- std::all_of / std::any_of / std::none_of: проверка условий на диапазоне.""",
        "task": "Дан вектор std::vector<int> nums = {10, -5, 20, 0, -15, 30};\nИспользуйте std::count_if и лямбда-выражение, чтобы посчитать количество положительных чисел (> 0).\nВыведите:\nPositive count: 3",
        "initialCode": """#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> nums = {10, -5, 20, 0, -15, 30};
    
    // Подсчитайте количество чисел > 0 с помощью std::count_if и лямбды:
    int count = 0;
    
    std::cout << "Positive count: " << count << std::endl;
    return 0;
}
""",
        "solution": """#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> nums = {10, -5, 20, 0, -15, 30};
    int count = std::count_if(nums.begin(), nums.end(), [](int n) {
        return n > 0;
    });

    std::cout << "Positive count: " << count << std::endl;
    return 0;
}
""",
        "hints": [
            "Лямбда: [](int n) { return n > 0; }",
            "count = std::count_if(nums.begin(), nums.end(), ...);"
        ],
        "testInputs": [],
        "expectedOutput": "Positive count: 3\n"
    },
    {
        "id": 23,
        "module": "Модуль 6: Modern C++ и STL",
        "title": "Урок 23: Обработка исключений (try, catch, throw)",
        "lang": "C++",
        "difficulty": "Средний",
        "theory": """Исключения (Exceptions) — механизм сообщений об ошибках во время выполнения программы без использования кодов возврата.

Синтаксис:
try {
    // Код, который может сгенерировать исключение
    if (divisor == 0) {
        throw std::runtime_error(\"Division by zero!\");
    }
} catch (const std::runtime_error &e) {
    // Обработка конкретного типа ошибки
    std::cout << \"Error: \" << e.what() << std::endl;
} catch (const std::exception &e) {
    // Обработка любых стандартных исключений
} catch (...) {
    // Перехват абсолютно любого необработанного исключения
}

Раскрутка стека (Stack Unwinding):
Когда выбрасывается исключение, среда выполнения C++ начинает раскручивать стек вверх до ближайшего подходящего блока catch.
В процессе раскрутки стека для ВСЕХ локальных объектов на пройденных стековых фреймах вызываются их деструкторы! Благодаря RAII это гарантирует, что память и ресурсы не утекут даже при критическом сбое!

noexcept:
Ключевое слово noexcept указывает компилятору, что функция гарантированно не выбрасывает исключений (позволяет компилятору генерировать более быстрый машинный код).""",
        "task": "Напишите функцию double safeDivide(double a, double b), которая выбрасывает std::invalid_argument(\"Zero division\"), если b == 0.\nВ main вызовите safeDivide(10, 0) внутри блока try-catch и напечатайте:\nCaught exception: Zero division",
        "initialCode": """#include <iostream>
#include <stdexcept>

double safeDivide(double a, double b) {
    // Выбросьте std::invalid_argument если b == 0:
    return a / b;
}

int main() {
    try {
        safeDivide(10.0, 0.0);
    } catch (const std::invalid_argument &e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    return 0;
}
""",
        "solution": """#include <iostream>
#include <stdexcept>

double safeDivide(double a, double b) {
    if (b == 0.0) {
        throw std::invalid_argument("Zero division");
    }
    return a / b;
}

int main() {
    try {
        safeDivide(10.0, 0.0);
    } catch (const std::invalid_argument &e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    return 0;
}
""",
        "hints": [
            "if (b == 0.0) throw std::invalid_argument(\"Zero division\");",
            "Метод e.what() возвращает текст переданной ошибки."
        ],
        "testInputs": [],
        "expectedOutput": "Caught exception: Zero division\n"
    },
    {
        "id": 24,
        "module": "Модуль 6: Modern C++ и STL",
        "title": "Урок 24: Многопоточность: std::thread, std::mutex и race conditions",
        "lang": "C++",
        "difficulty": "Эксперт",
        "theory": """Современные процессоры содержат десятки физических ядер. Заголовок <thread> в C++11 принес стандартную кроссплатформенную модель работы с потоками.

Создание потока:
std::thread t(function_name, arg1, arg2);
t.join(); // Ждем завершения работы потока!
Если объект потока t будет уничтожен без вызова t.join() или t.detach(), среда C++ немедленно вызовет std::terminate() и аварийно завершит программу!

Состояние гонки (Race Condition) и Мьютексы (Mutex):
Если два потока одновременно читают и записывают одну и ту же переменную памяти без синхронизации, возникает Неопределенное Поведение (Undefined Behavior).
Для защиты критических секций используется std::mutex:
std::mutex mtx;
mtx.lock();
// критическая секция
mtx.unlock();

RAII-обертка std::lock_guard:
Вместо ручного вызова lock/unlock (где можно забыть unlock при исключении):
{
    std::lock_guard<std::mutex> lock(mtx); // захватывает мьютекс
    // мьютекс автоматически освободится при выходе из скобок!
}

Атомики std::atomic:
Для простых счетчиков и флагов заголовок <atomic> предоставляет lock-free атомарные типы:
std::atomic<int> counter(0);
counter++; // атомарная инструкция процессора (LOCK XADD на x86)!""",
        "task": "Изучите работу std::atomic<int>.\nСоздайте std::atomic<int> counter(0);\nВыполните инкремент counter++ 5 раз.\nВыведите значение счетчика:\nAtomic counter: 5",
        "initialCode": """#include <iostream>
#include <atomic>

int main() {
    std::atomic<int> counter(0);
    // Выполните 5 инкрементов:
    
    std::cout << "Atomic counter: " << counter.load() << std::endl;
    return 0;
}
""",
        "solution": """#include <iostream>
#include <atomic>

int main() {
    std::atomic<int> counter(0);
    for (int i = 0; i < 5; i++) {
        counter++;
    }

    std::cout << "Atomic counter: " << counter.load() << std::endl;
    return 0;
}
""",
        "hints": [
            "Используйте цикл for от 0 до 5 и counter++;",
            "counter.load() читает значение атомарно."
        ],
        "testInputs": [],
        "expectedOutput": "Atomic counter: 5\n"
    },
    {
        "id": 25,
        "module": "Модуль 6: Modern C++ и STL",
        "title": "Урок 25: Финальный курсовой проект: Реализация кастомного Vector",
        "lang": "C++",
        "difficulty": "Эксперт",
        "theory": """Поздравляем! Вы добрались до выпускного испытания.
Настоящее мастерство программиста на C/C++ проверяется умением реализовать фундаментальные структуры данных с нуля, без помощи STL.

Архитектура динамического массива (Custom Vector):
1. Три ключевых поля:
   - T *data_: указатель на непрерывную область памяти в куче.
   - size_t size_: текущее количество реально хранящихся элементов.
   - size_t capacity_: максимальная вместимость выделенного буфера.
2. Стратегия реаллокации (Geometric Expansion):
   Когда size_ == capacity_, мы выделяем новый буфер ВДВОЕ большего размера (new_cap = capacity_ * 2), перемещаем старые элементы и освобождаем старый буфер. Это дает амортизированную стоимость вставки O(1)!
3. Деструктор:
   Обязан освобождать delete[] data_.
4. Правило пяти (Rule of 5):
   Поскольку класс владеет сырым ресурсом памяти, необходимо явно реализовать или запретить копирование, чтобы избежать Double Free!""",
        "task": "Реализуйте упрощенный класс SimpleVector:\n- конструктор по умолчанию (size_ = 0, capacity_ = 2, data_ = new int[2])\n- деструктор delete[] data_\n- метод void push_back(int val) с автоматическим удвоением capacity при заполнении\n- метод int at(size_t index) const\nВ main добавьте числа 10, 20, 30 и выведите:\nVector size: 3, at(2) = 30",
        "initialCode": """#include <iostream>

class SimpleVector {
private:
    int *data_;
    size_t size_;
    size_t capacity_;

public:
    SimpleVector() : size_(0), capacity_(2), data_(new int[2]) {}
    ~SimpleVector() { delete[] data_; }

    void push_back(int val) {
        // Если size_ == capacity_, увеличьте capacity в 2 раза,
        // выделите новый массив, скопируйте данные, удалите старый.
        // Затем добавьте val и увеличьте size_.
    }

    int at(size_t index) const {
        return data_[index];
    }

    size_t size() const { return size_; }
};

int main() {
    SimpleVector v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    std::cout << "Vector size: " << v.size() << ", at(2) = " << v.at(2) << std::endl;
    return 0;
}
""",
        "solution": """#include <iostream>

class SimpleVector {
private:
    int *data_;
    size_t size_;
    size_t capacity_;

public:
    SimpleVector() : size_(0), capacity_(2), data_(new int[2]) {}
    ~SimpleVector() { delete[] data_; }

    void push_back(int val) {
        if (size_ == capacity_) {
            size_t new_cap = capacity_ * 2;
            int *new_data = new int[new_cap];
            for (size_t i = 0; i < size_; i++) {
                new_data[i] = data_[i];
            }
            delete[] data_;
            data_ = new_data;
            capacity_ = new_cap;
        }
        data_[size_++] = val;
    }

    int at(size_t index) const {
        return data_[index];
    }

    size_t size() const { return size_; }
};

int main() {
    SimpleVector v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    std::cout << "Vector size: " << v.size() << ", at(2) = " << v.at(2) << std::endl;
    return 0;
}
""",
        "hints": [
            "При size_ == capacity_ выделите new int[capacity_ * 2];",
            "Скопируйте старые элементы, вызовите delete[] data_; и обновите указатель.",
            "data_[size_++] = val;"
        ],
        "testInputs": [],
        "expectedOutput": "Vector size: 3, at(2) = 30\n"
    }
]

# Write JSON for web preview and general usage
json_path = "/home/user/TrainerCode/web_preview/public/lessons.json"
with open(json_path, "w", encoding="utf-8") as f:
    json.dump(lessons, f, ensure_ascii=False, indent=2)

print(f"Generated {len(lessons)} lessons into {json_path}")

# Generate C++ header for native application
def escape_cpp(s):
    # Escape backslashes, quotes, and newlines
    res = s.replace('\\', '\\\\').replace('"', '\\"').replace('\n', '\\n"\n    "')
    return f'"{res}"'

hpp_path = "/home/user/TrainerCode/src_win32/lessons_data.hpp"
with open(hpp_path, "w", encoding="utf-8") as f:
    f.write("""#pragma once
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
""")
    for les in lessons:
        f.write("    {\n")
        f.write("        Lesson l;\n")
        f.write(f"        l.id = {les['id']};\n")
        # We write helper function to convert UTF-8 literals to wstring
        f.write(f"        l.module_name = L{escape_cpp(les['module'])};\n")
        f.write(f"        l.title = L{escape_cpp(les['title'])};\n")
        f.write(f"        l.lang = L{escape_cpp(les['lang'])};\n")
        f.write(f"        l.difficulty = L{escape_cpp(les['difficulty'])};\n")
        f.write(f"        l.theory = L{escape_cpp(les['theory'])};\n")
        f.write(f"        l.task = L{escape_cpp(les['task'])};\n")
        f.write(f"        l.initial_code = L{escape_cpp(les['initialCode'])};\n")
        f.write(f"        l.solution = L{escape_cpp(les['solution'])};\n")
        f.write(f"        l.expected_output = L{escape_cpp(les['expectedOutput'])};\n")
        for h in les['hints']:
            f.write(f"        l.hints.push_back(L{escape_cpp(h)});\n")
        f.write("        list.push_back(l);\n")
        f.write("    }\n")
    f.write("""    return list;
}
""")

print(f"Generated {hpp_path}")
