#!/bin/bash

#SBATCH --partition=test
#SBATCH --job-name=paralelo_pi
#SBATCH --output=paralelo_pi.out
#SBATCH --error=paralelo_pi.err
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=32
#SBATCH --time=0-0:30
#SBATCH --hint=compute_bound
#SBATCH --exclusive

##Carrega as variáveis do sistema (compilador, etc)
rm paralelo_pi.txt
module load compilers/gnu/7.3
module load compilers/intel/2018.2.199
eval $loadIntelLibs

#Compila o código
mpiicc paralelo_pi.c -o paralelo_pi -lm

	tentativas=20 #Quantas vezes o código será executado
	
	for cores in 2 4 8 16 32 #números de cores utilizados
	do
		for size in 100000000 200000000 400000000 800000000 #tamanho do problema			
		do   									
			echo -e "\n$cores\t$size\t\t\c" >> "paralelo_pi.txt" 
				
			for tentativa in $(seq $tentativas) #Cria uma vetor de 1 a "tentativas"				
			do
				echo -e `srun -n $cores ./paralelo_pi $size`	#MPI usando somente $cores como número de processos e $size como tamanho da matriz							
			done			
		done
	done

exit 
