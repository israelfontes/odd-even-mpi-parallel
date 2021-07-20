/**
* @file odd-even_serial.c
* @brief Dado um tamanho 'n' este programa cria um vetor de inteiros pseudoaleatórios com tal tamanho
*	e o ordena utilizando a técnica odd-even explorando o processamento serial.
* @author Israel Medeiros Fontes
* @since 23/10/2020
* @date 27/10/2020
*/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void odd_even_sort(int a[], int n){

	int phase, i, temp;

	for(phase = 0; phase < n; phase++){
		if(phase%2 == 0){
			for(i = 1; i<n; i+=2){
				if(a[i-1]>a[i]){
					temp = a[i];
					a[i] = a[i-1];
					a[i-1] = temp;
				}
			}
		}else{
			for (i = 1; i < n-1; i += 2){
				if(a[i]>a[i+1]){
					temp = a[i];
					a[i] = a[i+1];
					a[i+1] = temp;					
				}
			}
		}
	}
}

void write_vector_in_file(int vector[], int n){
	FILE * file;
	
	char file_name[30];

	sprintf(file_name, "data/vectors/%d", n);

	file = fopen(file_name,"wb");

	if(file != NULL){
		for(int i=0; i<n;i++)
			fwrite(&vector[i], sizeof(int), 1, file);
		fclose(file);
	}else{
		printf("ODD: Erro ao abrir arquivo.\n");
		exit(1);
	}
}

void read_vector_in_file(int vector[], int n){
	FILE * file;
	
	char file_name[30];
	sprintf(file_name, "../data/vectors/%d", n);
	
	file = fopen(file_name, "rb");

	if(file != NULL){
		
		int i = 0;

		while(1){
			int value;

			size_t re = fread(&value, sizeof(int), 1, file);

			if(re<1)
				break;
			else
				vector[i++] = value; 
		}
		fclose(file);
	}else{
		printf("Erro ao absrir arquivo.\n");
		exit(1);
	}
}

int main(int argc, char **argv){
	
	int n = atoi(argv[1]);;

	int *vector = malloc(sizeof(int)*n);

	for(int i = 0; i < n; i++)
		vector[i] = rand()%n;

	write_vector_in_file(vector,n);
	
	clock_t t;
	t = clock();
	
	odd_even_sort(vector,n);
	t = clock() - t;
	printf("%ld", (int)((double)t)/((CLOCKS_PER_SEC)/100));

	free(vector);

	return 0;
}