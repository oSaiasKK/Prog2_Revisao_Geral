// Estrutura de Dados: Fila (Queue) FIFO (First-In, First-Out)
class TaskQueue {
    constructor() {
        this.items = [];
    }

    // Enfileirar
    enqueue(task) {
        this.items.push(task);
    }

    // Desenfileirar
    dequeue() {
        if (this.isEmpty()) return null;
        return this.items.shift();
    }

    // Espiar o primeiro item
    peek() {
        if (this.isEmpty()) return null;
        return this.items[0];
    }

    isEmpty() {
        return this.items.length === 0;
    }

    size() {
        return this.items.length;
    }

    getAll() {
        return [...this.items];
    }
}

module.exports = TaskQueue;
