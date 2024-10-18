#ifndef SINTATICA_H
#define SINTATICA_H

#include <stdbool.h>

#include "lista.h"

bool analiseSintatica(Lista *lista);
// GATILHO PARA A ANÁLISE SINTÁTICA DO BUFFER DE ENTRADA
//
// Se reconheceu, retorna verdadeiro, se não, retorna falso

Info *proxToken();
// RETORNA O PONTEIRO PARA O PŔOXIMO TOKEN NA LISTA
//
// Se não houver, retorna nulo

// ESTADOS
void PGRM(); // PGRM -> PROGRAMA id INICIO DECL CMD FIM;

void DECL(); // DECL -> TIPO SEQ_ID DECL_REC;

void DECL_REC(); // DECL_REC -> DECL | ε;

void TIPO(); // TIPO -> INTEIRO | REAL | CARACTER | CADEIA | LISTA_INT | LISTA_REAL;

void SEQ_ID(); // SEQ_ID -> id SEQ_ID_REC;

void SEQ_ID_REC(); // SEQ_ID_REC -> ',' SEQ_ID | ε;

void SEQ_ID_MUL(); // SEQ_ID_MUL -> id '[' num ']' SEQ_ID_MUL_REC;

void SEQ_ID_MUL_REC(); // SEQ_ID_MUL_REC -> ',' SEQ_ID_MUL | ε;

void CMD(); // CMD -> CMD_UNICO CMD_REC;

void CMD_REC(); // CMD_REC -> CMD CMD_REC | ε;

void CMD_UNICO(); // CMD_UNICO -> ENQUANTO EXPR_REL ENTAO CMD FIM_ENQUANTO |
                  //              SE EXPR_REL ENTAO CMD FIM_SE |
                  //              ESCREVA_CMD |
                  //              LEIA SEQ_ID |
                  //              SEQ_ID := EXPR;

void ESCREVA_CMD(); // ESCREVA_CMD -> ESCREVA str ESCREVA_REC |
                    //                ESCREVA SEQ_ID ESCREVA_REC;                

void ESCREVA_REC(); // ESCREVA_REC -> ',' ESCREVA_CMD ESCREVA_REC | ε;
//

void falha();
// TRATAMENTO DE FALHA

#endif SINTATICA_H