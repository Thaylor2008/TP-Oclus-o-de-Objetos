#include "Cena.h"
#include <iomanip>
#include <iostream>

Cena::Cena(int tempo, int capacidade) // construtor
    : tempo(tempo), n(0) {}

// Adiciona objeto visivel 
void Cena::adicionarVisivel(int id, double inicio, double fim) {
    if (n < cap_max) {
        visiveis[n].id = id;
        visiveis[n].inicio = inicio;
        visiveis[n].fim = fim;
        n++;
    }
}
int Cena::getTempo() const {
    return tempo;
}

// Imprimi os objetos visiveis na cena
void Cena::imprimir() const {
    std::cout << std::fixed << std::setprecision(2);

    TrechoVisivel copia[cap_max];
    for (int i = 0; i < n; i++) copia[i] = visiveis[i];

    // ordena por id
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (copia[j].id > copia[j + 1].id) {
                TrechoVisivel temp = copia[j];
                copia[j] = copia[j + 1];
                copia[j + 1] = temp;
            }
        }
    }

    // imprime em ordem de id
    for (int i = 0; i < n; i++) {
        std::cout << "S " << tempo << " "
                  << copia[i].id << " "
                  << copia[i].inicio << " "
                  << copia[i].fim << std::endl;
    }
}