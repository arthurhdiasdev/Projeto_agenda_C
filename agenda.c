#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_DESC 100

typedef struct {
    char data[11];  // formato: dd/mm/aaaa
    char hora[6];   // formato: hh:mm
    char descricao[MAX_DESC];
} Evento;

void adicionarEvento() {
    Evento e;
    FILE *f = fopen("eventos.txt", "a");

    if (!f) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    printf("Data (dd/mm/aaaa): ");
    scanf(" %10[^\n]", e.data);
    printf("Hora (hh:mm): ");
    scanf(" %5[^\n]", e.hora);
    printf("Descrição: ");
    getchar(); // limpar o buffer
    fgets(e.descricao, MAX_DESC, stdin);
    e.descricao[strcspn(e.descricao, "\n")] = '\0'; // remove '\n'

    fprintf(f, "%s|%s|%s\n", e.data, e.hora, e.descricao);
    fclose(f);
    printf("Evento adicionado com sucesso!\n");
}

void listarEventos() {
    Evento e;
    FILE *f = fopen("eventos.txt", "r");

    if (!f) {
        printf("Nenhum evento encontrado.\n");
        return;
    }

    printf("\n--- Lista de Eventos ---\n");
    while (fscanf(f, " %10[^|]|%5[^|]|%100[^\n]\n", e.data, e.hora, e.descricao) != EOF) {
        printf("Data: %s | Hora: %s | %s\n", e.data, e.hora, e.descricao);
    }
    fclose(f);
}

void buscarPorData() {
    char data[11];
    Evento e;
    int encontrado = 0;

    printf("Digite a data para buscar (dd/mm/aaaa): ");
    scanf(" %10[^\n]", data);

    FILE *f = fopen("eventos.txt", "r");
    if (!f) {
        printf("Nenhum evento encontrado.\n");
        return;
    }

    printf("\n--- Eventos em %s ---\n", data);
    while (fscanf(f, " %10[^|]|%5[^|]|%100[^\n]\n", e.data, e.hora, e.descricao) != EOF) {
        if (strcmp(e.data, data) == 0) {
            printf("Hora: %s | %s\n", e.hora, e.descricao);
            encontrado = 1;
        }
    }
    if (!encontrado) printf("Nenhum evento encontrado para essa data.\n");
    fclose(f);
}

void menu() {
    int opc;
    do {
        printf("\n===== AGENDA DE EVENTOS =====\n");
        printf("1. Adicionar Evento\n");
        printf("2. Listar Eventos\n");
        printf("3. Buscar por Data\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opc);

        switch (opc) {
            case 1: adicionarEvento(); break;
            case 2: listarEventos(); break;
            case 3: buscarPorData(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opção inválida!\n");
        }
    } while (opc != 0);
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    menu();
    return 0;
}
