#include <stdio.h>
#include <string.h>
#include <windows.h>

// Definições de cores para o terminal
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define RESET   "\x1b[0m"

int main() {
    // Configura a saída para UTF-8 (para acentos)
    SetConsoleOutputCP(65001);

    int opcao;

    do {
        printf(GREEN"\n===================================");
        printf(GREEN"\n===================================");
        printf(GREEN"\n=== SISTEMA DE GESTAO HOTELEIRA ===");
        printf(GREEN"\n===================================");
        printf(GREEN"\n===================================\n"RESET);


        printf("\n1. Cadastro de Hóspedes");
        printf("\n2. Controle de Quartos");
        printf("\n3. Registro de Reservas");
        printf("\n4. Check-in e Check-out");
        printf("\n5. Processamento de Pagamentos");
        printf("\n6. Emissão de Documentos");
        printf("\n7. Atualização de Limpeza");
        printf("\n8. Relatórios Gerenciais");
        printf("\n0. Sair");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                printf("Cadastro de Hóspedes\n");
                system("pause");
                break;
            case 2:
                printf("Controle de Quartos\n");
                system("pause");
                break;
            case 3:
                printf("Registro de Reservas\n");
                system("pause");
                break;
            case 4:
                printf("Check-in e Check-out\n");
                system("pause");
                break;
            case 5:
                printf("Processamento de Pagamentos\n");
                system("pause");
                break;
            case 6:
                printf("Emissão de Documentos\n");
                system("pause");
                break;
            case 7:
                printf("Atualização de Limpeza\n");
                system("pause");
                break;
            case 8:
                printf("Relatórios Gerenciais\n");
                system("pause");
                break;
            case 0:
                printf("Encerrando...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 0);

    return 0;
}