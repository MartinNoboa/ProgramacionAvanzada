/*----------------------------------------------------------------
*
* Programación avanzada: Manejo de semaforos
* Fecha creacion: Mayo 10, 2021
* Fechas edicion: Mayo 15, 2021
* Autor:
			Samuel Octavio Gonzalez - A01704696
			Martin Noboa - A01704052
*
* Ejemplo:
*		philosophers.c
*--------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <semaphore.h>

//numero de filosofos
#define N 5
//definir estados de filosofos
#define PENSANDO 0
#define HAMBRIENTO 1
#define COMIENDO 2


//declara mutex y arreglo de semaforos
sem_t mutex;
sem_t semaforo[N];

//declarar funciones para vecinos derecha e izquierda
int izq(int i){
    return i+4%N;
}
int der(int i){
    return i+1%N;
}

//declarar funciones para cada accion
void filosofos(int num);
//funcion para tomar los palillos
void tomar_palillos(int num);
//funcion para dejar los palillos
void dejar_palillos(int num);
//funcion para revisar estado de los vecinos
void checar_vecinos(int num);

//declarar arreglo de estados de los filosofos
int estados[N];
//declarar numero de filosofos
int filosofo[N] = {0,1,2,4};

int main(int argc, char* argv[]) {
    int pid;
    //inicializar semaforos
    sem_init(&mutex,0,1);
    for (int i = 0; i  < N; i++){
        sem_init(&semaforo[i],0,0);
    }

    //crear procesos hijo para cada filosofos
    for (int i = 0; i  < N; i++){
        if ( (pid = fork()) < 0 ) {
    		perror("Error al crear el proceso hijo");
    		exit(-1);
    	} else if (pid == 0) {
            printf("Filosofo %i esta pensando...\n",getpid() );
    		filosofos(filosofo[i]);
        }
	return 0;
    }
}

void filosofos(int num){
    for (int i = 0; i < N; i++){
        int i = num;
        sleep(1);
        tomar_palillos(i);
        sleep(0);
        dejar_palillos(i);
    }
}

void tomar_palillos(int num){
    sem_wait(&mutex);
    estados[num] = HAMBRIENTO;
    printf("Filosofo %i tiene hambre...\n",getpid() );
    checar_vecinos(num);
    sem_post(&mutex);
    sem_wait(&semaforo[num]);
    sleep(1);
}
void dejar_palillos(int num){
    sem_wait(&mutex);
    estados[num] = PENSANDO;
    printf("Filosofo %i termino de comer. Vuelve a pensar...\n", getpid() );
    checar_vecinos(izq(filosofo[num]));
    checar_vecinos(der(filosofo[num]));
    sem_post(&mutex);
}
void checar_vecinos(int num){
    //si estado es con hambre y vecino derecha e izquierda estan libres
    int posIzq = izq()
    if (estados[num] == HAMBRIENTO && estados[izq(filosofo[num])] != COMIENDO && estados[der(filosofo[num])] != COMIENDO){
        estados[num] = COMIENDO;
        sleep(2);
        printf("Filosofo %i esta comiendo tacos...\n", getpid() );
        sem_post(&semaforo[num]);
    }
}
