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

void adicionar_participante(Lista *lista, string nome, int semestre, int anoIngresso, string curso);
void editar_participante(Lista *lista, int id);
void mostrar_menu();
void processar_opcao(Lista *lista, int opcao);
int gerar_id(Lista *lista);
Node* buscar_participante(Lista *lista, int id);
void escrever_participante_no_arquivo(Lista *lista);
void sobrescrever_participantes_no_arquivo(Lista *lista);
void imprimir_participantes_do_arquivo();
void destruir_lista(Lista *lista);

int main() {
    Lista lista;
    int opcao;

    do {
        cout << endl;
        mostrar_menu();
        cin >> opcao;
        processar_opcao(&lista, opcao);
    } while (opcao != 0);

    destruir_lista(&lista);
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
    cout << "1. Adicionar participante" << endl;
    cout << "2. Editar participante" << endl;
    cout << "3. Mostrar Participantes" << endl;
    cout << "0. Sair" << endl;
    cout << "Escolha uma opcao: ";
}

void processar_opcao(Lista *lista, int opcao) {
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
