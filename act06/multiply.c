/*----------------------------------------------------------------
*
* Programación avanzada: Manejo de multihilos
* Fecha: Mayo 20, 2021
* Autor:
			Samuel Octavio Gonzalez - A01704696
			Martin Noboa - A01704052
*
* Ejemplo:
*		mutiply -a matrix_file_a.txt -b matrix_file_b.txt -t thread_amount
*--------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <fcntl.h>
#include <pthread.h>
float ** A;
float ** B;
float ** RESULT;
int numHilos, maxA, maxB;

void * multiplicar (void * param){
	int i,j,k;
	long id = (long) param;
	int row_thread = maxA/numHilos;
	int start = id * row_thread;
	int end = (id+1) * row_thread;

	for (i = start; i < end; i++){
		for(j=0;j<maxA;j++){
    		for(k=0;k<maxB;k++){
      			RESULT[i][j] += A[i][k]*B[k][j];
    		}
		}
	}
}

void imprimir_matrix(){
  	for(int i = 0; i < maxA; i++){
		for(int j = 0; j < maxA; j++){
        	printf("%f ", RESULT[i][j]);
      	}
      	printf("\n");
   }
}


int main(int argc, char* argv[]) {
	int a,b;

	//verificar numero de parametros (8)
	if (argc != 7){
		fprintf(stderr, "usage: %s -a matrix_file_a.txt -b matrix_file_b.txt -t thread_amount\n", argv[0]);
		return -1;
	}
	/*
	* Verificar que sean parametros correctos (-a,-b,-t)
	* -a -= -3
	* -b = -4
	* -t = -5
	*/
	//printf("%s %s %s \n", argv[1],argv[3],argv[5]);

	if(strcmp(argv[1] , "-a") != 0 ){
		fprintf(stderr, "Error -3\n");
		return -3;
	}
	if(strcmp(argv[3] , "-b") != 0 ){
		fprintf(stderr, "Error -4\n");
		return -4;
	}
	if(strcmp(argv[5] , "-t") != 0 ){
		fprintf(stderr, "Error -5\n");
		return -5;
	}
	/*
	*Checar que los archivos existan y no estan vacios
	* -a = -6
	* -b = -7
	*/
	FILE* fileA;
	FILE* fileB;
	fileA = fopen(argv[2] , "r");
	if (fileA == NULL){
		perror("fopen");
		return -6;
	}
	fileB = fopen(argv[4] , "r");
	if (fileB == NULL){
		perror("fopen");
		return -7;
	}
	//obtener tamaño de los archivos A y B
	fscanf(fileA, "%i", &maxA);
	fscanf(fileB, "%i", &maxB);
	//verificar -t es mayor a 0 = -8
	numHilos = atoi(argv[6]);
	if (numHilos < 1){
		fprintf(stderr, "Error -8\n");
		return -8;
	}
	//verificar que el tamaño de las matrices son iguales -9
	if (maxA != maxB){
		fprintf(stderr, "Error -9\n");
		return -9;
	}


	//declarar memoria para matrices A, B y Resultados
	int j;
	long i;
	A = malloc(maxA*sizeof(float*));
	 for(i=0;i<maxA;i++)
	   A[i]=malloc(maxA*sizeof(float));

 	B = malloc(maxB*sizeof(float*));
	 for(i=0;i<maxB;i++)
	   B[i]=malloc(maxB*sizeof(float));

 	RESULT =  malloc(maxA*sizeof(float*));
	for(i=0;i<maxA;i++){
		RESULT[i]=malloc(maxA*sizeof(float));
	}


	for(i = 0; i < maxA; i++){
    	for(j = 0; j < maxA; j++){
			fscanf(fileA, "%f", &A[i][j]);
      }
   }
   for(i = 0; i < maxB; i++){
	   for(j = 0; j < maxB; j++){
		   fscanf(fileB, "%f", &B[i][j]);
	 }
  }

	pthread_t tid[numHilos];


	for (i = 0; i < numHilos; i++) {
      pthread_create(&tid[i], NULL,multiplicar, (void*) i );
    }
    for (i = 0; i < numHilos; i++) {
  		pthread_join(tid[i], NULL);
  	}

	imprimir_matrix();


	//liberar memoria del buffer y cerrar archivos
	free(A);
	free(B);
	free(RESULT);
	fclose(fileA);
	fclose(fileB);

	pthread_exit(NULL);
	return 0;
}
