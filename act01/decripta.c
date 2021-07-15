/*----------------------------------------------------------------
*
* Programación avanzada: Manejo de archivos
* Fecha: Marzo 1, 2021
* Autor:
			Samuel Octavio Gonzalez - A01704696
			Martin Noboa - A01704052
*
*--------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>


int main(int argc, char* argv[]) {
	int origen, destino;
	//printf("%s %s %s", argv[0], argv[1],argv[2]);


	//chequear  numero de parametros
	if (argc != 3 ){
		printf("usage: %s origen destino\n", argv[0] );
		return -1;
	}

	//chequear que existe archivo origen
	if ((origen = open(argv[1], O_RDONLY)) < 0 ){
		perror(argv[0]);
		return -2;
	}

	//escribir, crear o truncar archivo destino
	if((destino = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666)) < 0 ){
		perror(argv[0]);
		return -3;
	}


	unsigned char *buffer;
	unsigned long  size = lseek(origen,0, SEEK_END);
	buffer = (unsigned char*) malloc(sizeof(unsigned char) * size);

	/*
	right >>         left <<
	a = 1100 0011
	a >> 4
	temp 1 = 0000 1100
	a << 4
	temp 2 = 0011 0000

	Guardar cada "mitad" en variables temporales
	Por si acaso, hacemos un AND con 240 o 15 ( 1111 0000 o 0000 1111) para quedarnos
	con los bits que queremos

	Realizamos un OR
	temp1 | temp2
	0000 1100
	0011 0000

	0011 1100

	*/

	lseek(origen,0, SEEK_SET);
	read(origen, buffer,size);

	for (int i = 0; i < size; i++){
		unsigned char temp1 = (buffer[i] & 240) >> 4;
		unsigned char temp2 = (buffer[i] &15)  << 4;
		buffer[i] = temp1 | temp2;
	}


	write(destino, buffer, size);
	printf("done\n");

	free(buffer);
	close(origen);
	close(destino);
	return 0;
}
