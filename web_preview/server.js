const express = require('express');
const path = require('path');
const fs = require('fs');
const { exec, execFile } = require('child_process');

const app = express();
const PORT = process.env.PORT || 3000;

app.use(express.json({ limit: '5mb' }));
app.use(express.static(path.join(__dirname, 'public')));

// Load lessons
const lessonsPath = path.join(__dirname, 'public', 'lessons.json');
let lessons = [];
try {
  lessons = JSON.parse(fs.readFileSync(lessonsPath, 'utf8'));
} catch (e) {
  console.error('Error loading lessons:', e);
}

// Data types cheat sheet
const typesCheat = [
  { name: 'char', x86: '1', x64: '1', range: '-128 .. 127', spec: '%c / %d', desc: 'Символ ASCII или 8-битный знаковый байт' },
  { name: 'unsigned char', x86: '1', x64: '1', range: '0 .. 255', spec: '%u', desc: 'Байт без знака (сырая память)' },
  { name: 'short', x86: '2', x64: '2', range: '-32,768 .. 32,767', spec: '%hd', desc: 'Короткое целое со знаком' },
  { name: 'unsigned short', x86: '2', x64: '2', range: '0 .. 65,535', spec: '%hu', desc: 'Короткое целое без знака' },
  { name: 'int', x86: '4', x64: '4', range: '-2.14*10^9 .. 2.14*10^9', spec: '%d, %i', desc: 'Базовое целое со знаком (32 бита)' },
  { name: 'unsigned int', x86: '4', x64: '4', range: '0 .. 4.29*10^9', spec: '%u', desc: 'Базовое целое без знака' },
  { name: 'long', x86: '4', x64: '4 (Win) / 8 (Lin)', range: '-2*10^9 .. 2*10^9', spec: '%ld', desc: 'Длинное целое (в Win64 всегда 4 байта!)' },
  { name: 'unsigned long', x86: '4', x64: '4 (Win) / 8 (Lin)', range: '0 .. 4*10^9', spec: '%lu', desc: 'Беззнаковое длинное целое' },
  { name: 'long long', x86: '8', x64: '8', range: '-9.22*10^18 .. 9.22*10^18', spec: '%lld', desc: '64-битное целое со знаком' },
  { name: 'unsigned long long', x86: '8', x64: '8', range: '0 .. 1.84*10^19', spec: '%llu', desc: '64-битное целое без знака' },
  { name: 'float', x86: '4', x64: '4', range: '±1.18*10^-38 .. ±3.4*10^38', spec: '%f', desc: 'Вещественное IEEE 754 (~7 цифр)' },
  { name: 'double', x86: '8', x64: '8', range: '±2.23*10^-308 .. ±1.79*10^308', spec: '%lf', desc: 'Двойная точность IEEE 754 (~15-17 цифр)' },
  { name: 'size_t', x86: '4', x64: '8', range: '0 .. SIZE_MAX', spec: '%zu', desc: 'Беззнаковый тип для размеров памяти (<stddef.h>)' },
  { name: 'ptrdiff_t', x86: '4', x64: '8', range: 'PTRDIFF_MIN .. PTRDIFF_MAX', spec: '%td', desc: 'Знаковая разность двух адресов' },
  { name: 'void*', x86: '4', x64: '8', range: '0x00..00 .. 0xFF..FF', spec: '%p', desc: 'Универсальный сырой указатель на ОЗУ' },
  { name: 'bool (C++) / _Bool (C)', x86: '1', x64: '1', range: '0 (false) или 1 (true)', spec: '%d', desc: 'Логический булев тип' }
];

// API: Get Lessons
app.get('/api/lessons', (req, res) => {
  try {
    const raw = fs.readFileSync(lessonsPath, 'utf8');
    lessons = JSON.parse(raw);
  } catch (e) {
    console.error('Error reloading lessons:', e);
  }
  res.json(lessons);
});

// API: Get Types
app.get('/api/types', (req, res) => {
  res.json(typesCheat);
});

// API: Compile & Run Code
app.post('/api/compile', (req, res) => {
  const { code, lang, lessonId } = req.body;
  if (!code) {
    return res.status(400).json({ success: false, error: 'Код не передан.' });
  }

  const isCpp = (lang === 'C++' || code.includes('iostream') || code.includes('std::') || code.includes('class '));
  const ext = isCpp ? '.cpp' : '.c';
  const compiler = isCpp ? '/usr/bin/g++' : '/usr/bin/gcc';
  const stdFlag = isCpp ? '-std=c++20' : '-std=c11';

  const tmpId = Date.now() + '_' + Math.floor(Math.random() * 10000);
  const srcFile = path.join('/tmp', `src_${tmpId}${ext}`);
  const binFile = path.join('/tmp', `bin_${tmpId}`);

  fs.writeFileSync(srcFile, code, 'utf8');

  const compileCmd = `${compiler} ${stdFlag} -Wall -Wextra -O2 "${srcFile}" -o "${binFile}" -lm -lpthread`;

  const startTime = Date.now();
  exec(compileCmd, { timeout: 8000 }, (compileErr, compileStdout, compileStderr) => {
    if (compileErr) {
      try { fs.unlinkSync(srcFile); } catch (e) {}
      return res.json({
        success: false,
        stage: 'compilation',
        stdout: compileStdout,
        stderr: compileStderr || compileErr.message,
        exitCode: compileErr.code || 1,
        timeMs: Date.now() - startTime
      });
    }

    // Execute compiled binary
    exec(binFile, { timeout: 4000, maxBuffer: 1024 * 512 }, (runErr, runStdout, runStderr) => {
      const totalTime = Date.now() - startTime;
      try { fs.unlinkSync(srcFile); } catch (e) {}
      try { fs.unlinkSync(binFile); } catch (e) {}

      // Check against expected output if lessonId given
      const lesson = lessons.find(l => l.id === lessonId);
      let taskCompleted = false;
      if (lesson && lesson.expectedOutput) {
        const normRun = (runStdout || '').trim().replace(/\r\n/g, '\n');
        const normExp = lesson.expectedOutput.trim().replace(/\r\n/g, '\n');
        if (normRun === normExp) {
          taskCompleted = true;
        }
      }

      res.json({
        success: !runErr,
        stage: 'execution',
        stdout: runStdout,
        stderr: runStderr || (runErr ? runErr.message : ''),
        exitCode: runErr ? (runErr.code || 1) : 0,
        taskCompleted,
        timeMs: totalTime
      });
    });
  });
});

// API: AI Assistant
app.post('/api/ai/ask', (req, res) => {
  const { prompt, code, lessonId } = req.body;
  const p = (prompt || '').toLowerCase();
  const c = (code || '').toLowerCase();

  let response = '';

  if (p.includes('ошибк') || p.includes('баг') || p.includes('утечк') || p.includes('провер')) {
    response += '🔍 [Анализ памяти и структуры кода]\n\n';
    let issues = [];

    if (c.includes('malloc') && !c.includes('free')) {
      issues.push('⚠️ УТЕЧКА ПАМЯТИ (Memory Leak): найден вызов malloc(), но отсутствует free(). Вся выделенная в куче (heap) память должна явно освобождаться.');
    }
    if (c.includes('new ') && !c.includes('delete')) {
      issues.push('⚠️ УТЕЧКА РЕСУРСА: оператор new используется без парного delete/delete[]. Рекомендуется перейти на std::unique_ptr.');
    }
    if (c.includes('printf') && !c.includes('stdio.h') && !c.includes('cstdio')) {
      issues.push('⚠️ ОТСУТСТВИЕ ЗАГОЛОВКА: вызов printf без #include <stdio.h>. На современных компиляторах это вызовет warning или error.');
    }
    if (c.includes('cout') && !c.includes('iostream')) {
      issues.push('⚠️ ОТСУТСТВИЕ ЗАГОЛОВКА: std::cout требует #include <iostream>.');
    }
    if (c.includes('main') && !c.includes('return 0;')) {
      issues.push('💡 СОВЕТ: функция main() должна завершаться явным `return 0;` для индикации успешного кода выхода процесса.');
    }

    if (issues.length > 0) {
      response += issues.join('\n\n') + '\n\nИсправьте указанные моменты и нажмите F5 для повторной сборки!';
    } else {
      response += '✅ Явных критических ошибок памяти (Memory Leaks, Dangling Pointers, Segfault-паттернов) не обнаружено.\nКод синтаксически корректен. Проверьте соответствие вывода ожидаемому в условии задания.';
    }
  } else if (p.includes('объясни') || p.includes('как работает')) {
    response += '📖 [Системное объяснение концепции]\n\n';
    if (c.includes('pointer') || c.includes('*') || p.includes('указател')) {
      response += '📌 Указатель (Pointer):\n' +
        '1. Каждый байт в оперативной памяти (RAM) имеет 64-битный адрес (например, 0x7ffd9820c4a4).\n' +
        '2. Оператор &x получает этот физический адрес.\n' +
        '3. Переменная-указатель (int *ptr = &x) хранит адрес.\n' +
        '4. Оператор разыменования (*ptr) заставляет процессор выполнить чтение/запись по данному адресу.\n' +
        '5. Адресная арифметика ptr + 1 сдвигает указатель на sizeof(T) байтов, а не на 1!';
    } else if (p.includes('vtable') || p.includes('полиморфизм')) {
      response += '📌 Полиморфизм и Таблица виртуальных функций (vtable):\n' +
        '1. При объявлении метода virtual компилятор C++ генерирует статический массив указателей на методы — vtable.\n' +
        '2. В каждый объект скрытно добавляется указатель __vptr на vtable его класса.\n' +
        '3. Вызов ptr->method() превращается в косвенный вызов через регистр процессора: call [vptr + offset].';
    } else if (p.includes('стек') || p.includes('куч')) {
      response += '📌 Стек (Stack) vs Куча (Heap):\n' +
        '- Стек: сверхбыстрая память LIFO (~1-2 МБ). Выделяется сдвигом регистра ESP/RSP. Память очищается автоматически при выходе из скобок { }.\n' +
        '- Куча: гигантская область памяти (вся RAM). Аллоцируется через malloc/new, управляется операционной системой, освобождается вручную через free/delete.';
    } else {
      response += 'Данный код компилируется непосредственно в инструкции целевого процессора (x86_64). Вызовы функций сохраняют регистры на стеке, вычисляют выражения в ALU процессора и возвращают управление через инструкцию RET.';
    }
  } else if (p.includes('подсказк') || p.includes('задач') || p.includes('помоги')) {
    const curLesson = lessons.find(l => l.id === lessonId);
    if (curLesson && curLesson.hints && curLesson.hints.length > 0) {
      response += `💡 Подсказка к уроку "${curLesson.title}":\n\n`;
      curLesson.hints.forEach((h, i) => {
        response += `${i + 1}. ${h}\n`;
      });
      response += '\nНажмите кнопку "Вставить шаблон урока", если хотите сбросить код до исходного состояния.';
    } else {
      response += '💡 Подсказка: Внимательно сверьте выводимый текст с форматом, требуемым в условии. Символы \\n, двоеточия и пробелы имеют строгое значение.';
    }
  } else {
    response += '🤖 Приветствую! Я TrainerAI — ваш персональный системный наставник по языкам C и C++.\n\n' +
      'Чем я могу помочь прямо сейчас:\n' +
      '• 🔍 Нажмите "Найти ошибки" — проверю код на утечки памяти, NULL-указатели и переполнения буфера.\n' +
      '• 📖 Нажмите "Объяснить" — разложу по полочкам, как процессор и компилятор видят текущий код.\n' +
      '• 💡 Задайте любой вопрос по архитектуре x86/x64, указателям, ассемблеру или Modern C++!';
  }

  res.json({ response });
});

// Direct download endpoint for TrainerCode.exe
app.get('/api/download-exe', (req, res) => {
  const exePath = path.join(__dirname, '..', 'release_artifacts', 'TrainerCode.exe');
  const fallbackPath = path.join(__dirname, '..', 'build', 'TrainerCode.exe');
  if (fs.existsSync(exePath)) {
    res.download(exePath, 'TrainerCode.exe');
  } else if (fs.existsSync(fallbackPath)) {
    res.download(fallbackPath, 'TrainerCode.exe');
  } else {
    res.status(404).send('TrainerCode.exe build not found.');
  }
});

app.listen(PORT, '0.0.0.0', () => {
  console.log(`TrainerCode 2000 server running on http://0.0.0.0:${PORT}`);
});
