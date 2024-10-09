/*
    Para a gramática:

    G = (V, Σ, P, PGRM).

    V = {PGRM, DECL, CMD, SEQ_ID, SEQ_ID_MUL, EXPR_REL, EMPR, CMD_REC, EXPR_REC, 
         TERMO, TERMO_REC, FATOR}.

    Σ = {PROGRAMA, id, INICIO, FIM, INTEIRO, REAL, CARACTER, CADEIA, LISTA_INT, LISTA_REAL, 
         ',', '[', num, ']', ENQUANTO, ENTAO, FIM_ENQUANTO, SE, FIM_SE, ESCREVA, str, LEIA,
         .M., .m., .I., '+', '-', ':=', '*', '/', '.'}.

    P = {PGRM -> PROGRAMA id INICIO DECL CMD FIM;
         DECL -> INTEIRO SEQ_ID DECL |
                 REAL SEQ_ID DECL |
                 CARACTER SEQ_ID DECL |
                 CADEIA SEQ_ID_MUL DECL |
                 LISTA_INT SEQ_ID_MUL DECL |
                 LISTA_REAL SEQ_ID_MUL DECL;
         SEQ_ID -> id',' SEQ_ID | id;
         SEQ_ID_MUL -> id'['num']'',' SEQ_ID_MUL | id'['num']';
         CMD -> ENQUANTO EXPR_REL ENTAO CMD FIM_ENQUANTO CMD_REC |
                SE EXPR_REL ENTAO CMD FIM_SE CMD_REC |
                EXPR CMD_REC;
         CMD_REC -> CMD CMD_REC |
                    ESCREVA SEQ_ID |
                    ESCREVA str |
                    LEIA SEQ_ID | ε;
         EXPR_REL -> EXPR .M. EXPR |
                     EXPR .m. EXPR |
                     EXPR .I. EXPR;
         EXPR -> TERMO EXPR_REC;
         EXPR_REC -> '+' TERMO EXPR_REC |
                     '-' TERMO EXPR_REC |
                     ':=' TERMO EXPR_REC | ε;
         TERMO -> FATOR TERMO_REC;
         TERMO_REC -> '*' FATOR TERMO_REC |
                      '/' FATOR TERMO_REC |
                      ':=' FATOR TERMO_REC | ε;
         FATOR -> FATOR'.'num | num | id}.
*/          

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "lista.h"

#include "lexica.h"

// a leitura só termina com o fim de arquivo, ou seja, aperte Ctrl+D ;)
char *leEntrada(){
     int i = 0; // índice no buffer
     char *buffer = NULL;
     char c;

     buffer = (char*) malloc(sizeof(char));

     while(1){
          c = getchar();

          if(c == EOF){
               buffer[i] = '\0';

               break;
          }

          // ignora espaço, quebra de linha e tabulação
          while(c == ' ' || c == '\n' || c == '\t'){
               c = getchar();

               if(c == EOF){
                    buffer[i] = '\0';

                    break;
               }
          }

          buffer[i] = c;

          i++;

          // redimensiona o buffer (método lento)
          buffer = (char*) realloc(buffer, sizeof(char) * (i + 1));
     }

     if(i > 0){
          return buffer;
     }else{ // o buffer está vazio
          free(buffer);

          return NULL;
     }
}

bool forFinal(int estado){
     switch(estado){
          case 113:  return true;
          case 125:  return true;
          case 215:  return true;
          case 2215: return true;
          case 2222: return true;
          case 31:   return true;
          case 317:  return true;
          case 321:  return true;
          case 40:   return true;
          case 513:  return true;
          case 524:  return true;
          case 622:  return true;
          case 633:  return true;
          case 612:  return true;
          case 71:   return true;
          case 82:   return true;
          case 90:   return true;
          case 1001: return true;
          case 11:   return true;
          case 12:   return true;
          case 13:   return true;
          case 1400: return true;
          case 1411: return true;
          case 1421: return true;
          case 1431: return true;
          case 15:   return true;
          case 16:   return true;
          case 1700: return true;
          case 18:   return true;
          case 19:   return true;
     
          default:  return false;
     }
}

bool varredura(){
     bool flag = false; // gambiarra
     int chave = 1; // 1º, 2º, 3º, ..., nº token
     char *buffer = NULL; // buffer de entrada
     int i = 0; // índice no buffer

     Lista *tokens = fazLista();

     buffer = leEntrada();
     if(buffer == NULL){
          return false;
     }

     int estado;
     char c;

     while(flag == false){
          if(flag == false){
               c = buffer[i];

               if(c != '\0'){
                    //printf("c = %c - estado = %d\n", c, estado);
               }else{
                    if(forFinal(estado) == true){
                         // caso ainda houver um token a ser classificado

                         flag = true;
                    }else{
                         break;
                    }
               }
          }else{
               // já terminou a varredura!
          }

          switch(estado){
               case 0: // Σ
                    switch(c){
                         case 'C': estado = 1; break;
                         case 'E': estado = 2; break;
                         case 'F': estado = 3; break;
                         case 'i': estado = 4; break;
                         case 'I': estado = 5; break;
                         case 'L': estado = 6; break;
                         case 'n': estado = 7; break;
                         case 'R': estado = 8; break;
                         case 'S': estado = 9; break;
                         case 's': estado = 10; break;
                         case ',': estado = 11; break;
                         case '[': estado = 12; break;
                         case ']': estado = 13; break;
                         case '.': estado = 14; break;
                         case '+': estado = 15; break;
                         case '-': estado = 16; break;
                         case ':': estado = 17; break;
                         case '*': estado = 18; break;
                         case '/': estado = 19; break;

                         default: estado = -1; break;
                    }

                    break;

               case 1: // {CADEIA, CARACTER}
                    if(c == 'A'){
                         estado = 100;
                    }else{
                         estado = -1;
                    }

                    break;

               case 100: // {CADEIA, CARACTER}
                    if(c == 'D'){
                         estado = 110;
                    }else if(c == 'R'){
                         estado = 120;
                    }else{
                         estado = -1;
                    }

                    break;

               case 110: // {CADEIA}
                    if(c == 'E'){
                         estado = 111;
                    }else{
                         estado = -1;
                    }

                    break;

               case 111: // {CADEIA}
                    if(c == 'I'){
                         estado = 112;
                    }else{
                         estado = -1;
                    }

                    break;

               case 112: // {CADEIA}
                    if(c == 'A'){
                         estado = 113;
                    }else{
                         estado = -1;
                    }

                    break;

               /* ESTADO FINAL */
               case 113: // TOKEN_CADEIA
                    printf("CADEIA\n");

                    estado = 0;

                    i--; // retrocede

                    break;
               
               case 120: // {CARACTER}
                    if(c == 'A'){
                         estado = 121;
                    }else{
                         estado = -1;
                    }

                    break;

               case 121: // {CARACTER}
                    if(c == 'C'){
                         estado = 122;
                    }else{
                         estado = -1;
                    }

                    break;

               case 122: // {CARACTER}
                    if(c == 'T'){
                         estado = 123;
                    }else{
                         estado = -1;
                    }

                    break;

               case 123: // {CARACTER}
                    if(c == 'E'){
                         estado = 124;
                    }else{
                         estado = -1;
                    }

                    break;

               case 124: // {CARACTER}
                    if(c == 'R'){
                         estado = 125;
                    }else{
                         estado = -1;
                    }

                    break;

               /* ESTADO FINAL */
               case 125: // TOKEN_CARACTER
                    printf("CARACTER\n");

                    estado = 0;

                    i--; // retrocede

                    break;

               case 2: // {ESCREVA, ENQUANTO, ENTAO}
                    if(c == 'S'){
                         estado = 210;
                    }else if(c == 'N'){
                         estado = 2200;
                    }else{
                         estado = -1;
                    }

                    break;

               case 210: // {ESCREVA}
                    if(c == 'C'){
                         estado = 211;
                    }else{
                         estado = -1;
                    }

                    break;

               case 211: // {ESCREVA}
                    if(c == 'R'){
                         estado = 212;
                    }else{
                         estado = -1;
                    }

                    break;

               case 212: // {ESCREVA}
                    if(c == 'E'){
                         estado = 213;
                    }else{
                         estado = -1;
                    }

                    break;

               case 213: // {ESCREVA}
                    if(c == 'V'){
                         estado = 214;
                    }else{
                         estado = -1;
                    }

                    break;

               case 214: // {ESCREVA}
                    if(c == 'A'){
                         estado = 215;
                    }else{
                         estado = -1;
                    }

                    break;

               /* ESTADO FINAL */
               case 215: // TOKEN_ESCREVA
                    printf("ESCREVA\n");

                    estado = 0;

                    i--; // retrocede

                    break;

               case 2200: // {ENQUANTO, ENTAO}
                    if(c == 'Q'){
                         estado = 2210;
                    }else if(c == 'T'){
                         estado = 2220;
                    }else{
                         estado = -1;
                    }

                    break;

               case 2210: // {ENQUANTO}
                    if(c == 'U'){
                         estado = 2211;
                    }else{
                         estado = -1;
                    }

                    break;

               case 2211: // {ENQUANTO}
                    if(c == 'A'){
                         estado = 2212;
                    }else{
                         estado = -1;
                    }

                    break;

               case 2212: // {ENQUANTO}
                    if(c == 'N'){
                         estado = 2213;
                    }else{
                         estado = -1;
                    }

                    break;

               case 2213: // {ENQUANTO}
                    if(c == 'T'){
                         estado = 2214;
                    }else{
                         estado = -1;
                    }

                    break;

               case 2214: // {ENQUANTO}
                    if(c == 'O'){
                         estado = 2215;
                    }else{
                         estado = -1;
                    }

                    break;

               /* ESTADO FINAL */
               case 2215: // TOKEN_ENQUANTO
                    printf("ENQUANTO\n");

                    estado = 0;

                    i--; // retrocede

                    break;

               case 2220: // {ENTAO}
                    if(c == 'A'){
                         estado = 2221;
                    }else{
                         estado = -1;
                    }

                    break;

               case 2221: // {ENTAO}
                    if(c == 'O'){
                         estado = 2222;
                    }else{
                         estado = -1;
                    }

                    break;

               /* ESTADO FINAL */
               case 2222: // TOKEN_ENTAO
                    printf("ENTAO\n");

                    estado = 0;

                    i--; // retrocede

                    break;

               case 3: // {FIM, FIM_ENQUANTO, FIM_SE}
                    if(c == 'I'){
                         estado = 30; 
                    }else{
                         estado = -1;
                    }

                    break;

               case 30: // {FIM, FIM_ENQUANTO, FIM_SE}
                    if(c == 'M'){
                         // espia o próximo caractere
                         c = buffer[i + 1];

                         if(c != '_'){
                              estado = 31;
                         }else{
                              estado = 300;
                         }
                    }else{
                         estado = -1;
                    }

                    break;

               /* ESTADO FINAL */
               case 31: // TOKEN_FIM
                    printf("FIM\n");

                    estado = 0;

                    i--; // retrocede

                    break;

               case 300: // {FIM_ENQUANTO, FIM_SE}
                    if(c == '_'){
                         estado = 301;
                    }else{
                         estado = -1;
                    }

                    break;

               case 301: // {FIM_ENQUANTO, FIM_SE}
                    if(c == 'E'){
                         estado = 310;
                    }else if(c == 'S'){
                         estado = 320;
                    }else{
                         estado = -1;
                    }

                    break;

               case 310: // {FIM_ENQUANTO}
                    if(c == 'N'){
                         estado = 311;
                    }else{
                         estado = -1;
                    }

                    break;

               case 311: // {FIM_ENQUANTO}
                    if(c == 'Q'){
                         estado = 312;
                    }else{
                         estado = -1;
                    }
                    
                    break;

               case 312: // {FIM_ENQUANTO}
                    if(c == 'U'){
                         estado = 313;
                    }else{
                         estado = -1;
                    }

                    break;

               case 313: // {FIM_ENQUANTO}
                    if(c == 'A'){
                         estado = 314;
                    }else{
                         estado = -1;
                    }

                    break;

               case 314: // {FIM_ENQUANTO}
                    if(c == 'N'){
                         estado = 315;
                    }else{
                         estado = -1;
                    }

                    break;

               case 315: // {FIM_ENQUANTO}
                    if(c == 'T'){
                         estado = 316;
                    }else{
                         estado = -1;
                    }

                    break;

               case 316: // {FIM_ENQUANTO}
                    if(c == 'O'){
                         estado = 317;
                    }else{
                         estado = -1;
                    }

                    break;

               /* ESTADO FINAL */
               case 317: // TOKEN_FIM_ENQUANTO
                    printf("FIM_ENQUANTO\n");

                    estado = 0;

                    i--; // retrocede

                    break;

               case 320: // {FIM_SE}
                    if(c == 'E'){
                         estado = 321;
                    }else{
                         estado = -1;
                    }

                    break;

               /* ESTADO FINAL */
               case 321: // TOKEN_FIM_SE
                    printf("FIM_SE\n");

                    estado = 0;

                    i--; // retrocede

                    break;

               case 4: // {id}
                    if(c == 'd'){
                         estado = 40;
                    }else{
                         estado = -1;
                    }

                    break;

               /* ESTADO FINAL */
               case 40: // TOKEN_ID
                    printf("id\n");

                    estado = 0;

                    i--; // retrocede

                    break;

               case 5: // {INICIO, INTEIRO}
                    if(c == 'N'){
                         estado = 50;
                    }else{
                         estado = -1;
                    }

                    break;

               case 50: // {INICIO, INTEIRO}
                    if(c == 'I'){
                         estado = 510;
                    }else if(c == 'T'){
                         estado = 520;
                    }else{
                         estado = -1;
                    }

                    break;

               case 510: // {INICIO}
                    if(c == 'C'){
                         estado = 511;
                    }else{
                         estado = -1;
                    }

                    break;

               case 511: // {INICIO}
                    if(c == 'I'){
                         estado = 512;
                    }else{
                         estado = -1;
                    }

                    break;

               case 512: // {INICIO}
                    if(c == 'O'){
                         estado = 513;
                    }else{
                         estado = -1;
                    }

                    break;

               /* ESTADO FINAL */
               case 513: // TOKEN_INICIO
                    printf("INICIO\n");

                    estado = 0;

                    i--; // retrocede

                    break;

               case 520: // {INTEIRO}
                    if(c == 'E'){
                         estado = 521;
                    }else{
                         estado = -1;
                    }

                    break;

               case 521: // {INTEIRO}
                    if(c == 'I'){
                         estado = 522;
                    }else{
                         estado = -1;
                    }

                    break;

               case 522: // {INTEIRO}
                    if(c == 'R'){
                         estado = 523;
                    }else{
                         estado = -1;
                    }

                    break;

               case 523: // {INTEIRO}
                    if(c == 'O'){
                         estado = 524;
                    }else{
                         estado = -1;
                    }

                    break;

               /* ESTADO FINAL */
               case 524: // TOKEN_INTEIRO
                    printf("INTEIRO\n");

                    estado = 0;

                    i--; // retrocede

                    break;

               case 6: // {LISTA_INT, LISTA_REAL, LEIA}
                    if(c == 'I'){
                         estado = 60;
                    }else if(c == 'E'){
                         estado = 610;
                    }else{
                         estado = -1;
                    }

                    break;

               case 60: // {LISTA_INT, LISTA_REAL}
                    if(c == 'S'){
                         estado = 61;
                    }else{
                         estado = -1;
                    }

                    break;

               case 61: // {LISTA_INT, LISTA_REAL}
                    if(c == 'T'){
                         estado = 62;
                    }else{
                         estado = -1;
                    }

                    break;

               case 62: // {LISTA_INT, LISTA_REAL}
                    if(c == 'A'){
                         estado = 63;
                    }else{
                         estado = -1;
                    }

                    break;

               case 63: // {LISTA_INT, LISTA_REAL}
                    if(c == '_'){
                         estado = 64;
                    }else{
                         estado = -1;
                    }

                    break;

               case 64: // {LISTA_INT, LISTA_REAL}
                    if(c == 'I'){
                         estado = 620;
                    }else if(c == 'R'){
                         estado = 630;
                    }else{
                         estado = -1;
                    }

                    break;

               case 620: // {LISTA_INT}
                    if(c == 'N'){
                         estado = 621;
                    }else{
                         estado = -1;
                    }

                    break;

               case 621: // {LISTA_INT}
                    if(c == 'T'){
                         estado = 622;
                    }else{
                         estado = -1;
                    }

                    break;

               /* ESTADO FINAL */
               case 622: // TOKEN_LISTA_INT
                    printf("LISTA_INT\n");

                    estado = 0;

                    i--; // retrocede

                    break;

               case 630: // {LISTA_REAL}
                    if(c == 'E'){
                         estado = 631;
                    }else{
                         estado = -1;
                    }

                    break;

               case 631: // {LISTA_REAL}
                    if(c == 'A'){
                         estado = 632;
                    }else{
                         estado = -1;
                    }

                    break;

               case 632: // {LISTA_REAL}
                    if(c == 'L'){
                         estado = 633;
                    }else{
                         estado = -1;
                    }

                    break;

               /* ESTADO FINAL */
               case 633: // TOKEN_LISTA_REAL
                    printf("LISTA_REAL\n");

                    estado = 0;

                    i--; // retrocede

                    break;

               case 610: // {LEIA}
                    if(c == 'I'){
                         estado = 611;
                    }else{
                         estado = -1;
                    }

                    break;

               case 611: // {LEIA}
                    if(c == 'A'){
                         estado = 612;
                    }else{
                         estado = -1;
                    }

                    break;

               /* ESTADO FINAL */
               case 612: // TOKEN_LEIA
                    printf("LEIA\n");

                    estado = 0;

                    i--; // retrocede

                    break;

               case 7: // {num}
                    if(c == 'u'){
                         estado = 70;
                    }else{
                         estado = -1;
                    }

                    break;

               case 70: // {num}
                    if(c == 'm'){
                         estado = 71;
                    }else{
                         estado = -1;
                    }

                    break;

               /* ESTADO FINAL */
               case 71: // TOKEN_NUM
                    printf("num\n");

                    estado = 0;

                    i--; // retrocede

                    break;

               case 8: // {REAL}
                    if(c == 'E'){
                         estado = 80;
                    }else{
                         estado = -1;
                    }

                    break;

               case 80: // {REAL}
                    if(c == 'A'){
                         estado = 81;
                    }else{
                         estado = -1;
                    }

                    break;

               case 81: // {REAL}
                    if(c == 'L'){
                         estado = 82;
                    }else{
                         estado = -1;
                    }

                    break;

               /* ESTADO FINAL */
               case 82: // TOKEN_REAL
                    printf("REAL\n");

                    estado = 0;

                    i--; // retrocede

                    break;

               case 9: // {SE}
                    if(c == 'E'){
                         estado = 90;
                    }else{
                         estado = -1;
                    }
          
                    break;

               /* ESTADO FINAL */
               case 90:
                    printf("SE\n");

                    estado = 0;

                    i--; // retrocede

                    break;

               case 10: // {str}
                    if(c == 't'){
                         estado = 1000;
                    }else{
                         estado = -1;
                    }

                    break;

               case 1000: // {str}
                    if(c == 'r'){
                         estado = 1001;
                    }else{
                         estado = -1;
                    }

                    break;

               /* ESTADO FINAL */
               case 1001: // TOKEN_STR
                    printf("str\n");

                    estado = 0;

                    i--; // retrocede

                    break;

               /* ESTADO FINAL */
               case 11: // // TOKEN_VIRGULA
                    printf(",\n");

                    estado = 0;

                    i--; // retrocede

                    break;

               /* ESTADO FINAL */
               case 12: // TOKEN_ABRE_COLCHETE
                    printf("[\n");

                    estado = 0;

                    i--; // retrocede

                    break;

               /* ESTADO FINAL */
               case 13: // TOKEN_FECHA_COLCHETE
                    printf("]\n");

                    estado = 0;

                    i--; // retrocede

                    break;

               case 14: // {.M., .m., .I., '.'}
                    if(c == 'M'){
                         estado = 1410;
                    }else if(c == 'm'){
                         estado = 1420;
                    }else if(c == 'I'){
                         estado = 1430;
                    }else{
                         estado = 1400; // reconheceu '.'
                    }

                    break;

               /* ESTADO FINAL */
               case 1400: // TOKEN_PONTO
                    printf(".\n");

                    estado = 0;

                    i--; // retrocede

                    break;

               case 1410: // {.M.}
                    if(c == '.'){
                         estado = 1411;
                    }else{
                         estado = -1;
                    }

                    break;

               /* ESTADO FINAL */
               case 1411: // TOKEN_MAIOR
                    printf(".M.\n");

                    estado = 0;

                    i--; // retrocede

                    break;

               case 1420: // {.m.}
                    if(c == '.'){
                         estado = 1421;
                    }else{
                         estado = -1;
                    }

                    break;

               /* ESTADO FINAL */
               case 1421: // TOKEN_MENOR
                    printf(".m.\n");

                    estado = 0;
                    
                    i--; // retrocede

                    break;

               case 1430: // {.I.}
                    if(c == '.'){
                         estado = 1431;
                    }else{
                         return -1;
                    }

                    break;

               /* ESTADO FINAL */
               case 1431: // TOKEN_IGUAL
                    printf(".I.\n");

                    estado = 0;

                    i--; // retrocede

                    break;

               /* ESTADO FINAL */
               case 15: // TOKEN_SOMA
                    printf("+\n");

                    estado = 0;

                    i--; // retrocede

                    break;

               /* ESTADO FINAL */
               case 16: // TOKEN_SUBTRACAO
                    printf("-\n");

                    estado = 0;

                    i--; // retrocede

                    break;

               case 17: // {:=}
                    if(c == '='){
                         estado = 1700;
                    }else{
                         estado = -1;
                    }

                    break;

               /* ESTADO FINAL */
               case 1700: // TOKEN_ATRIBUICAO
                    printf(":=\n");

                    estado = 0;

                    i--; // retrocede

                    break;

               /* ESTADO FINAL */
               case 18: // TOKEN_MULTIPLICACAO
                    printf("*\n");

                    estado = 0;

                    i--; // retrocede

                    break;

               /* ESTADO FINAL */
               case 19: // // TOKEN_DIVISAO
                    printf("/\n");

                    estado = 0;

                    i--; // retrocede

                    break;

               case -1: // falha
                    //printf("falhou!\n");

                    estado = 0;

                    i--;

                    break;
          }

          i++;
     }

     printf("Varredura completa!\n");

     return true;
}