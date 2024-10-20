#include <stdio.h>
#include <stdlib.h> // exit()
#include <string.h> // strcmp()
#include <stdbool.h>

#include "lista.h"

#include "lexica.h" // analiseLexica()
#include "sintatica.h" // analiseSintatica()

//
// Projeto de Compiladores, 21 de outubro de 2024.
//
// Rafael Renó Corrêa, 2022000403
//

int main(int argc, char **argv){
     Lista *tokens = NULL;
     bool debug = false;
     
     if(argc > 1){
          if(strcmp(argv[1], "-d") == 0){
               printf("Executando em modo de depuração...\n");

               debug = true;
          }
     }

     // Análise Léxica
     tokens = analiseLexica(debug);
     if(tokens == NULL)exit(EXIT_FAILURE);

     if(tamanhoLista(tokens) > 0){
          Token *token;
          int chave = 1; // 1º, 2º, 3º, ..., nº token

          printf("São os tokens:\n");
          while(true){
               token = consultaNo(tokens, chave);
               if(token == NULL)break;

               printf("(%d) %d : %s\n", chave, token->alias, token->value);

               chave++;
          }
     }else{
          fprintf(stderr, "Erro: Não há tokens válidos na entrada!\n");

          exit(EXIT_FAILURE);
     }
     //

     // Análise Sintática
     if(analiseSintatica(tokens, debug) == true){
          printf("Análise Sintática bem-sucedida!\n");
     }else{
          fprintf(stderr, "Erro: Análise Sintática mal-sucedida!\n");
          
          exit(EXIT_FAILURE);
     }
     //

     exit(EXIT_SUCCESS);
}