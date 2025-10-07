#include <iostream>
#include <fstream>
#include <string>
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

	// Vetor para armazenar trechos ja cobertos (oclusos)
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

			// Adiciona trecho visC-vel
			if (ini < fim) {
				cena.adicionarVisivel(objetos[i].getId(), ini, fim);
				ocupados[n_ocupados][0] = ini;
				ocupados[n_ocupados][1] = fim;
				n_ocupados++;
			}
		}
	}

	// Imprime a cena formatada (2 casas decimais)

	cena.imprimir();
}



int main(int argc, char* argv[]) {
	if (argc < 2) {
		cerr << "Uso: " << argv[0] << " <arquivo_de_entrada>" << endl;
		return 1;
	}

	ifstream arquivo(argv[1]);
	if (!arquivo.is_open()) {
    cerr << "Erro: não foi possível abrir o arquivo " << argv[1] << endl;
    return 1;
}

	int n_objetos = 0;
	int capacidade = 10;
	Objeto* todos_objetos = new Objeto[capacidade]; // vetor dinamico que guarda os objetos

	char comando;

	while (arquivo >> comando) {
		switch (comando) {
		case 'O': {
			int id;
			double x, y, largura;
			arquivo >> id >> x >> y >> largura;

			if (n_objetos >= capacidade) {
				int novaCap = capacidade * 2;
				Objeto* novoVet = new Objeto[novaCap];
				for (int i = 0; i < n_objetos; i++)
					novoVet[i] = todos_objetos[i];
				delete[] todos_objetos;
				todos_objetos = novoVet;
				capacidade = novaCap;
			}

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
			cerr << "Comando invC!lido: " << comando << endl;
			break;
		}
	}

	arquivo.close();
	delete[] todos_objetos; // libera memoria
	return 0;
}
