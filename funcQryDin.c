#include "funcQryDin.h"

#include "ParametrosSvg.h"
#include "data.h"
#include "declaracoes.h"
#include "funcoesPrimariasDin.h"
#include "varGlobal.h"

//prototipagem de set (dados da struct recebem algum valor) que sao usados neste arquivo, identificados no nome das funçõeos
void setDataCorC(void *Sdata, char *ScorC);
void setDataCorP(void *Sdata, char *ScorP);
void setDataOpacity(void *Sdata, int Sopacity);

void setVarBbi(void *Svar, int Sbbi);
void setVarBbi2(void *Svar, int Sbbi2);
void setVarBbiD(void *Svar, int SbbiD);
void setVarDiid(void *Svar, int Sdiid);
void setVarPointX(void *Svar, double SpointX);
void setVarPointY(void *Svar, double SpointY);
void setVarBBIX(void *Svar, double SBBIX);
void setVarBBIY(void *Svar, double SBBIY);
void setVarBBIW(void *Svar, double SBBIW);
void setVarBBIH(void *Svar, double SBBIH);

//função da tp compara se esta totalmente interno a um retangulo por X
int EstaSobrepostoX(Iten objeto1, Iten objeto2) {
    Posic aux1_0 = objeto1;
    Posic aux2_0 = objeto2;
    void *aux1 = getdata(aux1_0);
    void *aux2 = getdata(aux2_0);
    if (getDataX(aux2) >= getDataX(aux1) && getDataX(aux2) <= getDataX(aux1) + getDataW(aux1)) {
        return 1;
    }
    if (getDataX(aux2) + getDataW(aux2) >= getDataX(aux1) && getDataX(aux2) + getDataW(aux2) <= getDataX(aux1) + getDataW(aux1)) {
        return 1;
    }
    if (getDataX(aux1) >= getDataX(aux2) && getDataX(aux1) <= getDataX(aux2) + getDataW(aux2)) {
        return 1;
    }
    if (getDataX(aux1) + getDataW(aux1) >= getDataX(aux2) && getDataX(aux1) + getDataW(aux1) <= getDataX(aux2) + getDataW(aux2)) {
        return 1;
    }
    return 0;
}

//função da tp compara se esta totalmente interno a um retangulo por Y
int EstaSobrepostoY(Iten objeto1, Iten objeto2) {
    Posic aux1_0 = objeto1;
    Posic aux2_0 = objeto2;
    void *aux1 = getdata(aux1_0);
    void *aux2 = getdata(aux2_0);
    if (getDataY(aux2) >= getDataY(aux1) && getDataY(aux2) <= getDataY(aux1) + getDataH(aux1)) {
        return 1;
    }
    if (getDataY(aux2) + getDataH(aux2) >= getDataY(aux1) && getDataY(aux2) + getDataH(aux2) <= getDataY(aux1) + getDataH(aux1)) {
        return 1;
    }
    if (getDataY(aux1) >= getDataY(aux2) && getDataY(aux1) <= getDataY(aux2) + getDataH(aux2)) {
        return 1;
    }
    if (getDataY(aux1) + getDataH(aux1) >= getDataY(aux2) && getDataY(aux1) + getDataH(aux1) <= getDataY(aux2) + getDataH(aux2)) {
        return 1;
    }
    return 0;
}

//função da tp confere se o id esta na matriz que armazena retangulos sobrepostos
int NaoEstaNaMatriz(char *id, char **vetorId, int tamanhoLista) {
    for (int i = 0; i < tamanhoLista; i++) {
        if (!strcmp(id, vetorId[i])) {
            return 0;
        }
    }
    return 1;
}

//função da tp retorna o tamanho (nas linhas) do vetor de palavras que armazena retangulos sobrepostos
int LinhasVetorId(List list, char **vetorId) {
    int k = 0;
    for (int i = 0; i < getsize(list) * 5; i++) {
        if (vetorId[i][0] != '\0') {
            k++;
        }
    }
    return k;
}

//função da tp compara se os retangulos sobrepostos ja nao foram comparados anteriormente
int ParesDiferentes(char **vetorId, Iten objeto1, Iten objeto2, int listaTamanho10) {
    Posic aux1_0 = objeto1;
    Posic aux2_0 = objeto2;
    void *aux1 = getdata(aux1_0);
    void *aux2 = getdata(aux2_0);
    for (int i = 0; i < listaTamanho10; i++) {
        if (!strcmp(vetorId[i], getDataId(aux2))) {
            if (i % 2 == 0) {
                if (!strcmp(vetorId[i + 1], getDataId(aux1))) {
                    return 0;
                }
            }
            if (i % 2 != 0) {
                if (!strcmp(vetorId[i - 1], getDataId(aux1))) {
                    return 0;
                }
            }
        }
    }
    return 1;
}

//função da tpr compara se o retangulo1 do objeto1 esta totalmente interno com o retangulo2 passado nos parametros do qry
int EstaInterno(Iten objeto1, double x, double y, double w, double h) {
    Posic aux1_0 = objeto1;
    void *aux1 = getdata(aux1_0);
    if (getDataX(aux1) >= x && getDataX(aux1) + getDataW(aux1) <= x + w) {
        if (getDataY(aux1) >= y && getDataY(aux1) + getDataH(aux1) <= y + h) {
            return 1;
        }
    }
    return 0;
}

//função da dpi compara se o ponto dado nos parametros do qry esta interno a um retangulo do objeto1
int PontoEstaInterno(Iten objeto1, double x, double y) {
    Posic aux1_0 = objeto1;
    void *aux1 = getdata(aux1_0);
    if (x >= getDataX(aux1) && x <= getDataX(aux1) + getDataW(aux1)) {
        if (y >= getDataY(aux1) && y <= getDataY(aux1) + getDataH(aux1)) {
            return 1;
        }
    }
    return 0;
}

//função bbi/bbid compara e cria os pontos da bouding box
double *CriaBoudingBox(List list, int k, char **retangulo, double bbiX, double bbiY, double bbiW, double bbiH, void *Stvar) {
    Posic aux1_0 = gethead(list, Stvar);
    void *aux1 = getdata(aux1_0);
    double *vetor = calloc(4, sizeof(double));
    if (k == 0) {
        puts("o ponto dado nao intersecta nenhum retangulo");
    } else if (k == 1) {
        setVarBbi2(Stvar, 1);
        for (int i = 0; i < getsize(list); i++) {
            aux1 = getdata(aux1_0);
            for (int j = 0; j < k; j++) {
                if (!strcmp(getDataId(aux1), retangulo[j])) {
                    vetor[0] = getDataX(aux1);
                    vetor[1] = getDataY(aux1);
                    vetor[2] = getDataW(aux1);
                    vetor[3] = getDataH(aux1);
                }
            }
            aux1_0 = getnext(list, aux1_0, Stvar);
        }
    } else {
        for (int i = 0; i < getsize(list); i++) {
            aux1 = getdata(aux1_0);
            for (int j = 0; j < k; j++) {
                if (!strcmp(getDataId(aux1), retangulo[j])) {
                    if (getDataX(aux1) < bbiX) {
                        bbiX = getDataX(aux1);
                        vetor[0] = getDataX(aux1);
                    }
                    if (getDataY(aux1) < bbiY) {
                        bbiY = getDataY(aux1);
                        vetor[1] = getDataY(aux1);
                    }
                    if (getDataX(aux1) + getDataW(aux1) > bbiW) {
                        bbiW = getDataX(aux1) + getDataW(aux1);
                        vetor[2] = getDataX(aux1) + getDataW(aux1);
                    }
                    if (getDataY(aux1) + getDataH(aux1) > bbiH) {
                        bbiH = getDataY(aux1) + getDataH(aux1);
                        vetor[3] = getDataY(aux1) + getDataH(aux1);
                    }
                }
            }
            aux1_0 = getnext(list, aux1_0, Stvar);
        }
    }
    return vetor;
}

//tp
void Sobreposicao(List list, void *Stvar) {
    Posic aux1_0 = gethead(list, Stvar);
    void *aux1 = getdata(aux1_0);
    Posic aux2_0 = gethead(list, Stvar);
    void *aux2 = getdata(aux2_0);
    FILE *tp = fopen(getVarNome4(Stvar), "a");
    fprintf(tp, "TP:\n");
    int k = 0;
    int colorido = 0;
    int listaTamanho10 = getsize(list);
    int *verificador = calloc(listaTamanho10, sizeof(int));
    listaTamanho10 = listaTamanho10 * 10;
    char **vetorId = calloc(listaTamanho10, sizeof(char *));
    for (int i = 0; i < listaTamanho10; i++) {
        vetorId[i] = calloc(50, sizeof(char));
    }
    char **cor = Cores();
    for (int i = 0; i < getsize(list); i++) {
        aux1 = getdata(aux1_0);
        for (int j = 0; j < getsize(list); j++) {
            aux2 = getdata(aux2_0);
            if (strcmp(getDataId(aux1), getDataId(aux2)) && EstaSobrepostoX(aux1_0, aux2_0) && EstaSobrepostoY(aux1_0, aux2_0)) {
                if (ParesDiferentes(vetorId, aux1_0, aux2_0, listaTamanho10)) {
                    fprintf(tp, "%s//%s\n", getDataId(aux1), getDataId(aux2));
                    strcpy(vetorId[k++], getDataId(aux1));
                    strcpy(vetorId[k++], getDataId(aux2));
                    setDataCorP(aux1, cor[colorido]);
                    setDataCorP(aux2, cor[colorido]);
                    colorido++;
                    if (colorido >= 9) {
                        colorido = 0;
                    }
                    verificador[NaPosicaoIndex(list, aux1_0, Stvar)] = 1;
                    verificador[NaPosicaoIndex(list, aux2_0, Stvar)] = 1;
                    setDataOpacity(aux1, 100);
                    setDataOpacity(aux2, 100);
                }
            } else {
                if (!verificador[NaPosicaoIndex(list, aux1_0, Stvar)]) {
                    setDataOpacity(aux1, 0);
                }
                if (!verificador[NaPosicaoIndex(list, aux2_0, Stvar)]) {
                    setDataOpacity(aux2, 0);
                }
            }
            aux2_0 = getnext(list, aux2_0, Stvar);
        }
        aux2_0 = gethead(list, Stvar);
        aux1_0 = getnext(list, aux1_0, Stvar);
    }
    fprintf(tp, "\n");
    fclose(tp);
    for (int i = 0; i < listaTamanho10; i++) {
        free(vetorId[i]);
    }
    free(vetorId);
    for (int i = 0; i < 10; i++) {
        free(cor[i]);
    }
    free(cor);
    free(verificador);
}

//tpr
void Interno(List list, double x, double y, double w, double h, void *Stvar) {
    Posic aux1_0 = gethead(list, Stvar);
    void *aux1 = getdata(aux1_0);
    Posic aux2_0 = gethead(list, Stvar);
    void *aux2 = getdata(aux2_0);
    FILE *tpr = fopen(getVarNome4(Stvar), "a");
    fprintf(tpr, "TPR:\n");
    int k = 0;
    int colorido = 0;
    char **cor = Cores();
    int listaTamanho10 = getsize(list);
    int *verificador = calloc(listaTamanho10, sizeof(int));
    listaTamanho10 = listaTamanho10 * 10;
    char **vetorId = calloc(listaTamanho10, sizeof(char *));
    for (int i = 0; i < listaTamanho10; i++) {
        vetorId[i] = calloc(50, sizeof(char));
    }
    for (int i = 0; i < getsize(list); i++) {
        aux1 = getdata(aux1_0);
        if (EstaInterno(aux1_0, x, y, w, h)) {
            for (int j = 0; j < getsize(list); j++) {
                aux2 = getdata(aux2_0);
                if (EstaInterno(aux2_0, x, y, w, h) && EstaSobrepostoX(aux1_0, aux2_0) && EstaSobrepostoY(aux1_0, aux2_0)) {
                    if (i != j) {
                        if (ParesDiferentes(vetorId, aux1_0, aux2_0, listaTamanho10)) {
                            fprintf(tpr, "%s//", getDataId(aux1));
                            fprintf(tpr, "%s\n", getDataId(aux2));
                            strcpy(vetorId[k++], getDataId(aux1));
                            strcpy(vetorId[k++], getDataId(aux2));
                        }
                        setDataCorP(aux1, cor[colorido]);
                        setDataCorP(aux2, cor[colorido++]);
                        if (colorido >= 9) {
                            colorido = 0;
                        }
                        verificador[NaPosicaoIndex(list, aux1_0, Stvar)] = 1;
                        verificador[NaPosicaoIndex(list, aux2_0, Stvar)] = 1;
                        setDataOpacity(aux1, 100);
                        setDataOpacity(aux2, 100);
                    }
                } else {
                    if (!verificador[NaPosicaoIndex(list, aux1_0, Stvar)]) {
                        setDataOpacity(aux1, 0);
                    }
                    if (!verificador[NaPosicaoIndex(list, aux2_0, Stvar)]) {
                        setDataOpacity(aux2, 0);
                    }
                }
                aux2_0 = getnext(list, aux2_0, Stvar);
            }
        }
        aux2_0 = gethead(list, Stvar);
        aux1_0 = getnext(list, aux1_0, Stvar);
    }
    aux1_0 = gethead(list, Stvar);
    if (vetorId[0][0] == '\0') {
        for (int i = 0; i < getsize(list); i++) {
            aux1 = getdata(aux1_0);
            setDataOpacity(aux1, 0);
            aux1_0 = getnext(list, aux1_0, Stvar);
        }
    }
    fprintf(tpr, "\n");
    fclose(tpr);
    free(verificador);
    for (int i = 0; i < listaTamanho10; i++) {
        free(vetorId[i]);
    }
    for (int i = 0; i < 10; i++) {
        free(cor[i]);
    }
    free(cor);
    free(vetorId);
}

//dpi
void PontoInterno(List list, double x, double y, void *Stvar) {
    Posic aux1_0 = gethead(list, Stvar);
    void *aux1 = getdata(aux1_0);
    FILE *dpi = fopen(getVarNome4(Stvar), "a");
    fprintf(dpi, "DPI:\n");
    int h = 0;
    for (int i = 0; i < getsize(list); i++) {
        aux1 = getdata(aux1_0);
        if (PontoEstaInterno(aux1_0, x, y)) {
            fprintf(dpi, "/%s/ ", getDataId(aux1));
            RemoveCelula(list, aux1_0, Stvar);
            aux1_0 = gethead(list, Stvar);
            h = -1;
            i = -1;
        } else {
            aux1_0 = getnext(list, aux1_0, Stvar);
        }
        h++;
    }
    fprintf(dpi, "\n");
    fclose(dpi);
}

//dr
void InternoNoRetangulo(List list, char *id, void *Stvar) {
    Posic aux1_0 = gethead(list, Stvar);
    void *aux1 = getdata(aux1_0);
    Posic aux2_0 = gethead(list, Stvar);
    void *aux2 = getdata(aux2_0);
    FILE *dr = fopen(getVarNome4(Stvar), "a");
    fprintf(dr, "DR:\n");
    int h = 0;
    for (int i = 0; i < getsize(list); i++) {
        aux1 = getdata(aux1_0);
        if (!strcmp(getDataId(aux1), id)) {
            aux2 = aux1;
            break;
        }
        aux1_0 = getnext(list, aux1_0, Stvar);
    }
    for (int i = 0; i < getsize(list); i++) {
        aux1 = getdata(aux1_0);
        if (strcmp(getDataId(aux2), getDataId(aux1)) && EstaInterno(aux1_0, getDataX(aux2), getDataY(aux2), getDataW(aux2), getDataH(aux2))) {
            fprintf(dr, "%s\n", getDataId(aux1));
            fprintf(dr, "/%s/ ", getDataId(aux1));
            RemoveCelula(list, aux1_0, Stvar);
            aux1_0 = gethead(list, Stvar);
            h = -1;
            i = -1;
        } else {
            aux1_0 = getnext(list, aux1_0, Stvar);
        }
        h++;
    }
    fprintf(dr, "\n");
    fclose(dr);
}

//bbi
void BoudingBox(List list, double x, double y, void *Stvar) {
    Posic aux1_0 = gethead(list, Stvar);
    void *aux1 = getdata(aux1_0);
    FILE *bbi = fopen(getVarNome4(Stvar), "a");
    fprintf(bbi, "BBI:\nID    //COR DE PREENCHIMENTO//   COR DE CONTORNO\n");
    setVarPointX(Stvar, x);
    setVarPointY(Stvar, y);
    int k = 0;
    double bbiX = 10000;
    double bbiY = 10000;
    double bbiW = 0;
    double bbiH = 0;
    double *vetor;
    char troca[30];
    char **retangulo = calloc(getsize(list) * 10, sizeof(char *));
    for (int i = 0; i < getsize(list); i++) {
        aux1 = getdata(aux1_0);
        if (PontoEstaInterno(aux1_0, x, y)) {
            retangulo[k++] = getDataId(aux1);
            fprintf(bbi, "%s\t\t", getDataId(aux1));
            fprintf(bbi, "%s\t\t\t\t\t", getDataCorP(aux1));
            fprintf(bbi, "%s\n", getDataCorC(aux1));
            strcpy(troca, getDataCorC(aux1));
            setDataCorC(aux1, getDataCorP(aux1));
            setDataCorP(aux1, troca);
        }
        aux1_0 = getnext(list, aux1_0, Stvar);
    }
    vetor = CriaBoudingBox(list, k, retangulo, bbiX, bbiY, bbiW, bbiH, Stvar);
    if (getVarBbi2(Stvar) == 0) {
        setVarBbi(Stvar, 1);
    } else {
        setVarBbi(Stvar, 2);
    }
    setVarBBIX(Stvar, vetor[0]);
    setVarBBIY(Stvar, vetor[1]);
    setVarBBIW(Stvar, vetor[2]);
    setVarBBIH(Stvar, vetor[3]);
    free(vetor);
    free(retangulo);
    fprintf(bbi, "\n");
    fclose(bbi);
}

//bbid
void BoudingBoxD(List list, char *id, void *Stvar) {
    Posic aux1_0 = gethead(list, Stvar);
    void *aux1 = getdata(aux1_0);
    Posic aux3_0 = gethead(list, Stvar);
    void *aux3 = getdata(aux3_0);
    FILE *bbid = fopen(getVarNome4(Stvar), "a");
    fprintf(bbid, "BBID:\nID    //COR DE PREENCHIMENTO//   COR DE CONTORNO\n");
    setVarBbiD(Stvar, 1);
    int k = 0;
    double bbiX = 10000;
    double bbiY = 10000;
    double bbiW = 0;
    double bbiH = 0;
    double *vetor;
    char troca[30];
    char **retangulo = calloc(getsize(list) * 10, sizeof(char *));
    for (int i = 0; i < getsize(list); i++) {
        aux1 = getdata(aux1_0);
        if (!strcmp(getDataId(aux1), id)) {
            break;
        }
        aux1_0 = getnext(list, aux1_0, Stvar);
    }
    for (int i = 0; i < getsize(list); i++) {
        aux3 = getdata(aux3_0);
        if (EstaInterno(aux3_0, getDataX(aux1), getDataY(aux1), getDataW(aux1), getDataH(aux1)) && strcmp(getDataId(aux1), getDataId(aux3))) {
            retangulo[k++] = getDataId(aux3);
            fprintf(bbid, "%s\t\t", getDataId(aux3));
            fprintf(bbid, "%s\t\t\t\t\t", getDataCorP(aux3));
            fprintf(bbid, "%s\n", getDataCorC(aux3));
            strcpy(troca, getDataCorC(aux3));
            setDataCorC(aux3, getDataCorP(aux3));
            setDataCorP(aux3, troca);
        }
        aux3_0 = getnext(list, aux3_0, Stvar);
    }
    vetor = CriaBoudingBox(list, k, retangulo, bbiX, bbiY, bbiW, bbiH, Stvar);
    if (getVarBbi2(Stvar) == 0) {
        setVarBbi(Stvar, 1);
    } else {
        setVarBbi(Stvar, 2);
    }
    setVarBBIX(Stvar, vetor[0]);
    setVarBBIY(Stvar, vetor[1]);
    setVarBBIW(Stvar, vetor[2]);
    setVarBBIH(Stvar, vetor[3]);
    free(vetor);
    free(retangulo);
    fprintf(bbid, "\n");
    fclose(bbid);
}

//iid
char **Iid(List list, char *id, int k, void *Stvar) {
    Posic aux1_0 = gethead(list, Stvar);
    void *aux1 = getdata(aux1_0);
    Posic aux2_0 = gethead(list, Stvar);
    void *aux2 = getdata(aux2_0);
    FILE *iid = fopen(getVarNome4(Stvar), "a");
    if (getVarDiid(Stvar) == 1) {
        fprintf(iid, "D");
    }
    fprintf(iid, "IID:\nID/--/ANCORA(x,y)/--/LARGURA/--/ALTURA/--/COR DE CONTORNO/--/COR DE PREENCHIMENTO\n\n");
    char **vetorId = calloc(getsize(list) * 10, sizeof(char *));
    int A = 0;
    int B = 0;
    for (int i = 0; i < getsize(list) * 10; i++) {
        vetorId[i] = calloc(getsize(list) * 10, sizeof(char));
    }
    for (int i = 0; i < getsize(list); i++) {
        aux1 = getdata(aux1_0);
        if (!strcmp(getDataId(aux1), id)) {
            strcpy(vetorId[A++], getDataId(aux1));
            aux2 = aux1;
            fprintf(iid, "%s/--/(%lf,%lf)/--/%lf/--/%lf/--/%s/--/%s\n", getDataId(aux1), getDataX(aux1), getDataY(aux1), getDataW(aux1), getDataH(aux1), getDataCorC(aux1), getDataCorP(aux1));
            break;
        }
        B++;
        aux1_0 = getnext(list, aux1_0, Stvar);
    }
    int verificadorA = 0;
    aux1_0 = gethead(list, Stvar);
    if (k < 0) {
        for (int i = B; i > B + k; i--) {
            aux1 = getdata(aux1_0);
            if (strcmp(getDataId(aux2), getDataId(aux1))) {
                strcpy(vetorId[A++], getDataId(aux1));
                fprintf(iid, "%s/--/(%lf,%lf)/--/%lf/--/%lf/--/%s/--/%s\n", getDataId(aux1), getDataX(aux1), getDataY(aux1), getDataW(aux1), getDataH(aux1), getDataCorC(aux1), getDataCorP(aux1));
            } else {
                break;
            }
            aux1_0 = getnext(list, aux1_0, Stvar);
            if (aux1_0 == NULL) {
                break;
            }
        }
    } else {
        for (int i = B + k; i >= B; i--) {
            aux1 = getdata(aux1_0);
            if (strcmp(getDataId(aux2), getDataId(aux1)) && verificadorA == 1) {
                strcpy(vetorId[A++], getDataId(aux1));
                fprintf(iid, "%s/--/(%lf,%lf)/--/%lf/--/%lf/--/%s/--/%s\n", getDataId(aux1), getDataX(aux1), getDataY(aux1), getDataW(aux1), getDataH(aux1), getDataCorC(aux1), getDataCorP(aux1));
            } else if (!strcmp(getDataId(aux2), getDataId(aux1))) {
                verificadorA = 1;
            }
            aux1_0 = getnext(list, aux1_0, Stvar);
            if (aux1_0 == NULL) {
                break;
            }
        }
    }
    fprintf(iid, "\n");
    fclose(iid);
    return vetorId;
}

//diid
void Diid(List list, char *id, int k, void *Stvar) {
    Posic aux1_0 = gethead(list, Stvar);
    void *aux1 = getdata(aux1_0);
    setVarDiid(Stvar, 1);
    char **vetorId = Iid(list, id, k, Stvar);
    setVarDiid(Stvar, 0);
    int tamanhoVetor = LinhasVetorId(list, vetorId);
    int h = 0;
    for (int i = 0; i < getsize(list); i++) {
        aux1 = getdata(aux1_0);
        if (!strcmp(getDataId(aux1), vetorId[0])) {
            break;
        }
        aux1_0 = getnext(list, aux1_0, Stvar);
        h++;
    }
    aux1_0 = gethead(list, Stvar);
    int verificadorA = 0;
    int verificadorB = 0;
    for (int j = 0; j < getsize(list); j++) {
        aux1 = getdata(aux1_0);
        for (int i = 1; i < tamanhoVetor; i++) {
            if (!strcmp(getDataId(aux1), vetorId[i])) {
                RemoveCelula(list, aux1_0, Stvar);
                verificadorA = 1;
                j = -1;
                break;
            } else {
                verificadorB = 1;
            }
        }
        if (verificadorA == 1) {
            aux1_0 = gethead(list, Stvar);
        } else if (verificadorB == 1) {
            aux1_0 = getnext(list, aux1_0, Stvar);
        }
        verificadorA = 0;
    }
    for (int i = 0; i < getsize(list) * 5; i++) {
        free(vetorId[i]);
    }
    free(vetorId);
}

//imprime lisita no svg
void ImprimeLista(List list, char *nome, void *Stvar) {
    Posic aux1_0 = gethead(list, Stvar);
    void *aux;
    char saida[100];
    char path[150];
    strcpy(path, getVarSaida(Stvar));
    strcpy(saida, nome);
    strcat(path, "/");
    strcat(path, saida);
    strcpy(saida, path);
    FILE *file4 = fopen(saida, "w");
    fprintf(file4, "<svg>");
    for (int i = 0; i < getsize(list); i++) {
        aux = getdata(aux1_0);
        fprintf(file4, "\n\t<rect x=\" %lf \" y=\" %lf \" width=\" %lf \" height=\" %lf \" stroke=\"%s\" stroke-width=\"2px\" fill=\"%s\" opacity=\"%d\"/>", getDataX(aux), getDataY(aux), getDataW(aux), getDataH(aux), getDataCorC(aux), getDataCorP(aux), getDataOpacity(aux));
        //fprintf(file4, "\n\t<text x=\"%lf\" y=\"%lf\" font-size=\"10\">%s</text>", getDataX(aux) + 2, getDataY(aux) + 10, getDataId(aux));
        if (getVarPointX(Stvar) != 0 && getVarPointY(Stvar) != 0) {
            fprintf(file4, "<circle cx=\"%lf\" cy=\"%lf\" r=\"5\" stroke=\"black\" stroke-width=\"2.5\" fill=\"red\" />", getVarPointX(Stvar), getVarPointY(Stvar));
        }
        aux1_0 = getnext(list, aux1_0, Stvar);
    }
    if (getVarBbi(Stvar) == 1) {
        fprintf(file4, "\n\t<rect x=\" %lf \" y=\" %lf \" width=\" %lf \" height=\" %lf \" stroke=\"red\" stroke-width=\"6px\" fill=\"none\" opacity=\"100\" stroke-dasharray=\"5\"/>", getVarBBIX(Stvar), getVarBBIY(Stvar), getVarBBIW(Stvar) - getVarBBIX(Stvar), getVarBBIH(Stvar) - getVarBBIY(Stvar));
        if (getVarBbiD(Stvar) == 0) {
            fprintf(file4, "<circle cx=\"%lf\" cy=\"%lf\" r=\"5\" stroke=\"black\" stroke-width=\"2.5\" fill=\"red\" />", getVarPointX(Stvar), getVarPointY(Stvar));
        }
    } else if (getVarBbi(Stvar) == 2) {
        fprintf(file4, "\n\t<rect x=\" %lf \" y=\" %lf \" width=\" %lf \" height=\" %lf \" stroke=\"red\" stroke-width=\"6px\" fill=\"none\" opacity=\"100\" stroke-dasharray=\"5\"/>", getVarBBIX(Stvar), getVarBBIY(Stvar), getVarBBIW(Stvar), getVarBBIH(Stvar));
        if (getVarBbiD(Stvar) == 0) {
            fprintf(file4, "<circle cx=\"%lf\" cy=\"%lf\" r=\"5\" stroke=\"black\" stroke-width=\"2.5\" fill=\"red\" />", getVarPointX(Stvar), getVarPointY(Stvar));
        }
    }
    fprintf(file4, "\n</svg>");
    fclose(file4);
}

//muda as cores dos retangulos para caso chame uma função que o faça
char **Cores() {
    char **cor = calloc(10, sizeof(char *));
    for (int i = 0; i < 10; i++) {
        cor[i] = calloc(30, sizeof(char));
    }
    strcpy(cor[0], "red");
    strcpy(cor[1], "purple");
    strcpy(cor[2], "blue");
    strcpy(cor[3], "green");
    strcpy(cor[4], "yellow");
    strcpy(cor[5], "pink");
    strcpy(cor[6], "grey");
    strcpy(cor[7], "orange");
    strcpy(cor[8], "black");
    strcpy(cor[9], "maroon");
    return cor;
}