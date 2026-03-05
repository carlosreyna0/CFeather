#ifndef TOKENIZER_H
#define TOKENIZER_H

typedef struct Token;
enum TokenType;
Token analyze(char[] token_text);
Token[] tokenize(char[] src);

#endif 