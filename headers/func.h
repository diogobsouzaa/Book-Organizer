#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

#define TRUE 1
#define FALSE 0

//#define FIM_REGISTRO "#"
#define VAZIO "@"

#define REGISTROS "dados/registros.txt"
#define INDICES_P "dados/indices primarios.txt"
#define INDICES_S "dados/indices secundarios.txt"

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
} Livro; // " manga "

typedef struct {
    char isbn[15];
    int posicao;
} IndicePrimario;

typedef struct {
    char titulo[MAX_TITULO];
    int posicao;
} IndiceSecundario;
 

void criar_registro(FILE *arquivo_registros, FILE *arquivoIndicePrimario, FILE *arquivoIndiceSecundario, Node** headP, Node** headS);//cria um registro (de tamanho fixo e campos de tamanho fixo) e coloca no arquivo, coloca tambem nos indices
void ler_registro(FILE *arquivo_registros, Node* headP, Node* headS);//procura no indice primario ou secundario e imprime o registro
void apagar_registro(FILE *arquivo_registros, FILE *arquivoIndicePrimario, FILE *arquivoIndiceSecundario);//procura no indice primario ou secundario e apaga o registro nas listas de indices e no arquivo de registros

int encontrar_registro_isbn(Node* headP); //procura na lista de indice primario e retorna posição do registro
int encontrar_registro_titulo(Node* headS); //procura na lista de indice secundario e retorna posição do registro

void att_registro(FILE *arquivo_registros,FILE* arquivoIndicePrimario, FILE* arquivoIndiceSecundario, Node *headP, Node *headS);//atualizar o arquivo de registro, após procurar nos indices e achar o registro
void att_indiceP(FILE *arquivoIndicePrimario, char *isbn, int posicao, Node *headP);//atualiza o indice primario na RAM e no arquivo
void att_indiceS(FILE *arquivoIndiceSecundario, char *titulo, int posicao, Node *headS);//atualiza o indice secundario na RAM e no arquivo

void RAM_IndicePrimario(char isbn[15], int posicao, Node** headP); //coloca um dado de indice primario na lista encadeada (list.c)
//como o indice secundario possui apenas o titulo nao eh possivel coloca-lo em ordem, como se fosse com o autor (por exemplo), porque os titulos serao sempre diferentes
void RAM_IndiceSecundario(char titulo[MAX_TITULO], int posicao, Node** headS); //coloca um dado de indice secundario na lista encadeada (list.c)

void arq_IndicePrimario_RAM(FILE *arquivoIndicePrimario, Node** headP); //coloca os dados do arquivo de indices primarios na RAM (em uma lista encadeada (list.c))
void arq_IndiceSecundario_RAM(FILE *arquivoIndiceSecundario, Node** headS); //coloca os dados do arquivo de indices secundarios na RAM (em uma lista encadeada (list.c))
void ColocaArquivo_IndiceP(FILE *arquivoIndicePrimario, Node* headP); //coloca os dados da RAM no arquivo de indices primarios
void ColocaArquivo_IndiceS(FILE *arquivoIndiceSecundario, Node* headS); //coloca os dados da RAM no arquivo de indices secundarios 