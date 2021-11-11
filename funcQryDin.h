#ifndef FUNCQRYDIN_H
#define FUNCQRYDIN_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "declaracoes.h"

//funções da qry, tanto para lista estatica quanto para lista dinamica

//função da tp compara se esta totalmente interno a um retangulo por X
int EstaSobrepostoX(Iten objeto1, Iten objeto2);

//função da tp compara se esta totalmente interno a um retangulo por Y
int EstaSobrepostoY(Iten objeto1, Iten objeto2);

//função da tp confere se o id esta na matriz que armazena retangulos sobrepostos
int NaoEstaNaMatriz(char *id, char **vetorId, int tamanhoLista);

//função da tp retorna o tamanho (nas linhas) do vetor de palavras que armazena retangulos sobrepostos
int LinhasVetorId(List list, char **vetorId);

//função da tp compara se os retangulos sobrepostos ja nao foram comparados anteriormente
int ParesDiferentes(char **vetorId, Iten objeto1, Iten objeto2, int listaTamanho10);

//função da tpr compara se o retangulo1 do objeto1 esta totalmente interno com o retangulo2 passado nos parametros do qry
int EstaInterno(Iten objeto1, double x, double y, double w, double h);

//função da dpi compara se o ponto dado nos parametros do qry esta interno a um retangulo do objeto1
int PontoEstaInterno(Iten objeto1, double x, double y);

//função bbi/bbid compara e cria os pontos da bouding box
double *CriaBoudingBox(List list, int k, char **retangulo, double bbiX, double bbiY, double bbiW, double bbiH, void *Stvar);

//tp
void Sobreposicao(List list, void *Stvar);

//tpr
void Interno(List list, double x, double y, double w, double h, void *Stvar);

//dpi
void PontoInterno(List list, double x, double y, void *Stvar);

//dr
void InternoNoRetangulo(List list, char *id, void *Stvar);

//bbi
void BoudingBox(List list, double x, double y, void *Stvar);

//bbid
void BoudingBoxD(List list, char *id, void *Stvar);

//iid
char **Iid(List list, char *id, int k, void *Stvar);

//diid
void Diid(List list, char *id, int k, void *Stvar);

//imprime lisita no svg
void ImprimeLista(List list, char *nome, void *Stvar);

//muda as cores dos retangulos para caso chame uma função que o faça
char **Cores();

/**/
#endif