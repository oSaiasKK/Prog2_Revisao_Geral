const express = require('express');
const sqlite3 = require('sqlite3').verbose();
const path = require('path');
const Task = require('./Task');
const TaskQueue = require('./TaskQueue');

const app = express();
const PORT = process.env.PORT || 3000;

// Middlewares
app.use(express.json());
app.use(express.static(path.join(__dirname, 'public')));

// Inicialização do Banco de Dados SQLite
const db = new sqlite3.Database('./database.sqlite', (err) => {
    if (err) console.error('Erro ao conectar ao banco de dados:', err.message);
    else console.log('Conectado ao Banco de Dados SQLite com sucesso.');
});

// Criar Tabela de Tarefas
db.run(`
    CREATE TABLE IF NOT EXISTS tarefas (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        titulo TEXT NOT NULL,
        descricao TEXT,
        prioridade TEXT DEFAULT 'media',
        status TEXT DEFAULT 'pendente',
        criadaEm TEXT
    )
`);

// Estrutura de dados Fila em memória para processamento sequencial
const filaDeExecucao = new TaskQueue();

// --- ROTAS DA API REST (CLIENTE-SERVIDOR) ---

// 1. READ (GET) - Listar todas as tarefas
app.get('/api/tarefas', (req, res) => {
    db.all("SELECT * FROM tarefas ORDER BY id DESC", [], (err, rows) => {
        if (err) return res.status(500).json({ error: err.message });
        
        const tarefas = rows.map(r => new Task(r.id, r.titulo, r.descricao, r.prioridade, r.status, r.criadaEm).toJSON());
        res.json(tarefas);
    });
});

// 2. CREATE (POST) - Criar nova tarefa
app.post('/api/tarefas', (req, res) => {
    const { titulo, descricao, prioridade } = req.body;
    
    // Instancia classe OO para validação
    const novaTarefa = new Task(null, titulo, descricao, prioridade);
    const validacao = novaTarefa.validar();

    if (!validacao.valido) {
        return res.status(400).json({ error: validacao.erro });
    }

    const sql = `INSERT INTO tarefas (titulo, descricao, prioridade, status, criadaEm) VALUES (?, ?, ?, ?, ?)`;
    const params = [novaTarefa.titulo, novaTarefa.descricao, novaTarefa.prioridade, novaTarefa.status, novaTarefa.criadaEm];

    db.run(sql, params, function (err) {
        if (err) return res.status(500).json({ error: err.message });
        
        const tarefaCadastrada = new Task(this.lastID, novaTarefa.titulo, novaTarefa.descricao, novaTarefa.prioridade, novaTarefa.status, novaTarefa.criadaEm);
        
        // Se a tarefa estiver pendente, adiciona na Fila de Execução (ED)
        filaDeExecucao.enqueue(tarefaCadastrada.toJSON());

        res.status(201).json(tarefaCadastrada.toJSON());
    });
});

// 3. UPDATE (PUT) - Atualizar uma tarefa
app.put('/api/tarefas/:id', (req, res) => {
    const { id } = req.params;
    const { titulo, descricao, prioridade, status } = req.body;

    const sql = `UPDATE tarefas SET titulo = ?, descricao = ?, prioridade = ?, status = ? WHERE id = ?`;
    
    db.run(sql, [titulo, descricao, prioridade, status, id], function (err) {
        if (err) return res.status(500).json({ error: err.message });
        if (this.changes === 0) return res.status(404).json({ error: 'Tarefa não encontrada.' });
        
        res.json({ message: 'Tarefa atualizada com sucesso!', id });
    });
});

// 4. DELETE (DELETE) - Excluir uma tarefa
app.delete('/api/tarefas/:id', (req, res) => {
    const { id } = req.params;
    
    db.run(`DELETE FROM tarefas WHERE id = ?`, [id], function (err) {
        if (err) return res.status(500).json({ error: err.message });
        if (this.changes === 0) return res.status(404).json({ error: 'Tarefa não encontrada.' });
        
        res.json({ message: 'Tarefa excluída com sucesso!' });
    });
});

// 5. PROCESSAR FILA DE TAREFAS (Uso da Estrutura de Dados FIFO)
app.post('/api/tarefas/processar-fila', (req, res) => {
    db.all("SELECT * FROM tarefas WHERE status = 'pendente' ORDER BY id ASC", [], (err, rows) => {
        if (err) return res.status(500).json({ error: err.message });
        if (rows.length === 0) return res.status(400).json({ message: 'Nenhuma tarefa pendente na fila.' });

        const proximaTarefa = rows[0]; // Primeiro a entrar (FIFO)
        
        db.run("UPDATE tarefas SET status = 'concluida' WHERE id = ?", [proximaTarefa.id], function (err) {
            if (err) return res.status(500).json({ error: err.message });
            res.json({ message: `Tarefa "${proximaTarefa.titulo}" processada e concluída da fila!`, tarefa: proximaTarefa });
        });
    });
});

// Iniciar Servidor
app.listen(PORT, () => {
    console.log(`Servidor rodando em http://localhost:${PORT}`);
});
