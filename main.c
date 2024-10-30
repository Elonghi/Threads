#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>

// Função que será executada pelas threads
void *routine(void *arg)
{
    struct timespec inicio, fim;
    clock_gettime(CLOCK_MONOTONIC, &inicio);
    printf("%s\n", (char *)arg);
    clock_gettime(&fim);
    printf("Tempo de execução: %lf\n", (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1000000000.0);
    return NULL;
}

// Função para verificar se o número de threads é válido
int validaEntradaThreads(int threadsNumber)
{
    int validThreads[3] = {2, 4, 8};
    for (int i = 0; i < 3; i++)
    {
        if (threadsNumber == validThreads[i])
        {
            return 1;
        }
    }
    return -1;
}
// Corrigindo a assinatura da função filtraArgumentos
int filtraArgumentos(int argc, char *argv[], char *argumento)
{
    int i;
    int arquivos = 0;
    int indiceArquivoSaida;
    for (i = 2; i < argc; i++)
    {
        if (strcmp(argv[i], "-o") == 0)
        {
            indiceArquivoSaida = i + 1;
            break;
        }
        arquivos++;
    }

    if (strcmp(argumento, "arquivosDeEntrada") == 0)
    {
        return arquivos;
    }
    if(strcmp(argumento, "arquivoDeSaida") == 0)
    {
        return indiceArquivoSaida;
    }
    return -1;
}

int main(int argc, char *argv[])
{
    int i;
    int num_threads = atoi(argv[1]);  // Convertendo argumento para inteiro
    int result; 
    int arquivos;
    char *nomeArquivoDeSaida; // Variável para armazenar o resultado da validação

    // Verificando se o número de threads é válido
    if (validaEntradaThreads(num_threads) != 1)
    {
        printf("Numero de threads invalido! Aceitos somente 2, 4 ou 8\n");
        return -1;
    }

    arquivos = filtraArgumentos(argc, argv, "arquivosDeEntrada");
    nomeArquivoDeSaida = argv[filtraArgumentos(argc, argv, "arquivoDeSaida")];

    // Alocando dinamicamente memória para o vetor de threads
    pthread_t *threads = (pthread_t *)malloc(num_threads * sizeof(pthread_t));

    // Verificando se a alocação foi bem-sucedida
    if (threads == NULL)
    {
        printf("Erro ao alocar memória para as threads.\n");
        return -1;
    }

    // Criando as threads
    for (i = 0; i < num_threads; i++)
    {
        printf("Creating thread %d\n", i);
        pthread_create(&threads[i], NULL, routine, (void *)argv[1]);
    }

    // Esperando todas as threads terminarem
    for (i = 0; i < num_threads; i++)
    {
        pthread_join(threads[i], NULL);
    }

    // Liberando a memória alocada dinamicamente
    free(threads);

    return 0;
}
