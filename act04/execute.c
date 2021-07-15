/*----------------------------------------------------------------
*
* Programación avanzada: Manejo de señales
* Fecha: Abril 15, 2021
* Autor:
			Samuel Octavio Gonzalez - A01704696
			Martin Noboa - A01704052
*
*--------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <setjmp.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

//variables para leer los archivos
unsigned char *buffer1;
unsigned char *buffer2;
unsigned char *buffer3;

//strings para guardar los comandos de los archivos
unsigned char* comando1;
unsigned char* comandoCompleto1;
unsigned char* comando2;
unsigned char* comandoCompleto2;
unsigned char* comando3;
unsigned char* comandoCompleto3;

void sighandlerR1(){
	int pid;
	if ((pid = fork()) < 0){
		perror("Error creando proceso.");
		exit(-8);
	}else if(pid == 0 ){
		execlp(comando1,comandoCompleto1, NULL);
	}
}

void sighandlerR2(){
	int pid;
	if ((pid = fork()) < 0){
		perror("Error creando proceso.");
		exit(-9);
	}else if(pid == 0 ){
		execlp(comando2,comandoCompleto2, NULL);
	}
}

void sighandlerPWR(){
	int pid;
	if ((pid = fork()) < 0){
		perror("Error creando proceso.");
		exit(-10);
	}else if(pid == 0 ){
		execlp(comando3,comandoCompleto3, NULL);
	}
}

void sighandlerINT(){
	puts("Ending...");
	free(buffer1);
	free(buffer2);
	free(buffer3);
	exit(0);
}

int main(int argc, char* argv[]) {
	int f1,f2,f3;

	//verificar num de argumentos
	if (argc != 4){
		fprintf(stderr, "usage: %s file1 fil2 fil3\n", argv[0]);
		return -1;
	}

	//verificar que archivos existan
	if ((f1 = open(argv[1], O_RDONLY)) < 0){
		printf( "%s: the file %s does not exist.\n", argv[0],argv[1]);
		return -2;
	}
	if ((f2 = open(argv[2], O_RDONLY)) < 0){
		printf( "%s: the file %s does not exist.\n", argv[0],argv[2]);
		return -3;
	}
	if ((f3 = open(argv[3], O_RDONLY)) < 0){
		printf( "%s: the file %s does not exist.\n", argv[0],argv[3]);
		return -4;
	}

	//verificar si esta vacio
	if (lseek(f1,0,SEEK_END) == 0){
		printf( "%s: the file %s is empty.\n", argv[0],argv[1]);
		return -5;
	}
	if (lseek(f2,0,SEEK_END) == 0){
		printf( "%s: the file %s is empty.\n", argv[0],argv[2]);
		return -6;
	}
	if (lseek(f3,0,SEEK_END) == 0){
		printf( "%s: the file %s is empty.\n", argv[0],argv[3]);
		return -7;
	}

	//leer archivos
	//archivo 1 (f1)

	unsigned long  size1 = lseek(f1,0, SEEK_END);
	buffer1 = (unsigned char*) malloc(sizeof(unsigned char) * size1);
	lseek(f1,0, SEEK_SET);
	read(f1, buffer1,size1);
	comando1 = strtok(buffer1, "," );
	comandoCompleto1 = strtok(NULL, "," );
	//printf(" Comando 1 = %s Comando 1 completo =  %s\n", comando1 ,comandoCompleto1 );
	close(f1);

	unsigned long  size2 = lseek(f2,0, SEEK_END);
	buffer2 = (unsigned char*) malloc(sizeof(unsigned char) * size2);
	lseek(f2,0, SEEK_SET);
	read(f2, buffer2,size2);
	comando2 = strtok(buffer2, "," );
	comandoCompleto2 = strtok(NULL, "," );
	close(f2);

	unsigned long  size3 = lseek(f3,0, SEEK_END);
	buffer3 = (unsigned char*) malloc(sizeof(unsigned char) * size3);
	lseek(f3,0, SEEK_SET);
	read(f3, buffer3,size3);
	comando3 = strtok(buffer3, "," );
	comandoCompleto3 = strtok(NULL, "," );
	//printf(" Comando 3 = %s Comando 3 completo =  %s\n", comando3 ,comandoCompleto3 );
	close(f3);


	puts("Waiting for signal...");

	//manejador de señales
	signal(SIGUSR1, sighandlerR1);
 	signal(SIGUSR2, sighandlerR2);
 	signal(SIGPWR, sighandlerPWR);
	signal(SIGINT, sighandlerINT);

	while(1){
		pause();
	}

	return 0;
}
