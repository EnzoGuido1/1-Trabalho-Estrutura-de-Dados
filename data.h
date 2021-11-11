#ifndef DATA_H
#define DATA_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//aloca memoria suficiente para uma struct de dados
void* callocData();

//bloco de get, retorna o valor de um dado expecifico da struct quando chamada
//indicado no nome da função
char* getDataId(void* Sdata);
char* getDataCorC(void* Sdata);
char* getDataCorP(void* Sdata);
int getDataOpacity(void* Sdata);
double getDataX(void* Sdata);
double getDataY(void* Sdata);
double getDataW(void* Sdata);
double getDataH(void* Sdata);

/**/
#endif