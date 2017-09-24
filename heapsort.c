#include "heapsort.h"

//ordenacao heapsort
void heapsort(Vetor *vetor) {

	if (vetor == NULL) {
		return;
	}else if (vetor->valor == NULL || vetor->n < 2){
		return;
	}

	unsigned int	filho,
			pai,
			aux,
			retorno,
			n;

	n = vetor->n;

	//build heap
	filho = 1;
	while (filho < vetor->n) {

		retorno = filho+1;
		pai = (filho-1)/2;

		while (vetor->valor[pai] < vetor->valor[filho]) {

			swap(vetor->valor[pai], vetor->valor[filho]);
			
			if (pai == 0) {
				break;
			}

			filho = pai;
			pai = (filho-1)/2;

		}

		filho = retorno;

	}
	//Vetor_print(stdout, vetor, '\n');

	while (n > 1) {

		//trocar elementos iniciais e finais do heap
		n--;
		swap(vetor->valor[0], vetor->valor[n]);

		//restaurar propriedade do heap
		pai = 0;
		filho = 1;
		while (filho < n) {

			if (vetor->valor[filho] > vetor->valor[pai]) {
				aux = filho;
			} else {
				aux = pai;
			}

			if (filho+1 < n) {
				if (vetor->valor[filho+1] > vetor->valor[aux]) {
					aux = filho+1;
				}
			}

			if (aux == pai) {
				break;
			}

			swap(vetor->valor[pai], vetor->valor[aux]);

			pai = aux;
			filho = 2*pai+1;

		}

	}

}
