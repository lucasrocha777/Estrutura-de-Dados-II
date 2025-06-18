



# Trabalho Prático IV - Implementação de Tabela Hash em C

## Disciplina  
**Estruturas de Dados II**  
**Professor:** Jean Bertrand  
**Data de Entrega:** 23 de Junho de 2025

---

## Integrantes do Grupo

- **Lucas Gabriel Rocha Constancio** – Matricula: *[2023010280]*  
- **LUCAS MATHEUS NOBRE COELHO** - Matricula: *[2023010727]*
- **GUILHERME ANTÔNIO JOSÉ CAETANO RAMOS MATOS** - Matricula: *[2023010736]*
- **YAN DOS SANTOS TEIXEIRA** - Matricula: *[2023010530]*
---

## Descrição do Projeto

Este projeto tem como objetivo a implementação de uma Tabela Hash em linguagem C utilizando:

- Função Hash com método da multiplicação  
- Tratamento de colisões por Encadeamento Separado (listas ligadas)

O programa simula um sistema de armazenamento de notas de alunos (chave = nome do aluno + índice, valor = nota) e realiza operações de inserção, busca, remoção e impressão da tabela. Além disso, gera estatísticas sobre o uso da tabela e demonstra colisões.

---

## Estrutura do Projeto

- `hash.h` – Definições das estruturas e protótipos das funções.  
- `hash.c` – Implementação da Tabela Hash e funções auxiliares.  
- `main.c` – Programa principal que testa todas as operações.

---

## Como Funciona a Função Hash

A função hash foi implementada com o Método da Multiplicação, utilizando a constante A = 0.6180339887 (inspirada no número áureo).  
A string é convertida em um valor numérico k por meio da soma ponderada dos caracteres:

Loop de conversão da chave:
- Para cada caractere `c` da chave, multiplica-se `k` por 31 e soma-se o valor de `c`:
  `k = k * 31 + (unsigned char)c;`

Depois, aplicamos a fórmula:
- `produto = k * A`
- `frac = produto - floor(produto)`
- `indice = TAMANHO_TABELA * frac`

---

## Compilação e Execução

### Requisitos

- Compilador C (GCC ou compatível)
- Sistema operacional com terminal

### Instruções

1. Compile o projeto:
   gcc main.c hash.c -o tabela_hash

2. Execute o programa:
   ./tabela_hash

---

## Funcionalidades Demonstradas

- Inserção de 50 pares aleatórios de aluno/nota  
- Impressão da tabela completa  
- Estatísticas como:
  - Total de colisões
  - Taxa de ocupação
  - Tamanho da maior lista encadeada
- Demonstração de colisões com prefixos específicos  
- Liberação correta da memória

---

## Dificuldades Encontradas

- Garantir boa distribuição da função hash  
- Gerenciar corretamente memória dinâmica com malloc e free  
- Evitar vazamentos de memória ao remover elementos  
- Entender e implementar encadeamento separado corretamente

---

## Benefícios do Código

- Clareza e modularidade: separação entre cabeçalho, implementação e programa principal  
- Código comentado: fácil entendimento para futuros desenvolvedores  
- Tratamento de colisões funcional: permite múltiplas chaves por índice  
- Estatísticas úteis: permitem visualizar o comportamento da Tabela Hash  
- Fácil extensão: pode ser adaptado para armazenar outros tipos de dados

### Melhorias Futuras

- Implementar redimensionamento automático da tabela  
- Adotar alocação dinâmica de strings  
- Melhor interface de interação com o usuário

---

## Observações Finais

- O código foi escrito em conformidade com o padrão C99.  
- Todos os requisitos descritos no enunciado foram implementados.  
- Garantimos a liberação total de memória e a ausência de vazamentos.
