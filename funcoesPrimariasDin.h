#ifndef FUNCOESPRIMARIASDIN_H
#define FUNCOESPRIMARIASDIN_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "declaracoes.h"

//funções da geo, header tanto da lista estatica quanto da lista dinamica

//bloco de get, retorna valores e posicoes especificas da lista, identificado no nome da funcao
Posic gethead(List list, void* Stvar);
Posic getlast(List list, void* Stvar);
Posic getprevious(List list, Posic aux, void* Stvar);
int getsize(List list);
Iten getdata(Posic aux);
Posic getnext(List list, Posic aux, void* Stvar);
Posic getant(List list, Posic aux);

//retorna uma lista vazia sem tamanho
List CriaLista(void* Stvar);

//remove um elemento da lista, caso a lista nao tenha elementos retorna vazio
//entra uma celula do tipo posic para remoção
void RemoveCelula(List list, Posic aux, void* Stvar);

//retorna primeiro espaço livre na lista, comparando a primeira celula disponivel
int LivreE(List list);

//retorna posição por index, recebe de argumento o index de remoção da lista
//caso seja inserido um index menor que zero ou maior que o tamanho da lista retorna NULL
Posic NaPosicao(List list, int index, void* Stvar);

//retorna posição por index, recebe de argumento a posição da celula de remoção da lista
//caso seja inserido uma posicao menor que zero ou maior que o tamanho da lista retorna NULL
int NaPosicaoIndex(List list, Posic aux, void* Stvar);

//libera list, da free na estrutura da lista
void FreeLista(List list, void* Stvar);

//Dinamica: insere no final da lista, recebe de argumento um iten do tipo ponteiro pra void
//Estatica: insere no primeiro espaço disponivel, recebe de argumento um iten do tipo ponteiro pra void
Posic InsereElemento(List list, Iten iten, void* Stvar);

//insere no inicio da lista, recebe de argumento um iten do tipo ponteiro pra void
Posic InsereNoInicio(List list, Iten iten, void* Stvar);

/**/
#endif