const API_URL = '/api/tarefas';

document.addEventListener('DOMContentLoaded', () => {
    loadTasks();

    const form = document.getElementById('task-form');
    const btnCancel = document.getElementById('btn-cancel');
    const btnProcessQueue = document.getElementById('btn-process-queue');

    form.addEventListener('submit', handleFormSubmit);
    btnCancel.addEventListener('click', resetForm);
    btnProcessQueue.addEventListener('click', processQueue);
});

// GET: Buscar e listar tarefas
async function loadTasks() {
    try {
        const response = await fetch(API_URL);
        const tasks = await response.json();
        renderTable(tasks);
    } catch (error) {
        console.error('Erro ao carregar tarefas:', error);
    }
}

// Renderizar Tabela no DOM
function renderTable(tasks) {
    const tbody = document.getElementById('task-tbody');
    tbody.innerHTML = '';

    if (tasks.length === 0) {
        tbody.innerHTML = '<tr><td colspan="6" style="text-align:center;">Nenhuma tarefa cadastrada.</td></tr>';
        return;
    }

    tasks.forEach(task => {
        const tr = document.createElement('tr');
        tr.innerHTML = `
            <td>${task.id}</td>
            <td><strong>${escapeHtml(task.titulo)}</strong></td>
            <td>${escapeHtml(task.descricao || '-')}</td>
            <td><span class="badge badge-${task.prioridade}">${task.prioridade}</span></td>
            <td><span class="status-${task.status}">${task.status}</span></td>
            <td>
                <button class="btn btn-edit" onclick="prepareEdit(${task.id}, '${escapeHtml(task.titulo)}', '${escapeHtml(task.descricao || '')}', '${task.prioridade}', '${task.status}')">Editar</button>
                <button class="btn btn-delete" onclick="deleteTask(${task.id})">Excluir</button>
            </td>
        `;
        tbody.appendChild(tr);
    });
}

// POST e PUT: Criar ou Atualizar Tarefa
async function handleFormSubmit(e) {
    e.preventDefault();

    const id = document.getElementById('task-id').value;
    const titulo = document.getElementById('titulo').value;
    const descricao = document.getElementById('descricao').value;
    const prioridade = document.getElementById('prioridade').value;

    const taskData = { titulo, descricao, prioridade, status: 'pendente' };

    try {
        let response;
        if (id) {
            // PUT: Alteração
            response = await fetch(`${API_URL}/${id}`, {
                method: 'PUT',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify(taskData)
            });
        } else {
            // POST: Inclusão
            response = await fetch(API_URL, {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify(taskData)
            });
        }

        if (response.ok) {
            resetForm();
            loadTasks();
        } else {
            const err = await response.json();
            alert(`Erro: ${err.error}`);
        }
    } catch (error) {
        console.error('Erro na requisição:', error);
    }
}

// DELETE: Excluir Tarefa
async function deleteTask(id) {
    if (!confirm('Tem certeza que deseja excluir esta tarefa?')) return;

    try {
        const response = await fetch(`${API_URL}/${id}`, { method: 'DELETE' });
        if (response.ok) {
            loadTasks();
        } else {
            alert('Erro ao excluir tarefa.');
        }
    } catch (error) {
        console.error('Erro ao excluir:', error);
    }
}

// Preparar Formulário para Edição
function prepareEdit(id, titulo, descricao, prioridade, status) {
    document.getElementById('task-id').value = id;
    document.getElementById('titulo').value = titulo;
    document.getElementById('descricao').value = descricao;
    document.getElementById('prioridade').value = prioridade;
    document.getElementById('form-title').innerText = 'Editar Tarefa #' + id;
    document.getElementById('btn-cancel').style.display = 'inline-block';
}

function resetForm() {
    document.getElementById('task-id').value = '';
    document.getElementById('task-form').reset();
    document.getElementById('form-title').innerText = 'Nova Tarefa';
    document.getElementById('btn-cancel').style.display = 'none';
}

// Processar Fila (FIFO)
async function processQueue() {
    try {
        const response = await fetch(`${API_URL}/processar-fila`, { method: 'POST' });
        const res = await response.json();
        alert(res.message);
        loadTasks();
    } catch (error) {
        console.error('Erro ao processar fila:', error);
    }
}

function escapeHtml(text) {
    return text.replace(/'/g, "\'").replace(/"/g, "&quot;");
}
