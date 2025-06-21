#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINHA 256
#define MAX_SENSOR 100

typedef struct {
    long timestamp;
    char id_sensor[32];
    char valor[64];
} Leitura;

int comparar_desc(const void *a, const void *b) {
    return ((Leitura*)b)->timestamp - ((Leitura*)a)->timestamp;
}

void organizar_dados(const char *arquivo_entrada) {
    FILE *fp = fopen(arquivo_entrada, "r");
    if (!fp) {
        perror("Erro ao abrir arquivo");
        exit(1);
    }

    Leitura leituras[10000];
    int total = 0;

    while (fscanf(fp, "%ld %s %s", &leituras[total].timestamp, leituras[total].id_sensor, leituras[total].valor) == 3) {
        total++;
    }

    fclose(fp);

    qsort(leituras, total, sizeof(Leitura), comparar_desc);

    for (int i = 0; i < total; i++) {
        char nome_arquivo[64];
        snprintf(nome_arquivo, sizeof(nome_arquivo), "%s.txt", leituras[i].id_sensor);
        FILE *out = fopen(nome_arquivo, "a");
        fprintf(out, "%ld %s %s\n", leituras[i].timestamp, leituras[i].id_sensor, leituras[i].valor);
        fclose(out);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <arquivo_entrada>\n", argv[0]);
        return 1;
    }
    organizar_dados(argv[1]);
    return 0;
}