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
	
Instanciamos un arreglo de 4 operadores, los números provienen de la tabla ASCII [^ascii] donde cada char pertenece un entero sin signar de 8 bit (0-255)
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
`strlen(str)` [^strlen]
Primero pasamos a `tolower(str[i]);` [^tolow] para obtener los caracteres en minúsculas, de esta forma tenemos más control. Como se puede ver en la tabla de [^ascii] 48 para abajo se encuentran caracteres que no nos interesa comprobar lo mismo para el 102 entonces si algún carácter posee entre [0-47] y [103-255] (ya que el 102 es `f` y la misma pertenece a los caracteres hexadecimales) retornamos none mejor dicho sería un error léxico. Exceptuando si se tratara de operadores que se encuentra en 42, 43, 45 y 47.
Los que cumplen con el criterio se va asignado el tipo de cadena que es; octal, decimal, etc.
```c
inline enum TipoDeCadena get_type(const char* str)
{
	enum TipoDeCadena explicit_type = none;
	for (size_t i = 0; i < strlen(str); i++)
	{
		const int low = tolower(str[i]);
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

La otra función esencial que forma fuertemente parte del ejercicio es la conversión del `char a enteros`
Observando [^ascii] podemos ver que si el char es un decimal (entre 0 y 9) el char forma parte entre 48 y 57 de la tabla ASCII substraemos por el mínimo (48) para representar el entero
```c
inline int char_to_int(char ch)
{
	if(isdigit(ch))
		return (int)ch - 48;
	return -1;
}
```
</details>

[^tolow]: [tolower()](https://www.programiz.com/c-programming/library-function/ctype.h/tolower) convierte los caracteres que tengan mayúsculas en minúsculas 
[^ascii]: https://elcodigoascii.com.ar
[^strlen]: [strlen()](https://learn.microsoft.com/es-es/cpp/c-runtime-library/reference/strlen-wcslen-mbslen-mbslen-l-mbstrlen-mbstrlen-l?view=msvc-170)
