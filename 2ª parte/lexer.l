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

"PROGRAMA"            { printf("PROGRAMA\n"); return PROGRAMA; }
"INICIO"              { printf("INICIO\n"); return INICIO; }
"FIM"                 { printf("FIM\n"); return FIM; }
"INTEIRO"             { printf("INTEIRO\n"); return INTEIRO; }
"REAL"                { printf("REAL\n"); return REAL; }
"CARACTER"            { printf("CARACTER\n"); return CARACTER; }
"CADEIA"              { printf("CADEIA\n"); return CADEIA; }
"LISTA_INT"           { printf("LISTA_INT\n"); return LISTA_INT; }
"LISTA_REAL"          { printf("LISTA_REAL\n"); return LISTA_REAL; }
","                   { printf(",\n"); return VIRGULA; }
"["                   { printf("[\n"); return ABRE_COLCHETES; }
"]"                   { printf("]\n"); return FECHA_COLCHETES; }
"ENQUANTO"            { printf("ENQUANTO\n"); return ENQUANTO; }
"ENTAO"               { printf("ENTAO\n"); return ENTAO; }
"FIM_ENQUANTO"        { printf("FIM_ENQUANTO\n"); return FIM_ENQUANTO; }
"SE"                  { printf("SE\n"); return SE; }
"FIM_SE"              { printf("FIM_SE\n"); return FIM_SE; }
"ESCREVA"             { printf("ESCREVA\n"); return ESCREVA; }
"LEIA"                { printf("LEIA\n"); return LEIA; }
".M."                 { printf(".M.\n"); return MAIOR; }
".m."                 { printf(".m.\n"); return MENOR; }
".I."                 { printf(".I.\n"); return IGUAL; }
"+"                   { printf("+\n"); return SOMA; }
"-"                   { printf("-\n"); return SUBTRACAO; }
":="                  { printf(":=\n"); return ATRIBUICAO; }
"*"                   { printf("*\n"); return MULTIPLICACAO; }
"/"                   { printf("/\n"); return DIVISAO; }
"("                   { printf("(\n"); return ABRE_PARENTESES; }
")"                   { printf(")\n"); return FECHA_PARENTESES; }
[a-zA-Z][a-zA-Z0-9_]* { printf("ID (%s)\n", yytext); return ID; }
[0-9]+                { yylval.ival = atoi(yytext); printf("NUM_INT (%d)\n", yylval.ival); return NUM_INT; }
[0-9]+"."[0-9]+       { yylval.fval = atof(yytext); printf("NUM_FLOAT (%f)\n", yylval.fval); return NUM_FLOAT; }
\'.*?\'               { printf("STR (%s)\n", yytext); return STR; }
[ \t\n]+              ; // ignora espaço em branco, tabulação e quebra de linha
\{[^}]*\}             { printf("Comentário ignorado: %s\n", yytext); } // ignora comentários
.                     { printf("Token não reconhecido: %s\n", yytext); }

%%

int yywrap() {
    return 1;
}
