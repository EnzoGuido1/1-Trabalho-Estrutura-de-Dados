CC = gcc
TS = -g -fstack-protector-all -std=c99

all: progrest progrdin
	rm *.o

progrest: main.o funcoesPrimariasEst.o funcQryDin.o ParametrosSvg.o data.o varGlobal.o
	$(CC) $(TS) main.o funcoesPrimariasEst.o funcQryDin.o ParametrosSvg.o data.o varGlobal.o -o progrest

progrdin: main.o funcoesPrimariasDin.o funcQryDin.o ParametrosSvg.o data.o varGlobal.o
	$(CC) $(TS) main.o funcoesPrimariasDin.o funcQryDin.o ParametrosSvg.o data.o varGlobal.o -o progrdin

main.o:  main.c declaracoes.h funcoesPrimariasDin.h funcQryDin.h ParametrosSvg.h data.h varGlobal.h
	$(CC) $(TS) -c main.c

funcoesPrimariasDin.o: funcoesPrimariasDin.c declaracoes.h funcoesPrimariasDin.h funcQryDin.h ParametrosSvg.h data.h varGlobal.h
	$(CC) $(TS) -c funcoesPrimariasDin.c

funcoesPrimariasEst.o: funcoesPrimariasEst.c declaracoes.h funcoesPrimariasDin.h funcQryDin.h ParametrosSvg.h data.h varGlobal.h
	$(CC) $(TS) -c funcoesPrimariasEst.c

funcQryDin.o: funcQryDin.c declaracoes.h funcoesPrimariasDin.h funcQryDin.h ParametrosSvg.h data.h varGlobal.h
	$(CC) $(TS) -c funcQryDin.c

ParametrosSvg.o: ParametrosSvg.c declaracoes.h funcoesPrimariasDin.h funcQryDin.h ParametrosSvg.h data.h varGlobal.h
	$(CC) $(TS) -c ParametrosSvg.c

data.o: data.c data.h
	$(CC) $(TS) -c data.c

varGlobal.o: varGlobal.c varGlobal.h
	$(CC) $(TS) -c varGlobal.c
