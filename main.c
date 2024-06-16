#include "headers/func.h"
#include "headers/list.h"

int main() {
    Node *headP = NULL;
    Node *headS = NULL;

    // Abre os arquivos
    FILE *out_registros = fopen(REGISTROS, "w+");
    if (out_registros == NULL) {
        printf("Erro ao abrir o arquivo de registros\n");
        exit(1);
    }
    FILE *out_indices_primarios = fopen(INDICES_P, "w+");
    if (out_indices_primarios == NULL) {
        printf("Erro ao abrir o arquivo de indices primarios\n");
        exit(1);
    }
    FILE *out_indices_secundarios = fopen(INDICES_S, "w+");
    if (out_indices_secundarios == NULL) {
        printf("Erro ao abrir o arquivo de indices secundarios\n");
        exit(1);
    }

    // Coloca os indices em RAM (se já existirem no arquivo)
    arq_IndicePrimario_RAM(out_indices_primarios, &headP);
    arq_IndiceSecundario_RAM(out_indices_secundarios, &headS);

    int opcao = 0;    
    
    while (opcao != 5) {
        printf("MENU PRINCIPAL\nEscolha uma opcao:\n");
        printf("1. Criar Registro\n");
        printf("2. Ler Registros\n");
        printf("3. Alterar Registro\n");
        printf("4. Apagar Registro\n");
        printf("5. Salvar e Sair\n");
        printf("Selecione uma opcao: \n");

        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                criar_registro(out_registros, out_indices_primarios, out_indices_secundarios, &headP, &headS);
                printf("\nRegistro criado\n\n");
                break;
            case 2:
                ler_registro(out_registros, headP, headS);
                printf("\n\n");
                break;
            case 3:
                att_registro(out_registros, out_indices_primarios, out_indices_secundarios, headP, headS);
                printf("\n\n");
                break;
            case 4:
                apagar_registro(out_registros, out_indices_primarios, out_indices_secundarios, &headP, &headS);
                printf("\n\n");
                break;
            case 5:
                // Atualizar arquivo de indices
                ColocaArquivo_IndiceP(out_indices_primarios, headP);
                ColocaArquivo_IndiceS(out_indices_secundarios, headS);
                printf("\nConteudo salvo - Saindo ...\n");
                break;
            default:
                printf("Opcao invalida -- escolha outra opcao: ");
                break;    
        }
    }

    fclose(out_registros);
    fclose(out_indices_primarios);
    fclose(out_indices_secundarios);

    return 0;
}

