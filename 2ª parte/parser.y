%{
// 2ª Parte do Projeto Final de Compiladores
// Analisador Sintático Ascendente LALR(1) para a Gramática CalcBasica
//
// Rafael Renó Corrêa
//
// Compilação: "yacc -d parser.y" (Windows) ou "bison -d parser.y" (Linux)

#include <stdio.h>
#include <stdlib.h>

// declarações para evitar erros de compilação
int yylex(void);
void yyerror(const char *s);
%}

%union{
	int ival;   // p/ inteiros
	float fval; // p/ reais
}

// declaração de tokens
%token PROGRAMA
%token ID
%token INICIO
%token FIM
%token INTEIRO
%token REAL
%token CARACTER
%token VIRGULA
%token CADEIA
%token LISTA_INT
%token LISTA_REAL
%token ABRE_COLCHETES
%token <ival> NUM_INT
%token <fval> NUM_FLOAT
%token FECHA_COLCHETES
%token ENQUANTO
%token SE
%token ENTAO
%token FIM_SE
%token ESCREVA
%token STR
%token LEIA
%token ATRIBUICAO
%token MAIOR
%token MENOR
%token IGUAL
%token SOMA
%token SUBTRACAO
%token MULTIPLICACAO
%token DIVISAO
%token ABRE_PARENTESES
%token FECHA_PARENTESES
%token FIM_ENQUANTO

%start PGRM

%%

// Regras da gramática
PGRM:
    PROGRAMA ID INICIO DECL CMD FIM
    {
     printf("Reconheceu :)\n");
    }
    ;

DECL:
    TIPO SEQ_ID DECL
    | TIPO_MUL SEQ_ID_MUL DECL
    | /* vazio */
    ;

TIPO:
    INTEIRO
    | REAL
    | CARACTER
    ;

SEQ_ID:
    ID SEQ_ID_REC
    ;

SEQ_ID_REC:
    VIRGULA ID SEQ_ID_REC
    | /* vazio */
    ;

TIPO_MUL:
    CADEIA
    | LISTA_INT
    | LISTA_REAL
    ;

SEQ_ID_MUL:
    ID ABRE_COLCHETES NUM_INT FECHA_COLCHETES SEQ_ID_MUL_REC
    | ID ABRE_COLCHETES ID FECHA_COLCHETES SEQ_ID_MUL_REC
    ;

SEQ_ID_MUL_REC:
    VIRGULA ID ABRE_COLCHETES NUM_INT FECHA_COLCHETES SEQ_ID_MUL_REC
    | VIRGULA ID ABRE_COLCHETES ID FECHA_COLCHETES SEQ_ID_MUL_REC
    | /* vazio */
    ;

CMD:
    ENQUANTO EXPR_REL CMD FIM_ENQUANTO CMD
    | SE EXPR_REL ENTAO CMD FIM_SE CMD
    | ESCREVA STR ESCREVA_REC CMD
    | ESCREVA ID ESCREVA_REC CMD
    | ESCREVA ID ABRE_COLCHETES NUM_INT FECHA_COLCHETES ESCREVA_REC CMD
    | ESCREVA ID ABRE_COLCHETES ID FECHA_COLCHETES ESCREVA_REC CMD
    | LEIA SEQ_ID CMD
    | LEIA SEQ_ID_MUL CMD
    | SEQ_ID ATRIBUICAO EXPR CMD
    | /* vazio */
    ;

ESCREVA_REC:
    VIRGULA STR ESCREVA_REC
    | VIRGULA ID ESCREVA_REC
    | VIRGULA ID ABRE_COLCHETES NUM_INT FECHA_COLCHETES ESCREVA_REC
    | VIRGULA ID ABRE_COLCHETES ID FECHA_COLCHETES ESCREVA_REC
    | /* vazio */
    ;

EXPR_REL:
    EXPR MAIOR EXPR
    | EXPR MENOR EXPR
    | EXPR IGUAL EXPR
    ;

EXPR:
    TERMO EXPR_REC
    ;

EXPR_REC:
    SOMA TERMO EXPR_REC
    | SUBTRACAO TERMO EXPR_REC
    | /* vazio */
    ;

TERMO:
    FATOR TERMO_REC
    ;

TERMO_REC:
    MULTIPLICACAO FATOR TERMO_REC
    | DIVISAO FATOR TERMO_REC
    | /* vazio */
    ;

FATOR:
    ABRE_PARENTESES EXPR FECHA_PARENTESES
    | NUM_INT
    | NUM_FLOAT
    | ID
    | ID ABRE_COLCHETES NUM_INT FECHA_COLCHETES
    | ID ABRE_COLCHETES ID FECHA_COLCHETES
    ;

%%

// tratamento de erro
void yyerror(const char *s) {
    fprintf(stderr, "Erro: %s\n", s);
}

int main() {
    return yyparse();
}
