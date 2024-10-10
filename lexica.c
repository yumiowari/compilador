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

     Dada as expressões regulares:

     id = letra(letra|digito)*

     str = '"'(letra|numero)*'"'

     num = digito*
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

          default: return false;
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
                    if(forFinal(estado) == true){ // caso ainda houver um token a ser classificado
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
                         // reconhecimento de símbolos reservados
                         case 'C': estado = 1;   break; // {CARACTER, CADEIA}
                         case 'E': estado = 13;  break; // {ENQUANTO, ENTAO, ESCREVA}
                         case 'F': estado = 30;  break; // {FIM, FIM_ENQUANTO, FIM_SE}
                         case 'I': estado = 45;  break; // {INICIO, INTEIRO}
                         case 'L': estado = 56;  break; // {LEIA, LISTA_INT, LISTA_REAL}
                         case 'P': estado = 72;  break; // {PROGRAMA}
                         case 'R': estado = 80;  break; // {REAL}
                         case 'S': estado = 84;  break; // {SE}
                         case '"': estado = 86;  break; // {str}
                         case ',': estado = 88;  break; // {','}
                         case '[': estado = 89;  break; // {'['}
                         case ']': estado = 90;  break; // {']'}
                         case '.': estado = 91;  break; // {'.M.', '.m.', '.I.', '.'}
                         case '+': estado = 99;  break; // {'+'}
                         case '-': estado = 100; break; // {'-'}
                         case ':': estado = 101; break; // {':='}
                         case '*': estado = 103; break; // {'*'}
                         case '/': estado = 104; break; // {'/'}
                         //

                         // tratamento de erro
                         default:  estado = -1;  break;
                         //
                    }

                    // {id}
                    if((c >= 'A') && (c <= 'Z') || (c >= 'a') && (c <= 'z')){ 
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
                    printf("CADEIA\n");

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
                    printf("CARACTER\n");

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
                    printf("ESCREVA\n");

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
                    printf("ENQUANTO\n");

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
                    printf("ENTAO\n");

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
                    printf("FIM\n");

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
                    printf("FIM_ENQUANTO\n");

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
                    printf("FIM_SE\n");

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
                    printf("INICIO\n");

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
                    printf("INTEIRO\n");

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
                    printf("LISTA_INT\n");

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
                    printf("LISTA_REAL\n");

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
                    printf("LEIA\n");

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
                    printf("PROGRAMA\n");

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
                    printf("REAL\n");

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
                    printf("SE\n");

                    estado = 0;

                    i--; // retrocede

                    break;
               //

               case 86: // '"'letra*'"'
                    if((c >= 'A') && (c <= 'Z') || (c >= 'a') && (c <= 'z') || (c >= '0') && (c <= '9')){
                         estado = 86;
                    }else if(c == '"'){
                         estado = 87;
                    }else{
                         estado = -1;
                    }

                    break;

               // ESTADO FINAL
               case 87: // TOKEN_STRING
                    printf("string\n");

                    estado = 0;

                    i--; // retrocede

                    break;
               //

               // ESTADO FINAL
               case 88: // TOKEN_VIRGULA
                    printf(",\n");

                    estado = 0;

                    i--; // retrocede

                    break;
               //

               // ESTADO FINAL
               case 89: // TOKEN_ABRE_COLCHETE
                    printf("[\n");

                    estado = 0;

                    i--; // retrocede

                    break;
               //

               // ESTADO FINAL
               case 90: // TOKEN_FECHA_COLCHETE
                    printf("]\n");

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
                    printf(".\n");

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
                    printf(".M.\n");

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
                    printf(".m.\n");

                    estado = 0;
                    
                    i--; // retrocede

                    break;
               //

               case 97: // {.I.}
                    if(c == '.'){
                         estado = 98;
                    }else{
                         return -1;
                    }

                    break;

               // ESTADO FINAL
               case 98: // TOKEN_IGUAL
                    printf(".I.\n");

                    estado = 0;

                    i--; // retrocede

                    break;
               //

               // ESTADO FINAL
               case 99: // TOKEN_SOMA
                    printf("+\n");

                    estado = 0;

                    i--; // retrocede

                    break;
               //

               // ESTADO FINAL
               case 100: // TOKEN_SUBTRACAO
                    printf("-\n");

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
                    printf(":=\n");

                    estado = 0;

                    i--; // retrocede

                    break;
               //

               // ESTADO FINAL
               case 103: // TOKEN_MULTIPLICACAO
                    printf("*\n");

                    estado = 0;

                    i--; // retrocede

                    break;
               //

               // ESTADO FINAL
               case 104: // // TOKEN_DIVISAO
                    printf("/\n");

                    estado = 0;

                    i--; // retrocede

                    break;
               //

               case 105: // {id}
                    if((c >= 'A') && (c <= 'Z') || (c >= 'a') && (c <= 'z') || (c >= '0') && (c <= '9')){ // // letra(letra|digito)*
                         estado = 105;
                    }else if(c == ';'){ // alcançou o ';'
                         estado = 106;
                    }else{
                         estado = -1;
                    }

                    break;

               // ESTADO FINAL
               case 106: // TOKEN_ID
                    printf("identificador\n");

                    estado = 0;

                    i--; // retrocede

                    break;
               //

               case 107: // {num}
                    if((c >= '0') && (c <= '9')){ // digito*
                         estado = 107;
                    }else if(c == ';'){ // alcançou o ';'
                         estado = 108;
                    }else{
                         estado = -1;
                    }

                    break;

               // ESTADO FINAL
               case 108: // TOKEN_NUMERO
                    printf("numero\n");

                    estado = 0;

                    i--; // retrocede

                    break;
               //

               // ESTADO DE FALHA
               case -1:
                    printf("falhou!\n");

                    estado = 0;

                    i--; // retrocede

                    break;
               //
          }

          i++;
     }

     printf("Varredura completa!\n");

     return true;
}