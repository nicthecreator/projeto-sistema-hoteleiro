#   Sistema de Gestão Hoteleira

Este projeto consiste na estrutura de um software voltado à gestão hoteleira, desenvolvido como parte do **Projeto Integrador de Estrutura de Dados** no **Centro Universitário UNIEURO**. O sistema visa integrar de forma organizada e eficiente os principais processos operacionais e administrativos de um hotel.

## 📋 Sobre o Projeto
A solução foi projetada com foco em modularidade, eficiência e segurança da informação. O sistema permite o controle de quartos e disponibilidade em tempo real, articulando-se com módulos financeiros e gerenciais para suporte à tomada de decisões no ambiente hoteleiro.

### 🆕 Funcionalidades Implementadas (Versão Atual)
O código atual já contempla as seguintes funcionalidades estruturais:
* **Sistema de Login e Autenticação:** Acesso seguro com limite de tentativas de falha (máximo de 3 tentativas antes do bloqueio).
* **Controle de Perfis de Usuário:** Uso de `structs` para gerenciamento de credenciais, dividindo o acesso em três níveis hierárquicos:
  * *Recepção*
  * *Administração*
  * *Equipe de Limpeza*
* **Navegação por Menus Direcionados:** Interfaces em console específicas para cada perfil logado, garantindo que cada usuário acesse apenas as opções pertinentes ao seu cargo.

### Principais Funcionalidades (Requisitos Funcionais)
O sistema contempla as seguintes funcionalidades automáticas:
* **Cadastro de Hóspedes (RF01):** Inserção, consulta e atualização dos dados cadastrais dos clientes.
* **Controle de Quartos (RF02):** Visualização e alteração do status (disponível, ocupado, em limpeza ou em manutenção).
* **Registro de Reservas (RF03):** Registro de novas reservas com verificação automática de disponibilidade.
* **Check-in e Check-out (RF04):** Automatização dos processos de entrada e saída, integrando a liberação dos quartos.
* **Processamento de Pagamentos (RF05):** Registro de transações financeiras de forma integrada e segura.
* **Emissão de Documentos (RF06):** Geração automática de faturas e relatórios financeiros.
* **Atualização de Limpeza (RF07):** Atualização do status dos quartos pela equipe de governança após a higienização.
* **Relatórios Gerenciais (RF08):** Consolidação de dados de desempenho e ocupação para gestão.

## 🛠️ Tecnologias Utilizadas
* **Linguagem:** C
* **Interface:** Console (Terminal) com suporte a cores ANSI e codificação UTF-8 para acentuação.
* **Bibliotecas Principais no momento:** `stdio.h`, `string.h`, `windows.h`.

## 🏗️ Requisitos Não Funcionais
Para garantir a qualidade e o desempenho, o software segue as seguintes diretrizes:
* **Segurança:** Proteção de dados sensíveis e integridade das informações financeiras.
* **Modularidade:** Estrutura em módulos independentes para facilitar a manutenção.
* **Desempenho em Tempo Real:** Atualização instantânea da disponibilidade e fluxo de hospedagem.
* **Confiabilidade:** Centralização de dados para reduzir falhas operacionais e erros de registro.
* **Escalabilidade:** Estrutura preparada para suportar o aumento do fluxo de dados.

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
