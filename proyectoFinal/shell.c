/*----------------------------------------------------------------
*
* Programación avanzada: Proyecto final
* Fecha creacion:  Junio 2, 2021
* Autor:
			Martin Noboa - A01704052
* Descipcion:
* Programa que corre un "mini shell". Recibe comandos o un archivo de texto con comandos
* Ejemplo:
*		gcc shell <argumentos>
*--------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>

#define MAX 512

void fileCommands(char *file);
void miniShell();
void getCommands(char *commands);
int runCommand(char *command);

int main(int argc, char* argv[]){
	int file;
	// Chequear numero de argumentos
	if (argc > 2){
		printf("usage: %s <archivo>\n", argv[0]);
		return -1;
	}else if(argc == 2){
		//verificar que el archivo exite
		if ((file = open(argv[1], O_RDONLY)) < 0){
			printf("Error al abrir el archivo %s.\n", argv[1]);
			return -2;
		}
		fileCommands(argv[1]);
	}else{
		miniShell();
	}



	close(file);
	return 0;
}

/*
===============================Funciones==============================
*/

/**
* Function: miniShell
* ----------------------------------------------------------------
* Espera el input del usuario para correr comandos
* @parameters: none
* @returns : 0 if succesfull
*/
void miniShell(){
	char command[MAX];
	bool quit = false;
	//esperar que el usuario ingrese comandos
	while(!quit){
		//tomar input del usuario
		fgets(command, MAX, stdin);
		//chequear si el comando es una linea de salto
		if(strcmp(command, "quit\n") == 0 || strcmp(command,"Quit\n") == 0){
			quit = true;
			break;
		}
		//Funcion para recuperar los comandos (en caso que sean mas de uno) y ejecutarlos en procesos hijos
		getCommands(command);
	}
	//Este exit es importante, en caso que se ingrese "quit" para salir del mini shell
	exit(0);
}

/**
* Function: fileCommands
* ----------------------------------------------------------------
* Lee y manda a ejecutar los comandos dentro del archivo de texto
* @parameters:
* 	file -> path del archivo
* @returns :
*/
void fileCommands(char *path){
	FILE * readFile = fopen(path, "r");
	char commands[MAX];
	bool quit = false;

	printf("\nLeyendo archivo %s....\n", path);
	//leer archivo linea por linea
	while(!quit){
		fgets(commands, sizeof(commands), readFile);

		//detener ejecucion si se encuentra con quit o Quit
		if(strcmp(commands, "quit\n") == 0 || strcmp(commands,"Quit\n") == 0){
			quit = true;
			break;
		}
		//llamar a la funcion getCommands para separar comandos en caso que haya mas de uno
		getCommands(commands);
		}
		printf("\nArchivo %s completado.\n", path);
		fclose(readFile);
		//Este exit es importante, en caso que se ingrese "quit" para salir del mini shell
		exit(0);
}


/**
* Function: getCommands
* ----------------------------------------------------------------
* Separa los comandos con ";" en lineas separadas
* @parameters:
* 	commands -> string del input del usuario
* @returns :
*/
void getCommands(char * commands){
	char * command;
	int pid;
	//separar en caso de salto de linea
	command = strtok(commands, "\n");
	//separar por puntos y comas
	command = strtok(commands,";");

	while(command != NULL){
		//crear proceso hijo
		if ((pid = fork()) == 0){
			runCommand(command);
			exit(0);
		}

			command = strtok(NULL,";");

	}
}

/**
* Function: runCommand
* ----------------------------------------------------------------
* Ejecuta comando
* @parameters:
* 	comando -> string que es el comando a ejecutar
* @returns :
* 	0 if succesfull
* 	-1 if error
*/
int runCommand(char *command){
	char *comando[255], *com;
	int i = 0;
	//convertir el string en un array para execvp
	com = strtok(command," ");
	if (com == NULL){
		printf("\nError: Comando no valido.\n" );
	}else{
		while(com != NULL){
			//recorremos el string y armamos un arreglo con los pipes
			//execvp espera un array donde el primer item es el comando a ejecutar
			comando[i] = com;
			i++;
			com = strtok(NULL," ");
		}
		comando[i] = NULL;
		int ejecutar = execvp(comando[0], comando);
		if(ejecutar == -1){
			printf("\nError al ejecutar el comando.\n");
			return -1;
		}

		return 0;
	}



}
