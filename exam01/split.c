/*----------------------------------------------------------------
*
* Programación avanzada: Examen 01
* Fecha: Marzo 8, 2021
* Autor:
			Martin Noboa - A01704052
*
*--------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <math.h>
#include <sys/types.h>



int main(int argc, char* argv[]) {
	int origen;

	//chequear  numero de parametros
	if (argc != 3 ){
		printf("usage: %s source size\n", argv[0] );
		return -1;
	}

	//chequear que existe archivo origen
	if ((origen = open(argv[1], O_RDONLY)) < 0 ){
		printf("%s: No such file or directory\n", argv[0]);
		return -2;
	}

	//revisar valor del segundo argumento
	if(atoi(argv[2]) <= 0){
		printf("%s: size must be a positive number greater than zero\n", argv[0]);
		return -3;
	}

	//agarrar el valor del split
	int split = atoi(argv[2]);
	// determinar la longitud del archivo origen
	unsigned long size = lseek(origen,0,SEEK_END);
	lseek(origen, 0, SEEK_SET);
	//crear buffer con el tamaño maximo del split
	unsigned char *buffer = (unsigned char*) malloc(sizeof(unsigned char)* split);

	/*
	* en un while loop, leemos la cantidad de bytes en split y las guardamos en un archivo
	* con lseek (seek_cur) avanzamos el apuntador la misma cantidad de bytes
	* continuamos hasta que no haya bytes por leer

	* incluimos un if despues de cada lectura donde comprobamos si los bytes por leer son mayores
	* a split o si debemos cambiar el valor de split para no leer  de mas
	*/

	double max = ceil(size/split) + 1;
	printf("%s: generating files ", argv[0]);
	for (int i = 0; i < max ; i++){
		int file;
		//printf("%li %i %f\n", size,split, max);
		char  arch[] = "archivo0x.txt";

		arch[7] = i - (i%10) + '0';
		arch[8] = i%10 + '0';
		//printf("%s \n", arch);
		size -= split;

		file = creat(arch,0666);
		read(origen, buffer, split);
		write(file, buffer, split);
		close(file);
		printf(" %s ", arch);

	}



	free(buffer);
	close(origen);

	return 0;
}
