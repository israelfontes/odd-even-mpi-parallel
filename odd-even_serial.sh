#!/bin/bash

rm times/time_of_odd-even_serial.txt
rm bin/odd-even_serial

#Compilação de Código.
gcc -g -Wall src/odd-even_serial.c -o bin/odd-even_serial

#Loop principal de execuções.
	tentativas=5 #Quantas vezes o código será executado dado um par (cores,size)

		for size in 120000 150000 180000 210000 #tamanho do problema
		do   	
			echo -e "\n$size\t\t\c" >> "times/time_of_odd-even_serial.txt" 

			timer=0
			for tentativa in $(seq $tentativas) #Cria uma vetor de 1 até "tentativas"
			do
				#Executar o código.
				valor=`./bin/odd-even_serial $size`
				#echo $valor
				timer=$((valor+timer))
			done

			echo -e `echo "scale=2;${timer}/100/${tentativas}"|bc` >> "times/time_of_odd-even_serial.txt" 
		done

exit
