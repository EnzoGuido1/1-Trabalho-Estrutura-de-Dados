#include "ParametrosSvg.h"

#include "data.h"
#include "declaracoes.h"
#include "funcQryDin.h"
#include "funcoesPrimariasDin.h"
#include "varGlobal.h"

//prototipagem de set (dados da struct recebem algum valor) que sao usados neste arquivo, identificados no nome das funçõeos
void setDataId(void *Sdata, char *Sid);
void setDataCorC(void *Sdata, char *ScorC);
void setDataCorP(void *Sdata, char *ScorP);
void setDataOpacity(void *Sdata, int Sopacity);
void setDataX(void *Sdata, double Sx);
void setDataY(void *Sdata, double Sy);
void setDataW(void *Sdata, double Sw);
void setDataH(void *Sdata, double Sh);

void setVarEntrada(void *Svar, char *Entrada);
void setVarSaida(void *Svar, char *Saida);
void setVarGeo(void *Svar, char *Geo);
void setVarQry(void *Svar, char *Qry);
void setVarNome4(void *Svar, char *Nome4);
void setVarNx(void *Svar, int Snx);
void setVarBbi(void *Svar, int Sbbi);
void setVarBbi2(void *Svar, int Sbbi2);
void setVarBbiD(void *Svar, int SbbiD);
void setVarDiid(void *Svar, int Sdiid);
void setVarVisitas(void *Svar, int Svisitas);
void setVarTamanhoOrigin(void *Svar, int StamanhoOrigin);
void setVarPointX(void *Svar, double SpointX);
void setVarPointY(void *Svar, double SpointY);
void setVarBBIX(void *Svar, double SBBIX);
void setVarBBIY(void *Svar, double SBBIY);
void setVarBBIW(void *Svar, double SBBIW);
void setVarBBIH(void *Svar, double SBBIH);

//alloca variaveis globais
char *ArgumentosParametros(char **argv, int i, int h) {
    char *argumento = calloc(h, sizeof(char));
    strcpy(argumento, argv[i + 1]);
    i++;
    return argumento;
}

//scaneia comandos para svg do geo
void SvgRetangulo(List list, void *Stvar) {
    char funcao[1000];
    char corc[30];
    char corp[30];
    char id[30];
    int tamanho = 0;
    double x, y, w, h;
    FILE *file3 = fopen(getVarGeo(Stvar), "r");
    void *dados;
    while (fscanf(file3, "%s", funcao) != -1) {
        if (!strcmp(funcao, "cc")) {
            fscanf(file3, "%s", funcao);
            if (!strcmp(funcao, "@")) {
                strcpy(corc, "rgba(0,0,0,0)");
            } else {
                strcpy(corc, funcao);
            }
        } else if (!strcmp(funcao, "cp")) {
            fscanf(file3, "%s", funcao);
            if (!strcmp(funcao, "@")) {
                strcpy(corp, "rgba(0,0,0,0)");
            } else {
                strcpy(corp, funcao);
            }
        } else if (!strcmp(funcao, "r")) {
            tamanho++;
            dados = callocData();
            setDataCorC(dados, corc);
            setDataCorP(dados, corp);
            fscanf(file3, "%s", id);
            fscanf(file3, "%lf", &x);
            setDataX(dados, x);
            fscanf(file3, "%lf", &y);
            setDataY(dados, y);
            fscanf(file3, "%lf", &w);
            setDataW(dados, w);
            fscanf(file3, "%lf", &h);
            setDataH(dados, h);
            setDataOpacity(dados, 100);
            setDataId(dados, id);
            InsereElemento(list, dados, Stvar);
        }
    }
    // tamanhoOrigin = tamanho;
    setVarTamanhoOrigin(Stvar, tamanho);
    fclose(file3);
}

//scaneia comandos para svg do qry na lista dinamica
void SvgFuncoes(List list, void *Stvar) {
    char funcao[30];
    char id[30];
    int k = 0;
    char **libera;
    double x;
    double y;
    double w;
    double h;
    int m;
    // FILE *file5 = fopen(qry, "r");
    FILE *file5 = fopen(getVarQry(Stvar), "r");
    while (fscanf(file5, "%s", funcao) != -1) {
        if (!strcmp(funcao, "tp")) {
            Sobreposicao(list, Stvar);
        } else if (!strcmp(funcao, "tpr")) {
            fscanf(file5, "%lf", &x);
            fscanf(file5, "%lf", &y);
            fscanf(file5, "%lf", &w);
            fscanf(file5, "%lf", &h);
            Interno(list, x, y, w, h, Stvar);
        } else if (!strcmp(funcao, "dpi")) {
            fscanf(file5, "%lf", &x);
            fscanf(file5, "%lf", &y);
            PontoInterno(list, x, y, Stvar);
        } else if (!strcmp(funcao, "dr")) {
            fscanf(file5, "%s", id);
            InternoNoRetangulo(list, id, Stvar);
        } else if (!strcmp(funcao, "bbi")) {
            fscanf(file5, "%lf", &x);
            fscanf(file5, "%lf", &y);
            BoudingBox(list, x, y, Stvar);
        } else if (!strcmp(funcao, "bbid")) {
            fscanf(file5, "%s", id);
            BoudingBoxD(list, id, Stvar);
        } else if (!strcmp(funcao, "iid")) {
            fscanf(file5, "%s", id);
            fscanf(file5, "%d", &m);
            libera = Iid(list, id, m, Stvar);
            for (int i = 0; i < getsize(list) * 5; i++) {
                free(libera[i]);
            }
            free(libera);
        } else if (!strcmp(funcao, "diid")) {
            fscanf(file5, "%s", id);
            fscanf(file5, "%d", &m);
            Diid(list, id, m, Stvar);
        }
    }
    fclose(file5);
}

//imprime o grafico svg
void Ib(List list, char **argv, int j, char *arquivo, void *Stvar) {
    strcat(arquivo, ".svg");
    char path[150];
    // strcpy(path, pathSaida);
    strcpy(path, getVarSaida(Stvar));
    strcat(path, "/");
    strcat(path, arquivo);
    strcpy(arquivo, path);
    FILE *file2 = fopen(arquivo, "w");
    FILE *file10 = fopen("coleta.txt", "r");
    double novaListaTamanho;
    double novaVisitas;
    double variavel;
    int cont = 1;
    char funcao[30];
    fprintf(file2, "<svg version=\"1.2\" viewBox = \"0 0 1000 800\">\n\t<rect width=\"100%%\" height=\"100%%\" fill=\"white\"/>\n\t<text x=\"465\" y=\"775\" font-size=\"25\">%s</text>\n\t<line x1=\"80\" y1=\"20\" x2=\"80\" y2=\"700\" style=\"stroke: black\"></line>\n\t<line x1=\"80\" y1=\"700\" x2=\"960\" y2=\"700\" style=\"stroke: black\"></line>\n\n\t", argv[j + 2]);
    while (fscanf(file10, "%s", funcao) != -1) {
        if (!strcmp(funcao, "visitas")) {
            fscanf(file10, "%lf", &novaVisitas);
            variavel = novaVisitas;
            while (variavel > 260) {
                variavel = variavel - 260;
                cont++;
            }
        }
    }
    fclose(file10);
    file10 = fopen("coleta.txt", "r");
    while (fscanf(file10, "%s", funcao) != -1) {
        if (!strcmp(funcao, "visitas")) {
            fscanf(file10, "%lf", &novaVisitas);
            if (cont > 1) {
                novaVisitas = novaVisitas / cont;
            }
            novaVisitas = 700 - (novaVisitas * 2.5);
            fscanf(file10, "%s", funcao);
            if (!strcmp(funcao, "tamanho")) {
                fscanf(file10, "%lf", &novaListaTamanho);
                if (cont > 1) {
                    novaListaTamanho = novaListaTamanho / cont;
                }
                novaListaTamanho = 80 + (novaListaTamanho * 5);
                fprintf(file2, "<line x1=\"80\" y1=\"%.2lf\" x2=\"%.2lf\" y2=\"%.2lf\" style=\"stroke: black\" stroke-width=\"2\" stroke-dasharray=\"5\"></line>\n\t", novaVisitas, novaListaTamanho, novaVisitas);
                fprintf(file2, "<line x1=\"%.2lf\" y1=\"700\" x2=\"%.2lf\" y2=\"%.2lf\" style=\"stroke: black\" stroke-width=\"2\" stroke-dasharray=\"5\"></line>\n\t", novaListaTamanho, novaListaTamanho, novaVisitas);
                fprintf(file2, "<circle r=\"3\" cx=\"%.2lf\" cy=\"%.2lf\" fill=\"red\" stroke=\"black\" stroke-width=\"1.5\" ></circle>\n\n\t", novaListaTamanho, novaVisitas);
            }
        }
    }
    float a = 105;
    int b = 0;
    int c;
    for (int i = 0; i < 35; i++) {
        if (b % 2 == 0) {
            c = 695;
        } else {
            c = 690;
        }
        fprintf(file2, "<line x1=\"%.0f\" y1=\"%d\" x2=\"%.0f\" y2=\"700\" style=\"stroke: black;\"></line>\n\t", a, c, a);
        b++;
        a = a + 25;
    }
    fprintf(file2, "\n\t");
    b = 0;
    a = 687.5;
    for (int i = 0; i < 54; i++) {
        if (b % 2 == 0) {
            c = 85;
        } else {
            c = 90;
        }
        fprintf(file2, "<line x1=\"80\" y1=\"%.1f\" x2=\"%d\" y2=\"%.1f\" style=\"stroke: black;\"></line>\n\t", a, c, a);
        b++;
        a = a - 12.5;
    }
    fprintf(file2, "\n\t");
    a = 80;
    c = 0;
    for (int i = 0; i < 18; i++) {
        fprintf(file2, "<text x=\"%.0f\" y=\"715\">%d</text>\n\t", a, c * cont);
        a = a + 50;
        c = c + 10;
    }
    fprintf(file2, "<text x=\"480\" y=\"735\" class=\"label-title\">Tamanho</text>\n");
    fprintf(file2, "\n\t");
    a = 700;
    b = 0;
    c = 280;
    for (int i = 0; i < 15; i++) {
        if (c == 0) {
            a = 70;
        } else if (c < 100) {
            a = 62;
        } else {
            a = 55;
        }
        fprintf(file2, "<text x=\"%.0f\" y=\"%d\">%d</text>\n\t", a, b, c * cont);
        b = b + 50;
        c = c - 20;
    }
    fprintf(file2, "<text x=\"10\" y=\"375\" class=\"label-title\">Visitas</text>\n");
    fprintf(file2, "</svg>");
    fclose(file2);
    fclose(file10);
}

//confere o nome dos arquivos geo e qry ate o ponto e retorna a string anterior
char *Nome(char *nome) {
    char *ret = calloc(strlen(nome) + 150, sizeof(char));
    int cont = 0;
    do {
        ret[cont] = nome[cont];
        cont++;
    } while (nome[cont] != '.');
    return ret;
}

//scaneia os imputs do terminal e chama as operações nescessarias, alem de reformular o nome do qry svg e txt de saida
void *Parametros(int argc, char **argv, void *Stvar) {
    FILE *file;
    void *list;
    int verificadorSaida = 0;
    int verificadorEntrada = 0;
    // verificadorDiid = 0;
    setVarDiid(Stvar, 0);
    // visitas = 0;
    setVarVisitas(Stvar, 0);
    // pointX = 0;
    setVarPointX(Stvar, 0);
    // pointY = 0;
    setVarPointY(Stvar, 0);
    // BBIX = 0;
    setVarBBIX(Stvar, 0);
    // BBIY = 0;
    setVarBBIY(Stvar, 0);
    // BBIW = 0;
    setVarBBIW(Stvar, 0);
    // BBIH = 0;
    setVarBBIH(Stvar, 0);
    // verificadorBbi = 0;
    setVarBbi(Stvar, 0);
    // verificadorBbi2 = 0;
    setVarBbi2(Stvar, 0);
    // verificadorBbiD = 0;
    setVarBbiD(Stvar, 0);
    int contador = 0;
    int verificadorQry = 0;
    int verificadorGrafico = 0;
    int verificadorColeta = 0;
    int verificadorInColeta = 0;
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-e")) {
            // pathEntrada = ArgumentosParametros(argv, i, 150);
            setVarEntrada(Stvar, argv[i + 1]);
            verificadorEntrada = 1;
        }
        if (!strcmp(argv[i], "-f")) {
            // geo = ArgumentosParametros(argv, i, 150);
            setVarGeo(Stvar, argv[i + 1]);
        }
        if (!strcmp(argv[i], "-o")) {
            // pathSaida = ArgumentosParametros(argv, i, 150);
            setVarSaida(Stvar, argv[i + 1]);
            verificadorSaida = 1;
        }
        if (!strcmp(argv[i], "-q")) {
            // qry = ArgumentosParametros(argv, i, 150);
            setVarQry(Stvar, argv[i + 1]);
            verificadorQry = 1;
        }
        if (!strcmp(argv[i], "-ib")) {
            file = fopen("coleta.txt", "w");
            fprintf(file, "%d", 1);
            verificadorInColeta = 1;
            fclose(file);
            //função de inicialização;
        }
        if (!strcmp(argv[i], "-cb")) {
            int *verificador = calloc(2, sizeof(int));
            file = fopen("coleta.txt", "r");
            if (file != NULL) {
                fscanf(file, "%d", verificador);
                if (*verificador == 1) {
                    //função de continuação;
                } else {
                    puts("coleta nao iniciada");
                }
            } else {
                puts("coleta nao iniciada");
            }
            free(verificador);
            fclose(file);
            verificadorColeta = 1;
        }
        if (!strcmp(argv[i], "-fb")) {
            contador = i;
            verificadorGrafico = 1;
        }
    }
    char tamanhoEstatico[200];
    char leitura[30];
    strcpy(tamanhoEstatico, getVarEntrada(Stvar));
    strcat(tamanhoEstatico, "/");
    // strcat(tamanhoEstatico, geo);
    strcat(tamanhoEstatico, getVarGeo(Stvar));
    // FILE *file8 = fopen(geo, "r");
    if (verificadorEntrada == 1) {
        FILE *file8 = fopen(tamanhoEstatico, "r");
        fscanf(file8, "%s", leitura);
        if (!strcmp(leitura, "nx")) {
            // fscanf(file8, "%d", &nx);
            int auxNx;
            fscanf(file8, "%d", &auxNx);
            setVarNx(Stvar, auxNx);
        }
        fclose(file8);
    }
    list = CriaLista(Stvar);
    // char *nome = Nome(geo);  // svg geo
    char *nome = Nome(getVarGeo(Stvar));
    if (verificadorEntrada == 1) {
        char path2[150];
        // strcpy(path2, pathEntrada);
        strcpy(path2, getVarEntrada(Stvar));
        strcat(path2, "/");
        // strcat(path2, geo);
        strcat(path2, getVarGeo(Stvar));
        // strcpy(geo, path2);
        setVarGeo(Stvar, path2);
    }
    SvgRetangulo(list, Stvar);
    // nome4 = calloc(150, sizeof(char));  // concat geo com qry para o txt
    // strcpy(nome4, nome);
    setVarNome4(Stvar, nome);
    char aux33[150] = "";
    int contadorA = 0;
    int comparadorA = 0;
    for (int i = 0; i < strlen(nome) + 1; i++) {
        if (comparadorA == 1) {
            aux33[contadorA] = nome[i];
            contadorA++;
        }
        if (nome[i] == '/') {
            comparadorA = 1;
        }
    }
    if (contadorA == 0) {
        strcpy(aux33, nome);
    }
    sprintf(nome, "%s.svg", aux33);
    ImprimeLista(list, nome, Stvar);
    if (verificadorQry == 1) {
        // char *nome2 = Nome(qry);  // concat geo com qry
        char *nome2 = Nome(getVarQry(Stvar));
        if (verificadorEntrada == 1) {
            char path3[150];
            // strcpy(path3, pathEntrada);
            strcpy(path3, getVarEntrada(Stvar));
            strcat(path3, "/");
            // strcat(path3, qry);
            strcat(path3, getVarQry(Stvar));
            // strcpy(qry, path3);
            setVarQry(Stvar, path3);
        }
        char *nome3 = calloc(strlen(nome2) + 1, 1);  // concat geo com qry para o svg
        strcpy(nome3, nome2);
        nome2 = realloc(nome2, strlen(nome2) + strlen(nome) + 10);
        // sprintf(nome2, "%s-%s.svg", nome4, nome3);
        char *auxiliar = getVarNome4(Stvar);
        char *auxiliar2 = nome3;
        char aux3[150] = "";
        char aux4[150] = "";
        int contador = 0;
        int comparador = 0;
        for (int i = 0; i < strlen(auxiliar); i++) {
            if (comparador == 1) {
                aux3[contador] = auxiliar[i];
                contador++;
            }
            if (auxiliar[i] == '/') {
                comparador = 1;
            }
        }
        if (contador == 0) {
            strcpy(aux3, auxiliar);
        }
        comparador = 0;
        contador = 0;
        for (int i = 0; i < strlen(auxiliar2); i++) {
            if (comparador == 1) {
                aux4[contador] = auxiliar2[i];
                contador++;
            }
            if (auxiliar2[i] == '/') {
                comparador = 1;
            }
        }
        if (contador == 0) {
            strcpy(aux4, auxiliar2);
        }
        sprintf(nome2, "%s-%s.svg", aux3, aux4);
        // sprintf(nome4, "%s-%s.txt", nome4, aux4);
        char auxNome4[1000];
        sprintf(auxNome4, "%s-%s.txt", aux3, aux4);
        setVarNome4(Stvar, auxNome4);
        char path[150];
        // strcpy(path, pathSaida);
        strcpy(path, getVarSaida(Stvar));
        strcat(path, "/");
        // strcat(path, nome4);
        strcat(path, getVarNome4(Stvar));
        // strcpy(nome4, path);
        setVarNome4(Stvar, path);
        SvgFuncoes(list, Stvar);
        ImprimeLista(list, nome2, Stvar);
        free(nome2);
        free(nome3);
    }
    free(nome);
    if (verificadorInColeta == 1 || verificadorColeta == 1) {
        file = fopen("coleta.txt", "a");
        fprintf(file, "\n%s", "visitas");
        // fprintf(file, " %d", visitas);
        fprintf(file, " %d", getVarVisitas(Stvar));
        fprintf(file, "\n%s", "tamanho");
        // fprintf(file, " %d", tamanhoOrigin);
        fprintf(file, " %d", getVarTamanhoOrigin(Stvar));
        verificadorInColeta = 0;
        verificadorColeta = 0;
        fclose(file);
    }
    if (verificadorGrafico == 1) {
        int *verificador = calloc(2, sizeof(int));
        char arquivo[50];
        file = fopen("coleta.txt", "a");
        fprintf(file, "\n%s", "visitas");
        // fprintf(file, " %d", visitas);
        fprintf(file, " %d", getVarVisitas(Stvar));
        fprintf(file, "\n%s", "tamanho");
        // fprintf(file, " %d", tamanhoOrigin);
        fprintf(file, " %d", getVarTamanhoOrigin(Stvar));
        fclose(file);
        file = fopen("coleta.txt", "r");
        if (file != NULL) {
            fscanf(file, "%d", verificador);
            if (*verificador == 1) {
                strcpy(arquivo, argv[contador + 1]);
                Ib(list, argv, contador, arquivo, Stvar);
            } else {
                puts("coleta nao iniciada");
            }
            fclose(file);
        } else {
            puts("coleta nao iniciada");
        }
        file = fopen("coleta.txt", "w");
        fprintf(file, "%d", 0);
        fclose(file);
        free(verificador);
        verificadorGrafico = 0;
    }
    return list;
}
