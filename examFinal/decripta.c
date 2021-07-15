/*----------------------------------------------------------------
*
* Programación avanzada: Examen final
* Fecha creacion:  Junio 14, 2021
* Autor:
			Martin Noboa - A01704052
* Descipcion:
* Programa decripta un archivo de texto reacomodando la secuencia de bits en un byte
* Ejemplo:
*		gcc decripta.c <archivoEntrada> <archivoSalida>
*--------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>


int main(int argc, char* argv[]){
	int origen, destino;

	//revisar numero de parametros recibidos
	if (argc != 3){
		printf("usage: %s origen destino\n", argv[0] );
		return -1;
	}

	//revisar si archivo origen existe
	if ((origen = open(argv[1], O_RDONLY)) < 0 ){
		perror(argv[0]);
		return -2;
	}

	//revisar si el archivo destino existe, se puede truncar o si se debe crear
	if((destino = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666)) < 0 ){
		perror(argv[0]);
		return -3;
	}

	//declarar buffer para leer archivo origen
	unsigned char *buffer;
	unsigned long  size = lseek(origen,0, SEEK_END);
	buffer = (unsigned char*) malloc(sizeof(unsigned char) * size);

	//leer archivo origen
	lseek(origen,0, SEEK_SET);
	read(origen, buffer,size);

	/**
	* Usando logica de bits, dividimos en 2 cada byte.
	* Hacemos un AND con 250 (1111 0000) y 15 (0000 1111) para los
	* 4 bits izquierdos y derechos respectivamente
	* Realizamos un OR con el resultado previo de cada mitad para completar el reacomodo
	* del byte
	*/
	for (int i = 0; i < size; i++){
		unsigned char izq = (buffer[i] & 240) >> 4;
		unsigned char der = (buffer[i] &15)  << 4;
		buffer[i] = izq | der;
	}
	
	write(destino, buffer, size);
	printf("done\n");



	//liberar memoria y cerrar archivos
	free(buffer);
	close(origen);
	close(destino);
	return 0;
}
