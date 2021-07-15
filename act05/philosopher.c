#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/wait.h>


#define N 5
#define THINKING 0
#define HUNGRY 1
#define EATING 2


sem_t mutex;
sem_t semaforo[N];

int left(int i){

	return (i+4)%N;
}

int right(int i){

	return (i+1)%N;
}

void filosofos(int num);

void tomarPalillos(int num);

void dejarPalillos(int num);

void test(int);

int estados[N];
int filosofo[N]={0, 1, 2, 3, 4};


int main(){

	int pid;

	sem_init(&mutex,0,1);

	for(int i=0; i < N; i++){
		sem_init(&semaforo[i],0,0);
	}

	for(int i=0; i < N; i++){
		if((pid = fork())<0){
			perror("Error al crear el proceso hijo");
			exit(-1);
		}else if(pid == 0){
			printf("Filosofo %i esta pensando... \n", getpid());
			filosofos(filosofo[i]);
		}
	}


	return 0;

}

void filosofos(int num){

		for(int i=0; i<2; i++){
			int i = num;
			sleep(1);
			tomarPalillos(i);
			sleep(0);
			dejarPalillos(i);
		}
}

void tomarPalillos(int num){

	sem_wait(&mutex);
	estados[num]= HUNGRY;
	printf("Filosofo %i tiene hambre... \n", getpid());
	test(num);
	sem_post(&mutex);
	sem_wait(&semaforo[num]);
	sleep(1);
}

void dejarPalillos(int num){

		sem_wait(&mutex);
		estados[num]=THINKING;
		printf("Filosofo %i termino de comer. Vuelve a pensar .. \n", getpid());
		test(left(filosofo[num]));
		test(right(filosofo[num]));
		sem_post(&mutex);



}

void test(int num){

	if(estados[num] == HUNGRY && left(filosofo[num]) != EATING && right(filosofo[num]) != EATING ){
		estados[num] = EATING;
		sleep(2);

		printf ("Filosofo %i esta comiendo tacos.. \n", getpid());
		sem_post(&semaforo[num]);
	}

}
