# Projeto de Compiladores

## Parte 2

Analisador Léxico e Analisador Sintático Ascendente LALR(1) _Flex + Yacc_ para a gramática CalcBásica.

### Compilação:

- Analisador Sintático:

`yacc -d parser.y (Windows) ou bison -d parser.y (Linux)`

> Cria o `parser.tab.c` e o `parser.tab.h`.

- Analisador Léxico:

`flex lexer.l`

- Executável:

`gcc parser.tab.c lex.yy.c -o parser`

### Uso:

- Padrão:
`./parser`

- (Exemplo) Substituindo a entrada:
`./parser < in.txt`

---

Feito com amor por Rafael Renó Corrêa 🪶