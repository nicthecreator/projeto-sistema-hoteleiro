#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <time.h>

// DECLARAÇÃO GLOBAL

int totalreservas = 0;
int totalHospedes = 0;
int totalBoletos = 0;
int totalNotas = 0;

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

// STRUCT DE BOLETO
typedef struct
{
    int idBoleto;
    int idReserva;
    float valor;
    char dataVencimento[11];
    char status[20]; // "PENDENTE", "PAGO", "VENCIDO"
    char codigoBarras[50];
} boleto;
boleto boletos[100];

// STRUCT DE NOTA FISCAL
typedef struct
{
    int idNotaFiscal;
    int idReserva;
    char cpfHospede[20];
    char nomeHospede[60];
    float valorTotal;
    char dataEmissao[11];
    char itens[200];
} notaFiscal;
notaFiscal notasFiscais[100];

//==================== PROTOTIPOS ====================
void sistemaDeLogin();
void iniciarQuartos();
void salvarHospedes();
void carregarHospedes();
void salvarQuartos();
void carregarQuartos();
void salvarReservas();
void carregarReservas();
int validarCPF(char *cpf);
int validarDataNascimento(char *data);
int validarDataFutura(char *data);
void cadastroDeHospedes();
void verificarHospedesCadastrados();
void controleDeQuartos();
void listarQuartosDisponiveis();
void listarQuartos();
void atualizarStatusQuarto();
void fazerReserva();
void verificarReservas();
void fazerCheckIn();
void fazerCheckOut();
void buscarHospedeCPF();
void removerHospede();
void menuRecepcionista();
void menuAdministrador();
void menuAuxiliarDeLimpeza();
void menuHospede();

// Novos prototipos
void gerarBoleto(int idReserva, float valor, char *dataVencimento);
void realizarPagamento();
void verBoletosEmitidos();
void verNotasFiscais();
void fazerReservaComBoleto();

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

// FUNÇÕES PARA SALVAR E CARREGAR DADOS DOS HÓSPEDES, QUARTOS E RESERVAS

    // SALVAR E CARREGAR HÓSPEDES
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

// SALVAR E CARREGAR QUARTOS
void salvarQuartos() {
    FILE *arquivo = fopen("quartos.dat", "wb"); 
    if (arquivo != NULL) {
        // Salva os 30 quartos de uma vez
        fwrite(quartos, sizeof(quarto), 30, arquivo);
        fclose(arquivo);
    } else {
        printf("\nErro ao salvar os quartos no disco!\n");
    }
}

void carregarQuartos() {
    FILE *arquivo = fopen("quartos.dat", "rb"); 
    if (arquivo != NULL) {
        fread(quartos, sizeof(quarto), 30, arquivo);
        fclose(arquivo);
        printf("[SISTEMA] Status dos quartos carregado com sucesso!\n");
    } else {
        // Se o arquivo não existir (primeira vez), inicializa e já salva
        printf("[SISTEMA] Criando novo banco de dados para os quartos.\n");
        iniciarQuartos(); 
        salvarQuartos();
    }
}

// SALVAR E CARREGAR RESERVAS
void salvarReservas() {
    FILE *arquivo = fopen("reservas.dat", "wb"); 
    if (arquivo != NULL) {
        // Salva com base no 'totalreservas'
        fwrite(reservas, sizeof(reserva), totalreservas, arquivo);
        fclose(arquivo);
    } else {
        printf("\nErro ao salvar as reservas no disco!\n");
    }
}

void carregarReservas() {
    FILE *arquivo = fopen("reservas.dat", "rb"); 
    if (arquivo != NULL) {
        totalreservas = fread(reservas, sizeof(reserva), 50, arquivo);
        fclose(arquivo);
        printf("[SISTEMA] %d reserva(s) carregada(s) com sucesso!\n", totalreservas);
    } else {
        printf("[SISTEMA] Nenhum banco de dados de reservas encontrado.\n");
    }
}

// SALVAR E CARREGAR BOLETOS
void salvarBoletos() {
    FILE *arquivo = fopen("boletos.dat", "wb");
    if (arquivo != NULL) {
        fwrite(boletos, sizeof(boleto), totalBoletos, arquivo);
        fclose(arquivo);
    }
}

void carregarBoletos() {
    FILE *arquivo = fopen("boletos.dat", "rb");
    if (arquivo != NULL) {
        totalBoletos = fread(boletos, sizeof(boleto), 100, arquivo);
        fclose(arquivo);
        printf("[SISTEMA] %d boleto(s) carregado(s) com sucesso!\n", totalBoletos);
    }
}

// SALVAR E CARREGAR NOTAS FISCAIS
void salvarNotasFiscais() {
    FILE *arquivo = fopen("notasfiscais.dat", "wb");
    if (arquivo != NULL) {
        fwrite(notasFiscais, sizeof(notaFiscal), totalNotas, arquivo);
        fclose(arquivo);
    }
}

void carregarNotasFiscais() {
    FILE *arquivo = fopen("notasfiscais.dat", "rb");
    if (arquivo != NULL) {
        totalNotas = fread(notasFiscais, sizeof(notaFiscal), 100, arquivo);
        fclose(arquivo);
        printf("[SISTEMA] %d nota(s) fiscal(is) carregada(s) com sucesso!\n", totalNotas);
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

    // Verifica se a lista está vazia primeiro
    if (totalHospedes == 0) {
        printf("Nenhum hospede cadastrado no momento.\n");
        return;
    }

    // O loop agora roda estritamente até o número de hóspedes ativos
    for (int j = 0; j < totalHospedes; j++)
    {
        printf("Nome: %s\n", hosped[j].nome);
        printf("Data de Nascimento: %s\n", hosped[j].dataDeNascimento);
        printf("CPF: %s\n", hosped[j].cpf);
        printf("-------------------------\n");
    }
    
    printf("\nTotal de hospedes cadastrados: %d\n", totalHospedes);
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
        listarQuartosDisponiveis();
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

// FUNÇÃO PARA LISTAR APENAS QUARTOS DISPONÍVEIS
void listarQuartosDisponiveis()
{
    printf("\n===========================");
    printf("\n=== QUARTOS DISPONIVEIS ===");
    printf("\n===========================\n");
    int encontrou = 0;

    for (int i = 0; i < 30; i++)
    {
        // Verifica se o status do quarto é "DISPONIVEL"
        if (strcmp(quartos[i].status, "DISPONIVEL") == 0)
        {
            printf("Quarto %d - %s - \033[32m%s\033[0m\n",
                quartos[i].numero,
                quartos[i].tipo,
                quartos[i].status);
            encontrou = 1; // Marca que encontrou pelo menos um
        }
    }

    // Se o loop rodar inteiro e não achar nada, avisa o usuário
    if (encontrou == 0)
    {
        printf("Nenhum quarto disponivel no momento. O hotel esta lotado!\n");
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

    // SELEÇÃO DO QUARTO E VERIFICAÇÃO DE DISPONIBILIDADE
    printf("\nNumero do quarto desejado: ");
    scanf("%d", &nova.numeroQuarto);
    
    // Bloqueia se o número for inválido ou se o status for DIFERENTE (!= 0) de DISPONIVEL
    if (nova.numeroQuarto < 1 || nova.numeroQuarto > 30 || strcmp(quartos[nova.numeroQuarto - 1].status, "DISPONIVEL") != 0)
    {
        // Se cair aqui, mostra pro usuário qual é o status real do quarto
        printf("Erro: Quarto indisponivel para reserva. Status atual: %s\n", quartos[nova.numeroQuarto - 1].status);
        return;
    }
    
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
    salvarReservas();
    
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
                salvarQuartos();
                salvarReservas();
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
        salvarQuartos();
        salvarReservas();
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

    printf("\n==============================");
    printf("\n=== BUSCAR HOSPEDE POR CPF ===");
    printf("\n==============================");

    // VALIDAÇÃO DO CPF
        int cpfValido = 0;
        do
        {
            printf("\nInsira o CPF (Formato: XXX.XXX.XXX-XX): ");
            scanf("%s", cpfBusca);

            if (validarCPF(cpfBusca))
            {
                cpfValido = 1;
            }
            else
            {
                printf("Erro: CPF Inválido. Não esqueça dos pontos e do traço!\n");
            }
        } while (!cpfValido);

    // Percorre todos os hóspedes cadastrados
    for (int i = 0; i < totalHospedes; i++)
    {
        // Compara o CPF digitado com o CPF salvo
        if (strcmp(hosped[i].cpf, cpfBusca) == 0)
        {
            printf("\n\033[1;32mHospede Encontrado:\033[0m\n");

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
        printf("\n\033[1;31mHospede não Encontrado.\033[0m\n");
    }
}

// FUNÇÃO PARA REMOVER HÓSPEDE

void removerHospede()
{
    char cpfRemover[20];

    // Variável de controle
    int encontrado = 0;

    printf("\n=======================");
    printf("\n=== REMOVER HOSPEDE ===");
    printf("\n=======================");

    // VALIDAÇÃO DO CPF
    int cpfValido = 0;
    do
    {
        printf("\nDigite o CPF do hospede (Formato: XXX.XXX.XXX-XX): ");
        scanf("%s", cpfRemover);

        if (validarCPF(cpfRemover))
        {
            cpfValido = 1;
        }
        else
        {
            printf("Erro: CPF Inválido. Não esqueça dos pontos e do traço!\n");
        }
    } while (!cpfValido);

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

            printf("\n\033[1;32mHospede removido com sucesso!\033[0m\n");

            break;
        }
    }

    // Caso não encontre
    if (encontrado == 0)
    {
        printf("\n\033[1;31mHospede nao encontrado.\033[0m\n");
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

    salvarQuartos();
    printf("\nStatus atualizado com sucesso!\n");
}

// ========== FUNÇÃO PARA GERAR BOLETO ==========

void gerarBoleto(int idReserva, float valor, char *dataVencimento) {
    if (totalBoletos >= 100) {
        printf("Limite de boletos atingido!\n");
        return;
    }
    
    boleto novoBoleto;
    novoBoleto.idBoleto = totalBoletos + 1;
    novoBoleto.idReserva = idReserva;
    novoBoleto.valor = valor;
    strcpy(novoBoleto.dataVencimento, dataVencimento);
    strcpy(novoBoleto.status, "PENDENTE");
    
    // Gera um código de barras fictício
    sprintf(novoBoleto.codigoBarras, "34191.79001 01043.510047 91020.150008 7 81970000015000");
    
    boletos[totalBoletos] = novoBoleto;
    totalBoletos++;
    salvarBoletos();
    
    printf("\nBoleto gerado com sucesso!\n");
    printf("ID do Boleto: %d\n", novoBoleto.idBoleto);
    printf("Valor: R$ %.2f\n", valor);
    printf("Vencimento: %s\n", dataVencimento);
    printf("Codigo de Barras: %s\n", novoBoleto.codigoBarras);
}

// ========== FUNÇÃO PARA REALIZAR PAGAMENTO ==========

void realizarPagamento() {
    char cpfHospede[20];
    int idBoleto;
    int encontrou = 0;
    
    printf("\n===================================");
    printf("\n=== REALIZAR PAGAMENTO ===");
    printf("\n===================================\n");
    
    // Validação do CPF
    int cpfValido = 0;
    do {
        printf("Digite seu CPF (XXX.XXX.XXX-XX): ");
        scanf("%s", cpfHospede);
        
        if (validarCPF(cpfHospede)) {
            cpfValido = 1;
        } else {
            printf("Erro: CPF Invalido. Use o formato correto!\n");
        }
    } while (!cpfValido);
    
    // VERIFICAÇÃO SE O HÓSPEDE EXISTE NO SISTEMA
    int hospedeExiste = 0;
    for (int i = 0; i < totalHospedes; i++) {
        if (strcmp(hosped[i].cpf, cpfHospede) == 0) {
            hospedeExiste = 1;
            break;
        }
    }
    
    if (!hospedeExiste) {
        printf("\n\033[1;31mErro: Este CPF nao esta cadastrado no hotel!\033[0m\n");
        return; // Retorna para o menu
    }
    
    // Lista boletos pendentes do hóspede
    printf("\n--- BOLETOS PENDENTES ---\n");
    for (int i = 0; i < totalBoletos; i++) {
        for (int j = 0; j < totalreservas; j++) {
            if (reservas[j].idReserva == boletos[i].idReserva && 
                strcmp(reservas[j].cpfHospede, cpfHospede) == 0 &&
                strcmp(boletos[i].status, "PENDENTE") == 0) {
                
                printf("\nID Boleto: %d\n", boletos[i].idBoleto);
                printf("Valor: R$ %.2f\n", boletos[i].valor);
                printf("Vencimento: %s\n", boletos[i].dataVencimento);
                printf("Status: %s\n", boletos[i].status);
                printf("------------------------\n");
                encontrou = 1;
            }
        }
    }
    
    if (!encontrou) {
        printf("Hospede encontrado, mas nenhum boleto pendente para este CPF.\n");
        return;
    }
    
    // Solicita o ID do boleto para pagamento
    printf("\nDigite o ID do boleto que deseja pagar: ");
    scanf("%d", &idBoleto);
    
    // Processa o pagamento
    for (int i = 0; i < totalBoletos; i++) {
        if (boletos[i].idBoleto == idBoleto && strcmp(boletos[i].status, "PENDENTE") == 0) {
            strcpy(boletos[i].status, "PAGO");
            
            // Gera nota fiscal automaticamente após o pagamento
            for (int j = 0; j < totalreservas; j++) {
                if (reservas[j].idReserva == boletos[i].idReserva) {
                    char nomeHospede[60] = "";
                    for (int k = 0; k < totalHospedes; k++) {
                        if (strcmp(hosped[k].cpf, reservas[j].cpfHospede) == 0) {
                            strcpy(nomeHospede, hosped[k].nome);
                            break;
                        }
                    }
                    
                    notaFiscal nf;
                    nf.idNotaFiscal = totalNotas + 1;
                    nf.idReserva = reservas[j].idReserva;
                    strcpy(nf.cpfHospede, reservas[j].cpfHospede);
                    strcpy(nf.nomeHospede, nomeHospede);
                    nf.valorTotal = boletos[i].valor;
                    
                    time_t t = time(NULL);
                    struct tm tm = *localtime(&t);
                    sprintf(nf.dataEmissao, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
                    
                    sprintf(nf.itens, "Estadia - Quarto %d - Check-in: %s ate %s", 
                            reservas[j].numeroQuarto, reservas[j].dataCheckIn, reservas[j].dataCheckOut);
                    
                    notasFiscais[totalNotas] = nf;
                    totalNotas++;
                    salvarNotasFiscais();
                    
                    printf("\nPagamento realizado com sucesso!\n");
                    printf("Nota fiscal gerada automaticamente. ID da NF: %d\n", nf.idNotaFiscal);
                    break;
                }
            }
            
            salvarBoletos();
            return;
        }
    }
    
    printf("\nBoleto nao encontrado ou ja foi pago!\n");

}
// ========== FUNÇÃO PARA VER BOLETOS EMITIDOS ==========

void verBoletosEmitidos() {
    char cpfHospede[20];
    int encontrou = 0;
    
    printf("\n===================================");
    printf("\n=== BOLETOS EMITIDOS ===");
    printf("\n===================================\n");
    
    // Validação do CPF
    int cpfValido = 0;
    do {
        printf("Digite seu CPF (XXX.XXX.XXX-XX): ");
        scanf("%s", cpfHospede);
        
        if (validarCPF(cpfHospede)) {
            cpfValido = 1;
        } else {
            printf("Erro: CPF Invalido. Use o formato correto!\n");
        }
    } while (!cpfValido);
    
    // VERIFICAÇÃO SE O HÓSPEDE EXISTE NO SISTEMA
    int hospedeExiste = 0;
    for (int i = 0; i < totalHospedes; i++) {
        if (strcmp(hosped[i].cpf, cpfHospede) == 0) {
            hospedeExiste = 1;
            break;
        }
    }
    
    if (!hospedeExiste) {
        printf("\n\033[1;31mErro: Este CPF nao esta cadastrado no hotel!\033[0m\n");
        return; // Retorna para o menu
    }
    
    printf("\n--- HISTORICO DE BOLETOS ---\n");
    for (int i = 0; i < totalBoletos; i++) {
        for (int j = 0; j < totalreservas; j++) {
            if (reservas[j].idReserva == boletos[i].idReserva && 
                strcmp(reservas[j].cpfHospede, cpfHospede) == 0) {
                
                printf("\nBOLETO #%d\n", boletos[i].idBoleto);
                printf("Valor: R$ %.2f\n", boletos[i].valor);
                printf("Vencimento: %s\n", boletos[i].dataVencimento);
                printf("Status: %s\n", boletos[i].status);
                printf("Codigo de Barras: %s\n", boletos[i].codigoBarras);
                printf("------------------------\n");
                encontrou = 1;
            }
        }
    }
    
    if (!encontrou) {
        printf("Hospede encontrado, mas nenhum boleto gerado para este CPF.\n");
    }
}

// ========== FUNÇÃO PARA VER NOTAS FISCAIS ==========

void verNotasFiscais() {
    char cpfHospede[20];
    int encontrou = 0;
    
    printf("\n===================================");
    printf("\n=== NOTAS FISCAIS ===");
    printf("\n===================================\n");
    
    // Validação do CPF
    int cpfValido = 0;
    do {
        printf("Digite seu CPF (XXX.XXX.XXX-XX): ");
        scanf("%s", cpfHospede);
        
        if (validarCPF(cpfHospede)) {
            cpfValido = 1;
        } else {
            printf("Erro: CPF Invalido. Use o formato correto!\n");
        }
    } while (!cpfValido);
    
    // VERIFICAÇÃO SE O HÓSPEDE EXISTE NO SISTEMA
    int hospedeExiste = 0;
    for (int i = 0; i < totalHospedes; i++) {
        if (strcmp(hosped[i].cpf, cpfHospede) == 0) {
            hospedeExiste = 1;
            break;
        }
    }
    
    if (!hospedeExiste) {
        printf("\n\033[1;31mErro: Este CPF nao esta cadastrado no hotel!\033[0m\n");
        return; // Retorna para o menu
    }
    
    printf("\n--- NOTAS FISCAIS EMITIDAS ---\n");
    for (int i = 0; i < totalNotas; i++) {
        if (strcmp(notasFiscais[i].cpfHospede, cpfHospede) == 0) {
            printf("\nNOTA FISCAL #%d\n", notasFiscais[i].idNotaFiscal);
            printf("Data de Emissao: %s\n", notasFiscais[i].dataEmissao);
            printf("Valor Total: R$ %.2f\n", notasFiscais[i].valorTotal);
            printf("Itens: %s\n", notasFiscais[i].itens);
            printf("CNPJ Emissor: 12.345.678/0001-90\n");
            printf("------------------------\n");
            encontrou = 1;
        }
    }
    
    if (!encontrou) {
        printf("Hospede encontrado, mas nenhuma nota fiscal emitida para este CPF.\n");
    }
}

// ========== FUNÇÃO PARA GERAR BOLETO APÓS RESERVA (ATUALIZADA) ==========

void fazerReservaComBoleto() {
    if (totalreservas >= 50) {
        printf("Limite de reservas atingido!\n");
        return;
    }
    
    reserva nova;
    nova.idReserva = totalreservas + 1;
    printf("\n--- NOVA RESERVA ---\n");
    
    // VALIDAÇÃO DO CPF
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

    // VERIFICAÇÃO SE O HÓSPEDE EXISTE
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

    // SELEÇÃO DO QUARTO
    printf("\nNumero do quarto desejado: ");
    scanf("%d", &nova.numeroQuarto);
    
    if (nova.numeroQuarto < 1 || nova.numeroQuarto > 30 || strcmp(quartos[nova.numeroQuarto - 1].status, "DISPONIVEL") != 0) {
        printf("Erro: Quarto indisponivel para reserva. Status atual: %s\n", quartos[nova.numeroQuarto - 1].status);
        return;
    }
    
    // DATAS
    int dataInValida = 0;
    do {
        printf("Data de check-in (DD/MM/AAAA) [Atual ou Futura]: ");
        scanf("%s", nova.dataCheckIn);
        
        if (validarDataFutura(nova.dataCheckIn)) {
            dataInValida = 1;
        } else {
            printf("Erro: Formato invalido ou data no passado.\n");
        }
    } while (!dataInValida);    

    printf("Data de check-out (DD/MM/AAAA): ");
    scanf("%s", nova.dataCheckOut);
    
    nova.status = 0; // reservado
    reservas[totalreservas] = nova;
    totalreservas++;
    salvarReservas();
    
    // CALCULA VALOR DA ESTADIA (exemplo: R$ 100 por dia)
    float valorDiaria = 100.00;
    if (strcmp(quartos[nova.numeroQuarto - 1].tipo, "Suite Premium") == 0) {
        valorDiaria = 250.00;
    } else if (strcmp(quartos[nova.numeroQuarto - 1].tipo, "Duplo") == 0) {
        valorDiaria = 150.00;
    }
    
    float valorTotal = valorDiaria; // Simplificado - ideal seria calcular dias
    
    // Gera data de vencimento (7 dias após check-in)
    char dataVencimento[11];
    // Simplificado: apenas copia a data de check-in + 7 dias
    strcpy(dataVencimento, nova.dataCheckIn);
    
    // Gera o boleto
    gerarBoleto(nova.idReserva, valorTotal, dataVencimento);
    
    printf("\nReserva criada com sucesso! ID: %d\n", nova.idReserva);
    printf("Boleto gerado no valor de R$ %.2f\n", valorTotal);
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
        printf("\nEscolha uma opção: ");
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
            printf("Número inválido, tente novamente.\n");
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
        printf("\nEscolha uma opção: ");

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
            printf("Número inválido, tente novamente.\n");
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
        printf("\nEscolha uma opção: ");

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
            printf("Número inválido, tente novamente.\n");
            break;
        }
    } while (1);
}

// MENU HOSPEDE

void menuHospede()
{
    int opcao;

    do
    {
        printf("\n=========================");
        printf("\n=== PAINEL DO HOSPEDE ===");
        printf("\n=========================");
        printf("\n1. Consultar disponibilidade");
        printf("\n2. Realizar Reserva");
        printf("\n3. Realizar Pagamento (Ver boletos emitidos)");
        printf("\n4. Visualizar notas fiscais");
        printf("\n5. Fazer Reserva Com Boleto");
        printf("\n6. Sair");
        printf("\nEscolha uma opção: ");

        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            listarQuartos();
            break;
        case 2:
            fazerReserva();
            break;
        case 3:
            realizarPagamento();
            break;
        case 4:
            verNotasFiscais();
            break;
        case 5:
            fazerReservaComBoleto();
            break;
        case 6:
            return;

        default:
            printf("Número inválido, tente novamente.\n");
            break;
        }
    } while (1);
}

// ========== FUNÇÃO PRINCIPAL (MAIN) ==========

int main()
{
    // Essa função é para conZigurar o console para usar a codificação UTF-8
    SetConsoleOutputCP(65001);

    // Chamando a função para carregar os hóspedes do arquivo quando o programa iniciar, para que os dados sejam persistidos mesmo após fechar o programa
    carregarHospedes();
    // Chamando a função para carregar os quartos do arquivo quando o programa iniciar, para que o status dos quartos sejam mantidos mesmo após fechar o programa
    carregarQuartos();
    // Chamando a função para carregar as reservas do arquivo quando o programa iniciar, para que os dados sejam persistidos mesmo após fechar o programa
    carregarReservas();
    // Chamando a função para carregar os boletos do arquivo quando o programa inciar, para que os dados sejam persistidos mesmo após fechar o programa
    carregarBoletos();
    // Chamando a função para carregar as notas fiscais do arquivo quando o programa iniciar, para que os dados sejam persistidos mesmo após fechar o programa
    carregarNotasFiscais();

    // Puxando a função do SISTEMA DE LOGIN para o início do programa, para que o usuário seja direcionado para a tela de login assim que abrir o programa
    sistemaDeLogin();

    while (1)
    {
        sistemaDeLogin(); // Loop infinito pra manter o programa vivo
    }

    return 0;
}