# Projeto "Turma do Café"

## Descrição

O projeto "Turma do Café" visa auxiliar uma comunidade da Fatec Araras, que compartilha o interesse comum por café, no controle dos seus participantes e contribuintes.

## Funcionalidades do Programa

### Participantes da Comunidade

1. **Criar Estrutura de Participantes**
   - Armazena informações como ID, nome (somente primeiro nome), semestre e ano de ingresso na Fatec Araras, e curso (DSM, SI, ou GE).
   - Não há limites no número de participantes.
   - **Menu**: Opção para inserir novos participantes na comunidade "Turma do Café".

2. **Editar Dados dos Participantes**
   - Permite editar todos os dados de um participante, exceto o ID, utilizando o ID como referência.
   - **Menu**: Opção para editar dados dos participantes.

3. **Carregar Participantes de Arquivo**
   - Lê os dados de todos os participantes de um arquivo-texto chamado `participantes.txt` e alimenta a estrutura de dados.
   - **Menu**: Opção para carregar os dados dos participantes a partir do arquivo.

4. **Gravar Participantes em Arquivo**
   - Grava os dados de todos os participantes em um arquivo-texto chamado `participantes.txt`, sobrescrevendo o conteúdo existente.
   - **Menu**: Opção para salvar os dados dos participantes no arquivo após operações de inserção e edição.

### Contribuintes da Comunidade

5. **Criar Estrutura de Contribuintes**
   - Armazena informações como ID do participante, mês (1-12), ano (>=2024), e valor da contribuição.
   - **Menu**: Opção "Cadastrar contribuição" para inserir novas contribuições, verificando se o ID do participante existe na estrutura de participantes.

6. **Gravar Contribuintes em Arquivo**
   - Grava os dados de todos os contribuintes em um arquivo-texto chamado `contribuintes.txt`, sobrescrevendo o conteúdo existente.
   - **Menu**: Opção para salvar os dados dos contribuintes no arquivo.

7. **Gravar Contribuintes por Curso em Arquivos**
   - Grava os dados dos contribuintes em arquivos separados por curso: `contribuintes_DSM.txt`, `contribuintes_SI.txt`, `contribuintes_GE.txt`.
   - **Menu**: Opção para gerar relatórios de contribuintes por curso.

## Estrutura do Menu Principal

O menu principal deve permitir a execução das seguintes opções:

1. Inserir novo participante
2. Editar dados do participante
3. Carregar participantes do arquivo `participantes.txt`
4. Salvar participantes no arquivo `participantes.txt`
5. Cadastrar contribuição
6. Salvar contribuintes no arquivo `contribuintes.txt` e mostrar os contribuintes
7. Salvar contribuintes em arquivos por curso (`contribuintes_DSM.txt`, `contribuintes_SI.txt`, `contribuintes_GE.txt`)

## Requisitos Técnicos

- O programa deve ser escrito em C++.
- Utilizar estruturas de dados dinâmicas para armazenar participantes e contribuintes.
- Implementar funções para manipulação dos dados conforme descrito nas funcionalidades.

## Como Executar

1. Compile o código-fonte utilizando um compilador de C++.
2. Execute o programa compilado.
3. Utilize o menu principal para navegar e utilizar as funcionalidades do programa.

## Exemplo de Execução

- Ao iniciar, o menu principal será exibido com as opções descritas.
- Selecione a opção desejada digitando o número correspondente e siga as instruções na tela.

## Arquivos

- `participantes.txt`: Armazena os dados de todos os participantes.
- `contribuintes.txt`: Armazena os dados de todos os contribuintes.
- `contribuintes_DSM.txt`: Armazena os dados dos contribuintes do curso DSM.
- `contribuintes_SI.txt`: Armazena os dados dos contribuintes do curso SI.
- `contribuintes_GE.txt`: Armazena os dados dos contribuintes do curso GE.
