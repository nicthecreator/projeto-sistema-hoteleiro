#   Sistema de Gestão Hoteleira

Este projeto consiste na estrutura de um software voltado à gestão hoteleira, desenvolvido como parte do **Projeto Integrador de Estrutura de Dados** no **Centro Universitário UNIEURO**. O sistema visa integrar de forma organizada e eficiente os principais processos operacionais e administrativos de um hotel.

## 📋 Sobre o Projeto
A solução foi projetada com foco em modularidade, eficiência e segurança da informação. O sistema permite o controle de quartos e disponibilidade em tempo real, articulando-se com módulos financeiros e gerenciais para suporte à tomada de decisões no ambiente hoteleiro.

### 🆕 Funcionalidades Implementadas (Versão Atual)
O código atual já contempla as seguintes funcionalidades estruturais:
* **Sistema de Login Contínuo e Autenticação:** Acesso seguro com limite de tentativas de falha (máximo de 3 tentativas antes do bloqueio). O sistema opera em loop, retornando à tela de login após o logout do usuário.
* **Controle de Perfis de Usuário:** Uso de vetores de `structs` para gerenciamento de credenciais, dividindo o acesso em quatro níveis hierárquicos:
  * **Recepção** (Acesso a cadastros, reservas e check-in/out)
  * **Administração** (Acesso a relatórios e gestão de hóspedes - *em desenvolvimento*)
  * **Equipe de Limpeza** (Visualização e atualização do status dos quartos)
  * **Hóspede** (Acesso estruturado para consultas e pagamentos - *em desenvolvimento*)
* **Navegação por Menus Direcionados:** Interfaces em console específicas para cada perfil logado, garantindo que cada usuário acesse apenas as opções pertinentes ao seu cargo.
* **Interface Visual Aprimorada:** Utilização de códigos de escape ANSI para colorir o status dos quartos (Verde para Disponível, Vermelho para Ocupado, Azul para Manutenção e Amarelo para Limpeza).

### ⚙️ Principais Funcionalidades (Requisitos Funcionais)
O sistema contempla as seguintes funcionalidades (ativas e estruturadas):
* **Cadastro de Hóspedes (RF01):** Inserção e listagem dos dados cadastrais dos clientes (Nome, Data de Nascimento, CPF) com limite de até 20 hóspedes.
* **Controle de Quartos (RF02):** Inicialização automática de 30 quartos (Solteiro, Duplo e Suíte Premium). Visualização colorida e alteração manual do status (Disponível, Ocupado, Em Limpeza ou Em Manutenção).
* **Registro de Reservas (RF03):** Criação de novas reservas, atrelando o CPF do hóspede ao número do quarto desejado, com verificação de limites (até 50 reservas) e validação de disponibilidade.
* **Check-in e Check-out (RF04):** Automatização da entrada e saída de hóspedes, integrando a liberação e ocupação dos quartos de acordo com o ID da reserva.
* **Processamento de Pagamentos e Documentos (RF05/RF06):** Menus já estruturados no painel do hóspede para futuras implementações de boletos e notas fiscais.

## 🛠️ Tecnologias Utilizadas
* **Linguagem:** C
* **Interface:** Console (Terminal) com suporte a cores ANSI.
* **Codificação:** Suporte a UTF-8 (`SetConsoleOutputCP(65001)`) para correta exibição de acentuação e caracteres especiais.
* **Bibliotecas Principais:** * `stdio.h` e `stdlib.h` (Entrada/saída e alocação)
  * `string.h` (Manipulação de strings e comparação de credenciais/status)
  * `windows.h` (Configurações do console do Windows)

## 🏗️ Requisitos Não Funcionais
Para garantir a qualidade e o desempenho, o software segue as seguintes diretrizes:
* **Segurança:** Bloqueio de acesso após tentativas inválidas.
* **Modularidade:** Separação do código em funções de menu, cadastro e operações diárias.
* **Desempenho em Tempo Real:** Atualização instantânea da disponibilidade dos quartos e fluxo de hospedagem na memória.
* **Confiabilidade:** Tratamento para impedir alocação de quartos já ocupados.

## 🚀 Como Executar
O arquivo principal do sistema é o `main.c`.
1. Certifique-se de ter um compilador C instalado (como o GCC).
2. No terminal, compile o arquivo:
   ```bash
   
   gcc main.c -o sistema_hotel
   ```
   ## 👥 Equipe de Desenvolvimento
Projeto desenvolvido pelos acadêmicos de **Análise e Desenvolvimento de Sistemas**:
* Nicolas Gabriel
* Guilherme Willee
* João Paulo
* Juan Felipe
* Mateus Gabriel

* **Professor Orientador:** Paulo Augusto 

---
*Brasília, 2026*
