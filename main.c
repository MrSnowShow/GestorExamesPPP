#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "funcoes.h"

int main()
{
    Exame *e;
    e = cria_exame();
    print_exame(e);
    return 0;
}
