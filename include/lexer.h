/*
 * This is my compiler's lexer
 * It's used to split the input string into tokens
 * so the program can read the code easier.
 */


#ifndef LEXER_H
#define LEXER_H

#include "debug.h"
#include "defs.h"
#include "vector.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


define_vector(char)	// declaration of vector(char)

void lexerError(const char *msg) {
#ifndef DEBUG_H
	err(msg);
#else
	puts(msg);
	exit(1);
#endif
}

enum TokenType {
	EF = -1,
	NL,
	TAB,
	NUMBER,
	IDENT,
	CHAR,
	STRING,
	KEYWORD,

	LABEL = 101, 	// not support yet
	GOTO,		// not support yet
	WRITE,
	READ,
	LET,
	IF,
	ELSE,
	WHILE,

	EQ = 201,
	EQEQ,
	NOTEQ,
	LT,
	LTEQ,
	GT,
	GTEQ,
	PLUS,
	MINUS,
	ASTERISK,
	SLASH,
	MOD,
	ARROW,		// =>
	ROUND_OPEN,	// (
	ROUND_CLOSE,	// )
	SQUARE_OPEN,	// [
	SQUARE_CLOSE	// ]
};

#define KEYWORD_COUNT		12
const char *keyword[] = {
	"int",
	"float",
	"string",
	"char",
	"array",
	
	"write",
	"read",
	
	"let",
	
	"if",
	"else",
	
	"while",

	"return"
};
bool checkKeyword(const char *s) {
	for(int i = 0; i < KEYWORD_COUNT; ++i) {
		if(strcmp(s, keyword[i]) == 0) {
			return 1;
		}
	}
	return 0;
}

struct Token {
	vector(char) str;
	int type;
};

struct lexer {
	char *source, curChar;
	int len, curPos;
} lexer;

void nextChar() {
	++lexer.curPos;
	if(lexer.curPos >= lexer.len) {
		lexer.curChar = 0;
	}
	else {
		lexer.curChar = lexer.source[lexer.curPos];
	}

}

size_t _token_cnt = 0;
struct Token lexerToken[MAX_TOKEN];
struct Token *newToken() {
	++_token_cnt;
	if(_token_cnt >= MAX_TOKEN) {
		lexerError("Too much token in the program: Increase MAX_TOKEN value in ./include/defs.h and recompile the compiler.");
	}

	lexerToken[_token_cnt].str.size = 0;
	lexerToken[_token_cnt].str.arr = NULL;
	lexerToken[_token_cnt].type = -3;

	return &lexerToken[_token_cnt];
}

void lexerClean() {
	for(int i = 1; i <= _token_cnt; ++i) {
		del(&lexerToken[i].str);
	}
}
void lexerInit(char *s) {
	lexer.source = s;
	lexer.len = strlen(s);
	lexer.curPos = -1;
	lexer.curChar = 0;

	nextChar();

	atexit(lexerClean);
}
char peek() {
	if(lexer.curPos + 1 >= lexer.len) {
		return 0;
	}
	return lexer.source[lexer.curPos + 1];
}
void skipWhitespace() {
	while(lexer.curChar == ' ' || lexer.curChar == '\r') {
		nextChar();
	}
}
void skipSpaceAndTab() {
	while(lexer.curChar == ' ' || lexer.curChar == '\t' || lexer.curChar == '\r') {
		nextChar();
	}
}
void skipComment() {
	if(lexer.curChar == '#') {
		while(lexer.curChar != '\n') {
			nextChar();
		}
	}
	else {
		// solve multiline comment
	}
}

struct Token *getToken() {
	skipWhitespace();
	skipComment();

	struct Token *token = newToken();
	switch(lexer.curChar) {
		case '+':
			push_back(&token->str, '+');
			token->type = PLUS;
			break;
		case '-':
			push_back(&token->str, '-');
			token->type = MINUS;
			break;
		case '*':
			push_back(&token->str, '*');
			token->type = ASTERISK;
			break;
		case '/':
			push_back(&token->str, '/');
			token->type = SLASH;
			break;
		case '%':
			push_back(&token->str, '%');
			token->type = MOD;
			break;

		case '\t':
			push_back(&token->str, '\t');
			token->type = TAB;
			break;
		case '\n':
			push_back(&token->str, '\n');
			token->type = NL;
			break;

		case '=':
			push_back(&token->str, '=');

			if(peek() == '=') {
				push_back(&token->str, '=');
				token->type = EQEQ;
				nextChar();
			}
			else if(peek() == '>') {
				push_back(&token->str, '>');
				token->type = ARROW;
				nextChar();
			}
			else {
				token->type = EQ;
			}
			break;

		case '<':
			push_back(&token->str, '<');

			if(peek() == '=') {
				push_back(&token->str, '=');
				token->type = LTEQ;
				nextChar();
			}
			else {
				token->type = LT;
			}
			break;
		case '>':
			push_back(&token->str, '>');
			if(peek() == '=') {
				push_back(&token->str, '=');
				token->type = GTEQ;
				nextChar();
			}
			else {
				token->type = GT;
			}
			break;

		case '!':
			push_back(&token->str, '!');

			if(peek() == '=') {
				push_back(&token->str, '=');
				token->type = NOTEQ;
				nextChar();
			}
			else {
				lexerError("Expected != not !");
			}
			break;

		case '(':
			push_back(&token->str, '(');
			token->type = ROUND_OPEN;
			break;
		case ')':
			push_back(&token->str, ')');
			token->type = ROUND_CLOSE;
			break;

		case '[':
			push_back(&token->str, '[');
			token->type = SQUARE_OPEN;
			break;
		case ']':
			push_back(&token->str, ']');
			token->type = SQUARE_CLOSE;
			break;


		case 0:
			push_back(&token->str, 0);
			token->type = EF;
			break;

		default:

			if(lexer.curChar == '.' || isdigit(lexer.curChar)) {
				int cntDot = (lexer.curChar == '.');
				push_back(&token->str, lexer.curChar);
				while(peek() == '.' || isdigit(peek())) {
					nextChar();
					push_back(&token->str, lexer.curChar);
					if(lexer.curChar == '.') {
						++cntDot;
					}
				}
				if(cntDot > 1) {
					lexerError("\nInvalid number: Too many dots '.'");
				}
				token->type = NUMBER;
			}
			else if(lexer.curChar == '_' || isalpha(lexer.curChar)) {
				push_back(&token->str, lexer.curChar);
				while(peek() == '_' || isalnum(peek())) {
					nextChar();
					push_back(&token->str, lexer.curChar);
				}

				push_back(&token->str, 0);
				token->type = checkKeyword(token->str.arr) ? KEYWORD : IDENT; 
			}
			else if(lexer.curChar == '"') {
				push_back(&token->str, lexer.curChar);
				while(peek() && peek() != '"') {
					nextChar();
					push_back(&token->str, lexer.curChar);
				}

				if(peek() != '"') {
					lexerError("\nInvalid string (no close \")");
				}

				nextChar();
				push_back(&token->str, lexer.curChar);
				token->type = STRING;
			}
			else if(lexer.curChar == '\'') {
				nextChar();

				if(lexer.curChar == '\\') {
					nextChar();
					push_back(&token->str, lexer.curChar);	// accept all \* (but C compiler may not able to compile)
				}
				else {
					push_back(&token->str, lexer.curChar);
				}

				nextChar();
				if(lexer.curChar != '\'') {
					lexerError("\nInvalid Character (no close ' or no such character)");
				}

				token->type = CHAR;
			}
			else {
				lexerError("\nUnknown token");
			}

			break;
	}

	push_back(&token->str, 0);

	nextChar();
	return token;
}

#endif
