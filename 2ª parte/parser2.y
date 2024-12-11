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

// união de tipos p/ o yylval
%union{
	int num;    // quando inteiro
	float fnum; // quando real
	int str;    // quando string
}

// declaração de tokens
%token PROGRAMA
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
%token FECHA_COLCHETES
%token ENQUANTO
%token FIM_ENQUANTO
%token SE
%token ENTAO
%token FIM_SE
%token MAIOR
%token MENOR
%token IGUAL
%token ESCREVA
%token LEIA
%token ATRIB
%token SOMA
%token SUB
%token MULTI
%token DIV
%token ABRE_PARENTESES
%token FECHA_PARENTESES

%token <str> ID
%token <num> NUM
%token <fnum> FNUM
%token <str> STR

%start PGRM

%%

// Regras da gramática
PGRM:
    PROGRAMA ID INICIO DECL CMD FIM
    ;

DECL:
    TIPO ID SEQ_ID DECL
    | TIPO_ARR ARR SEQ_ARR DECL
    | /* vazio */
    ;

TIPO:
    INTEIRO
    | REAL
    | CARACTER
    ;

SEQ_ID:
    VIRGULA ID SEQ_ID
    | /* vazio */
    ;

TIPO_ARR:
    CADEIA
    | LISTA_INT
    | LISTA_REAL
    ;

ARR:
    ID ABRE_COLCHETES NUM FECHA_COLCHETES
    | ID ABRE_COLCHETES ID FECHA_COLCHETES
    ;

SEQ_ARR:
    VIRGULA ARR SEQ_ARR
    | /* vazio */
    ;

CMD:
    CMD_REPET CMD
    | CMD_PRINT CMD
    | CMD_SCANF CMD
    | CMD_ATRIB CMD
    | /* vazio */
    ;

CMD_REPET:
    ENQUANTO EXPR_REL CMD FIM_ENQUANTO
    | SE EXPR_REL ENTAO CMD FIM_SE
    ;

EXPR_REL:
    EXPR MAIOR EXPR
    | EXPR MENOR EXPR
    | EXPR IGUAL EXPR
    ;

CMD_PRINT:
    ESCREVA STR ESCREVA_REC
    | ESCREVA ID ESCREVA_REC
    | ESCREVA ARR ESCREVA_REC
    ;

ESCREVA_REC:
    VIRGULA STR ESCREVA_REC
    | VIRGULA ID ESCREVA_REC
    | VIRGULA ARR ESCREVA_REC
    | /* vazio */
    ;

CMD_SCANF:
    LEIA ID SEQ_ID
    | LEIA ARR SEQ_ARR
    ;

CMD_ATRIB:
    ID SEQ_ID ATRIB EXPR
    ;

EXPR:
    TERMO
    | EXPR SOMA TERMO
    | EXPR SUB TERMO
    ;

TERMO:
    FATOR
    | TERMO MULTI FATOR
    | TERMO DIV FATOR
    ;

FATOR:
    ABRE_PARENTESES EXPR FECHA_PARENTESES
    | NUM
    | FNUM
    | ID
    | ARR
    ;

%%

// tratamento de erro
void yyerror(const char *s) {
    fprintf(stderr, "Erro: %s\n", s);
}

int main() {
    if(yyparse() == 0){ // yyparse() retorna 0 em caso de sucesso
        printf("Análise Sintática Ascendente concluída!\n");
    }

    return yyparse();
}
