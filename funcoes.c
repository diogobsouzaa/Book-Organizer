#include "headers/func.h"

void criar_registro(FILE *arquivo_registros, FILE *arquivoIndicePrimario, FILE *arquivoIndiceSecundario){
    Livro livro;
    IndicePrimario indicePrimario;
    IndiceSecundario indiceSecundario;

    fseek(arquivo_registros, 0, SEEK_END);
    int posicao = ftell(arquivo_registros);

    printf("Forneça algumas informações sobre o livro: \n");
    printf("ISBN: ");
    scanf("%s\n", livro.isbn);
    printf("\nTitulo: ");
    scanf(" %[^\n]", livro.titulo);
    printf("\nAutores: ");
    scanf(" %[^\n]", livro.autores);
    printf("\nAno de Inicio: ");
    scanf("%d", &livro.ano_inicio);
    printf("\nAno de Fim: ");
    scanf("%d", &livro.ano_fim);
    printf("\nGenero: ");
    scanf(" %[^\n]", livro.genero);
    printf("\nRevista: ");
    scanf(" %[^\n]", livro.revista);
    printf("\nEditora: ");
    scanf(" %[^\n]", livro.editora);
    printf("\nAno da Edicao: ");
    scanf("%d", &livro.ano_edicao);
    printf("\nQuantidade de Volumes: ");
    scanf("%d", &livro.quantidade_volumes);
    printf("\nQuantidade de Volumes Adquiridos: ");
    scanf("%d", &livro.quantidade_volumes_adquiridos);

    printf("\nQuais volumes voce possui ? (para parar envie -1) : ");
    int sair = 0;
    for (int i = 0; i < MAX_VOLUMES; i++) {
        scanf("%d", &sair);
        if (sair != -1){
            livro.volumes_adquiridos[i] = sair;
        }
        else{
            break;
        }
    }

    fwrite(&livro, sizeof(Livro), 1, arquivo_registros);

    
    strcpy(indicePrimario.isbn, livro.isbn);
    indicePrimario.posicao = posicao;
    fseek(arquivoIndicePrimario, 0, SEEK_END);
    fwrite(&indicePrimario, sizeof(IndicePrimario), 1, arquivoIndicePrimario);

    
    strcpy(indiceSecundario.titulo, livro.titulo);
    indiceSecundario.posicao = posicao;
    fseek(arquivoIndiceSecundario, 0, SEEK_END);
    fwrite(&indiceSecundario, sizeof(IndiceSecundario), 1, arquivoIndiceSecundario);

}


int encontrar_registro_isbn(FILE *arquivo_registros, FILE *arquivoIndicePrimario, FILE *arquivoIndiceSecundario);

int encontrar_registro_titulo(FILE *arquivo_registros, FILE *arquivoIndicePrimario, FILE *arquivoIndiceSecundario);

void ler_registro(FILE *arquivo_registros, FILE *arquivoIndicePrimario, FILE *arquivoIndiceSecundario);

void att_registro(FILE *arquivo_registros, FILE *arquivoIndicePrimario, FILE *arquivoIndiceSecundario);

att_indiceP(FILE *arquivoIndicePrimario, char *isbn, int posicao);

att_indiceS(FILE *arquivoIndiceSecundario, char *titulo, int posicao);

void apagar_registro(FILE *arquivo_registros, FILE *arquivoIndicePrimario, FILE *arquivoIndiceSecundario);