#!/bin/bash

#SBATCH --partition=test
#SBATCH --job-name=serial_pi
#SBATCH --output=serial_pi.out
#SBATCH --error=serial_pi.err
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=32
#SBATCH --time=0-0:30
#SBATCH --hint=compute_bound
#SBATCH --exclusive

#Carrega os módulos do sistema
rm serial_pi.txt
module load compilers/gnu/7.3
module load compilers/intel/2018.2.199
eval $loadIntelLibs	

#Compilando o código
gcc serial_pi.c -o serial_pi -lm

tentativas=20 #Quantas vezes o código será executado
				
	for size in 100000000 200000000 400000000 800000000 #tamanho do problema			
	do   									
		echo -e "\n$size\t\t\c" >> "serial_pi.txt" 
			
		for tentativa in $(seq $tentativas) #Cria uma vetor de 1 a "tentativas"				
		do
			echo -e `./serial_pi $size`								
		done			
	done

exit 


