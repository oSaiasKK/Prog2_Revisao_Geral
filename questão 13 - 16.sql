-- Atividade por: Isaias Ramos Batista

-- Questão 13

CREATE TABLE autores (
    id_autor INT AUTO_INCREMENT PRIMARY KEY,
    nome VARCHAR(100) NOT NULL,
    nacionalidade VARCHAR(50)
);

CREATE TABLE livros (
    id_livro INT AUTO_INCREMENT PRIMARY KEY,
    titulo VARCHAR(150) NOT NULL,
    isbn VARCHAR(20) UNIQUE NOT NULL,
    ano_publicacao INT,
    quantidade_disponivel INT DEFAULT 1,
    id_autor INT NOT NULL,
    CONSTRAINT fk_livros_autores FOREIGN KEY (id_autor) 
        REFERENCES autores(id_autor) 
        ON DELETE RESTRICT 
        ON UPDATE CASCADE
);

CREATE TABLE usuarios (
    id_usuario INT AUTO_INCREMENT PRIMARY KEY,
    nome VARCHAR(100) NOT NULL,
    email VARCHAR(100) UNIQUE NOT NULL,
    telefone VARCHAR(20),
    data_cadastro DATE DEFAULT (CURRENT_DATE)
);

CREATE TABLE emprestimos (
    id_emprestimo INT AUTO_INCREMENT PRIMARY KEY,
    id_livro INT NOT NULL,
    id_usuario INT NOT NULL,
    data_emprestimo DATE NOT NULL,
    data_devolucao_prevista DATE NOT NULL,
    data_devolucao_real DATE,
    CONSTRAINT fk_emprestimos_livros FOREIGN KEY (id_livro) 
        REFERENCES livros(id_livro) 
        ON DELETE RESTRICT 
        ON UPDATE CASCADE,
    CONSTRAINT fk_emprestimos_usuarios FOREIGN KEY (id_usuario) 
        REFERENCES usuarios(id_usuario) 
        ON DELETE RESTRICT 
        ON UPDATE CASCADE
);

INSERT INTO autores (nome, nacionalidade) VALUES
('Machado de Assis', 'Brasileira'),
('George Orwell', 'Britânica'),
('Clarice Lispector', 'Brasileira'),
('J.R.R. Tolkien', 'Britânica');

INSERT INTO livros (titulo, isbn, ano_publicacao, quantidade_disponivel, id_autor) VALUES
('Dom Casmurro', '9788535902778', 1899, 3, 1),
('Memórias Póstumas de Brás Cubas', '9788535910667', 1881, 0, 1),
('1984', '9788535914849', 1949, 5, 2),
('A Hora da Estrela', '9788535910124', 1977, 2, 3),
('O Senhor dos Anéis: A Sociedade do Anel', '9788535902006', 1954, 0, 4);

INSERT INTO usuarios (nome, email, telefone) VALUES
('Ana Silva', 'ana.silva@email.com', '(11) 98765-4321'),
('Carlos Eduardo', 'carlos.eduardo@email.com', '(21) 97654-3210'),
('Mariana Costa', 'mariana.costa@email.com', '(31) 96543-2109');

INSERT INTO emprestimos (id_livro, id_usuario, data_emprestimo, data_devolucao_prevista, data_devolucao_real) VALUES
(2, 1, '2026-10-01', '2026-10-15', NULL),
(5, 2, '2026-10-05', '2026-10-19', NULL),
(1, 3, '2026-09-15', '2026-09-29', '2026-09-28');

-- Questão 14

-- 1. Listar todos os livros
SELECT * FROM livros;

-- 2. Mostrar somente título e autor
SELECT 
    l.titulo, 
    a.nome AS autor
FROM livros l
JOIN autores a ON l.id_autor = a.id_autor;

-- 3. Buscar livros de determinado autor (Ex: Machado de Assis)
SELECT 
    l.titulo, 
    l.isbn, 
    l.ano_publicacao
FROM livros l
JOIN autores a ON l.id_autor = a.id_autor
WHERE a.nome = 'Machado de Assis';

-- 4. Mostrar os livros ordenados alfabeticamente
SELECT 
    l.titulo, 
    a.nome AS autor, 
    l.ano_publicacao
FROM livros l
JOIN autores a ON l.id_autor = a.id_autor
ORDER BY l.titulo ASC;

-- 5. Mostrar apenas livros disponíveis
SELECT 
    l.titulo, 
    a.nome AS autor, 
    l.quantidade_disponivel
FROM livros l
JOIN autores a ON l.id_autor = a.id_autor
WHERE l.quantidade_disponivel > 0;

-- Questão 15

-- A regra de integridade referencial com "ON DELETE RESTRICT" bloqueia a exclusão de registros em tabelas pai (como "livros" ou "usuarios") 
-- se existirem vínculos na tabela filho ("emprestimos"), evitando dados "órfãos". Para resolver esse bloqueio, pode-se excluir manualmente 
-- os registros associados primeiro, configurar a chave estrangeira com "ON DELETE CASCADE" para deleção automática, ou aplicar a exclusão lógica
-- (`UPDATE ativo = FALSE`), que preserva o histórico do sistema.

-- Alterar o nome de um usuário
UPDATE usuarios 
SET nome = 'Ana Silva Sauauro' 
WHERE id_usuario = 1;

-- Alterar a disponibilidade de um livro (aumentar/diminuir estoque)
UPDATE livros 
SET quantidade_disponivel = 4 
WHERE id_livro = 1;

-- Atualizar a data de devolução real de um empréstimo (registrar devolução)
UPDATE emprestimos 
SET data_devolucao_real = '2026-10-09' 
WHERE id_emprestimo = 1;

-- Excluir um usuário
DELETE FROM emprestimos 
WHERE id_usuario = 3;

DELETE FROM usuarios 
WHERE id_usuario = 3;


-- Excluir um livro
DELETE FROM emprestimos 
WHERE id_livro = 5;

DELETE FROM livros 
WHERE id_livro = 5;

-- Questão 16

-- 1. Nome do usuário e título do livro emprestado
SELECT 
    u.nome AS usuario, 
    l.titulo AS livro
FROM emprestimos e
INNER JOIN usuarios u ON e.id_usuario = u.id_usuario
INNER JOIN livros l ON e.id_livro = l.id_livro;


-- 2. Todos os empréstimos realizados
SELECT 
    e.id_emprestimo,
    u.nome AS usuario,
    l.titulo AS livro,
    e.data_emprestimo,
    e.data_devolucao_prevista,
    e.data_devolucao_real
FROM emprestimos e
INNER JOIN usuarios u ON e.id_usuario = u.id_usuario
INNER JOIN livros l ON e.id_livro = l.id_livro;


-- 3. Empréstimos ainda não devolvidos
SELECT 
    e.id_emprestimo,
    u.nome AS usuario,
    l.titulo AS livro,
    e.data_emprestimo,
    e.data_devolucao_prevista
FROM emprestimos e
INNER JOIN usuarios u ON e.id_usuario = u.id_usuario
INNER JOIN livros l ON e.id_livro = l.id_livro
WHERE e.data_devolucao_real IS NULL;


-- 4. Quantidade de empréstimos realizada por usuário
SELECT 
    u.nome AS usuario,
    COUNT(e.id_emprestimo) AS total_emprestimos
FROM usuarios u
LEFT JOIN emprestimos e ON u.id_usuario = e.id_usuario
GROUP BY u.id_usuario, u.nome;


-- 5. Livros que nunca foram emprestados
SELECT 
    l.id_livro,
    l.titulo,
    a.nome AS autor
FROM livros l
LEFT JOIN emprestimos e ON l.id_livro = e.id_livro
LEFT JOIN autores a ON l.id_autor = a.id_autor
WHERE e.id_emprestimo IS NULL;