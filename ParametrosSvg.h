#ifndef PARAMETROSSVG_H
#define PARAMETROSSVG_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "declaracoes.h"

//alloca variaveis globais
char *ArgumentosParametros(char **argv, int i, int h);

//scaneia comandos para svg do geo
void SvgRetangulo(List list, void *Stvar);

//scaneia comandos para svg do qry na lista dinamica
void SvgFuncoes(List list, void *Stvar);

//imprime o grafico svg
void Ib(List list, char **argv, int j, char *arquivo, void *Stvar);

//confere o nome dos arquivos geo e qry ate o ponto e retorna a string anterior
char *Nome(char *nome);

//scaneia os imputs do terminal e chama as operações nescessarias, alem de reformular o nome do qry svg e txt de saida
void *Parametros(int argc, char **argv, void *Stvar);

/**/
#endif