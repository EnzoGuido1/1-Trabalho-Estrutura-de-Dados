#include "funcoesPrimariasDin.h"

#include "ParametrosSvg.h"
#include "data.h"
#include "declaracoes.h"
#include "funcQryDin.h"
#include "varGlobal.h"

//prototipagem de set (dados da struct recebem algum valor) que sao usados neste arquivo, identificados no nome das funçõeos
void setVarVisitas(void *Svar, int Svisitas);
void setVarTamanhoOrigin(void *Svar, int StamanhoOrigin);

//struct celula da lista dinamica, contem os dados e referencias de proximo e anterior de uma determinada celula da lista
typedef struct celula {
    void *Dados;
    struct celula *prox;
    struct celula *ant;

} Celula;

//struct lista da lista dinamica, contem o tamanho e referencias de ultimo e primeiro elemento da lista
typedef struct lista {
    int tamanho;
    Celula *cabeca;
    Celula *rabo;

} Lista;

//bloco de get, retorna valores e posicoes especificas da lista, identificado no nome da funcao
Posic gethead(List list, void *Stvar) {
    Lista *lista = list;
    if (!lista->tamanho) {
        return NULL;
    }
    setVarVisitas(Stvar, getVarVisitas(Stvar) + 1);
    return lista->cabeca;
}

Posic getlast(List list, void *Stvar) {
    Lista *lista = list;
    if (!lista->tamanho) {
        return NULL;
    }
    setVarVisitas(Stvar, getVarVisitas(Stvar) + 1);
    return lista->rabo;
}

Posic getprevious(List list, Posic aux, void *Stvar) {
    Lista *ponteiro = list;
    Celula *aux1 = aux;
    if (aux1 == ponteiro->cabeca) {
        return NULL;
    }
    setVarVisitas(Stvar, getVarVisitas(Stvar) + 1);
    return aux1->ant;
}

int getsize(List list) {
    Lista *lista = list;
    return lista->tamanho;
}

Iten getdata(Posic aux) {
    Celula *ponteiro = aux;
    if (aux == NULL) {
        return NULL;
    }
    return ponteiro->Dados;
}

Posic getnext(List list, Posic aux, void *Stvar) {
    Celula *ponteiro = aux;
    if (ponteiro->prox == NULL) {
        return NULL;
    }
    setVarVisitas(Stvar, getVarVisitas(Stvar) + 1);
    return ponteiro->prox;
}

Posic getant(List list, Posic aux) {
    Celula *aux1 = aux;
    return aux1->ant;
}

//retorna uma lista vazia
List CriaLista(void *Stvar) {
    Lista *ponteiro = malloc(sizeof(Lista));
    ponteiro->tamanho = 0;
    ponteiro->cabeca = ponteiro->rabo = NULL;
    return ponteiro;
}

//remove um elemento da lista
void RemoveCelula(List list, Posic aux, void *Stvar) {
    Lista *lista = list;
    Celula *aux3 = aux;
    if (!lista->tamanho) {
        printf("Lista Vazia!");
        return;
    } else if (aux3 == lista->cabeca) {
        lista->cabeca = lista->cabeca->prox;
        lista->cabeca->ant = NULL;
    } else if (aux3 == lista->rabo) {
        lista->rabo = aux3->ant;
        lista->rabo->prox = NULL;
    } else {
        Celula *aux2 = aux3->ant;
        Celula *aux4 = aux3->prox;
        if (!aux3 || !aux2) {
            return;
        }
        aux4->ant = aux2;
        aux2->prox = aux3->prox;
    }
    lista->tamanho--;
    free(aux3);
}

//retorna posição por index
Posic NaPosicao(List list, int index, void *Stvar) {
    Lista *lista = list;
    Celula *aux = lista->cabeca;
    if (index < 0 || index > lista->tamanho - 1) {
        puts("Index Invalido");
        return NULL;
    }
    for (int i = 0; i < index; i++) {
        aux = aux->prox;
    }
    setVarVisitas(Stvar, getVarVisitas(Stvar) + 1);
    return aux;
}

//retorna index por posição
int NaPosicaoIndex(List list, Posic aux, void *Stvar) {
    Lista *lista = list;
    Celula *aux1 = aux;
    Celula *aux2 = lista->cabeca;
    for (int i = 0; i < lista->tamanho; i++) {
        if (aux1 == aux2) {
            return i;
        }
        aux2 = aux2->prox;
    }
    setVarVisitas(Stvar, getVarVisitas(Stvar) + 1);
    return -1;
}

//libera lista
void FreeLista(List list, void *Stvar) {
    Lista *lista = list;
    Celula *aux = lista->cabeca, *aux2;
    setVarVisitas(Stvar, getVarVisitas(Stvar) + 1);
    for (int i = 0; i < lista->tamanho; i++) {
        aux2 = aux;
        Iten *ponteiro = getdata(aux);
        free(ponteiro);
        setVarVisitas(Stvar, getVarVisitas(Stvar) + 1);
        aux = aux->prox;
        free(aux2);
    }
    setVarVisitas(Stvar, getVarVisitas(Stvar) + 1);
    free(lista);
    puts("Memoria Liberada!");
}

//insere no final da lista
Posic InsereElemento(List list, Iten iten, void *Stvar) {
    Lista *lista = list;
    Celula *aux = calloc(1, sizeof(Celula));
    aux->Dados = iten;
    if (lista->tamanho == 0) {
        lista->cabeca = aux;
        lista->rabo = aux;
        aux->prox = NULL;
        aux->ant = NULL;
    } else {
        aux->ant = lista->rabo;
        lista->rabo->prox = aux;
        lista->rabo = aux;
        aux->prox = NULL;
    }
    lista->tamanho++;
    setVarTamanhoOrigin(Stvar, getsize(list));
    return aux;
}

//insere no inicio da lista
Posic InsereNoInicio(List list, Iten iten, void *Stvar) {
    Lista *lista = list;
    Celula *ponteiro = NaPosicao(list, 0, Stvar);
    if (!lista->tamanho) {
        ponteiro->Dados = iten;
        ponteiro->prox = NULL;
        lista->cabeca = ponteiro;
    } else {
        ponteiro->Dados = iten;
        ponteiro->prox = lista->cabeca;
        lista->cabeca = ponteiro;
    }
    lista->tamanho++;
    setVarTamanhoOrigin(Stvar, getsize(list));
    return ponteiro;
}
