// include/Cena.h
#ifndef CENA_H
#define CENA_H

#include <iostream>
#include <iomanip>

struct TrechoVisivel {
    int id;
    double inicio;
    double fim;
};

class Cena {
private:
    
    int tempo;
    int n;        // número de objetos visíveis
    static const int cap_max = 100;
    TrechoVisivel visiveis[cap_max];

public:
    Cena(int tempo = 0, int capacidade = 100); // construtor

    int getTempo() const;
    void adicionarVisivel(int id, double inicio, double fim);
    void imprimir() const;
    
};

#endif