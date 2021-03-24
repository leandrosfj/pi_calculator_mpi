/*  Calculo de Pi - Método de Monte Carlo - Código Serial 
	Leandro S Ferreira Jr */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>

int main (int argc, char* argv[]) {
	
	struct timeval comeco, final;  //Struct timeval para calcular o tempo de execução
	double x,y,raio,valorpi;
	int cont, size, pdentro=0;
	srand(time(NULL));  //Função rand usando time para randomizar os valores
	size = atoi(argv[1]); //atoi converte a string de argv que recebe o tamanho n em inteiro
	

	gettimeofday(&comeco, NULL); //Mede o tempo inicial 

	for (int i=0; i<size; i++) {
      
    	x = (double)rand() / RAND_MAX; //Gera x entre 0 e 1
    	y = (double)rand() / RAND_MAX; //Gera y entre 0 e 1
    	raio = sqrt(x*x + y*y);
    	
    	if (raio<=1) { 
    		pdentro++;  //Verifica se o ponto está dentro e salva na variável local da thread
    	}
    }

    valorpi=((double)pdentro/size)*4;	    //Calcula Pi

    
	gettimeofday(&final, NULL); //Mede o tempo final
	printf("Size %d PI %.10f \n", size, valorpi); //Imprime o valor de Pi em serial_pi.out

	char nomedoarquivo[] = "serial_pi.txt";
    FILE *fp;  
    fp = fopen(nomedoarquivo, "a");    //Abre o arquivo txt
    
    if (fp == NULL) {
      exit(1);
    }
	else {
		fprintf(fp, "%.3f\t", (final.tv_sec+final.tv_usec*1e-6)-(comeco.tv_sec+comeco.tv_usec*1e-6)); //Salva o tempo de execução na tabela
    	fclose(fp);
	}

	return 0;
}