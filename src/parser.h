#include "tinyexpr.h"
#include <stdlib.h>

int parser_init();
int parser_update(char * expr);
void parser_step(double delta);
double parser_eval();
