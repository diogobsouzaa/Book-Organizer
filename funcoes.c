#include "headers/func.h"
#include "headers/list.h"

void criar_registro(FILE *arquivo_registros, FILE *arquivoIndicePrimario, FILE *arquivoIndiceSecundario, Node* headP, Node* headS){
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

    // Preenchendo campos de string até o tamanho máximo com VAZIO
    memset(livro.titulo + strlen(livro.titulo), VAZIO, MAX_TITULO - strlen(livro.titulo));
    memset(livro.autores + strlen(livro.autores), VAZIO, MAX_AUTOR - strlen(livro.autores));
    memset(livro.genero + strlen(livro.genero), VAZIO, MAX_GENERO - strlen(livro.genero));
    memset(livro.revista + strlen(livro.revista), VAZIO, MAX_REVISTA - strlen(livro.revista));
    memset(livro.editora + strlen(livro.editora), VAZIO, MAX_EDITORA - strlen(livro.editora));

    // Garantindo que as strings terminem com '\0'
    livro.titulo[MAX_TITULO - 1] = '\0';
    livro.autores[MAX_AUTOR - 1] = '\0';
    livro.genero[MAX_GENERO - 1] = '\0';
    livro.revista[MAX_REVISTA - 1] = '\0';
    livro.editora[MAX_EDITORA - 1] = '\0';

    // Escrevendo no arquivo de registros
    fwrite(&livro, sizeof(Livro), 1, arquivo_registros);

    // Colocando FIM_REGISTRO no final do registro
    fwrite(FIM_REGISTRO, sizeof(char), 1, arquivo_registros);

    // Escrevendo no arquivos de indices
    // Se isbn mudou 
    RAM_IndicePrimario(livro.isbn, posicao, headP);
    RAM_IndiceSecundario(livro.titulo, posicao, headS);
}



void RAM_IndicePrimario(char isnb[15], int posicao, Node* headP){
    inserirNoFim(&headP, isnb, posicao);
}

void RAM_IndiceSecundario(char titulo[MAX_TITULO], int posicao, Node* headS){
    inserirNoFim(&headS, titulo, posicao);
}

void arq_IndicePrimario_RAM(FILE *arquivoIndicePrimario, Node* headP){
    IndicePrimario indicePrimario;
    fseek(arquivoIndicePrimario, 0, SEEK_SET);
    while(fread(&indicePrimario, sizeof(IndicePrimario), 1, arquivoIndicePrimario)){
        RAM_IndicePrimario(indicePrimario.isbn, indicePrimario.posicao, headP);
    }
}

void arq_IndiceSecundario_RAM(FILE *arquivoIndiceSecundario, Node* headS){
    IndiceSecundario indiceSecundario;
    fseek(arquivoIndiceSecundario, 0, SEEK_SET);
    while(fread(&indiceSecundario, sizeof(IndiceSecundario), 1, arquivoIndiceSecundario)){
        RAM_IndiceSecundario(indiceSecundario.titulo, indiceSecundario.posicao, headS);
    }
}

void ColocaArquivo_IndiceP(FILE *arquivoIndicePrimario, Node* headP){
    IndicePrimario indicePrimario;
    Node* current = headP;
    fseek(arquivoIndicePrimario, 0, SEEK_SET);
    while(current != NULL){
        strcpy(indicePrimario.isbn, current->dado);
        indicePrimario.posicao = current->posicao;
        fwrite(&indicePrimario, sizeof(IndicePrimario), 1, arquivoIndicePrimario);
        current = current->next;
    }
}

void ColocaArquivo_IndiceS(FILE *arquivoIndiceSecundario, Node* headS){
    IndiceSecundario indiceSecundario;
    Node* current = headS;
    fseek(arquivoIndiceSecundario, 0, SEEK_SET);
    while(current != NULL){
        strcpy(indiceSecundario.titulo, current->dado);
        indiceSecundario.posicao = current->posicao;
        fwrite(&indiceSecundario, sizeof(IndiceSecundario), 1, arquivoIndiceSecundario);
        current = current->next;
    }
}

int encontrar_registro_isbn(Node* headP){
    char isbn[15];
    printf("Forneça o ISBN do livro: ");
    scanf("%s", isbn);
    Node* current = buscarPorDado(headP, isbn);
    if(current != NULL){
        return current->posicao;
    }
    else{
        return -1;
    }
}

int encontrar_registro_titulo(Node* headP){
    char titulo[MAX_TITULO];
    printf("Forneça o titulo do livro: ");
    scanf("%s", titulo);
    Node* current = buscarPorDado(headP, titulo);
    if(current != NULL){
        return current->posicao;
    }
    else{
        return -1;
    }
}
 
void ler_registro(FILE *arquivo_registros, Node* headP, Node* headS){
    int opcao;
    printf("Como deseja procurar o registro ?\n");
    printf("1. ISBN\n");
    printf("2. Titulo\n");
    printf("Selecione uma opcao: ");
    scanf("%d", &opcao);

    int posicao = -1;
    if(opcao == 1){
        posicao = encontrar_registro_isbn(headP);
    }
    if (opcao == 2){
        posicao = encontrar_registro_titulo(headS);
    }
    if(posicao != -1){
        Livro livro;
        fseek(arquivo_registros, posicao, SEEK_SET);
        fread(&livro, sizeof(Livro), 1, arquivo_registros);
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
            printf("%d ", livro.volumes_adquiridos[i]);
        }
        printf("\n");
    }
    else{
        printf("Registro nao encontrado\n");
    }
}

void att_registro(FILE *arquivo_registros,FILE *arquivoIndicePrimario, FILE *arquivoIndiceSecundario, Node *headP, Node *headS){
    int opcao;
    printf("Como deseja procurar o registro ?\n");
    printf("1. ISBN\n");
    printf("2. Titulo\n");
    printf("Selecione uma opcao: ");
    scanf("%d", &opcao);

    int posicao = -1;
    if(opcao == 1){
        posicao = encontrar_registro_isbn(headP);
    }
    if (opcao == 2){
        posicao = encontrar_registro_titulo(headS);
    }
    if(posicao != -1){
        Livro livro;
        //fread(&livro, sizeof(Livro), 1, arquivo_registros);
        printf("Forneça algumas informações sobre o livro: \n");
        printf("ISBN: ");//!
        scanf("%s\n", livro.isbn);//!
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

        fseek(arquivo_registros, posicao, SEEK_SET);
        fwrite(&livro, sizeof(Livro), 1, arquivo_registros);
        
        att_indiceP(arquivoIndicePrimario, livro.isbn, posicao, headP);
        att_indiceS(arquivoIndiceSecundario, livro.titulo, posicao, headS);

        printf("Registro atualizado com sucesso\n");
    }
    else{
        printf("Registro nao encontrado\n");
    }
}



void att_indiceP(FILE *arquivoIndicePrimario, char *isbn, int posicao, Node* headP){//!
    Node* current = buscarPorDado(headP, isbn);
    if(current != NULL){
        current->posicao = posicao;
        strcpy(current->dado, isbn);
    }
    else{
        inserirNoFim(&headP, isbn, posicao);
    }
    ColocaArquivo_IndiceP(arquivoIndicePrimario, headP);
}

void att_indiceS(FILE *arquivoIndiceSecundario, char *titulo, int posicao, Node* headS){//!
    Node* current = buscarPorDado(headS, titulo);
    if(current != NULL){
        current->posicao = posicao;
        strcpy(current->dado, titulo);
    }
    else{
        inserirNoFim(&headS, titulo, posicao);
    }
    ColocaArquivo_IndiceS(arquivoIndiceSecundario, headS);
}

void apagar_registro(FILE *arquivo_registros, FILE *arquivoIndicePrimario, FILE *arquivoIndiceSecundario);