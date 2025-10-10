#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Objeto.hpp"
#include "Cena.hpp"
using namespace std;

void ordenarObjetos(Objeto* objetos, int n_objetos) {
    for (int i = 0; i < n_objetos - 1; i++) {
        for (int j = 0; j < n_objetos - i - 1; j++) {
            if (objetos[j].getY() > objetos[j + 1].getY()) {
                Objeto temp = objetos[j];
                objetos[j] = objetos[j + 1];
                objetos[j + 1] = temp;
            }
        }
    }
}

void geraCena(Objeto* objetos, int n_objetos, int tempo) {
    // Cria a cena
    Cena cena(tempo);

    // Ordena objetos por profundidade (y crescente)
    ordenarObjetos(objetos, n_objetos);

    // Vetor para armazenar trechos já cobertos (oclusos)
    const int MAX_SEG = 100;
    double ocupados[MAX_SEG][2];
    int n_ocupados = 0;

    // Percorre todos os objetos na ordem correta
    for (int i = 0; i < n_objetos; i++) {
        double ini = objetos[i].inicio();
        double fim = objetos[i].fim();

        // Percorre todos os trechos já ocupados e divide o intervalo visível
        for (int j = 0; j < n_ocupados; j++) {
            // se não há interseção com o trecho ocupado, continua
            if (fim <= ocupados[j][0] || ini >= ocupados[j][1])
                continue;

            // Se o início está antes do trecho ocupado, adiciona o trecho visível à esquerda
            if (ini < ocupados[j][0]) {
                cena.adicionarVisivel(objetos[i].getId(), ini, ocupados[j][0]);
            }

            // Avança o início até o final do trecho ocupado
            ini = ocupados[j][1];
        }

        // Se sobrou parte visível no final, adiciona também
        if (ini < fim) {
            cena.adicionarVisivel(objetos[i].getId(), ini, fim);
        }

        // Marca o trecho como ocupado (para oclusões futuras)
        ocupados[n_ocupados][0] = objetos[i].inicio();
        ocupados[n_ocupados][1] = objetos[i].fim();
        n_ocupados++;
    }

    // Imprime a cena formatada (2 casas decimais)
    cena.imprimir();
}

int main() {
    const int MAX_OBJ = 100;
    Objeto todos_objetos[MAX_OBJ];
    int n_objetos = 0;

    string linha;
    while (getline(cin, linha)) {
        if (linha.empty()) continue; // ignora linhas vazias

        char tipo = linha[0];
        istringstream iss(linha);
        char tipoChar;

        if (tipo == 'O') {
            int id;
            double x, y, largura;
            iss >> tipoChar >> id >> x >> y >> largura;
            if (n_objetos < MAX_OBJ)
                todos_objetos[n_objetos++] = Objeto(id, x, y, largura);
        }
        else if (tipo == 'M') {
            int tempo, id;
            double x, y;
            iss >> tipoChar >> tempo >> id >> x >> y;
            for (int i = 0; i < n_objetos; i++) {
                if (todos_objetos[i].getId() == id) {
                    todos_objetos[i].alteraxy(x, y);
                    break;
                }
            }
        }
        else if (tipo == 'C') {
            int tempo;
            iss >> tipoChar >> tempo;
            ordenarObjetos(todos_objetos, n_objetos);
            geraCena(todos_objetos, n_objetos, tempo);
        }
    }

    return 0;
}
