#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> // Essa biblioteca serve para usar os structs e manipulação de strings

// STRUCT DE LOGIN NO SISTEMA

typedef struct{
    char login[30];
    char senha[30];
} pessoa; pessoa p[5];  // diminuindo o nome da struct para "p" e o "[1]" é o máximo de pessoas com logins e senhas

// MENU RECEPCIONISTA

void menuRecepcionista() {
    int opcao;
    printf("\n==========================");
    printf("\n=== PAINEL DA RECEPCAO ===");
    printf("\n==========================\n");
    printf("1. Cadastro de Hospedes\n");
    printf("2. Controle de Quartos\n");
    printf("3. Reservas Feitas\n");
    printf("4. Check-in\n");
    printf("5. Check Out\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);


    switch (opcao){
    case 1:
    printf("\nCadastro de Hospedes selecionado");
        break;
    
    default:
        printf("Numero invalido, tente novamente.");
        break;
    }
}


// MENU ADMINISTRADOR

void menuAdministrador(){
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

void menuAuxiliarDeLimpeza(){
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


int main(){
    
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

    while (tentativas < 3 && logado == 0){
        printf("\n===================================");
        printf("\n=== SISTEMA DE GESTAO HOTELEIRA ===");
        printf("\n===================================");
        printf("\nLogin: ");
        scanf("%s", login); // armazenando os dados inseridos pelo usuário para o vetor login que está dentro da função main
        printf("\nSenha: ");
        scanf("%s", senha);

        if ((strcmp(login,p[0].login)==0) && (strcmp(senha,p[0].senha)==0)){ // A função strcmp é responsável por comparar string com string
        // RECEPCIONISTA LOGADO
            printf("\nBem-vindo(a), Recepcionista!\n");
            logado = 1;
            menuRecepcionista();
        } else if((strcmp(login,p[1].login)==0) && (strcmp(senha,p[1].senha)==0)) {

        // ADMIN LOGADO
            printf("\nBem-vindo(a), Administrador!\n");
            logado = 1;
            menuAdministrador();
        } else if((strcmp(login,p[2].login)==0) && (strcmp(senha,p[2].senha)==0)) {

        // EQUIPE DE LIMPEZA LOGADO
            printf("\nBem-vindo(a), Auxiliar de limpeza!\n");
            logado = 1;
            menuAuxiliarDeLimpeza();
        } 
        else{
           tentativas++;
           printf("\nErro: Credenciais incorretas.\n");
           if (tentativas < 3) {
            printf("Voce tem mais %d tentativa(s).\n", 3 - tentativas);
           } else {
            printf("Acesso bloqueado por seguranca!\n");
           }
    }
    }


    

    return 0;
}
