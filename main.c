#include "headers/func.h"

void main(){
    FILE *out_registros = fopen (REGISTROS, "w+");

    int opcao;

    printf("MENU PRINCIPAL\n\nEscolha uma opção:\n");
    printf("1. Criar Registro\n");
    printf("2. Ler Registros\n");
    printf("3. Alterar Registro\n");
    printf("4. Apagar Registro\n");
    printf("5. Sair\n");
    printf("Selecione uma opcao: \n");    
    
    while(TRUE){

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
        }
        fclose(out_registros);

    }
}