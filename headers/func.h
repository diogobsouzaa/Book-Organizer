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

//lista encadeada que armazena os dados do indice primario



typedef struct {
    char isbn[15];
    int posicao;
} IndicePrimario;

typedef struct {
    char titulo[MAX_TITULO];
    int posicao;
} IndiceSecundario;

void criar_registro(FILE *arquivo_registros, FILE *arquivoIndicePrimario, FILE *arquivoIndiceSecundario);
void ler_registro(FILE *arquivo_registros, FILE *arquivoIndicePrimario, FILE *arquivoIndiceSecundario);
void att_registro(FILE *arquivo_registros, FILE *arquivoIndicePrimario, FILE *arquivoIndiceSecundario);
void apagar_registro(FILE *arquivo_registros, FILE *arquivoIndicePrimario, FILE *arquivoIndiceSecundario);
int encontrar_registro_isbn(FILE *arquivo_registros, FILE *arquivoIndicePrimario, FILE *arquivoIndiceSecundario); //retorna posição do registro
int encontrar_registro_titulo(FILE *arquivo_registros, FILE *arquivoIndicePrimario, FILE *arquivoIndiceSecundario); //retorna posição do registro
int att_indiceP(FILE *arquivoIndicePrimario, char *isbn, int posicao);
int att_indiceS(FILE *arquivoIndiceSecundario, char *titulo, int posicao);