#include "ParametrosSvg.h"
#include "data.h"
#include "declaracoes.h"
#include "funcQryDin.h"
#include "funcoesPrimariasDin.h"
#include "varGlobal.h"

//prototipagem de set (dados da struct recebem algum valor) que sao usados neste arquivo, identificados no nome das funçõeos
void setVarVisitas(void *Svar, int Svisitas);
void setVarTamanhoOrigin(void *Svar, int StamanhoOrigin);

//struct celula da lista dinamica, contem os dados e referencia de proximo de uma determinada celula da lista
typedef struct celulaE {
    void *Dados;
    int prox;
} CelulaE;

//struct lista da lista dinamica, contem o tamanho e referencias de ultimo, primeiro elemento
// e primeira celula livre (disponivel para inserir elementos) da lista
typedef struct listaEstatica {
    CelulaE *vetor;
    int prim, livre, listaTamanho, rabo;

} ListaEstatica;

//bloco de get, retorna valores e posicoes especificas da lista, identificado no nome da funcao
Posic gethead(List list, void *Stvar) {
    ListaEstatica *ponteiro = list;
    if (!ponteiro->listaTamanho) {
        return NULL;
    }
    setVarVisitas(Stvar, getVarVisitas(Stvar) + 1);
    return &ponteiro->vetor[ponteiro->prim];
}

Posic getlast(List list, void *Stvar) {
    ListaEstatica *ponteiro = list;
    if (!ponteiro->listaTamanho) {
        return NULL;
    }
    setVarVisitas(Stvar, getVarVisitas(Stvar) + 1);
    return &ponteiro->vetor[ponteiro->rabo];
}

Posic getprevious(List list, Posic aux, void *Stvar) {
    ListaEstatica *ponteiro = list;
    CelulaE *aux1 = &ponteiro->vetor[ponteiro->prim];
    CelulaE *aux2;
    if (aux == aux1) {
        return NULL;
    } else {
        for (int i = 0; i < ponteiro->listaTamanho; i++) {
            aux2 = getnext(list, aux1, Stvar);
            if (aux2 == aux) {
                return aux1;
            }
            aux1 = getnext(list, aux1, Stvar);
        }
    }
    return NULL;
}

int getsize(List list) {
    ListaEstatica *ponteiro = list;
    return ponteiro->listaTamanho;
}

Iten getdata(Posic aux) {
    CelulaE *ponteiro = aux;
    if (aux == NULL) {
        return NULL;
    }
    return ponteiro->Dados;
}

Posic getnext(List list, Posic aux, void *Stvar) {
    ListaEstatica *lista = list;
    CelulaE *ponteiro = aux;
    if (ponteiro->prox == -1) {
        return NULL;
    }
    setVarVisitas(Stvar, getVarVisitas(Stvar) + 1);
    return &lista->vetor[ponteiro->prox];
}

//retorna uma lista vazia
List CriaLista(void *Stvar) {
    ListaEstatica *ponteiro = calloc(1, sizeof(ListaEstatica));
    ponteiro->prim = -1;
    ponteiro->rabo = -1;
    ponteiro->livre = 0;
    ponteiro->listaTamanho = 0;
    ponteiro->vetor = calloc(getVarNx(Stvar), sizeof(CelulaE));
    for (int i = 0; i < getVarNx(Stvar); i++) {
        ponteiro->vetor[i].Dados = NULL;
        ponteiro->prim = ponteiro->vetor[i].prox;
    }
    return ponteiro;
}

//remove um elemento da lista
void RemoveCelula(List list, Posic aux, void *Stvar) {
    ListaEstatica *listaEstatica = list;
    CelulaE *aux1 = aux;
    CelulaE *aux5;
    int aux2 = NaPosicaoIndex(list, aux, Stvar);
    if (!listaEstatica->listaTamanho) {
        printf("Lista Vazia!");
        return;
    } else if (aux1 == &listaEstatica->vetor[listaEstatica->prim]) {
        listaEstatica->prim = listaEstatica->vetor[aux2].prox;
    } else if (aux1 == &listaEstatica->vetor[listaEstatica->rabo]) {
        aux5 = getprevious(list, aux, Stvar);
        listaEstatica->rabo = NaPosicaoIndex(list, aux5, Stvar);
        listaEstatica->vetor[listaEstatica->rabo].prox = -1;
    } else {
        CelulaE *aux3 = getprevious(list, aux, Stvar);
        CelulaE *aux4 = getnext(list, aux, Stvar);
        if (!aux1 || !aux3) {
            return;
        }
        aux3->prox = NaPosicaoIndex(list, aux4, Stvar);
    }
    listaEstatica->listaTamanho--;
}

//retorna primeiro espaço livre na celula
int LivreE(List list) {
    ListaEstatica *listaEstatica = list;
    return listaEstatica->livre;
}

///retorna posição por index
Posic NaPosicao(List list, int index, void *Stvar) {
    ListaEstatica *listaEstatica = list;
    int aux = listaEstatica->prim;
    if (!listaEstatica->listaTamanho) {
        return 0;
    } else if (index < 0 || index > listaEstatica->listaTamanho - 1) {
        puts("Index Invalido");
        return NULL;
    }
    for (int i = 0; i < index; i++) {
        aux = listaEstatica->vetor[aux].prox;
    }
    setVarVisitas(Stvar, getVarVisitas(Stvar) + 1);
    CelulaE *aux1 = &listaEstatica->vetor[aux];
    return aux1;
}

//retorna index por posição
int NaPosicaoIndex(List list, Posic aux, void *Stvar) {
    ListaEstatica *listaEstatica = list;
    CelulaE *aux1 = aux;
    CelulaE *aux2 = NaPosicao(list, listaEstatica->prim, Stvar);
    for (int i = 0; i < listaEstatica->listaTamanho + getVarTamanhoOrigin(Stvar); i++) {
        if (aux1 == &listaEstatica->vetor[i]) {
            return i;
        }
    }
    setVarVisitas(Stvar, getVarVisitas(Stvar) + 1);
    return -1;
}

//libera lista
void FreeLista(List list, void *Stvar) {
    ListaEstatica *listaEstatica = list;
    for (int i = 0; i < listaEstatica->listaTamanho; i++) {
        Iten *ponteiro = getdata(&listaEstatica->vetor[i]);
        free(ponteiro);
    }
    free(listaEstatica->vetor);
    free(listaEstatica);
    puts("Memoria Liberada!");
}

//insere no primeiro espaço disponivel
Posic InsereElemento(List list, Iten iten, void *Stvar) {
    ListaEstatica *listaEstatica = list;
    int ponteiro = LivreE(list);
    CelulaE *aux;
    listaEstatica->vetor[ponteiro].Dados = iten;
    listaEstatica->vetor[ponteiro].prox = -1;
    if (!listaEstatica->listaTamanho) {
        listaEstatica->prim = 0;
        listaEstatica->rabo = 0;
        listaEstatica->listaTamanho++;
        listaEstatica->livre++;
        return aux;
    } else {
        aux = NaPosicao(list, listaEstatica->listaTamanho - 1, Stvar);
        int aux2 = NaPosicaoIndex(list, aux, Stvar);
        listaEstatica->rabo = ponteiro;
        listaEstatica->vetor[aux2].prox = ponteiro;
        listaEstatica->listaTamanho++;
        listaEstatica->livre++;
    }
    setVarTamanhoOrigin(Stvar, getsize(list));
    return aux;
}

//insere no inicio
Posic InsereNoInicio(List list, Iten iten, void *Stvar) {
    ListaEstatica *listaEstatica = list;
    CelulaE *ponteiro = NaPosicao(list, 0, Stvar);
    if (!listaEstatica->listaTamanho) {
        ponteiro->Dados = iten;
        ponteiro->prox = -1;
        listaEstatica->prim = NaPosicaoIndex(list, ponteiro, Stvar);
    } else {
        ponteiro->Dados = iten;
        ponteiro->prox = listaEstatica->prim;
        listaEstatica->prim = NaPosicaoIndex(list, ponteiro, Stvar);
    }
    listaEstatica->listaTamanho++;
    setVarTamanhoOrigin(Stvar, getsize(list));
    return ponteiro;
}