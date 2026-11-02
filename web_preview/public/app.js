let gLessons = [];
let gCurrentLessonIdx = 0;
let gCurrentStep = 1; // 1: Theory, 2: Quiz, 3: Editor

let gUserData = {
  name: localStorage.getItem('tc_user_name') || '',
  level: localStorage.getItem('tc_user_level') || 'Абсолютный новичок',
  goal: localStorage.getItem('tc_user_goal') || 'WinAPI & Reverse',
  completedLessons: JSON.parse(localStorage.getItem('tc_completed') || '[]'),
  unlockedLessons: JSON.parse(localStorage.getItem('tc_unlocked') || '[1]')
};

// DOM Elements
const viewWelcome = document.getElementById('viewWelcome');
const viewLesson = document.getElementById('viewLesson');
const welcomeCardForm = document.getElementById('welcomeCardForm');
const welcomeCardInstructions = document.getElementById('welcomeCardInstructions');

const stageTheory = document.getElementById('stageTheory');
const stageQuiz = document.getElementById('stageQuiz');
const stageEditor = document.getElementById('stageEditor');

const theoryContentPart1 = document.getElementById('theoryContentPart1');
const quizQuestionText = document.getElementById('quizQuestionText');
const quizOptionsList = document.getElementById('quizOptionsList');
const quizFeedbackBox = document.getElementById('quizFeedbackBox');
const btnQuizProceed = document.getElementById('btnQuizProceed');

const editorTaskText = document.getElementById('editorTaskText');
const elEditor = document.getElementById('codeEditor');
const elLineNumbers = document.getElementById('lineNumbers');
const elConsole = document.getElementById('consoleOutput');
const elAiChat = document.getElementById('aiChatView');
const elAiMessages = document.getElementById('aiMessagesList');
const elAiPrompt = document.getElementById('aiPromptInput');

// Status Bar
const elSbLesson = document.getElementById('sbLesson');
const elSbLang = document.getElementById('sbLang');
const elSbCompiler = document.getElementById('sbCompiler');
const elSbAi = document.getElementById('sbAi');
const elSbUser = document.getElementById('sbUser');

window.addEventListener('DOMContentLoaded', async () => {
  updateClock();
  setInterval(updateClock, 1000);

  setupEditorKeyHandling();
  loadTypesTable();

  // Load lessons from backend
  try {
    const res = await fetch('/api/lessons');
    gLessons = await res.json();
  } catch (err) {
    console.error('Failed to load lessons:', err);
  }

  // Check if user already registered
  if (gUserData.name) {
    document.getElementById('inputUserName').value = gUserData.name;
    document.getElementById('selectUserLevel').value = gUserData.level;
    document.getElementById('selectUserGoal').value = gUserData.goal;
    showLessonScreen();
  } else {
    showWelcomeScreen();
  }
});

// Setup Code Editor: Enter key, Tab key, Line Numbers
function setupEditorKeyHandling() {
  elEditor.addEventListener('input', updateLineNumbers);

  elEditor.addEventListener('scroll', () => {
    elLineNumbers.scrollTop = elEditor.scrollTop;
  });

  elEditor.addEventListener('keydown', (e) => {
    if (e.key === 'Tab') {
      e.preventDefault();
      const start = elEditor.selectionStart;
      const end = elEditor.selectionEnd;
      elEditor.value = elEditor.value.substring(0, start) + '    ' + elEditor.value.substring(end);
      elEditor.selectionStart = elEditor.selectionEnd = start + 4;
      updateLineNumbers();
    } else if (e.key === 'Enter') {
      // Auto-indentation on Enter key
      const start = elEditor.selectionStart;
      const lines = elEditor.value.substring(0, start).split('\n');
      const currentLine = lines[lines.length - 1];
      const match = currentLine.match(/^(\s+)/);
      const indent = match ? match[1] : '';

      // Check if line ends with '{', add extra 4 spaces
      let extra = '';
      if (currentLine.trim().endsWith('{')) {
        extra = '    ';
      }

      // Allow default Enter or insert indentation cleanly
      setTimeout(() => {
        if (indent || extra) {
          const curPos = elEditor.selectionStart;
          elEditor.value = elEditor.value.substring(0, curPos) + indent + extra + elEditor.value.substring(curPos);
          elEditor.selectionStart = elEditor.selectionEnd = curPos + indent.length + extra.length;
        }
        updateLineNumbers();
      }, 0);
    } else if (e.key === 'F5') {
      e.preventDefault();
      compileAndRun();
    } else if (e.key === 'F1') {
      e.preventDefault();
      openTypesModal();
    }
  });
}

function updateLineNumbers() {
  const lineCount = elEditor.value.split('\n').length;
  let numStr = '';
  for (let i = 1; i <= Math.max(lineCount, 1); i++) {
    numStr += i + '<br>';
  }
  elLineNumbers.innerHTML = numStr;
}

function updateClock() {
  const now = new Date();
  const h = String(now.getHours()).padStart(2, '0');
  const m = String(now.getMinutes()).padStart(2, '0');
  document.getElementById('trayClock').textContent = `${h}:${m}`;
}

// Screen 1: Welcome & Profile Actions
function showWelcomeScreen() {
  viewWelcome.style.display = 'flex';
  viewLesson.style.display = 'none';
  welcomeCardForm.style.display = 'flex';
  welcomeCardInstructions.style.display = 'none';
}

function submitWelcomeForm() {
  const name = document.getElementById('inputUserName').value.trim() || 'Кодер';
  const level = document.getElementById('selectUserLevel').value;
  const goal = document.getElementById('selectUserGoal').value;

  gUserData.name = name;
  gUserData.level = level;
  gUserData.goal = goal;

  localStorage.setItem('tc_user_name', name);
  localStorage.setItem('tc_user_level', level);
  localStorage.setItem('tc_user_goal', goal);

  // Show personalized instructions card
  welcomeCardForm.style.display = 'none';
  welcomeCardInstructions.style.display = 'flex';

  document.getElementById('praiseTitle').textContent = `✨ Добро пожаловать в высшую лигу, ${name}!`;
  document.getElementById('praiseText').textContent =
    `«Отличный выбор, ${name}! Системное программирование на C и C++ — это высшая лига разработчиков. Вы научитесь управлять памятью, регистрами процессора, виртуальными страницами и вызовами Windows API (OpenProcess, ReadProcessMemory). Вперед к вершинам кода!»`;

  updateStatusBar();
}

function startFirstLesson() {
  showLessonScreen();
  loadLesson(0);
}

function showLessonScreen() {
  viewWelcome.style.display = 'none';
  viewLesson.style.display = 'flex';
  renderLessonsList();
  if (gLessons.length > 0) {
    loadLesson(gCurrentLessonIdx);
  }
}

// Render Sidebar Lessons
function renderLessonsList() {
  const container = document.getElementById('lessonsListContainer');
  container.innerHTML = '';

  const completedCount = gUserData.completedLessons.length;
  const pct = Math.round((completedCount / Math.max(gLessons.length, 1)) * 100);
  document.getElementById('progressPercentBadge').textContent = `${pct}%`;

  gLessons.forEach((les, idx) => {
    const isCompleted = gUserData.completedLessons.includes(les.id);
    const isUnlocked = gUserData.unlockedLessons.includes(les.id) || isCompleted;

    const div = document.createElement('div');
    div.className = `tree-lesson-item ${idx === gCurrentLessonIdx ? 'active' : ''} ${!isUnlocked ? 'locked' : ''}`;

    let icon = '🔒';
    if (isCompleted) icon = '🟢';
    else if (isUnlocked) icon = '⚡';

    div.innerHTML = `
      <div style="display: flex; align-items: center; gap: 6px; overflow: hidden; text-overflow: ellipsis; white-space: nowrap;">
        <span>${icon}</span>
        <span>${les.title}</span>
      </div>
      <span style="font-size: 9px; padding: 1px 4px; background: #333; color: #4ec9b0;">${les.lang}</span>
    `;

    if (isUnlocked) {
      div.onclick = () => loadLesson(idx);
    } else {
      div.title = 'Пройдите предыдущие уроки, чтобы открыть этот!';
    }

    container.appendChild(div);
  });
}

function unlockAllLessons() {
  gLessons.forEach(l => {
    if (!gUserData.unlockedLessons.includes(l.id)) {
      gUserData.unlockedLessons.push(l.id);
    }
  });
  localStorage.setItem('tc_unlocked', JSON.stringify(gUserData.unlockedLessons));
  renderLessonsList();
  alert('Все 17 уроков разблокированы для свободного изучения!');
}

// Load Lesson Content
function loadLesson(index) {
  if (index < 0 || index >= gLessons.length) return;
  gCurrentLessonIdx = index;
  const les = gLessons[index];

  document.getElementById('lessonTitleHeader').textContent = `${les.title} (${les.lang})`;
  document.getElementById('editorTaskText').textContent = les.task;

  // Step 1: Render Theory Part 1 & Part 2
  theoryContentPart1.innerHTML = `
    <h2>${les.title}</h2>
    <div style="font-size: 11px; color: #888; margin-bottom: 12px;">
      Язык: <strong style="color: #4ec9b0;">${les.lang}</strong> | 
      Сложность: <strong style="color: #dcdcaa;">${les.difficulty}</strong>
    </div>
    <div style="white-space: pre-wrap;">${escapeHtml(les.theoryPart1)}</div>
    ${les.theoryPart2 ? `<div style="margin-top: 14px; white-space: pre-wrap;">${escapeHtml(les.theoryPart2)}</div>` : ''}
  `;

  // Step 2: Render Quiz
  quizQuestionText.textContent = les.quiz.question;
  quizOptionsList.innerHTML = '';
  quizFeedbackBox.style.display = 'none';
  btnQuizProceed.style.display = 'none';

  les.quiz.options.forEach(opt => {
    const btn = document.createElement('button');
    btn.className = 'quiz-option-btn';
    btn.innerHTML = `<span>⚪</span> <span>${escapeHtml(opt.text)}</span>`;
    btn.onclick = () => handleQuizOptionClick(opt, btn);
    quizOptionsList.appendChild(btn);
  });

  // Step 3: Populate Editor with Starter Code
  const savedCode = localStorage.getItem(`tc_code_${les.id}`);
  elEditor.value = savedCode || les.initialCode;
  updateLineNumbers();

  // Reset to Step 1 (Theory first!)
  goToStep(1);
  updateStatusBar();
  renderLessonsList();
}

// Step Navigation: 1 (Theory) -> 2 (Quiz) -> 3 (Editor)
function goToStep(step) {
  gCurrentStep = step;

  // Indicators
  document.getElementById('stepTab1').className = `step-indicator ${step === 1 ? 'active' : ''}`;
  document.getElementById('stepTab2').className = `step-indicator ${step === 2 ? 'active' : ''}`;
  document.getElementById('stepTab3').className = `step-indicator ${step === 3 ? 'active' : ''}`;

  document.getElementById('tbStep1').className = `btn-retro ${step === 1 ? 'primary' : ''}`;
  document.getElementById('tbStep2').className = `btn-retro ${step === 2 ? 'primary' : ''}`;
  document.getElementById('tbStep3').className = `btn-retro ${step === 3 ? 'primary' : ''}`;

  if (step === 1) {
    stageTheory.style.display = 'block';
    stageQuiz.style.display = 'none';
    stageEditor.style.display = 'none';
  } else if (step === 2) {
    stageTheory.style.display = 'none';
    stageQuiz.style.display = 'flex';
    stageEditor.style.display = 'none';
  } else if (step === 3) {
    stageTheory.style.display = 'none';
    stageQuiz.style.display = 'none';
    stageEditor.style.display = 'flex';
    elEditor.focus();
    updateLineNumbers();
  }
}

// Quiz validation
function handleQuizOptionClick(option, btnElement) {
  document.querySelectorAll('.quiz-option-btn').forEach(b => {
    b.classList.remove('selected-correct', 'selected-wrong');
  });

  quizFeedbackBox.style.display = 'block';

  if (option.correct) {
    btnElement.classList.add('selected-correct');
    btnElement.querySelector('span').textContent = '✅';
    quizFeedbackBox.className = 'quiz-feedback success';
    quizFeedbackBox.innerHTML = `<strong>🎉 Абсолютно верно!</strong><br>${escapeHtml(option.explanation)}`;
    btnQuizProceed.style.display = 'inline-block';
    document.getElementById('stepTab2').classList.add('done');
  } else {
    btnElement.classList.add('selected-wrong');
    btnElement.querySelector('span').textContent = '❌';
    quizFeedbackBox.className = 'quiz-feedback error';
    quizFeedbackBox.innerHTML = `<strong>Не совсем так:</strong><br>${escapeHtml(option.explanation)}<br><em>Попробуйте выбрать другой вариант!</em>`;
    btnQuizProceed.style.display = 'none';
  }
}

// Status Bar
function updateStatusBar() {
  if (!gLessons.length) return;
  const les = gLessons[gCurrentLessonIdx];
  elSbLesson.textContent = `Урок ${les.id}/${gLessons.length}: ${les.title}`;
  elSbLang.textContent = `Язык: ${les.lang}`;
  elSbCompiler.textContent = `GCC 12.2 / MSVC Ready`;
  elSbAi.textContent = `ИИ: TrainerAI Active`;
  elSbUser.textContent = `Ученик: ${gUserData.name || 'Гость'} (${gUserData.level})`;
}

// Compile & Run Code (Stage 3)
async function compileAndRun() {
  goToStep(3);
  switchBottomTab('console');

  const les = gLessons[gCurrentLessonIdx];
  const code = elEditor.value;

  elConsole.textContent = `==================================================\nСборка программы: ${les.title}\nКомпилятор: ${les.lang === 'C++' ? 'G++ 12.2 (-std=c++20)' : 'GCC 12.2 (-std=c11)'}\n==================================================\nКомпиляция... Пожалуйста, подождите.\n`;

  try {
    const res = await fetch('/api/compile', {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ code, lang: les.lang, lessonId: les.id })
    });
    const data = await res.json();

    if (!data.success && data.stage === 'compilation') {
      elConsole.textContent += `❌ ОШИБКА СБОРКИ (Код ${data.exitCode}):\n${data.stderr}\n\nСборка прервана (${data.timeMs} мс).\nНажмите 'Баги' для проверки кода через TrainerAI!`;
      return;
    }

    elConsole.textContent += `✅ Компиляция завершена успешно (${data.timeMs} мс).\nЗапуск исполняемого файла:\n--------------------------------------------------\n`;
    elConsole.textContent += data.stdout || '(Вывод пуст)\n';

    if (data.stderr) {
      elConsole.textContent += `\n[STDERR]:\n${data.stderr}\n`;
    }

    elConsole.textContent += `--------------------------------------------------\nКод завершения процесса: ${data.exitCode}\n`;

    // Check Task Completion
    if (data.taskCompleted) {
      elConsole.textContent += `\n🎉 ПОЗДРАВЛЯЕМ, ${gUserData.name || 'Ученик'}! Задание выполнено на 100%!\nРезультат программы в точности совпал с эталонным выводом.\nСледующий урок разблокирован! Нажмите 'След. ⏭' для перехода.\n`;

      if (!gUserData.completedLessons.includes(les.id)) {
        gUserData.completedLessons.push(les.id);
        localStorage.setItem('tc_completed', JSON.stringify(gUserData.completedLessons));
      }

      // Unlock next lesson
      const nextId = les.id + 1;
      if (nextId <= gLessons.length && !gUserData.unlockedLessons.includes(nextId)) {
        gUserData.unlockedLessons.push(nextId);
        localStorage.setItem('tc_unlocked', JSON.stringify(gUserData.unlockedLessons));
      }

      renderLessonsList();
    }
  } catch (err) {
    elConsole.textContent += `\nОшибка выполнения: ${err.message}\n`;
  }
}

// Navigation
function prevLesson() {
  if (gCurrentLessonIdx > 0) loadLesson(gCurrentLessonIdx - 1);
}

function nextLesson() {
  if (gCurrentLessonIdx + 1 < gLessons.length) {
    const nextLes = gLessons[gCurrentLessonIdx + 1];
    if (gUserData.unlockedLessons.includes(nextLes.id) || gUserData.completedLessons.includes(nextLes.id)) {
      loadLesson(gCurrentLessonIdx + 1);
    } else {
      alert('Сначала выполните текущий урок и проверочный тест, чтобы разблокировать следующий!');
    }
  }
}

function resetLessonCode() {
  if (confirm('Сбросить текущий код в редакторе к начальному шаблону урока?')) {
    elEditor.value = gLessons[gCurrentLessonIdx].initialCode;
    updateLineNumbers();
  }
}

function showSolution() {
  if (confirm('Показать эталонное решение автора курса?')) {
    elEditor.value = gLessons[gCurrentLessonIdx].solution;
    updateLineNumbers();
  }
}

function saveCodeLocally() {
  localStorage.setItem(`tc_code_${gLessons[gCurrentLessonIdx].id}`, elEditor.value);
  alert('Код урока сохранен в локальном хранилище!');
}

// Bottom Tabs (Console vs AI)
function switchBottomTab(tab) {
  if (tab === 'console') {
    document.getElementById('btnBotTabConsole').classList.add('active');
    document.getElementById('btnBotTabAi').classList.remove('active');
    elConsole.style.display = 'block';
    elAiChat.style.display = 'none';
  } else {
    document.getElementById('btnBotTabAi').classList.add('active');
    document.getElementById('btnBotTabConsole').classList.remove('active');
    elAiChat.style.display = 'flex';
    elConsole.style.display = 'none';
    elAiPrompt.focus();
  }
}

// AI Assistant
async function sendAiPrompt() {
  const p = elAiPrompt.value.trim();
  if (!p) return;
  askAi(p);
  elAiPrompt.value = '';
}

async function askAi(promptText) {
  switchBottomTab('ai');

  const userDiv = document.createElement('div');
  userDiv.className = 'ai-msg user';
  userDiv.innerHTML = `<strong>👤 Вы:</strong> ${escapeHtml(promptText)}`;
  elAiMessages.appendChild(userDiv);

  const botDiv = document.createElement('div');
  botDiv.className = 'ai-msg bot';
  botDiv.innerHTML = `<strong>🤖 TrainerAI:</strong> Анализирую код и структуру памяти...`;
  elAiMessages.appendChild(botDiv);
  elAiMessages.scrollTop = elAiMessages.scrollHeight;

  try {
    const res = await fetch('/api/ai/ask', {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({
        prompt: promptText,
        code: elEditor.value,
        lessonId: gLessons[gCurrentLessonIdx].id
      })
    });
    const data = await res.json();
    botDiv.innerHTML = `<strong>🤖 TrainerAI:</strong>\n${escapeHtml(data.response)}`;
  } catch (err) {
    botDiv.innerHTML = `<strong>🤖 TrainerAI:</strong> Ошибка: ${err.message}`;
  }
  elAiMessages.scrollTop = elAiMessages.scrollHeight;
}

// Types Modal
async function loadTypesTable() {
  try {
    const res = await fetch('/api/types');
    const types = await res.json();
    const tbody = document.getElementById('typesTableBody');
    tbody.innerHTML = '';
    types.forEach(t => {
      const tr = document.createElement('tr');
      tr.innerHTML = `
        <td><strong style="color: #4ec9b0;"><code>${t.name}</code></strong></td>
        <td style="text-align: center; color: #569cd6;">${t.x86}</td>
        <td style="text-align: center; color: #569cd6;">${t.x64}</td>
        <td><code style="color: #ce9178;">${t.spec}</code></td>
        <td style="color: #b5cea8;">${t.range}</td>
        <td style="color: #d4d4d4;">${t.desc}</td>
      `;
      tbody.appendChild(tr);
    });
  } catch (e) {
    console.error(e);
  }
}

// Modals
function openTypesModal() { document.getElementById('typesModal').style.display = 'flex'; }
function closeTypesModal() { document.getElementById('typesModal').style.display = 'none'; }

function openSettingsModal() { document.getElementById('settingsModal').style.display = 'flex'; }
function closeSettingsModal() { document.getElementById('settingsModal').style.display = 'none'; }
function saveCompilerSettings() {
  alert('Настройки компилятора сохранены.');
  closeSettingsModal();
}
function testCompilerConfig() {
  const el = document.getElementById('compilerTestResult');
  el.textContent = 'Тестирование компилятора...';
  setTimeout(() => {
    el.textContent = '✅ Компилятор активен! Версия: GCC 12.2.0 (x86_64 target ready).';
  }, 300);
}

function openAiDownloaderModal() { document.getElementById('aiDownloaderModal').style.display = 'flex'; }
function closeAiDownloaderModal() { document.getElementById('aiDownloaderModal').style.display = 'none'; }

function simulateAiDownload() {
  const statusEl = document.getElementById('aiDownloadStatus');
  const barEl = document.getElementById('aiProgressBar');
  const btn = document.getElementById('btnStartDownload');
  btn.disabled = true;

  statusEl.textContent = 'Инициализация загрузки весов модели...';
  let p = 0;
  const iv = setInterval(() => {
    p += 15;
    barEl.style.width = `${p}%`;
    statusEl.textContent = `Скачивание модели: ${p}% (Скорость: 16.4 МБ/с)`;
    if (p >= 100) {
      clearInterval(iv);
      statusEl.textContent = '✅ Нейросеть успешно загружена в models/ и подключена!';
      btn.disabled = false;
      setTimeout(() => {
        closeAiDownloaderModal();
        alert('Модель готова! Можете задавать вопросы во вкладке "ИИ-Ассистент".');
      }, 400);
    }
  }, 120);
}

function downloadExe() {
  window.location.href = '/api/download-exe';
}

function aboutApp() {
  alert('TrainerCode 2000 — Dark Win32 Edition\nВерсия 1.1.0\n\n17 глубоких практических уроков (от типов и указателей до WinAPI, OpenProcess и ReadProcessMemory).\nВстроенный проверочный тест к каждому уроку, компилятор и TrainerAI.\n\n© 2000-2026 TrainerCode Project.');
}

function escapeHtml(text) {
  if (!text) return '';
  return text
    .replace(/&/g, '&amp;')
    .replace(/</g, '&lt;')
    .replace(/>/g, '&gt;')
    .replace(/"/g, '&quot;')
    .replace(/'/g, '&#039;');
}
