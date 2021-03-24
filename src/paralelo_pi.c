/*  Calculo de Pi - Método de Monte Carlo - Código Paralelo 
	Leandro S Ferreira Jr */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <sys/time.h>
#include <mpi.h>

int main (int argc, char* argv[]) {
	
	struct timeval comeco, final; //Struct timeval para calcular o tempo de execução
	double x,y,raio,valorpi;
	int size, pdentro=0, pdentrolocal=0;
	int threads,rank;
	
	size = atoi(argv[1]); //atoi converte a string de argv que recebe o tamanho n em inteiro
	srand(time(NULL)); //Função rand usando time para randomizar os valores

	MPI_Init(NULL,NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &threads);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	gettimeofday(&comeco, NULL); //Mede o tempo inicial 

	for (int i=0; i < size/threads; i++) {
      //Calculo de Pi
      x = (double)rand() / RAND_MAX; //Gera x entre 0 e 1
      y = (double)rand() / RAND_MAX; //Gera y entre 0 e 1
      raio = sqrt(x*x + y*y);    	
    	
    	if (raio<=1) { 
    		pdentrolocal++;  //Verifica se o ponto está dentro e salva na variável local da thread
    	}
    }

    MPI_Reduce(&pdentrolocal, &pdentro, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD); //Reduz o resultado das threads à pdentro

	if(rank==0) {
    	
    	valorpi=((double)pdentro/size)*4; //Calcula Pi			
		
		gettimeofday(&final, NULL); //Mede o tempo final
		printf("Size %d PI %.10f \n", size, valorpi); //Imprime o valor de Pi em paralelo_pi.out

		char saida[] = "paralelo_pi.txt"; 
		FILE *fp;	    							
		fp = fopen(saida, "a");    //Abre o arquivo txt
	    
		if (fp == NULL) {   	
	    	exit(1);
		} 
		else {		
			fprintf(fp, "%.3f\t", (final.tv_sec+final.tv_usec*1e-6)-(comeco.tv_sec+comeco.tv_usec*1e-6)); //Salva o tempo de execução na tabela 
	    	fclose(fp);
		}
	}

	MPI_Finalize (); 
	return 0;
}