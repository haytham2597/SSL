#pragma once

//Este algoritmo resuelve el tipo de cadena usando automatas

#ifndef AUTOMATAS_MODULES_AUTOMATA_H
#define AUTOMATAS_MODULES_AUTOMATA_H

#ifndef AUTOMATAS_LIBS_COMMON_H
#include "../libs/common.h"
#endif


/*typedef struct Node
{
	char* cadena;
	struct Node* sig;
}node_;

node_* create()
{
    node_* ret = malloc(sizeof(node_));
    ret->sig = NULL;
    return ret;
}*/

//Tabla de transiciones
/*const int tt_octal[4][9] = {
	{1,3,3,3,3,3,3,3,3},
    {3,2,2,2,2,2,2,2,3},
    {2,2,2,2,2,2,2,2,3},
    {3,3,3,3,3,3,3,3,3},
};*/
const int tt_octal[5][9] = {
    {1,4,4,4,4,4,4,4,4},
    {3,2,2,2,2,2,2,2,4},
    {2,2,2,2,2,2,2,2,4},
    {4,4,4,4,4,4,4,4,4},
    {4,4,4,4,4,4,4,4,4},
};

const int tt_decimal[4][13] = {
	{1,1,3,2,2,2,2,2,2,2,2,2,3},
    {3,3,3,2,2,2,2,2,2,2,2,2,3},
    {3,3,2,2,2,2,2,2,2,2,2,2,3},
    {3,3,3,3,3,3,3,3,3,3,3,3,3},
};

const int tt_hexadecimal[4][18] = {
	{1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
    {3,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
    {2,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3},
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
};

int col_octal(char c)
{
    const int v = char_to_int(c);
    if (v >= 8 || v == -1) //v==-1 es porque no es digito
        return 8;
    return v;
}

int col_decimal(char c)
{
    if (c == '+')
        return 0;
    if (c == '-')
        return 1;
    for (char v = '0'; v <= '9'; v++)
        if (v == c)
            return char_to_int(v)+2;
    return 12;
}

int col_hex(char c)
{
    const char hex[] = { '0','x','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f' };
    for (int i = 0; i < sizeof(hex); i++)
        if (hex[i] == c)
            return i;
    return sizeof(hex);
}

enum TipoDeCadena verify_string(char* str)
{
    const enum TipoDeCadena type = get_type(str);
    
    if (type == none)
        return type;
    
    int state = -1;
    for(size_t i=0;i<strlen(str);i++)
    {
	    if(type == octal)
	    {
            state = tt_octal[state][col_octal(str[i])];
	    }
        else if(type == decimal)
        {
            state = tt_decimal[state][col_decimal(str[i])];
        }
        else if(type == hexadecimal)
        {
            state = tt_hexadecimal[state][col_hex(str[i])];
        }
    }
    //printf("STATE: %i\n", state);
    if (type == octal && state == 4)
        return type;
    if(type == decimal || type== hexadecimal)
        if (state == 3)
            return type;
    return none;
}


#endif