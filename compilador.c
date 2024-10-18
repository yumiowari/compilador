#include <stdio.h>
#include <stdlib.h> // exit()
#include <stdbool.h>

#include "lista.h"
#include "lexica.h"

int main(){
     Lista *tokens = NULL;

     tokens = analiseLexica();
     if(tokens == NULL)exit(EXIT_FAILURE);

     if(tamanhoLista(tokens) > 0){
          Info *token;
          int chave = 1; // 1º, 2º, 3º, ..., nº token

          while(true){
               token = consultaNo(tokens, chave);
               if(token == NULL)break;

               printf("%d : %s\n", token->alias, token->value);

               chave++;
          }
     }else{
          exit(EXIT_FAILURE);
     }

     liberaLista(lista);

     exit(EXIT_SUCCESS);
}