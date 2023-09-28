#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int charToInt(char c){
    int i = c;
    return i - 48;
}

struct Nodo{
    char *cadena;
    struct Nodo *sig;
};

struct Nodo* iniciar(){
    struct Nodo *ret = malloc(sizeof(struct Nodo));
    ret->cadena = malloc(1); // Asignamos memoria para un carácter
    ret->cadena[0] = '\0';  // Inicializamos con una cadena vacía
    ret->sig = NULL;
    return ret;
}

// Sobrecarga
struct Nodo* iniciarCompleto(char *cadena){
    struct Nodo *ret = malloc(sizeof(struct Nodo));
    ret->cadena = malloc(strlen(cadena) + 1); // Asignamos memoria suficiente para la cadena
    strcpy(ret->cadena, cadena); // Copiamos la cadena
    ret->sig = NULL;
    return ret;
}

void vaciarCadena(char *cadena){
    memset(cadena, 0, strlen(cadena));
}

void agregar(struct Nodo *cadenas, char *str){
    struct Nodo *aux = cadenas;
    while(aux->sig != NULL){
        aux = aux->sig;
    }
    aux->sig = iniciarCompleto(str);
}

struct Nodo* separarCadenas(char *str){
    struct Nodo *ret = iniciar();
    char aux;
    char cadena[20] = "";
    for(int i=0; str[i] != '\0'; i++){
        aux = str[i];
        if( aux == '$'){
            //la cadena da vacio si recien cree la lista entonces reemplazo
            if(strcmp(ret->cadena, "") == 0){
                ret = iniciarCompleto(cadena);
                vaciarCadena(cadena);
            }
            else{
                agregar(ret, cadena);
                //lst->sig = iniciarCompleto(cadena);
                vaciarCadena(cadena);
            }
        }
        else{
            int len = strlen(cadena);
            cadena[len] = aux;
            cadena[len + 1] = '\0';
        }
    }
    //el ultimo se queda sin separador asi que hay que agregarlo despues de iterar todo
    agregar(ret, cadena);
    return ret;
}

//muestra todas las cadenas separadas del texto inicial
void mostrar(struct Nodo *cadenas){
    struct Nodo *aux = cadenas;
    while(aux != NULL){
        printf("%s",aux->cadena);
        printf("\n\n");
        aux = aux->sig;
    }
}

//nos fijamos en las primeras restricciones para saber que automata debemos utilizar
//esto no garantiza que la cadena este bien escrita
void sacarTipo(char *str, int *tipoPalabra){
    if(str[0] == '0'){
        if(str[1] == 'x'){
            *tipoPalabra = 16;
        }
        else{
            *tipoPalabra = 8;
        }
    }
    else{
        *tipoPalabra = 10;
    }
}

int columnaOctal(int c){
    switch(c)
    {
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;    
        default:
            return 8;
    }
}

int verificaOctal(char *str){
    const int ttOctal[4][9] = {{1,3,3,3,3,3,3,3,3},
                               {3,2,2,2,2,2,2,2,3},
                               {2,2,2,2,2,2,2,2,3},
                               {3,3,3,3,3,3,3,3,3},
                              };
    int estado = 0;
    int i = 0;
    int c = str[0];

    while(c != '\0')
    {
        estado = ttOctal[estado][columnaOctal(c)];
        i++;
        c = str[i];
    }

    if(estado==2)//el de finalizacion en nuestro caso
    {
        return 1;
    }

    return 0;
}

int columnaDecimal(int c){
    switch(c)
    {
        case '+':
            return 0;
        case '-':
            return 1;
        case '0':
            return 2;
        case '1':
            return 3;
        case '2':
            return 4;
        case '3':
            return 5;
        case '4':
            return 6;
        case '5':
            return 7;
        case '6':
             return 8;
        case '7':
            return 9;   
        case '8':
            return 10;
        case '9':
            return 11;    
        default:
            return 12;
    }
}

int verificaDecimal(char *str){
    const int ttDecimal[4][13] = {{1,1,3,2,2,2,2,2,2,2,2,2,3},
                                  {3,3,3,2,2,2,2,2,2,2,2,2,3},
                                  {3,3,2,2,2,2,2,2,2,2,2,2,3},
                                  {3,3,3,3,3,3,3,3,3,3,3,3,3},
                                 };
    int estado = 0;
    int i = 0;
    int c = str[0];

    while(c != '\0')
    {
        estado = ttDecimal[estado][columnaDecimal(c)];
        i++;
        c = str[i];
    }

    if(estado==2)//el de finalizacion en nuestro caso
    {
        return 1;
    }

    return 0;
}

int columnaHexadecimal(int c){
    switch(c)
    {
        case '0':
            return 0;
        case 'x':
            return 1;
        case '1':
            return 2;
        case '2':
            return 3;
        case '3':
            return 4;
        case '4':
            return 5;
        case '5':
            return 6;
        case '6':
            return 7;
        case '7':
            return 8;
        case '8':
            return 9;
        case '9':
            return 10;
        case 'A':
            return 11;
        case 'B':
            return 12;
        case 'C':
            return 13;
        case 'D':
            return 14;
        case 'E':
            return 15;
        case 'F':
            return 16;      
        default:
            return 17;
    }
}

int verificaHexadecimal(char *str){
    const int ttHexadecimal[4][18] = {{1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
                                      {3,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
                                      {2,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3},
                                      {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
                                     };
    int estado = 0;
    int i = 0;
    int c = str[0];

    while(c != '\0')
    {
        estado = ttHexadecimal[estado][columnaHexadecimal(c)];
        i++;
        c = str[i];
    }

    if(estado==2)//el de finalizacion en nuestro caso
    {
        return 1;
    }

    return 0;
}

int esPalabra(char *str, int *tipoPalabra){
    sacarTipo(str, tipoPalabra);
    int resultado;
    if(*tipoPalabra == 8){
        resultado = verificaOctal(str);
    }
    else if(*tipoPalabra == 10){
        resultado = verificaDecimal(str);
    }
    else if(*tipoPalabra == 16){
        resultado = verificaHexadecimal(str);
    }
    return resultado;
}

void sumarContador(int *octales,int *decimales, int *hexadecimales, int tipoPalabra){
    switch(tipoPalabra){
        case 8: (*octales)++; break;
        case 10: (*decimales)++; break;
        case 16: (*hexadecimales)++; break;
    }
}

void verificarCadenas(struct Nodo *cadenas, int *octales,int *decimales, int *hexadecimales){
    char *str;
    int i = 1;
    int tipoPalabra = 0;
    for(struct Nodo *aux = cadenas; aux != NULL; aux = aux->sig){
        str = aux->cadena;
        if(esPalabra(str, &tipoPalabra))
        {
            sumarContador(octales, decimales, hexadecimales, tipoPalabra);
            tipoPalabra = 0;
        }
        else{
        printf("LA CADENA %i TIENE ERROR LEXICO \n",i);
        }
        i++;
    }
}

void mostrarResultados(int octales,int decimales, int hexadecimales){
    printf("EXISTEN %i CADENAS PERTENECIENTES AL GRUPO DE LOS OCTALES BIEN ESCRITAS \n", octales);
    printf("EXISTEN %i CADENAS PERTENECIENTES AL GRUPO DE LOS DECIMALES BIEN ESCRITAS \n", decimales);
    printf("EXISTEN %i CADENAS PERTENECIENTES AL GRUPO DE LOS HEXADECIMALES BIEN ESCRITAS \n", hexadecimales);
}

int main()
{
    char str[50];
    printf("escriba la cadena");
    printf("\n");
    scanf("%s", str);
    struct Nodo* cadenas = separarCadenas(str);
    mostrar(cadenas);
    int octales = 0;
    int decimales = 0;
    int hexadecimales = 0;
    verificarCadenas(cadenas,&octales,&decimales,&hexadecimales);
    mostrarResultados(octales, decimales, hexadecimales);
    system("pause");
    return 0;
}