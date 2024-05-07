GABRIEL AMARAL

Código parser.tab.c alterado na linha 1499:

      yychar = YYLEX;  -->  yychar = YYLEX.type;

Alterado para receber o token.type.      