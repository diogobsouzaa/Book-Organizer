#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura de um nó da lista
typedef struct Node {
    char dado[40];
    int posicao;
    struct Node* next;
} Node;

Node* criarNode(char* dado, int posicao);
void inserirNoInicio(Node** head, char* dado, int posicao);
void inserirNoFim(Node** head, char* dado, int posicao);
Node* buscarPorPosicao(Node* head, int posicao);
Node* buscarPorDado(Node* head, char* dado);
void inserirNoMeio(Node** head, char* dado, int posicao, int novaPosicao);
void imprimirLista(Node* head);
void remover(Node** head, int posicao);
void removerPorDado(Node** head, char* dado);

