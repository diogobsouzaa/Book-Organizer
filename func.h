#ifndef FUNC_H
#define FUNC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

#define TRUE 1
#define FALSE 0

//#define FIM_REGISTRO "#"
#define VAZIO "@"

#define REGISTROS "dados/registros.txt"
#define INDICES_P "dados/indices_primarios.txt"
#define INDICES_S "dados/indices_secundarios.txt"

#define MAX_TITULO 30
#define MAX_AUTOR 30
#define MAX_GENERO 20
#define MAX_REVISTA 20
#define MAX_EDITORA 20
#define MAX_VOLUMES 20

typedef struct {
    char isbn[15];
    char titulo[MAX_TITULO];
    char autores[MAX_AUTOR];
    int ano_inicio;
    int ano_fim;
    char genero[MAX_GENERO];
    char revista[MAX_REVISTA];
    char editora[MAX_EDITORA];
    int ano_edicao;
    int quantidade_volumes;
    int quantidade_volumes_adquiridos;
    int volumes_adquiridos[MAX_VOLUMES];
} Livro; // "manga"

typedef struct {
    char isbn[15];
    int posicao;
} IndicePrimario;

typedef struct {
    char titulo[MAX_TITULO];
    int posicao;
} IndiceSecundario;

void criar_registro(FILE *arquivo_registros, FILE *arquivoIndicePrimario, FILE *arquivoIndiceSecundario, Node** headP, Node** headS); // cria um registro e coloca no arquivo e nos indices
void ler_registro(FILE *arquivo_registros, Node* headP, Node* headS); // procura no indice primario ou secundario e imprime o registro
void apagar_registro(FILE *arquivo_registros, FILE *arquivoIndicePrimario, FILE *arquivoIndiceSecundario, Node** headP, Node** headS); // procura no indice primario ou secundario e apaga o registro

int encontrar_registro_isbn(Node* headP, const char* isbn); // procura na lista de indice primario e retorna a posição do registro
int encontrar_registro_titulo(Node* headS, const char* titulo); // procura na lista de indice secundario e retorna a posição do registro

void att_registro(FILE *arquivo_registros, FILE* arquivoIndicePrimario, FILE* arquivoIndiceSecundario, Node *headP, Node *headS); // atualiza o arquivo de registro
void att_indiceP(FILE *arquivoIndicePrimario, const char *isbn, int posicao, Node *headP); // atualiza o indice primario na RAM e no arquivo
void att_indiceS(FILE *arquivoIndiceSecundario, const char *titulo, int posicao, Node *headS); // atualiza o indice secundario na RAM e no arquivo

void RAM_IndicePrimario(char isbn[15], int posicao, Node** headP); // coloca um dado de indice primario na lista encadeada
void RAM_IndiceSecundario(char titulo[MAX_TITULO], int posicao, Node** headS); // coloca um dado de indice secundario na lista encadeada

void arq_IndicePrimario_RAM(FILE *arquivoIndicePrimario, Node** headP); // coloca os dados do arquivo de indices primarios na RAM
void arq_IndiceSecundario_RAM(FILE *arquivoIndiceSecundario, Node** headS); // coloca os dados do arquivo de indices secundarios na RAM
void ColocaArquivo_IndiceP(FILE *arquivoIndicePrimario, Node* headP); // coloca os dados da RAM no arquivo de indices primarios
void ColocaArquivo_IndiceS(FILE *arquivoIndiceSecundario, Node* headS); // coloca os dados da RAM no arquivo de indices secundarios

#endif // FUNC_H

