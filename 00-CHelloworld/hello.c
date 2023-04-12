#define _CRT_SECURE_NO_WARNINGS //Defino esto para poder utilizar el fopen, sino tengo que utilizar la función fopen_s para su seguridad
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	const char* hello = "Hola mundo!";
	printf("%s", hello);

	FILE* fptr = fopen("output.txt", "w"); //El segundo argumento "w" (write) crea un archivo vacío para escribirlo, si el archivo ya existe borra todo su contenido y lo escribe.
	if (fptr == NULL) //ups no puede crear un archivo para escribir
	{
		printf("Error el programa no puede crear un archivo");
		return 1; //Sistema de código de error. 1 = ERROR_INVALID_FUNCTION.
	}
	fprintf(fptr, "%s", hello); //Escribo el contenido de la variable hello en el archivo "output.txt"
	if (fclose(fptr) == EOF) //Cierro el flujo del archivo y se vacían todos los búferes si la salida de esta función es igual a EOF significa que hubo un error
	{
		printf("El programa no pudo cerrar el flujo del archivo");
		return 1;
	}
	return 0; //ERROR_SUCCESS, es decir la operación se completó con éxito.
}
