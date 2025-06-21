#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

long converter_para_timestamp(const char *data_str) {
    struct tm t = {0};
    sscanf(data_str, "%d-%d-%dT%d:%d:%d",
        &t.tm_year, &t.tm_mon, &t.tm_mday,
        &t.tm_hour, &t.tm_min, &t.tm_sec);
    t.tm_year -= 1900;
    t.tm_mon -= 1;
    return mktime(&t);
}

char *gerar_valor(char *tipo) {
    static char buffer[32];
    if (strcmp(tipo, "CONJ_Z") == 0) {
        sprintf(buffer, "%d", rand() % 1000);
    } else if (strcmp(tipo, "CONJ_Q") == 0) {
        sprintf(buffer, "%.2f", (float)rand() / RAND_MAX * 100.0);
    } else if (strcmp(tipo, "TEXTO") == 0) {
        int len = 4 + rand() % 12;
        for (int i = 0; i < len; i++)
            buffer[i] = 'A' + rand() % 26;
        buffer[len] = '\0';
    } else if (strcmp(tipo, "BINARIO") == 0) {
        strcpy(buffer, rand() % 2 ? "true" : "false");
    } else {
        strcpy(buffer, "INVAL");
    }
    return buffer;
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("Uso: %s <inicio> <fim> <sensor:tipo>...\n", argv[0]);
        return 1;
    }

    srand(time(NULL));
    long t_ini = converter_para_timestamp(argv[1]);
    long t_fim = converter_para_timestamp(argv[2]);

    if (t_ini == -1 || t_fim == -1 || t_ini >= t_fim) {
        printf("Intervalo de tempo inválido.\n");
        return 1;
    }

    FILE *out = fopen("dados_gerados.txt", "w");

    for (int i = 3; i < argc; i++) {
        char sensor[32], tipo[16];
        if (sscanf(argv[i], "%[^:]:%s", sensor, tipo) != 2) {
            printf("Formato inválido: %s\n", argv[i]);
            continue;
        }

        if (strcmp(tipo, "CONJ_Z") && strcmp(tipo, "CONJ_Q") &&
            strcmp(tipo, "TEXTO") && strcmp(tipo, "BINARIO")) {
            printf("Tipo inválido para %s\n", sensor);
            continue;
        }

        for (int j = 0; j < 2000; j++) {
            long ts = t_ini + rand() % (t_fim - t_ini);
            fprintf(out, "%ld %s %s\n", ts, sensor, gerar_valor(tipo));
        }
    }

    fclose(out);
    printf("Arquivo 'dados_gerados.txt' criado com sucesso!\n");
    return 0;
}