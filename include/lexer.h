/*
 * This is my compiler's lexer
 * It's used to split the input string into tokens
 * so the program can read the code easier.
 */


#ifndef LEXER_H
#define LEXER_H

#include "debug.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum TokenType {
	EF = -1,
	NL,
	TAB,
	NUMBER,
	IDENT,
	STRING,

	LABEL = 101,
	GOTO,
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
	ARROW		// =>
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

void lexerInit(char *s) {
	lexer.source = s;
	lexer.len = strlen(s);
	lexer.curPos = -1;
	lexer.curChar = 0;

	nextChar();
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
void lexerError(const char *msg) {
#ifndef DEBUG_H
	err(msg);
#else
	puts(msg);
	exit(1);
#endif
}
int getToken() {
	skipWhitespace();
	skipComment();

	int token;
	switch(lexer.curChar) {
		case '+':
			token = PLUS;
			break;
		case '-':
			token = MINUS;
			break;
		case '*':
			token = ASTERISK;
			break;
		case '/':
			token = SLASH;
			break;
		case '%':
			token = MOD;
			break;

		case '\t':
			token = TAB;
			break;
		case '\n':
			token = NL;
			break;

		case '=':

			if(peek() == '=') {
				token = EQEQ;
				nextChar();
			}
			else if(peek() == '>') {
				token = ARROW;
				nextChar();
			}
			else {
				token = EQ;
			}
			break;

		case '<':
			if(peek() == '=') {
				token = LTEQ;
				nextChar();
			}
			else {
				token = LT;
			}
			break;
		case '>':
			if(peek() == '=') {
				token = GTEQ;
				nextChar();
			}
			else {
				token = GT;
			}
			break;

		case '!':
			if(peek() == '=') {
				token = NOTEQ;
				nextChar();
			}
			else {
				lexerError("Expected != not !");
			}
			break;


		case 0:
			token = EF;
			break;

		default:

			if(isdigit(lexer.curChar)) {
			}
			else if(isalpha(lexer.curChar)) {
			}
			else {
				lexerError("Unknown token");
			}

			break;
	}

	nextChar();
	return token;
}

#endif
