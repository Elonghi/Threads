#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_ELEMENTOS 30

int main() {
    FILE *arquivo;
    int i, numero;

    // Inicializa o gerador de números aleatórios com base no tempo atual
    srand(time(NULL));

    // Abre o arquivo para escrita
    arquivo = fopen("numeros.dat", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Gera e escreve os números aleatórios no arquivo
    for (i = 0; i < NUM_ELEMENTOS; i++) {
        numero = rand() % 100; // Gera um número entre 0 e 99
        fprintf(arquivo, "%d\n", numero);
    }

    // Fecha o arquivo
    fclose(arquivo);

    printf("Arquivo 'numeros.dat' gerado com sucesso.\n");

    return 0;
}
