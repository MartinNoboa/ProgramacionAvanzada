/*----------------------------------------------------------------
*
* Programación avanzada: Examen 02
* Fecha: Abril 19, 2021
* Autor:
			Martin Noboa - A01704052
* Descipcion:
			Elimina todas las ocurrencia de una palabra  <palabra>
			en el contenido de todos y cada uno de los archivos regulares que existen en un directorio.
* Uso:
			censure <palabra> processes <dir>
*
*--------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <wait.h>
#include <fcntl.h>


void list(char* dir_name, char* program,  char * word, int processes);
void delete(char *name, char *directory, char *word);

int main(int argc, char* argv[]) {
	char dir_name[PATH_MAX + 1];
	char *directory;


	//chequear numero de argumentos
	if (argc < 3 || argc > 4){
		fprintf(stderr, "usage: %s word processes [directory]\n", argv[0]);
		return -1;
	}

	//revisar si num de procesos es numero positivo mayor a 1
	int processes = atoi(argv[2]);
	if(processes <= 1){
		printf("%s: the number of processes must be greater than 1.\n", argv[0]);
		return -3;
	}

	getcwd(dir_name, PATH_MAX);
	directory = dir_name;

	//si recibe el directorio
	if (argc == 3){
		directory = argv[4];
	}

	list(directory,argv[0] ,argv[1], processes);
	return 0;
}


void list(char *dir_name, char* program ,char *word, int processes) {
	char path[PATH_MAX + NAME_MAX + 1];
	DIR *dir;
	struct dirent *direntry;
	struct stat info;
	int pid;

	if ( (dir = opendir(dir_name)) == NULL ) {
		perror(program);
		exit(-2);
	}

	while( (direntry = readdir(dir)) != NULL) {
		if(strcmp(direntry->d_name,".") != 0 && strcmp(direntry->d_name,"..") != 0){
			lstat(path, &info);
			for(int i = 0; i < processes; i++){
					if((pid = fork()) < 0 ){
						perror("Error al crear el hijo.");
					}else if(pid == 0){

							delete(direntry->d_name,dir_name,word);
						}
			}
		}

	}




	closedir(dir);
	//printf("\n");
}

void delete(char *name, char *directory, char *word) {
	struct stat info;
	char filename[PATH_MAX + NAME_MAX + 1];
	int match = 0, archivo;
	lstat(filename, &info);

	printf("create a child %i => %s", getpid(), directory);

	//buscar la palabra
	if ((archivo = open(filename, O_RDONLY)) < 0 ){
		printf( "Error al abrir el archivo\n");
		exit(-2);
	}
	close(archivo);

}
