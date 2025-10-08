#include <iostream>
#include <fstream>
#include <string>
#include "Objeto.h"
#include "Cena.h"
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

	// Ordena objetos por profundidade
	ordenarObjetos(objetos, n_objetos);

	// Vetor para armazenar trechos ja cobertos
	const int MAX_SEG = 100;
	double ocupados[MAX_SEG][2];
	int n_ocupados = 0;

	// Percorre todos os objetos na ordem correta
	for (int i = 0; i < n_objetos; i++) {
		double ini = objetos[i].inicio();
		double fim = objetos[i].fim();
		bool visivel = true;

		// Verifica se esta completamente coberto
		for (int j = 0; j < n_ocupados; j++) {
			if (ini >= ocupados[j][0] && fim <= ocupados[j][1]) {
				visivel = false;
				break;
			}
		}

		if (visivel) {
			// Ajusta se estiver parcialmente coberto
			for (int j = 0; j < n_ocupados; j++) {
				if (ini < ocupados[j][1] && fim > ocupados[j][0]) {
					if (ini < ocupados[j][0]) fim = ocupados[j][0];
					else ini = ocupados[j][1];
				}
			}

			// Adiciona trecho visivel
			if (ini < fim) {
				cena.adicionarVisivel(objetos[i].getId(), ini, fim);
				ocupados[n_ocupados][0] = ini;
				ocupados[n_ocupados][1] = fim;
				n_ocupados++;
			}
		}
	}

	// Imprime a cena com 2 casas decimais
	cena.imprimir();
}


int main() {
    string entrada;
    cin >> entrada;
	ifstream arquivo(entrada);
	
	if (!arquivo.is_open()) {
    cerr << "Erro: não foi possível abrir o arquivo " << entrada << endl;
    return 1;
}

	const int MAX_OBJ = 100;
    Objeto todos_objetos[MAX_OBJ];
    int n_objetos = 0;

	char comando;

	while (arquivo >> comando) {
		switch (comando) {
		case 'O': {
			int id;
			double x, y, largura;
			arquivo >> id >> x >> y >> largura;
			todos_objetos[n_objetos++] = Objeto(id, x, y, largura);
			break;
		}

		case 'M': {
			int tempo, id;
			double x, y;
			arquivo >> tempo >> id >> x >> y;

			// procura o objeto e move
			for (int i = 0; i < n_objetos; i++) {
				if (todos_objetos[i].getId() == id) {
					todos_objetos[i].alteraxy(x, y);
					break;
				}
			}
			break;
		}

		case 'C': {
			int tempo;
			arquivo >> tempo;
			geraCena(todos_objetos, n_objetos, tempo);
			break;
		}

		default:
			cerr << "Comando invalido: " << comando << endl;
			break;
		}
	}

	arquivo.close();
	return 0;
}