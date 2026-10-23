// Classe Orientada a Objetos representando a entidade Tarefa
class Task {
    #id; // Atributo privado

    constructor(id, titulo, descricao, prioridade = 'media', status = 'pendente', criadaEm = null) {
        this.#id = id;
        this.titulo = titulo;
        this.descricao = descricao;
        this.prioridade = prioridade;
        this.status = status;
        this.criadaEm = criadaEm || new Date().toISOString();
    }

    getId() {
        return this.#id;
    }

    concluir() {
        this.status = 'concluida';
    }

    validar() {
        if (!this.titulo || this.titulo.trim().length < 3) {
            return { valido: false, erro: 'O título deve conter pelo menos 3 caracteres.' };
        }
        if (!['baixa', 'media', 'alta'].includes(this.prioridade)) {
            return { valido: false, erro: 'Prioridade deve ser baixa, media ou alta.' };
        }
        return { valido: true };
    }

    toJSON() {
        return {
            id: this.#id,
            titulo: this.titulo,
            descricao: this.descricao,
            prioridade: this.prioridade,
            status: this.status,
            criadaEm: this.criadaEm
        };
    }
}

module.exports = Task;
