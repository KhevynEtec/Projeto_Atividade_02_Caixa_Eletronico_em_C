#include <stdio.h>
#include <string.h>

int main() {
    int saldo = 1000;
    int saque = 0;
    int continuar = 1;
    int i, a, b;
    int resto, achou, total_caixa, saldo_antigo;
    int numero_recibo = 1;
    int mostrar;
    int c;
    char linha[100];
    char titulo[30];
    FILE *arquivo;

    int notas[5] = {100, 50, 20, 10, 5};
    int qtd[5] = {0, 4, 10, 5, 10};
    int usadas[5];

    /* ---- CARREGAR DADOS DO CAIXA ---- */
    arquivo = fopen("caixa.txt", "r");

    if (arquivo != NULL) {
        if (fscanf(arquivo, "%d", &saldo) != 1) {
            saldo = 1000;
        }

        for (i = 0; i < 5; i++) {
            if (fscanf(arquivo, "%d", &qtd[i]) != 1 || qtd[i] < 0) {
                qtd[i] = (int[]){0, 4, 10, 5, 10}[i];
            }
        }

        fclose(arquivo);
    }

    /* ---- CONTAR RECIBOS ---- */
    arquivo = fopen("recibo.txt", "r");

    if (arquivo != NULL) {
        while (fgets(linha, sizeof(linha), arquivo) != NULL) {
            if (strstr(linha, "RECIBO") != NULL) {
                numero_recibo++;
            }
        }
        fclose(arquivo);
    }

    while (continuar == 1) {
        printf("\nSaldo atual: %d\n", saldo);
        printf("Digite valor do saque: ");

        if (scanf("%d", &saque) != 1) {
            while ((c = getchar()) != '\n' && c != EOF);
            if (c == EOF) break;
            printf("Digite apenas numeros\n");
            continue;
        }

        if (saque <= 0) {
            printf("Valor invalido\n");
        } else if (saque % 5 != 0) {
            printf("Tem que ser multiplo de 5\n");
            printf("Saque nao realizado, nenhum recibo foi gerado\n");
        } else if (saque > saldo) {
            printf("Saldo insuficiente\n");
        } else {
            achou = 0;

            for (a = qtd[0]; a >= 0 && achou == 0; a--) {
                for (b = qtd[1]; b >= 0 && achou == 0; b--) {
                    resto = saque - a * 100 - b * 50;

                    if (resto < 0) continue;

                    usadas[0] = a;
                    usadas[1] = b;

                    for (i = 2; i < 5; i++) {
                        usadas[i] = resto / notas[i];

                        if (usadas[i] > qtd[i]) {
                            usadas[i] = qtd[i];
                        }

                        resto -= usadas[i] * notas[i];
                    }

                    if (resto == 0) {
                        achou = 1;
                    }
                }
            }

            if (achou == 0) {
                printf("O caixa nao tem notas suficientes\n");
                printf("Saque nao realizado, nenhum recibo foi gerado\n");
            } else {
                for (i = 0; i < 5; i++) {
                    qtd[i] -= usadas[i];
                }

                saldo_antigo = saldo;
                saldo -= saque;

                printf("\nNotas entregues:\n");

                for (i = 0; i < 5; i++) {
                    if (usadas[i] > 0) {
                        printf("Notas de %d: %d\n", notas[i], usadas[i]);
                    }
                }

                printf("Novo saldo: %d\n", saldo);

                /* ---- SALVAR DADOS DO CAIXA ---- */
                arquivo = fopen("caixa.txt", "w");

                if (arquivo == NULL) {
                    printf("Erro ao salvar os dados do caixa!\n");
                } else {
                    fprintf(arquivo, "%d\n", saldo);

                    for (i = 0; i < 5; i++) {
                        fprintf(arquivo, "%d\n", qtd[i]);
                    }

                    fclose(arquivo);
                    printf("Dados do caixa salvos com sucesso!\n");
                }

                /* ---- GERAR RECIBO ---- */
                arquivo = fopen("recibo.txt", "a");

                if (arquivo == NULL) {
                    printf("Erro ao abrir arquivo do recibo\n");
                } else {
                    fprintf(arquivo, "------ RECIBO %d ------\n", numero_recibo);
                    fprintf(arquivo, "Valor do saque: %d\n", saque);

                    for (i = 0; i < 5; i++) {
                        if (usadas[i] > 0) {
                            fprintf(arquivo, "Notas de %d: %d\n", notas[i], usadas[i]);
                        }
                    }

                    fprintf(arquivo, "Saldo anterior: %d\n", saldo_antigo);
                    fprintf(arquivo, "Saldo atual: %d\n", saldo);
                    fprintf(arquivo, "----------------------\n\n");

                    fclose(arquivo);

                    printf("Recibo %d salvo no arquivo recibo.txt\n", numero_recibo);

                    /* ---- MOSTRAR RECIBO ---- */
                    arquivo = fopen("recibo.txt", "r");

                    if (arquivo == NULL) {
                        printf("Erro ao abrir arquivo para leitura\n");
                    } else {
                        sprintf(titulo, "RECIBO %d ", numero_recibo);
                        mostrar = 0;

                        printf("\n");

                        while (fgets(linha, sizeof(linha), arquivo) != NULL) {
                            if (strstr(linha, titulo) != NULL) {
                                mostrar = 1;
                            }

                            if (mostrar == 1) {
                                printf("%s", linha);
                            }
                        }

                        fclose(arquivo);
                    }

                    numero_recibo++;
                }
            }
        }

        /* ---- MOSTRAR NOTAS DISPONIVEIS ---- */
        total_caixa = 0;

        printf("\nNotas que ainda tem no caixa:\n");

        for (i = 0; i < 5; i++) {
            printf("Notas de %d: %d\n", notas[i], qtd[i]);
            total_caixa += notas[i] * qtd[i];
        }

        if (saldo <= 0) {
            printf("Voce nao tem mais saldo\n");
            break;
        }

        if (total_caixa == 0) {
            printf("O caixa ficou sem notas\n");
            break;
        }

        printf("\nDeseja realizar outro saque? (1 - Sim / 0 - Nao): ");

        if (scanf("%d", &continuar) != 1) {
            while ((c = getchar()) != '\n' && c != EOF);
            continuar = 0;
        }
    }

    return 0;
}
