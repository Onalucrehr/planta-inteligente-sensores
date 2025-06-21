#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct {
    long timestamp;
    char valor[64];
} Leitura;

Leitura buscar_proximo(char *arquivo, long alvo) {
    FILE *fp = fopen(arquivo, "r");
    if (!fp) {
        perror("Arquivo não encontrado");
        exit(1);
    }

    Leitura leituras[10000];
    int total = 0;
    char sensor[32];

    while (fscanf(fp, "%ld %s %s", &leituras[total].timestamp, sensor, leituras[total].valor) == 3) {
        total++;
    }
    fclose(fp);

    int ini = 0, fim = total - 1, melhor = -1;
    long min_diff = LONG_MAX;
    while (ini <= fim) {
        int mid = (ini + fim) / 2;
        long diff = labs(leituras[mid].timestamp - alvo);
        if (diff < min_diff) {
            min_diff = diff;
            melhor = mid;
        }

        if (leituras[mid].timestamp > alvo) {
            ini = mid + 1;
        } else {
            fim = mid - 1;
        }
    }

    return leituras[melhor];
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s <sensor> <timestamp>\n", argv[0]);
        return 1;
    }

    char arquivo[64];
    snprintf(arquivo, sizeof(arquivo), "%s.txt", argv[1]);

    long alvo = atol(argv[2]);
    Leitura resultado = buscar_proximo(arquivo, alvo);

    printf("Leitura mais próxima: %ld %s\n", resultado.timestamp, resultado.valor);
    return 0;
}