#ifndef LEXICA_H
#define LEXICA_H

#include <stdbool.h>

#define TOKEN_PROGRAMA         "PROGRAMA"     // Início do programa
#define TOKEN_IDENTIFICADOR    "id"           // Identificador
#define TOKEN_INICIO           "INICIO"       // Início do bloco de comandos
#define TOKEN_FIM              "FIM"          // Fim do programa
#define TOKEN_INTEIRO          "INTEIRO"      // Declaração de inteiro
#define TOKEN_REAL             "REAL"         // Declaração de real
#define TOKEN_CARACTER         "CARACTER"     // Declaração de caractere
#define TOKEN_CADEIA           "CADEIA"       // Declaração de cadeia de caracteres
#define TOKEN_LISTA_INT        "LISTA_INT"    // Declaração de lista de inteiros
#define TOKEN_LISTA_REAL       "LISTA_REAL"   // Declaração de lista de reais
#define TOKEN_VIRGULA          ","            // Separador
#define TOKEN_ABRE_COLCHETE    "["            // Abre colchete
#define TOKEN_NUMERO           "num"          // Número inteiro
#define TOKEN_FECHA_COLCHETE   "]"            // Fecha colchete
#define TOKEN_ENQUANTO         "ENQUANTO"     // Laço enquanto
#define TOKEN_ENTAO            "ENTAO"        // Início do bloco condicional
#define TOKEN_FIM_ENQUANTO     "FIM_ENQUANTO" // Fim do enquanto
#define TOKEN_SE               "SE"           // Condicional se
#define TOKEN_FIM_SE           "FIM_SE"       // Fim do condicional
#define TOKEN_ESCREVA          "ESCREVA"      // Comando de saída
#define TOKEN_STRING           "str"          // String
#define TOKEN_LEIA             "LEIA"         // Comando de entrada
#define TOKEN_MAIOR            ".M."          // Operador maior
#define TOKEN_MENOR            ".m."          // Operador menor
#define TOKEN_IGUAL            ".I."          // Operador igual
#define TOKEN_SOMA             "+"            // Adição
#define TOKEN_SUBTRACAO        "-"            // Subtração
#define TOKEN_ATRIBUICAO       ":="           // Atribuição
#define TOKEN_MULTIPLICACAO    "*"            // Multiplicação
#define TOKEN_DIVISAO          "/"            // Divisão
#define TOKEN_PONTO            "."            // Ponto
#define TOKEN_ABRE_PARENTESES  "("            // Abre parênteses
#define TOKEN_FECHA_PARENTESES ")"            // Fecha parênteses

bool analiseLexica();
// GATILHO PARA A VARREDURA E CLASSIFICAÇÃO DO BUFFER DE ENTRADA
//
// Retorna verdadeira se sucedeu e falso se não.

bool varredura();
// FAZ A VARREDURA DO BUFFER DE ENTRADA
//
// Retorna verdadeira se sucedeu e falso se não.

bool verificaFinal(int estado);
// VERIFICA SE O ESTADO É FINAL
//
// Se for, retorna verdadeiro, se não, retorna falso.

char *preencheEntrada();
// PREENCHE O BUFFER A PARTIR DA ENTRADA PADRÃO
//
// Retorna o ponteiro para o buffer (se nulo, não havia caracteres válidos na entrada).

#endif // LEXICA_H