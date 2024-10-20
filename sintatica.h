#ifndef SINTATICA_H
#define SINTATICA_H

#include <stdbool.h>

#include "lista.h"

bool analiseSintatica(Lista *tokens, bool debug);

// ESTADOS //

bool PGRM(); // PGRM -> PROGRAMA id INICIO DECL CMD FIM;

void DECL(); // DECL -> TIPO SEQ_ID DECL         |
             //         TIPO_MUL SEQ_ID_MUL DECL |
             //         ε;

void TIPO(); // TIPO -> INTEIRO | REAL | CARACTER | CADEIA;

void SEQ_ID(); // SEQ_ID -> id SEQ_ID_REC;

void SEQ_ID_REC(); // SEQ_ID_REC -> ',' id SEQ_ID_REC | ε;

void TIPO_MUL(); // TIPO_MUL -> LISTA_INT | LISTA_REAL;

void SEQ_ID_MUL(); // SEQ_ID_MUL -> id '[' num ']' SEQ_ID_MUL_REC |
                   //               id '[' id ']' SEQ_ID_MUL_REC;

void SEQ_ID_MUL_REC(); // SEQ_ID_MUL_REC -> ',' id '[' num ']' SEQ_ID_MUL_REC |
                       //                   ',' id '[' id ']' SEQ_ID_MUL_REC  |
                       //                   ε;

void CMD(); // CMD -> ENQUANTO EXPR_REL CMD FIM_ENQUANTO CMD |
            //        SE EXPR_REL ENTAO CMD FIM_SE CMD       |
            //        ESCREVA str ESCREVA_REC CMD            |
            //        ESCREVA id ESCREVA_REC CMD             |
            //        ESCREVA id '[' num ']' ESCREVA_REC CMD |
            //        ESCREVA id '[' id ']' ESCREVA_REC CMD  |
            //        LEIA SEQ_ID CMD                        |
            //        LEIA SEQ_ID_MUL CMD                    |
            //        SEQ_ID := EXPR CMD                     |
            //        ε;

void ESCREVA_REC(); // ESCREVA_REC -> ',' str ESCREVA_REC            |
                    //                ',' id ESCREVA_REC             |
                    //                ',' id '[' num ']' ESCREVA_REC |
                    //                ',' id '[' id ']' ESCREVA_REC  |
                    //                ε;

void EXPR_REL(); // EXPR_REL -> EXPR .M. EXPR |
                 //             EXPR .m. EXPR |
                 //             EXPR .I. EXPR;

void EXPR(); // EXPR -> TERMO EXPR_REC;

void EXPR_REC(); // EXPR_REC -> '+' TERMO EXPR_REC |
                 //             '-' TERMO EXPR_REC |
                 //             ε;

void TERMO(); // TERMO -> FATOR TERMO_REC;

void TERMO_REC(); // TERMO_REC -> '*' FATOR TERMO_REC |
                  //              '/' FATOR TERMO_REC |
                  //              ε;

void FATOR(); // FATOR -> '(' EXPR ')'   |
              //          num            |
              //          num '.' num    |
              //          id             |
              //          id '[' num ']' |
              //          id '[' id ']';

/////////////

void proxToken(char *estado, char *tokenEsperado);

void falha(char *estado, char *tokenEsperado, char *tokenObtido);

#endif // SINTATICA_H