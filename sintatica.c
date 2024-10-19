#include <stdio.h>
#include <stdlib.h> // exit()
#include <stdbool.h>

#include "lista.h"

#include "sintatica.h"

Token *token;
Lista *tokens;
int chave = 1;

void analiseSintatica(Lista *ptr_tokens){ // S -> PGRM
    tokens = ptr_tokens;
    if(tokens == NULL){
        fprintf(stderr, "Erro: a lista de tokens nunca foi alocada.\n");
        
        exit(EXIT_FAILURE);
    }

    PGRM();
}

// ESTADOS //

void PGRM(){ // PGRM -> PROGRAMA id INICIO DECL CMD FIM;
    proxToken();

    if(token->alias == TOKEN_PROGRAMA){
        proxToken();

        if(token->alias == TOKEN_IDENTIFICADOR){
            proxToken();

            if(token->alias == TOKEN_INICIO){
                DECL();
                CMD();

                proxToken();

                if(token->alias == TOKEN_FIM){
                    printf("Análise Sintática concluída com sucesso!\n");
                }else falha(token->value, "FIM");
            }else falha(token->value, "INICIO");
        }else falha(token->value, "id");
    }else falha(token->value, "PROGRAMA");
}

void DECL(){ // DECL -> TIPO SEQ_ID DECL_REC;
    TIPO();
    SEQ_ID();
    DECL_REC();
}

void DECL_REC(){ // DECL_REC -> DECL DECL_REC |
                 //             ε;
    DECL();
    DECL_REC();
}

void TIPO(){ // TIPO -> INTEIRO   |
             //         REAL      |
             //         CARACTER  |
             //         CADEIA    |
             //         LISTA_INT |
             //         LISTA_REAL;
    proxToken();

    if(
        token->alias == TOKEN_INTEIRO    || // TIPO -> INTEIRO;
        token->alias == TOKEN_REAL       || // TIPO -> REAL;
        token->alias == TOKEN_CARACTER   || // TIPO -> CARACTER;
        token->alias == TOKEN_CADEIA     || // TIPO -> CADEIA;
        token->alias == TOKEN_LISTA_INT  || // TIPO -> LISTA_INT;
        token->alias == TOKEN_LISTA_REAL    // TIPO-> LISTA_REAL;
    ){}else falha(token->value, "TIPO");
}

void SEQ_ID(){ // SEQ_ID -> id SEQ_ID_REC;
    proxToken();

    if(token->alias == TOKEN_IDENTIFICADOR){
        SEQ_ID_REC();
    }else falha(token->value, "id");
}

void SEQ_ID_REC(){ // SEQ_ID_REC -> ',' SEQ_ID SEQ_ID_REC |
                   //               ε;
    proxToken();

    if(token->alias == TOKEN_VIRGULA){
        SEQ_ID();
        SEQ_ID_REC();
    }else{} // SEQ_ID_REC -> ε;
}

void SEQ_ID_MUL(){ // SEQ_ID_MUL -> id '[' num ']' SEQ_ID_MUL_REC;
    proxToken();

    if(token->alias == TOKEN_IDENTIFICADOR){
        proxToken();

        if(token->alias == TOKEN_ABRE_COLCHETE){
            proxToken();

            if(token->alias == TOKEN_NUMERO){
                proxToken();

                if(token->alias == TOKEN_FECHA_COLCHETE){
                    SEQ_ID_MUL_REC();
                }else falha(token->value, "]");
            }else falha(token->value, "num");
        }else falha(token->value, "[");
    }else falha(token->value, "id");
}

void SEQ_ID_MUL_REC(){ // SEQ_ID_MUL_REC -> ',' SEQ_ID_MUL SEQ_ID_MUL_REC |
                       // ε;
    proxToken();

    if(token->alias == TOKEN_VIRGULA){
        SEQ_ID_MUL();
        SEQ_ID_MUL_REC();
    }else{} // SEQ_ID_REC -> ε;
}

void CMD(){ // CMD -> CMD_UNICO CMD_REC;
    CMD_UNICO();
    CMD_REC();
}

void CMD_REC(){ // CMD_REC -> CMD CMD_REC |
                // ε;
    CMD();
    CMD_REC();
}

void CMD_UNICO(){ // CMD_UNICO -> ENQUANTO EXPR_REL ENTAO CMD FIM_ENQUANTO |
                  //              SE EXPR_REL ENTAO CMD FIM_SE             |
                  //              ESCREVA str ESCREVA_REC                  |
                  //              ESCREVA SEQ_ID ESCREVA_REC               |
                  //              LEIA SEQ_ID                              |
                  //              SEQ_ID := EXPR;
    proxToken();

    if(token->alias == TOKEN_ENQUANTO){ // CMD_UNICO -> ENQUANTO EXPR_REL ENTAO CMD FIM_ENQUANTO;
        EXPR_REL();

        proxToken();

        if(token->alias == TOKEN_ENTAO){
            CMD();

            if(token->alias == TOKEN_FIM_ENQUANTO){}else falha(token->value, "FIM_ENQUANTO");
        }else falha(token->value, "ENTAO");
    }else if(token ->alias == TOKEN_SE){ // CMD_UNICO -> SE EXPR_REL ENTAO CMD FIM_SE;
        EXPR_REL();

        proxToken();

        if(token->alias == TOKEN_ENTAO){
            CMD();

            if(token->alias == TOKEN_FIM_SE){}else falha(token->value, "FIM_SE");
        }else falha(token->value, "ENTAO");
    }else if(token->alias == TOKEN_ESCREVA){
        proxToken();

        if(token->alias == TOKEN_STRING){ // CMD_UNICO -> ESCREVA str ESCREVA_REC;
            ESCREVA_REC();
        }else{ // CMD_UNICO -> ESCREVA SEQ_ID ESCREVA_REC;
            SEQ_ID();
        }
    }else if(token->alias == TOKEN_LEIA){ // CMD_UNICO -> LEIA SEQ_ID;
        SEQ_ID();
    }else{
        SEQ_ID();

        proxToken();

        if(token->alias == TOKEN_ATRIBUICAO){
            EXPR();
        }else falha(token->value, ":=");
    }
}

void ESCREVA_REC(){ // ESCREVA_REC -> ',' str ESCREVA_REC    |
                    //                ',' SEQ_ID ESCREVA_REC |
                    //                ε;              ε;
    proxToken();

    if(token->alias == TOKEN_VIRGULA){
        proxToken();

        if(token->alias == TOKEN_STRING){
            ESCREVA_REC();
        }else{
            SEQ_ID();
            ESCREVA_REC();
        }
    }else{} // ESCREVA_REC -> ε;
}

void EXPR_REL(){ // EXPR_REL -> EXPR OP_REL EXPR;
    EXPR();
    OP_REL();
    EXPR();
}

void OP_REL(){ // OP_REL -> .M. |
               //           .m. |
               //           .I.;
    proxToken();

    if(
        token->alias == TOKEN_MAIOR || // OP_REL -> .M.;
        token->alias == TOKEN_MENOR || // OP_REL -> .m.;
        token->alias == TOKEN_IGUAL    // OP_REL -> .I.;
    ){}else falha(token->value, "OP_REL");
}

void EXPR(){ // EXPR -> TERMO EXPR_REC;
    TERMO();
    EXPR_REC();
}

void EXPR_REC(){ // EXPR_REC -> '+' TERMO EXPR_REC |
                 //             '-' TERMO EXPR_REC |
                 //             ε;
    proxToken();

    if(
        token->alias == TOKEN_SOMA      || // EXPR_REC -> '+' TERMO EXPR_REC;
        token->alias == TOKEN_SUBTRACAO    // EXPR_REC -> '-' TERMO EXPR_REC;
    ){
        TERMO();
        EXPR_REC();
    }else{} // EXPR_REC -> ε;
}

void TERMO(){ // TERMO -> FATOR TERMO_REC;
    FATOR();
    TERMO_REC();
}

void TERMO_REC(){ // TERMO_REC -> '*' FATOR TERMO_REC |
                  //              '/' FATOR TERMO_REC |
                  //              ε;
    proxToken();

    if(
        token->alias == TOKEN_MULTIPLICACAO || // TERMO_REC -> '*' FATOR TERMO_REC;
        token->alias == TOKEN_DIVISAO          // TERMO_REC -> '/' FATOR TERMO_REC;
    ){
        FATOR();
        TERMO_REC();
    }else{} // TERMO_REC -> ε;
}

void FATOR(){ // FATOR -> '(' EXPR ')'  |
              //          FATOR '.' num |
              //          num           |
              //          id;
    proxToken();

    if(token->alias == TOKEN_ABRE_PARENTESES){
        EXPR();

        proxToken();

        if(token->alias == TOKEN_FECHA_PARENTESES){}else falha(token->value, ")");
    }else if(
        token->alias == TOKEN_NUMERO        || // FATOR -> num;
        token->alias == TOKEN_IDENTIFICADOR    // FATOR -> id;
    ){}else{ // FATOR -> FATOR '.' num;
        FATOR();

        proxToken();

        if(token->alias == TOKEN_PONTO){
            proxToken();

            if(token->alias == TOKEN_NUMERO){}else falha(token->value, "num");
        }else falha(token->value, ".");
    }
}

/////////////

void proxToken(){
    Token *aux;

    aux = consultaNo(tokens, chave);
    if(aux != NULL){
        token = aux;

        printf("%d : %s\n", token->alias, token->value);

        chave++;
    }else{
        fprintf(stderr, "Erro: alcançou o final da lista de tokens.\n");
    
        exit(EXIT_FAILURE);
    }
}

void falha(char *obtido, char *esperado){
    fprintf(stderr, "Obtido: %s; Esperado: %s.\n", obtido, esperado);
}