#ifndef CENA_H
#define CENA_H

struct TrechoVisivel {
    int id;
    double inicio;
    double fim;
};

class Cena {
private:
    
    int tempo;
    int n;        // número de objetos visíveis
    static const int cap_max = 100; // capacidade max de objetos visiveis na cena
    TrechoVisivel visiveis[cap_max]; // vetor com os objetos visiveis em cena 
    

public:
    Cena(int tempo = 0, int capacidade = 100); // construtor

    int getTempo() const;
    
    // Adiciona objeto visivel 
    void adicionarVisivel(int id, double inicio, double fim);
    
    // Imprimi os objetos visiveis na cena
    void imprimir() const;
    
};

#endif
