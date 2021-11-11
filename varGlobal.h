#ifndef VARGLOBAL_H
#define VARGLOBAL_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//aloca memoria suficiente para uma struct de dados
void *createVar();

//bloco de get, retorna o valor de um dado expecifico da struct quando chamada
//indicado no nome da função
char *getVarEntrada(void *Svar);
char *getVarSaida(void *Svar);
char *getVarGeo(void *Svar);
char *getVarQry(void *Svar);
char *getVarNome4(void *Svar);
int getVarNx(void *Svar);
int getVarLista(void *Svar);
int getVarBbi(void *Svar);
int getVarBbi2(void *Svar);
int getVarBbiD(void *Svar);
int getVarDiid(void *Svar);
int getVarVisitas(void *Svar);
int getVarTamanhoOrigin(void *Svar);
double getVarPointX(void *Svar);
double getVarPointY(void *Svar);
double getVarBBIX(void *Svar);
double getVarBBIY(void *Svar);
double getVarBBIW(void *Svar);
double getVarBBIH(void *Svar);

/**/
#endif