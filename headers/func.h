#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

#define FIM_REGISTRO "#"
#define FIM_CAMPO "|"

#define REGISTROS "registros.txt"
#define INDICES_P "indices primarios.txt"
#define INDICES_S "indices secundarios.txt"

#define MAX_TITULO 30
#define MAX_AUTOR 30
#define MAX_GENERO 10
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
} Livro; // " manga "

void criar_registro(FILE *arquivo_registros);
void ler_registro(FILE *arquivo_registros);
void att_registro(FILE *arquivo_registros);
void apagar_registro(FILE *arquivo_registros);
