#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 1000

typedef struct alunos {
    char nome[50];
    int matricula;
    int documento;
} Alunos;

void countingSort(Alunos arr[], int n) {
    Alunos output[n];
    int count[256] = {0};
    int i;

    for (i = 0; i < n; i++)
        count[(int) arr[i].nome[0]]++;

    for (i = 1; i <= 255; i++)
        count[i] += count[i - 1];

    for (i = n - 1; i >= 0; i--) {
        output[count[(int) arr[i].nome[0]] - 1] = arr[i];
        count[(int) arr[i].nome[0]]--;
    }

    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

int main(void) {
    FILE *arquivo;
    Alunos lista[MAX];
    int i, n = 0;
    char opcao;

    arquivo = fopen("alunos.txt", "r");

    if (arquivo == NULL) {
        printf("O arquivo nao foi encontrado.\n");
        exit(1);
    }

    while (fscanf(arquivo, "%s %d %d", lista[n].nome, &lista[n].matricula, &lista[n].documento) != EOF)
        n++;

    fclose(arquivo);
    printf("O arquivo foi carregado com sucesso!\n");

    printf("Deseja adicionar um novo aluno? (S/N) ");
    scanf(" %c", &opcao);

    if (opcao == 'S' || opcao == 's') {
        printf("Nome do aluno: ");
        scanf("%s", lista[n].nome);
        printf("Matricula do aluno: ");
        scanf("%d", &lista[n].matricula);
        printf("Documento do aluno(RG ou CPF): ");
        scanf("%d", &lista[n].documento);

        countingSort(lista, n + 1);
        n++;

        arquivo = fopen("alunos.txt", "w");

        for (i = 0; i < n; i++)
            fprintf(arquivo, "%s %d %d\n", lista[i].nome, lista[i].matricula, lista[i].documento);

        fclose(arquivo);

        printf("O aluno foi adicionado com sucesso!\n");
    }
    if (opcao == 'N' || opcao == 'n'){
      printf("Nao sera adicionado um novo aluno no arquivo");
    }

    printf("Tempo de execucao do processo de ordenacao: ");
    clock_t inicio, fim;
    double tempo_execucao;
    inicio = clock();

    countingSort(lista, n);

    fim = clock();
    tempo_execucao = (double) (fim - inicio) / CLOCKS_PER_SEC;
    printf("%lf segundos.\n", tempo_execucao);

    arquivo = fopen("alunos.txt", "w");

    for (i = 0; i < n; i++)
        fprintf(arquivo, "%s %d %d\n", lista[i].nome, lista[i].matricula, lista[i].documento);

    fclose(arquivo);

    printf("Os alunos foram ordenados com sucesso!\n");
    return 0;
}
