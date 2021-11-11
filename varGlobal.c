#include "varGlobal.h"
//struct de dados, contem os dados que sao inseridos na hora de inserir um elemento
typedef struct varGlobal {
    char *pathEntrada;
    char *pathSaida;
    char *geo;
    char *qry;
    char *nome4;
    int nx;
    int verificadorLista;
    int verificadorBbi;
    int verificadorBbi2;
    int verificadorBbiD;
    int verificadorDiid;
    int visitas;
    int tamanhoOrigin;
    double pointX;
    double pointY;
    double BBIX;
    double BBIY;
    double BBIW;
    double BBIH;
} VarGlobal;

//aloca memoria suficiente para uma struct de dados
void *createVar() {
    VarGlobal *ponteiro = calloc(1, sizeof(VarGlobal));
    ponteiro->pathEntrada = calloc(1, sizeof(char));
    ponteiro->pathSaida = calloc(1, sizeof(char));
    ponteiro->geo = calloc(1, sizeof(char));
    ponteiro->qry = calloc(1, sizeof(char));
    ponteiro->nome4 = calloc(1, sizeof(char));
    return ponteiro;
}

//bloco de get, retorna o valor de um dado expecifico da struct quando chamada indicado no nome da função
char *getVarEntrada(void *Svar) {
    VarGlobal *varGlobal = Svar;
    return varGlobal->pathEntrada;
}

char *getVarSaida(void *Svar) {
    VarGlobal *varGlobal = Svar;
    return varGlobal->pathSaida;
}

char *getVarGeo(void *Svar) {
    VarGlobal *varGlobal = Svar;
    return varGlobal->geo;
}

char *getVarQry(void *Svar) {
    VarGlobal *varGlobal = Svar;
    return varGlobal->qry;
}

char *getVarNome4(void *Svar) {
    VarGlobal *varGlobal = Svar;
    return varGlobal->nome4;
}

int getVarNx(void *Svar) {
    VarGlobal *varGlobal = Svar;
    return varGlobal->nx;
}

int getVarLista(void *Svar) {
    VarGlobal *varGlobal = Svar;
    return varGlobal->verificadorLista;
}

int getVarBbi(void *Svar) {
    VarGlobal *varGlobal = Svar;
    return varGlobal->verificadorBbi;
}

int getVarBbi2(void *Svar) {
    VarGlobal *varGlobal = Svar;
    return varGlobal->verificadorBbi2;
}

int getVarBbiD(void *Svar) {
    VarGlobal *varGlobal = Svar;
    return varGlobal->verificadorBbiD;
}

int getVarDiid(void *Svar) {
    VarGlobal *varGlobal = Svar;
    return varGlobal->verificadorDiid;
}

int getVarVisitas(void *Svar) {
    VarGlobal *varGlobal = Svar;
    return varGlobal->visitas;
}

int getVarTamanhoOrigin(void *Svar) {
    VarGlobal *varGlobal = Svar;
    return varGlobal->tamanhoOrigin;
}

double getVarPointX(void *Svar) {
    VarGlobal *varGlobal = Svar;
    return varGlobal->pointX;
}

double getVarPointY(void *Svar) {
    VarGlobal *varGlobal = Svar;
    return varGlobal->pointY;
}

double getVarBBIX(void *Svar) {
    VarGlobal *varGlobal = Svar;
    return varGlobal->BBIX;
}

double getVarBBIY(void *Svar) {
    VarGlobal *varGlobal = Svar;
    return varGlobal->BBIY;
}

double getVarBBIW(void *Svar) {
    VarGlobal *varGlobal = Svar;
    return varGlobal->BBIW;
}

double getVarBBIH(void *Svar) {
    VarGlobal *varGlobal = Svar;
    return varGlobal->BBIH;
}

//bloco de set, quando chamada a função. um dado expecifico da struct recebe o valor passado no argumento
void setVarEntrada(void *Svar, char *Entrada) {
    VarGlobal *varGlobal = Svar;
    varGlobal->pathEntrada = realloc(varGlobal->pathEntrada, strlen(varGlobal->pathEntrada) + strlen(Entrada) + 1);
    strcpy(varGlobal->pathEntrada, Entrada);
}

void setVarSaida(void *Svar, char *Saida) {
    VarGlobal *varGlobal = Svar;
    varGlobal->pathSaida = realloc(varGlobal->pathSaida, strlen(varGlobal->pathSaida) + strlen(Saida) + 1);
    strcpy(varGlobal->pathSaida, Saida);
}

void setVarGeo(void *Svar, char *Geo) {
    VarGlobal *varGlobal = Svar;
    varGlobal->geo = realloc(varGlobal->geo, strlen(varGlobal->geo) + strlen(Geo) + 1);
    strcpy(varGlobal->geo, Geo);
}

void setVarQry(void *Svar, char *Qry) {
    VarGlobal *varGlobal = Svar;
    varGlobal->qry = realloc(varGlobal->qry, strlen(varGlobal->qry) + strlen(Qry) + 1);
    strcpy(varGlobal->qry, Qry);
}

void setVarNome4(void *Svar, char *Nome4) {
    VarGlobal *varGlobal = Svar;
    varGlobal->nome4 = realloc(varGlobal->nome4, strlen(varGlobal->nome4) + strlen(Nome4) + 1);
    strcpy(varGlobal->nome4, Nome4);
}

void setVarNx(void *Svar, int Snx) {
    VarGlobal *varGlobal = Svar;
    varGlobal->nx = Snx;
}

void setVarLista(void *Svar, int Slista) {
    VarGlobal *varGlobal = Svar;
    varGlobal->verificadorLista = Slista;
}

void setVarBbi(void *Svar, int Sbbi) {
    VarGlobal *varGlobal = Svar;
    varGlobal->verificadorBbi = Sbbi;
}

void setVarBbi2(void *Svar, int Sbbi2) {
    VarGlobal *varGlobal = Svar;
    varGlobal->verificadorBbi2 = Sbbi2;
}

void setVarBbiD(void *Svar, int SbbiD) {
    VarGlobal *varGlobal = Svar;
    varGlobal->verificadorBbiD = SbbiD;
}

void setVarDiid(void *Svar, int Sdiid) {
    VarGlobal *varGlobal = Svar;
    varGlobal->verificadorDiid = Sdiid;
}

void setVarVisitas(void *Svar, int Svisitas) {
    VarGlobal *varGlobal = Svar;
    varGlobal->visitas = Svisitas;
}

void setVarTamanhoOrigin(void *Svar, int StamanhoOrigin) {
    VarGlobal *varGlobal = Svar;
    varGlobal->tamanhoOrigin = StamanhoOrigin;
}

void setVarPointX(void *Svar, double SpointX) {
    VarGlobal *varGlobal = Svar;
    varGlobal->pointX = SpointX;
}

void setVarPointY(void *Svar, double SpointY) {
    VarGlobal *varGlobal = Svar;
    varGlobal->pointY = SpointY;
}

void setVarBBIX(void *Svar, double SBBIX) {
    VarGlobal *varGlobal = Svar;
    varGlobal->BBIX = SBBIX;
}

void setVarBBIY(void *Svar, double SBBIY) {
    VarGlobal *varGlobal = Svar;
    varGlobal->BBIY = SBBIY;
}

void setVarBBIW(void *Svar, double SBBIW) {
    VarGlobal *varGlobal = Svar;
    varGlobal->BBIW = SBBIW;
}

void setVarBBIH(void *Svar, double SBBIH) {
    VarGlobal *varGlobal = Svar;
    varGlobal->BBIH = SBBIH;
}
