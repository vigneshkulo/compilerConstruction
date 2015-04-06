bison -d parser.y 
flex syntax.l 
gcc -g parser.tab.c lex.yy.c -ll -o run
