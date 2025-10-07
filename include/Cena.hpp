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
    int cap;      // capacidade máxima de objetos
    TrechoVisivel* visiveis; // ponteiro para vetor dinâmico

public:
    Cena(int tempo = 0, int capacidade = 10);
    ~Cena(); // destrutor para liberar memória

    void adicionarVisivel(int id, double inicio, double fim);
    void imprimir() const;
    int getTempo() const;
};

#endif
