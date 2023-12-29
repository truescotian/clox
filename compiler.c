#include <stdio.h>

#include "common.h"
#include "compiler.h"
#include "scanner.h"

void compile(const char* source) {
	printf("Compiling source\n");

  initScanner(source);

	int line = -1;

	printf("Scanning tokens\n");
  for (;;) {
    Token token = scanToken();

		// first column is line number, second is numeric 
		// value of token type, then finally the lexeme.
		// example: print 1 + 2;
		// 1 31 'print'
		// | 21 '1'
		// | 7 '+'
		// | 21 '2'
		// | 8 ';'
		// 2 39 '' <-- this this empty lexeme is the EOF token.
    if (token.line != line) {
      printf("%4d ", token.line);
      line = token.line;
    } else {
      printf("   | ");
    }
    printf("%2d '%.*s'\n", token.type, token.length, token.start); 

    if (token.type == TOKEN_EOF) break;
  }

	printf("Compile complete!\n");
}
