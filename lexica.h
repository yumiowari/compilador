#ifndef LEXICA_H
#define LEXICA_H

#include <stdbool.h>

#include "lista.h"

Lista *analiseLexica(bool debug);
// GATILHO PARA A ANÁLISE LÉXICA DO BUFFER DE ENTRADA
//
// Retorna o ponteiro para a lista de tokens
// (se nulo, não havia tokens válidos na entrada)

bool verificaFinal(int estado);
// VERIFICA SE O ESTADO É FINAL
//
// Se for, retorna verdadeiro, se não, retorna falso.

char *preencheEntrada();
// PREENCHE O BUFFER A PARTIR DA ENTRADA PADRÃO
//
// Retorna o ponteiro para o buffer (se nulo, não havia caracteres válidos na entrada).

#endif // LEXICA_H