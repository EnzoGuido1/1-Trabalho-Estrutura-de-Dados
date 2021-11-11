#include "ParametrosSvg.h"
#include "data.h"
#include "declaracoes.h"
#include "funcQryDin.h"
#include "funcoesPrimariasDin.h"
#include "varGlobal.h"

int main(int argc, char** argv) {
    void* StDados = callocData();
    void* StVar = createVar();
    List list = Parametros(argc, argv, StVar);
    FreeLista(list, StVar);
    return 0;
}