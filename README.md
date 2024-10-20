# Projeto de Compiladores

## Parte 1

---

### Compilação:

`gcc -c lista.c -o lista.o && gcc -c lexica.c -o lexica.o && gcc -c sintatica.c -o sintatica.o && gcc compilador.c lista.o lexica.o sintatica.o -o compilador`

### Uso:

- Padrão:
`./compilador`

- Depuração:
`./compilador -d`

- (Exemplo) Substituindo a entrada:
`./compilador < in.txt`

- (Exemplo) Substituindo a entrada e depurando:
`./compilador < in.txt -d`

---

Feito com amor por Rafael Renó Corrêa 🪶