#include "data.h"

//struct de dados, contem os dados que sao inseridos na hora de inserir um elemento
typedef struct dados {
    char id[100];
    char corC[30];
    char corP[30];
    int opacity;
    double x;
    double y;
    double w;
    double h;

} Dados;

//aloca memoria suficiente para uma struct de dados
void* callocData() {
    Dados* dados = calloc(1, sizeof(Dados));
    return dados;
}

//bloco de get, retorna o valor de um dado expecifico da struct quando chamada indicado no nome da função
char* getDataId(void* Sdata) {
    Dados* dados = Sdata;
    return dados->id;
}

char* getDataCorC(void* Sdata) {
    Dados* dados = Sdata;
    return dados->corC;
}

char* getDataCorP(void* Sdata) {
    Dados* dados = Sdata;
    return dados->corP;
}

int getDataOpacity(void* Sdata) {
    Dados* dados = Sdata;
    return dados->opacity;
}

double getDataX(void* Sdata) {
    Dados* dados = Sdata;
    return dados->x;
}

double getDataY(void* Sdata) {
    Dados* dados = Sdata;
    return dados->y;
}

double getDataW(void* Sdata) {
    Dados* dados = Sdata;
    return dados->w;
}

double getDataH(void* Sdata) {
    Dados* dados = Sdata;
    return dados->h;
}

//bloco de set, quando chamada a função. um dado expecifico da struct recebe o valor passado no argumento
void setDataId(void* Sdata, char* Sid) {
    Dados* dados = Sdata;
    strcpy(dados->id, Sid);
}

void setDataCorC(void* Sdata, char* ScorC) {
    Dados* dados = Sdata;
    strcpy(dados->corC, ScorC);
}

void setDataCorP(void* Sdata, char* ScorP) {
    Dados* dados = Sdata;
    strcpy(dados->corP, ScorP);
}

void setDataOpacity(void* Sdata, int Sopacity) {
    Dados* dados = Sdata;
    dados->opacity = Sopacity;
}

void setDataX(void* Sdata, double Sx) {
    Dados* dados = Sdata;
    dados->x = Sx;
}

void setDataY(void* Sdata, double Sy) {
    Dados* dados = Sdata;
    dados->y = Sy;
}

void setDataW(void* Sdata, double Sw) {
    Dados* dados = Sdata;
    dados->w = Sw;
}

void setDataH(void* Sdata, double Sh) {
    Dados* dados = Sdata;
    dados->h = Sh;
}
