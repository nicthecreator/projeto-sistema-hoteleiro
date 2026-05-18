#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // Essa biblioteca serve para usar os structs e manipulação de strings
#include <windows.h> // Essa biblioteca é para usar a função Sleep, que é responsável por criar uma pausa no programa, deixando a experiência do usuário mais fluida

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
    char nome[60];
    char dataDeNascimento[20];
    char cpf[20];
} hospede;
hospede hosped[20];

// STRUCT DE QUARTO

typedef struct

{
    int numero;
    char tipo[20]; // "solteiro", "casal", "suite"
    float preco;
    int disponivel; // 1 = livre, 0 = ocupado;

} quarto;
quarto quartos[30];

// STRUCT DE RESERVA

typedef struct {
    int idReserva;
    char cpfHospede[20];
    int numeroQuarto;
    char dataCheckIn[11];
    char dataCheckOut[11];
    int status;        // 0 = reservado, 1 = check‑in feito, 2 = check‑out feito
} reserva;
reserva reservas[50];


// DECLARAÇÃO GLOBAL
int totalreservas = 0;

//==================== FUNÇÕES ====================

// ========== FUNÇÕES DA RECEPÇÃO ==========

// FUNÇÃO DE CADASTRO DE HOSPEDES
void cadastroDeHospedes()
{
    static int i = 0;
    int adicionarNovoHospede = 0;
    printf("\nCadastro de Hospedes selecionado.\n");
    printf("\nInsira o nome do hospede: ");
    scanf(" %60[^\n]", hosped[i].nome);
    printf("\nInsira a data de nascimento: ");
    scanf("%s", hosped[i].dataDeNascimento);
    printf("\nInsira o CPF: ");
    scanf("%s", hosped[i].cpf);

    printf("\nInformacoes do hospede:\n");
    printf("Nome: %s\n", hosped[i].nome);
    printf("Data de Nascimento: %s\n", hosped[i].dataDeNascimento);
    printf("CPF: %s\n", hosped[i].cpf);

    printf("\nDeseja adicionar outro hospede? Sim (1) / Não (2): ");
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
    printf("\nHospedes Cadastrados:\n\n");
    printf("-------------------------\n");
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

// FUNÇÃO DE CONTROLE DE QUARTOS

void controleDeQuartos()
{
    for (int i = 0; i < 30; i++) // inicializa os 30 quartos com números, tipos e preços
{
    quartos[i].numero = i + 1;
    quartos[i].disponivel = 1; // todos livres no início
    if (i < 10)
    {
        strcpy(quartos[i].tipo, "Solteiro");
        quartos[i].preco = 120.0;
    }
    else if (i < 20)
    {
        strcpy(quartos[i].tipo, "Duplo");
        quartos[i].preco = 180.0;
    }
    else
    {
        strcpy(quartos[i].tipo, "Suite");
        quartos[i].preco = 350.0;
    }
}

    int opcao;
    printf("\n===========================");
    printf("\n=== CONTROLE DE QUARTOS ===");
    printf("\n===========================\n");
    printf("1. Listar todos os quartos\n");
    printf("2. Ver apenas quartos disponiveis\n");
    printf("3. Alterar disponibilidade manualmente\n");
    printf("Escolha: ");
    scanf("%d", &opcao);

    if (opcao == 1)
    {
        for (int i = 0; i < 30; i++)
        {
            printf("Quarto %d - %s - R$%.2f - %s\n",
                quartos[i].numero,
                quartos[i].tipo,
                quartos[i].preco,
                quartos[i].disponivel ? "\033[0;32mDISPONIVEL\033[0m\n" : "OCUPADO");
        }
    }
    else if (opcao == 2)
    {
        for (int i = 0; i < 30; i++)
        {
            if (quartos[i].disponivel)
                printf("Quarto %d - %s - R$%.2f\n",
                    quartos[i].numero, quartos[i].tipo, quartos[i].preco);
        }
    }
    else if (opcao == 3)
    {
        int num, disp;
        printf("Numero do quarto: ");
        scanf("%d", &num);
        if (num >= 1 && num <= 30)
        {
            printf("Novo status (1=disponivel, 0=ocupado): ");
            scanf("%d", &disp);
            quartos[num - 1].disponivel = disp;
            printf("Status alterado.\n");
        }
        else
        {
            printf("Quarto invalido.\n");
        }
    }
} 

// FUNÇÃO DE VERIFICAR RESERVAS FEITAS

void fazerReserva() {
    if (totalreservas >= 50) {
        printf("Limite de reservas atingido!\n");
        return;
    }
    reserva nova;
    nova.idReserva = totalreservas + 1;
    printf("\n--- NOVA RESERVA ---\n");
    printf("CPF do hospede: ");
    scanf("%s", nova.cpfHospede);
    // Verifica se o CPF existe em hosped[] (opcional)
    printf("Numero do quarto desejado: ");
    scanf("%d", &nova.numeroQuarto);
    if (nova.numeroQuarto < 1 || nova.numeroQuarto > 30 || quartos[nova.numeroQuarto-1].disponivel == 0) {
        printf("Quarto invalido ou ocupado. Reserva nao concluida.\n");
        return;
    }
    printf("Data de check-in (DD/MM/AAAA): ");
    scanf("%s", nova.dataCheckIn);
    printf("Data de check-out (DD/MM/AAAA): ");
    scanf("%s", nova.dataCheckOut);
    nova.status = 0;  // reservado
    reservas[totalreservas] = nova;
    totalreservas++;
    printf("Reserva criada com sucesso! ID: %d\n", nova.idReserva);
}

// FUNÇÃO DE VERIFICAR RESERVAS FEITAS

void verificarReservas() {
    printf("\n--- RESERVAS ATIVAS (status reservado) ---\n");
    int encontrou = 0;
    for (int i = 0; i < totalreservas; i++) {
        if (reservas[i].status == 0) {
            printf("Reserva ID: %d\n", reservas[i].idReserva);
            printf("CPF Hospede: %s\n", reservas[i].cpfHospede);
            printf("Quarto: %d\n", reservas[i].numeroQuarto);
            printf("Check-in: %s   Check-out: %s\n", reservas[i].dataCheckIn, reservas[i].dataCheckOut);
            printf("------------------------\n");
            encontrou = 1;
        }
    }
    if (!encontrou)
        printf("Nenhuma reserva ativa.\n");
}

// FUNÇÃO DE CHECK-IN

void fazerCheckIn() {
    char cpf[20];
    int idReserva;
    printf("\n--- CHECK-IN ---\n");
    printf("Digite o CPF do hospede: ");
    scanf("%s", cpf);
    printf("Digite o ID da reserva: ");
    scanf("%d", &idReserva);

    for (int i = 0; i < totalreservas; i++) {
        if (reservas[i].status == 0 && 
            strcmp(reservas[i].cpfHospede, cpf) == 0 && 
            reservas[i].idReserva == idReserva) {
            
            int numQuarto = reservas[i].numeroQuarto;
            if (quartos[numQuarto-1].disponivel == 1) {
                quartos[numQuarto-1].disponivel = 0;
                reservas[i].status = 1;   // check-in realizado
                printf("Check-in realizado com sucesso! Quarto %d agora esta ocupado.\n", numQuarto);
            } else {
                printf("Erro: Quarto ja esta ocupado!\n");
            }
            return;
        }
    }
    printf("Reserva nao encontrada ou ja finalizada.\n");
}

// FUNÇÃO DE CHECK-OUT

void fazerCheckOut() {
    int numQuarto;
    printf("\n--- CHECK-OUT ---\n");
    printf("Numero do quarto: ");
    scanf("%d", &numQuarto);
    if (numQuarto < 1 || numQuarto > 30) {
        printf("Quarto invalido.\n");
        return;
    }
    if (quartos[numQuarto-1].disponivel == 0) {
        quartos[numQuarto-1].disponivel = 1;
        // Atualiza a reserva correspondente para status 2 (check-out)
        for (int i = 0; i < totalreservas; i++) {
            if (reservas[i].numeroQuarto == numQuarto && reservas[i].status == 1) {
                reservas[i].status = 2;
                break;
            }
        }
        printf("Check-out realizado. Quarto %d agora esta disponivel.\n", numQuarto);
    } else {
        printf("Quarto ja esta disponivel (nao ha hospede).\n");
    }
}



// ==================== MENUS ====================

// MENU RECEPCIONISTA

void menuRecepcionista()
{
    do
    {
        int opcao;
        printf("\n==========================");
        printf("\n=== PAINEL DA RECEPCAO ===");
        printf("\n==========================");
        printf("\n1. Cadastro de Hospedes");
        printf("\n2. Verificar Hospedes Cadastrados");
        printf("\n3. Controle de Quartos");
        printf("\n4. Fazer Reserva");
        printf("\n5. Verificar Reservas Feitas");
        printf("\n6. Check-in");
        printf("\n7. Check Out");
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
            controleDeQuartos();
            break;
        case 4:
            fazerReserva();
            break;
        case 5:
            verificarReservas();
            break;
        case 6:
            fazerCheckIn();
            break;
        case 7:   // opção extra para criar reservas
            fazerCheckOut();
            break;
        default:
            printf("Numero invalido, tente novamente.\n");
            break;
        }

    } while (1);
}

// MENU ADMINISTRADOR

void menuAdministrador()
{
    int opcao;

    do
    {
        printf("\n===============================");
        printf("\n=== PAINEL DO ADMINISTRADOR ===");
        printf("\n===============================");
        printf("\n1. Relatorio de Hospedes");
        printf("\n2. Buscar Hospede por CPF");
        printf("\n3. Remover Hospede");
        printf("\n4. Verificar Hospedes");
        printf("\n5. Voltar ao Login");
        printf("\nEscolha uma opcao: ");

        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            RelatorioHospedes();
            break;

        case 2:
            buscarHospedeCPF();
            break;

        case 3:
            removerHospede();
            break;

        case 4:
            verificarHospedesCadastrados();
            break;

        case 5:
            printf("\nVoltando ao painel de login...\n");
            return;

        default:
            printf("\nOpcao invalida!\n");
            break;
        }

    } while (1);
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
    printf("\nEscolha uma opcao: ");
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

// MENU HOSPEDE

void menuHospede()
{
    printf("\n=====================================");
    printf("\n========= PAINEL DO HOSPEDE =========");
    printf("\n=====================================");
    printf("\n1. Consultar disponibilidade");
    printf("\n2. Realizar Reserva");
    printf("\n3. Check-in");
    printf("\n4. Check-out");
    printf("\n5. Realizar Pagamento (Ver boletos emitidos)");
    printf("\n6. Visualizar notas fiscais");
    printf("\nEscolha uma opcao: ");
    int opcao;

    scanf("%d", &opcao);

    switch (opcao)
    {
    case 1:
        /* code */
        break;
    case 2:
        /* code */
        break;
    case 3:
        /* code */
        break;
    case 4:
        /* code */
        break;
    case 5:
        /* code */
        break;

    default:
        break;
    }
}

// ========== FUNÇÃO PRINCIPAL (MAIN) ==========

int main()
{
    SetConsoleOutputCP(65001); // Essa função é para configurar o console para usar a codificação UTF-8, permitindo que caracteres acentuados sejam exibidos corretamente no console do Windows.

    // ====== SISTEMA DE LOGIN ======

    char login[30]; // responsável por armazenar a senha inserida pelo usuário
    char senha[30];

    int tentativas = 0;
    int logado = 0;

    //   ====== USUARIOS ======
    // Usuario da recepcao
    strcpy(p[0].login, "r");
    strcpy(p[0].senha, "r");
    // Usuario da administracao
    strcpy(p[1].login, "a");
    strcpy(p[1].senha, "a");
    // Usuario da equipe de limpeza
    strcpy(p[2].login, "l");
    strcpy(p[2].senha, "l");
    // Usuario Hospede
    strcpy(p[3].login, "h");
    strcpy(p[3].senha, "h");

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
        else if ((strcmp(login, p[3].login) == 0) && (strcmp(senha, p[3].senha) == 0))
        {

            // HOSPEDE LOGADO
            printf("\nBem-vindo(a), Hospede!\n");
            logado = 1;
            menuHospede();
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