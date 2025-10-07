// src/Cena.cpp
#include "Cena.hpp"
#include <iomanip>
#include <cstdlib>


Cena::Cena(int tempo, int capacidade)
    : tempo(tempo), n(0), cap(capacidade) 
{
    visiveis = new TrechoVisivel[capacidade]; // aloca vetor
}

Cena::~Cena() {
    delete[] visiveis; // destrutor, libera memória
}

void Cena::adicionarVisivel(int id, double inicio, double fim) {
    if (n >= cap) {
        // aumenta a capacidade quando encher o vetor (crescimento dinâmico)
        int novaCap = cap * 2;
        TrechoVisivel* novoVet = new TrechoVisivel[novaCap];

        // copia os elementos antigos
        for (int i = 0; i < n; i++) {
            novoVet[i] = visiveis[i];
        }

        // libera o vetor antigo
        delete[] visiveis;
        visiveis = novoVet;
        cap = novaCap;
    }

    visiveis[n].id = id;
    visiveis[n].inicio = inicio;
    visiveis[n].fim = fim;
    n++;
}

void Cena::imprimir() const {
    std::cout << std::fixed << std::setprecision(2);
    for (int i = 0; i < n; i++) {
        std::cout << "S " << tempo << " "
                  << visiveis[i].id << " "
                  << visiveis[i].inicio << " "
                  << visiveis[i].fim << std::endl;
    }
}

int Cena::getTempo() const {
    return tempo;
}