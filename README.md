# Projeto de Processamento de Sensores Industriais

Este repositório contém três programas em C que processam, consultam e geram dados de sensores industriais.

## Programas

### 1. Organizador de Dados (`organizar_dados.c`)
- Entrada: arquivo bruto com leituras no formato `<TIMESTAMP> <ID_SENSOR> <VALOR>`
- Saída: arquivos separados por sensor, com dados ordenados em ordem decrescente.

### 2. Consulta por Instante (`consulta_temporal.c`)
- Entrada: nome do sensor e timestamp (epoch)
- Saída: leitura mais próxima do instante informado (com busca binária).

### 3. Gerador de Arquivo (`gerar_dados.c`)
- Entrada: intervalo de tempo e sensores com tipo (`CONJ_Z`, `CONJ_Q`, `TEXTO`, `BINARIO`)
- Saída: `dados_gerados.txt` com 2000 leituras por sensor.

## Compilação

```bash
gcc -o organizar_dados organizar_dados.c
gcc -o consulta_temporal consulta_temporal.c
gcc -o gerar_dados gerar_dados.c
```

## Uso

```bash
./organizar_dados dados_gerados.txt
./consulta_temporal sensor1 1718572800
./gerar_dados 2024-06-01T00:00:00 2024-06-02T00:00:00 sensor1:CONJ_Z sensor2:TEXTO
```

## Autor
Aluno: [Seu Nome]
Entrega: 16/06