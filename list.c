#include "headers/list.h"

// Função para criar um novo nó
Node* criarNode(char* dado, int posicao) {
    Node* node = (Node*) malloc(sizeof(Node));
    strcpy(node->dado, dado);
    node->posicao = posicao;
    node->next = NULL;
    return node;
}

// Função para inserir um novo nó no início da lista
void inserirNoInicio(Node** head, char* dado, int posicao) {
    Node* node = criarNode(dado, posicao);
    node->next = *head;
    *head = node;
}

// Função para inserir um novo nó no final da lista
void inserirNoFim(Node** head, char* dado, int posicao) {
    Node* node = criarNode(dado, posicao);
    if (*head == NULL) {
        *head = node;
    } else {
        Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = node;
    }
}

// Função para buscar um nó pela posição
Node* buscarPorPosicao(Node* head, int posicao) {
    Node* current = head;
    while (current != NULL) {
        if (current->posicao == posicao) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Função para buscar um nó pelo dado
Node* buscarPorDado(Node* head, char* dado) {
    Node* current = head;
    while (current != NULL) {
        if (strcmp(current->dado, dado) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Função para inserir um novo nó no meio da lista, após encontrar a posição
void inserirNoMeio(Node** head, char* dado, int posicao, int novaPosicao) {
    Node* node = criarNode(dado, novaPosicao);
    Node* current = buscarPorPosicao(*head, posicao);
    if (current != NULL) {
        node->next = current->next;
        current->next = node;
    } else {
        printf("Posição não encontrada\n");
    }
}

// Função para imprimir a lista
void imprimirLista(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("Dado: %s, Posição: %d\n", current->dado, current->posicao);
        current = current->next;
    }
}

// Função para remover um nó pela posição
void remover(Node** head, int posicao) {
    Node* current = *head;
    Node* previous = NULL;

    while (current != NULL) {
        if (current->posicao == posicao) {
            if (previous == NULL) {
                *head = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
    printf("Posição não encontrada\n");
}

// Função para remover um nó pelo dado
void removerPorDado(Node** head, char* dado) {
    Node* current = *head;
    Node* previous = NULL;

    while (current != NULL) {
        if (strcmp(current->dado, dado) == 0) {
            if (previous == NULL) {
                *head = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
    printf("Dado não encontrado\n");
}

