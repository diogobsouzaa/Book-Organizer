#include "headers/func.h"
#include "headers/list.h"

void criar_registro(FILE *arquivo_registros, FILE *arquivoIndicePrimario, FILE *arquivoIndiceSecundario, Node** headP, Node** headS) {
    Livro livro;

    fseek(arquivo_registros, 0, SEEK_END);
    int posicao = ftell(arquivo_registros);

    printf("Forneca algumas informacoes sobre o livro: \n");
    printf("ISBN: ");
    scanf("%s", livro.isbn);
    printf("Titulo: ");
    scanf(" %[^\n]", livro.titulo);
    printf("Autores: ");
    scanf(" %[^\n]", livro.autores);
    printf("Ano de Inicio: ");
    scanf("%d", &livro.ano_inicio);
    printf("Ano de Fim: ");
    scanf("%d", &livro.ano_fim);
    printf("Genero: ");
    scanf(" %[^\n]", livro.genero);
    printf("Revista: ");
    scanf(" %[^\n]", livro.revista);
    printf("Editora: ");
    scanf(" %[^\n]", livro.editora);
    printf("Ano da Edicao: ");
    scanf("%d", &livro.ano_edicao);
    printf("Quantidade de Volumes: ");
    scanf("%d", &livro.quantidade_volumes);
    printf("Quantidade de Volumes Adquiridos: ");
    scanf("%d", &livro.quantidade_volumes_adquiridos);

    printf("Quais volumes voce possui? (para parar envie -1): ");
    int sair = 0;
    for (int i = 0; i < MAX_VOLUMES; i++) {
        scanf("%d", &sair);
        if (sair != -1) {
            livro.volumes_adquiridos[i] = sair;
        } else {
            livro.volumes_adquiridos[i] = -1;
            break;
        }
    }

    // Escrevendo no arquivo de registros
    fwrite(&livro, sizeof(Livro), 1, arquivo_registros);

    // Escrevendo em RAM os indices
    RAM_IndicePrimario(livro.isbn, posicao, headP);
    RAM_IndiceSecundario(livro.titulo, posicao, headS);
}

void RAM_IndicePrimario(char isbn[15], int posicao, Node** headP) {
    inserirNoFim(headP, isbn, posicao);
}

void RAM_IndiceSecundario(char titulo[MAX_TITULO], int posicao, Node** headS) {
    inserirNoFim(headS, titulo, posicao);
}

void arq_IndicePrimario_RAM(FILE *arquivoIndicePrimario, Node** headP) {
    IndicePrimario indicePrimario;
    fseek(arquivoIndicePrimario, 0, SEEK_SET);
    while (fread(&indicePrimario, sizeof(IndicePrimario), 1, arquivoIndicePrimario)) {
        RAM_IndicePrimario(indicePrimario.isbn, indicePrimario.posicao, headP);
    }
}

void arq_IndiceSecundario_RAM(FILE *arquivoIndiceSecundario, Node** headS) {
    IndiceSecundario indiceSecundario;
    fseek(arquivoIndiceSecundario, 0, SEEK_SET);
    while (fread(&indiceSecundario, sizeof(IndiceSecundario), 1, arquivoIndiceSecundario)) {
        RAM_IndiceSecundario(indiceSecundario.titulo, indiceSecundario.posicao, headS);
    }
}

void ColocaArquivo_IndiceP(FILE *arquivoIndicePrimario, Node* headP) {
    IndicePrimario indicePrimario;
    Node* current = headP;
    fseek(arquivoIndicePrimario, 0, SEEK_SET);
    while (current != NULL) {
        strcpy(indicePrimario.isbn, current->dado);
        indicePrimario.posicao = current->posicao;
        fwrite(&indicePrimario, sizeof(IndicePrimario), 1, arquivoIndicePrimario);
        current = current->next;
    }
}

void ColocaArquivo_IndiceS(FILE *arquivoIndiceSecundario, Node* headS) {
    IndiceSecundario indiceSecundario;
    Node* current = headS;
    fseek(arquivoIndiceSecundario, 0, SEEK_SET);
    while (current != NULL) {
        strcpy(indiceSecundario.titulo, current->dado);
        indiceSecundario.posicao = current->posicao;
        fwrite(&indiceSecundario, sizeof(IndiceSecundario), 1, arquivoIndiceSecundario);
        current = current->next;
    }
}

int encontrar_registro_isbn(Node* headP) {
    char isbn[15];
    printf("Forneca o ISBN do livro: ");
    scanf("%s", isbn);
    Node* current = buscarPorDado(headP, isbn);
    if (current != NULL) {
        return current->posicao;
    } else {
        return -1;
    }
}

int encontrar_registro_titulo(Node* headS) {
    char titulo[MAX_TITULO];
    printf("Forneca o titulo do livro: ");
    scanf("%s", titulo);
    Node* current = buscarPorDado(headS, titulo);
    if (current != NULL) {
        return current->posicao;
    } else {
        return -1;
    }
}

void ler_registro(FILE *arquivo_registros, Node* headP, Node* headS) {
    int opcao;
    printf("Como deseja procurar o registro?\n");
    printf("1. ISBN\n");
    printf("2. Titulo\n");
    printf("Selecione uma opcao: ");
    scanf("%d", &opcao);

    if (opcao != 1 && opcao != 2) {
        printf("Opcao invalida. Por favor, selecione 1 ou 2.\n");
        return;
    }

    int posicao = -1;
    if (opcao == 1) {
        posicao = encontrar_registro_isbn(headP);
    } else if (opcao == 2) {
        posicao = encontrar_registro_titulo(headS);
    }

    if (posicao != -1) {
        Livro livro;
        fseek(arquivo_registros, posicao, SEEK_SET);
        fread(&livro, sizeof(Livro), 1, arquivo_registros);

        // Verifica se o registro foi deletado
        if (strcmp(livro.isbn, VAZIO) == 0) {
            printf("Registro nao encontrado\n");
            return;
        }

        printf("\nISBN: %s\n", livro.isbn);
        printf("Titulo: %s\n", livro.titulo);
        printf("Autores: %s\n", livro.autores);
        printf("Ano de Inicio: %d\n", livro.ano_inicio);
        printf("Ano de Fim: %d\n", livro.ano_fim);
        printf("Genero: %s\n", livro.genero);
        printf("Revista: %s\n", livro.revista);
        printf("Editora: %s\n", livro.editora);
        printf("Ano da Edicao: %d\n", livro.ano_edicao);
        printf("Quantidade de Volumes: %d\n", livro.quantidade_volumes);
        printf("Quantidade de Volumes Adquiridos: %d\n", livro.quantidade_volumes_adquiridos);
        printf("Volumes Adquiridos: ");
        for (int i = 0; i < MAX_VOLUMES; i++) {
            if (livro.volumes_adquiridos[i] != -1) {
                printf("%d ", livro.volumes_adquiridos[i]);
            } else {
                break;
            }
        }
        printf("\n");
    } else {
        printf("Registro nao encontrado\n");
    }
}

void att_registro(FILE *arquivo_registros, FILE *arquivoIndicePrimario, FILE *arquivoIndiceSecundario, Node *headP, Node *headS) {
    int opcao;
    printf("Como deseja procurar o registro?\n");
    printf("1. ISBN\n");
    printf("2. Titulo\n");
    printf("Selecione uma opcao: ");
    scanf("%d", &opcao);

    int posicao = -1;
    if (opcao == 1) {
        posicao = encontrar_registro_isbn(headP);
    } else if (opcao == 2) {
        posicao = encontrar_registro_titulo(headS);
    }

    if (posicao != -1) {
        fseek(arquivo_registros, posicao, SEEK_SET);
        Livro livro;
        fread(&livro, sizeof(Livro), 1, arquivo_registros);

        printf("Forneca as novas informacoes sobre o livro (deixe em branco para manter o valor atual):\n");

        char buffer[100];

        printf("ISBN [%s]: ", livro.isbn);
        scanf("%s", buffer);
        if (strcmp(buffer, "") != 0) strcpy(livro.isbn, buffer);

        printf("Titulo [%s]: ", livro.titulo);
        scanf(" %[^\n]", buffer);
        if (strcmp(buffer, "") != 0) strcpy(livro.titulo, buffer);

        printf("Autores [%s]: ", livro.autores);
        scanf(" %[^\n]", buffer);
        if (strcmp(buffer, "") != 0) strcpy(livro.autores, buffer);

        printf("Ano de Inicio [%d]: ", livro.ano_inicio);
        scanf("%s", buffer);
        if (strcmp(buffer, "") != 0) livro.ano_inicio = atoi(buffer);

        printf("Ano de Fim [%d]: ", livro.ano_fim);
        scanf("%s", buffer);
        if (strcmp(buffer, "") != 0) livro.ano_fim = atoi(buffer);

        printf("Genero [%s]: ", livro.genero);
        scanf(" %[^\n]", buffer);
        if (strcmp(buffer, "") != 0) strcpy(livro.genero, buffer);

        printf("Revista [%s]: ", livro.revista);
        scanf(" %[^\n]", buffer);
        if (strcmp(buffer, "") != 0) strcpy(livro.revista, buffer);

        printf("Editora [%s]: ", livro.editora);
        scanf(" %[^\n]", buffer);
        if (strcmp(buffer, "") != 0) strcpy(livro.editora, buffer);

        printf("Ano da Edicao [%d]: ", livro.ano_edicao);
        scanf("%s", buffer);
        if (strcmp(buffer, "") != 0) livro.ano_edicao = atoi(buffer);

        printf("Quantidade de Volumes [%d]: ", livro.quantidade_volumes);
        scanf("%s", buffer);
        if (strcmp(buffer, "") != 0) livro.quantidade_volumes = atoi(buffer);

        printf("Quantidade de Volumes Adquiridos [%d]: ", livro.quantidade_volumes_adquiridos);
        scanf("%s", buffer);
        if (strcmp(buffer, "") != 0) livro.quantidade_volumes_adquiridos = atoi(buffer);

        printf("Volumes Adquiridos (separados por espaco, -1 para finalizar): ");
        int i = 0;
        while (i < MAX_VOLUMES) {
            int volume;
            scanf("%d", &volume);
            if (volume == -1) break;
            livro.volumes_adquiridos[i++] = volume;
        }
        while (i < MAX_VOLUMES) livro.volumes_adquiridos[i++] = -1;

        fseek(arquivo_registros, posicao, SEEK_SET);
        fwrite(&livro, sizeof(Livro), 1, arquivo_registros);

        // Atualizar os índices
        att_indiceP(arquivoIndicePrimario, livro.isbn, posicao, headP);
        att_indiceS(arquivoIndiceSecundario, livro.titulo, posicao, headS);

        printf("Registro atualizado com sucesso.\n");
    } else {
        printf("Registro nao encontrado.\n");
    }
}

void att_indiceP(FILE *arquivoIndicePrimario, char *isbn, int posicao, Node *headP) {
    Node* current = buscarPorDado(headP, isbn);
    if (current != NULL) {
        current->posicao = posicao;
        strcpy(current->dado, isbn);
    } else {
        inserirNoFim(&headP, isbn, posicao);
    }
    ColocaArquivo_IndiceP(arquivoIndicePrimario, headP);
}

void att_indiceS(FILE *arquivoIndiceSecundario, char *titulo, int posicao, Node *headS) {
    Node* current = buscarPorDado(headS, titulo);
    if (current != NULL) {
        current->posicao = posicao;
        strcpy(current->dado, titulo);
    } else {
        inserirNoFim(&headS, titulo, posicao);
    }
    ColocaArquivo_IndiceS(arquivoIndiceSecundario, headS);
}

void apagar_registro(FILE *arquivo_registros, FILE *arquivoIndicePrimario, FILE *arquivoIndiceSecundario, Node **headP, Node **headS) {
    int opcao;
    printf("Como deseja procurar o registro para apagar?\n");
    printf("1. ISBN\n");
    printf("2. Titulo\n");
    printf("Selecione uma opcao: ");
    scanf("%d", &opcao);

    int posicao = -1;
    if (opcao == 1) {
        posicao = encontrar_registro_isbn(*headP);
    } else if (opcao == 2) {
        posicao = encontrar_registro_titulo(*headS);
    }

    if (posicao != -1) {
        fseek(arquivo_registros, posicao, SEEK_SET);
        Livro livro;
        fread(&livro, sizeof(Livro), 1, arquivo_registros);
        
        printf("Tem certeza que deseja apagar o registro do livro '%s' (ISBN: %s)? (s/n): ", livro.titulo, livro.isbn);
        char confirmacao;
        scanf(" %c", &confirmacao);

        if (confirmacao == 's' || confirmacao == 'S') {
            // Marcar todos os campos do registro como vazio
            strcpy(livro.isbn, VAZIO);
            strcpy(livro.titulo, VAZIO);
            strcpy(livro.autores, VAZIO);
            livro.ano_inicio = -1;
            livro.ano_fim = -1;
            strcpy(livro.genero, VAZIO);
            strcpy(livro.revista, VAZIO);
            strcpy(livro.editora, VAZIO);
            livro.ano_edicao = -1;
            livro.quantidade_volumes = -1;
            livro.quantidade_volumes_adquiridos = -1;
            for (int i = 0; i < MAX_VOLUMES; i++) {
                livro.volumes_adquiridos[i] = -1;
            }

            fseek(arquivo_registros, posicao, SEEK_SET);
            fwrite(&livro, sizeof(Livro), 1, arquivo_registros);

            // Atualizar os índices
            removerPorDado(headP, livro.isbn);
            removerPorDado(headS, livro.titulo);

            // Salvar alterações nos arquivos de índices
            ColocaArquivo_IndiceP(arquivoIndicePrimario, *headP);
            ColocaArquivo_IndiceS(arquivoIndiceSecundario, *headS);

            printf("Registro apagado com sucesso.\n");
        } else {
            printf("Operacao cancelada.\n");
        }
    } else {
        printf("Registro nao encontrado.\n");
    }
}

