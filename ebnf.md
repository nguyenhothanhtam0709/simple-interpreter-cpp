```ebnf
expr    : term ((PLUS | MINUS) term)*
term    : factor ((MUL | DIV) factor)*
factor  : (PLUS | MINUS) factor | INTEGER | LPAREN expr RPAREN
```
