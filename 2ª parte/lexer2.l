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
\{[^}]*\}             { printf("Comentário ignorado: %s\n", yytext); } // ignora comentários

"PROGRAMA"            { return PROGRAMA; }
"INICIO"              { return INICIO; }
"FIM"                 { return FIM; }
"INTEIRO"             { return INTEIRO; }
"REAL"                { return REAL; }
"CARACTER"            { return CARACTER; }
","                   { return VIRGULA; }
"CADEIA"              { return CADEIA; }
"LISTA_INT"           { return LISTA_INT; }
"LISTA_REAL"          { return LISTA_REAL; }
"["                   { return ABRE_COLCHETES; }
"]"                   { return FECHA_COLCHETES; }
"ENQUANTO"            { return ENQUANTO; }
"FIM_ENQUANTO"        { return FIM_ENQUANTO; }
"SE"                  { return SE; }
"ENTAO"               { return ENTAO; }
"FIM_SE"              { return FIM_SE; }
".M."                 { return MAIOR; }
".m."                 { return MENOR; }
".I."                 { return IGUAL; }
"ESCREVA"             { return ESCREVA; }
"LEIA"                { return LEIA; }
":="                  { return ATRIB; }
"+"                   { return SOMA; }
"-"                   { return SUB; }
"*"                   { return MULTI; }
"/"                   { return DIV; }
"("                   { return ABRE_PARENTESES; }
")"                   { return FECHA_PARENTESES; }

[a-zA-Z][a-zA-Z0-9_]* { return ID; }
[0-9]+                { return NUM; }
\'.*?\'               { return STR; }

.                     { printf("Token não reconhecido: %s\n", yytext); }

%%

int yywrap() {
    return 1;
}
