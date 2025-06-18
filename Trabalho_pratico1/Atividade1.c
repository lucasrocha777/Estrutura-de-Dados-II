/*Algoritmo para Construção de Árvore Binária a partir de Expressões Aritméticas
 Analisar Expressão
 Ler a expressão aritmética e identificar números, operadores e parênteses.
 Construir Árvore
 Organizar a árvore respeitando a precedência matemática.
 Implementar Percurso
 Garantir que a avaliação da expressão seja correta ao percorrer a árvore.
 O algoritmo deve reconhecer como a precedência de operações modifica a estrutura da árvore. 
Por exemplo:
 • A expressão 2 * 4 + 3 resultará em uma estrutura arbórea que reflete a multiplicação 
sendo avaliada antes da adição.
 • A expressão 2 * (4 + 3) produzirá uma árvore onde a adição dentro dos parênteses é 
priorizada na estrutura
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

// Pilha para operadores
typedef struct {
    char data[MAX_SIZE];
    int top;
} Stack;

// Fila para saida em RPN
typedef struct {
    char data[MAX_SIZE][MAX_SIZE];
    int front, rear;
} Queue;

// Inicializa pilha
void initStack(Stack *s) {
    s->top = -1;
}

// Inicializa fila
void initQueue(Queue *q) {
    q -> front = q -> rear = -1;
}

// Empilha um operador 
void push (Stack *s, char op) {
    if (s -> top < MAX_SIZE - 1) {
        s -> data[++(s -> top)] = op;
    }
}

// Desempilha um operador
char pop(Stack *s) {
    if (s -> top >= 0) {
        return s -> data[(s -> top)--];
    }
    return '\0';
}

// Adiciona a fila de saida RPN
void enqueue(Queue *q, const char *token) {
    if (q -> rear < MAX_SIZE - 1) {
        strcpy(q -> data[++(q -> rear)], token);
    }
}

int precedence(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

void shuntingYard(const char *expr, Queue *output) {
    Stack opStack;
    initStack(&opStack);

    char token[20];
    int i = 0, j = 0;

    while (expr[i] != '\0') {
        if (isdigit(expr[i])) {
            j = 0;
            while (isdigit(expr[i])) {
                token[j++] = expr[i++];
            }
            token[j] = '\0';
            enqueue(output, token);
        } else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') {
            while (opStack.top != -1 && precedence(opStack.data[opStack.top]) >= precedence(expr[i])) {
                char op[2] = {pop(&opStack), '\0'};
                enqueue(output, op);
            }
            push(&opStack, expr[i]);
            i++;
        } else if (expr[i] == ' ') {
            i++;
        } else {
            printf("Caractere inválido: %c\n", expr[i]);
            exit(1);
        }
    }

    // Desempilha operadores restantes
    while (opStack.top != -1) {
        char op[2] = {pop(&opStack), '\0'};
        enqueue(output, op);
    }
}

int evaluateRPN(Queue *rpn) {
    Stack evalStack;
    initStack(&evalStack);

    for (int i = rpn->front + 1; i <= rpn->rear; i++) {
        if (isdigit(rpn->data[i][0])) {
            push(&evalStack, atoi(rpn->data[i]));
        } else {
            int b = pop(&evalStack);
            int a = pop(&evalStack);
            switch (rpn->data[i][0]) {
                case '+': push(&evalStack, a + b); break;
                case '-': push(&evalStack, a - b); break;
                case '*': push(&evalStack, a * b); break;
                case '/': push(&evalStack, a / b); break;
            }
        }
    }
    return pop(&evalStack);
}

int main() {
    char expr[MAX_SIZE];
    printf("Digite uma expressão (ex: 2 + 3 * 4): ");
    fgets(expr, MAX_SIZE, stdin);
    expr[strcspn(expr, "\n")] = '\0'; // Remove o '\n' do fgets

    Queue rpn;
    initQueue(&rpn);

    shuntingYard(expr, &rpn);
    int result = evaluateRPN(&rpn);

    printf("Resultado: %d\n", result);
    return 0;
}