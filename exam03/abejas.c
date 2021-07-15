/*----------------------------------------------------------------
*
* Programación avanzada: Examen 03
* Fecha creacion: Mayo 24, 2021
* Fechas edicion:
* Autor:
			Martin Noboa - A01704052
*
* Ejemplo:
*		gcc abejas.c numeroAbejas numeroPorciones
*--------------------------------------------------------------*/

#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/wait.h>

int numeroAbejas;
int numeroPorciones;
int porciones;
sem_t mutex;
int contador = 0;

void poteLleno();
void llenarPote();
void vaciarPote();


int main(int argc, char* argv[]){
	int pid;
	sem_init(&mutex,0,1);

	if (argc != 3){
		fprintf(stderr, "usage: %s numeroAbejas numeroPorciones\n", argv[0]);
		return -1;
	}
	numeroAbejas = atoi(argv[1]);
	numeroPorciones = atoi(argv[2]);

	if (numeroAbejas < 1){
		printf("Numero de abejas debe ser mayor a 1\n");
		return -2;
	}
	if (numeroPorciones < 1){
		printf("Numero de porciones debe ser mayor a 1\n");
		return -3;
	}

	for (int i = 0; i < numeroAbejas; i++){
		if((pid = fork())<0){
			perror("Error al crear el proceso hijo");
			exit(-4);
		}else if(pid == 0){
			printf("Abeja %i esta recolectando miel... \n", getpid());
			llenarPote();
		}
	}

	return 0;
}


void llenarPote(){
	if (contador != numeroPorciones){
		sem_wait(&mutex);
		contador++;
		printf("Se esta llenando el pote...\n" );
		poteLleno();
		sem_post(&mutex);
	}

}

void poteLleno(){

	while(1){
		if (contador == numeroPorciones){
			sem_wait(&mutex);
			printf("El pote ya se lleno\n");
			vaciarPote();
		}
	}
}

void vaciarPote(){
	contador = 0;
	printf("El oso se comio todo el pote de miel...\n");
	printf("Las abejas vuelven a trabajar...\n");
}
