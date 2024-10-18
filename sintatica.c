#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "lista.h"

#include "sintatica.h"

int chave = 1;

Info *token;
Lista *lista;

bool analiseSintatica(Lista *ptr){ // S -> PGRM;
    lista = ptr;
    
    PGRM();
}

void PGRM(){ // PGRM -> PROGRAMA id INICIO DECL CMD FIM;
    token = proxToken();

    if(token->alias == TOKEN_PROGRAMA){
        token = proxToken();

        if(token->alias == TOKEN_IDENTIFICADOR){
            token = proxToken();

            if(token->alias == TOKEN_INICIO){
                token = proxToken();

                DECL();
                CMD();

                if(token->alias == TOKEN_FIM){
                    printf("Reconheceu!\n");
                }else{
                    printf("Não reconheceu.\n")
                }
            }else falha();
        }else falha();
    }else falha();
}

void DECL(){ // DECL -> TIPO SEQ_ID DECL_REC;
    TIPO();
    SEQ_ID();
    DECL_REC();
}

void DECL_REC(){ // DECL_REC -> DECL | ε;
    DECL();
}

void TIPO(){ // TIPO -> INTEIRO | REAL | CARACTER | CADEIA | LISTA_INT | LISTA_REAL;
    token = proxToken();

    if(token.alias == TOKEN_INTEIRO){

    }else if(token.alias == TOKEN_REAL){

    }else if(token.alias == TOKEN_CARACTER){

    }else if(token.alias == TOKEN_CADEIA){

    }else if(token.alias == TOKEN_LISTA_INT){

    }else if(token.alias == TOKEN_REAL){

    }else falha();
}

void SEQ_ID(){ // SEQ_ID -> id SEQ_ID_REC;
    token = proxToken();

    if(token.alias == TOKEN_IDENTIFICADOR){
        SEQ_ID_REC();
    }else falha();
}

void SEQ_ID_REC(){ // SEQ_ID_REC -> ',' SEQ_ID | ε;
    token = proxToken();

    if(token.alias == TOKEN_VIRGULA){
        SEQ_ID();
    }else{
        // SEQ_ID_REC -> ε;
    }
}

void SEQ_ID_MUL(){ // SEQ_ID_MUL -> id '[' num ']' SEQ_ID_MUL_REC;
    token = proxToken();

    if(token.alias == TOKEN_IDENTIFICADOR){
        token = proxToken();

        if(token.alias == TOKEN_ABRE_COLCHETE){
            token = proxToken();

            if(token.alias == TOKEN_NUMERO){
                token = proxToken();

                if(token.alias == TOKEN_FECHA_COLCHETE){
                    SEQ_ID_MUL_REC();
                }else falha();
            }else falha();
        }else falha();
    }else falha();
}

void SEQ_ID_MUL_REC(){ // SEQ_ID_MUL_REC -> ',' SEQ_ID_MUL | ε;
    token = proxToken();

    if(token.alias == TOKEN_VIRGULA){
        SEQ_ID_MUL();
    }else{
        // SEQ_ID_MUL_REC -> ε;
    }
}

void CMD(){ // CMD -> CMD_UNICO CMD_REC;
    CMD_UNICO();
    CMD_REC();
}

void CMD_REC(){ // CMD_REC -> CMD CMD_REC | ε;
    CMD();
    CMD_REC();
}

void CMD_UNICO(){
    token = proxToken();

    if(token.alias == TOKEN_ENQUANTO){ // CMD_UNICO -> ENQUANTO EXPR_REL ENTAO CMD FIM_ENQUANTO;
        EXPR_REL();

        token = proxToken();

        if(token.alias == TOKEN_ENTAO){
            CMD();

            token = proxToken();

            if(token.alias == TOKEN_FIM_ENQUANTO){

            }else falha();
        }else falha();
    }else if(token.alias == TOKEN_SE){ // CMD_UNICO -> SE EXPR_REL ENTAO CMD FIM_SE;
        EXPR_REL();

        token = proxToken();

        if(token.alias == TOKEN_ENTAO){
            CMD();

            token = proxToken();

            if(token.alias == TOKEN_FIM_SE){

            }else falha();
        }else falha();
    }else if(token.alias == TOKEN_ESCREVA){ // CMD_UNICO -> ESCREVA_CMD;
        ESCREVA_CMD();
    }else if(token.alias == TOKEN_LEIA){ // CMD_UNICO -> LEIA SEQ_ID;
        SEQ_ID();
    }else{ // CMD_UNICO -> SEQ_ID := EXPR;
        SEQ_ID();

        token = proxToken();

        if(token.alias == TOKEN_ATRIBUICAO){
            EXPR();
        }else falha();
    }
}

void ESCREVA_CMD(){
    token = proxToken();

    if(token.alias == TOKEN_ESCREVA){
        token = proxToken();

        if(token.alias == TOKEN_STRING){ // ESCREVA_CMD -> ESCREVA str ESCREVA_REC;
            ESCREVA_REC();
        }else{ // ESCREVA_CMD -> ESCREVA SEQ_ID ESCREVA_REC;
            SEQ_ID();
            ESCREVA_REC();
        }
    }else falha();
}

void void ESCREVA_REC(){ // ESCREVA_REC -> ',' SEQ_ID ESCREVA_REC | ε;
    token = proxToken();

    if(token.alias == TOKEN_VIRGULA){
        ESCREVA_CMD();
        ESCREVA_REC();
    }else{
        // ESCREVA_REC -> ε
    }
}

Info *proxToken(){
    Info *ptr; // ponteiro para o token

    ptr = consultaNo(lista, chave);
    if(ptr == NULL)return NULL;
    
    chave++;

    return ptr;
}

void falha(){
    printf("Falhou!\n");
}