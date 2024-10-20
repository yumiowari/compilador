/*
    Para a gramática:

    G = (V, Σ, P, PGRM).

    V = {PGRM, DECL, TIPO, SEQ_ID, SEQ_ID_REC, TIPO_MUL, SEQ_ID_MUL, SEQ_ID_MUL_REC, 
         CMD, ESCREVA_REC, EXPR_REL, EXPR, EXPR_REC, TERMO, TERMO_REC, FATOR}.

    Σ = {PROGRAMA, id, INICIO, FIM, INTEIRO, REAL, CARACTER, ',', CADEIA, LISTA_INT,
         LISTA_REAL, '[', num, ']', ENQUANTO, SE, ENTAO, FIM_SE, ESCREVA, str, LEIA,
         ':=', .M., .m., .I., '+', '-', '*', '/', '(', ')', FIM_ENQUANTO}.

    P = {
         PGRM -> PROGRAMA id INICIO DECL CMD FIM;

         DECL -> TIPO SEQ_ID DECL         |
                 TIPO_MUL SEQ_ID_MUL DECL |
                 ε;

         TIPO -> INTEIRO | REAL | CARACTER;

         SEQ_ID -> id SEQ_ID_REC;

         SEQ_ID_REC -> ',' id SEQ_ID_REC | ε;

         TIPO_MUL -> CADEIA | LISTA_INT | LISTA_REAL;

         SEQ_ID_MUL -> id '[' num ']' SEQ_ID_MUL_REC |
                       id '[' id ']' SEQ_ID_MUL_REC;

         SEQ_ID_MUL_REC -> ',' id '[' num ']' SEQ_ID_MUL_REC |
                           ',' id '[' id ']' SEQ_ID_MUL_REC  |
                           ε;

         CMD -> ENQUANTO EXPR_REL CMD FIM_ENQUANTO CMD |
                SE EXPR_REL ENTAO CMD FIM_SE CMD       |
                ESCREVA str ESCREVA_REC CMD            |
                ESCREVA id ESCREVA_REC CMD             |
                ESCREVA id '[' num ']' ESCREVA_REC CMD |
                ESCREVA id '[' id ']' ESCREVA_REC CMD  |
                LEIA SEQ_ID CMD                        |
                LEIA SEQ_ID_MUL CMD                    |
                SEQ_ID := EXPR CMD                     |
                ε;

         ESCREVA_REC -> ',' str ESCREVA_REC            |
                        ',' id ESCREVA_REC             |
                        ',' id '[' num ']' ESCREVA_REC |
                        ',' id '[' id ']' ESCREVA_REC  |
                        ε;

         EXPR_REL -> EXPR .M. EXPR |
                     EXPR .m. EXPR |
                     EXPR .I. EXPR;

         EXPR -> TERMO EXPR_REC;

         EXPR_REC -> '+' TERMO EXPR_REC |
                     '-' TERMO EXPR_REC |
                     ε;

         TERMO -> FATOR TERMO_REC;

         TERMO_REC -> '*' FATOR TERMO_REC |
                      '/' FATOR TERMO_REC |
                      ε;

         FATOR -> '(' EXPR ')'   |
                  num            |
                  num '.' num    |
                  id             |
                  id '[' num ']' |
                  id '[' id ']';
        }.

    id = letra(dígito|letra)*

    str = '\''(letra|dígito)*'\''

    num = dígitodígito*
*/

//
// Implementação de Analisador Sintático Recursivo
//
// Projeto de Compiladores, 21 de outubro de 2024.
//
// Rafael Renó Corrêa, 2022000403
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "lista.h"

#include "sintatica.h"

// VARIÁVEIS GLOBAIS //
bool debug = false;
Token *token; // token atual
Lista *tokens; // lista de tokens
int chave = 1; // chave na lista
///////////////////////

bool analiseSintatica(Lista *ptr, bool flag){
    debug = flag;
    tokens = ptr;
    if(tokens == NULL)return false;

    return PGRM();
}

// ESTADOS //

bool PGRM(){ // PGRM -> PROGRAMA id INICIO DECL CMD FIM;
    proxToken("PGRM", "PROGRAMA");

    if(token->alias == TOKEN_PROGRAMA){
        proxToken("PGRM", "id");

        if(token->alias == TOKEN_IDENTIFICADOR){
            proxToken("PGRM", "INICIO");

            if(token->alias == TOKEN_INICIO){
                DECL();
                CMD();

                proxToken("PGRM", "FIM");

                if(token->alias == TOKEN_FIM){
                    return true;
                }else return false;
            }else falha("PGRM", "INICIO", token->value);
        }else falha("PGRM", "id", token->value);
    }else falha("PGRM", "PROGRAMA", token->value);
}

void DECL(){ // DECL -> TIPO SEQ_ID DECL         |
             //         TIPO_MUL SEQ_ID_MUL DECL |
             //         ε;
    proxToken("DECL", "INTEIRO, REAL, CARACTER, CADEIA, LISTA_INT ou LISTA_REAL"); // espia o próximo token
    if( // DECL -> TIPO SEQ_ID DECL;
        token->alias == TOKEN_INTEIRO ||
        token->alias == TOKEN_REAL    ||
        token->alias == TOKEN_CARACTER 
    ){
        if(debug)printf("Retrocedeu...\n");
        chave--; // retrocede o token

        TIPO();
        SEQ_ID();
        DECL();
    }else if( // DECL -> TIPO_MUL SEQ_ID_MUL DECL;
        token->alias == TOKEN_CADEIA    ||
        token->alias == TOKEN_LISTA_INT ||
        token->alias == TOKEN_LISTA_REAL
    ){
        if(debug)printf("Retrocedeu...\n");
        chave--; // retrocede o token

        TIPO_MUL();
        SEQ_ID_MUL();
        DECL();
    }else{ // DECL -> ε;
        if(debug)printf("Retrocedeu...\n");
        chave--; // retrocede o token
    }
}

void TIPO(){ // TIPO -> INTEIRO | REAL | CARACTER;
    proxToken("TIPO", "INTEIRO, REAL ou CARACTER");

    if(
        token->alias == TOKEN_INTEIRO ||
        token->alias == TOKEN_REAL    ||
        token->alias == TOKEN_CARACTER 
    ){}else falha("TIPO", "INTEIRO, REAL ou CARACTER", token->value);
}

void SEQ_ID(){ // SEQ_ID -> id SEQ_ID_REC | ε;
    proxToken("SEQ_ID", "id");

    if(token->alias == TOKEN_IDENTIFICADOR){
        SEQ_ID_REC();
    }else falha("SEQ_ID", "id", token->value);
}

void SEQ_ID_REC(){ // SEQ_ID_REC -> ',' id SEQ_ID_REC | ε;
    proxToken("SEQ_ID_REC", "','");

    if(token->alias == TOKEN_VIRGULA){
        proxToken("SEQ_ID_REC", "id");

        if(token->alias == TOKEN_IDENTIFICADOR){
            SEQ_ID_REC();
        }else falha("SEQ_ID_REC", "id", token->value);
    }else{ // SEQ_ID_REC -> ε;
        if(debug)printf("Retrocedeu...\n");
        chave--; // retrocede o token
    }
}

void TIPO_MUL(){ // TIPO_MUL -> CADEIA | LISTA_INT | LISTA_REAL;
    proxToken("TIPO_MUL", "CADEIA, LISTA_INT ou LISTA_REAL");

    if(
        token->alias == TOKEN_CADEIA    ||
        token->alias == TOKEN_LISTA_INT ||
        token->alias == TOKEN_LISTA_REAL 
    ){}else falha("TIPO_MUL", "CADEIA, LISTA_INT ou LISTA_REAL", token->value);
}

void SEQ_ID_MUL(){ // SEQ_ID_MUL -> id '[' num ']' SEQ_ID_MUL_REC |
                   //               id '[' id ']' SEQ_ID_MUL_REC;
    proxToken("SEQ_ID_MUL", "id");

    if(token->alias == TOKEN_IDENTIFICADOR){
        proxToken("SEQ_ID_MUL", "'['");

        if(token->alias == TOKEN_ABRE_COLCHETES){
            proxToken("SEQ_ID_MUL", "num");

            if(
                token->alias == TOKEN_NUMERO        ||
                token->alias == TOKEN_IDENTIFICADOR
            ){
                proxToken("SEQ_ID_MUL", "']'");

                if(token->alias == TOKEN_FECHA_COLCHETES){
                    SEQ_ID_MUL_REC();
                }else falha("SEQ_ID_MUL", "']'", token->value);
            }else falha("SEQ_ID_MUL", "num", token->value);
        }else falha("SEQ_ID_MUL", "'['", token->value);
    }else falha("SEQ_ID_MUL", "id", token->value);
}

void SEQ_ID_MUL_REC(){ // SEQ_ID_MUL_REC -> ',' id '[' num ']' SEQ_ID_MUL_REC |
                       //                   ',' id '[' id ']' SEQ_ID_MUL_REC  |
                       //                   ε;
    proxToken("SEQ_ID_MUL_REC", "','");

    if(token->alias == TOKEN_VIRGULA){
        proxToken("SEQ_ID_MUL_REC", "id");

        if(token->alias == TOKEN_IDENTIFICADOR){
            proxToken("SEQ_ID_MUL_REC", "'['");

            if(token->alias == TOKEN_ABRE_COLCHETES){
                proxToken("SEQ_ID_MUL_REC", "num");

                if(
                    token->alias == TOKEN_NUMERO        ||
                    token->alias == TOKEN_IDENTIFICADOR
                ){
                    proxToken("SEQ_ID_MUL_REC", "']'");

                    if(token->alias == TOKEN_FECHA_COLCHETES){
                        SEQ_ID_MUL_REC();
                    }else falha("SEQ_ID_MUL_REC", "']'", token->value);
                }else falha("SEQ_ID_MUL_REC", "num", token->value);
            }else falha("SEQ_ID_MUL_REC", "'['", token->value);
        }else falha("SEQ_ID_MUL_REC", "id", token->value);
    }else{ // SEQ_ID_MUL_REC -> ε;
        if(debug)printf("Retrocedeu...\n");
        chave--; // retrocede o token
    }
}

void CMD(){ // CMD -> ENQUANTO EXPR_REL CMD FIM_ENQUANTO CMD |
            //        SE EXPR_REL ENTAO CMD FIM_SE CMD       |
            //        ESCREVA str ESCREVA_REC CMD            |
            //        ESCREVA id ESCREVA_REC CMD             |
            //        ESCREVA id '[' num ']' ESCREVA_REC CMD |
            //        ESCREVA id '[' id ']' ESCREVA_REC CMD  |
            //        LEIA SEQ_ID CMD                        |
            //        LEIA SEQ_ID_MUL CMD                    |
            //        SEQ_ID := EXPR CMD                     |
            //        ε;
    proxToken("CMD", "ENQUANTO, SE, ESCREVA, LEIA ou id");

    switch(token->alias){
        case TOKEN_ENQUANTO: // CMD -> ENQUANTO EXPR_REL ENTAO CMD FIM_ENQUANTO CMD;
            EXPR_REL();
            CMD();

            proxToken("CMD", "FIM_ENQUANTO");

            if(token->alias == TOKEN_FIM_ENQUANTO){
                CMD();
            }else falha("CMD", "FIM_ENQUANTO", token->value);

            break;

        case TOKEN_SE: // CMD -> SE EXPR_REL ENTAO CMD FIM_SE CMD;
            EXPR_REL();

            proxToken("CMD", "ENTAO");

            if(token->alias == TOKEN_ENTAO){
                CMD();

                proxToken("CMD", "FIM_SE");

                if(token->alias == TOKEN_FIM_SE){
                    CMD();
                }else falha("CMD", "FIM_SE", token->value);
            }else falha("CMD", "ENTAO", token->value);

            break;

        case TOKEN_ESCREVA: // CMD -> ESCREVA str ESCREVA_REC CMD            |
                            //        ESCREVA id ESCREVA_REC CMD             |
                            //        ESCREVA id '[' num ']' ESCREVA_REC CMD |
                            //        ESCREVA id '[' id ']' ESCREVA_REC CMD;
            proxToken("CMD", "str ou id");

            if(token->alias == TOKEN_STRING){ // CMD -> ESCREVA str ESCREVA_REC CMD;
                ESCREVA_REC();
                CMD();
            }else if(token->alias == TOKEN_IDENTIFICADOR){
                proxToken("CMD", "["); // espia o próximo token

                if(token->alias == TOKEN_ABRE_COLCHETES){
                    proxToken("CMD", "num ou id");

                    if(
                        token->alias == TOKEN_NUMERO        || // CMD -> ESCREVA id '[' num ']' ESCREVA_REC CMD;
                        token->alias == TOKEN_IDENTIFICADOR    // CMD -> ESCREVA id '[' id ']' ESCREVA_REC CMD;
                    ){
                        proxToken("CMD", "]");

                        if(token->alias == TOKEN_FECHA_COLCHETES){
                            ESCREVA_REC();
                            CMD();
                        }else falha("CMD", "]", token->value);
                    }else falha("CMD", "num ou id", token->value);
                }else{ // CMD -> ESCREVA id ESCREVA_REC CMD;
                    if(debug)printf("Retrocedeu...\n");
                    chave--; // retrocede o token

                    ESCREVA_REC();
                    CMD();
                }
            }else falha("CMD", "str ou id", token->value);

            break;

        case TOKEN_LEIA: // CMD -> LEIA SEQ_ID CMD |
                         //        LEIA SEQ_ID_MUL CMD;
            proxToken("CMD", "id"); // espia o próximo token

            if(token->alias == TOKEN_IDENTIFICADOR){
                proxToken("CMD", "'['"); // espia o token depois do próximo

                if(token->alias == TOKEN_ABRE_COLCHETES){ // CMD -> LEIA SEQ_ID_MUL CMD;
                    if(debug)printf("Retrocedeu...\n");
                    if(debug)printf("Retrocedeu...\n");
                    chave -= 2; // retrocede o token duas vezes

                    SEQ_ID_MUL();
                    CMD();
                }else{ // CMD -> LEIA SEQ_ID CMD;
                    if(debug)printf("Retrocedeu...\n");
                    if(debug)printf("Retrocedeu...\n");
                    chave -= 2; // retrocede o token duas vezes

                    SEQ_ID();
                    CMD();
                }
            }else falha("CMD", "id", token->value);

            break;

        case TOKEN_IDENTIFICADOR: // CMD -> SEQ_ID := EXPR CMD;
            if(debug)printf("Retrocedeu...\n");
            chave--; // retrocede o token

            SEQ_ID();

            proxToken("CMD", ":=");
            
            if(token->alias == TOKEN_ATRIBUICAO){
                EXPR();
                CMD();
            }else falha("CMD", ":=", token->value);

            break;

        default: // CMD -> ε;
            if(debug)printf("Retrocedeu...\n");
            chave--; // retrocede o token

            break;
    }
}

void ESCREVA_REC(){ // ESCREVA_REC -> ',' str ESCREVA_REC            |
                    //                ',' id ESCREVA_REC             |
                    //                ',' id '[' num ']' ESCREVA_REC |
                    //                ',' id '[' id ']' ESCREVA_REC  |
                    //                ε;
    proxToken("ESCREVA_REC", "','");

    if(token->alias == TOKEN_VIRGULA){
        proxToken("ESCREVA_REC", "str ou id");

        if(token->alias == TOKEN_STRING){ // ESCREVA_REC -> ',' str ESCREVA_REC;
            ESCREVA_REC();
        }else if(token->alias == TOKEN_IDENTIFICADOR){
            proxToken("ESCREVA_REC", "'['"); // espia o próximo token

            if(token->alias == TOKEN_ABRE_COLCHETES){
                proxToken("ESCREVA_REC", "num ou id");

                if(
                    token->alias == TOKEN_NUMERO        || // ESCREVA_REC -> ',' id '[' num ']' ESCREVA_REC;
                    token->alias == TOKEN_IDENTIFICADOR    // ESCREVA_REC -> ',' id '[' id ']' ESCREVA_REC;
                ){
                    proxToken("ESCREVA_REC", "]");

                    if(token->alias == TOKEN_FECHA_COLCHETES){
                        ESCREVA_REC();
                    }else falha("ESCREVA_REC", "]", token->value);
                }else falha("ESCREVA_REC", "num ou id", token->value);
            }else{ // ESCREVA_REC -> ',' id ESCREVA_REC;
                if(debug)printf("Retrocedeu...\n");
                chave--; // retrocede o token
            }
        }else falha("ESCREVA_REC", "str ou id", token->value);
    }else{ // ESCREVA_REC -> ε;
        if(debug)printf("Retrocedeu...\n");
        chave--; // retrocede o token
    }
}

void EXPR_REL(){ // EXPR_REL -> EXPR .M. EXPR |
                 //             EXPR .m. EXPR |
                 //             EXPR .I. EXPR;
    EXPR();

    proxToken("EXPR_REL", ".M., .m. ou .I.");

    if(
        token->alias == TOKEN_MAIOR ||
        token->alias == TOKEN_MENOR ||
        token->alias == TOKEN_IGUAL
    ){
        EXPR();
    }else falha("EXPR_REL", ".M., .m. ou .I.", token->value);
}

void EXPR(){ // EXPR -> TERMO EXPR_REC;
    TERMO();
    EXPR_REC();
}

void EXPR_REC(){ // EXPR_REC -> '+' TERMO EXPR_REC |
                 //             '-' TERMO EXPR_REC |
                 //             ε;
    proxToken("EXPR_REC", "'+' ou '-'");

    if(
        token->alias == TOKEN_SOMA ||
        token->alias == TOKEN_SUBTRACAO
    ){
        TERMO();
        EXPR_REC();
    }else{ // EXPR_REC -> ε;
        if(debug)printf("Retrocedeu...\n");
        chave--; // retrocede o token
    }
}

void TERMO(){ // TERMO -> FATOR TERMO_REC;
    FATOR();
    TERMO_REC();
}


void TERMO_REC(){ // TERMO_REC -> '*' FATOR TERMO_REC |
                  //              '/' FATOR TERMO_REC |
                  //              ε;
    proxToken("TERMO_REC", "'*' ou '/'");

    if(
        token->alias == TOKEN_MULTIPLICACAO ||
        token->alias == TOKEN_DIVISAO
    ){
        FATOR();
        TERMO_REC();
    }else{ // TERMO_REC -> ε;
        if(debug)printf("Retrocedeu...\n");
        chave--; // retrocede o token
    }
}

void FATOR(){ // FATOR -> '(' EXPR ')'   |
              //          num            |
              //          num '.' num    |
              //          id             |
              //          id '[' num ']' |
              //          id '[' id ']';
    proxToken("FATOR", "'(', num ou id");

    if(token->alias == TOKEN_ABRE_PARENTESES){
        EXPR();

        proxToken("FATOR", "')'");

        if(token->alias == TOKEN_FECHA_PARENTESES){
            // FATOR -> '(' EXPR ')';
        }else falha("FATOR", "')'", token->value);
    }else if(token->alias == TOKEN_NUMERO){
        proxToken("FATOR", "'.'");

        if(token->alias == TOKEN_PONTO){
            proxToken("FATOR", "num");

            if(token->alias == TOKEN_NUMERO){
                // FATOR -> num '.' num;
            }else falha("FATOR", "num", token->value);
        }else{ // FATOR -> num;
            if(debug)printf("Retrocedeu...\n");
            chave--; // retrocede o token
        }
    }else if(token->alias == TOKEN_IDENTIFICADOR){
        proxToken("FATOR", "'['");

        if(token->alias == TOKEN_ABRE_COLCHETES){
            proxToken("FATOR", "num ou id");

            if(
                token->alias == TOKEN_NUMERO        ||
                token->alias == TOKEN_IDENTIFICADOR
            ){
                proxToken("FATOR", "']'");

                if(token->alias == TOKEN_FECHA_COLCHETES){
                    // FATOR -> id '[' num ']' | id '[' id ']';
                }else falha("FATOR", "']'", token->value);
            }else falha("FATOR", "num ou id", token->value);
        }else{ // FATOR -> id;
            if(debug)printf("Retrocedeu...\n");
            chave--; // retrocede o token
        }
    }else falha("FATOR", "'(', num ou id", token->value);
}

/////////////

void proxToken(char *estado, char *tokenEsperado){
    token = consultaNo(tokens, chave);
    if(token == NULL){
        if(debug)fprintf(stderr, "Erro: Fim de arquivo inesperado.\n");

        exit(EXIT_FAILURE);
    }

    chave++;

    if(debug)printf("(%s : %d) %s : %s\n", estado, chave, tokenEsperado, token->value);
}

void falha(char *estado, char *tokenEsperado, char *tokenObtido){
    if(debug)fprintf(stderr, "Erro: (%s : %d) %s : %s\n", estado, chave, tokenEsperado, tokenObtido);
}