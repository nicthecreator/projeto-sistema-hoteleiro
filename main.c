#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// =======================
// STRUCT DE LOGIN
// =======================

typedef struct
{
    char login[30];
    char senha[30];
} pessoa;

pessoa p[5];

// =======================
// STRUCT DE HOSPEDES
// =======================

typedef struct
{
    char nome[50];
    char dataDeNascimento[20];
    char cpf[20];
} hospede;

hospede hosped[20];

// ======================================================
// FUNÇÕES DA RECEPÇÃO
// ======================================================

// CADASTRO DE HÓSPEDES
void cadastroDeHospedes()
{
    static int i = 0;
    int adicionarNovoHospede = 0;

    printf("\nCadastro de Hospedes selecionado.\n");

    printf("\nInsira o nome completo do hospede: ");
    getchar();
    fgets(hosped[i].nome, 50, stdin);

    hosped[i].nome[strcspn(hosped[i].nome, "\n")] = '\0';

    printf("\nInsira a data de nascimento do hospede (00/00/0000): ");
    scanf("%s", hosped[i].dataDeNascimento);

    printf("\nInsira o CPF do hospede (000.000.000-00): ");
    scanf("%s", hosped[i].cpf);

    printf("\nInformacoes do hospede:\n");
    printf("Nome: %s\n", hosped[i].nome);
    printf("Data de Nascimento: %s\n", hosped[i].dataDeNascimento);
    printf("CPF: %s\n", hosped[i].cpf);

    printf("\nDeseja adicionar outro hospede? Sim (1) / Nao (2): ");
    scanf("%d", &adicionarNovoHospede);

    if (adicionarNovoHospede == 1)
    {
        i++;

        if (i < 20)
        {
            cadastroDeHospedes();
        }
        else
        {
            printf("\nLimite de hospedes atingido!\n");
            i = 0;
        }
    }
    else
    {
        i = 0;
    }
}

// VERIFICAR HÓSPEDES
void verificarHospedesCadastrados()
{
    printf("\n==============================");
    printf("\n=== HOSPEDES CADASTRADOS ===");
    printf("\n==============================\n");

    for (int j = 0; j < 20; j++)
    {
        if (strlen(hosped[j].nome) > 0)
        {
            printf("Nome: %s\n", hosped[j].nome);
            printf("Data de Nascimento: %s\n", hosped[j].dataDeNascimento);
            printf("CPF: %s\n", hosped[j].cpf);
            printf("-----------------------------\n");
        }
    }
}

// ======================================================
// FUNÇÕES ADMINISTRADOR
// ======================================================

// RELATÓRIO
void relatorioHospedes()
{
    int total = 0;

    printf("\n==============================");
    printf("\n=== RELATORIO DE HOSPEDES ===");
    printf("\n==============================\n");

    for (int i = 0; i < 20; i++)
    {
        if (strlen(hosped[i].nome) > 0)
        {
            printf("\nHospede %d\n", i + 1);
            printf("Nome: %s\n", hosped[i].nome);
            printf("Data de Nascimento: %s\n", hosped[i].dataDeNascimento);
            printf("CPF: %s\n", hosped[i].cpf);
            printf("-----------------------------\n");

            total++;
        }
    }

    printf("\nTotal de hospedes cadastrados: %d\n", total);
}

// BUSCAR HÓSPEDE
void buscarHospedeCPF()
{
    char cpfBusca[20];
    int encontrado = 0;

    printf("\nDigite o CPF do hospede: ");
    scanf("%s", cpfBusca);

    for (int i = 0; i < 20; i++)
    {
        if (strcmp(hosped[i].cpf, cpfBusca) == 0)
        {
            printf("\n=== HOSPEDE ENCONTRADO ===\n");
            printf("Nome: %s\n", hosped[i].nome);
            printf("Data de Nascimento: %s\n", hosped[i].dataDeNascimento);
            printf("CPF: %s\n", hosped[i].cpf);

            encontrado = 1;
            break;
        }
    }

    if (encontrado == 0)
    {
        printf("\nHospede nao encontrado.\n");
    }
}

// REMOVER HÓSPEDE
void removerHospede()
{
    char cpfRemover[20];
    int encontrado = 0;

    printf("\nDigite o CPF do hospede que deseja remover: ");
    scanf("%s", cpfRemover);

    for (int i = 0; i < 20; i++)
    {
        if (strcmp(hosped[i].cpf, cpfRemover) == 0)
        {
            strcpy(hosped[i].nome, "");
            strcpy(hosped[i].dataDeNascimento, "");
            strcpy(hosped[i].cpf, "");

            printf("\nHospede removido com sucesso!\n");

            encontrado = 1;
            break;
        }
    }

    if (encontrado == 0)
    {
        printf("\nHospede nao encontrado.\n");
    }
}

// ======================================================
// MENUS
// ======================================================

// MENU RECEPCIONISTA
void menuRecepcionista()
{
    int opcao;

    do
    {
        printf("\n==========================");
        printf("\n=== PAINEL DA RECEPCAO ===");
        printf("\n==========================");
        printf("\n1. Cadastro de Hospedes");
        printf("\n2. Verificar Hospedes Cadastrados");
        printf("\n3. Voltar ao Login");
        printf("\nEscolha uma opcao: ");

        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            cadastroDeHospedes();
            break;

        case 2:
            verificarHospedesCadastrados();
            break;

        case 3:
            printf("\nVoltando ao painel de login...\n");
            return;

        default:
            printf("\nOpcao invalida!\n");
            break;
        }

    } while (1);
}


// MENU LIMPEZA
void menuAuxiliarDeLimpeza()
{
    int opcao;

    do
    {
        printf("\n=====================================");
        printf("\n=== PAINEL AUXILIAR DE LIMPEZA ===");
        printf("\n=====================================");
        printf("\n1. Atualizar Status do Quarto");
        printf("\n2. Voltar ao Login");
        printf("\nEscolha uma opcao: ");

        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("\nStatus atualizado com sucesso!\n");
            break;

        case 2:
            printf("\nVoltando ao painel de login...\n");
            return;

        default:
            printf("\nOpcao invalida!\n");
            break;
        }

    } while (1);
}

// ======================================================
// MAIN
// ======================================================

int main()
{
    char login[30];
    char senha[30];

    // USUÁRIOS

    strcpy(p[0].login, "Recepcionista");
    strcpy(p[0].senha, "recepcao123");

    strcpy(p[1].login, "Admin");
    strcpy(p[1].senha, "admin123");

    strcpy(p[2].login, "Limpeza");
    strcpy(p[2].senha, "limpeza123");

    while (1)
    {
        int tentativas = 0;
        int logado = 0;

        while (tentativas < 3 && logado == 0)
        {
            printf("\n===================================");
            printf("\n=== SISTEMA DE GESTAO HOTELEIRA ===");
            printf("\n===================================");

            printf("\nLogin: ");
            scanf("%s", login);

            printf("Senha: ");
            scanf("%s", senha);

            // RECEPCIONISTA
            if ((strcmp(login, p[0].login) == 0) &&
                (strcmp(senha, p[0].senha) == 0))
            {
                printf("\nBem-vindo(a), Recepcionista!\n");

                logado = 1;

                menuRecepcionista();
            }

            // ADMIN
            else if ((strcmp(login, p[1].login) == 0) &&
                     (strcmp(senha, p[1].senha) == 0))
            {
                printf("\nBem-vindo(a), Administrador!\n");

                logado = 1;

                menuAdministrador();
            }

            // LIMPEZA
            else if ((strcmp(login, p[2].login) == 0) &&
                     (strcmp(senha, p[2].senha) == 0))
            {
                printf("\nBem-vindo(a), Auxiliar de Limpeza!\n");

                logado = 1;

                menuAuxiliarDeLimpeza();
            }

            else
            {
                tentativas++;

                printf("\nErro: Credenciais incorretas.\n");

                if (tentativas < 3)
                {
                    printf("Voce tem mais %d tentativa(s).\n",
                           3 - tentativas);
                }
                else
                {
                    printf("\nAcesso bloqueado por seguranca!\n");
                }
            }
        }
    }

    return 0;
}