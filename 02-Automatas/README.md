# "Automatas" en C
Trabajo prático N°2, en este TP aprendemos a comprobar el tipo de cadena; nada, octal, decimal o hexadecimal. En caso de ser decimales y tener operaciones aritméticas realizamos cálculo de la misma y recibimos su resultado.
Sumado a todo esto también contamos la cantidad de grupos correctos que existen.

## Integrantes
| Nombre & Apellido | Nro. Legajo |
| --- | --- |
| Dimitri Isakow | 164.780-5 |
| Nahuel Alejandro García | 208.997-0 |
| Martín Gonzalo Larrart | 209.042-9 |
| Pedro Jose Nicolas Alvarez | 177.232-6 |

# Introducción 
Para la resolución de operaciones aritméticas en una cadena es necesario pasar la notación `infija` a notación `polaca inversa` la idea se sacó de la guía teórica de `Matemática Discreta Unidad 9 página 129`

<details open>
  <summary>Funciones esenciales</summary>
Instanciamos un arreglo de 4 operadores, los números provienen de la tabla ASCII [^1] donde cada char pertenece un entero sin signar de 8 bit (0-255) 
[^1]: https://elcodigoascii.com.ar/
```c
int operators[] = { 42,47,45,43 }; 
```

## Cabeceras
```c
enum TipoDeCadena { none, octal, decimal, hexadecimal };
int char_to_int(char ch);
int is_operator(int ascii);
int is_possible_calculate(const char* eq); 
int contain_operator(const char* str);
int op_precedence(char c);
enum TipoDeCadena get_type(const char* str);
char* add_parenthesis(const char* eq);
```

## Explicación de algunas funciones
```c

inline enum TipoDeCadena get_type(const char* str)
{
	enum TipoDeCadena explicit_type = none;
	for (size_t i = 0; i < strlen(str); i++)
	{
		const int low = tolower(str[i]); //[^2]
		if (is_operator(low)) //Excluir los que contienen operaciones, ya que solo validamos cadena aunque la cadena tenga signo con decimal, retorna decimal igual.
			continue;
		if (low < 48 || low > 102)
			return none;
		if (low >= 48 && low <= 55) {
			if ((int)explicit_type < octal)
				explicit_type = octal;
			if (low > 55 && low <= 57)
				explicit_type = decimal;
		}
		else if (isdigit(low)) {
			if((int)explicit_type < decimal)
				explicit_type = decimal;
		}
		else
			explicit_type = hexadecimal;
	}
	return explicit_type;
}

```
[^2]: [tolower()](https://www.programiz.com/c-programming/library-function/ctype.h/tolower) convierte los caracteres que tengan mayúsculas en minúsculas 

</details>


