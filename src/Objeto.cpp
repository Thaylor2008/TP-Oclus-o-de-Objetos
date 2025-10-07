#include "Objeto.hpp"

// construtor
Objeto::Objeto(int id, double x, double y, double largura)
    : id(id), x(x), y(y), largura(largura) {}

//acesso aos dados 
int Objeto::getId() const { return id; } // o acessa o id
double Objeto::getX() const { return x; } // o acessa o x
double Objeto::getY() const { return y; } // o acessa o y
double Objeto::getLargura() const { return largura; }  // o acessa a largura 

// move o objeto, altera x e y
void Objeto::alteraxy(double novoX, double novoY) {
    x = novoX;
    y = novoY;
}

// retorna o início do objeto
double Objeto::inicio() const {
    return x - largura / 2.0f;
}

// retona o final do objeto 
double Objeto::fim() const {
   return x + largura / 2.0f;
}