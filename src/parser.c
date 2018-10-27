#include "parser.h"

te_expr *_expr = NULL;
double _t = 0;
te_variable _vars[] = {{"t", &_t}};

int parser_init(){
  return parser_update("sin(t*440*6.28/44100)");
}


// return 0 if no errors
int parser_update(char * expr){
  int err;
  _expr = te_compile(expr, _vars, 1, &err);
  return err;
}

void parser_step(double delta){
  _t += delta;
}


// evaluate the expression and returns its value
double parser_eval(){
  if(_expr==NULL)
    return 10.0;
  return te_eval(_expr);
}
