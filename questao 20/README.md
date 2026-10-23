# Sistema Web Cliente-Servidor: Gerenciador de Tarefas (Task Manager)

Este projeto foi desenvolvido como trabalho final da disciplina de Desenvolvimento Web / Programação. Consiste em uma aplicação web full-stack completa utilizando a arquitetura Cliente-Servidor, com banco de dados SQLite, Orientação a Objetos, Estruturas de Dados e suporte a operações CRUD via API REST.

---

## 📋 Sumário
1. [Tema Escolhido](#tema-escolhido)
2. [Estrutura do Projeto](#estrutura-do-projeto)
3. [Como Executar o Projeto](#como-executar-o-projeto)
4. [Arquitetura Cliente-Servidor](#arquitetura-cliente-servidor)
5. [Rotas e Endpoints (API REST)](#rotas-e-endpoints-api-rest)
6. [Demonstração do CRUD](#demonstração-do-crud)
7. [Orientação a Objetos (Classe Task)](#orientação-a-objetos-classe-task)
8. [Estrutura de Dados (Fila/Queue)](#estrutura-de-dados-filaqueue)
9. [Respostas para Revisão Conceitual](#respostas-para-revisão-conceitual)

---

## 🎯 Tema Escolhido
**Sistema de Gerenciamento de Tarefas (Task Manager)**

O sistema permite criar, listar, alterar status/prioridade, filtrar e remover tarefas, além de processar automaticamente tarefas em fila por ordem de prioridade/chegada.

---

## 🛠️ Como Executar o Projeto

### Pré-requisitos
- **Node.js** (versão 14 ou superior) instalada na máquina.

### Passo a Passo

1. Extraia o arquivo `sistema_web_cliente_servidor.zip`.
2. Abra o terminal na pasta extraída:
   ```bash
   cd sistema_web_cliente_servidor
   ```
3. Instale as dependências:
   ```bash
   npm install
   ```
4. Inicie o servidor:
   ```bash
   npm start
   ```
5. Acesse no seu navegador:
   ```
   http://localhost:3000
   ```

---

## 🏛️ Explicação da Arquitetura Cliente-Servidor

A aplicação segue estritamente o modelo **Cliente-Servidor (Client-Server)** com desacoplamento entre frontend e backend via protocolo **HTTP/JSON**:

- **Cliente (Frontend):**
  - Desenvolvido em **HTML5**, **CSS3 (Flexbox/Grid)** e **JavaScript assíncrono (Fetch API)**.
  - É responsável pela apresentação da interface gráfica ao usuário, captura de dados digitados nos formulários, validação inicial no lado do cliente e envio de requisições AJAX assíncronas para o servidor sem recarregar a página.

- **Servidor (Backend):**
  - Desenvolvido em **Node.js** com o framework **Express**.
  - Responsável por escutar requisições HTTP na porta 3000, rotear os pedidos, aplicar regras de negócio, validar os dados recebidos no corpo da requisição (`req.body`), manipular o Banco de Dados e devolver respostas HTTP formatadas em **JSON** junto com os devidos **Códigos de Status HTTP** (ex: 200, 201, 400, 404, 500).

- **Banco de Dados:**
  - Banco de dados relacional **SQLite3** persistido em arquivo local (`database.sqlite`).
  - Armazena a tabela `tarefas` garantindo a persistência dos dados entre reinicializações do servidor.

---

## 🔌 Rotas/Endpoints da API RESTful

| Método HTTP | Endpoint / Rota | Descrição | Status HTTP de Sucesso |
| :--- | :--- | :--- | :--- |
| `GET` | `/api/tarefas` | Retorna a lista de todas as tarefas cadastradas no banco de dados. | `200 OK` |
| `GET` | `/api/tarefas/:id` | Retorna os detalhes de uma tarefa específica por ID. | `200 OK` |
| `POST` | `/api/tarefas` | Cria e cadastra uma nova tarefa no banco de dados. | `201 Created` |
| `PUT` | `/api/tarefas/:id` | Atualiza os dados de uma tarefa existente. | `200 OK` |
| `DELETE` | `/api/tarefas/:id` | Exclui uma tarefa do banco de dados pelo seu ID. | `200 OK` |
| `POST` | `/api/tarefas/processar-fila` | Processa e conclui a tarefa mais antiga da Fila (FIFO). | `200 OK` |

---

## 🔄 Demonstrativo das Operações CRUD

1. **CREATE (POST `/api/tarefas`):**
   - Recebe dados em JSON (`titulo`, `descricao`, `prioridade`, `status`).
   - Instancia a classe `Task` e realiza a inserção `INSERT INTO tarefas ...`.

2. **READ (GET `/api/tarefas`):**
   - Executa a consulta `SELECT * FROM tarefas ORDER BY id DESC`.
   - Retorna um array JSON com todos os registros.

3. **UPDATE (PUT `/api/tarefas/:id`):**
   - Executa `UPDATE tarefas SET titulo=?, descricao=?, prioridade=?, status=? WHERE id=?`.
   - Atualiza o registro no banco.

4. **DELETE (DELETE `/api/tarefas/:id`):**
   - Executa `DELETE FROM tarefas WHERE id=?`.
   - Remove permanentemente o registro.

---

## 🧩 Orientação a Objetos (Classe `Task`)

A entidade principal do sistema foi modelada na classe `Task` (`Task.js`).

```javascript
class Task {
    #id; // Atributo privado (Encapsulamento)
    
    constructor(id, titulo, descricao, prioridade = 'media', status = 'pendente', criadaEm = null) {
        this.#id = id;
        this.titulo = titulo;
        this.descricao = descricao;
        this.prioridade = prioridade;
        this.status = status;
        this.criadaEm = criadaEm || new Date().toISOString();
    }

    // Getters e Setters (Encapsulamento)
    getId() { return this.#id; }
    
    // Método da Classe
    concluir() {
        this.status = 'concluida';
    }

    // Método de Validação de Regra de Negócio
    validar() {
        if (!this.titulo || this.titulo.trim().length < 3) {
            return { valido: false, erro: 'O título deve ter pelo menos 3 caracteres.' };
        }
        if (!['baixa', 'media', 'alta'].includes(this.prioridade)) {
            return { valido: false, erro: 'Prioridade inválida.' };
        }
        return { valido: true };
    }
}
```

- **Atributos:** `#id`, `titulo`, `descricao`, `prioridade`, `status`, `criadaEm`.
- **Encapsulamento:** O ID da tarefa é privado (`#id`), protegido contra alterações externas diretas, acessível apenas pelo método `getId()`.
- **Métodos:** `validar()` valida os dados da entidade; `concluir()` altera o estado do objeto.

---

## 🏗️ Estrutura de Dados (Fila / Queue)

O sistema utiliza uma **Fila (Queue)** baseada no princípio **FIFO (First-In, First-Out — Primeiro a Entrar, Primeiro a Sair)** para gerenciar o lote de execução de tarefas pendentes (`TaskQueue.js`).

```javascript
class TaskQueue {
    constructor() {
        this.items = []; // Estrutura linear interna
    }

    // Enfileirar (Enqueue)
    enqueue(task) {
        this.items.push(task);
    }

    // Desenfileirar (Dequeue) - Remove o primeiro elemento da fila (FIFO)
    dequeue() {
        if (this.isEmpty()) return null;
        return this.items.shift();
    }

    isEmpty() {
        return this.items.length === 0;
    }
}
```

**Aplicação no Projeto:**
A Fila organiza as tarefas pendentes por ordem de chegada. Quando o usuário clica em "Processar Próxima Tarefa da Fila", o sistema aplica o método `dequeue()`, retirando o item mais antigo da fila e marcando-o como concluído.

---

## 📚 Questões para Revisão Conceitual (Respostas Completas)

### 1. Diferença entre Função e Procedimento
- **Função:** Bloco de código reutilizável que processa dados e **obrigatoriamente retorna um valor** para o ponto onde foi chamada. Exemplo: `function somar(a, b) { return a + b; }`.
- **Procedimento:** Bloco de código que executa um conjunto de instruções/ações mas **não retorna valor** (retorna `void`/`undefined`). Exemplo: `function exibirMensagem(msg) { console.log(msg); }`.

### 2. Parâmetros e Valores de Retorno
- **Parâmetros:** Variáveis declaradas na assinatura de uma função que recebem os valores (argumentos) passados durante sua chamada.
- **Valores de Retorno:** A saída gerada pelo processamento da função devolvida através da palavra-chave `return`.

### 3. Caso-base em uma Função Recursiva
- O **caso-base** é a condição de parada de uma função recursiva. Sem o caso-base, a função continuaria chamando a si mesma infinitamente até estourar a memória (estouro de pilha / *Stack Overflow*).

### 4. Diferença entre Recursão e Repetição
- **Recursão:** Acontece quando uma função chama a si mesma até atingir o caso-base. Adequada para problemas divisíveis em subproblemas idênticos (ex: árvores, fatorial).
- **Repetição (Laços/Loops):** Utiliza estruturas de controle (`for`, `while`, `do-while`) para executar um bloco repetidamente com base em uma condição, geralmente consumindo menos memória que a recursão.

### 5. Funcionamento de Listas, Pilhas e Filas
- **Lista:** Coleção sequencial onde elementos podem ser inseridos, acessados ou removidos em qualquer posição (início, meio ou fim).
- **Pilha:** Estrutura linear restrita onde a inserção e a remoção ocorrem no mesmo extremo (topo).
- **Fila:** Estrutura linear onde elementos são inseridos no final e removidos no início.

### 6. Conceitos de LIFO e FIFO
- **LIFO (Last-In, First-Out):** "Último a entrar, primeiro a sair". Princípio de funcionamento da **Pilha**. Exemplo: pilha de pratos ou o botão "Desfazer" (Ctrl+Z).
- **FIFO (First-In, First-Out):** "Primeiro a entrar, primeiro a sair". Princípio de funcionamento da **Fila**. Exemplo: fila de banco ou fila de impressão.

### 7. Classes, Objetos, Atributos e Métodos
- **Classe:** O "molde" ou projeto abstrato que define as características e comportamentos de uma entidade.
- **Objeto:** Uma instância concreta criada a partir de uma classe (`new Task()`).
- **Atributos:** Variáveis que representam as características/estado do objeto (ex: `titulo`, `status`).
- **Métodos:** Funções associadas à classe que definem as ações e comportamentos do objeto (ex: `concluir()`, `validar()`).

### 8. Encapsulamento e Herança
- **Encapsulamento:** Técnica de esconder os detalhes internos e dados sensíveis de um objeto, permitindo acesso apenas por métodos públicos (getters/setters). Protege contra modificações indevidas.
- **Herança:** Mecanismo que permite a uma classe filha reutilizar e estender atributos e métodos de uma classe pai/superclasse (palavra-chave `extends`).

### 9. Banco de Dados Relacional
- Sistema de armazenamento de dados estruturado em **tabelas** compostas por linhas (registros) e colunas (campos), onde as tabelas se relacionam entre si garantindo integridade dos dados (ACID).

### 10. Chave Primária e Chave Estrangeira
- **Chave Primária (Primary Key - PK):** Coluna ou conjunto de colunas que identifica de forma **única** cada registro em uma tabela (ex: `id`). Não admite valores nulos ou duplicados.
- **Chave Estrangeira (Foreign Key - FK):** Coluna em uma tabela que faz referência à Chave Primária de outra tabela, criando um relacionamento entre elas.

### 11. Comandos SQL: CREATE, INSERT, SELECT, UPDATE e DELETE
- **`CREATE`:** Cria estruturas no banco (ex: `CREATE TABLE tarefas (...)`).
- **`INSERT`:** Insere novos registros (ex: `INSERT INTO tarefas (titulo) VALUES ('Aprender Node')`).
- **`SELECT`:** Consulta e recupera dados (ex: `SELECT * FROM tarefas WHERE status = 'pendente'`).
- **`UPDATE`:** Modifica registros existentes (ex: `UPDATE tarefas SET status = 'concluida' WHERE id = 1`).
- **`DELETE`:** Remove registros (ex: `DELETE FROM tarefas WHERE id = 1`).

### 12. Relacionamento entre Tabelas e JOIN
- **Relacionamento:** Vínculo lógico entre tabelas (1:1, 1:N, N:N).
- **JOIN:** Comando SQL utilizado para combinar dados de duas ou mais tabelas em uma única consulta com base em colunas relacionadas (ex: `INNER JOIN`, `LEFT JOIN`).

### 13. Diferença entre Cliente e Servidor
- **Cliente:** A interface/aplicação gráfica que faz a requisição de dados ou serviços (ex: Navegador Web).
- **Servidor:** A aplicação remota que processa as requisições, executa regras de negócio, acessa o banco e devolve as respostas esperadas.

### 14. Funcionamento Básico do Protocolo HTTP
- O protocolo **HTTP (HyperText Transfer Protocol)** opera em modelo de Requisição-Resposta (Request-Response). O cliente envia uma mensagem HTTP (com método, cabeçalhos e corpo) e o servidor processa e retorna uma mensagem de resposta (com código de status, cabeçalhos e dados).

### 15. Métodos HTTP (GET, POST, PUT/PATCH, DELETE)
- **`GET`:** Solicita a leitura/obtenção de recursos. Não altera dados no servidor.
- **`POST`:** Submete novos dados para criação de um recurso.
- **`PUT`:** Substitui/atualiza completamente um recurso existente.
- **`PATCH`:** Modifica parcialmente um recurso existente.
- **`DELETE`:** Remove um recurso específico.

### 16. Códigos de Status HTTP
- **1xx (Informativos):** Requisição recebida e em processamento.
- **2xx (Sucesso):** Ex: `200 OK` (Sucesso), `201 Created` (Recurso criado).
- **3xx (Redirecionamento):** Ex: `301 Moved Permanently`, `304 Not Modified`.
- **4xx (Erro do Cliente):** Ex: `400 Bad Request`, `404 Not Found`, `401 Unauthorized`.
- **5xx (Erro do Servidor):** Ex: `500 Internal Server Error`, `503 Service Unavailable`.

### 17. HTML Semântico
- Utilização de tags HTML de acordo com o seu significado conceitual (ex: `<header>`, `<nav>`, `<main>`, `<section>`, `<article>`, `<footer>`) em vez de genéricas `<div>` e `<span>`. Melhora a acessibilidade e SEO.

### 18. Seletores CSS
- Padrões usados para selecionar e estilizar elementos HTML:
  - **Seletor de Tipo/Tag:** `p { color: black; }`
  - **Seletor de Classe:** `.btn { padding: 10px; }`
  - **Seletor de ID:** `#header { background: #333; }`
  - **Seletores Compostos/Atributos:** `input[type="text"]`

### 19. Flexbox e CSS Grid
- **Flexbox (Flexible Box Layout):** Modelo unidimensional (linha OU coluna) ideal para alinhar e distribuir espaço entre itens dentro de um contêiner.
- **CSS Grid Layout:** Modelo bidimensional (linhas E colunas simultaneamente) ideal para criar layouts de páginas inteiras e estruturas complexas.

### 20. Funcionamento Geral de uma Aplicação Web Integrada a Banco de Dados
1. O usuário realiza uma ação na interface HTML/CSS (ex: clica em enviar formulário).
2. O JavaScript (Frontend) intercepta a ação e dispara uma requisição HTTP (Fetch API) para o backend.
3. O servidor (Backend - Express) recebe a requisição no endpoint configurado.
4. O backend valida os dados, executa a regra de negócio e envia um comando SQL ao Banco de Dados.
5. O Banco de Dados processa a instrução SQL e retorna o resultado ao servidor.
6. O servidor formata o resultado em JSON e devolve com um código HTTP para o cliente.
7. O cliente recebe o JSON e atualiza a página manipulando o DOM em tempo real.
