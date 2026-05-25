#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <time.h>

// DECLARAÇÃO GLOBAL

int totalreservas = 0;
int totalHospedes = 0;

// STRUCT DE LOGIN NO SISTEMA

typedef struct
{
    char login[30];
    char senha[30];
} pessoa;
pessoa p[5];

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
    char tipo[20];
    char status[20];

} quarto;
quarto quartos[30];

// STRUCT DE RESERVA

typedef struct
{
    int idReserva;
    char cpfHospede[20];
    int numeroQuarto;
    char dataCheckIn[11];
    char dataCheckOut[11];
    int status; 
} reserva;
reserva reservas[50];

//==================== FUNÇÕES ====================

// FUNÇÕES DO SISTEMA


// FUNÇÃO DE LOGIN

void sistemaDeLogin()
{
    // Declaração da Função de Login
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
                printf("Acesso bloqueado por seguranca! Encerrando o Sistema...\n");
                exit(0);
            }
        }
    }
}

// FUNÇÃO PARA INICIALIZAR OS QUARTOS

void iniciarQuartos()
{
    for (int i = 0; i < 30; i++)
    {
        quartos[i].numero = i + 1;

        // Todos começam disponiveis
        strcpy(quartos[i].status, "DISPONIVEL");

        // Define o tipo do quarto
        if (i < 10)
        {
            strcpy(quartos[i].tipo, "Solteiro");
        }
        else if (i < 20)
        {
            strcpy(quartos[i].tipo, "Duplo");
        }
        else
        {
            strcpy(quartos[i].tipo, "Suite Premium");
        }
    }
}

// FUNÇÕES DE MANIPULAÇÃO DE ARQUIVO (PERSISTÊNCIA)

    // Função para SALVAR os hóspedes no arquivo
void salvarHospedes() {
    // Abre (ou cria) um arquivo chamado "hospedes.dat" no modo "wb" (Write Binary - Escrita Binária)
    FILE *arquivo = fopen("hospedes.dat", "wb"); 
    
    if (arquivo != NULL) {
        // Escreve os dados do vetor 'hosped' no arquivo
        // fwrite(de onde vem, tamanho de cada item, quantos itens, para onde vai)
        fwrite(hosped, sizeof(hospede), totalHospedes, arquivo);
        fclose(arquivo); // Sempre feche o arquivo após usar!
    } else {
        printf("\nErro ao tentar salvar os dados dos hospedes no disco!\n");
    }
}

    // Função para CARREGAR os hóspedes do arquivo quando o programa iniciar
void carregarHospedes() {
    // Abre o arquivo no modo "rb" (Read Binary - Leitura Binária)
    FILE *arquivo = fopen("hospedes.dat", "rb"); 
    
    if (arquivo != NULL) {
        // Lê os dados do arquivo e joga direto para o vetor 'hosped'
        // A função fread retorna a quantidade de itens que ela conseguiu ler
        totalHospedes = fread(hosped, sizeof(hospede), 20, arquivo);
        fclose(arquivo);
        printf("\n[SISTEMA] %d hospede(s) carregado(s) do banco de dados com sucesso!\n", totalHospedes);
    } else {
        // Se o arquivo não existir (primeira vez rodando), ele apenas avisa
        printf("\n[SISTEMA] Nenhum banco de dados de hospedes encontrado. Um novo sera criado ao cadastrar.\n");
    }
}

// ========== FUNÇÕES DA RECEPÇÃO ==========

// Função para validar o formato do CPF (XXX.XXX.XXX-XX)
int validarCPF(char *cpf)
{
    if (strlen(cpf) != 14)
        return 0; // Verifica o tamanho exato
    if (cpf[3] != '.' || cpf[7] != '.' || cpf[11] != '-')
        return 0; // Verifica os pontos e traço

    // Verifica se os outros caracteres são números
    for (int i = 0; i < 14; i++)
    {
        if (i != 3 && i != 7 && i != 11)
        {
            if (!isdigit(cpf[i]))
                return 0;
        }
    }
    return 1; // CPF válido no formato
}

// Função para validar formato da data (exige as barras no formato DD/MM/AAAA)
int validarDataNascimento(char *data)
{
    // Verifica se tem exatos 10 caracteres
    if (strlen(data) != 10)
        return 0;

    // Verifica se as barras estão nas posições corretas
    if (data[2] != '/' || data[5] != '/')
        return 0;

    return 1; // Tem as barras e o tamanho certo
}

// FUNÇÃO DE CADASTRO DE HOSPEDES
void cadastroDeHospedes()
{
    int adicionarNovoHospede;
    do
    {
        if (totalHospedes >= 20)
        {
            printf("Limite de hospedes atingido!\n");
            break;
        }

        printf("\nCadastro de Hospedes selecionado.\n");

        printf("\nInsira o nome do hospede: ");
        scanf(" %60[^\n]", hosped[totalHospedes].nome);

        // VALIDAÇÃO DA DATA DE NASCIMENTO
        int dataValida = 0;
        do
        {
            printf("\nInsira a data de nascimento (DD/MM/AAAA): ");
            scanf("%s", hosped[totalHospedes].dataDeNascimento);

            if (validarDataNascimento(hosped[totalHospedes].dataDeNascimento))
            {
                dataValida = 1;
            }
            else
            {
                printf("Erro: Formato inválido. Não esqueça de usar as barras (Ex: 01/01/2000).\n");
            }
        } while (!dataValida);

        // VALIDAÇÃO DO CPF
        int cpfValido = 0;
        do
        {
            printf("\nInsira o CPF (Formato: XXX.XXX.XXX-XX): ");
            scanf("%s", hosped[totalHospedes].cpf);

            if (validarCPF(hosped[totalHospedes].cpf))
            {
                cpfValido = 1;
            }
            else
            {
                printf("Erro: CPF Inválido. Não esqueça dos pontos e do traço!\n");
            }
        } while (!cpfValido);

        totalHospedes++;
        
        // SALVA OS DADOS NO ARQUIVO LOGO APÓS O CADASTRO!
        salvarHospedes();

        printf("\nDeseja adicionar outro hospede? Sim (1) / Nao (2): ");
        scanf("%d", &adicionarNovoHospede);
        
    } while (adicionarNovoHospede == 1);
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
            printf("\nTotal de hospedes cadastrados: %d\n", totalHospedes);
            printf("Fim da lista de hospedes cadastrados.\n");
            break; // Sai do loop se encontrar uma posição vazia, assumindo que os hóspedes são cadastrados sequencialmente
        }
    }
    
}

// FUNÇÃO DE CONTROLE DE QUARTOS

void controleDeQuartos()
{
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
        listarQuartos();
    }
    else if (opcao == 2)
    {
    }
    else if (opcao == 3)
    {
        atualizarStatusQuarto();
    }
    else
    {
        printf("Quarto invalido.\n");
    }
}

// Função para validar se a data está no formato DD/MM/AAAA e é igual ou maior que hoje
int validarDataFutura(char *data)
{
    if (strlen(data) != 10)
        return 0;
    if (data[2] != '/' || data[5] != '/')
        return 0;

    int dia, mes, ano;
    if (sscanf(data, "%d/%d/%d", &dia, &mes, &ano) != 3)
        return 0;

    // Pega a data atual do computador
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int diaAtual = tm.tm_mday;
    int mesAtual = tm.tm_mon + 1;
    int anoAtual = tm.tm_year + 1900;

    // Lógica para saber se a data é igual ou posterior a hoje
    if (ano > anoAtual)
        return 1;
    if (ano == anoAtual && mes > mesAtual)
        return 1;
    if (ano == anoAtual && mes == mesAtual && dia >= diaAtual)
        return 1;

    return 0; // Retorna 0 se a data for no passado ou inválida
}

// FUNÇÃO DE FAZER RESERVA
// FUNÇÃO DE FAZER RESERVA
void fazerReserva()
{
    if (totalreservas >= 50)
    {
        printf("Limite de reservas atingido!\n");
        return;
    }
    
    reserva nova;
    nova.idReserva = totalreservas + 1;
    printf("\n--- NOVA RESERVA ---\n");
    
    // VALIDAÇÃO DO CPF (Exige pontos e traço)
    int cpfValido = 0;
    do {
        printf("CPF do hospede (XXX.XXX.XXX-XX): ");
        scanf("%s", nova.cpfHospede);
        
        if (validarCPF(nova.cpfHospede)) {
            cpfValido = 1;
        } else {
            printf("Erro: CPF Invalido. Nao esqueca dos pontos e do traco!\n");
        }
    } while (!cpfValido);

    // VERIFICAÇÃO SE O HÓSPEDE EXISTE NO SISTEMA
    int hospedeCadastrado = 0;
    for (int i = 0; i < totalHospedes; i++) {
        if (strcmp(hosped[i].cpf, nova.cpfHospede) == 0) {
            hospedeCadastrado = 1; 
            printf("Hospede %s encontrado!\n", hosped[i].nome);
            break; 
        }
    }

    if (hospedeCadastrado == 0) {
        printf("Erro: Hospede nao encontrado! Por favor, cadastre o hospede antes de fazer a reserva.\n");
        return; 
    }

    // =======================================================
    // NOVIDADE: SELEÇÃO DO QUARTO E VERIFICAÇÃO DE DISPONIBILIDADE
    // =======================================================
    printf("\nNumero do quarto desejado: ");
    scanf("%d", &nova.numeroQuarto);
    
    // Bloqueia se o número for inválido ou se o status for DIFERENTE (!= 0) de DISPONIVEL
    if (nova.numeroQuarto < 1 || nova.numeroQuarto > 30 || strcmp(quartos[nova.numeroQuarto - 1].status, "DISPONIVEL") != 0)
    {
        // Se cair aqui, mostra pro usuário qual é o status real do quarto
        printf("Erro: Quarto indisponivel para reserva. Status atual: %s\n", quartos[nova.numeroQuarto - 1].status);
        return;
    }
    // =======================================================
    
    // VALIDAÇÃO DA DATA DE CHECK-IN (Exige barras e data >= hoje)
    int dataInValida = 0;
    do {
        printf("Data de check-in (DD/MM/AAAA) [Atual ou Futura]: ");
        scanf("%s", nova.dataCheckIn);
        
        if (validarDataFutura(nova.dataCheckIn)) {
            dataInValida = 1;
        } else {
            printf("Erro: Formato invalido ou data no passado. Use DD/MM/AAAA e digite uma data valida.\n");
        }
    } while (!dataInValida);    

    printf("Data de check-out (DD/MM/AAAA): ");
    scanf("%s", nova.dataCheckOut);
    
    nova.status = 0; // reservado
    reservas[totalreservas] = nova;
    totalreservas++;
    
    printf("\nReserva criada com sucesso! ID: %d\n", nova.idReserva);
}

// FUNÇÃO DE VERIFICAR RESERVAS FEITAS

void verificarReservas()
{
    printf("\n--- RESERVAS ATIVAS (status reservado) ---\n");
    int encontrou = 0;
    for (int i = 0; i < totalreservas; i++)
    {
        if (reservas[i].status == 0)
        {
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

void fazerCheckIn()
{
    char cpf[20];
    int idReserva;
    printf("\n--- CHECK-IN ---\n");

    // VALIDAÇÃO DO CPF
        int cpfValido = 0;
        do
        {
            printf("\nInsira o CPF (Formato: XXX.XXX.XXX-XX): ");
            scanf("%s", cpf);

            if (validarCPF(cpf))
            {
                cpfValido = 1;
            }
            else
            {
                printf("Erro: CPF Inválido. Não esqueça dos pontos e do traço!\n");
            }
        } while (!cpfValido);


    printf("Digite o ID da reserva: ");
    scanf("%d", &idReserva);


    for (int i = 0; i < totalreservas; i++)
    {
        if (reservas[i].status == 0 &&
            strcmp(reservas[i].cpfHospede, cpf) == 0 &&
            reservas[i].idReserva == idReserva)
        {

            int numQuarto = reservas[i].numeroQuarto;
            if (strcmp(quartos[numQuarto - 1].status, "DISPONIVEL") == 0)
            {
                strcpy(quartos[numQuarto - 1].status, "OCUPADO");
                reservas[i].status = 1; // check-in realizado
                printf("Check-in realizado com sucesso! Quarto %d agora esta ocupado.\n", numQuarto);
            }
            else
            {
                printf("Erro: Quarto ja esta ocupado!\n");
            }
            return;
        }
    }
    printf("Reserva nao encontrada ou ja finalizada.\n");
}

// FUNÇÃO DE CHECK-OUT

void fazerCheckOut()
{
    int numQuarto;
    printf("\n--- CHECK-OUT ---\n");
    printf("Numero do quarto: ");
    scanf("%d", &numQuarto);
    if (numQuarto < 1 || numQuarto > 30)
    {
        printf("Quarto invalido.\n");
        return;
    }
    if (strcmp(quartos[numQuarto - 1].status, "OCUPADO") == 0)
    {
        strcpy(quartos[numQuarto - 1].status, "DISPONIVEL");
        // Atualiza a reserva correspondente para status 2 (check-out)
        for (int i = 0; i < totalreservas; i++)
        {
            if (reservas[i].numeroQuarto == numQuarto && reservas[i].status == 1)
            {
                reservas[i].status = 2;
                break;
            }
        }
        printf("Check-out realizado. Quarto %d agora esta disponivel.\n", numQuarto);
    }
    else
    {
        printf("Quarto ja esta disponivel (não ha hospede).\n");
    }
}

// ========== FUNÇÕES DA ADMINISTRAÇÃO ==========


// FUNÇÃO PARA BUSCAR HÓSPEDE POR CPF

void buscarHospedeCPF()
{
    char cpfBusca[20];

    // Variável para saber se encontrou o hóspede
    int encontrado = 0;

    printf("\n====================================");
    printf("\n====== BUSCAR HOSPEDE POR CPF ======");
    printf("\n====================================");

    printf("\nDigite o CPF do hospede: ");
    scanf("%s", cpfBusca);

    // Percorre todos os hóspedes cadastrados
    for (int i = 0; i < totalHospedes; i++)
    {
        // Compara o CPF digitado com o CPF salvo
        if (strcmp(hosped[i].cpf, cpfBusca) == 0)
        {
            printf("\n\n===== HOSPEDE ENCONTRADO =====");

            printf("\nNome: %s", hosped[i].nome);
            printf("\nData de Nascimento: %s", hosped[i].dataDeNascimento);
            printf("\nCPF: %s\n", hosped[i].cpf);

            encontrado = 1;

            break;
        }
    }

    // Caso não encontre
    if (encontrado == 0)
    {
        printf("\nHospede nao encontrado.\n");
    }
}

// FUNÇÃO PARA REMOVER HÓSPEDE

void removerHospede()
{
    char cpfRemover[20];

    // Variável de controle
    int encontrado = 0;

    printf("\n====================================");
    printf("\n========= REMOVER HOSPEDE ==========");
    printf("\n====================================");

    printf("\nDigite o CPF do hospede: ");
    scanf("%s", cpfRemover);

    // Procura o hóspede
    for (int i = 0; i < totalHospedes; i++)
    {
        // Se encontrar o CPF
        if (strcmp(hosped[i].cpf, cpfRemover) == 0)
        {
            encontrado = 1;

            // Move os próximos hóspedes para trás
            for (int j = i; j < totalHospedes - 1; j++)
            {
                hosped[j] = hosped[j + 1];
            }

            // Diminui a quantidade de hóspedes
            totalHospedes--;

            // Salva no arquivo atualizado
            salvarHospedes();

            printf("\nHospede removido com sucesso!\n");

            break;
        }
    }

    // Caso não encontre
    if (encontrado == 0)
    {
        printf("\nHospede nao encontrado.\n");
    }
}


// ========== FUNÇÕES DA AUXILIAR DE LIMPEZA ==========

// FUNÇÃO PARA LISTAR QUARTOS

void listarQuartos()
{
    printf("\n======= LISTA DE QUARTOS =======\n");

    for (int i = 0; i < 30; i++)
    {
        char *cor = "\033[0m"; // Começa com a cor padrão (reset)

        // Verifica qual é o status para definir a cor correta
        if (strcmp(quartos[i].status, "DISPONIVEL") == 0)
        {
            cor = "\033[32m"; // Verde
        }
        else if (strcmp(quartos[i].status, "OCUPADO") == 0)
        {
            cor = "\033[31m"; // Vermelho
        }
        else if (strcmp(quartos[i].status, "EM MANUTENÇÃO") == 0)
        {
            cor = "\033[34m"; // Azul
        }
        else if (strcmp(quartos[i].status, "EM LIMPEZA") == 0)
        {
            cor = "\033[33m"; // Amarelo
        }

        // O %s antes do status injeta a cor, e o \033[0m no final reseta a cor do terminal
        printf("Quarto %d - %s - %s%s\033[0m\n",
            quartos[i].numero,
            quartos[i].tipo,
            cor,
            quartos[i].status);
    }
}

// FUNÇÃO PARA ATUALIZAR STATUS

void atualizarStatusQuarto()
{
    int numero;
    int opcao;

    printf("\nNumero do quarto: (1 a 10 Solteiros, 11 a 20 Duplos, 21 a 30 Suites): ");
    scanf("%d", &numero);

    // Verifica se o quarto existe
    if (numero < 1 || numero > 30)
    {
        printf("Quarto invalido.\n");
        return;
    }

    printf("\n1. DISPONIVEL");
    printf("\n2. EM MANUTENÇÃO");
    printf("\n3. OCUPADO");
    printf("\n4. EM LIMPEZA");
    printf("\nEscolha: ");

    scanf("%d", &opcao);

    // Atualiza o status
    if (opcao == 1)
    {
        strcpy(quartos[numero - 1].status, "DISPONIVEL");
    }
    else if (opcao == 2)
    {
        strcpy(quartos[numero - 1].status, "EM MANUTENÇÃO");
    }
    else if (opcao == 3)
    {
        strcpy(quartos[numero - 1].status, "OCUPADO");
    }
    else if (opcao == 4)
    {
        strcpy(quartos[numero - 1].status, "EM LIMPEZA");
    }
    else
    {
        printf("Opcao invalida.\n");
    }

    printf("\nStatus atualizado com sucesso!\n");
}

// ========== FUNÇÕES DO HÓSPEDE ==========

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
        printf("\n8. Sair");
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
        case 7:
            fazerCheckOut();
            break;
        case 8:
            return;
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
        printf("\n4. Verificar total de Hospedes Cadastrados");
        printf("\n5. Sair");
        printf("\nEscolha uma opcao: ");

        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            verificarHospedesCadastrados();
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
            return;

        default:
            printf("Numero invalido, tente novamente.\n");
            break;
        }

    } while (1);
}

// MENU AUXILIAR DE LIMPEZA

void menuAuxiliarDeLimpeza()
{
    int opcao;
    do
    {
        printf("\n=====================================");
        printf("\n=== PAINEL DO AUXILIAR DE LIMPEZA ===");
        printf("\n=====================================\n");
        printf("1. Listar quartos\n");
        printf("2. Atualizar status do quarto\n");
        printf("3. Sair\n");
        printf("\nEscolha uma opcao: ");

        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            listarQuartos();
            break;
        case 2:
            atualizarStatusQuarto();
            break;
        case 3:
            return;
        default:
            printf("Numero invalido, tente novamente.\n");
            break;
        }
    } while (1);
}

// MENU HOSPEDE

void menuHospede()
{
    printf("\n=====================================");
    printf("\n========= PAINEL DO HOSPEDE =========");
    printf("\n=====================================");
    printf("\n1. Consultar disponibilidade");
    printf("\n2. Realizar Reserva");
    printf("\n3. Realizar Pagamento (Ver boletos emitidos)");
    printf("\n4. Visualizar notas fiscais");
    printf("\n5. Sair");
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
        return;

    default:
        break;
    }
}

// ========== FUNÇÃO PRINCIPAL (MAIN) ==========

int main()
{
    // Essa função é para conZigurar o console para usar a codificação UTF-8
    SetConsoleOutputCP(65001);

    // Chamando a função para carregar os hóspedes do arquivo quando o programa iniciar, para que os dados sejam persistidos mesmo após fechar o programa
    carregarHospedes();

    // Chamando a função para inicializar os quartos do hotel, para que eles já estejam prontos para serem usados quando o usuário fizer login
    iniciarQuartos();

    // Puxando a função do SISTEMA DE LOGIN para o início do programa, para que o usuário seja direcionado para a tela de login assim que abrir o programa
    sistemaDeLogin();

    while (1)
    {
        sistemaDeLogin(); // Loop infinito pra manter o programa vivo
    }

    return 0;
}