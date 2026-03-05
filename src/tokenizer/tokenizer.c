#include "tokenizer.h"
#include <string.h>

typedef struct
{
	char[] text;
	TokenType type;
	int line;
}Token;
enum TokenType
{
	IDENTIFIER,
	OPERATOR,	
	LITERAL,
	KEYWORD,
	PARENTHESIS_OPEN, PARENTHESIS_CLOSE,
	CURLY_BRACE_OPEN, CURLY_BRACE_CLOSE,
	SQUARE_BRACE_OPEN, SQUARE_BRACE_CLOSE
}
Token analyze(char[] token_text)
{
	TokenType type = NULL; //if type is unchanged and stays NULL, then that means there is a syntax error in the Feather script
	
	if(strcmp(token_text, "+") == 0)
	{
		type = OPERATOR;
	}
	else if(strcmp(token_text, "-") == 0)
	{
		type = OPERATOR;
	}
	else if(strcmp(token_text, "*") == 0)
	{
		type = OPERATOR;
	}
	else if(strcmp(token_text, "/") == 0)
	{
		type = OPERATOR;
	}
	else if(strcmp(token_text, "%") == 0)
	{
		type = OPERATOR;
	}
	else if(strcmp(token_text, "^") == 0)
	{
 		type = OPERATOR;
	}
	else if(strcmp(token_text, "=") == 0)
	{
		type = OPERATOR;
	}
	else if(strcmp(token_text, ":") == 0)
	{
		type = OPERATOR;
	}	
	else if(strcmp(token_text, "?") == 0)
	{
		type = OPERATOR;
	}
	else if(strcmp(token_text, ",") == 0)
	{
		type = OPERATOR;
	}
	else if(strcmp(token_text, "++") == 0)
	{
		type = OPERATOR;
	}
	else if(strcmp(token_text, "--") == 0)
	{
		type = OPERATOR;
	}
	else if(strcmp(token_text, "+=") == 0)
	{
		type = OPERATOR;
	}
	else if(strcmp(token_text, "-=") == 0)
	{
		type = OPERATOR;
	}
	else if(strcmp(token_text, "*=") == 0)
	{
		type = OPERATOR;
	}
	else if(strcmp(token_text, "/=") == 0)
	{
		type = OPERATOR;
	}
	else if(strcmp(token_text, "%=") == 0)
	{
		type = OPERATOR;
	}
	else if(strcmp(token_text, "^=") == 0)
	{
		type = OPERATOR;
	}
	else if(strcmp(token_text, "if") == 0)
	{
		type = KEYWORD;
	}
	else if(strcmp(token_text, "elif") == 0)
	{
		type = KEYWORD;
	}
	else if(strcmp(token_text, "else") == 0)
	{
		type = KEYWORD;
	}	
	else if(strcmp(token_text, "return"))	
	{
		type = KEYWORD;
	}
	else if(strcmp(token_text, "for") == 0)
	{
		type = KEYWORD;
	}
	else if(strcmp(token_text, "while") == 0)
	{
		type = KEYWORD;
	}
	else if(strcmp(token_text, "break") == 0)
	{
		type = KEYWORD;
	}
	else if(strcmp(token_text, "[") == 0)
	{
		type = SQUARE_BRACE_OPEN;
	}
	else if(strcmp(token_text, "]") == 0)
	{
		type = SQUARE_BRACE_CLOSE;
	}
	else if(strcmp(token_text, "(") == 0)
	{
		type = PARENTHESIS_OPEN;
	}
	else if(strcmp(token_text, ")") == 0)
	{
		type = PARENTHESIS_CLOSE;
	}
	else if(strcmp(token_text, "{") == 0)
	{
		type = CURLY_BRACE_OPEN;
	}
	else if(strcmp(token_text, "}") == 0)
	{
		type = CURLY_BRACE_CLOSE;
	}else
	{
		//either an identifier, or a literal
		
		int identifier = 1, single_string = 0, double_string = 0;
		int exit = 0;
		
		for(int i = 0; i < sizeof(token_text) / sizeof(char); i++)
		{
			char current = token_text[i];
			if(exit == 1)
			{
				break;
			}
			switch(current)
			{
				case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': case '0': case '.':
					if(i == 0)
					{
						identifier = 0;
						exit = 1;
					}
					break;
				default:
					//a string or an identifier
					if(i != 0){
						break;
					}
					if(current == '\'')
					{
						//single_string ('example')
						
						single_string = 1;
						double_string = 0;
						identifier = 0;
						exit = 1;
					}
					else if(current == '"')
					{
						//double_string ("example")
						
						double_string = 1;
						single_string = 0;
						identifier = 0;
						exit = 1;
					}
					else
					{
						//identifier (example)
						
						identifier = 1;
						single_string = 0;
						double_string = 0;
						exit = 1;
					}
					break;
			}	
		}
		//check if syntax is valid since i ignored checking if a string is surrounded by quotes
		
		if(identifier == 1)
		{
			//an_identifier
			
			type = IDENTIFIER;
		}
		else if(single_string == 1)
		{
			//'a string'
			if(token_text[sizeof(token_text) / sizeof(token_text[0]) - 1] == '\'')
			{
				type = LITERAL;
			}
			
		}
		else if(double_string == 1)
		{
			//"a string"
			if(token_text[sizeof(token_text) / sizeof(token_text[0]) - 1] == '"')
			{
				type = LITERAL;
			}
			
		}
		else if(identifier == 0)
		{
			//a number
			if(token_text[sizeof(token_text) / sizeof(token_text[0]) - 1] != '.')
			{
				type = LITERAL;
			}
			
		}
	}
	
	return type;
}
Token tokenize(char[] src)
{
	/*
		example:
			add(a, b)
				return a + b
			x = 23
			y = 5
			print(add(a, b))
	*/
	char[sizeof(src) / sizeof(char)] current_text = "";
	Token[sizeof(src) / sizeof(char)] tokens;
	
	for(int i = 0; i < sizeof(src) / sizeof(char); i++)
	{
		char current = src[i];
		
		switch(current)
		{
			case '+': case '-': case '*': case '/': case '^': case '%': case '=': case '(': case ')': case '[': case ']': case ':': case '?': case '[': case ']': case '.': case ',':
				//symbols
				break
			case ' ':
				//check if it is a space or indentation, if a space, lexically analyze current_text and then add it as a token 
				break;
			case '\n':
				//newline, send to lexer than add as a token
				break;
			default:
				//identifier or number, modify current_text to include it
				break;
		}
		
	}
	return NULL;

}
