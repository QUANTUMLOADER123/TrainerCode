#pragma once
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
    {
        Lesson l;
        l.id = 1;
        l.title = L"Урок 1: Архитектура ЭВМ, память и первая программа";
        l.lang = L"C";
        l.difficulty = L"Новичок";
        l.theory_part1 = L"Добро пожаловать в элитную школу системного программирования TrainerCode!\n"
    "\n"
    "Языки C и C++ — это фундамент операционных систем (Windows, Linux), игровых движков (Unreal Engine), античитов, драйверов и высокопроизводительного софта. В отличие от Python или Java, здесь нет интерпретатора и виртуальной машины. Код компилируется напрямую в машинные инструкции процессора (x86/x64).\n"
    "\n"
    "Как устроен компьютер:\n"
    "1. Процессор (CPU): Выполняет инструкции (MOV, ADD, JMP, CALL) на тактовой частоте миллиарды раз в секунду. Внутри CPU есть свербыстрые ячейки — регистры (RAX, RBX, RCX, RDX, RSP, RIP).\n"
    "2. Оперативная память (RAM): Огромный массив байт. Каждый байт имеет свой уникальный числовой адрес (например, 0x00401000).\n"
    "3. Точка входа в программу: В операционной системе процесс запускается с функции main().\n"
    "   Синтаксис в C:\n"
    "   #include <stdio.h>\n"
    "\n"
    "   int main(void) {\n"
    "       printf(\"Hello, TrainerCode!\\n\");\n"
    "       return 0;\n"
    "   }\n"
    "\n"
    "Препроцессор (#include <stdio.h>): директива, которая перед компиляцией вставляет объявления стандартных функций ввода-вывода (printf).\n"
    "printf(\"...\\n\"): выводит текст в стандартный поток вывода (консоль). '\\n' — символ перевода строки.\n"
    "return 0;: возвращает операционной системе код 0, что означает: \"Программа завершилась штатно и без ошибок\".";
        l.quiz.question = L"Что означает директива `#include <stdio.h>` и зачем в конце `main` пишется `return 0;`?";
        {
            QuizOption opt;
            opt.id = L"a";
            opt.text = L"#include подключает стандартную библиотеку ввода-вывода, а return 0 сообщает ОС об успешном завершении";
            opt.correct = true;
            opt.explanation = L"Верно! #include подключает заголовок stdio.h для printf, а код возврата 0 является стандартным сигналом успеха для операционной системы.";
            l.quiz.options.push_back(opt);
        }
        {
            QuizOption opt;
            opt.id = L"b";
            opt.text = L"Это объявление глобальной переменной для выделения 0 байт памяти";
            opt.correct = false;
            opt.explanation = L"Неверно. #include — директива препроцессора, а return 0 возвращает код завершения из main.";
            l.quiz.options.push_back(opt);
        }
        {
            QuizOption opt;
            opt.id = L"c";
            opt.text = L"return 0 перезагружает компьютер в безопасном режиме";
            opt.correct = false;
            opt.explanation = L"Конечно нет. return 0 просто завершает процесс с кодом выхода 0.";
            l.quiz.options.push_back(opt);
        }
        l.theory_part2 = L"Закрепление материала:\n"
    "Компилятор превращает ваш C-код в машинный файл формата PE (.exe на Windows) или ELF (на Linux).\n"
    "В Windows структура программы включает:\n"
    "- Секция .text: исполняемый машинный код\n"
    "- Секция .data: глобальные инициализированные переменные\n"
    "- Секция .rdata: строковые константы (read-only)\n"
    "\n"
    "Теперь напишите вашу первую программу в редакторе кода!";
        l.task = L"Напишите программу на Си, которая выводит:\n"
    "TrainerCode 2000 System Active\n"
    "Target CPU: x86_64\n"
    "и возвращает 0.";
        l.initial_code = L"#include <stdio.h>\n"
    "\n"
    "int main(void) {\n"
    "    // Выведите требуемый текст:\n"
    "    \n"
    "    return 0;\n"
    "}\n"
    "";
        l.solution = L"#include <stdio.h>\n"
    "\n"
    "int main(void) {\n"
    "    printf(\"TrainerCode 2000 System Active\\n\");\n"
    "    printf(\"Target CPU: x86_64\\n\");\n"
    "    return 0;\n"
    "}\n"
    "";
        l.expected_output = L"TrainerCode 2000 System Active\n"
    "Target CPU: x86_64\n"
    "";
        l.hints.push_back(L"Используйте printf с символом '\\n' в конце каждой строки.");
        l.hints.push_back(L"Проверьте регистр букв: TrainerCode 2000 System Active");
        list.push_back(l);
    }
    {
        Lesson l;
        l.id = 2;
        l.title = L"Урок 2: Фундаментальные типы данных, память и sizeof";
        l.lang = L"C";
        l.difficulty = L"Новичок";
        l.theory_part1 = L"Память компьютера дискретна: минимальная адресуемая ячейка — 1 байт (8 бит).\n"
    "В Си каждый тип данных занимает фиксированное число байт:\n"
    "\n"
    "1. Целочисленные типы:\n"
    "- char (1 байт = 8 бит): от -128 до 127 (символ ASCII или маленькое число).\n"
    "- unsigned char (1 байт): от 0 до 255.\n"
    "- short (2 байта = 16 бит): от -32,768 до 32,767.\n"
    "- int (4 байта = 32 бита): от -2,147,483,648 до 2,147,483,647 (~2 миллиарда).\n"
    "- unsigned int (4 байта): от 0 до 4,294,967,295 (~4 миллиарда).\n"
    "- long long (8 байт = 64 бита): от -9*10^18 до 9*10^18.\n"
    "- unsigned long long (8 байт): до 18*10^18.\n"
    "\n"
    "2. Дробные типы (с плавающей точкой IEEE 754):\n"
    "- float (4 байта): ~7 десятичных цифр точности.\n"
    "- double (8 байт): ~15-17 цифр точности.\n"
    "\n"
    "3. Оператор sizeof:\n"
    "Оператор sizeof(тип_или_переменная) возвращает точный размер в байтах.\n"
    "Спецификатор для вывода sizeof в printf — %zu.\n"
    "\n"
    "Спецификаторы printf:\n"
    "%d — знаковый int\n"
    "%u — беззнаковый unsigned int\n"
    "%lld — long long\n"
    "%f — float / double\n"
    "%c — символ char\n"
    "%p — адрес указателя в шестнадцатеричном виде (hex)";
        l.quiz.question = L"Сколько байт занимает тип int на 64-битной архитектуре x86_64 и какой диапазон у unsigned char?";
        {
            QuizOption opt;
            opt.id = L"a";
            opt.text = L"int занимает 4 байта, а unsigned char имеет диапазон от 0 до 255";
            opt.correct = true;
            opt.explanation = L"Абсолютно верно! В стандартных моделях данных (LLP64 на Windows и LP64 на Linux) int равен 32 битам (4 байта), а 8-битный unsigned char хранит числа от 0 до 2^8 - 1 = 255.";
            l.quiz.options.push_back(opt);
        }
        {
            QuizOption opt;
            opt.id = L"b";
            opt.text = L"int занимает 8 байт, а unsigned char от -128 до 127";
            opt.correct = false;
            opt.explanation = L"Неверно. 8 байт занимает long long. А unsigned char не может быть отрицательным.";
            l.quiz.options.push_back(opt);
        }
        {
            QuizOption opt;
            opt.id = L"c";
            opt.text = L"int занимает 1 байт, unsigned char от 0 до 100";
            opt.correct = false;
            opt.explanation = L"Неверно. 1 байт занимает char.";
            l.quiz.options.push_back(opt);
        }
        l.theory_part2 = L"Внимание: Переполнение чисел (Integer Overflow):\n"
    "Если к signed int прибавить единицу при значении 2,147,483,647, произойдет переполнение в отрицательное число -2,147,483,648 (Undefined Behavior в Си).\n"
    "Для системного программиста критично понимать точные размеры типов!";
        l.task = L"Объявите переменные:\n"
    "- int health = 100;\n"
    "- double armor = 45.5;\n"
    "- unsigned char level = 5;\n"
    "Выведите их значения и размеры в байтах (через sizeof):\n"
    "Health: 100 (4 bytes)\n"
    "Armor: 45.50 (8 bytes)\n"
    "Level: 5 (1 bytes)";
        l.initial_code = L"#include <stdio.h>\n"
    "\n"
    "int main(void) {\n"
    "    // Объявите переменные и напечатайте результат:\n"
    "    \n"
    "    return 0;\n"
    "}\n"
    "";
        l.solution = L"#include <stdio.h>\n"
    "\n"
    "int main(void) {\n"
    "    int health = 100;\n"
    "    double armor = 45.5;\n"
    "    unsigned char level = 5;\n"
    "\n"
    "    printf(\"Health: %d (%zu bytes)\\n\", health, sizeof(health));\n"
    "    printf(\"Armor: %.2f (%zu bytes)\\n\", armor, sizeof(armor));\n"
    "    printf(\"Level: %u (%zu bytes)\\n\", level, sizeof(level));\n"
    "    return 0;\n"
    "}\n"
    "";
        l.expected_output = L"Health: 100 (4 bytes)\n"
    "Armor: 45.50 (8 bytes)\n"
    "Level: 5 (1 bytes)\n"
    "";
        l.hints.push_back(L"Используйте %.2f для вывода armor с двумя знаками после запятой.");
        l.hints.push_back(L"Используйте %zu для вывода размера sizeof.");
        list.push_back(l);
    }
    {
        Lesson l;
        l.id = 3;
        l.title = L"Урок 3: Функции, аргументы и Стек Вызовов (Call Stack)";
        l.lang = L"C";
        l.difficulty = L"Новичок";
        l.theory_part1 = L"Что такое функция?\n"
    "Функция — это изолированный фрагмент кода с именем, входными аргументами и возвращаемым значением:\n"
    "int calculate_damage(int base_dmg, int armor) {\n"
    "    return base_dmg - armor;\n"
    "}\n"
    "\n"
    "Как работает передача аргументов в Си:\n"
    "В языке Си ВСЕ аргументы передаются ИСКЛЮЧИТЕЛЬНО ПО ЗНАЧЕНИЮ (Pass by Value).\n"
    "Когда вы передаете переменную в функцию, в памяти создается её ТОЧНАЯ КОПИЯ.\n"
    "Если изменить аргумент внутри функции:\n"
    "void try_change(int x) {\n"
    "    x = 999; // изменится только локальная копия!\n"
    "}\n"
    "Оригинальная переменная в вызвавшей функции останется нетронутой!\n"
    "\n"
    "Стек вызовов (Call Stack):\n"
    "При каждом вызове функции процессор резервирует память на стеке (Stack Frame):\n"
    "- Регистр RSP (указатель вершины стека) сдвигается вниз.\n"
    "- На стек помещается адрес возврата (куда вернуться после команды RET).\n"
    "- Размещаются локальные переменные функции.\n"
    "Когда функция завершается (return), её фрейм мгновенно уничтожается!";
        l.quiz.question = L"Если передать обычную переменную int a = 10 в функцию void foo(int a) { a = 50; }, изменится ли a в main()?";
        {
            QuizOption opt;
            opt.id = L"a";
            opt.text = L"Нет, не изменится, потому что в C аргументы передаются по значению (создается копия на стеке)";
            opt.correct = true;
            opt.explanation = L"Верно! В языке C все передается по значению. Чтобы изменить оригинал, потребуется передать адрес переменной (указатель).";
            l.quiz.options.push_back(opt);
        }
        {
            QuizOption opt;
            opt.id = L"b";
            opt.text = L"Да, изменится на 50, так как имя переменной совпадает";
            opt.correct = false;
            opt.explanation = L"Неверно. Область видимости аргумента ограничена телом функции foo, это независимая копия.";
            l.quiz.options.push_back(opt);
        }
        l.theory_part2 = L"Области видимости:\n"
    "Локальные переменные живут на стеке только пока выполняется блок { }.\n"
    "Если перед локальной переменной поставить ключевое слово static:\n"
    "static int counter = 0;\n"
    "Она переместится со стека в глобальный сегмент данных .data и сохранит свое значение между вызовами функции!";
        l.task = L"Напишите функцию int apply_bonus(int score, int multiplier), которая возвращает score * multiplier.\n"
    "В main вызовите ее для score = 150 и multiplier = 3 и выведите:\n"
    "Final Score: 450";
        l.initial_code = L"#include <stdio.h>\n"
    "\n"
    "// Напишите функцию apply_bonus здесь:\n"
    "\n"
    "int main(void) {\n"
    "    int score = 150;\n"
    "    int multiplier = 3;\n"
    "    \n"
    "    // Вызовите функцию и выведите результат:\n"
    "    \n"
    "    return 0;\n"
    "}\n"
    "";
        l.solution = L"#include <stdio.h>\n"
    "\n"
    "int apply_bonus(int score, int multiplier) {\n"
    "    return score * multiplier;\n"
    "}\n"
    "\n"
    "int main(void) {\n"
    "    int score = 150;\n"
    "    int multiplier = 3;\n"
    "    int total = apply_bonus(score, multiplier);\n"
    "    printf(\"Final Score: %d\\n\", total);\n"
    "    return 0;\n"
    "}\n"
    "";
        l.expected_output = L"Final Score: 450\n"
    "";
        l.hints.push_back(L"Сигнатура функции: int apply_bonus(int score, int multiplier)");
        l.hints.push_back(L"В теле функции верните score * multiplier;");
        list.push_back(l);
    }
    {
        Lesson l;
        l.id = 4;
        l.title = L"Урок 4: Ключевое слово inline, макросы и оптимизации";
        l.lang = L"C";
        l.difficulty = L"Средний";
        l.theory_part1 = L"Накладные расходы на вызов функции:\n"
    "Когда процессор вызывает обычную функцию, происходят машинные операции:\n"
    "1. Запись регистров-аргументов (RCX, RDX, R8, R9 по соглашению fastcall).\n"
    "2. Инструкция CALL: сохранение адреса возврата на вершину стека.\n"
    "3. Пролог функции (push rbp, mov rbp, rsp).\n"
    "4. Тело функции.\n"
    "5. Эпилог функции (pop rbp).\n"
    "6. Инструкция RET: снятие адреса со стека и прыжок обратно.\n"
    "Для крошечных функций из 1-2 строк эти накладные расходы могут занимать больше времени, чем сами полезные вычисления!\n"
    "\n"
    "Ключевое слово inline:\n"
    "inline int square(int x) {\n"
    "    return x * x;\n"
    "}\n"
    "Ключевое слово inline — это указание компилятору: «Не делай CALL/RET, а просто вставь тело функции прямо в место вызова!».\n"
    "В результате машинный код работает с максимальной скоростью, без работы со стеком.\n"
    "\n"
    "Макросы препроцессора (#define):\n"
    "#define MAX(a, b) ((a) > (b) ? (a) : (b))\n"
    "Макросы заменяют текст ДО компиляции. Внимание: в макросах всегда оборачивайте параметры в скобки, иначе возможны баги с приоритетом операций.";
        l.quiz.question = L"Какова главная цель спецификатора inline перед функцией?";
        {
            QuizOption opt;
            opt.id = L"a";
            opt.text = L"Устранить накладные расходы на инструкции CALL/RET путем подстановки тела функции прямо в точку вызова";
            opt.correct = true;
            opt.explanation = L"Именно! Компилятор подставляет машинный код на месте, экономя такты процессора на работу со стеком.";
            l.quiz.options.push_back(opt);
        }
        {
            QuizOption opt;
            opt.id = L"b";
            opt.text = L"Запретить компилятору использовать оптимизацию";
            opt.correct = false;
            opt.explanation = L"Наоборот, inline является хинтом оптимизации.";
            l.quiz.options.push_back(opt);
        }
        l.theory_part2 = L"В современном C/C++ компиляторы (GCC/MSVC) при включенных флагах оптимизации -O2 / /O2 часто сами решают, какие функции заинлайнить.\n"
    "Спецификатор inline также необходим в C++, если вы определяете функцию в .h заголовочном файле, чтобы избежать ошибки линковщика multiple definition.";
        l.task = L"Напишите inline функцию:\n"
    "static inline int clamp(int val, int min, int max)\n"
    "которая возвращает min если val < min, max если val > max, иначе val.\n"
    "В main проверьте: clamp(150, 0, 100) и clamp(-20, 0, 100):\n"
    "Clamped 1: 100\n"
    "Clamped 2: 0";
        l.initial_code = L"#include <stdio.h>\n"
    "\n"
    "// Объявите static inline функцию clamp:\n"
    "\n"
    "int main(void) {\n"
    "    printf(\"Clamped 1: %d\\n\", clamp(150, 0, 100));\n"
    "    printf(\"Clamped 2: %d\\n\", clamp(-20, 0, 100));\n"
    "    return 0;\n"
    "}\n"
    "";
        l.solution = L"#include <stdio.h>\n"
    "\n"
    "static inline int clamp(int val, int min, int max) {\n"
    "    if (val < min) return min;\n"
    "    if (val > max) return max;\n"
    "    return val;\n"
    "}\n"
    "\n"
    "int main(void) {\n"
    "    printf(\"Clamped 1: %d\\n\", clamp(150, 0, 100));\n"
    "    printf(\"Clamped 2: %d\\n\", clamp(-20, 0, 100));\n"
    "    return 0;\n"
    "}\n"
    "";
        l.expected_output = L"Clamped 1: 100\n"
    "Clamped 2: 0\n"
    "";
        l.hints.push_back(L"static inline int clamp(int val, int min, int max)");
        l.hints.push_back(L"if (val < min) return min; if (val > max) return max; return val;");
        list.push_back(l);
    }
    {
        Lesson l;
        l.id = 5;
        l.title = L"Урок 5: Побитовые операции, битовые сдвиги и флаги";
        l.lang = L"C";
        l.difficulty = L"Средний";
        l.theory_part1 = L"Побитовые операции — это хлеб системного программиста, разработчика драйверов и трейнеров. Они работают напрямую с битами в регистрах процессора за 1 такт!\n"
    "\n"
    "Операторы:\n"
    "1. & (Побитовое И / AND):\n"
    "   1 & 1 = 1, иначе 0. Применяется для проверки или маскирования битов.\n"
    "2. | (Побитовое ИЛИ / OR):\n"
    "   0 | 0 = 0, если хоть один бит равен 1, то 1. Применяется для установки флагов.\n"
    "3. ^ (Исключающее ИЛИ / XOR):\n"
    "   1 ^ 1 = 0, 0 ^ 0 = 0, разные биты дают 1. Применяется для инвертирования или шифрования.\n"
    "4. ~ (Побитовое НЕ / NOT):\n"
    "   Инвертирует все биты числа (0 становится 1, 1 становится 0).\n"
    "5. << (Сдвиг влево):\n"
    "   x << n сдвигает биты влево на n позиций (эквивалентно умножению на 2^n).\n"
    "6. >> (Сдвиг вправо):\n"
    "   x >> n делит на 2^n.\n"
    "\n"
    "Идиомы системного программирования:\n"
    "- Установить n-й бит: flags |= (1U << n);\n"
    "- Сбросить n-й бит: flags &= ~(1U << n);\n"
    "- Проверить n-й бит: if (flags & (1U << n)) { ... }\n"
    "- Переключить n-й бит: flags ^= (1U << n);";
        l.quiz.question = L"Какое выражение устанавливает 3-й бит числа flags в 1, не меняя остальные биты?";
        {
            QuizOption opt;
            opt.id = L"a";
            opt.text = L"flags |= (1 << 3);";
            opt.correct = true;
            opt.explanation = L"Верно! 1 << 3 формирует маску с единицей в третьем бите (0b00001000 = 8), а побитовое ИЛИ (|) устанавливает этот бит в 1.";
            l.quiz.options.push_back(opt);
        }
        {
            QuizOption opt;
            opt.id = L"b";
            opt.text = L"flags &= ~(1 << 3);";
            opt.correct = false;
            opt.explanation = L"Это выражение сбрасывает (обнуляет) 3-й бит, а не устанавливает.";
            l.quiz.options.push_back(opt);
        }
        {
            QuizOption opt;
            opt.id = L"c";
            opt.text = L"flags = flags + 3;";
            opt.correct = false;
            opt.explanation = L"Обычное сложение сломает остальные биты при переносе разряда.";
            l.quiz.options.push_back(opt);
        }
        l.theory_part2 = L"В операционной системе Windows права доступа к памяти и процессам кодируются битовыми масками:\n"
    "PROCESS_VM_READ (0x0010), PROCESS_VM_WRITE (0x0020), PROCESS_VM_OPERATION (0x0008).\n"
    "Объединяя их через |, мы получаем комбинированный флаг:\n"
    "DWORD desired_access = PROCESS_VM_READ | PROCESS_VM_WRITE;";
        l.task = L"Дана переменная unsigned int flags = 0;\n"
    "1. Установите бит 2 (значение 4) и бит 4 (значение 16).\n"
    "2. Выведите получившееся десятичное число.\n"
    "3. Сбросьте бит 2 и выведите результат.\n"
    "Ожидаемый вывод:\n"
    "Flags with bits 2 and 4: 20\n"
    "Flags after clearing bit 2: 16";
        l.initial_code = L"#include <stdio.h>\n"
    "\n"
    "int main(void) {\n"
    "    unsigned int flags = 0;\n"
    "    // Установите биты 2 и 4:\n"
    "    \n"
    "    printf(\"Flags with bits 2 and 4: %u\\n\", flags);\n"
    "\n"
    "    // Сбросьте бит 2:\n"
    "    \n"
    "    printf(\"Flags after clearing bit 2: %u\\n\", flags);\n"
    "    return 0;\n"
    "}\n"
    "";
        l.solution = L"#include <stdio.h>\n"
    "\n"
    "int main(void) {\n"
    "    unsigned int flags = 0;\n"
    "    flags |= (1 << 2);\n"
    "    flags |= (1 << 4);\n"
    "    printf(\"Flags with bits 2 and 4: %u\\n\", flags);\n"
    "\n"
    "    flags &= ~(1 << 2);\n"
    "    printf(\"Flags after clearing bit 2: %u\\n\", flags);\n"
    "    return 0;\n"
    "}\n"
    "";
        l.expected_output = L"Flags with bits 2 and 4: 20\n"
    "Flags after clearing bit 2: 16\n"
    "";
        l.hints.push_back(L"Установка бита n: flags |= (1 << n);");
        l.hints.push_back(L"Сброс бита n: flags &= ~(1 << n);");
        list.push_back(l);
    }
    {
        Lesson l;
        l.id = 6;
        l.title = L"Урок 6: УКАЗАТЕЛИ (Pointers) — Фундамент Си и Реверсинга";
        l.lang = L"C";
        l.difficulty = L"Средний";
        l.theory_part1 = L"ВНИМАНИЕ! Этот урок — самый важный во всем курсе.\n"
    "Понимание указателей отличает настоящего системного программиста от любителя.\n"
    "\n"
    "Что такое указатель?\n"
    "Указатель — это переменная, значением которой является АДРЕС в оперативной памяти другого объекта!\n"
    "\n"
    "Два базовых оператора:\n"
    "1. Оператор & (Address-of — взятие адреса):\n"
    "   int health = 100;\n"
    "   // Переменная health лежит в памяти, например, по адресу 0x0019FF2C.\n"
    "   int *ptr = &health; // В ptr теперь записан адрес 0x0019FF2C!\n"
    "\n"
    "2. Оператор * (Dereference — разыменование):\n"
    "   Оператор * заставляет процессор пойти по адресу, хранящемуся в указателе, и прочитать/записать значение.\n"
    "   *ptr = 250; // Мы изменили значение переменной health на 250 через ее адрес!\n"
    "\n"
    "Размер указателя:\n"
    "На 32-битных системах указатель занимает 4 байта.\n"
    "На 64-битных системах (x86_64) указатель занимает 8 байт (так как адреса 64-битные).\n"
    "Тип указателя (int*, char*, double*) указывает компилятору, сколько байт читать/писать при разыменовании!";
        l.quiz.question = L"Если int x = 42; int *p = &x; что произойдет при выполнении *p = 99;?";
        {
            QuizOption opt;
            opt.id = L"a";
            opt.text = L"Значение переменной x изменится на 99, потому что p хранит ее адрес памяти";
            opt.correct = true;
            opt.explanation = L"Блестяще! Оператор * разыменовывает указатель p и записывает 99 непосредственно в ячейку памяти переменной x.";
            l.quiz.options.push_back(opt);
        }
        {
            QuizOption opt;
            opt.id = L"b";
            opt.text = L"Изменится адрес самого указателя p, а x останется равным 42";
            opt.correct = false;
            opt.explanation = L"Неверно. Адрес изменился бы при p = ..., а запись *p = ... меняет целевой объект.";
            l.quiz.options.push_back(opt);
        }
        l.theory_part2 = L"NULL и висячие указатели (Dangling Pointers):\n"
    "Если указатель равен NULL (0x00000000), разыменование (*ptr) вызовет фатальное аппаратное исключение процессора:\n"
    "EXCEPTION_ACCESS_VIOLATION (0xC0000005) на Windows или Segmentation fault на Linux.\n"
    "Всегда проверяйте указатели перед разыменованием!";
        l.task = L"Напишите функцию void add_gold(int *player_gold, int amount), которая через указатель увеличивает золото игрока.\n"
    "В main создайте int gold = 500;, вызовите add_gold(&gold, 250) и напечатайте:\n"
    "Player Gold: 750";
        l.initial_code = L"#include <stdio.h>\n"
    "\n"
    "// Напишите функцию add_gold здесь:\n"
    "\n"
    "int main(void) {\n"
    "    int gold = 500;\n"
    "    // Вызовите add_gold, передав адрес:\n"
    "    \n"
    "    printf(\"Player Gold: %d\\n\", gold);\n"
    "    return 0;\n"
    "}\n"
    "";
        l.solution = L"#include <stdio.h>\n"
    "\n"
    "void add_gold(int *player_gold, int amount) {\n"
    "    if (player_gold != NULL) {\n"
    "        *player_gold += amount;\n"
    "    }\n"
    "}\n"
    "\n"
    "int main(void) {\n"
    "    int gold = 500;\n"
    "    add_gold(&gold, 250);\n"
    "    printf(\"Player Gold: %d\\n\", gold);\n"
    "    return 0;\n"
    "}\n"
    "";
        l.expected_output = L"Player Gold: 750\n"
    "";
        l.hints.push_back(L"Сигнатура: void add_gold(int *player_gold, int amount)");
        l.hints.push_back(L"Внутри функции: *player_gold += amount;");
        l.hints.push_back(L"При вызове передайте адрес: add_gold(&gold, 250);");
        list.push_back(l);
    }
    {
        Lesson l;
        l.id = 7;
        l.title = L"Урок 7: Адресная арифметика, void* и байтовые смещения";
        l.lang = L"C";
        l.difficulty = L"Средний";
        l.theory_part1 = L"Адресная арифметика (Pointer Arithmetic):\n"
    "Когда вы прибавляете число k к указателю ptr:\n"
    "ptr + k\n"
    "Адрес в памяти увеличивается НЕ на k байт, а на:\n"
    "k * sizeof(*ptr) байт!\n"
    "\n"
    "Пример:\n"
    "int arr[3] = {10, 20, 30};\n"
    "int *p = arr; // указывает на arr[0] (допустим адрес 0x1000)\n"
    "p + 1;        // адрес станет 0x1004! Потому что sizeof(int) == 4.\n"
    "\n"
    "Универсальный указатель void*:\n"
    "void* — это сырой бестиповый указатель на память.\n"
    "Он может хранить адрес любого объекта (int, float, struct).\n"
    "Однако void* НЕЛЬЗЯ разыменовать напрямую (*p — ошибка компиляции), потому что компилятор не знает тип и размер данных!\n"
    "Перед разыменованием void* необходимо явно привести к нужному типу:\n"
    "int val = *(int*)raw_ptr;\n"
    "\n"
    "Указатели на байты (unsigned char*):\n"
    "В реверс-инжиниринге и трейнерах адреса часто приводят к unsigned char* (или uintptr_t), потому что sizeof(unsigned char) == 1 байт. Это позволяет сдвигаться по памяти ровно на заданное количество байт (Offset)!";
        l.quiz.question = L"Если указатель int *ptr равен адресу 0x2000, чему будет равен адрес выражения ptr + 2 (при sizeof(int) = 4)?";
        {
            QuizOption opt;
            opt.id = L"a";
            opt.text = L"0x2008 (сместится на 2 * 4 = 8 байт)";
            opt.correct = true;
            opt.explanation = L"Верно! Адресная арифметика умножает приращение на размер базового типа (2 * 4 = 8 байт в шестнадцатеричной системе).";
            l.quiz.options.push_back(opt);
        }
        {
            QuizOption opt;
            opt.id = L"b";
            opt.text = L"0x2002 (сместится ровно на 2 байта)";
            opt.correct = false;
            opt.explanation = L"Неверно. На 2 байта сместился бы указатель типа char*.";
            l.quiz.options.push_back(opt);
        }
        l.theory_part2 = L"Указатель на указатель (Двойной указатель, **ptr):\n"
    "Переменная, которая хранит адрес ДРУГОГО указателя.\n"
    "Используется, когда функции нужно изменить сам адрес указателя (например, при выделении динамической памяти).";
        l.task = L"Дан массив int numbers[4] = {11, 22, 33, 44};\n"
    "Используя указатель int *ptr = numbers; и адресную арифметику (ptr + 2), прочитайте и выведите третий элемент массива:\n"
    "Third element via pointer: 33";
        l.initial_code = L"#include <stdio.h>\n"
    "\n"
    "int main(void) {\n"
    "    int numbers[4] = {11, 22, 33, 44};\n"
    "    int *ptr = numbers;\n"
    "\n"
    "    // Получите третий элемент через *(ptr + 2):\n"
    "    int val = 0;\n"
    "    \n"
    "    printf(\"Third element via pointer: %d\\n\", val);\n"
    "    return 0;\n"
    "}\n"
    "";
        l.solution = L"#include <stdio.h>\n"
    "\n"
    "int main(void) {\n"
    "    int numbers[4] = {11, 22, 33, 44};\n"
    "    int *ptr = numbers;\n"
    "    int val = *(ptr + 2);\n"
    "\n"
    "    printf(\"Third element via pointer: %d\\n\", val);\n"
    "    return 0;\n"
    "}\n"
    "";
        l.expected_output = L"Third element via pointer: 33\n"
    "";
        l.hints.push_back(L"arr[i] абсолютно эквивалентно *(ptr + i)");
        l.hints.push_back(L"Для третьего элемента используйте *(ptr + 2).");
        list.push_back(l);
    }
    {
        Lesson l;
        l.id = 8;
        l.title = L"Урок 8: Динамическая память в куче (Heap): malloc и free";
        l.lang = L"C";
        l.difficulty = L"Средний";
        l.theory_part1 = L"Стек vs Куча (Stack vs Heap):\n"
    "- Стек (Stack): Размер фиксирован (~1-2 МБ). Переменные создаются мгновенно, но удаляются при выходе из функции.\n"
    "- Куча (Heap): Вся свободная оперативная память компьютера (гигабайты). Выделяется и освобождается вручную разработчиком во время работы программы (Runtime).\n"
    "\n"
    "Функции работы с кучей (<stdlib.h>):\n"
    "1. malloc(size_t size):\n"
    "   Выделяет блок памяти указанного размера в байтах. Возвращает void* на начало блока или NULL, если память не удалось выделить.\n"
    "   Внимание: malloc НЕ очищает память, там лежит старый 'мусор'!\n"
    "   int *arr = (int*)malloc(10 * sizeof(int));\n"
    "\n"
    "2. free(void *ptr):\n"
    "   Возвращает выделенный блок операционной системе.\n"
    "   После free(ptr) переменная ptr становится «висячим указателем» (Dangling Pointer). Хорошая практика: сразу занулять его: ptr = NULL;\n"
    "\n"
    "Смертные грехи:\n"
    "- Утечка памяти (Memory Leak): забыли вызвать free(). Программа пожирает RAM до зависания ПК.\n"
    "- Double Free: вызов free(ptr) дважды для одного адреса — краш кучи (Heap Corruption).\n"
    "- Use-After-Free: чтение или запись по указателю после вызова free.";
        l.quiz.question = L"Что произойдет, если в цикле вызывать malloc() и не вызывать free()?";
        {
            QuizOption opt;
            opt.id = L"a";
            opt.text = L"Утечка памяти (Memory Leak): программа постепенно потребит всю доступную память системы";
            opt.correct = true;
            opt.explanation = L"Верно. Операционная система не освобождает кучу сама до завершения процесса, поэтому память утекает.";
            l.quiz.options.push_back(opt);
        }
        {
            QuizOption opt;
            opt.id = L"b";
            opt.text = L"Компилятор автоматически вставит free в конце цикла";
            opt.correct = false;
            opt.explanation = L"В языке Си нет сборщика мусора и авто-free.";
            l.quiz.options.push_back(opt);
        }
        l.theory_part2 = L"Безопасный паттерн работы с динамической памятью:\n"
    "1. Всегда проверять результат malloc на NULL:\n"
    "   if (buf == NULL) { /* обработка нехватки памяти */ }\n"
    "2. Освобождать память строго в том же модуле/контексте, где она была создана.\n"
    "3. Присваивать NULL после free.";
        l.task = L"Выделите в куче массив из 3 целых чисел с помощью malloc.\n"
    "Запишите в них числа: 10, 20, 30.\n"
    "Вычислите их сумму и выведите:\n"
    "Allocated sum: 60\n"
    "Затем освободите память через free().";
        l.initial_code = L"#include <stdio.h>\n"
    "#include <stdlib.h>\n"
    "\n"
    "int main(void) {\n"
    "    // 1. Выделите память под 3 int через malloc\n"
    "    \n"
    "    // 2. Проверьте на NULL\n"
    "    \n"
    "    // 3. Заполните массив и найдите сумму\n"
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
    "    if (arr == NULL) return 1;\n"
    "\n"
    "    arr[0] = 10;\n"
    "    arr[1] = 20;\n"
    "    arr[2] = 30;\n"
    "\n"
    "    int sum = arr[0] + arr[1] + arr[2];\n"
    "    printf(\"Allocated sum: %d\\n\", sum);\n"
    "\n"
    "    free(arr);\n"
    "    arr = NULL;\n"
    "    return 0;\n"
    "}\n"
    "";
        l.expected_output = L"Allocated sum: 60\n"
    "";
        l.hints.push_back(L"int *arr = (int*)malloc(3 * sizeof(int));");
        l.hints.push_back(L"Обязательно вызовите free(arr); в конце.");
        list.push_back(l);
    }
    {
        Lesson l;
        l.id = 9;
        l.title = L"Урок 9: Структуры (struct), объединения и выравнивание (Padding)";
        l.lang = L"C";
        l.difficulty = L"Средний";
        l.theory_part1 = L"Структура (struct) — это пользовательский составной тип, объединяющий поля разных типов под одной крышей.\n"
    "\n"
    "Объявление:\n"
    "typedef struct {\n"
    "    char name[32];\n"
    "    int health;\n"
    "    float speed;\n"
    "} Entity;\n"
    "\n"
    "Доступ к полям:\n"
    "1. Через точку (.), если у нас сам объект:\n"
    "   Entity player;\n"
    "   player.health = 100;\n"
    "\n"
    "2. Через стрелку (->), если у нас УКАЗАТЕЛЬ на структуру:\n"
    "   Entity *ptr = &player;\n"
    "   ptr->health = 100; // эквивалентно (*ptr).health = 100\n"
    "\n"
    "Выравнивание данных в памяти (Structure Padding):\n"
    "Процессоры x86/x64 читают память порциями по 4 или 8 байт.\n"
    "Поэтому компилятор выравнивает поля структуры, вставляя невидимые пустые байты (Padding)!\n"
    "Пример:\n"
    "struct Test {\n"
    "    char c; // 1 байт + 3 байта padding!\n"
    "    int x;  // 4 байта\n"
    "};\n"
    "Размер sizeof(struct Test) равен 8 байтам, а не 5!\n"
    "Для упаковки структур в сетевых пакетах и структурах памяти процессов используется директива #pragma pack(push, 1).";
        l.quiz.question = L"Если у нас есть указатель Entity *p, как правильно обратиться к его полю health?";
        {
            QuizOption opt;
            opt.id = L"a";
            opt.text = L"p->health (или (*p).health)";
            opt.correct = true;
            opt.explanation = L"Верно! Оператор стрелочки (->) совмещает разыменование указателя и доступ к полю структуры.";
            l.quiz.options.push_back(opt);
        }
        {
            QuizOption opt;
            opt.id = L"b";
            opt.text = L"p.health";
            opt.correct = false;
            opt.explanation = L"Неверно. Точка используется только когда переменная является самим объектом, а не указателем.";
            l.quiz.options.push_back(opt);
        }
        l.theory_part2 = L"В игровых движках и системных процессах сущности (игроки, боты, снаряды) всегда представлены структурами в памяти. Зная смещение (Offset) поля health внутри структуры, можно модифицировать здоровье персонажа прямо в ОЗУ!";
        l.task = L"Создайте структуру PlayerData с полями: int id, int hp, int ammo.\n"
    "Напишите функцию void heal(PlayerData *p, int amount), которая через стрелку -> увеличивает p->hp на amount.\n"
    "В main создайте PlayerData p = {1, 50, 30};, вызовите heal(&p, 50) и выведите:\n"
    "Player ID 1 HP: 100";
        l.initial_code = L"#include <stdio.h>\n"
    "\n"
    "// Объявите структуру PlayerData и функцию heal:\n"
    "\n"
    "int main(void) {\n"
    "    PlayerData p = {1, 50, 30};\n"
    "    // Вызовите heal(&p, 50) и напечатайте результат:\n"
    "    \n"
    "    return 0;\n"
    "}\n"
    "";
        l.solution = L"#include <stdio.h>\n"
    "\n"
    "typedef struct {\n"
    "    int id;\n"
    "    int hp;\n"
    "    int ammo;\n"
    "} PlayerData;\n"
    "\n"
    "void heal(PlayerData *p, int amount) {\n"
    "    if (p != NULL) {\n"
    "        p->hp += amount;\n"
    "    }\n"
    "}\n"
    "\n"
    "int main(void) {\n"
    "    PlayerData p = {1, 50, 30};\n"
    "    heal(&p, 50);\n"
    "    printf(\"Player ID %d HP: %d\\n\", p.id, p.hp);\n"
    "    return 0;\n"
    "}\n"
    "";
        l.expected_output = L"Player ID 1 HP: 100\n"
    "";
        l.hints.push_back(L"Используйте typedef struct { int id; int hp; int ammo; } PlayerData;");
        l.hints.push_back(L"В функции: p->hp += amount;");
        list.push_back(l);
    }
    {
        Lesson l;
        l.id = 10;
        l.title = L"Урок 10: Переход к C++: классы, инкапсуляция и ссылки &";
        l.lang = L"C++";
        l.difficulty = L"Средний";
        l.theory_part1 = L"Язык C++ создавался как 'C с классами'. C++ сохраняет всю низкоуровневую мощь Си, но добавляет Объектно-Ориентированное Программирование (ООП) с нулевыми накладными расходами (Zero-Cost Abstractions).\n"
    "\n"
    "Ссылки (References, &):\n"
    "В C++ появилась ссылка — безопасный псевдоним существующего объекта:\n"
    "void modify(int &ref) {\n"
    "    ref = 500; // меняет оригинальную переменную без указателей и *!\n"
    "}\n"
    "В отличие от указателей, ссылка:\n"
    "- Не может быть нулевой (nullptr).\n"
    "- Не может быть перепривязана к другому объекту.\n"
    "\n"
    "Классы (class) в C++:\n"
    "Класс объединяет данные (поля) и функции (методы).\n"
    "Спецификаторы доступа:\n"
    "- private: доступно только методам самого класса (скрытая реализация).\n"
    "- public: внешний интерфейс.\n"
    "\n"
    "Конструктор и деструктор:\n"
    "- Конструктор: вызывается автоматически при рождении объекта.\n"
    "- Деструктор (~ClassName): вызывается автоматически при выходе из области видимости { } или при delete. Это основа идиомы RAII!";
        l.quiz.question = L"В чем главное отличие ссылки (int &ref) от указателя (int *ptr)?";
        {
            QuizOption opt;
            opt.id = L"a";
            opt.text = L"Ссылка не может быть nullptr, инициализируется один раз и не требует оператора разыменования (*)";
            opt.correct = true;
            opt.explanation = L"Верно! Ссылка — это синтаксический псевдоним переменной, гарантирующий валидность объекта.";
            l.quiz.options.push_back(opt);
        }
        {
            QuizOption opt;
            opt.id = L"b";
            opt.text = L"Ссылка занимает 100 байт памяти и работает медленнее указателя";
            opt.correct = false;
            opt.explanation = L"На машинном уровне ссылка компилируется в тот же самый указатель, накладных расходов ноль.";
            l.quiz.options.push_back(opt);
        }
        l.theory_part2 = L"Указатель this:\n"
    "Внутри любого нестатического метода класса неявно доступен указатель this, хранящий адрес текущего экземпляра объекта в памяти.";
        l.task = L"Создайте класс SafeBox с private полем int secret_.\n"
    "Сделайте public конструктор SafeBox(int code) и метод int getSecret() const.\n"
    "В main создайте SafeBox box(777); и выведите:\n"
    "Secret Code: 777";
        l.initial_code = L"#include <iostream>\n"
    "\n"
    "// Создайте класс SafeBox:\n"
    "\n"
    "int main() {\n"
    "    SafeBox box(777);\n"
    "    std::cout << \"Secret Code: \" << box.getSecret() << std::endl;\n"
    "    return 0;\n"
    "}\n"
    "";
        l.solution = L"#include <iostream>\n"
    "\n"
    "class SafeBox {\n"
    "private:\n"
    "    int secret_;\n"
    "\n"
    "public:\n"
    "    SafeBox(int code) : secret_(code) {}\n"
    "\n"
    "    int getSecret() const {\n"
    "        return secret_;\n"
    "    }\n"
    "};\n"
    "\n"
    "int main() {\n"
    "    SafeBox box(777);\n"
    "    std::cout << \"Secret Code: \" << box.getSecret() << std::endl;\n"
    "    return 0;\n"
    "}\n"
    "";
        l.expected_output = L"Secret Code: 777\n"
    "";
        l.hints.push_back(L"private: int secret_;");
        l.hints.push_back(L"public: SafeBox(int code) : secret_(code) {}");
        list.push_back(l);
    }
    {
        Lesson l;
        l.id = 11;
        l.title = L"Урок 11: Умные указатели Modern C++ (std::unique_ptr, RAII)";
        l.lang = L"C++";
        l.difficulty = L"Продвинутый";
        l.theory_part1 = L"Сырые указатели с new и delete — главный источник критических уязвимостей в ПО (70% всех уязвимостей Microsoft и Google происходят из-за ошибок управления памятью).\n"
    "Modern C++ (начиная с C++11) решил эту проблему раз и навсегда концепцией RAII и Умными Указателями (<memory>).\n"
    "\n"
    "RAII (Resource Acquisition Is Initialization):\n"
    "Ресурс (память, файл, хэндл процесса) захватывается в конструкторе и гарантированно освобождается в деструкторе, даже если в программе выброшено исключение!\n"
    "\n"
    "std::unique_ptr:\n"
    "- Единоличное владение объектом в куче.\n"
    "- При выходе unique_ptr из области видимости { }, он автоматически вызывает delete!\n"
    "- Нулевые накладные расходы (размер ровно 8 байт, как у сырого указателя).\n"
    "- Создание:\n"
    "  #include <memory>\n"
    "  auto ptr = std::make_unique<int>(100);\n"
    "\n"
    "std::shared_ptr:\n"
    "- Разделяемое владение со счетчиком ссылок (Reference Count).\n"
    "- Объект удаляется только когда последний shared_ptr уничтожен.";
        l.quiz.question = L"Почему в Modern C++ рекомендуется предпочитать std::unique_ptr вместо сырого `new` / `delete`?";
        {
            QuizOption opt;
            opt.id = L"a";
            opt.text = L"unique_ptr автоматически освобождает память в деструкторе, предотвращая утечки памяти и не создавая накладных расходов";
            opt.correct = true;
            opt.explanation = L"Абсолютно верно! Принцип RAII гарантирует освобождение ресурсов при выходе из скобок {} без риска забыть delete.";
            l.quiz.options.push_back(opt);
        }
        {
            QuizOption opt;
            opt.id = L"b";
            opt.text = L"unique_ptr делает программу на 500% быстрее";
            opt.correct = false;
            opt.explanation = L"Скорость ровно такая же, как у сырого указателя (Zero-Cost).";
            l.quiz.options.push_back(opt);
        }
        l.theory_part2 = L"unique_ptr нельзя скопировать (конструктор копирования удален), но можно передать владение через std::move:\n"
    "std::unique_ptr<int> p2 = std::move(ptr); // ptr станет nullptr, а p2 завладеет объектом.";
        l.task = L"Используя std::make_unique, выделите в куче число int со значением 4096.\n"
    "Разыменуйте его и напечатайте:\n"
    "Unique value: 4096";
        l.initial_code = L"#include <iostream>\n"
    "#include <memory>\n"
    "\n"
    "int main() {\n"
    "    // Создайте unique_ptr с помощью std::make_unique:\n"
    "    \n"
    "    // Разыменуйте и выведите:\n"
    "    \n"
    "    return 0;\n"
    "}\n"
    "";
        l.solution = L"#include <iostream>\n"
    "#include <memory>\n"
    "\n"
    "int main() {\n"
    "    auto ptr = std::make_unique<int>(4096);\n"
    "    std::cout << \"Unique value: \" << *ptr << std::endl;\n"
    "    return 0;\n"
    "}\n"
    "";
        l.expected_output = L"Unique value: 4096\n"
    "";
        l.hints.push_back(L"auto ptr = std::make_unique<int>(4096);");
        l.hints.push_back(L"Выведите: *ptr");
        list.push_back(l);
    }
    {
        Lesson l;
        l.id = 12;
        l.title = L"Урок 12: Введение в Windows API (WinAPI) и типы Win32";
        l.lang = L"C++";
        l.difficulty = L"Продвинутый";
        l.theory_part1 = L"Добро пожаловать в высшую лигу системного программирования для Windows!\n"
    "Windows API (WinAPI) — это интерфейс ядра и подсистем Microsoft Windows. Именно на WinAPI написаны системные утилиты, античиты, дебаггеры, трейнеры и сам интерфейс Windows.\n"
    "\n"
    "Подключение:\n"
    "#include <windows.h>\n"
    "\n"
    "Фундаментальные типы Win32 (псевдонимы в windows.h):\n"
    "- BOOL: целое число (TRUE = 1, FALSE = 0).\n"
    "- BYTE: беззнаковый 8-битный байт (unsigned char).\n"
    "- WORD: 16-битное число (2 байта).\n"
    "- DWORD: Double Word — 32-битное число (4 байта, unsigned long).\n"
    "- QWORD: Quad Word — 64-битное число (8 байт).\n"
    "- LPVOID: Long Pointer to Void (void*) — сырой указатель на память.\n"
    "- LPCSTR: const char* (указатель на строку ANSI).\n"
    "- LPCWSTR: const wchar_t* (указатель на Unicode UTF-16 строку).\n"
    "- HANDLE: Непрозрачный числовой дескриптор системного ресурса (процесса, потока, файла, мьютекса) в таблице ядра операционной системы!\n"
    "- HWND: Дескриптор окна.\n"
    "\n"
    "Обработка ошибок:\n"
    "Большинство функций WinAPI в случае ошибки возвращают 0 или NULL.\n"
    "Чтобы узнать точную причину ошибки, вызывается функция GetLastError(), возвращающая числовой код ошибки (например, ERROR_ACCESS_DENIED = 5).";
        l.quiz.question = L"Что представляет собой тип HANDLE в Windows API?";
        {
            QuizOption opt;
            opt.id = L"a";
            opt.text = L"Непрозрачный системный дескриптор (индекс в таблице объектов ядра ОС) для управления процессами, файлами или потоками";
            opt.correct = true;
            opt.explanation = L"Верно! HANDLE — это абстрактный токен ядра, выдаваемый операционной системой для безопасного управления ресурсом.";
            l.quiz.options.push_back(opt);
        }
        {
            QuizOption opt;
            opt.id = L"b";
            opt.text = L"Обычная переменная float для хранения координат мыши";
            opt.correct = false;
            opt.explanation = L"Неверно. HANDLE — ключевой тип дескриптора ядра Windows.";
            l.quiz.options.push_back(opt);
        }
        l.theory_part2 = L"Соглашение об именовании в WinAPI:\n"
    "Многие функции существуют в двух вариантах:\n"
    "- Функция с суффиксом 'A' (ANSI, char*): MessageBoxA\n"
    "- Функция с суффиксом 'W' (Wide/Unicode, wchar_t*): MessageBoxW\n"
    "В современных приложениях всегда рекомендуется использовать Unicode ('W') версию.";
        l.task = L"Изучите типы Win32:\n"
    "Объявите переменные:\n"
    "DWORD pid = 1337;\n"
    "BOOL is_running = 1;\n"
    "Выведите в stdout:\n"
    "Process ID: 1337, Status: Active";
        l.initial_code = L"#include <stdio.h>\n"
    "\n"
    "// В эмуляции определим Win32 типы:\n"
    "typedef unsigned long DWORD;\n"
    "typedef int BOOL;\n"
    "\n"
    "int main(void) {\n"
    "    DWORD pid = 1337;\n"
    "    BOOL is_running = 1;\n"
    "\n"
    "    // Выведите строку:\n"
    "    \n"
    "    return 0;\n"
    "}\n"
    "";
        l.solution = L"#include <stdio.h>\n"
    "\n"
    "typedef unsigned long DWORD;\n"
    "typedef int BOOL;\n"
    "\n"
    "int main(void) {\n"
    "    DWORD pid = 1337;\n"
    "    BOOL is_running = 1;\n"
    "\n"
    "    if (is_running) {\n"
    "        printf(\"Process ID: %lu, Status: Active\\n\", pid);\n"
    "    }\n"
    "    return 0;\n"
    "}\n"
    "";
        l.expected_output = L"Process ID: 1337, Status: Active\n"
    "";
        l.hints.push_back(L"Используйте %lu для типа DWORD (unsigned long).");
        l.hints.push_back(L"Выведите: Process ID: 1337, Status: Active");
        list.push_back(l);
    }
    {
        Lesson l;
        l.id = 13;
        l.title = L"Урок 13: Виртуальная память Windows и права доступа к страницам";
        l.lang = L"C++";
        l.difficulty = L"Эксперт";
        l.theory_part1 = L"Виртуальная память (Virtual Memory Architecture):\n"
    "В современных операционных системах ни один процесс не обращается к физическим планкам RAM напрямую!\n"
    "Каждый процесс живет в своем собственном изолированном Виртуальном Адресном Пространстве (Virtual Address Space):\n"
    "- В 32-битных приложениях: диапазон адресов 0x00000000 .. 0x7FFFFFFF (2 ГБ пространства пользователя).\n"
    "- В 64-битных приложениях: гигантский диапазон до 128 ТБ (0x0000000000000000 .. 0x7FFFFFFFFFFF)!\n"
    "\n"
    "Страницы памяти (Pages):\n"
    "Память делится на страницы фиксированного размера — стандартно 4096 байт (4 КБ).\n"
    "Процессор (блок MMU) транслирует виртуальные адреса в физические через таблицы страниц (Page Tables).\n"
    "\n"
    "Флаги защиты страниц памяти (Page Protection):\n"
    "Каждая страница имеет строгие права доступа:\n"
    "- PAGE_NOACCESS: обращение запрещено (краш).\n"
    "- PAGE_READONLY: разрешено только чтение (попытка записи вызывает Access Violation).\n"
    "- PAGE_READWRITE: чтение и запись (обычная память кучи, стека и переменных).\n"
    "- PAGE_EXECUTE_READ: исполнение кода и чтение (секция .text программы).\n"
    "- PAGE_EXECUTE_READWRITE: чтение, запись и исполнение (часто используется для хуков и инъекций шеллкода).\n"
    "\n"
    "Функции WinAPI:\n"
    "- VirtualAlloc / VirtualFree: выделение виртуальных страниц.\n"
    "- VirtualProtect: изменение прав доступа к странице памяти.";
        l.quiz.question = L"Какой стандартный размер страницы памяти в архитектуре x86/x64 Windows?";
        {
            QuizOption opt;
            opt.id = L"a";
            opt.text = L"4096 байт (4 КБ)";
            opt.correct = true;
            opt.explanation = L"Верно! 4096 байт (0x1000) — стандартный размер страницы виртуальной памяти в архитектуре x86 и x86_64.";
            l.quiz.options.push_back(opt);
        }
        {
            QuizOption opt;
            opt.id = L"b";
            opt.text = L"64 байта";
            opt.correct = false;
            opt.explanation = L"64 байта — это размер строки кэша процессора (Cache Line), а не страницы памяти.";
            l.quiz.options.push_back(opt);
        }
        l.theory_part2 = L"Если попытаться изменить байты в секции кода программы, защищенной PAGE_EXECUTE_READ, программа немедленно упадет с ошибкой 0xC0000005.\n"
    "Чтобы пропатчить инструкцию в памяти (например, заменить JNE на NOP), трейнеры сначала вызывают VirtualProtect, устанавливают PAGE_EXECUTE_READWRITE, записывают байты и восстанавливают исходную защиту!";
        l.task = L"Изучите размер страницы памяти:\n"
    "Объявите константу size_t page_size = 4096;\n"
    "Вычислите, сколько целых чисел int (по 4 байта) помещается в одну страницу памяти:\n"
    "Integers in 4KB page: 1024";
        l.initial_code = L"#include <stdio.h>\n"
    "\n"
    "int main(void) {\n"
    "    size_t page_size = 4096;\n"
    "    size_t int_size = sizeof(int);\n"
    "\n"
    "    // Посчитайте количество:\n"
    "    size_t count = 0;\n"
    "    \n"
    "    printf(\"Integers in 4KB page: %zu\\n\", count);\n"
    "    return 0;\n"
    "}\n"
    "";
        l.solution = L"#include <stdio.h>\n"
    "\n"
    "int main(void) {\n"
    "    size_t page_size = 4096;\n"
    "    size_t int_size = sizeof(int);\n"
    "    size_t count = page_size / int_size;\n"
    "\n"
    "    printf(\"Integers in 4KB page: %zu\\n\", count);\n"
    "    return 0;\n"
    "}\n"
    "";
        l.expected_output = L"Integers in 4KB page: 1024\n"
    "";
        l.hints.push_back(L"count = page_size / int_size;");
        list.push_back(l);
    }
    {
        Lesson l;
        l.id = 14;
        l.title = L"Урок 14: Процессы в Windows, PID и функция OpenProcess";
        l.lang = L"C++";
        l.difficulty = L"Эксперт";
        l.theory_part1 = L"Идентификатор процесса (Process ID / PID):\n"
    "Каждому запущенному процессу в Windows операционная система присваивает уникальное число — PID (например, 4820).\n"
    "\n"
    "Функция OpenProcess:\n"
    "Чтобы взаимодействовать с чужим процессом (читать память, внедрять поток или изменять переменные), программа должна открыть дескриптор (HANDLE) целевого процесса с помощью функции OpenProcess:\n"
    "\n"
    "HANDLE OpenProcess(\n"
    "    DWORD dwDesiredAccess,  // Требуемые права доступа\n"
    "    BOOL  bInheritHandle,   // Наследование дескриптора (обычно FALSE)\n"
    "    DWORD dwProcessId       // PID целевого процесса\n"
    ");\n"
    "\n"
    "Флаги доступа (dwDesiredAccess):\n"
    "- PROCESS_VM_READ (0x0010): право читать память процесса (ReadProcessMemory).\n"
    "- PROCESS_VM_WRITE (0x0020): право записывать в память процесса (WriteProcessMemory).\n"
    "- PROCESS_VM_OPERATION (0x0008): право модифицировать виртуальную память (VirtualProtectEx).\n"
    "- PROCESS_ALL_ACCESS (0x1F0FFF): полные права доступа на любые действия.\n"
    "\n"
    "Закрытие дескриптора:\n"
    "После завершения работы с процессом дескриптор ОБЯЗАТЕЛЬНО должен быть закрыт:\n"
    "CloseHandle(hProcess);\n"
    "Иначе в ядре операционной системы произойдет утечка дескрипторов (Handle Leak)!";
        l.quiz.question = L"Какую функцию Windows API необходимо вызвать после окончания работы с открытым HANDLE процесса?";
        {
            QuizOption opt;
            opt.id = L"a";
            opt.text = L"CloseHandle(hProcess);";
            opt.correct = true;
            opt.explanation = L"Верно! CloseHandle закрывает дескриптор ядра и предотвращает утечку ресурсов ОС.";
            l.quiz.options.push_back(opt);
        }
        {
            QuizOption opt;
            opt.id = L"b";
            opt.text = L"free(hProcess);";
            opt.correct = false;
            opt.explanation = L"Неверно. free() освобождает память в куче Си, а дескрипторы ядра закрываются только через CloseHandle.";
            l.quiz.options.push_back(opt);
        }
        l.theory_part2 = L"Если OpenProcess вернул NULL, значит доступ не получен.\n"
    "Типичные причины:\n"
    "1. Процесс с таким PID уже завершился.\n"
    "2. Недостаточно прав (процесс запущен от имени Администратора или защищен античитом / PatchGuard). Требуется привилегия SeDebugPrivilege.";
        l.task = L"Смоделируйте логику открытия процесса:\n"
    "Пусть целевой PID = 2048, флаги доступа = 0x0010 (PROCESS_VM_READ).\n"
    "Выведите строку проверки статуса:\n"
    "Target PID: 2048, DesiredAccess: 0x0010, Status: Handle Acquired";
        l.initial_code = L"#include <stdio.h>\n"
    "\n"
    "int main(void) {\n"
    "    unsigned long target_pid = 2048;\n"
    "    unsigned long desired_access = 0x0010;\n"
    "\n"
    "    // Выведите результат:\n"
    "    \n"
    "    return 0;\n"
    "}\n"
    "";
        l.solution = L"#include <stdio.h>\n"
    "\n"
    "int main(void) {\n"
    "    unsigned long target_pid = 2048;\n"
    "    unsigned long desired_access = 0x0010;\n"
    "\n"
    "    printf(\"Target PID: %lu, DesiredAccess: 0x%04lX, Status: Handle Acquired\\n\", target_pid, desired_access);\n"
    "    return 0;\n"
    "}\n"
    "";
        l.expected_output = L"Target PID: 2048, DesiredAccess: 0x0010, Status: Handle Acquired\n"
    "";
        l.hints.push_back(L"Используйте формат 0x%04lX для вывода шестнадцатеричного флага доступа.");
        list.push_back(l);
    }
    {
        Lesson l;
        l.id = 15;
        l.title = L"Урок 15: Чтение памяти другого процесса через ReadProcessMemory";
        l.lang = L"C++";
        l.difficulty = L"Эксперт";
        l.theory_part1 = L"Мы подошли к главному инструменту анализа памяти в Windows — функции ReadProcessMemory!\n"
    "С ее помощью отладчики (x64dbg, Cheat Engine) и трейнеры считывают значения здоровья, патронов, координат или указателей из чужого адресного пространства.\n"
    "\n"
    "Сигнатура функции:\n"
    "BOOL ReadProcessMemory(\n"
    "    HANDLE  hProcess,             // Дескриптор целевого процесса (из OpenProcess)\n"
    "    LPCVOID lpBaseAddress,        // Адрес в памяти целевого процесса, откуда читать\n"
    "    LPVOID  lpBuffer,             // Адрес в НАШЕЙ памяти (буфер), куда сохранить данные\n"
    "    SIZE_T  nSize,                // Сколько байт прочитать (например, sizeof(int))\n"
    "    SIZE_T *lpNumberOfBytesRead   // Сколько байт реально прочитано (можно передать NULL)\n"
    ");\n"
    "\n"
    "Как это работает по шагам:\n"
    "1. Пусть в целевой игре переменная здоровья игрока int health = 100 находится по адресу 0x0045A120.\n"
    "2. В нашей программе мы заводим локальную переменную:\n"
    "   int my_health = 0;\n"
    "3. Вызываем ReadProcessMemory:\n"
    "   ReadProcessMemory(hProcess, (LPCVOID)0x0045A120, &my_health, sizeof(my_health), NULL);\n"
    "4. Ядро Windows приостанавливает поток, считывает 4 байта из страниц памяти целевого процесса и копирует в наш адрес &my_health.\n"
    "5. Теперь в переменной my_health лежит точное значение 100!";
        l.quiz.question = L"Что передается в качестве второго аргумента (lpBaseAddress) в ReadProcessMemory?";
        {
            QuizOption opt;
            opt.id = L"a";
            opt.text = L"Адрес в памяти целевого процесса, откуда нужно прочитать байты";
            opt.correct = true;
            opt.explanation = L"Верно! lpBaseAddress — это виртуальный адрес ячейки памяти внутри целевого процесса.";
            l.quiz.options.push_back(opt);
        }
        {
            QuizOption opt;
            opt.id = L"b";
            opt.text = L"Путь к файлу на жестком диске";
            opt.correct = false;
            opt.explanation = L"Неверно. ReadProcessMemory работает с ОЗУ, а не с диском.";
            l.quiz.options.push_back(opt);
        }
        l.theory_part2 = L"Многоуровневые указатели (Pointer Paths):\n"
    "В реальных играх адреса меняются при каждом перезапуске (динамическая куча).\n"
    "Поэтому используется цепочка смещений (Offsets):\n"
    "BaseAddress -> [Base + 0x10] -> [Address + 0x48] -> Final Health Value.\n"
    "ReadProcessMemory вызывается последовательно для каждого указателя в цепочке!";
        l.task = L"Смоделируйте чтение значения через эмулятор буфера:\n"
    "Пусть имитированная память target_ram[4] = {10, 20, 999, 40};\n"
    "Адрес смещения offset = 2.\n"
    "Прочитайте значение по смещению и выведите:\n"
    "ReadProcessMemory Result: 999 HP (bytes read: 4)";
        l.initial_code = L"#include <stdio.h>\n"
    "\n"
    "int main(void) {\n"
    "    int target_ram[4] = {10, 20, 999, 40};\n"
    "    size_t offset = 2;\n"
    "\n"
    "    int read_buffer = 0;\n"
    "    size_t bytes_read = sizeof(int);\n"
    "\n"
    "    // Скопируйте значение из target_ram[offset] в read_buffer:\n"
    "    \n"
    "    printf(\"ReadProcessMemory Result: %d HP (bytes read: %zu)\\n\", read_buffer, bytes_read);\n"
    "    return 0;\n"
    "}\n"
    "";
        l.solution = L"#include <stdio.h>\n"
    "\n"
    "int main(void) {\n"
    "    int target_ram[4] = {10, 20, 999, 40};\n"
    "    size_t offset = 2;\n"
    "\n"
    "    int read_buffer = target_ram[offset];\n"
    "    size_t bytes_read = sizeof(int);\n"
    "\n"
    "    printf(\"ReadProcessMemory Result: %d HP (bytes read: %zu)\\n\", read_buffer, bytes_read);\n"
    "    return 0;\n"
    "}\n"
    "";
        l.expected_output = L"ReadProcessMemory Result: 999 HP (bytes read: 4)\n"
    "";
        l.hints.push_back(L"read_buffer = target_ram[offset];");
        list.push_back(l);
    }
    {
        Lesson l;
        l.id = 16;
        l.title = L"Урок 16: Запись в память процесса через WriteProcessMemory и патчинг NOP";
        l.lang = L"C++";
        l.difficulty = L"Эксперт";
        l.theory_part1 = L"Изменение памяти (Memory Editing):\n"
    "Функция WriteProcessMemory позволяет перезаписать память чужого процесса.\n"
    "\n"
    "Сигнатура:\n"
    "BOOL WriteProcessMemory(\n"
    "    HANDLE  hProcess,               // Дескриптор процесса (требует PROCESS_VM_WRITE)\n"
    "    LPVOID  lpBaseAddress,          // Адрес в чужом процессе, КУДА писать\n"
    "    LPCVOID lpBuffer,               // Буфер в нашей программе, ОТКУДА брать байты\n"
    "    SIZE_T  nSize,                  // Сколько байт записать\n"
    "    SIZE_T *lpNumberOfBytesWritten  // Сколько байт записано реально\n"
    ");\n"
    "\n"
    "Патчинг опкодов (Code Patching) и инструкция NOP:\n"
    "В процессорах архитектуры x86/x64 инструкция уменьшения здоровья выглядит как:\n"
    "SUB DWORD PTR [RAX+0x10], EDX   // Вычитание патронов или здоровья (байт-код: 29 50 10)\n"
    "Чтобы отключить расход патронов (Infinite Ammo), системный хакер заменяет эти инструкции на «пустые операции» — NOP (No Operation).\n"
    "Опкод инструкции NOP в x86/x64 равен одному байту: 0x90!\n"
    "Когда процессор доходит до байта 0x90, он ничего не делает и сразу переходит к следующей инструкции. Расход патронов отключен!";
        l.quiz.question = L"Какой опкод в архитектуре x86/x64 соответствует инструкции NOP (No Operation)?";
        {
            QuizOption opt;
            opt.id = L"a";
            opt.text = L"0x90";
            opt.correct = true;
            opt.explanation = L"Верно! Однобайтовая инструкция 0x90 (NOP) является классическим приемом патчинга в ассемблере x86.";
            l.quiz.options.push_back(opt);
        }
        {
            QuizOption opt;
            opt.id = L"b";
            opt.text = L"0x00";
            opt.correct = false;
            opt.explanation = L"0x00 в опкодах x86 — это часть инструкции ADD [RAX], AL, а не NOP.";
            l.quiz.options.push_back(opt);
        }
        {
            QuizOption opt;
            opt.id = L"c";
            opt.text = L"0xFF";
            opt.correct = false;
            opt.explanation = L"0xFF — это группа опкодов CALL/JMP/INC/DEC.";
            l.quiz.options.push_back(opt);
        }
        l.theory_part2 = L"Перед вызовом WriteProcessMemory для изменения секции кода (.text) необходимо вызвать VirtualProtectEx, чтобы сменить права страницы с PAGE_EXECUTE_READ на PAGE_EXECUTE_READWRITE, иначе функция завершится с кодом ERROR_ACCESS_DENIED.";
        l.task = L"Смоделируйте NOP-патчинг:\n"
    "Дан массив машинных инструкций:\n"
    "unsigned char code_bytes[3] = {0x29, 0x50, 0x10}; // sub [rax+10], edx\n"
    "Замените все 3 байта на опкод 0x90 (NOP).\n"
    "Выведите результат в шестнадцатеричном виде:\n"
    "Patched bytes: 0x90 0x90 0x90 (NOP applied)";
        l.initial_code = L"#include <stdio.h>\n"
    "\n"
    "int main(void) {\n"
    "    unsigned char code_bytes[3] = {0x29, 0x50, 0x10};\n"
    "\n"
    "    // Замените все 3 байта на 0x90:\n"
    "    \n"
    "    printf(\"Patched bytes: 0x%02X 0x%02X 0x%02X (NOP applied)\\n\",\n"
    "           code_bytes[0], code_bytes[1], code_bytes[2]);\n"
    "    return 0;\n"
    "}\n"
    "";
        l.solution = L"#include <stdio.h>\n"
    "\n"
    "int main(void) {\n"
    "    unsigned char code_bytes[3] = {0x29, 0x50, 0x10};\n"
    "    code_bytes[0] = 0x90;\n"
    "    code_bytes[1] = 0x90;\n"
    "    code_bytes[2] = 0x90;\n"
    "\n"
    "    printf(\"Patched bytes: 0x%02X 0x%02X 0x%02X (NOP applied)\\n\",\n"
    "           code_bytes[0], code_bytes[1], code_bytes[2]);\n"
    "    return 0;\n"
    "}\n"
    "";
        l.expected_output = L"Patched bytes: 0x90 0x90 0x90 (NOP applied)\n"
    "";
        l.hints.push_back(L"code_bytes[0] = 0x90; code_bytes[1] = 0x90; code_bytes[2] = 0x90;");
        list.push_back(l);
    }
    {
        Lesson l;
        l.id = 17;
        l.title = L"Урок 17: Финальный курсовой проект: Memory Trainer Engine на C++";
        l.lang = L"C++";
        l.difficulty = L"Эксперт";
        l.theory_part1 = L"Поздравляем! Вы прошли путь от азов языка Си до системной работы с виртуальной памятью и Windows API!\n"
    "Теперь вы обладаете полным арсеналом знаний:\n"
    "- Понимание архитектуры x86_64, регистров и страниц памяти.\n"
    "- Управление указателями, адресами и смещениями.\n"
    "- Структуры данных и ООП в C++.\n"
    "- Системные вызовы Windows: OpenProcess, ReadProcessMemory, WriteProcessMemory, CloseHandle.\n"
    "\n"
    "Архитектура собственного Memory Trainer Engine:\n"
    "Оформим законченный класс `ProcessMemoryManager`:\n"
    "1. Хранит дескриптор `HANDLE hProcess_` и `DWORD pid_`.\n"
    "2. Конструктор принимает PID и открывает процесс.\n"
    "3. Деструктор автоматически закрывает HANDLE (принцип RAII!).\n"
    "4. Шаблонный метод `template <typename T> T Read(uintptr_t address)` для безопасного чтения любого типа (int, float, struct).\n"
    "5. Шаблонный метод `template <typename T> bool Write(uintptr_t address, T value)` для записи значений.\n"
    "\n"
    "С этим классом вы сможете написать реальный трейнер или утилиту диагностики памяти для любой Windows-программы!";
        l.quiz.question = L"Почему оформление работы с памятью процесса в C++ класс с RAII деструктором является лучшей практикой?";
        {
            QuizOption opt;
            opt.id = L"a";
            opt.text = L"Деструктор класса гарантированно закроет дескриптор CloseHandle(hProcess_), предотвращая утечки ресурсов ядра ОС при выходе из области видимости";
            opt.correct = true;
            opt.explanation = L"Идеально! Это золотой стандарт надежного системного C++ софта.";
            l.quiz.options.push_back(opt);
        }
        {
            QuizOption opt;
            opt.id = L"b";
            opt.text = L"Потому что C++ запрещает использовать Си-функции";
            opt.correct = false;
            opt.explanation = L"C++ полностью обратно совместим с Си и WinAPI.";
            l.quiz.options.push_back(opt);
        }
        l.theory_part2 = L"Выпускное практическое задание:\n"
    "Реализуйте каркас системного класса `TrainerMemory`, прочитайте и обновите эмулированное значение переменной здоровья игрока!";
        l.task = L"Реализуйте класс TrainerMemory:\n"
    "- Метод int readInt(uintptr_t addr)\n"
    "- Метод void writeInt(uintptr_t addr, int val)\n"
    "В main примените его к адресу имитированного значения health = 100, запишите 9999 (GodMode) и выведите:\n"
    "[TrainerCode Engine] Target Health: 9999 (Freeze Active)";
        l.initial_code = L"#include <iostream>\n"
    "#include <cstdint>\n"
    "\n"
    "// Реализуйте класс TrainerMemory для работы с адресами памяти:\n"
    "class TrainerMemory {\n"
    "private:\n"
    "    int simulated_ram_[16];\n"
    "\n"
    "public:\n"
    "    TrainerMemory() {\n"
    "        for (int i = 0; i < 16; i++) simulated_ram_[i] = 0;\n"
    "        simulated_ram_[4] = 100; // По адресу смещения 4 лежит здоровье\n"
    "    }\n"
    "\n"
    "    int readInt(uintptr_t offset) {\n"
    "        return simulated_ram_[offset];\n"
    "    }\n"
    "\n"
    "    void writeInt(uintptr_t offset, int val) {\n"
    "        simulated_ram_[offset] = val;\n"
    "    }\n"
    "};\n"
    "\n"
    "int main() {\n"
    "    TrainerMemory trainer;\n"
    "    // Запишите 9999 по смещению 4 и выведите:\n"
    "    \n"
    "    return 0;\n"
    "}\n"
    "";
        l.solution = L"#include <iostream>\n"
    "#include <cstdint>\n"
    "\n"
    "class TrainerMemory {\n"
    "private:\n"
    "    int simulated_ram_[16];\n"
    "\n"
    "public:\n"
    "    TrainerMemory() {\n"
    "        for (int i = 0; i < 16; i++) simulated_ram_[i] = 0;\n"
    "        simulated_ram_[4] = 100;\n"
    "    }\n"
    "\n"
    "    int readInt(uintptr_t offset) {\n"
    "        return simulated_ram_[offset];\n"
    "    }\n"
    "\n"
    "    void writeInt(uintptr_t offset, int val) {\n"
    "        simulated_ram_[offset] = val;\n"
    "    }\n"
    "};\n"
    "\n"
    "int main() {\n"
    "    TrainerMemory trainer;\n"
    "    trainer.writeInt(4, 9999);\n"
    "    int current_hp = trainer.readInt(4);\n"
    "\n"
    "    std::cout << \"[TrainerCode Engine] Target Health: \" << current_hp << \" (Freeze Active)\" << std::endl;\n"
    "    return 0;\n"
    "}\n"
    "";
        l.expected_output = L"[TrainerCode Engine] Target Health: 9999 (Freeze Active)\n"
    "";
        l.hints.push_back(L"trainer.writeInt(4, 9999);");
        l.hints.push_back(L"Выведите: [TrainerCode Engine] Target Health: 9999 (Freeze Active)");
        list.push_back(l);
    }
    return list;
}
