%{
// 2ª Parte do Projeto Final de Compiladores
// Analisador Léxico para a Gramática CalcBasica
//
// Rafael Renó Corrêa
//
// Compilação: "flex lexer.l"

#include "parser.tab.h" // cabeçalho gerado pelo Yacc/Bison
#include <stdio.h>
%}

%%

"PROGRAMA"            { printf("Símbolo: PROGRAMA\n"); return PROGRAMA; }
"INICIO"              { printf("Símbolo: INICIO\n"); return INICIO; }
"FIM"                 { printf("Símbolo: FIM\n"); return FIM; }
"INTEIRO"             { printf("Símbolo: INTEIRO\n"); return INTEIRO; }
"REAL"                { printf("Símbolo: REAL\n"); return REAL; }
"CARACTER"            { printf("Símbolo: CARACTER\n"); return CARACTER; }
"CADEIA"              { printf("Símbolo: CADEIA\n"); return CADEIA; }
"LISTA_INT"           { printf("Símbolo: LISTA_INT\n"); return LISTA_INT; }
"LISTA_REAL"          { printf("Símbolo: LISTA_REAL\n"); return LISTA_REAL; }
","                   { printf("Símbolo: ,\n"); return VIRGULA; }
"["                   { printf("Símbolo: [\n"); return ABRE_COLCHETES; }
"]"                   { printf("Símbolo: ]\n"); return FECHA_COLCHETES; }
"ENQUANTO"            { printf("Símbolo: ENQUANTO\n"); return ENQUANTO; }
"ENTAO"               { printf("Símbolo: ENTAO\n"); return ENTAO; }
"FIM_ENQUANTO"        { printf("Símbolo: FIM_ENQUANTO\n"); return FIM_ENQUANTO; }
"SE"                  { printf("Símbolo: SE\n"); return SE; }
"FIM_SE"              { printf("Símbolo: FIM_SE\n"); return FIM_SE; }
"ESCREVA"             { printf("Símbolo: ESCREVA\n"); return ESCREVA; }
"LEIA"                { printf("Símbolo: LEIA\n"); return LEIA; }
".M."                 { printf("Símbolo: .M.\n"); return MAIOR; }
".m."                 { printf("Símbolo: .m.\n"); return MENOR; }
".I."                 { printf("Símbolo: .I.\n"); return IGUAL; }
"+"                   { printf("Símbolo: +\n"); return SOMA; }
"-"                   { printf("Símbolo: -\n"); return SUBTRACAO; }
":="                  { printf("Símbolo: :=\n"); return ATRIBUICAO; }
"*"                   { printf("Símbolo: *\n"); return MULTIPLICACAO; }
"/"                   { printf("Símbolo: /\n"); return DIVISAO; }
"."                   { printf("Símbolo: .\n"); return PONTO; }
"("                   { printf("Símbolo: (\n"); return ABRE_PARENTESES; }
")"                   { printf("Símbolo: )\n"); return FECHA_PARENTESES; }
[a-zA-Z][a-zA-Z0-9_]* { printf("Símbolo: id (%s)\n", yytext); return ID; }
[0-9]+                { printf("Símbolo: número (%s)\n", yytext); return NUM; }
\'.*?\'               { printf("Símbolo: string (%s)\n", yytext); return STR; }
[ \t\n]+              ; // ignora espaço em branco, tabulação e quebra de linha
\{[^}]*\}             { printf("Comentário ignorado: %s\n", yytext); } // ignora comentários
.                     { printf("Token não reconhecido: %s\n", yytext); }

%%

int yywrap() {
    return 1;
}
