#include <stdio.h>
#include <stdlib.h> // exit()
#include <stdbool.h>

#include "lista.h"

#include "lexica.h" // analiseLexica()
#include "sintatica.h" // analiseSintatica

int main(){
     Lista *tokens = NULL;

     // Análise Léxica
     tokens = analiseLexica();
     if(tokens == NULL)exit(EXIT_FAILURE);

     if(tamanhoLista(tokens) > 0){
          Token *token;
          int chave = 1; // 1º, 2º, 3º, ..., nº token

          while(true){
               token = consultaNo(tokens, chave);
               if(token == NULL)break;

               //printf("%d : %s\n", token->alias, token->value);

               chave++;
          }
     }else{
          exit(EXIT_FAILURE);
     }
     //

     // Análise Sintática
     analiseSintatica(tokens);

     if(tamanhoLista(tokens) == 0){
          liberaLista(tokens);

          exit(EXIT_SUCCESS);
     }else{
          liberaLista(tokens);

          exit(EXIT_FAILURE);
     }
     //
}