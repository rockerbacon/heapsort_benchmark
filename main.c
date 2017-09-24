#include <stdio.h>
#include <papi.h>
#include "heapsort.h"

#define TESTE_DIM_INICIO	10
#define TESTE_DIM_FIM		30
#define Neventos 3
#define ARQUIVO "heapsortResult.txt"

int main (void) {

	unsigned int i, k;
	double tempoSegundos, dadosSegundos;
	long long int *ciclos, *flops, *flips;
	long long int tamanho;

	int eventos[Neventos] = { PAPI_FP_OPS, PAPI_FP_INS, PAPI_TOT_CYC };
	long long int SaidaEvento[Neventos];

	FILE *saida = fopen(ARQUIVO, "w");

	Vetor vetor;

	PAPI_library_init(PAPI_VER_CURRENT);

	time_t tempo;
	srand((unsigned)time(&tempo));
	
	printf("-------------HEAPSORT---------------\n");
	fprintf(saida, "-------------HEAPSORT---------------\n");

	flops = &SaidaEvento[0];
	flips = &SaidaEvento[1];
	ciclos = &SaidaEvento[2];

	for(i = TESTE_DIM_INICIO, tamanho = 1<<TESTE_DIM_INICIO; tamanho <= 1<<TESTE_DIM_FIM; i++, tamanho <<= 1 ) {
				
		fprintf(stderr, "\rRodando Ordenacao de Tamanho: 2^%u = %lld Kb", i, tamanho/1024);
		
		Vetor_init(&vetor, tamanho/sizeof(long));

		for (k = 0; k < tamanho/sizeof(long); k++) {
			vetor.valor[k] = -1*k;
		}
	
		//Vetor_print(stdout, &vetor, '\n');
		PAPI_start_counters(eventos, Neventos);
		tempo = PAPI_get_real_usec();

		heapsort(&vetor);

		tempo = PAPI_get_real_usec() - tempo;
		//Vetor_print(stdout, &vetor, '\0');
		PAPI_stop_counters(SaidaEvento, Neventos);
	
		tempoSegundos = (double)tempo/1000000;
		dadosSegundos = (double)tamanho/tempoSegundos/(1 << 20);
		
		fprintf(saida, "Tamanho: 2^%u = %lf kb\n", i, (double)tamanho/1024);
		fprintf(saida, "Dados por segundo: %lf Mb/s\n", dadosSegundos);
		fprintf(saida, "Tempo: %lf segundos\n", tempoSegundos);
		fprintf(saida, "Ciclos: %lld\n", *ciclos);
		fprintf(saida, "FLOPS: %lld\n", *flops);
		fprintf(saida,"FLIPS: %lld\n\n", *flips);
		fflush(saida);

		Vetor_free(&vetor);

	}
	
	fprintf (stderr, "\n");
	fclose(saida);
	PAPI_shutdown();

	return 0;

}
