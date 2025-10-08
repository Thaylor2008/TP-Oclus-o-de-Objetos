#ifndef OBJETO_H
#define OBJETO_H

class Objeto {
private:
    int id; // ID do objeto
    double x, y, largura;    // x = centro no eixo X, y = profundidade, largura do objeto
 
public:
    // construtor
    Objeto(int id = -1, double x = 0, double y = 0, double largura = 0);

    // acesso aos dados
    int getId() const;
    double getX() const;
    double getY() const;
    double getLargura() const;

    //função pra mover objeto, atualiza x e y
    void alteraxy(double novoX, double novoY);

    // O início do objeto 
    double inicio() const;
    // O fim do objeto
    double fim() const;
};  
#endif
