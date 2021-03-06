#ifndef VETOR_H
#define VETOR_H

#define swap(a, b) { long int aux_swap = a; a = b; b = aux_swap; }

#define CACHE_SIZE 16*1024

#include <stdio.h>
#include "bool.h"

/*DEFINICAO VETOR*/
typedef struct _Vetor {

	long int *valor;
	unsigned int n;

}Vetor;

/*OPERACOES VETOR*/
//inicializar vetor, retorna false em caso de erro durante alocacao de memoria
extern bool Vetor_init(Vetor *vetor, unsigned int n);

//liberar espaco alocado pelo vetor
extern void Vetor_free(Vetor *vetor);

//imprime vetor na saida desejada
//char c eh impresso apos o termino da impressao do vetor
extern void Vetor_print(FILE *saida, Vetor *vetor, char c);

#endif
