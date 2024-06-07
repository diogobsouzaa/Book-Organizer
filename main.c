#include "headers/func.h"
#include "headers/list.h"

void main(){
    Node *headP = NULL;
    Node *headS = NULL;

    // Abre os arquivos
    FILE *out_registros = fopen (REGISTROS, "w+");
    if(out_registros == NULL){
        printf("Erro ao abrir o arquivo de registros\n");
        exit(1);
    }
    FILE *out_indices_primarios = fopen (INDICES_P, "w+");
    if(out_indices_primarios == NULL){
        printf("Erro ao abrir o arquivo de indices primarios\n");
        exit(1);
    }
    FILE *out_indices_secundarios = fopen (INDICES_S, "w+");
    if(out_indices_secundarios == NULL){
        printf("Erro ao abrir o arquivo de indices secundarios\n");
        exit(1);
    }


    int opcao;

    printf("MENU PRINCIPAL\n\nEscolha uma opção:\n");
    printf("1. Criar Registro\n");
    printf("2. Ler Registros\n");
    printf("3. Alterar Registro\n");
    printf("4. Apagar Registro\n");
    printf("5. Sair\n");
    printf("Selecione uma opcao: \n");    
    
    while(opcao != 5){

        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                void criar_registro(out_registros);
                printf("\n\n");
                break;
            case 2:
                void ler_registro(out_registros);
                printf("\n\n");
                break;
            case 3:
                void att_registro(out_registros);
                printf("\n\n");
                break;
            case 4:
                void apagar_registro(out_registros);
                printf("\n\n");
                break;
            case 5:
                printf("\nSaindo ...");
                break;
            default:
                prinft("opcao invalida -- escolha outra opcao: ");
                break;    
        }
        fclose(out_registros);
        fclose(out_indices_primarios);
        fclose(out_indices_secundarios);
    }
}