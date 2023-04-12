# "Hello, World!" en C
En este trabajo práctico aprendemos cómo escribir un programa que imprima "Hola Mundo!" en la pantalla y escribir esa cadena en un archivo "output.txt"
También aprendemos a usar el repositorio GIT.

Objetivos:
- Demostrar capacidad para editar, compilar, y ejecutar programas C mediante el
desarrollo de un programa simple.
- Tener un primer contacto con las herramientas necesarias para abordar la resolución
de los trabajos posteriores

Temas: 
- Sistema de control de versiones.
- Lenguaje de programación C.
- Proceso de compilación
- Pruebas.

## Datos 
- Número de equipo: 5
- Autores de la resolución: Dimitri Isakow
- Usuario github: haytham2597
- Legajo: 164.780-5
- Apellido: Isakow
- Nombre: Dimitri
- Número y título del trabajo: 00-CHelloworld
- Compilador: MSVC v142
- IDE: Visual Studio 2022

## Introducción [Código completo](https://github.com/haytham2597/SSL/blob/master/00-CHelloworld/hello.c)
- Crear proyecto llamado "00-CHelloworld", crear repositorio público y publicarlo.
- Agregar readme.md que actúe como frontpage en el repositorio público y en las carpetas de los trabajos prácticos
Pasos desarrollados en el programa: 
Crear un programa que imprima una cadena y guardar la cadena en un archivo.
1. Escribimos un programa e incluímos las bibliotecas que necesitamos, en este caso:
```c
#include <stdio.h>
#include <stdlib.h>
```
2. Luego el bloque main
```c
int main(int argc, char *argv[])
{
}
```
### Dentro del bloque main agregamos los siguientes códigos
3. Creamos una variable y le llamamos hello
```c
const char *hello = "Hola Mundo!"
printf("%s", hello); //Imprimimos
return 0;
```
A esta altura, compilamos para comprobar el funcionamiento correcto del programa y la salida esperada. 

4. Creamos la variable fptr, especificamos la ruta a crear el archivo "output.txt", escribimos y lo cerramos
```c
FILE* fptr = fopen("output.txt", "w");
if(fptr == NULL) //ups no puede crear un archivo para escribir
{
  printf("Error el programa no puede crear un archivo");
  return 1; //Sistema de código de error. 1 = ERROR_INVALID_FUNCTION.
}
fprintf(fptr, "%s", hello); //Escribo el contenido de la variable hello en el archivo "output.txt"
if(fclose(fptr) == EOF) //Cierro el flujo del archivo y se vacían todos los búferes
{
  printf("El programa no pudo cerrar el flujo del archivo");
  return 1;
}
return 0;
```
Volvemos a compilar y FIN. El programa funciona correctamente.
### Resultado:
1. Imprime la cadena en la pantalla
2. Crea un archivo txt, lo escribe en él y lo guarda
