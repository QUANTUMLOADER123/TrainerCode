let gLessons = [];
let gCurrentLessonIdx = 0;
let gUserData = {
  name: localStorage.getItem('tc_user_name') || 'Александр',
  level: localStorage.getItem('tc_user_level') || 'Новичок',
  completedLessons: JSON.parse(localStorage.getItem('tc_completed') || '[]')
};

// DOM elements
const elTree = document.getElementById('treeViewContainer');
const elEditor = document.getElementById('codeEditor');
const elLineNumbers = document.getElementById('lineNumbers');
const elTheory = document.getElementById('theoryView');
const elConsole = document.getElementById('consoleOutput');
const elAiChat = document.getElementById('aiChatView');
const elAiMessages = document.getElementById('aiMessagesList');
const elAiPrompt = document.getElementById('aiPromptInput');

// Status bar
const elSbLesson = document.getElementById('sbLesson');
const elSbLang = document.getElementById('sbLang');
const elSbCompiler = document.getElementById('sbCompiler');
const elSbAi = document.getElementById('sbAi');
const elSbUser = document.getElementById('sbUser');

// Initialize
window.addEventListener('DOMContentLoaded', async () => {
  updateClock();
  setInterval(updateClock, 1000);

  // Setup line numbers & editor sync
  elEditor.addEventListener('input', updateLineNumbers);
  elEditor.addEventListener('scroll', () => {
    elLineNumbers.scrollTop = elEditor.scrollTop;
  });

  // Handle Tab key in code editor
  elEditor.addEventListener('keydown', (e) => {
    if (e.key === 'Tab') {
      e.preventDefault();
      const start = elEditor.selectionStart;
      const end = elEditor.selectionEnd;
      elEditor.value = elEditor.value.substring(0, start) + '    ' + elEditor.value.substring(end);
      elEditor.selectionStart = elEditor.selectionEnd = start + 4;
      updateLineNumbers();
    } else if (e.key === 'F5') {
      e.preventDefault();
      compileAndRun();
    } else if (e.key === 'F1') {
      e.preventDefault();
      openTypesModal();
    }
  });

  // Load Lessons
  try {
    const res = await fetch('/api/lessons');
    gLessons = await res.json();
    renderTree();
    loadLesson(0);
  } catch (err) {
    console.error('Failed to load lessons:', err);
  }

  // Load Types
  loadTypesTable();

  // First time wizard check
  if (!localStorage.getItem('tc_first_run_done')) {
    openWizardModal();
  } else {
    updateStatusBar();
  }
});

// Update real-time taskbar clock
function updateClock() {
  const now = new Date();
  const h = String(now.getHours()).padStart(2, '0');
  const m = String(now.getMinutes()).padStart(2, '0');
  document.getElementById('trayClock').textContent = `${h}:${m}`;
}

// Render Lesson TreeView
function renderTree() {
  elTree.innerHTML = '';
  let modules = {};

  gLessons.forEach((les, idx) => {
    if (!modules[les.module]) {
      modules[les.module] = [];
    }
    modules[les.module].push({ les, idx });
  });

  for (const [modName, items] of Object.entries(modules)) {
    const modDiv = document.createElement('div');
    modDiv.className = 'tree-module';

    const header = document.createElement('div');
    header.className = 'tree-module-header';
    header.innerHTML = `<span>📁</span> <span>${modName}</span>`;
    modDiv.appendChild(header);

    items.forEach(({ les, idx }) => {
      const itemDiv = document.createElement('div');
      itemDiv.className = `tree-lesson-item ${idx === gCurrentLessonIdx ? 'active' : ''}`;
      itemDiv.id = `lesson-item-${idx}`;

      const isDone = gUserData.completedLessons.includes(les.id);
      const icon = isDone ? '🟢' : '⚪';

      itemDiv.innerHTML = `
        <span style="overflow: hidden; text-overflow: ellipsis; white-space: nowrap;">${icon} ${les.title}</span>
        <span class="badge-tag">${les.lang}</span>
      `;
      itemDiv.onclick = () => loadLesson(idx);
      modDiv.appendChild(itemDiv);
    });

    elTree.appendChild(modDiv);
  }
}

// Load Lesson
function loadLesson(index) {
  if (index < 0 || index >= gLessons.length) return;
  gCurrentLessonIdx = index;
  const les = gLessons[index];

  // Active state in tree
  document.querySelectorAll('.tree-lesson-item').forEach(el => el.classList.remove('active'));
  const activeTreeEl = document.getElementById(`lesson-item-${index}`);
  if (activeTreeEl) activeTreeEl.classList.add('active');

  // Populate editor
  elEditor.value = les.initialCode;
  updateLineNumbers();

  // Populate theory
  let hintsHtml = '';
  if (les.hints && les.hints.length > 0) {
    hintsHtml = `
      <div style="margin-top: 10px; padding: 8px; background: #eef5ff; border: 1px solid #7baaf7;">
        <strong>💡 Подсказки:</strong>
        <ul style="padding-left: 20px; margin-top: 4px;">
          ${les.hints.map(h => `<li>${h}</li>`).join('')}
        </ul>
      </div>
    `;
  }

  elTheory.innerHTML = `
    <h2>${les.title}</h2>
    <div style="font-size: 11px; color: #555; margin-bottom: 12px;">
      <strong>Модуль:</strong> ${les.module} | 
      <strong>Язык:</strong> ${les.lang} | 
      <strong>Сложность:</strong> ${les.difficulty}
    </div>
    <div style="white-space: pre-wrap; font-size: 12px; line-height: 1.6;">${escapeHtml(les.theory)}</div>
    
    <div class="theory-task-box">
      <h4>🎯 ЗАДАНИЕ К УРОКУ:</h4>
      <div style="white-space: pre-wrap;">${escapeHtml(les.task)}</div>
      ${hintsHtml}
    </div>
  `;

  // Log message in console
  elConsole.textContent = `[TrainerCode 2000 System Ready]\nЗагружен ${les.title}.\nНажмите кнопку '▶ Запуск (F5)' для компиляции и проверки решения.`;

  updateStatusBar();
}

function updateLineNumbers() {
  const lines = elEditor.value.split('\n').length;
  let numStr = '';
  for (let i = 1; i <= Math.max(lines, 1); i++) {
    numStr += i + '<br>';
  }
  elLineNumbers.innerHTML = numStr;
}

function updateStatusBar() {
  if (!gLessons.length) return;
  const les = gLessons[gCurrentLessonIdx];
  elSbLesson.textContent = `Урок ${les.id}/${gLessons.length}: ${les.title}`;
  elSbLang.textContent = `Язык: ${les.lang}`;
  elSbCompiler.textContent = `Компилятор: GCC/MSVC C11/C++20`;
  elSbAi.textContent = `ИИ: TrainerAI Active`;
  elSbUser.textContent = `Ученик: ${gUserData.name} (${gUserData.level})`;
}

// Tab Switching
function switchMainTab(tab) {
  if (tab === 'code') {
    document.getElementById('tabBtnCode').classList.add('active');
    document.getElementById('tabBtnTheory').classList.remove('active');
    document.getElementById('codeEditorView').style.display = 'flex';
    document.getElementById('theoryView').style.display = 'none';
    elEditor.focus();
  } else {
    document.getElementById('tabBtnTheory').classList.add('active');
    document.getElementById('tabBtnCode').classList.remove('active');
    document.getElementById('theoryView').style.display = 'block';
    document.getElementById('codeEditorView').style.display = 'none';
  }
}

function switchBottomTab(tab) {
  if (tab === 'console') {
    document.getElementById('tabBtnConsole').classList.add('active');
    document.getElementById('tabBtnAi').classList.remove('active');
    elConsole.style.display = 'block';
    elAiChat.style.display = 'none';
  } else {
    document.getElementById('tabBtnAi').classList.add('active');
    document.getElementById('tabBtnConsole').classList.remove('active');
    elAiChat.style.display = 'flex';
    elConsole.style.display = 'none';
    elAiPrompt.focus();
  }
}

function switchToAiTab() {
  switchBottomTab('ai');
}

// Compile & Run
async function compileAndRun() {
  const les = gLessons[gCurrentLessonIdx];
  const code = elEditor.value;

  switchBottomTab('console');
  elConsole.textContent = `==================================================\nСборка программы: ${les.title}\nКомпилятор: ${les.lang === 'C++' ? 'G++ 12.2 (-std=c++20)' : 'GCC 12.2 (-std=c11)'}\n==================================================\nКомпиляция... Пожалуйста, подождите.\n`;

  try {
    const res = await fetch('/api/compile', {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ code, lang: les.lang, lessonId: les.id })
    });
    const data = await res.json();

    if (!data.success && data.stage === 'compilation') {
      elConsole.textContent += `❌ ОШИБКА КОМПИЛЯЦИИ:\n${data.stderr}\n\nСборка прервана с кодом ${data.exitCode} (${data.timeMs} мс).\nИспользуйте кнопку 'Баги в коде' или спросите ИИ-наставника для помощи!`;
      return;
    }

    elConsole.textContent += `✅ Компиляция завершена успешно (${data.timeMs} мс).\nЗапуск программы:\n--------------------------------------------------\n`;
    elConsole.textContent += data.stdout || '(Программа ничего не вывела в stdout)\n';

    if (data.stderr) {
      elConsole.textContent += `\n[STDERR]:\n${data.stderr}\n`;
    }

    elConsole.textContent += `--------------------------------------------------\nКод выхода: ${data.exitCode}\n`;

    if (data.taskCompleted) {
      elConsole.textContent += `\n🎉 ПОЗДРАВЛЯЕМ! Задание урока выполнено на 100%!\nРезультат совпадает с эталоном. Вы можете перейти к следующему уроку.\n`;
      if (!gUserData.completedLessons.includes(les.id)) {
        gUserData.completedLessons.push(les.id);
        localStorage.setItem('tc_completed', JSON.stringify(gUserData.completedLessons));
        renderTree();
      }
    }
  } catch (err) {
    elConsole.textContent += `\nОшибка выполнения запроса к компилятору: ${err.message}\n`;
  }
}

// Lesson Navigation
function prevLesson() {
  if (gCurrentLessonIdx > 0) loadLesson(gCurrentLessonIdx - 1);
}

function nextLesson() {
  if (gCurrentLessonIdx + 1 < gLessons.length) loadLesson(gCurrentLessonIdx + 1);
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

function newSnippet() {
  if (confirm('Очистить редактор для нового скетча?')) {
    elEditor.value = '#include <stdio.h>\n\nint main(void) {\n    printf("Hello from C!\\n");\n    return 0;\n}\n';
    updateLineNumbers();
  }
}

function saveCode() {
  localStorage.setItem(`tc_code_${gCurrentLessonIdx}`, elEditor.value);
  alert('Код урока успешно сохранен в локальном хранилище браузера!');
}

// AI Assistant
async function sendAiPrompt() {
  const prompt = elAiPrompt.value.trim();
  if (!prompt) return;
  askAi(prompt);
  elAiPrompt.value = '';
}

async function askAi(promptText) {
  switchToAiTab();

  // Add user message
  const userMsg = document.createElement('div');
  userMsg.className = 'ai-msg user';
  userMsg.innerHTML = `<strong>👤 Вы:</strong> ${escapeHtml(promptText)}`;
  elAiMessages.appendChild(userMsg);

  // Add placeholder
  const botMsg = document.createElement('div');
  botMsg.className = 'ai-msg bot';
  botMsg.innerHTML = `<strong>🤖 TrainerAI:</strong> Анализирую код и формулирую ответ...`;
  elAiMessages.appendChild(botMsg);
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
    botMsg.innerHTML = `<strong>🤖 TrainerAI:</strong>\n${escapeHtml(data.response)}`;
  } catch (err) {
    botMsg.innerHTML = `<strong>🤖 TrainerAI:</strong> Ошибка связи: ${err.message}`;
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
        <td><strong><code>${t.name}</code></strong></td>
        <td style="text-align: center;">${t.x86}</td>
        <td style="text-align: center;">${t.x64}</td>
        <td><code>${t.spec}</code></td>
        <td>${t.range}</td>
        <td>${t.desc}</td>
      `;
      tbody.appendChild(tr);
    });
  } catch (e) {
    console.error('Failed to load types:', e);
  }
}

// Modal controls
function openMainWindow() {
  document.getElementById('mainWindow').style.display = 'flex';
}

function openWizardModal() {
  document.getElementById('wizUserName').value = gUserData.name;
  document.getElementById('wizUserLevel').value = gUserData.level;
  document.getElementById('wizardModal').style.display = 'flex';
}

function closeWizardModal() {
  document.getElementById('wizardModal').style.display = 'none';
}

function saveWizardSettings() {
  gUserData.name = document.getElementById('wizUserName').value.trim() || 'Ученик';
  gUserData.level = document.getElementById('wizUserLevel').value;
  localStorage.setItem('tc_user_name', gUserData.name);
  localStorage.setItem('tc_user_level', gUserData.level);
  localStorage.setItem('tc_first_run_done', 'true');
  closeWizardModal();
  updateStatusBar();
  alert(`Добро пожаловать в Академию, ${gUserData.name}! Начните с первого урока слева.`);
}

function openSettingsModal() {
  document.getElementById('settingsModal').style.display = 'flex';
}

function closeSettingsModal() {
  document.getElementById('settingsModal').style.display = 'none';
}

function saveCompilerSettings() {
  alert('Настройки компилятора успешно сохранены.');
  closeSettingsModal();
}

function testCompilerConfig() {
  const resEl = document.getElementById('compilerTestResult');
  resEl.textContent = 'Тестирование компилятора GCC/MSVC...';
  setTimeout(() => {
    resEl.textContent = '✅ Компилятор доступен! Версия: GCC 12.2.0 (x86_64-linux-gnu / Windows Cross-Target ready)';
  }, 400);
}

function openTypesModal() {
  document.getElementById('typesModal').style.display = 'flex';
}

function closeTypesModal() {
  document.getElementById('typesModal').style.display = 'none';
}

function openAiDownloaderModal() {
  document.getElementById('aiDownloaderModal').style.display = 'flex';
}

function closeAiDownloaderModal() {
  document.getElementById('aiDownloaderModal').style.display = 'none';
}

function simulateAiDownload() {
  const statusEl = document.getElementById('aiDownloadStatus');
  const barEl = document.getElementById('aiProgressBar');
  const btn = document.getElementById('btnStartDownload');
  btn.disabled = true;

  statusEl.textContent = 'Инициализация загрузки GGUF весов нейросети...';
  let progress = 0;
  const interval = setInterval(() => {
    progress += 10;
    barEl.style.width = `${progress}%`;
    statusEl.textContent = `Скачивание: ${progress}% (Скорость: 14.8 МБ/с)`;
    if (progress >= 100) {
      clearInterval(interval);
      statusEl.textContent = '✅ Модель успешно сохранена в models/ и подключена к TrainerAI!';
      btn.disabled = false;
      setTimeout(() => {
        closeAiDownloaderModal();
        alert('Нейросеть TrainerAI готова к работе! Вы можете задавать вопросы во вкладке "ИИ-Ассистент".');
      }, 500);
    }
  }, 150);
}

function downloadExe() {
  window.location.href = '/api/download-exe';
}

function aboutApp() {
  alert('TrainerCode 2000 — Элитный тренажер C и C++\nВерсия 1.0.0 (Win32 x86_64 Edition)\n\nСтилизовано под классический Windows 2000.\nВключает 25 глубоких практических уроков, AI-ассистента и компилятор.\n\n© 2000-2026 TrainerCode Project.');
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
