/*
     Para a gramática:

     G = (V, Σ, P, PGRM).

     V = {PGRM, DECL, DECL_REC, TIPO, SEQ_ID, SEQ_ID_REC, SEQ_ID_MUL, SEQ_ID_MUL_REC,
          CMD, CMD_REC, CMD_UNICO, ESCREVA_CMD, ESCREVA_REC, EXPR_REL, OP_REL, EXPR,
          EXPR_REC, TERMO, TERMO_REC, FATOR}.

     Σ = {PROGRAMA, id, INICIO, FIM, INTEIRO, REAL, CARACTER, CADEIA, LISTA_INT, LISTA_REAL,
          ',', '[', num, ']', ENQUANTO, ENTAO, FIM_ENQUANTO, SE, FIM_SE, ESCREVA, str, LEIA,
          .M., .I., '+', '-', ':=', '*', '/', '(', ')'}.

     P = {PGRM -> PROGRAMA id INICIO DECL CMD FIM;

          DECL -> TIPO SEQ_ID DECL_REC;
          DECL_REC -> DECL DECL_REC | 
                      ε;
          TIPO -> INTEIRO   |
                  REAL      |
                  CARACTER  |
                  CADEIA    |
                  LISTA_INT |
                  LISTA_REAL;

          SEQ_ID -> id SEQ_ID_REC;
          SEQ_ID_REC -> ',' SEQ_ID SEQ_ID_REC |
                        ε;

          SEQ_ID_MUL -> id '[' num ']' SEQ_ID_MUL_REC;
          SEQ_ID_MUL_REC -> ',' SEQ_ID_MUL SEQ_ID_MUL_REC |
                            ε;

          CMD -> CMD_UNICO CMD_REC;
          CMD_REC -> CMD CMD_REC |
                     ε;
          CMD_UNICO -> ENQUANTO EXPR_REL ENTAO CMD FIM_ENQUANTO |
                       SE EXPR_REL ENTAO CMD FIM_SE             |
                       ESCREVA str ESCREVA_REC                  |
                       ESCREVA SEQ_ID ESCREVA_REC               |
                       LEIA SEQ_ID                              |
                       SEQ_ID := EXPR;
                         
          ESCREVA_REC -> ',' ESCREVA_CMD ESCREVA_REC |
                         ε;

          EXPR_REL -> EXPR OP_REL EXPR;
          OP_REL -> .M. |
                    .m. |
                    .I.;

          EXPR -> TERMO EXPR_REC;
          EXPR_REC -> '+' TERMO EXPR_REC |
                      '-' TERMO EXPR_REC |
                      ε;

          TERMO -> FATOR TERMO_REC;
          TERMO_REC -> '*' FATOR TERMO_REC |
                       '/' FATOR TERMO_REC |
                       ε;

          FATOR -> '(' EXPR ')' |
                   FATOR '.' num |
                   num |
                   id;
     }.

     Dadas as expressões regulares:

     id = letra(letra|digito)*

     str = '\''(letra|numero)*'\''

     num = digito*
*/          
          

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> // strcpy()

#include "lista.h"

#include "lexica.h"

// a leitura só termina com o fim de arquivo, ou seja, aperte Ctrl+D ;)
char *preencheEntrada(){
     int i = 0; // índice no buffer
     char *buffer = NULL;
     int buffer_size = 1024;
     char c;

     buffer = (char*) malloc(sizeof(char) * buffer_size);

     while(true){
          c = getchar();

          if(c == EOF){
               buffer[i] = '\0';

               break;
          }

          // ignora comentários
          if(c == '{'){
               while(c != '}'){
                    c = getchar();

                    if(c == EOF){
                         buffer[i] = '\0';
                    
                         break;
                    }
               }

               c = getchar(); // consome '}'
          }
          //

          buffer[i] = c;

          i++;

          // redimensiona o buffer (método rápido)
          if(i >= buffer_size){
               buffer_size += 1024; // aumenta o buffer em 1KB

               buffer = (char*) realloc(buffer, sizeof(char) * buffer_size);
          }
     }

     if(i > 0){
          return buffer;
     }else{
          free(buffer);

          return NULL;
     }
}

bool verificaFinal(int estado){
     switch(estado){
          case 6:   return true; // TOKEN_CADEIA
          case 12:  return true; // TOKEN_CARACTER
          case 19:  return true; // TOKEN_ESCREVA
          case 26:  return true; // TOKEN_ENQUANTO
          case 29:  return true; // TOKEN_ENTAO
          case 32:  return true; // TOKEN_FIM
          case 42:  return true; // TOKEN_FIM_ENQUANTO
          case 44:  return true; // TOKEN_FIM_SE
          case 50:  return true; // TOKEN_INICIO
          case 55:  return true; // TOKEN_INTEIRO
          case 64:  return true; // TOKEN_LISTA_INT
          case 68:  return true; // TOKEN_LISTA_REAL
          case 71:  return true; // TOKEN_LEIA
          case 79:  return true; // TOKEN_PROGRAMA
          case 83:  return true; // TOKEN_REAL
          case 85:  return true; // TOKEN_SE
          case 87:  return true; // TOKEN_STRING
          case 88:  return true; // TOKEN_VIRGULA
          case 89:  return true; // TOKEN_ABRE_COLCHETE
          case 90:  return true; // TOKEN_FECHA_COLCHETE
          case 92:  return true; // TOKEN_PONTO
          case 94:  return true; // TOKEN_MAIOR
          case 96:  return true; // TOKEN_MENOR
          case 98:  return true; // TOKEN_IGUAL
          case 99:  return true; // TOKEN_SOMA
          case 100: return true; // TOKEN_SUBTRACAO
          case 102: return true; // TOKEN_ATRIBUICAO
          case 103: return true; // TOKEN_MULTIPLICACAO
          case 104: return true; // TOKEN_DIVISAO
          case 106: return true; // TOKEN_IDENTIFICADOR
          case 108: return true; // TOKEN_NUMERO
          case 109: return true; // TOKEN_ABRE_PARENTESES
          case 110: return true; // TOKEN_FECHA_PARENTESES

          default: return false;
     }
}

Lista *analiseLexica(){
     bool flag = false; // condição de parada

     // para a varredura
     bool flagErro = false; // para caso de erro
     char *buffer = NULL; // buffer de entrada
     int i = 0; // índice no buffer
     int estado;
     char c;

     buffer = preencheEntrada();
     if(buffer == NULL)return NULL;
     //

     // para a classificação
     char auxBffr[1024];
     int j = 0; // índice no buffer auxiliar
     Lista *tokens = NULL;
     int chave = 1; // 1º, 2º, 3º, ..., nº token
     Token dados;

     tokens = fazLista();
     if(tokens == NULL)return NULL;
     //
     
     while(!flag){
          if(!flag){
               c = buffer[i];

               if(c != '\0'){
                    //printf("c = %c - estado = %d\n", c, estado);
               }else{
                    if(verificaFinal(estado)){ // caso ainda houver algum token a ser classificado
                         flag = true;
                    }else{
                         break;
                    }
               }
          }

          switch(estado){
               case 0: // Σ
                    switch(c){
                         // reconhecimento de símbolos reservados
                         case 'C': estado = 1;   break; // {CARACTER, CADEIA}
                         case 'E': estado = 13;  break; // {ENQUANTO, ENTAO, ESCREVA}
                         case 'F': estado = 30;  break; // {FIM, FIM_ENQUANTO, FIM_SE}
                         case 'I': estado = 45;  break; // {INICIO, INTEIRO}
                         case 'L': estado = 56;  break; // {LEIA, LISTA_INT, LISTA_REAL}
                         case 'P': estado = 72;  break; // {PROGRAMA}
                         case 'R': estado = 80;  break; // {REAL}
                         case 'S': estado = 84;  break; // {SE}
                         case '\'': estado = 86; break; // {str}
                         case ',': estado = 88;  break; // {','}
                         case '[': estado = 89;  break; // {'['}
                         case ']': estado = 90;  break; // {']'}
                         case '.': estado = 91;  break; // {'.M.', '.m.', '.I.', '.'}
                         case '+': estado = 99;  break; // {'+'}
                         case '-': estado = 100; break; // {'-'}
                         case ':': estado = 101; break; // {':='}
                         case '*': estado = 103; break; // {'*'}
                         case '/': estado = 104; break; // {'/'}
                         case '(': estado = 109; break; // {'('}
                         case ')': estado = 110; break; // {')'}
                         //

                         // tratamento de erro
                         default:  estado = -1;  break;
                         //
                    }

                    // tratamento de espaços, quebra de linha e tabulação
                    if((c == ' ') || (c == '\n') || (c == '\t')){
                         estado -2;
                    }
                    //

                    // {id}
                    if(
                       ((c >= 'A') && (c <= 'Z')) ||
                       ((c >= 'a') && (c <= 'z'))
                      )
                    { 
                         if(
                            c != 'C' &&
                            c != 'E' &&
                            c != 'F' &&
                            c != 'I' &&
                            c != 'L' &&
                            c != 'P' &&
                            c != 'R' &&
                            c != 'S'
                           )
                         {
                              estado = 105;
                         }
                    }
                    //

                    // {num}
                    if((c >= '0') && (c <= '9')){
                         estado = 107;
                    }
                    //

                    break;

               case 1: // {CADEIA, CARACTER}
                    if(c == 'A'){
                         estado = 2;
                    }else{
                         estado = -1;
                    }

                    break;

               case 2: // {CADEIA, CARACTER}
                    if(c == 'D'){
                         estado = 3;
                    }else if(c == 'R'){
                         estado = 7;
                    }else{
                         estado = -1;
                    }

                    break;

               case 3: // {CADEIA}
                    if(c == 'E'){
                         estado = 4;
                    }else{
                         estado = -1;
                    }

                    break;

               case 4: // {CADEIA}
                    if(c == 'I'){
                         estado = 5;
                    }else{
                         estado = -1;
                    }

                    break;

               case 5: // {CADEIA}
                    if(c == 'A'){
                         estado = 6;
                    }else{
                         estado = -1;
                    }

                    break;

               // ESTADO FINAL
               case 6: // TOKEN_CADEIA
                    //printf("TOKEN_CADEIA\n");
                    dados.alias = TOKEN_CADEIA;
                    strcpy(dados.value, "CADEIA");

                    insereNo(tokens, chave, &dados, "back");
                    chave++;

                    estado = 0;

                    i--; // retrocede

                    break;
               //
               
               case 7: // {CARACTER}
                    if(c == 'A'){
                         estado = 8;
                    }else{
                         estado = -1;
                    }

                    break;

               case 8: // {CARACTER}
                    if(c == 'C'){
                         estado = 9;
                    }else{
                         estado = -1;
                    }

                    break;

               case 9: // {CARACTER}
                    if(c == 'T'){
                         estado = 10;
                    }else{
                         estado = -1;
                    }

                    break;

               case 10: // {CARACTER}
                    if(c == 'E'){
                         estado = 11;
                    }else{
                         estado = -1;
                    }

                    break;

               case 11: // {CARACTER}
                    if(c == 'R'){
                         estado = 12;
                    }else{
                         estado = -1;
                    }

                    break;

               // ESTADO FINAL
               case 12: // TOKEN_CARACTER
                    //printf("TOKEN_CARACTER\n");
                    dados.alias = TOKEN_CARACTER;
                    strcpy(dados.value, "CARACTER");

                    insereNo(tokens, chave, &dados, "back");
                    chave++;

                    estado = 0;

                    i--; // retrocede

                    break;
               //

               case 13: // {ESCREVA, ENQUANTO, ENTAO}
                    if(c == 'S'){
                         estado = 14;
                    }else if(c == 'N'){
                         estado = 20;
                    }else{
                         estado = -1;
                    }

                    break;

               case 14: // {ESCREVA}
                    if(c == 'C'){
                         estado = 15;
                    }else{
                         estado = -1;
                    }

                    break;

               case 15: // {ESCREVA}
                    if(c == 'R'){
                         estado = 16;
                    }else{
                         estado = -1;
                    }

                    break;

               case 16: // {ESCREVA}
                    if(c == 'E'){
                         estado = 17;
                    }else{
                         estado = -1;
                    }

                    break;

               case 17: // {ESCREVA}
                    if(c == 'V'){
                         estado = 18;
                    }else{
                         estado = -1;
                    }

                    break;

               case 18: // {ESCREVA}
                    if(c == 'A'){
                         estado = 19;
                    }else{
                         estado = -1;
                    }

                    break;

               // ESTADO FINAL
               case 19: // TOKEN_ESCREVA
                    //printf("TOKEN_ESCREVA\n");
                    dados.alias = TOKEN_ESCREVA;
                    strcpy(dados.value, "ESCREVA");

                    insereNo(tokens, chave, &dados, "back");
                    chave++;

                    estado = 0;

                    i--; // retrocede

                    break;
               //

               case 20: // {ENQUANTO, ENTAO}
                    if(c == 'Q'){
                         estado = 21;
                    }else if(c == 'T'){
                         estado = 27;
                    }else{
                         estado = -1;
                    }

                    break;

               case 21: // {ENQUANTO}
                    if(c == 'U'){
                         estado = 22;
                    }else{
                         estado = -1;
                    }

                    break;

               case 22: // {ENQUANTO}
                    if(c == 'A'){
                         estado = 23;
                    }else{
                         estado = -1;
                    }

                    break;

               case 23: // {ENQUANTO}
                    if(c == 'N'){
                         estado = 24;
                    }else{
                         estado = -1;
                    }

                    break;

               case 24: // {ENQUANTO}
                    if(c == 'T'){
                         estado = 25;
                    }else{
                         estado = -1;
                    }

                    break;

               case 25: // {ENQUANTO}
                    if(c == 'O'){
                         estado = 26;
                    }else{
                         estado = -1;
                    }

                    break;

               // ESTADO FINAL
               case 26: // TOKEN_ENQUANTO
                    //printf("TOKEN_ENQUANTO\n");
                    dados.alias = TOKEN_ENQUANTO;
                    strcpy(dados.value, "ENQUANTO");

                    insereNo(tokens, chave, &dados, "back");
                    chave++;

                    estado = 0;

                    i--; // retrocede

                    break;
               //

               case 27: // {ENTAO}
                    if(c == 'A'){
                         estado = 28;
                    }else{
                         estado = -1;
                    }

                    break;

               case 28: // {ENTAO}
                    if(c == 'O'){
                         estado = 29;
                    }else{
                         estado = -1;
                    }

                    break;

               // ESTADO FINAL
               case 29: // TOKEN_ENTAO
                    //printf("TOKEN_ENTAO\n");
                    dados.alias = TOKEN_ENTAO;
                    strcpy(dados.value, "ENTAO");

                    insereNo(tokens, chave, &dados, "back");
                    chave++;

                    estado = 0;

                    i--; // retrocede

                    break;
               //

               case 30: // {FIM, FIM_ENQUANTO, FIM_SE}
                    if(c == 'I'){
                         estado = 31; 
                    }else{
                         estado = -1;
                    }

                    break;

               case 31: // {FIM, FIM_ENQUANTO, FIM_SE}
                    if(c == 'M'){
                         c = buffer[i + 1]; // espia o próximo caractere

                         if(c != '_'){
                              estado = 32;
                         }else{
                              estado = 33;
                         }
                    }else{
                         estado = -1;
                    }

                    break;

               // ESTADO FINAL
               case 32: // TOKEN_FIM
                    //printf("TOKEN_FIM\n");
                    dados.alias = TOKEN_FIM;
                    strcpy(dados.value, "FIM");

                    insereNo(tokens, chave, &dados, "back");
                    chave++;

                    estado = 0;

                    i--; // retrocede

                    break;
               //

               case 33: // {FIM_ENQUANTO, FIM_SE}
                    if(c == '_'){
                         estado = 34;
                    }else{
                         estado = -1;
                    }

                    break;

               case 34: // {FIM_ENQUANTO, FIM_SE}
                    if(c == 'E'){
                         estado = 35;
                    }else if(c == 'S'){
                         estado = 43;
                    }else{
                         estado = -1;
                    }

                    break;

               case 35: // {FIM_ENQUANTO}
                    if(c == 'N'){
                         estado = 36;
                    }else{
                         estado = -1;
                    }

                    break;

               case 36: // {FIM_ENQUANTO}
                    if(c == 'Q'){
                         estado = 37;
                    }else{
                         estado = -1;
                    }
                    
                    break;

               case 37: // {FIM_ENQUANTO}
                    if(c == 'U'){
                         estado = 38;
                    }else{
                         estado = -1;
                    }

                    break;

               case 38: // {FIM_ENQUANTO}
                    if(c == 'A'){
                         estado = 39;
                    }else{
                         estado = -1;
                    }

                    break;

               case 39: // {FIM_ENQUANTO}
                    if(c == 'N'){
                         estado = 40;
                    }else{
                         estado = -1;
                    }

                    break;

               case 40: // {FIM_ENQUANTO}
                    if(c == 'T'){
                         estado = 41;
                    }else{
                         estado = -1;
                    }

                    break;

               case 41: // {FIM_ENQUANTO}
                    if(c == 'O'){
                         estado = 42;
                    }else{
                         estado = -1;
                    }

                    break;

               // ESTADO FINAL
               case 42: // TOKEN_FIM_ENQUANTO
                    //printf("TOKEN_FIM_ENQUANTO\n");
                    dados.alias = TOKEN_FIM_ENQUANTO;
                    strcpy(dados.value, "FIM_ENQUANTO");

                    insereNo(tokens, chave, &dados, "back");
                    chave++;

                    estado = 0;

                    i--; // retrocede

                    break;
               //

               case 43: // {FIM_SE}
                    if(c == 'E'){
                         estado = 44;
                    }else{
                         estado = -1;
                    }

                    break;

               // ESTADO FINAL
               case 44: // TOKEN_FIM_SE
                    //printf("TOKEN_FIM_SE\n");
                    dados.alias = TOKEN_FIM_SE;
                    strcpy(dados.value, "FIM_SE");

                    insereNo(tokens, chave, &dados, "back");
                    chave++;

                    estado = 0;

                    i--; // retrocede

                    break;
               //

               case 45: // {INICIO, INTEIRO}
                    if(c == 'N'){
                         estado = 46;
                    }else{
                         estado = -1;
                    }

                    break;

               case 46: // {INICIO, INTEIRO}
                    if(c == 'I'){
                         estado = 47;
                    }else if(c == 'T'){
                         estado = 51;
                    }else{
                         estado = -1;
                    }

                    break;

               case 47: // {INICIO}
                    if(c == 'C'){
                         estado = 48;
                    }else{
                         estado = -1;
                    }

                    break;

               case 48: // {INICIO}
                    if(c == 'I'){
                         estado = 49;
                    }else{
                         estado = -1;
                    }

                    break;

               case 49: // {INICIO}
                    if(c == 'O'){
                         estado = 50;
                    }else{
                         estado = -1;
                    }

                    break;

               // ESTADO FINAL
               case 50: // TOKEN_INICIO
                    //printf("TOKEN_INICIO\n");
                    dados.alias = TOKEN_INICIO;
                    strcpy(dados.value, "INICIO");

                    insereNo(tokens, chave, &dados, "back");
                    chave++;

                    estado = 0;

                    i--; // retrocede

                    break;
               //

               case 51: // {INTEIRO}
                    if(c == 'E'){
                         estado = 52;
                    }else{
                         estado = -1;
                    }

                    break;

               case 52: // {INTEIRO}
                    if(c == 'I'){
                         estado = 53;
                    }else{
                         estado = -1;
                    }

                    break;

               case 53: // {INTEIRO}
                    if(c == 'R'){
                         estado = 54;
                    }else{
                         estado = -1;
                    }

                    break;

               case 54: // {INTEIRO}
                    if(c == 'O'){
                         estado = 55;
                    }else{
                         estado = -1;
                    }

                    break;

               // ESTADO FINAL
               case 55: // TOKEN_INTEIRO
                    //printf("TOKEN_INTEIRO\n");
                    dados.alias = TOKEN_INTEIRO;
                    strcpy(dados.value, "INTEIRO");

                    insereNo(tokens, chave, &dados, "back");
                    chave++;

                    estado = 0;

                    i--; // retrocede

                    break;
               //

               case 56: // {LISTA_INT, LISTA_REAL, LEIA}
                    if(c == 'I'){
                         estado = 57;
                    }else if(c == 'E'){
                         estado = 69;
                    }else{
                         estado = -1;
                    }

                    break;

               case 57: // {LISTA_INT, LISTA_REAL}
                    if(c == 'S'){
                         estado = 58;
                    }else{
                         estado = -1;
                    }

                    break;

               case 58: // {LISTA_INT, LISTA_REAL}
                    if(c == 'T'){
                         estado = 59;
                    }else{
                         estado = -1;
                    }

                    break;

               case 59: // {LISTA_INT, LISTA_REAL}
                    if(c == 'A'){
                         estado = 60;
                    }else{
                         estado = -1;
                    }

                    break;

               case 60: // {LISTA_INT, LISTA_REAL}
                    if(c == '_'){
                         estado = 61;
                    }else{
                         estado = -1;
                    }

                    break;

               case 61: // {LISTA_INT, LISTA_REAL}
                    if(c == 'I'){
                         estado = 62;
                    }else if(c == 'R'){
                         estado = 65;
                    }else{
                         estado = -1;
                    }

                    break;

               case 62: // {LISTA_INT}
                    if(c == 'N'){
                         estado = 63;
                    }else{
                         estado = -1;
                    }

                    break;

               case 63: // {LISTA_INT}
                    if(c == 'T'){
                         estado = 64;
                    }else{
                         estado = -1;
                    }

                    break;

               // ESTADO FINAL
               case 64: // TOKEN_LISTA_INT
                    //printf("TOKEN_LISTA_INT\n");
                    dados.alias = TOKEN_LISTA_INT;
                    strcpy(dados.value, "LISTA_INT");

                    insereNo(tokens, chave, &dados, "back");
                    chave++;

                    estado = 0;

                    i--; // retrocede

                    break;
               //

               case 65: // {LISTA_REAL}
                    if(c == 'E'){
                         estado = 66;
                    }else{
                         estado = -1;
                    }

                    break;

               case 66: // {LISTA_REAL}
                    if(c == 'A'){
                         estado = 67;
                    }else{
                         estado = -1;
                    }

                    break;

               case 67: // {LISTA_REAL}
                    if(c == 'L'){
                         estado = 68;
                    }else{
                         estado = -1;
                    }

                    break;

               // ESTADO FINAL
               case 68: // TOKEN_LISTA_REAL
                    //printf("TOKEN_LISTA_REAL\n");
                    dados.alias = TOKEN_LISTA_REAL;
                    strcpy(dados.value, "LISTA_REAL");

                    insereNo(tokens, chave, &dados, "back");
                    chave++;

                    estado = 0;

                    i--; // retrocede

                    break;
               //

               case 69: // {LEIA}
                    if(c == 'I'){
                         estado = 70;
                    }else{
                         estado = -1;
                    }

                    break;

               case 70: // {LEIA}
                    if(c == 'A'){
                         estado = 71;
                    }else{
                         estado = -1;
                    }

                    break;

               // ESTADO FINAL
               case 71: // TOKEN_LEIA
                    //printf("TOKEN_LEIA\n");
                    dados.alias = TOKEN_LEIA;
                    strcpy(dados.value, "LEIA");

                    insereNo(tokens, chave, &dados, "back");
                    chave++;

                    estado = 0;

                    i--; // retrocede

                    break;
               //

               case 72:
                    if(c == 'R'){
                         estado = 73;
                    }else{
                         estado = -1;
                    }

                    break;

               case 73:
                    if(c == 'O'){
                         estado = 74;
                    }else{
                         estado = -1;
                    }

                    break;

               case 74:
                    if(c == 'G'){
                         estado = 75;
                    }else{
                         estado = -1;
                    }

                    break;

               case 75:
                    if(c == 'R'){
                         estado = 76;
                    }else{
                         estado = -1;
                    }

                    break;

               case 76:
                    if(c == 'A'){
                         estado = 77;
                    }else{
                         estado = -1;
                    }

                    break;

               case 77:
                    if(c == 'M'){
                         estado = 78;
                    }else{
                         estado = -1;
                    }

                    break;

               case 78:
                    if(c == 'A'){
                         estado = 79;
                    }else{
                         estado = -1;
                    }

                    break;

               // ESTADO FINAL
               case 79: // TOKEN_PROGRAMA
                    //printf("TOKEN_PROGRAMA\n");
                    dados.alias = TOKEN_PROGRAMA;
                    strcpy(dados.value, "PROGRAMA");

                    insereNo(tokens, chave, &dados, "back");
                    chave++;

                    estado = 0;

                    i--; // retrocede

                    break;
               //

               case 80: // {REAL}
                    if(c == 'E'){
                         estado = 81;
                    }else{
                         estado = -1;
                    }

                    break;

               case 81: // {REAL}
                    if(c == 'A'){
                         estado = 82;
                    }else{
                         estado = -1;
                    }

                    break;

               case 82: // {REAL}
                    if(c == 'L'){
                         estado = 83;
                    }else{
                         estado = -1;
                    }

                    break;

               // ESTADO FINAL
               case 83: // TOKEN_REAL
                    //printf("TOKEN_REAL\n");
                    dados.alias = TOKEN_REAL;
                    strcpy(dados.value, "REAL");

                    insereNo(tokens, chave, &dados, "back");
                    chave++;

                    estado = 0;

                    i--; // retrocede

                    break;
               //

               case 84: // {SE}
                    if(c == 'E'){
                         estado = 85;
                    }else{
                         estado = -1;
                    }
          
                    break;

               // ESTADO FINAL
               case 85: // TOKEN_SE
                    //printf("TOKEN_SE\n");
                    dados.alias = TOKEN_SE;
                    strcpy(dados.value, "SE");

                    insereNo(tokens, chave, &dados, "back");
                    chave++;

                    estado = 0;

                    i--; // retrocede

                    break;
               //

               case 86: // {str}
                    if(((c >= ' ') && (c <= '~')) && (c != '\'')){ // '\''letra*'\''
                         estado = 86;
                    }else if(c == '\''){
                         estado = 87;

                         auxBffr[j] = c;

                         j++;

                         break;
                    }else{
                         estado = -1;
                    }

                    // espia o caractere que trouxe ao estado e copia para o buffer auxiliar
                    auxBffr[j] = buffer[i - 1];
                    j++;

                    break;

               // ESTADO FINAL
               case 87: // TOKEN_STRING
                    //printf("TOKEN_STRING\n");
                    dados.alias = TOKEN_STRING;
                    auxBffr[j] = '\0';
                    strcpy(dados.value, auxBffr);
                    j = 0;

                    insereNo(tokens, chave, &dados, "back");
                    chave++;


                    estado = 0;

                    i--; // retrocede

                    break;
               //

               // ESTADO FINAL
               case 88: // TOKEN_VIRGULA
                    //printf("TOKEN_VIRGULA\n");
                    dados.alias = TOKEN_VIRGULA;
                    strcpy(dados.value, ",");

                    insereNo(tokens, chave, &dados, "back");
                    chave++;

                    estado = 0;

                    i--; // retrocede

                    break;
               //

               // ESTADO FINAL
               case 89: // TOKEN_ABRE_COLCHETE
                    //printf("TOKEN_ABRE_COLCHETE\n");
                    dados.alias = TOKEN_ABRE_COLCHETE;
                    strcpy(dados.value, "[");

                    insereNo(tokens, chave, &dados, "back");
                    chave++;

                    estado = 0;

                    i--; // retrocede

                    break;
               //

               // ESTADO FINAL
               case 90: // TOKEN_FECHA_COLCHETE
                    //printf("TOKEN_FECHA_COLCHETE\n");
                    dados.alias = TOKEN_FECHA_COLCHETE;
                    strcpy(dados.value, "]");

                    insereNo(tokens, chave, &dados, "back");
                    chave++;

                    estado = 0;

                    i--; // retrocede

                    break;
               //

               case 91: // {.M., .m., .I., '.'}
                    if(c == 'M'){
                         estado = 93;
                    }else if(c == 'm'){
                         estado = 95;
                    }else if(c == 'I'){
                         estado = 97;
                    }else{
                         estado = 92; // reconheceu '.'

                         i--; // retrocede
                    }

                    break;

               // ESTADO FINAL
               case 92: // TOKEN_PONTO
                    //printf("TOKEN_PONTO\n");
                    dados.alias = TOKEN_PONTO;
                    strcpy(dados.value, ".");

                    insereNo(tokens, chave, &dados, "back");
                    chave++;

                    estado = 0;

                    i--; // retrocede

                    break;
               //

               case 93: // {.M.}
                    if(c == '.'){
                         estado = 94;
                    }else{
                         estado = -1;
                    }

                    break;

               // ESTADO FINAL
               case 94: // TOKEN_MAIOR
                    //printf("TOKEN_MAIOR\n");
                    dados.alias = TOKEN_MAIOR;
                    strcpy(dados.value, ".M.");

                    insereNo(tokens, chave, &dados, "back");
                    chave++;

                    estado = 0;

                    i--; // retrocede

                    break;
               //

               case 95: // {.m.}
                    if(c == '.'){
                         estado = 96;
                    }else{
                         estado = -1;
                    }

                    break;

               // ESTADO FINAL
               case 96: // TOKEN_MENOR
                    //printf("TOKEN_MENOR\n");
                    dados.alias = TOKEN_MENOR;
                    strcpy(dados.value, ".m.");

                    insereNo(tokens, chave, &dados, "back");
                    chave++;

                    estado = 0;
                    
                    i--; // retrocede

                    break;
               //

               case 97: // {.I.}
                    if(c == '.'){
                         estado = 98;
                    }else{
                         estado = -1;
                    }

                    break;

               // ESTADO FINAL
               case 98: // TOKEN_IGUAL
                    //printf("TOKEN_IGUAL\n");
                    dados.alias = TOKEN_IGUAL;
                    strcpy(dados.value, ".I.");

                    insereNo(tokens, chave, &dados, "back");
                    chave++;

                    estado = 0;

                    i--; // retrocede

                    break;
               //

               // ESTADO FINAL
               case 99: // TOKEN_SOMA
                    //printf("TOKEN_SOMA\n");
                    dados.alias = TOKEN_SOMA;
                    strcpy(dados.value, "+");

                    insereNo(tokens, chave, &dados, "back");
                    chave++;

                    estado = 0;

                    i--; // retrocede

                    break;
               //

               // ESTADO FINAL
               case 100: // TOKEN_SUBTRACAO
                    //printf("TOKEN_SUBTRACAO\n");
                    dados.alias = TOKEN_SUBTRACAO;
                    strcpy(dados.value, "-");

                    insereNo(tokens, chave, &dados, "back");
                    chave++;

                    estado = 0;

                    i--; // retrocede

                    break;
               //

               case 101: // {:=}
                    if(c == '='){
                         estado = 102;
                    }else{
                         estado = -1;
                    }

                    break;

               // ESTADO FINAL
               case 102: // TOKEN_ATRIBUICAO
                    //printf("TOKEN_ATRIBUICAO\n");
                    dados.alias = TOKEN_ATRIBUICAO;
                    strcpy(dados.value, ":=");

                    insereNo(tokens, chave, &dados, "back");
                    chave++;

                    estado = 0;

                    i--; // retrocede

                    break;
               //

               // ESTADO FINAL
               case 103: // TOKEN_MULTIPLICACAO
                    //printf("TOKEN_MULTIPLICACAO\n");
                    dados.alias = TOKEN_MULTIPLICACAO;
                    strcpy(dados.value, "*");

                    insereNo(tokens, chave, &dados, "back");
                    chave++;

                    estado = 0;

                    i--; // retrocede

                    break;
               //

               // ESTADO FINAL
               case 104: // // TOKEN_DIVISAO
                    //printf("TOKEN_DIVISAO\n");
                    dados.alias = TOKEN_DIVISAO;
                    strcpy(dados.value, "/");

                    insereNo(tokens, chave, &dados, "back");
                    chave++;

                    estado = 0;

                    i--; // retrocede

                    break;
               //

               case 105: // {id}
                    if( 
                       ((c >= 'A') && (c <= 'Z')) ||
                       ((c >= 'a') && (c <= 'z')) ||
                       ((c >= '0') && (c <= '9')) ||
                       (c == '_')
                      ) // letra(letra|digito)*
                    {
                         estado = 105;
                    }else if((c == '[') || (c == ']')){ // em caso de array
                         estado = 106;

                         // espia o caractere antes de retroceder
                         auxBffr[j] = buffer[i - 1];
                         j++;

                         i--; // retrocede

                         break;
                    }else if(c == ','){ // em caso de vários identificadores
                         estado = 106;

                         // espia o caractere antes de retroceder
                         auxBffr[j] = buffer[i - 1];
                         j++;

                         i--; // retrocede

                         break;
                    }else{
                         estado = 106;
                    }

                    // espia o caractere que trouxe ao estado e copia para o buffer auxiliar
                    auxBffr[j] = buffer[i - 1];
                    j++;

                    break;

               // ESTADO FINAL
               case 106: // TOKEN_IDENTIFICADOR
                    //printf("TOKEN_IDENTIFICADOR\n");
                    dados.alias = TOKEN_IDENTIFICADOR;
                    auxBffr[j] = '\0';
                    strcpy(dados.value, auxBffr);
                    j = 0;

                    insereNo(tokens, chave, &dados, "back");
                    chave++;

                    estado = 0;

                    i--; // retrocede

                    break;
               //

               case 107: // {num}
                    if((c >= '0') && (c <= '9')){ // digito*
                         estado = 107;
                    }else if((c == '[') || (c == ']')){ // em caso de array
                         estado = 108;

                         // espia o caractere antes de retroceder
                         auxBffr[j] = buffer[i - 1];
                         j++;

                         i--; // retrocede

                         break;
                    }else{
                         estado = 108;
                    }

                    // espia o caractere que trouxe ao estado e copia para o buffer auxiliar
                    auxBffr[j] = buffer[i - 1];
                    j++;

                    break;

               // ESTADO FINAL
               case 108: // TOKEN_NUMERO
                    //printf("TOKEN_NUMERO\n");
                    dados.alias = TOKEN_NUMERO;
                    auxBffr[j] = '\0';
                    strcpy(dados.value, auxBffr);
                    j = 0;

                    insereNo(tokens, chave, &dados, "back");
                    chave++;

                    estado = 0;

                    i--; // retrocede

                    break;
               //

               // ESTADO FINAL
               case 109: // TOKEN_ABRE_PARENTESES
                    //printf("TOKEN_ABRE_PARENTESES\n");
                    dados.alias = TOKEN_ABRE_PARENTESES;
                    strcpy(dados.value, "(");

                    insereNo(tokens, chave, &dados, "back");
                    chave++;

                    estado = 0;

                    i--; // retrocede

                    break;
               //

               // ESTADO FINAL
               case 110: // TOKEN_FECHA_PARENTESES
                    //printf("TOKEN_FECHA_PARENTESES\n");
                    dados.alias = TOKEN_FECHA_PARENTESES;
                    strcpy(dados.value, ")");

                    insereNo(tokens, chave, &dados, "back");
                    chave++;

                    estado = 0;

                    i--; // retrocede

                    break;
               //

               // TRATAMENTO DE ERRO
               case -1:
                    c = buffer[i - 1];
                    if((c == ' ') || (c == '\n') || (c == '\t')){
                         estado = -2;

                         i--; // retrocede
                    }else{
                         flagErro = true;

                         estado = 0;

                         i--; // retrocede
                    }
                    

                    break;
               //

               // TRATAMENTO DE ESPAÇO, QUEBRA DE LINHA E TABULAÇÃO
               case -2: // {' ', '\n', '\t'}
                    if((c == ' ') || (c == '\n') || (c == '\t')){
                         estado = -2;
                    }else{
                         estado = 0;

                         i--; // retrocede
                    }

                    break;
               //
          }

          i++;
     }

     if(!flagErro){
          printf("Análise Léxica bem-sucedida!\n");
     }else{
          fprintf(stderr, "Análise Léxica encerrou com erro(s).\n");
     }

     return tokens;
}