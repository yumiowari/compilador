%{
// 2ª Parte do Projeto Final de Compiladores
// Analisador Léxico para a Gramática CalcBasica
//
// Rafael Renó Corrêa
//
// Compilação: "flex lexer.l"

#include "parser.tab.h" // cabeçalho gerado pelo Yacc/Bison
#include <stdio.h> // printf()
#include <stdlib.h> // atoi(), atof()
%}

%%

[ \t\n]+              ; // ignora espaço em branco, tabulação e quebra de linha
\{[^}]*\}             { printf("Comentário: %s\n", yytext); } // ignora comentários

"PROGRAMA"            { printf("Token PROGRAMA: %s\n", yytext); return PROGRAMA; }
"INICIO"              { printf("Token INICIO: %s\n", yytext); return INICIO; }
"FIM"                 { printf("Token FIM: %s\n", yytext); return FIM; }
"INTEIRO"             { printf("Token INTEIRO: %s\n", yytext); return INTEIRO; }
"REAL"                { printf("Token REAL: %s\n", yytext); return REAL; }
"CARACTER"            { printf("Token CARACTER: %s\n", yytext); return CARACTER; }
","                   { printf("Token VIRGULA: %s\n", yytext); return VIRGULA; }
"CADEIA"              { printf("Token CADEIA: %s\n", yytext); return CADEIA; }
"LISTA_INT"           { printf("Token LISTA_INT: %s\n", yytext); return LISTA_INT; }
"LISTA_REAL"          { printf("Token LISTA_REAL: %s\n", yytext); return LISTA_REAL; }
"["                   { printf("Token ABRE_COLCHETES: %s\n", yytext); return ABRE_COLCHETES; }
"]"                   { printf("Token FECHA_COLCHETES: %s\n", yytext); return FECHA_COLCHETES; }
"ENQUANTO"            { printf("Token ENQUANTO: %s\n", yytext); return ENQUANTO; }
"FIM_ENQUANTO"        { printf("Token FIM_ENQUANTO: %s\n", yytext); return FIM_ENQUANTO; }
"SE"                  { printf("Token SE: %s\n", yytext); return SE; }
"ENTAO"               { printf("Token ENTAO: %s\n", yytext); return ENTAO; }
"FIM_SE"              { printf("Token FIM_SE: %s\n", yytext); return FIM_SE; }
".M."                 { printf("Token MAIOR: %s\n", yytext); return MAIOR; }
".m."                 { printf("Token MENOR: %s\n", yytext); return MENOR; }
".I."                 { printf("Token IGUAL: %s\n", yytext); return IGUAL; }
"ESCREVA"             { printf("Token ESCREVA: %s\n", yytext); return ESCREVA; }
"LEIA"                { printf("Token LEIA: %s\n", yytext); return LEIA; }
":="                  { printf("Token ATRIB: %s\n", yytext); return ATRIB; }
"+"                   { printf("Token SOMA: %s\n", yytext); return SOMA; }
"-"                   { printf("Token SUB: %s\n", yytext); return SUB; }
"*"                   { printf("Token MULTI: %s\n", yytext); return MULTI; }
"/"                   { printf("Token DIV: %s\n", yytext); return DIV; }
"("                   { printf("Token ABRE_PARENTESES: %s\n", yytext); return ABRE_PARENTESES; }
")"                   { printf("Token FECHA_PARENTESES: %s\n", yytext); return FECHA_PARENTESES; }

[a-zA-Z][a-zA-Z0-9_]* { printf("Token ID: %s\n", yytext); return ID; }
[0-9]+                { printf("Token NUM: %s\n", yytext); return NUM; }
\'.*?\'               { printf("Token STR: %s\n", yytext); return STR; }

.                     { printf("Token desconhecido: %s\n", yytext); }

%%

// yywrap() é chamada quando todo o conteúdo do arquivo de entrada foi processado.
int yywrap() {
    printf("Análise Léxica concluída!\n");

    return 1;
}
