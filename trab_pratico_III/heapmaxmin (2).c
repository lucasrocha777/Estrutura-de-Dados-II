#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// --- Protótipos das Funções ---
void trocar(int *a, int *b);
int obterPai(int i);
int obterFilhoEsquerdo(int i);
int obterFilhoDireito(int i);
void imprimirVetor(int arr[], int n, const char *mensagem);

// Protótipos para Max Heap
void maxHeapificarParaBaixo(int arr[], int tamanho, int idx);
void maxHeapificarParaCima(int arr[], int i);
void construirMaxHeap(int arr[], int tamanho);
void inserirMaxHeap(int arr[], int *tamanho, int valor);
int extrairMaxHeap(int arr[], int *tamanho);

// Protótipos para Min Heap
void minHeapificarParaBaixo(int arr[], int tamanho, int idx);
void minHeapificarParaCima(int arr[], int i);
void construirMinHeap(int arr[], int tamanho);
void inserirMinHeap(int arr[], int *tamanho, int valor);
int extrairMinHeap(int arr[], int *tamanho);

// Protótipo para Heap Sort
void heapSort(int arr[], int tamanho);

// --- Implementações das Funções ---

// Funções auxiliares (já existentes)
void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int obterPai(int i) {
    return (i - 1) / 2;
}

int obterFilhoEsquerdo(int i) {
    return 2 * i + 1;
}

int obterFilhoDireito(int i) {
    return 2 * i + 2;
}

void imprimirVetor(int arr[], int n, const char *mensagem) {
    printf("%s: [", mensagem);
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

// --- Implementações para Max Heap ---
void maxHeapificarParaBaixo(int arr[], int tamanho, int idx) {
    int maior = idx;
    int filhoEsquerdo = obterFilhoEsquerdo(idx);
    int filhoDireito = obterFilhoDireito(idx);

    if (filhoEsquerdo < tamanho && arr[filhoEsquerdo] > arr[maior]) {
        maior = filhoEsquerdo;
    }

    if (filhoDireito < tamanho && arr[filhoDireito] > arr[maior]) {
        maior = filhoDireito;
    }

    if (maior != idx) {
        trocar(&arr[idx], &arr[maior]);
        maxHeapificarParaBaixo(arr, tamanho, maior);
    }
}

void maxHeapificarParaCima(int arr[], int i) {
    while (i > 0) {
        int pai = obterPai(i);
        if (arr[i] > arr[pai]) {
            trocar(&arr[i], &arr[pai]);
            i = pai;
        } else {
            break;
        }
    }
}

void construirMaxHeap(int arr[], int tamanho) {
    for (int i = (tamanho / 2) - 1; i >= 0; i--) {
        maxHeapificarParaBaixo(arr, tamanho, i);
    }
}

void inserirMaxHeap(int arr[], int *tamanho, int valor) {
    (*tamanho)++;
    arr[*tamanho - 1] = valor;
    maxHeapificarParaCima(arr, *tamanho - 1);
}

int extrairMaxHeap(int arr[], int *tamanho) {
    if (*tamanho <= 0) {
        printf("Heap vazia!\n");
        return -1;
    }
    
    int raiz = arr[0];
    arr[0] = arr[*tamanho - 1];
    (*tamanho)--;
    maxHeapificarParaBaixo(arr, *tamanho, 0);
    return raiz;
}

// --- Implementações para Min Heap ---
void minHeapificarParaBaixo(int arr[], int tamanho, int idx) {
    int menor = idx;
    int filhoEsquerdo = obterFilhoEsquerdo(idx);
    int filhoDireito = obterFilhoDireito(idx);

    if (filhoEsquerdo < tamanho && arr[filhoEsquerdo] < arr[menor]) {
        menor = filhoEsquerdo;
    }

    if (filhoDireito < tamanho && arr[filhoDireito] < arr[menor]) {
        menor = filhoDireito;
    }

    if (menor != idx) {
        trocar(&arr[idx], &arr[menor]);
        minHeapificarParaBaixo(arr, tamanho, menor);
    }
}

void minHeapificarParaCima(int arr[], int i) {
    while (i > 0) {
        int pai = obterPai(i);
        if (arr[i] < arr[pai]) {
            trocar(&arr[i], &arr[pai]);
            i = pai;
        } else {
            break;
        }
    }
}

void construirMinHeap(int arr[], int tamanho) {
    for (int i = (tamanho / 2) - 1; i >= 0; i--) {
        minHeapificarParaBaixo(arr, tamanho, i);
    }
}

void inserirMinHeap(int arr[], int *tamanho, int valor) {
    (*tamanho)++;
    arr[*tamanho - 1] = valor;
    minHeapificarParaCima(arr, *tamanho - 1);
}

int extrairMinHeap(int arr[], int *tamanho) {
    if (*tamanho <= 0) {
        printf("Heap vazia!\n");
        return -1;
    }
    
    int raiz = arr[0];
    arr[0] = arr[*tamanho - 1];
    (*tamanho)--;
    minHeapificarParaBaixo(arr, *tamanho, 0);
    return raiz;
}

// --- Implementação do Heap Sort ---
void heapSort(int arr[], int tamanho) {
    construirMaxHeap(arr, tamanho);
    
    for (int i = tamanho - 1; i > 0; i--) {
        trocar(&arr[0], &arr[i]);
        maxHeapificarParaBaixo(arr, i, 0);
    }
}

// --- Função Principal (Main) ---
int main() {
    // Teste Max Heap
    int vetor_max[] = {4, 10, 3, 5, 1, 8, 12};
    int tamanho_max = sizeof(vetor_max) / sizeof(vetor_max[0]);

    imprimirVetor(vetor_max, tamanho_max, "Vetor Original (para Max Heap)");
    construirMaxHeap(vetor_max, tamanho_max);
    imprimirVetor(vetor_max, tamanho_max, "Max Heap Construida");

    printf("\n");

    // Teste Min Heap
    int vetor_min[] = {4, 10, 3, 5, 1, 8, 12};
    int tamanho_min = sizeof(vetor_min) / sizeof(vetor_min[0]);

    imprimirVetor(vetor_min, tamanho_min, "Vetor Original (para Min Heap)");
    construirMinHeap(vetor_min, tamanho_min);
    imprimirVetor(vetor_min, tamanho_min, "Min Heap Construida");

    printf("\n=== TESTES DAS NOVAS FUNCOES ===\n");

    // Testes Max Heap
    printf("\n--- Testes Max Heap ---\n");
    inserirMaxHeap(vetor_max, &tamanho_max, 15);
    imprimirVetor(vetor_max, tamanho_max, "Apos inserir 15");

    inserirMaxHeap(vetor_max, &tamanho_max, 0);
    imprimirVetor(vetor_max, tamanho_max, "Apos inserir 0");

    inserirMaxHeap(vetor_max, &tamanho_max, 7);
    imprimirVetor(vetor_max, tamanho_max, "Apos inserir 7");

    int extraido = extrairMaxHeap(vetor_max, &tamanho_max);
    printf("Elemento extraído (Max Heap): %d\n", extraido);
    imprimirVetor(vetor_max, tamanho_max, "Apos extrair raiz");

    // Testes Min Heap
    printf("\n--- Testes Min Heap ---\n");
    inserirMinHeap(vetor_min, &tamanho_min, 0);
    imprimirVetor(vetor_min, tamanho_min, "Apos inserir 0");

    inserirMinHeap(vetor_min, &tamanho_min, 2);
    imprimirVetor(vetor_min, tamanho_min, "Apos inserir 2");

    inserirMinHeap(vetor_min, &tamanho_min, 10);
    imprimirVetor(vetor_min, tamanho_min, "Apos inserir 10");

    extraido = extrairMinHeap(vetor_min, &tamanho_min);
    printf("Elemento extraído (Min Heap): %d\n", extraido);
    imprimirVetor(vetor_min, tamanho_min, "Apos extrair raiz");

    // Teste Heap Sort
    printf("\n--- Teste Heap Sort ---\n");
    int vetor_sort[] = {7, 2, 9, 1, 5, 3, 8, 4, 6};
    int tamanho_sort = sizeof(vetor_sort) / sizeof(vetor_sort[0]);

    imprimirVetor(vetor_sort, tamanho_sort, "Vetor Original (para Heap Sort)");
    heapSort(vetor_sort, tamanho_sort);
    imprimirVetor(vetor_sort, tamanho_sort, "Vetor Ordenado (Heap Sort)");

    return 0;
}