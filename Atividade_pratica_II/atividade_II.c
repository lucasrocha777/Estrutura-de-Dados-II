/*
Implementar um algoritmo de arvore Binaria de 
Busca e Arvore AVL.
- Verificar como os dados são inseridos nas  
arvores separadamente;
-  implementar o algoritmo de busca em ordem, 
pré ordem e pós ordem (mostrar a diferença em  
cada arvore)
-  implementar o algoritmo de busca e contabilizar 
quantas vezes ele foi acionado em cada arvore 
para buscar o próximo elemento

Discente: Lucas Gabriel Rocha Constancio
Matricula: 2023010280
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// Criando os ponteiros ABB 
typedef struct Node {
    int valor;
    struct Node* esquerda;
    struct Node* direita;
} Node;
// criando os ponteiros da AVL
typedef struct NodeAVL {
    int valor;
    struct NodeAVL* esquerda;
    struct NodeAVL* direita;
    int altura;
} NodeAVL;
// Contadores de buscas
int contadorBuscaABB = 0;
int contadorBuscaAVL = 0;
// ABB
Node* criarNode(int valor) {
    Node* novo = (Node*)malloc(sizeof(Node));
    novo->valor = valor;
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}
Node* inserirABB(Node* raiz, int valor) {
    if (raiz == NULL) return criarNode(valor);
    if (valor < raiz->valor)
        raiz->esquerda = inserirABB(raiz->esquerda, valor);
    else
        raiz->direita = inserirABB(raiz->direita, valor);
    return raiz;
}
void emOrdemABB(Node* raiz) {
    if (raiz != NULL) {
        emOrdemABB(raiz->esquerda);
        printf("%d ", raiz->valor);
        emOrdemABB(raiz->direita);
    }
}
void preOrdemABB(Node* raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->valor);
        preOrdemABB(raiz->esquerda);
        preOrdemABB(raiz->direita);
    }
}
void posOrdemABB(Node* raiz) {
    if (raiz != NULL) {
        posOrdemABB(raiz->esquerda);
        posOrdemABB(raiz->direita);
        printf("%d ", raiz->valor);
    }
}
Node* buscarABB(Node* raiz, int valor) {
    contadorBuscaABB++;
    if (raiz == NULL || raiz->valor == valor)
        return raiz;
    if (valor < raiz->valor)
        return buscarABB(raiz->esquerda, valor);
    else
        return buscarABB(raiz->direita, valor);
}
// AVL
int altura(NodeAVL* N) {
    if (N == NULL)
        return 0;
    return N->altura;
}
int max(int a, int b) {
    return (a > b) ? a : b;
}
NodeAVL* criarNodeAVL(int valor) {
    NodeAVL* node = (NodeAVL*)malloc(sizeof(NodeAVL));
    node->valor = valor;
    node->esquerda = NULL;
    node->direita = NULL;
    node->altura = 1;
    return node;
}
NodeAVL* rotacaoDireita(NodeAVL* y) {
    NodeAVL* x = y->esquerda;
    NodeAVL* T2 = x->direita;
    x->direita = y;
    y->esquerda = T2;
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;
    return x;
}
NodeAVL* rotacaoEsquerda(NodeAVL* x) {
    NodeAVL* y = x->direita;
    NodeAVL* T2 = y->esquerda;
    y->esquerda = x;
    x->direita = T2;
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;
    return y;
}
int getBalance(NodeAVL* N) {
    if (N == NULL)
        return 0;
    return altura(N->esquerda) - altura(N->direita);
}
NodeAVL* inserirAVL(NodeAVL* node, int valor) {
    if (node == NULL)
        return criarNodeAVL(valor);
    if (valor < node->valor)
        node->esquerda = inserirAVL(node->esquerda, valor);
    else if (valor > node->valor)
        node->direita = inserirAVL(node->direita, valor);
    else
        return node;
    node->altura = 1 + max(altura(node->esquerda), altura(node->direita));
    int balance = getBalance(node);
    // Rotação simples direita
    if (balance > 1 && valor < node->esquerda->valor)
        return rotacaoDireita(node);
    // Rotação simples esquerda
    if (balance < -1 && valor > node->direita->valor)
        return rotacaoEsquerda(node);
    // Rotação dupla esquerda-direita
    if (balance > 1 && valor > node->esquerda->valor) {
        node->esquerda = rotacaoEsquerda(node->esquerda);
        return rotacaoDireita(node);
    }
    // Rotação dupla direita-esquerda
    if (balance < -1 && valor < node->direita->valor) {
        node->direita = rotacaoDireita(node->direita);
        return rotacaoEsquerda(node);
    }
    return node;
}
void emOrdemAVL(NodeAVL* raiz) {
    if (raiz != NULL) {
        emOrdemAVL(raiz->esquerda);
        printf("%d ", raiz->valor);
        emOrdemAVL(raiz->direita);
    }
}
void preOrdemAVL(NodeAVL* raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->valor);
        preOrdemAVL(raiz->esquerda);
        preOrdemAVL(raiz->direita);
    }
}
void posOrdemAVL(NodeAVL* raiz) {
    if (raiz != NULL) {
        posOrdemAVL(raiz->esquerda);
        posOrdemAVL(raiz->direita);
        printf("%d ", raiz->valor);
    }
}
NodeAVL* buscarAVL(NodeAVL* raiz, int valor) {
    contadorBuscaAVL++;
    if (raiz == NULL || raiz->valor == valor)
        return raiz;
    if (valor < raiz->valor)
        return buscarAVL(raiz->esquerda, valor);
    else
        return buscarAVL(raiz->direita, valor);
}
// main com o menu 
int main() {
    Node* raizABB = NULL;
    NodeAVL* raizAVL = NULL;
    // Inicializa o gerador de números aleatórios
    srand(time(NULL));
    int n = 10; // Número de valores a serem gerados
    for (int i = 0; i < n; i++) {
        int valorAleatorio = rand() % 100; // Gera um número aleatório entre 0 e 99
        raizABB = inserirABB(raizABB, valorAleatorio);
        raizAVL = inserirAVL(raizAVL, valorAleatorio);
    }
    printf("=== Percursos ===\n");
    printf("ABB - Em Ordem: ");
    emOrdemABB(raizABB);
    printf("\n");
    printf("AVL - Em Ordem: ");
    emOrdemAVL(raizAVL);
    printf("\n");
    printf("ABB - Pre Ordem: ");
    preOrdemABB(raizABB);
    printf("\n");
    printf("AVL - Pre Ordem: ");
    preOrdemAVL(raizAVL);
    printf("\n");
    printf("ABB - Pos Ordem: ");
    posOrdemABB(raizABB);
    printf("\n");
    printf("AVL - Pos Ordem: ");
    posOrdemAVL(raizAVL);
    printf("\n");
    printf("\n=== Teste de Busca ===\n");
    int busca = 25; // Valor a ser buscado
    buscarABB(raizABB, busca);
    buscarAVL(raizAVL, busca);
    printf("Busca pelo valor %d:\n", busca);
    printf("ABB - Contador de buscas: %d\n", contadorBuscaABB);
    printf("AVL - Contador de buscas: %d\n", contadorBuscaAVL);
    
    return 0;
}