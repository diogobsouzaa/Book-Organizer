#include "headers/func.h"

void criar_registro(FILE *arquivo_registros){
    Livro livro;
    fseek(arquivo_registros, 0, SEEK_END);

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

    printf("\nQuais volumes voce possui ? (para parar envie -1)");
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
}














void ler_registro(FILE *arquivo_registros);
void att_registro(FILE *arquivo_registros);
void apagar_registro(FILE *arquivo_registros);