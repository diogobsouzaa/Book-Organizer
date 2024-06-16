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

void criar_registro(FILE *arquivo_registros, FILE *arquivoIndicePrimario, FILE *arquivoIndiceSecundario, Node** headP, Node** headS);
void ler_registro(FILE *arquivo_registros, Node* headP, Node* headS);
void apagar_registro(FILE *arquivo_registros, FILE *arquivoIndicePrimario, FILE *arquivoIndiceSecundario, Node **headP, Node **headS);

int encontrar_registro_isbn(Node* headP);
int encontrar_registro_titulo(Node* headS);

void att_registro(FILE *arquivo_registros, FILE* arquivoIndicePrimario, FILE* arquivoIndiceSecundario, Node *headP, Node *headS);
void att_indiceP(FILE *arquivoIndicePrimario, char *isbn, int posicao, Node *headP);
void att_indiceS(FILE *arquivoIndiceSecundario, char *titulo, int posicao, Node *headS);

void RAM_IndicePrimario(char isbn[15], int posicao, Node** headP);
void RAM_IndiceSecundario(char titulo[MAX_TITULO], int posicao, Node** headS);

void arq_IndicePrimario_RAM(FILE *arquivoIndicePrimario, Node** headP);
void arq_IndiceSecundario_RAM(FILE *arquivoIndiceSecundario, Node** headS);
void ColocaArquivo_IndiceP(FILE *arquivoIndicePrimario, Node* headP);
void ColocaArquivo_IndiceS(FILE *arquivoIndiceSecundario, Node* headS);

