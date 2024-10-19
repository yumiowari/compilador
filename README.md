# Compilador

`gcc -c lista.c -o lista.o && gcc -c lexica.c -o lexica.o && gcc -c sintatica.c -o sintatica.o && gcc compilador.c lista.o lexica.o sintatica.o -o compilador`