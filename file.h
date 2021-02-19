#define FILE_PATH "/home/gustavo/Documents/projeto-1-tag/soc-dolphins_cleaned.mtx"

int readFile() {
    int a, b;
    FILE *fptr;                     // Criado ponteiro para arquivo

    fptr = fopen(FILE_PATH, "r");   // Abre o arquivo no modo leitura

    // Verifica se o arquivo foi aberto com sucesso
    if(fptr == NULL) {
        printf("Error! Opening file failed!");
        return 1;
    }

    // Loop que irá ler todas as linhas até o final do arquivo (EOF)
    while(fscanf(fptr, "%d %d", &a, &b) != EOF) {
        printf("%d %d\n", a, b);
    }

    fclose(fptr);
}