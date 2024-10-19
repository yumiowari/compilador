#ifndef SINTATICA_H
#define SINTATICA_H

#include <stdbool.h>

#include "lista.h"

void analiseSintatica(Lista *tokens);
// GATILHO PARA A ANÁLISE SINTÁTICA
//
// Recebe o ponteiro para a lista de tokens

// ESTADOS //

void PGRM(); // PGRM -> PROGRAMA id INICIO DECL CMD FIM;

void DECL(); // DECL -> TIPO SEQ_ID DECL_REC;

void DECL_REC(); // DECL_REC -> DECL DECL_REC |
                 // ε;

void TIPO(); // TIPO -> INTEIRO   |
             //         REAL      |
             //         CARACTER  |
             //         CADEIA    |
             //         LISTA_INT |
             //         LISTA_REAL;

void SEQ_ID(); // SEQ_ID -> id SEQ_ID_REC;

void SEQ_ID_REC(); // SEQ_ID_REC -> ',' SEQ_ID SEQ_ID_REC |
                   // ε;

void SEQ_ID_MUL(); // SEQ_ID_MUL -> id '[' num ']' SEQ_ID_MUL_REC;

void SEQ_ID_MUL_REC(); // SEQ_ID_MUL_REC -> ',' SEQ_ID_MUL SEQ_ID_MUL_REC |
                       // ε;

void CMD(); // CMD -> CMD_UNICO CMD_REC;

void CMD_REC(); // CMD_REC -> CMD CMD_REC |
                // ε;

void CMD_UNICO(); // CMD_UNICO -> ENQUANTO EXPR_REL ENTAO CMD FIM_ENQUANTO |
                  //              SE EXPR_REL ENTAO CMD FIM_SE             |
                  //              ESCREVA str ESCREVA_REC                  |
                  //              ESCREVA SEQ_ID ESCREVA_REC               |
                  //              LEIA SEQ_ID                              |
                  //              SEQ_ID := EXPR;

void ESCREVA_REC(); // ESCREVA_REC -> ',' str ESCREVA_REC    |
                    //                ',' SEQ_ID ESCREVA_REC |
                    //                ε;

void EXPR_REL(); // EXPR_REL -> EXPR OP_REL EXPR;

void OP_REL(); // OP_REL -> .M. |
               //           .m. |
               //           .I.;

void EXPR(); // EXPR -> TERMO EXPR_REC;

void EXPR_REC(); // EXPR_REC -> '+' TERMO EXPR_REC |
                 //             '-' TERMO EXPR_REC |
                 //             ε;

void TERMO(); // TERMO -> FATOR TERMO_REC;

void TERMO_REC(); // TERMO_REC -> '*' FATOR TERMO_REC |
                  //              '/' FATOR TERMO_REC |
                  //              ε;

void FATOR(); // FATOR -> '(' EXPR ')'  |
              //          FATOR '.' num |
              //          num           |
              //          id;

/////////////

void proxToken();
// FUNÇÃO PARA AVANÇAR O TOKEN

void falha(char *obtido, char *esperado);
// FUNÇÃO PARA FALHA NA ANÁLISE SINTÁTICA

#endif // SINTATICA_H