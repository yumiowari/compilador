# Projeto de Compiladores

## Parte 2

Analisador Léxico e Analisador Sintático Ascendente LALR(1) _Flex + Yacc_ para a gramática CalcBásica.

### Compilação:

- Para o Analisador Sintático:
  
`yacc -d parser.y` (Windows) ou `bison -d parser.y` (Linux)

> Cria o `parser.tab.c` e o `parser.tab.h`.

- Para o Analisador Léxico:

`flex lexer.l`

- Para o Executável:

`gcc parser.tab.c lex.yy.c -o parser`

### Uso:

- Padrão:
  
`./parser` (Linux) ou `parser.exe` (Windows)

- (Exemplo) Substituindo a entrada:

`./parser < in.txt` (Linux) ou `parser.exe < in.txt` (Windows)

---

Feito com amor por Rafael Renó Corrêa 🪶