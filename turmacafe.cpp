#include <iostream>
#include <fstream>
#include <string>

using namespace std;

typedef struct Participantes {
    int id;
    string nome;
    int semestre;
    int anoIngresso;
    string curso;
} Participantes;

struct Node {
    Participantes participante;
    Node *proximo;
};

struct Lista {
    Node *inicio = NULL;
    int tamanho = 0;
    int proximoID = 1;
};

typedef struct Contribuintes {
    int idParticipante;
    int mes;
    int ano;
    float valor;
} Contribuintes;

struct NodeContribuinte {
    Contribuintes contribuinte;
    NodeContribuinte *proximo;
};

struct ListaContribuintes {
    NodeContribuinte *inicio = NULL;
    int tamanho = 0;
};

void adicionar_participante(Lista *lista, string nome, int semestre, int anoIngresso, string curso);
void editar_participante(Lista *lista, int id);
void mostrar_menu();
void processar_opcao(Lista *lista, ListaContribuintes *listaCont, int opcao);
int gerar_id(Lista *lista);
Node* buscar_participante(Lista *lista, int id);
void escrever_participante_no_arquivo(Lista *lista);
void sobrescrever_participantes_no_arquivo(Lista *lista);
void imprimir_participantes_do_arquivo();
void destruir_lista(Lista *lista);

void novaContribuicao(Lista *lista, ListaContribuintes *listaCont);
void adicionar_contribuicao(ListaContribuintes *listaCont, int idParticipante, int mes, int ano, float valor);
void destruir_lista_contribuintes(ListaContribuintes *listaCont);

int selecionarMes();
int validarAno(int anoAtual);

void mostrarContribuintes(Lista *lista, ListaContribuintes *listaCont);
void contribuintesCurso(Lista *lista, ListaContribuintes *listaCont);

int main() {
    Lista lista;
    ListaContribuintes listaCont;
    int opcao;

    do {
        cout << endl;
        mostrar_menu();
        cin >> opcao;
        processar_opcao(&lista, &listaCont, opcao);
    } while (opcao != 0);

    destruir_lista(&lista);
    destruir_lista_contribuintes(&listaCont);
}

void adicionar_participante(Lista *lista, string nome, int semestre, int anoIngresso, string curso) {
    Node *new_node = new Node;
    if (new_node == NULL) {
        cerr << "Acabou a memória. " << endl;
        exit(1);
    }

    new_node->participante.id = gerar_id(lista);
    new_node->participante.nome = nome;
    new_node->participante.semestre = semestre;
    new_node->participante.anoIngresso = anoIngresso;
    new_node->participante.curso = curso;
    new_node->proximo = lista->inicio;

    lista->inicio = new_node;
    lista->tamanho++;

    sobrescrever_participantes_no_arquivo(lista);
}

void editar_participante(Lista *lista, int id) {
    cout << "Procurando participante com ID: " << id << endl;

    Node *node = buscar_participante(lista, id);
    if (node == NULL) {
        cout << "Participante não encontrado." << endl;
        return;
    } else {
        cout << endl;
        cout << "Participante encontrado: " << node->participante.nome << endl;
    }

    int semestre, anoIngresso;
    string nome, curso;

    cout << "Digite o novo nome: ";
    cin >> nome;
    cout << "Digite o novo semestre: ";
    cin >> semestre;
    cout << "Digite o novo ano de ingresso: ";
    cin >> anoIngresso;
    cout << "Digite o novo curso (DSM/SI/GE): ";
    cin >> curso;

    node->participante.nome = nome;
    node->participante.semestre = semestre;
    node->participante.anoIngresso = anoIngresso;
    node->participante.curso = curso;

    cout << "Participante atualizado com sucesso!" << endl;

    sobrescrever_participantes_no_arquivo(lista);
}

void mostrar_menu() {
    cout << "***** MENU PRINCIPAL *****" << endl;
    cout << "1. Novo Participante"       << endl;
    cout << "2. Editar participante"     << endl;
    cout << "3. Mostrar Participantes"   << endl;
    cout << "4. Nova Contribuição"       << endl;
    cout << "5. Mostrar Contribuintes"   << endl;
    cout << "6. Contribuintes por Curso" << endl;
    cout << "0. Sair"                    << endl;
    cout << "Escolha uma opcao: ";
}

void processar_opcao(Lista *lista, ListaContribuintes *listaCont, int opcao) {
    if (opcao == 1) {
        int semestre, anoIngresso;
        string nome, curso;

        cout << "Digite o nome: ";
        cin >> nome;

        cout << "Digite o semestre: ";
        cin >> semestre;

        cout << "Digite o ano de ingresso: ";
        cin >> anoIngresso;

        cout << "Digite o curso (DSM/SI/GE): ";
        cin >> curso;

        adicionar_participante(lista, nome, semestre, anoIngresso, curso);
        cout << "Participante adicionado com sucesso!" << endl;
    } else if (opcao == 2) {
        int id;
        cout << "Digite o ID do participante a ser editado: ";
        cin >> id;
        editar_participante(lista, id);
    } else if (opcao == 3) {
        imprimir_participantes_do_arquivo();
    } else if (opcao == 4) {
        novaContribuicao(lista, listaCont);
    } else if (opcao == 5) {
        mostrarContribuintes(lista, listaCont);
    } else if (opcao == 6) {
        contribuintesCurso(lista, listaCont);
    } else if (opcao != 0) {
        cout << "Opcao invalida. Tente novamente." << endl;
    }
}

int gerar_id(Lista *lista) {
    return lista->proximoID++;
}

Node* buscar_participante(Lista *lista, int id) {
    Node *atual = lista->inicio;
    while (atual != NULL) {
        if (atual->participante.id == id) {
            return atual;
        }
        atual = atual->proximo;
    }
    return NULL;
}

void escrever_participante_no_arquivo(Lista *lista) {
    ofstream arquivo("participantes.txt");

    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo." << endl;
        return;
    }

    Node *atual = lista->inicio;
    while (atual != NULL) {
        arquivo << "ID: " << atual->participante.id << endl;
        arquivo << "NOME: " << atual->participante.nome << endl;
        arquivo << "SEMESTRE: " << atual->participante.semestre << endl;
        arquivo << "ANO DE INGRESSO: " << atual->participante.anoIngresso << endl;
        arquivo << "CURSO: " << atual->participante.curso << endl;
        arquivo << "---------------------------------------------------" << endl;
        atual = atual->proximo;
    }

    arquivo.close();
}

void sobrescrever_participantes_no_arquivo(Lista *lista) {
    ofstream arquivo("participantes.txt");

    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo." << endl;
        return;
    }

    Node *atual = lista->inicio;
    while (atual != NULL) {
        arquivo << "ID: " << atual->participante.id << endl;
        arquivo << "Nome: " << atual->participante.nome << endl;
        arquivo << "Semestre: " << atual->participante.semestre << endl;
        arquivo << "Ano de Ingresso: " << atual->participante.anoIngresso << endl;
        arquivo << "Curso: " << atual->participante.curso << endl;
        arquivo << "---------------------------" << endl;
        atual = atual->proximo;
    }

    arquivo.close();
}

void imprimir_participantes_do_arquivo() {
    ifstream arquivo("participantes.txt");

    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo." << endl;
        return;
    }

    string linha;
    cout << endl;
    while (getline(arquivo, linha)) {
        cout << linha << endl;
    }

    arquivo.close();
}

void novaContribuicao(Lista *lista, ListaContribuintes *listaCont) {
    int idParticipante, mes, ano;
    float valor;

    cout << "Digite o ID do participante: ";
    cin >> idParticipante;

    Node *participanteEncontrado = buscar_participante(lista, idParticipante);
    if (participanteEncontrado == NULL) {
        cout << "Participante não encontrado!" << endl;
        return;
    } else {
        cout << endl;
        cout << "Participante encontrado: " << participanteEncontrado->participante.nome << endl;
    }

    mes = selecionarMes();
    ano = validarAno(2024);
    cout << "Digite o valor da contribuição: ";
    cin >> valor;

    adicionar_contribuicao(listaCont, idParticipante, mes, ano, valor);
    cout << "Contribuição cadastrada com sucesso!" << endl;
}

void adicionar_contribuicao(ListaContribuintes *listaCont, int idParticipante, int mes, int ano, float valor){
    NodeContribuinte *new_node = new NodeContribuinte;
    if(new_node == NULL){
        cerr << "Acabou a memória. " << endl;
        exit(1);
    }

    new_node->contribuinte.idParticipante = idParticipante;
    new_node->contribuinte.mes            = mes;
    new_node->contribuinte.ano            = ano;
    new_node->contribuinte.valor          = valor;
    new_node->proximo                     = listaCont->inicio;

    listaCont->inicio = new_node;
    listaCont->tamanho++;
}

void destruir_lista(Lista *lista) {
    Node *atual = lista->inicio;
    while (atual != NULL) {
        Node *proximo = atual->proximo;
        delete atual;
        atual = proximo;
    }
    lista->inicio = NULL;
    lista->tamanho = 0;
}

void destruir_lista_contribuintes(ListaContribuintes *listaCont) {
    NodeContribuinte *atual = listaCont->inicio;
    while (atual != NULL) {
        NodeContribuinte *proximo = atual->proximo;
        delete atual;
        atual = proximo;
    }
    listaCont->inicio = NULL;
    listaCont->tamanho = 0;
}

int selecionarMes() {
    int mes;
    cout << "Digite o mês da contribuição (1-12): ";
    cin >> mes;

    switch (mes) {
        case 1: return 1;
        case 2: return 2;
        case 3: return 3;
        case 4: return 4;
        case 5: return 5;
        case 6: return 6;
        case 7: return 7;
        case 8: return 8;
        case 9: return 9;
        case 10: return 10;
        case 11: return 11;
        case 12: return 12;
        default:
            cout << "Mês inválido. Tente novamente." << endl;
            return selecionarMes();
    }
}


int validarAno(int anoAtual) {
    int ano;
    cout << "Digite o ano da contribuição (>= " << anoAtual << "): ";
    cin >> ano;

    if (ano < anoAtual) {
        cout << "Ano inválido. Tente novamente." << endl;
        return validarAno(anoAtual); 
    }

    return ano;
}

void mostrarContribuintes(Lista *lista, ListaContribuintes *listaCont){
    ofstream arquivo("contribuintes.txt");

     if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo." << endl;
        return;
    }

    NodeContribuinte *atual = listaCont->inicio;
    while (atual != NULL) {
        Node *participante = buscar_participante(lista, atual->contribuinte.idParticipante);
        if (participante != NULL) {
            arquivo << "ID Participante: " << atual->contribuinte.idParticipante << endl;
            arquivo << "Nome: " << participante->participante.nome << endl;
            arquivo << "Mês: " << atual->contribuinte.mes << endl;
            arquivo << "Ano: " << atual->contribuinte.ano << endl;
            arquivo << "Valor: " << atual->contribuinte.valor << endl;
            arquivo << "--------------------------------------" << endl;
        }
        atual = atual->proximo;
    }

    arquivo.close();

    // Abrir o arquivo em modo de leitura e exibir o conteúdo no console
    ifstream arquivoLeitura("contribuintes.txt");

    if (!arquivoLeitura.is_open()) {
        cerr << "Erro ao abrir o arquivo para leitura." << endl;
        return;
    }

    string linha;
    cout << endl << "Contribuintes gravados no arquivo: " << endl;
    while (getline(arquivoLeitura, linha)) {
        cout << linha << endl;
    }

    arquivoLeitura.close();
}

void contribuintesCurso(Lista *lista, ListaContribuintes *listaCont) {
    bool existemDSM = false, existemSI = false, existemGE = false;

    NodeContribuinte *atual = listaCont->inicio;
    while (atual != NULL) {
        Node *participante = buscar_participante(lista, atual->contribuinte.idParticipante);
        if (participante != NULL) {
            if (participante->participante.curso == "DSM") {
                existemDSM = true;
            } else if (participante->participante.curso == "SI") {
                existemSI = true;
            } else if (participante->participante.curso == "GE") {
                existemGE = true;
            }
        }
        atual = atual->proximo;
    }

    if (existemDSM) {
        ofstream arquivoDSM("contribuintes_DSM.txt");
        if (!arquivoDSM.is_open()) {
            cerr << "Erro ao abrir o arquivo contribuintes_DSM.txt." << endl;
        } else {
            atual = listaCont->inicio;
            while (atual != NULL) {
                Node *participante = buscar_participante(lista, atual->contribuinte.idParticipante);
                if (participante != NULL && participante->participante.curso == "DSM") {
                    arquivoDSM << "ID Participante: " << atual->contribuinte.idParticipante << endl;
                    arquivoDSM << "Nome: " << participante->participante.nome << endl;
                    arquivoDSM << "Mês: " << atual->contribuinte.mes << endl;
                    arquivoDSM << "Ano: " << atual->contribuinte.ano << endl;
                    arquivoDSM << "Valor: " << atual->contribuinte.valor << endl;
                    arquivoDSM << "--------------------------------------" << endl;
                }
                atual = atual->proximo;
            }
            arquivoDSM.close();
        }
    }

    if (existemSI) {
        ofstream arquivoSI("contribuintes_SI.txt");
        if (!arquivoSI.is_open()) {
            cerr << "Erro ao abrir o arquivo contribuintes_SI.txt." << endl;
        } else {
            atual = listaCont->inicio;
            while (atual != NULL) {
                Node *participante = buscar_participante(lista, atual->contribuinte.idParticipante);
                if (participante != NULL && participante->participante.curso == "SI") {
                    arquivoSI << "ID Participante: " << atual->contribuinte.idParticipante << endl;
                    arquivoSI << "Nome: " << participante->participante.nome << endl;
                    arquivoSI << "Mês: " << atual->contribuinte.mes << endl;
                    arquivoSI << "Ano: " << atual->contribuinte.ano << endl;
                    arquivoSI << "Valor: " << atual->contribuinte.valor << endl;
                    arquivoSI << "--------------------------------------" << endl;
                }
                atual = atual->proximo;
            }
            arquivoSI.close();
        }
    }

    if (existemGE) {
        ofstream arquivoGE("contribuintes_GE.txt");
        if (!arquivoGE.is_open()) {
            cerr << "Erro ao abrir o arquivo contribuintes_GE.txt." << endl;
        } else {
            atual = listaCont->inicio;
            while (atual != NULL) {
                Node *participante = buscar_participante(lista, atual->contribuinte.idParticipante);
                if (participante != NULL && participante->participante.curso == "GE") {
                    arquivoGE << "ID Participante: " << atual->contribuinte.idParticipante << endl;
                    arquivoGE << "Nome: " << participante->participante.nome << endl;
                    arquivoGE << "Mês: " << atual->contribuinte.mes << endl;
                    arquivoGE << "Ano: " << atual->contribuinte.ano << endl;
                    arquivoGE << "Valor: " << atual->contribuinte.valor << endl;
                    arquivoGE << "--------------------------------------" << endl;
                }
                atual = atual->proximo;
            }
            arquivoGE.close();
        }
    }

    cout << "Contribuintes gravados nos arquivos por curso." << endl;
}
