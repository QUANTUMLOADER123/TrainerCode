# -*- coding: utf-8 -*-
import json
import os

lessons = [
    {
        "id": 1,
        "title": "Урок 1: Архитектура ЭВМ, память и первая программа",
        "lang": "C",
        "difficulty": "Новичок",
        "theoryPart1": """Добро пожаловать в элитную школу системного программирования TrainerCode!

Языки C и C++ — это фундамент операционных систем (Windows, Linux), игровых движков (Unreal Engine), античитов, драйверов и высокопроизводительного софта. В отличие от Python или Java, здесь нет интерпретатора и виртуальной машины. Код компилируется напрямую в машинные инструкции процессора (x86/x64).

Как устроен компьютер:
1. Процессор (CPU): Выполняет инструкции (MOV, ADD, JMP, CALL) на тактовой частоте миллиарды раз в секунду. Внутри CPU есть свербыстрые ячейки — регистры (RAX, RBX, RCX, RDX, RSP, RIP).
2. Оперативная память (RAM): Огромный массив байт. Каждый байт имеет свой уникальный числовой адрес (например, 0x00401000).
3. Точка входа в программу: В операционной системе процесс запускается с функции main().
   Синтаксис в C:
   #include <stdio.h>

   int main(void) {
       printf("Hello, TrainerCode!\\n");
       return 0;
   }

Препроцессор (#include <stdio.h>): директива, которая перед компиляцией вставляет объявления стандартных функций ввода-вывода (printf).
printf("...\\n"): выводит текст в стандартный поток вывода (консоль). '\\n' — символ перевода строки.
return 0;: возвращает операционной системе код 0, что означает: "Программа завершилась штатно и без ошибок".""",
        "quiz": {
            "question": "Что означает директива `#include <stdio.h>` и зачем в конце `main` пишется `return 0;`?",
            "options": [
                {
                    "id": "a",
                    "text": "#include подключает стандартную библиотеку ввода-вывода, а return 0 сообщает ОС об успешном завершении",
                    "correct": True,
                    "explanation": "Верно! #include подключает заголовок stdio.h для printf, а код возврата 0 является стандартным сигналом успеха для операционной системы."
                },
                {
                    "id": "b",
                    "text": "Это объявление глобальной переменной для выделения 0 байт памяти",
                    "correct": False,
                    "explanation": "Неверно. #include — директива препроцессора, а return 0 возвращает код завершения из main."
                },
                {
                    "id": "c",
                    "text": "return 0 перезагружает компьютер в безопасном режиме",
                    "correct": False,
                    "explanation": "Конечно нет. return 0 просто завершает процесс с кодом выхода 0."
                }
            ]
        },
        "theoryPart2": """Закрепление материала:
Компилятор превращает ваш C-код в машинный файл формата PE (.exe на Windows) или ELF (на Linux).
В Windows структура программы включает:
- Секция .text: исполняемый машинный код
- Секция .data: глобальные инициализированные переменные
- Секция .rdata: строковые константы (read-only)

Теперь напишите вашу первую программу в редакторе кода!""",
        "task": "Напишите программу на Си, которая выводит:\nTrainerCode 2000 System Active\nTarget CPU: x86_64\nи возвращает 0.",
        "initialCode": """#include <stdio.h>

int main(void) {
    // Выведите требуемый текст:
    
    return 0;
}
""",
        "solution": """#include <stdio.h>

int main(void) {
    printf("TrainerCode 2000 System Active\\n");
    printf("Target CPU: x86_64\\n");
    return 0;
}
""",
        "hints": [
            "Используйте printf с символом '\\n' в конце каждой строки.",
            "Проверьте регистр букв: TrainerCode 2000 System Active"
        ],
        "expectedOutput": "TrainerCode 2000 System Active\nTarget CPU: x86_64\n"
    },
    {
        "id": 2,
        "title": "Урок 2: Фундаментальные типы данных, память и sizeof",
        "lang": "C",
        "difficulty": "Новичок",
        "theoryPart1": """Память компьютера дискретна: минимальная адресуемая ячейка — 1 байт (8 бит).
В Си каждый тип данных занимает фиксированное число байт:

1. Целочисленные типы:
- char (1 байт = 8 бит): от -128 до 127 (символ ASCII или маленькое число).
- unsigned char (1 байт): от 0 до 255.
- short (2 байта = 16 бит): от -32,768 до 32,767.
- int (4 байта = 32 бита): от -2,147,483,648 до 2,147,483,647 (~2 миллиарда).
- unsigned int (4 байта): от 0 до 4,294,967,295 (~4 миллиарда).
- long long (8 байт = 64 бита): от -9*10^18 до 9*10^18.
- unsigned long long (8 байт): до 18*10^18.

2. Дробные типы (с плавающей точкой IEEE 754):
- float (4 байта): ~7 десятичных цифр точности.
- double (8 байт): ~15-17 цифр точности.

3. Оператор sizeof:
Оператор sizeof(тип_или_переменная) возвращает точный размер в байтах.
Спецификатор для вывода sizeof в printf — %zu.

Спецификаторы printf:
%d — знаковый int
%u — беззнаковый unsigned int
%lld — long long
%f — float / double
%c — символ char
%p — адрес указателя в шестнадцатеричном виде (hex)""",
        "quiz": {
            "question": "Сколько байт занимает тип int на 64-битной архитектуре x86_64 и какой диапазон у unsigned char?",
            "options": [
                {
                    "id": "a",
                    "text": "int занимает 4 байта, а unsigned char имеет диапазон от 0 до 255",
                    "correct": True,
                    "explanation": "Абсолютно верно! В стандартных моделях данных (LLP64 на Windows и LP64 на Linux) int равен 32 битам (4 байта), а 8-битный unsigned char хранит числа от 0 до 2^8 - 1 = 255."
                },
                {
                    "id": "b",
                    "text": "int занимает 8 байт, а unsigned char от -128 до 127",
                    "correct": False,
                    "explanation": "Неверно. 8 байт занимает long long. А unsigned char не может быть отрицательным."
                },
                {
                    "id": "c",
                    "text": "int занимает 1 байт, unsigned char от 0 до 100",
                    "correct": False,
                    "explanation": "Неверно. 1 байт занимает char."
                }
            ]
        },
        "theoryPart2": """Внимание: Переполнение чисел (Integer Overflow):
Если к signed int прибавить единицу при значении 2,147,483,647, произойдет переполнение в отрицательное число -2,147,483,648 (Undefined Behavior в Си).
Для системного программиста критично понимать точные размеры типов!""",
        "task": "Объявите переменные:\n- int health = 100;\n- double armor = 45.5;\n- unsigned char level = 5;\nВыведите их значения и размеры в байтах (через sizeof):\nHealth: 100 (4 bytes)\nArmor: 45.50 (8 bytes)\nLevel: 5 (1 bytes)",
        "initialCode": """#include <stdio.h>

int main(void) {
    // Объявите переменные и напечатайте результат:
    
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
            "Используйте %.2f для вывода armor с двумя знаками после запятой.",
            "Используйте %zu для вывода размера sizeof."
        ],
        "expectedOutput": "Health: 100 (4 bytes)\nArmor: 45.50 (8 bytes)\nLevel: 5 (1 bytes)\n"
    },
    {
        "id": 3,
        "title": "Урок 3: Функции, аргументы и Стек Вызовов (Call Stack)",
        "lang": "C",
        "difficulty": "Новичок",
        "theoryPart1": """Что такое функция?
Функция — это изолированный фрагмент кода с именем, входными аргументами и возвращаемым значением:
int calculate_damage(int base_dmg, int armor) {
    return base_dmg - armor;
}

Как работает передача аргументов в Си:
В языке Си ВСЕ аргументы передаются ИСКЛЮЧИТЕЛЬНО ПО ЗНАЧЕНИЮ (Pass by Value).
Когда вы передаете переменную в функцию, в памяти создается её ТОЧНАЯ КОПИЯ.
Если изменить аргумент внутри функции:
void try_change(int x) {
    x = 999; // изменится только локальная копия!
}
Оригинальная переменная в вызвавшей функции останется нетронутой!

Стек вызовов (Call Stack):
При каждом вызове функции процессор резервирует память на стеке (Stack Frame):
- Регистр RSP (указатель вершины стека) сдвигается вниз.
- На стек помещается адрес возврата (куда вернуться после команды RET).
- Размещаются локальные переменные функции.
Когда функция завершается (return), её фрейм мгновенно уничтожается!""",
        "quiz": {
            "question": "Если передать обычную переменную int a = 10 в функцию void foo(int a) { a = 50; }, изменится ли a в main()?",
            "options": [
                {
                    "id": "a",
                    "text": "Нет, не изменится, потому что в C аргументы передаются по значению (создается копия на стеке)",
                    "correct": True,
                    "explanation": "Верно! В языке C все передается по значению. Чтобы изменить оригинал, потребуется передать адрес переменной (указатель)."
                },
                {
                    "id": "b",
                    "text": "Да, изменится на 50, так как имя переменной совпадает",
                    "correct": False,
                    "explanation": "Неверно. Область видимости аргумента ограничена телом функции foo, это независимая копия."
                }
            ]
        },
        "theoryPart2": """Области видимости:
Локальные переменные живут на стеке только пока выполняется блок { }.
Если перед локальной переменной поставить ключевое слово static:
static int counter = 0;
Она переместится со стека в глобальный сегмент данных .data и сохранит свое значение между вызовами функции!""",
        "task": "Напишите функцию int apply_bonus(int score, int multiplier), которая возвращает score * multiplier.\nВ main вызовите ее для score = 150 и multiplier = 3 и выведите:\nFinal Score: 450",
        "initialCode": """#include <stdio.h>

// Напишите функцию apply_bonus здесь:

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
            "Сигнатура функции: int apply_bonus(int score, int multiplier)",
            "В теле функции верните score * multiplier;"
        ],
        "expectedOutput": "Final Score: 450\n"
    },
    {
        "id": 4,
        "title": "Урок 4: Ключевое слово inline, макросы и оптимизации",
        "lang": "C",
        "difficulty": "Средний",
        "theoryPart1": """Накладные расходы на вызов функции:
Когда процессор вызывает обычную функцию, происходят машинные операции:
1. Запись регистров-аргументов (RCX, RDX, R8, R9 по соглашению fastcall).
2. Инструкция CALL: сохранение адреса возврата на вершину стека.
3. Пролог функции (push rbp, mov rbp, rsp).
4. Тело функции.
5. Эпилог функции (pop rbp).
6. Инструкция RET: снятие адреса со стека и прыжок обратно.
Для крошечных функций из 1-2 строк эти накладные расходы могут занимать больше времени, чем сами полезные вычисления!

Ключевое слово inline:
inline int square(int x) {
    return x * x;
}
Ключевое слово inline — это указание компилятору: «Не делай CALL/RET, а просто вставь тело функции прямо в место вызова!».
В результате машинный код работает с максимальной скоростью, без работы со стеком.

Макросы препроцессора (#define):
#define MAX(a, b) ((a) > (b) ? (a) : (b))
Макросы заменяют текст ДО компиляции. Внимание: в макросах всегда оборачивайте параметры в скобки, иначе возможны баги с приоритетом операций.""",
        "quiz": {
            "question": "Какова главная цель спецификатора inline перед функцией?",
            "options": [
                {
                    "id": "a",
                    "text": "Устранить накладные расходы на инструкции CALL/RET путем подстановки тела функции прямо в точку вызова",
                    "correct": True,
                    "explanation": "Именно! Компилятор подставляет машинный код на месте, экономя такты процессора на работу со стеком."
                },
                {
                    "id": "b",
                    "text": "Запретить компилятору использовать оптимизацию",
                    "correct": False,
                    "explanation": "Наоборот, inline является хинтом оптимизации."
                }
            ]
        },
        "theoryPart2": """В современном C/C++ компиляторы (GCC/MSVC) при включенных флагах оптимизации -O2 / /O2 часто сами решают, какие функции заинлайнить.
Спецификатор inline также необходим в C++, если вы определяете функцию в .h заголовочном файле, чтобы избежать ошибки линковщика multiple definition.""",
        "task": "Напишите inline функцию:\nstatic inline int clamp(int val, int min, int max)\nкоторая возвращает min если val < min, max если val > max, иначе val.\nВ main проверьте: clamp(150, 0, 100) и clamp(-20, 0, 100):\nClamped 1: 100\nClamped 2: 0",
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
            "static inline int clamp(int val, int min, int max)",
            "if (val < min) return min; if (val > max) return max; return val;"
        ],
        "expectedOutput": "Clamped 1: 100\nClamped 2: 0\n"
    },
    {
        "id": 5,
        "title": "Урок 5: Побитовые операции, битовые сдвиги и флаги",
        "lang": "C",
        "difficulty": "Средний",
        "theoryPart1": """Побитовые операции — это хлеб системного программиста, разработчика драйверов и трейнеров. Они работают напрямую с битами в регистрах процессора за 1 такт!

Операторы:
1. & (Побитовое И / AND):
   1 & 1 = 1, иначе 0. Применяется для проверки или маскирования битов.
2. | (Побитовое ИЛИ / OR):
   0 | 0 = 0, если хоть один бит равен 1, то 1. Применяется для установки флагов.
3. ^ (Исключающее ИЛИ / XOR):
   1 ^ 1 = 0, 0 ^ 0 = 0, разные биты дают 1. Применяется для инвертирования или шифрования.
4. ~ (Побитовое НЕ / NOT):
   Инвертирует все биты числа (0 становится 1, 1 становится 0).
5. << (Сдвиг влево):
   x << n сдвигает биты влево на n позиций (эквивалентно умножению на 2^n).
6. >> (Сдвиг вправо):
   x >> n делит на 2^n.

Идиомы системного программирования:
- Установить n-й бит: flags |= (1U << n);
- Сбросить n-й бит: flags &= ~(1U << n);
- Проверить n-й бит: if (flags & (1U << n)) { ... }
- Переключить n-й бит: flags ^= (1U << n);""",
        "quiz": {
            "question": "Какое выражение устанавливает 3-й бит числа flags в 1, не меняя остальные биты?",
            "options": [
                {
                    "id": "a",
                    "text": "flags |= (1 << 3);",
                    "correct": True,
                    "explanation": "Верно! 1 << 3 формирует маску с единицей в третьем бите (0b00001000 = 8), а побитовое ИЛИ (|) устанавливает этот бит в 1."
                },
                {
                    "id": "b",
                    "text": "flags &= ~(1 << 3);",
                    "correct": False,
                    "explanation": "Это выражение сбрасывает (обнуляет) 3-й бит, а не устанавливает."
                },
                {
                    "id": "c",
                    "text": "flags = flags + 3;",
                    "correct": False,
                    "explanation": "Обычное сложение сломает остальные биты при переносе разряда."
                }
            ]
        },
        "theoryPart2": """В операционной системе Windows права доступа к памяти и процессам кодируются битовыми масками:
PROCESS_VM_READ (0x0010), PROCESS_VM_WRITE (0x0020), PROCESS_VM_OPERATION (0x0008).
Объединяя их через |, мы получаем комбинированный флаг:
DWORD desired_access = PROCESS_VM_READ | PROCESS_VM_WRITE;""",
        "task": "Дана переменная unsigned int flags = 0;\n1. Установите бит 2 (значение 4) и бит 4 (значение 16).\n2. Выведите получившееся десятичное число.\n3. Сбросьте бит 2 и выведите результат.\nОжидаемый вывод:\nFlags with bits 2 and 4: 20\nFlags after clearing bit 2: 16",
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
            "Установка бита n: flags |= (1 << n);",
            "Сброс бита n: flags &= ~(1 << n);"
        ],
        "expectedOutput": "Flags with bits 2 and 4: 20\nFlags after clearing bit 2: 16\n"
    },
    {
        "id": 6,
        "title": "Урок 6: УКАЗАТЕЛИ (Pointers) — Фундамент Си и Реверсинга",
        "lang": "C",
        "difficulty": "Средний",
        "theoryPart1": """ВНИМАНИЕ! Этот урок — самый важный во всем курсе.
Понимание указателей отличает настоящего системного программиста от любителя.

Что такое указатель?
Указатель — это переменная, значением которой является АДРЕС в оперативной памяти другого объекта!

Два базовых оператора:
1. Оператор & (Address-of — взятие адреса):
   int health = 100;
   // Переменная health лежит в памяти, например, по адресу 0x0019FF2C.
   int *ptr = &health; // В ptr теперь записан адрес 0x0019FF2C!

2. Оператор * (Dereference — разыменование):
   Оператор * заставляет процессор пойти по адресу, хранящемуся в указателе, и прочитать/записать значение.
   *ptr = 250; // Мы изменили значение переменной health на 250 через ее адрес!

Размер указателя:
На 32-битных системах указатель занимает 4 байта.
На 64-битных системах (x86_64) указатель занимает 8 байт (так как адреса 64-битные).
Тип указателя (int*, char*, double*) указывает компилятору, сколько байт читать/писать при разыменовании!""",
        "quiz": {
            "question": "Если int x = 42; int *p = &x; что произойдет при выполнении *p = 99;?",
            "options": [
                {
                    "id": "a",
                    "text": "Значение переменной x изменится на 99, потому что p хранит ее адрес памяти",
                    "correct": True,
                    "explanation": "Блестяще! Оператор * разыменовывает указатель p и записывает 99 непосредственно в ячейку памяти переменной x."
                },
                {
                    "id": "b",
                    "text": "Изменится адрес самого указателя p, а x останется равным 42",
                    "correct": False,
                    "explanation": "Неверно. Адрес изменился бы при p = ..., а запись *p = ... меняет целевой объект."
                }
            ]
        },
        "theoryPart2": """NULL и висячие указатели (Dangling Pointers):
Если указатель равен NULL (0x00000000), разыменование (*ptr) вызовет фатальное аппаратное исключение процессора:
EXCEPTION_ACCESS_VIOLATION (0xC0000005) на Windows или Segmentation fault на Linux.
Всегда проверяйте указатели перед разыменованием!""",
        "task": "Напишите функцию void add_gold(int *player_gold, int amount), которая через указатель увеличивает золото игрока.\nВ main создайте int gold = 500;, вызовите add_gold(&gold, 250) и напечатайте:\nPlayer Gold: 750",
        "initialCode": """#include <stdio.h>

// Напишите функцию add_gold здесь:

int main(void) {
    int gold = 500;
    // Вызовите add_gold, передав адрес:
    
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
            "Сигнатура: void add_gold(int *player_gold, int amount)",
            "Внутри функции: *player_gold += amount;",
            "При вызове передайте адрес: add_gold(&gold, 250);"
        ],
        "expectedOutput": "Player Gold: 750\n"
    },
    {
        "id": 7,
        "title": "Урок 7: Адресная арифметика, void* и байтовые смещения",
        "lang": "C",
        "difficulty": "Средний",
        "theoryPart1": """Адресная арифметика (Pointer Arithmetic):
Когда вы прибавляете число k к указателю ptr:
ptr + k
Адрес в памяти увеличивается НЕ на k байт, а на:
k * sizeof(*ptr) байт!

Пример:
int arr[3] = {10, 20, 30};
int *p = arr; // указывает на arr[0] (допустим адрес 0x1000)
p + 1;        // адрес станет 0x1004! Потому что sizeof(int) == 4.

Универсальный указатель void*:
void* — это сырой бестиповый указатель на память.
Он может хранить адрес любого объекта (int, float, struct).
Однако void* НЕЛЬЗЯ разыменовать напрямую (*p — ошибка компиляции), потому что компилятор не знает тип и размер данных!
Перед разыменованием void* необходимо явно привести к нужному типу:
int val = *(int*)raw_ptr;

Указатели на байты (unsigned char*):
В реверс-инжиниринге и трейнерах адреса часто приводят к unsigned char* (или uintptr_t), потому что sizeof(unsigned char) == 1 байт. Это позволяет сдвигаться по памяти ровно на заданное количество байт (Offset)!""",
        "quiz": {
            "question": "Если указатель int *ptr равен адресу 0x2000, чему будет равен адрес выражения ptr + 2 (при sizeof(int) = 4)?",
            "options": [
                {
                    "id": "a",
                    "text": "0x2008 (сместится на 2 * 4 = 8 байт)",
                    "correct": True,
                    "explanation": "Верно! Адресная арифметика умножает приращение на размер базового типа (2 * 4 = 8 байт в шестнадцатеричной системе)."
                },
                {
                    "id": "b",
                    "text": "0x2002 (сместится ровно на 2 байта)",
                    "correct": False,
                    "explanation": "Неверно. На 2 байта сместился бы указатель типа char*."
                }
            ]
        },
        "theoryPart2": """Указатель на указатель (Двойной указатель, **ptr):
Переменная, которая хранит адрес ДРУГОГО указателя.
Используется, когда функции нужно изменить сам адрес указателя (например, при выделении динамической памяти).""",
        "task": "Дан массив int numbers[4] = {11, 22, 33, 44};\nИспользуя указатель int *ptr = numbers; и адресную арифметику (ptr + 2), прочитайте и выведите третий элемент массива:\nThird element via pointer: 33",
        "initialCode": """#include <stdio.h>

int main(void) {
    int numbers[4] = {11, 22, 33, 44};
    int *ptr = numbers;

    // Получите третий элемент через *(ptr + 2):
    int val = 0;
    
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
            "arr[i] абсолютно эквивалентно *(ptr + i)",
            "Для третьего элемента используйте *(ptr + 2)."
        ],
        "expectedOutput": "Third element via pointer: 33\n"
    },
    {
        "id": 8,
        "title": "Урок 8: Динамическая память в куче (Heap): malloc и free",
        "lang": "C",
        "difficulty": "Средний",
        "theoryPart1": """Стек vs Куча (Stack vs Heap):
- Стек (Stack): Размер фиксирован (~1-2 МБ). Переменные создаются мгновенно, но удаляются при выходе из функции.
- Куча (Heap): Вся свободная оперативная память компьютера (гигабайты). Выделяется и освобождается вручную разработчиком во время работы программы (Runtime).

Функции работы с кучей (<stdlib.h>):
1. malloc(size_t size):
   Выделяет блок памяти указанного размера в байтах. Возвращает void* на начало блока или NULL, если память не удалось выделить.
   Внимание: malloc НЕ очищает память, там лежит старый 'мусор'!
   int *arr = (int*)malloc(10 * sizeof(int));

2. free(void *ptr):
   Возвращает выделенный блок операционной системе.
   После free(ptr) переменная ptr становится «висячим указателем» (Dangling Pointer). Хорошая практика: сразу занулять его: ptr = NULL;

Смертные грехи:
- Утечка памяти (Memory Leak): забыли вызвать free(). Программа пожирает RAM до зависания ПК.
- Double Free: вызов free(ptr) дважды для одного адреса — краш кучи (Heap Corruption).
- Use-After-Free: чтение или запись по указателю после вызова free.""",
        "quiz": {
            "question": "Что произойдет, если в цикле вызывать malloc() и не вызывать free()?",
            "options": [
                {
                    "id": "a",
                    "text": "Утечка памяти (Memory Leak): программа постепенно потребит всю доступную память системы",
                    "correct": True,
                    "explanation": "Верно. Операционная система не освобождает кучу сама до завершения процесса, поэтому память утекает."
                },
                {
                    "id": "b",
                    "text": "Компилятор автоматически вставит free в конце цикла",
                    "correct": False,
                    "explanation": "В языке Си нет сборщика мусора и авто-free."
                }
            ]
        },
        "theoryPart2": """Безопасный паттерн работы с динамической памятью:
1. Всегда проверять результат malloc на NULL:
   if (buf == NULL) { /* обработка нехватки памяти */ }
2. Освобождать память строго в том же модуле/контексте, где она была создана.
3. Присваивать NULL после free.""",
        "task": "Выделите в куче массив из 3 целых чисел с помощью malloc.\nЗапишите в них числа: 10, 20, 30.\nВычислите их сумму и выведите:\nAllocated sum: 60\nЗатем освободите память через free().",
        "initialCode": """#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // 1. Выделите память под 3 int через malloc
    
    // 2. Проверьте на NULL
    
    // 3. Заполните массив и найдите сумму
    
    // 4. Освободите память
    
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
    arr = NULL;
    return 0;
}
""",
        "hints": [
            "int *arr = (int*)malloc(3 * sizeof(int));",
            "Обязательно вызовите free(arr); в конце."
        ],
        "expectedOutput": "Allocated sum: 60\n"
    },
    {
        "id": 9,
        "title": "Урок 9: Структуры (struct), объединения и выравнивание (Padding)",
        "lang": "C",
        "difficulty": "Средний",
        "theoryPart1": """Структура (struct) — это пользовательский составной тип, объединяющий поля разных типов под одной крышей.

Объявление:
typedef struct {
    char name[32];
    int health;
    float speed;
} Entity;

Доступ к полям:
1. Через точку (.), если у нас сам объект:
   Entity player;
   player.health = 100;

2. Через стрелку (->), если у нас УКАЗАТЕЛЬ на структуру:
   Entity *ptr = &player;
   ptr->health = 100; // эквивалентно (*ptr).health = 100

Выравнивание данных в памяти (Structure Padding):
Процессоры x86/x64 читают память порциями по 4 или 8 байт.
Поэтому компилятор выравнивает поля структуры, вставляя невидимые пустые байты (Padding)!
Пример:
struct Test {
    char c; // 1 байт + 3 байта padding!
    int x;  // 4 байта
};
Размер sizeof(struct Test) равен 8 байтам, а не 5!
Для упаковки структур в сетевых пакетах и структурах памяти процессов используется директива #pragma pack(push, 1).""",
        "quiz": {
            "question": "Если у нас есть указатель Entity *p, как правильно обратиться к его полю health?",
            "options": [
                {
                    "id": "a",
                    "text": "p->health (или (*p).health)",
                    "correct": True,
                    "explanation": "Верно! Оператор стрелочки (->) совмещает разыменование указателя и доступ к полю структуры."
                },
                {
                    "id": "b",
                    "text": "p.health",
                    "correct": False,
                    "explanation": "Неверно. Точка используется только когда переменная является самим объектом, а не указателем."
                }
            ]
        },
        "theoryPart2": """В игровых движках и системных процессах сущности (игроки, боты, снаряды) всегда представлены структурами в памяти. Зная смещение (Offset) поля health внутри структуры, можно модифицировать здоровье персонажа прямо в ОЗУ!""",
        "task": "Создайте структуру PlayerData с полями: int id, int hp, int ammo.\nНапишите функцию void heal(PlayerData *p, int amount), которая через стрелку -> увеличивает p->hp на amount.\nВ main создайте PlayerData p = {1, 50, 30};, вызовите heal(&p, 50) и выведите:\nPlayer ID 1 HP: 100",
        "initialCode": """#include <stdio.h>

// Объявите структуру PlayerData и функцию heal:

int main(void) {
    PlayerData p = {1, 50, 30};
    // Вызовите heal(&p, 50) и напечатайте результат:
    
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
            "Используйте typedef struct { int id; int hp; int ammo; } PlayerData;",
            "В функции: p->hp += amount;"
        ],
        "expectedOutput": "Player ID 1 HP: 100\n"
    },
    {
        "id": 10,
        "title": "Урок 10: Переход к C++: классы, инкапсуляция и ссылки &",
        "lang": "C++",
        "difficulty": "Средний",
        "theoryPart1": """Язык C++ создавался как 'C с классами'. C++ сохраняет всю низкоуровневую мощь Си, но добавляет Объектно-Ориентированное Программирование (ООП) с нулевыми накладными расходами (Zero-Cost Abstractions).

Ссылки (References, &):
В C++ появилась ссылка — безопасный псевдоним существующего объекта:
void modify(int &ref) {
    ref = 500; // меняет оригинальную переменную без указателей и *!
}
В отличие от указателей, ссылка:
- Не может быть нулевой (nullptr).
- Не может быть перепривязана к другому объекту.

Классы (class) в C++:
Класс объединяет данные (поля) и функции (методы).
Спецификаторы доступа:
- private: доступно только методам самого класса (скрытая реализация).
- public: внешний интерфейс.

Конструктор и деструктор:
- Конструктор: вызывается автоматически при рождении объекта.
- Деструктор (~ClassName): вызывается автоматически при выходе из области видимости { } или при delete. Это основа идиомы RAII!""",
        "quiz": {
            "question": "В чем главное отличие ссылки (int &ref) от указателя (int *ptr)?",
            "options": [
                {
                    "id": "a",
                    "text": "Ссылка не может быть nullptr, инициализируется один раз и не требует оператора разыменования (*)",
                    "correct": True,
                    "explanation": "Верно! Ссылка — это синтаксический псевдоним переменной, гарантирующий валидность объекта."
                },
                {
                    "id": "b",
                    "text": "Ссылка занимает 100 байт памяти и работает медленнее указателя",
                    "correct": False,
                    "explanation": "На машинном уровне ссылка компилируется в тот же самый указатель, накладных расходов ноль."
                }
            ]
        },
        "theoryPart2": """Указатель this:
Внутри любого нестатического метода класса неявно доступен указатель this, хранящий адрес текущего экземпляра объекта в памяти.""",
        "task": "Создайте класс SafeBox с private полем int secret_.\nСделайте public конструктор SafeBox(int code) и метод int getSecret() const.\nВ main создайте SafeBox box(777); и выведите:\nSecret Code: 777",
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
            "private: int secret_;",
            "public: SafeBox(int code) : secret_(code) {}"
        ],
        "expectedOutput": "Secret Code: 777\n"
    },
    {
        "id": 11,
        "title": "Урок 11: Умные указатели Modern C++ (std::unique_ptr, RAII)",
        "lang": "C++",
        "difficulty": "Продвинутый",
        "theoryPart1": """Сырые указатели с new и delete — главный источник критических уязвимостей в ПО (70% всех уязвимостей Microsoft и Google происходят из-за ошибок управления памятью).
Modern C++ (начиная с C++11) решил эту проблему раз и навсегда концепцией RAII и Умными Указателями (<memory>).

RAII (Resource Acquisition Is Initialization):
Ресурс (память, файл, хэндл процесса) захватывается в конструкторе и гарантированно освобождается в деструкторе, даже если в программе выброшено исключение!

std::unique_ptr:
- Единоличное владение объектом в куче.
- При выходе unique_ptr из области видимости { }, он автоматически вызывает delete!
- Нулевые накладные расходы (размер ровно 8 байт, как у сырого указателя).
- Создание:
  #include <memory>
  auto ptr = std::make_unique<int>(100);

std::shared_ptr:
- Разделяемое владение со счетчиком ссылок (Reference Count).
- Объект удаляется только когда последний shared_ptr уничтожен.""",
        "quiz": {
            "question": "Почему в Modern C++ рекомендуется предпочитать std::unique_ptr вместо сырого `new` / `delete`?",
            "options": [
                {
                    "id": "a",
                    "text": "unique_ptr автоматически освобождает память в деструкторе, предотвращая утечки памяти и не создавая накладных расходов",
                    "correct": True,
                    "explanation": "Абсолютно верно! Принцип RAII гарантирует освобождение ресурсов при выходе из скобок {} без риска забыть delete."
                },
                {
                    "id": "b",
                    "text": "unique_ptr делает программу на 500% быстрее",
                    "correct": False,
                    "explanation": "Скорость ровно такая же, как у сырого указателя (Zero-Cost)."
                }
            ]
        },
        "theoryPart2": """unique_ptr нельзя скопировать (конструктор копирования удален), но можно передать владение через std::move:
std::unique_ptr<int> p2 = std::move(ptr); // ptr станет nullptr, а p2 завладеет объектом.""",
        "task": "Используя std::make_unique, выделите в куче число int со значением 4096.\nРазыменуйте его и напечатайте:\nUnique value: 4096",
        "initialCode": """#include <iostream>
#include <memory>

int main() {
    // Создайте unique_ptr с помощью std::make_unique:
    
    // Разыменуйте и выведите:
    
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
            "auto ptr = std::make_unique<int>(4096);",
            "Выведите: *ptr"
        ],
        "expectedOutput": "Unique value: 4096\n"
    },
    {
        "id": 12,
        "title": "Урок 12: Введение в Windows API (WinAPI) и типы Win32",
        "lang": "C++",
        "difficulty": "Продвинутый",
        "theoryPart1": """Добро пожаловать в высшую лигу системного программирования для Windows!
Windows API (WinAPI) — это интерфейс ядра и подсистем Microsoft Windows. Именно на WinAPI написаны системные утилиты, античиты, дебаггеры, трейнеры и сам интерфейс Windows.

Подключение:
#include <windows.h>

Фундаментальные типы Win32 (псевдонимы в windows.h):
- BOOL: целое число (TRUE = 1, FALSE = 0).
- BYTE: беззнаковый 8-битный байт (unsigned char).
- WORD: 16-битное число (2 байта).
- DWORD: Double Word — 32-битное число (4 байта, unsigned long).
- QWORD: Quad Word — 64-битное число (8 байт).
- LPVOID: Long Pointer to Void (void*) — сырой указатель на память.
- LPCSTR: const char* (указатель на строку ANSI).
- LPCWSTR: const wchar_t* (указатель на Unicode UTF-16 строку).
- HANDLE: Непрозрачный числовой дескриптор системного ресурса (процесса, потока, файла, мьютекса) в таблице ядра операционной системы!
- HWND: Дескриптор окна.

Обработка ошибок:
Большинство функций WinAPI в случае ошибки возвращают 0 или NULL.
Чтобы узнать точную причину ошибки, вызывается функция GetLastError(), возвращающая числовой код ошибки (например, ERROR_ACCESS_DENIED = 5).""",
        "quiz": {
            "question": "Что представляет собой тип HANDLE в Windows API?",
            "options": [
                {
                    "id": "a",
                    "text": "Непрозрачный системный дескриптор (индекс в таблице объектов ядра ОС) для управления процессами, файлами или потоками",
                    "correct": True,
                    "explanation": "Верно! HANDLE — это абстрактный токен ядра, выдаваемый операционной системой для безопасного управления ресурсом."
                },
                {
                    "id": "b",
                    "text": "Обычная переменная float для хранения координат мыши",
                    "correct": False,
                    "explanation": "Неверно. HANDLE — ключевой тип дескриптора ядра Windows."
                }
            ]
        },
        "theoryPart2": """Соглашение об именовании в WinAPI:
Многие функции существуют в двух вариантах:
- Функция с суффиксом 'A' (ANSI, char*): MessageBoxA
- Функция с суффиксом 'W' (Wide/Unicode, wchar_t*): MessageBoxW
В современных приложениях всегда рекомендуется использовать Unicode ('W') версию.""",
        "task": "Изучите типы Win32:\nОбъявите переменные:\nDWORD pid = 1337;\nBOOL is_running = 1;\nВыведите в stdout:\nProcess ID: 1337, Status: Active",
        "initialCode": """#include <stdio.h>

// В эмуляции определим Win32 типы:
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
            "Используйте %lu для типа DWORD (unsigned long).",
            "Выведите: Process ID: 1337, Status: Active"
        ],
        "expectedOutput": "Process ID: 1337, Status: Active\n"
    },
    {
        "id": 13,
        "title": "Урок 13: Виртуальная память Windows и права доступа к страницам",
        "lang": "C++",
        "difficulty": "Эксперт",
        "theoryPart1": """Виртуальная память (Virtual Memory Architecture):
В современных операционных системах ни один процесс не обращается к физическим планкам RAM напрямую!
Каждый процесс живет в своем собственном изолированном Виртуальном Адресном Пространстве (Virtual Address Space):
- В 32-битных приложениях: диапазон адресов 0x00000000 .. 0x7FFFFFFF (2 ГБ пространства пользователя).
- В 64-битных приложениях: гигантский диапазон до 128 ТБ (0x0000000000000000 .. 0x7FFFFFFFFFFF)!

Страницы памяти (Pages):
Память делится на страницы фиксированного размера — стандартно 4096 байт (4 КБ).
Процессор (блок MMU) транслирует виртуальные адреса в физические через таблицы страниц (Page Tables).

Флаги защиты страниц памяти (Page Protection):
Каждая страница имеет строгие права доступа:
- PAGE_NOACCESS: обращение запрещено (краш).
- PAGE_READONLY: разрешено только чтение (попытка записи вызывает Access Violation).
- PAGE_READWRITE: чтение и запись (обычная память кучи, стека и переменных).
- PAGE_EXECUTE_READ: исполнение кода и чтение (секция .text программы).
- PAGE_EXECUTE_READWRITE: чтение, запись и исполнение (часто используется для хуков и инъекций шеллкода).

Функции WinAPI:
- VirtualAlloc / VirtualFree: выделение виртуальных страниц.
- VirtualProtect: изменение прав доступа к странице памяти.""",
        "quiz": {
            "question": "Какой стандартный размер страницы памяти в архитектуре x86/x64 Windows?",
            "options": [
                {
                    "id": "a",
                    "text": "4096 байт (4 КБ)",
                    "correct": True,
                    "explanation": "Верно! 4096 байт (0x1000) — стандартный размер страницы виртуальной памяти в архитектуре x86 и x86_64."
                },
                {
                    "id": "b",
                    "text": "64 байта",
                    "correct": False,
                    "explanation": "64 байта — это размер строки кэша процессора (Cache Line), а не страницы памяти."
                }
            ]
        },
        "theoryPart2": """Если попытаться изменить байты в секции кода программы, защищенной PAGE_EXECUTE_READ, программа немедленно упадет с ошибкой 0xC0000005.
Чтобы пропатчить инструкцию в памяти (например, заменить JNE на NOP), трейнеры сначала вызывают VirtualProtect, устанавливают PAGE_EXECUTE_READWRITE, записывают байты и восстанавливают исходную защиту!""",
        "task": "Изучите размер страницы памяти:\nОбъявите константу size_t page_size = 4096;\nВычислите, сколько целых чисел int (по 4 байта) помещается в одну страницу памяти:\nIntegers in 4KB page: 1024",
        "initialCode": """#include <stdio.h>

int main(void) {
    size_t page_size = 4096;
    size_t int_size = sizeof(int);

    // Посчитайте количество:
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
        "id": 14,
        "title": "Урок 14: Процессы в Windows, PID и функция OpenProcess",
        "lang": "C++",
        "difficulty": "Эксперт",
        "theoryPart1": """Идентификатор процесса (Process ID / PID):
Каждому запущенному процессу в Windows операционная система присваивает уникальное число — PID (например, 4820).

Функция OpenProcess:
Чтобы взаимодействовать с чужим процессом (читать память, внедрять поток или изменять переменные), программа должна открыть дескриптор (HANDLE) целевого процесса с помощью функции OpenProcess:

HANDLE OpenProcess(
    DWORD dwDesiredAccess,  // Требуемые права доступа
    BOOL  bInheritHandle,   // Наследование дескриптора (обычно FALSE)
    DWORD dwProcessId       // PID целевого процесса
);

Флаги доступа (dwDesiredAccess):
- PROCESS_VM_READ (0x0010): право читать память процесса (ReadProcessMemory).
- PROCESS_VM_WRITE (0x0020): право записывать в память процесса (WriteProcessMemory).
- PROCESS_VM_OPERATION (0x0008): право модифицировать виртуальную память (VirtualProtectEx).
- PROCESS_ALL_ACCESS (0x1F0FFF): полные права доступа на любые действия.

Закрытие дескриптора:
После завершения работы с процессом дескриптор ОБЯЗАТЕЛЬНО должен быть закрыт:
CloseHandle(hProcess);
Иначе в ядре операционной системы произойдет утечка дескрипторов (Handle Leak)!""",
        "quiz": {
            "question": "Какую функцию Windows API необходимо вызвать после окончания работы с открытым HANDLE процесса?",
            "options": [
                {
                    "id": "a",
                    "text": "CloseHandle(hProcess);",
                    "correct": True,
                    "explanation": "Верно! CloseHandle закрывает дескриптор ядра и предотвращает утечку ресурсов ОС."
                },
                {
                    "id": "b",
                    "text": "free(hProcess);",
                    "correct": False,
                    "explanation": "Неверно. free() освобождает память в куче Си, а дескрипторы ядра закрываются только через CloseHandle."
                }
            ]
        },
        "theoryPart2": """Если OpenProcess вернул NULL, значит доступ не получен.
Типичные причины:
1. Процесс с таким PID уже завершился.
2. Недостаточно прав (процесс запущен от имени Администратора или защищен античитом / PatchGuard). Требуется привилегия SeDebugPrivilege.""",
        "task": "Смоделируйте логику открытия процесса:\nПусть целевой PID = 2048, флаги доступа = 0x0010 (PROCESS_VM_READ).\nВыведите строку проверки статуса:\nTarget PID: 2048, DesiredAccess: 0x0010, Status: Handle Acquired",
        "initialCode": """#include <stdio.h>

int main(void) {
    unsigned long target_pid = 2048;
    unsigned long desired_access = 0x0010;

    // Выведите результат:
    
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
            "Используйте формат 0x%04lX для вывода шестнадцатеричного флага доступа."
        ],
        "expectedOutput": "Target PID: 2048, DesiredAccess: 0x0010, Status: Handle Acquired\n"
    },
    {
        "id": 15,
        "title": "Урок 15: Чтение памяти другого процесса через ReadProcessMemory",
        "lang": "C++",
        "difficulty": "Эксперт",
        "theoryPart1": """Мы подошли к главному инструменту анализа памяти в Windows — функции ReadProcessMemory!
С ее помощью отладчики (x64dbg, Cheat Engine) и трейнеры считывают значения здоровья, патронов, координат или указателей из чужого адресного пространства.

Сигнатура функции:
BOOL ReadProcessMemory(
    HANDLE  hProcess,             // Дескриптор целевого процесса (из OpenProcess)
    LPCVOID lpBaseAddress,        // Адрес в памяти целевого процесса, откуда читать
    LPVOID  lpBuffer,             // Адрес в НАШЕЙ памяти (буфер), куда сохранить данные
    SIZE_T  nSize,                // Сколько байт прочитать (например, sizeof(int))
    SIZE_T *lpNumberOfBytesRead   // Сколько байт реально прочитано (можно передать NULL)
);

Как это работает по шагам:
1. Пусть в целевой игре переменная здоровья игрока int health = 100 находится по адресу 0x0045A120.
2. В нашей программе мы заводим локальную переменную:
   int my_health = 0;
3. Вызываем ReadProcessMemory:
   ReadProcessMemory(hProcess, (LPCVOID)0x0045A120, &my_health, sizeof(my_health), NULL);
4. Ядро Windows приостанавливает поток, считывает 4 байта из страниц памяти целевого процесса и копирует в наш адрес &my_health.
5. Теперь в переменной my_health лежит точное значение 100!""",
        "quiz": {
            "question": "Что передается в качестве второго аргумента (lpBaseAddress) в ReadProcessMemory?",
            "options": [
                {
                    "id": "a",
                    "text": "Адрес в памяти целевого процесса, откуда нужно прочитать байты",
                    "correct": True,
                    "explanation": "Верно! lpBaseAddress — это виртуальный адрес ячейки памяти внутри целевого процесса."
                },
                {
                    "id": "b",
                    "text": "Путь к файлу на жестком диске",
                    "correct": False,
                    "explanation": "Неверно. ReadProcessMemory работает с ОЗУ, а не с диском."
                }
            ]
        },
        "theoryPart2": """Многоуровневые указатели (Pointer Paths):
В реальных играх адреса меняются при каждом перезапуске (динамическая куча).
Поэтому используется цепочка смещений (Offsets):
BaseAddress -> [Base + 0x10] -> [Address + 0x48] -> Final Health Value.
ReadProcessMemory вызывается последовательно для каждого указателя в цепочке!""",
        "task": "Смоделируйте чтение значения через эмулятор буфера:\nПусть имитированная память target_ram[4] = {10, 20, 999, 40};\nАдрес смещения offset = 2.\nПрочитайте значение по смещению и выведите:\nReadProcessMemory Result: 999 HP (bytes read: 4)",
        "initialCode": """#include <stdio.h>

int main(void) {
    int target_ram[4] = {10, 20, 999, 40};
    size_t offset = 2;

    int read_buffer = 0;
    size_t bytes_read = sizeof(int);

    // Скопируйте значение из target_ram[offset] в read_buffer:
    
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
        "id": 16,
        "title": "Урок 16: Запись в память процесса через WriteProcessMemory и патчинг NOP",
        "lang": "C++",
        "difficulty": "Эксперт",
        "theoryPart1": """Изменение памяти (Memory Editing):
Функция WriteProcessMemory позволяет перезаписать память чужого процесса.

Сигнатура:
BOOL WriteProcessMemory(
    HANDLE  hProcess,               // Дескриптор процесса (требует PROCESS_VM_WRITE)
    LPVOID  lpBaseAddress,          // Адрес в чужом процессе, КУДА писать
    LPCVOID lpBuffer,               // Буфер в нашей программе, ОТКУДА брать байты
    SIZE_T  nSize,                  // Сколько байт записать
    SIZE_T *lpNumberOfBytesWritten  // Сколько байт записано реально
);

Патчинг опкодов (Code Patching) и инструкция NOP:
В процессорах архитектуры x86/x64 инструкция уменьшения здоровья выглядит как:
SUB DWORD PTR [RAX+0x10], EDX   // Вычитание патронов или здоровья (байт-код: 29 50 10)
Чтобы отключить расход патронов (Infinite Ammo), системный хакер заменяет эти инструкции на «пустые операции» — NOP (No Operation).
Опкод инструкции NOP в x86/x64 равен одному байту: 0x90!
Когда процессор доходит до байта 0x90, он ничего не делает и сразу переходит к следующей инструкции. Расход патронов отключен!""",
        "quiz": {
            "question": "Какой опкод в архитектуре x86/x64 соответствует инструкции NOP (No Operation)?",
            "options": [
                {
                    "id": "a",
                    "text": "0x90",
                    "correct": True,
                    "explanation": "Верно! Однобайтовая инструкция 0x90 (NOP) является классическим приемом патчинга в ассемблере x86."
                },
                {
                    "id": "b",
                    "text": "0x00",
                    "correct": False,
                    "explanation": "0x00 в опкодах x86 — это часть инструкции ADD [RAX], AL, а не NOP."
                },
                {
                    "id": "c",
                    "text": "0xFF",
                    "correct": False,
                    "explanation": "0xFF — это группа опкодов CALL/JMP/INC/DEC."
                }
            ]
        },
        "theoryPart2": """Перед вызовом WriteProcessMemory для изменения секции кода (.text) необходимо вызвать VirtualProtectEx, чтобы сменить права страницы с PAGE_EXECUTE_READ на PAGE_EXECUTE_READWRITE, иначе функция завершится с кодом ERROR_ACCESS_DENIED.""",
        "task": "Смоделируйте NOP-патчинг:\nДан массив машинных инструкций:\nunsigned char code_bytes[3] = {0x29, 0x50, 0x10}; // sub [rax+10], edx\nЗамените все 3 байта на опкод 0x90 (NOP).\nВыведите результат в шестнадцатеричном виде:\nPatched bytes: 0x90 0x90 0x90 (NOP applied)",
        "initialCode": """#include <stdio.h>

int main(void) {
    unsigned char code_bytes[3] = {0x29, 0x50, 0x10};

    // Замените все 3 байта на 0x90:
    
    printf("Patched bytes: 0x%02X 0x%02X 0x%02X (NOP applied)\\n",
           code_bytes[0], code_bytes[1], code_bytes[2]);
    return 0;
}
""",
        "solution": """#include <stdio.h>

int main(void) {
    unsigned char code_bytes[3] = {0x29, 0x50, 0x10};
    code_bytes[0] = 0x90;
    code_bytes[1] = 0x90;
    code_bytes[2] = 0x90;

    printf("Patched bytes: 0x%02X 0x%02X 0x%02X (NOP applied)\\n",
           code_bytes[0], code_bytes[1], code_bytes[2]);
    return 0;
}
""",
        "hints": [
            "code_bytes[0] = 0x90; code_bytes[1] = 0x90; code_bytes[2] = 0x90;"
        ],
        "expectedOutput": "Patched bytes: 0x90 0x90 0x90 (NOP applied)\n"
    },
    {
        "id": 17,
        "title": "Урок 17: Финальный курсовой проект: Memory Trainer Engine на C++",
        "lang": "C++",
        "difficulty": "Эксперт",
        "theoryPart1": """Поздравляем! Вы прошли путь от азов языка Си до системной работы с виртуальной памятью и Windows API!
Теперь вы обладаете полным арсеналом знаний:
- Понимание архитектуры x86_64, регистров и страниц памяти.
- Управление указателями, адресами и смещениями.
- Структуры данных и ООП в C++.
- Системные вызовы Windows: OpenProcess, ReadProcessMemory, WriteProcessMemory, CloseHandle.

Архитектура собственного Memory Trainer Engine:
Оформим законченный класс `ProcessMemoryManager`:
1. Хранит дескриптор `HANDLE hProcess_` и `DWORD pid_`.
2. Конструктор принимает PID и открывает процесс.
3. Деструктор автоматически закрывает HANDLE (принцип RAII!).
4. Шаблонный метод `template <typename T> T Read(uintptr_t address)` для безопасного чтения любого типа (int, float, struct).
5. Шаблонный метод `template <typename T> bool Write(uintptr_t address, T value)` для записи значений.

С этим классом вы сможете написать реальный трейнер или утилиту диагностики памяти для любой Windows-программы!""",
        "quiz": {
            "question": "Почему оформление работы с памятью процесса в C++ класс с RAII деструктором является лучшей практикой?",
            "options": [
                {
                    "id": "a",
                    "text": "Деструктор класса гарантированно закроет дескриптор CloseHandle(hProcess_), предотвращая утечки ресурсов ядра ОС при выходе из области видимости",
                    "correct": True,
                    "explanation": "Идеально! Это золотой стандарт надежного системного C++ софта."
                },
                {
                    "id": "b",
                    "text": "Потому что C++ запрещает использовать Си-функции",
                    "correct": False,
                    "explanation": "C++ полностью обратно совместим с Си и WinAPI."
                }
            ]
        },
        "theoryPart2": """Выпускное практическое задание:
Реализуйте каркас системного класса `TrainerMemory`, прочитайте и обновите эмулированное значение переменной здоровья игрока!""",
        "task": "Реализуйте класс TrainerMemory:\n- Метод int readInt(uintptr_t addr)\n- Метод void writeInt(uintptr_t addr, int val)\nВ main примените его к адресу имитированного значения health = 100, запишите 9999 (GodMode) и выведите:\n[TrainerCode Engine] Target Health: 9999 (Freeze Active)",
        "initialCode": """#include <iostream>
#include <cstdint>

// Реализуйте класс TrainerMemory для работы с адресами памяти:
class TrainerMemory {
private:
    int simulated_ram_[16];

public:
    TrainerMemory() {
        for (int i = 0; i < 16; i++) simulated_ram_[i] = 0;
        simulated_ram_[4] = 100; // По адресу смещения 4 лежит здоровье
    }

    int readInt(uintptr_t offset) {
        return simulated_ram_[offset];
    }

    void writeInt(uintptr_t offset, int val) {
        simulated_ram_[offset] = val;
    }
};

int main() {
    TrainerMemory trainer;
    // Запишите 9999 по смещению 4 и выведите:
    
    return 0;
}
""",
        "solution": """#include <iostream>
#include <cstdint>

class TrainerMemory {
private:
    int simulated_ram_[16];

public:
    TrainerMemory() {
        for (int i = 0; i < 16; i++) simulated_ram_[i] = 0;
        simulated_ram_[4] = 100;
    }

    int readInt(uintptr_t offset) {
        return simulated_ram_[offset];
    }

    void writeInt(uintptr_t offset, int val) {
        simulated_ram_[offset] = val;
    }
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
            "Выведите: [TrainerCode Engine] Target Health: 9999 (Freeze Active)"
        ],
        "expectedOutput": "[TrainerCode Engine] Target Health: 9999 (Freeze Active)\n"
    }
]

# Write JSON
json_path = "/home/user/TrainerCode/web_preview/public/lessons.json"
with open(json_path, "w", encoding="utf-8") as f:
    json.dump(lessons, f, ensure_ascii=False, indent=2)

print(f"Generated {len(lessons)} comprehensive lessons into {json_path}")

# Write C++ header
def escape_cpp(s):
    res = s.replace('\\', '\\\\').replace('"', '\\"').replace('\n', '\\n"\n    "')
    return f'"{res}"'

hpp_path = "/home/user/TrainerCode/src_win32/lessons_data.hpp"
with open(hpp_path, "w", encoding="utf-8") as f:
    f.write("""#pragma once
#include <string>
#include <vector>

struct QuizOption {
    std::wstring id;
    std::wstring text;
    bool correct;
    std::wstring explanation;
};

struct LessonQuiz {
    std::wstring question;
    std::vector<QuizOption> options;
};

struct Lesson {
    int id;
    std::wstring title;
    std::wstring lang;
    std::wstring difficulty;
    std::wstring theory_part1;
    LessonQuiz quiz;
    std::wstring theory_part2;
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
        f.write(f"        l.title = L{escape_cpp(les['title'])};\n")
        f.write(f"        l.lang = L{escape_cpp(les['lang'])};\n")
        f.write(f"        l.difficulty = L{escape_cpp(les['difficulty'])};\n")
        f.write(f"        l.theory_part1 = L{escape_cpp(les['theoryPart1'])};\n")
        f.write(f"        l.quiz.question = L{escape_cpp(les['quiz']['question'])};\n")
        for opt in les['quiz']['options']:
            f.write("        {\n")
            f.write("            QuizOption opt;\n")
            f.write(f"            opt.id = L{escape_cpp(opt['id'])};\n")
            f.write(f"            opt.text = L{escape_cpp(opt['text'])};\n")
            f.write(f"            opt.correct = {'true' if opt['correct'] else 'false'};\n")
            f.write(f"            opt.explanation = L{escape_cpp(opt['explanation'])};\n")
            f.write("            l.quiz.options.push_back(opt);\n")
            f.write("        }\n")
        f.write(f"        l.theory_part2 = L{escape_cpp(les['theoryPart2'])};\n")
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
