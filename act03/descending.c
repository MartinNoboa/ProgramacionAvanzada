/*----------------------------------------------------------------
*
* Programación avanzada: Manejo de procesos
* Fecha: Abril 5, 2021
* Autor:
			Samuel Octavio Gonzalez - A01704696
			Martin Noboa - A01704052
*
*--------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void child_process(int level, int current) {
	int pid, time = 1;

	if (current == level) {
		sleep(time);
		for(int i=0;i<level;i++){
			printf("\t");
		}
		printf("PPID = %i PID = %i NIVEL = %i\n", getppid(), getpid(), current);
		exit(0);
	} else {
		for(int i=0;i<current;i++){
			printf("\t");
		}
        printf("PPID = %i PID = %i NIVEL = %i\n", getppid(), getpid(), current);

        for(int i=0; i < (current+1); i++){
            if ( (pid = fork()) < 0 ) {
                perror("recursive fork");
                exit(-4);
            } else if (pid == 0) {
                child_process(level,++current);
            } else {
                wait(NULL);
            }
        }
        exit(0);

	}
}

int main(int argc, char* argv[]) {
	int pid;
	// chequear num de argumentos
	if (argc != 2) {
		fprintf(stderr, "usage: %s number\n", argv[0]);
		return -1;
	}


	//chequear si parametro es numero positivo mayor a 0
	int num = atoi(argv[1]);
	//arg es num negativo
	if (num < 0){
		fprintf(stderr, "%s:  the parameter must be a positive integer number\n", argv[0]);
		return -2;
	}
		//arg es cero
	if(num == 0){
		fprintf(stderr, "%s: the parameter must be a positive integer number\n", argv[0]);
		return -2;
	}

 	//llamar funcion recursiva
	if ( (pid = fork()) < 0 ) {
		perror("recursive fork");
		exit(-4);
	} else if (pid == 0) {
		child_process(num, 1);
	} else{
		printf("PPID = %i PID = %i LEVEL = 0\n", getppid(), getpid());
		wait(NULL);
	}


	return 0;
}
