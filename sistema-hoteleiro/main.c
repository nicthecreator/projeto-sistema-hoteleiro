#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Essa biblioteca serve para usar os structs e manipulação de strings

// STRUCT DE LOGIN NO SISTEMA

typedef struct
{
    char login[30];
    char senha[30];
} pessoa;
pessoa p[5]; // diminuindo o nome da struct para "p" e o "[1]" é o máximo de pessoas com logins e senhas

// STRUCT DE HOSPEDES

typedef struct
{
    char nome[30];
    char dataDeNascimento[20];
    char cpf[20];
} hospede;
hospede hosped[20];

// ========== FUNÇÕES DA RECEPÇÃO ==========

// FUNÇÃO DE CADASTRO DE HOSPEDES
void cadastroDeHospedes()
{
    static int i = 0;
    int adicionarNovoHospede = 0;
    printf("\nCadastro de Hospedes selecionado.\n");
    printf("\nInsira o nome do hospede: ");
    scanf("%s", hosped[i].nome);
    printf("\nInsira a data de nascimento do hospede(00/00/0000): ");
    scanf("%s", hosped[i].dataDeNascimento);
    printf("\nInsira o CPF do hospede (000.000.000-00): ");
    scanf("%s", hosped[i].cpf);

    printf("\nInformacoes do hospede:\n");
    printf("Nome: %s\n", hosped[i].nome);
    printf("Data de Nascimento: %s\n", hosped[i].dataDeNascimento);
    printf("CPF: %s\n", hosped[i].cpf);

    printf("Deseja adicionar outro hospede? Sim (1) / Não (2): ");
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
            printf("Limite de hospedes atingido!\n");
            i = 0;
        }
    }
    else
    {
        i = 0;
    }
}

// FUNÇÃO DE VERIFICAR HOSPEDES CADASTRADOS

void verificarHospedesCadastrados()
{
    printf("\nHospedes Cadastrados:\n");
    for (int j = 0; j < 20; j++)
    {
        if (strlen(hosped[j].nome) > 0)
        { // Verifica se o nome do hospede não está vazio
            printf("Nome: %s\n", hosped[j].nome);
            printf("Data de Nascimento: %s\n", hosped[j].dataDeNascimento);
            printf("CPF: %s\n", hosped[j].cpf);
            printf("-------------------------\n");
        }
        else
        {
            printf("Fim da lista de hospedes cadastrados.\n");
            break; // Sai do loop se encontrar uma posição vazia, assumindo que os hóspedes são cadastrados sequencialmente
        }
    }
}

// MENU RECEPCIONISTA

void menuRecepcionista()
{
    do
    {
        int opcao;
        printf("\n==========================");
        printf("\n=== PAINEL DA RECEPCAO ===");
        printf("\n==========================\n");
        printf("1. Cadastro de Hospedes\n");
        printf("2. Verificar Hospedes Cadastrados\n");
        printf("3. Controle de Quartos\n");
        printf("4. Verificar Reservas Feitas\n");
        printf("5. Check-in\n");
        printf("6. Check Out\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            cadastroDeHospedes();
            break;

        case 2:
            verificarHospedesCadastrados();
            break;

        default:
            printf("Numero invalido, tente novamente.");
            break;
        }

    } while (1);
}

// MENU ADMINISTRADOR

void menuAdministrador()
{
    int opcao;
    printf("\n===============================");
    printf("\n=== PAINEL DO ADMINISTRADOR ===");
    printf("\n===============================");
    printf("\n1. ");
    printf("\n2. ");
    printf("\n3. ");
    printf("\n4. ");
    printf("\n5. ");
    printf("\nEscolha uma opcao: ");

    scanf("%d", &opcao);

    switch (opcao)
    {
    case 1:
        /* code */
        break;

    default:
        break;
    }
}

// MENU AUXILIAR DE LIMPEZA

void menuAuxiliarDeLimpeza()
{
    printf("\n=====================================");
    printf("\n=== PAINEL DO AUXILIAR DE LIMPEZA ===");
    printf("\n=====================================");
    printf("\n1. ");
    printf("\n2. ");
    printf("\n3. ");
    printf("\n4. ");
    printf("\n5. ");
    printf("Escolha uma opcao: ");
    int opcao;

    scanf("%d", &opcao);

    switch (opcao)
    {
    case 1:
        /* code */
        break;

    default:
        break;
    }
}

int main()
{

    // ====== SISTEMA DE LOGIN ======

    char login[30]; // responsável por armazenar a senha inserida pelo usuário
    char senha[30];

    int tentativas = 0;
    int logado = 0;

    //   ====== USUARIOS ======
    // Usuario da recepcao
    strcpy(p[0].login, "Recepcionista");
    strcpy(p[0].senha, "recepcao123");
    // Usuario da administracao
    strcpy(p[1].login, "Admin");
    strcpy(p[1].senha, "admin123");
    // Usuario da equipe de limpeza
    strcpy(p[2].login, "Limpeza");
    strcpy(p[2].senha, "limpeza123");

    while (tentativas < 3 && logado == 0)
    {
        printf("\n===================================");
        printf("\n=== SISTEMA DE GESTAO HOTELEIRA ===");
        printf("\n===================================");
        printf("\nLogin: ");
        scanf("%s", login); // armazenando os dados inseridos pelo usuário para o vetor login que está dentro da função main
        printf("\nSenha: ");
        scanf("%s", senha);

        if ((strcmp(login, p[0].login) == 0) && (strcmp(senha, p[0].senha) == 0))
        { // A função strcmp é responsável por comparar string com string
            // RECEPCIONISTA LOGADO
            printf("\nBem-vindo(a), Recepcionista!\n");
            logado = 1;
            menuRecepcionista();
        }
        else if ((strcmp(login, p[1].login) == 0) && (strcmp(senha, p[1].senha) == 0))
        {

            // ADMIN LOGADO
            printf("\nBem-vindo(a), Administrador!\n");
            logado = 1;
            menuAdministrador();
        }
        else if ((strcmp(login, p[2].login) == 0) && (strcmp(senha, p[2].senha) == 0))
        {

            // EQUIPE DE LIMPEZA LOGADO
            printf("\nBem-vindo(a), Auxiliar de limpeza!\n");
            logado = 1;
            menuAuxiliarDeLimpeza();
        }
        else
        {
            tentativas++;
            printf("\nErro: Credenciais incorretas.\n");
            if (tentativas < 3)
            {
                printf("Voce tem mais %d tentativa(s).\n", 3 - tentativas);
            }
            else
            {
                printf("Acesso bloqueado por seguranca!\n");
            }
        }
    }

    return 0;
}
