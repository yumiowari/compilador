#include <stdio.h>

#include "lexica.h"

int main(){
     if(analiseLexica()){
          printf("Análise Léxica bem-sucedida!\n");
     }else{
          fprintf(stderr, "Análise Léxica encerrou com erro(s).\n");
     }
}