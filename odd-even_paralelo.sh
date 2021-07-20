#!/bin/bash

rm times/time_of_odd-even_paralelo.txt
rm bin/odd-even_paralelo

#Compilação de Código. 
mpicc -g -Wall src/odd-even_parallel.c -o bin/odd-even_paralelo

#Loop principal de execuções. 
	tentativas=5 #Quantas vezes o código será executado dado um par (cores,size)

	for cores in 2 4 8 #números de cores utilizados
	do
			for size in 120000 150000 180000 210000 #tamanho do problema
			do   	
				echo -e "\n$cores\t$size\t\t\c" >> "times/time_of_odd-even_paralelo.txt" 
				timer=0
				for tentativa in $(seq $tentativas) #Cria uma vetor de 1 a "tentativas"
				do
					#Executar o código.
					valor=`mpirun -np  $cores --oversubscribe ./bin/odd-even_paralelo $size`
					#echo $valor
					timer=$((valor+timer))

				done
				echo -e `echo "scale=2;${timer}/100/${tentativas}"|bc` >> "times/time_of_odd-even_paralelo.txt"
			done

	done
	
	exit 

exit
