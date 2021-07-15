/*----------------------------------------------------------------
*
* Programación avanzada: Manejo de directorios
* Fecha: Marzo 18, 2021
* Autor:
			Samuel Octavio Gonzalez - A01704696
			Martin Noboa - A01704052
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
#include <pwd.h>
#include <grp.h>

void list(char* dir_name, int recursive, char* program, char * find);
void get_info(char *name, char *directory, char *program, char * find);

int main(int argc, char* argv[]) {

	char dir_name[PATH_MAX + 1];
	char *directory;
	int recursive;

	// chequear numero de parametros
	if (argc < 3 || argc > 4){
		fprintf(stderr, "usage: %s [-r] [directory]\n", argv[0]);
		return -1;
	}
	//asignar el nombre del directorio a la variable
	directory = argv[2];

	//comprobar si es recursivo
	if (argc == 3){
		recursive = 0;
	}else if(argc == 4){
		if( strcmp(argv[3], "-r") != 0){
			fprintf(stderr, "usage: %s [-r] [directory]\n", argv[0]);
			return -3;
		}
		recursive = 1;
	}

	list(directory, recursive, argv[0], argv[1] );
	return 0;
}



void list(char *dir_name, int recursive, char *program, char* find) {
	char path[PATH_MAX + NAME_MAX + 1];
	DIR *dir;
	struct dirent *direntry;
	struct stat info;

	if ( (dir = opendir(dir_name)) == NULL ) {
		perror(program);
		exit(-2);
	}

	while( (direntry = readdir(dir)) != NULL) {
		get_info(direntry->d_name, dir_name, program, find);
	}
	if (recursive) {
		rewinddir(dir);
		while ( (direntry = readdir(dir)) != NULL ) {
			if (strcmp(direntry->d_name, ".") != 0 &&
			    strcmp(direntry->d_name, "..") != 0) {

				sprintf(path, "%s/%s", dir_name, direntry->d_name);
				lstat(path, &info);
				if ( (info.st_mode & S_IFMT) == S_IFDIR) {
					list(path, recursive, program,find);
				}
			}
		}
	}
	closedir(dir);
	//printf("\n");
}

void get_info(char *name, char *directory, char *program, char * find) {
	struct stat info;
	char filename[PATH_MAX + NAME_MAX + 1];

	sprintf(filename, "%s",  name);
	lstat(filename, &info);

	if (strstr(filename, find) != NULL){
		//imprimir path del archivos
		printf("Name:%s\n",filename);
		printf("Path:%s\n\n", directory);
	}
}
