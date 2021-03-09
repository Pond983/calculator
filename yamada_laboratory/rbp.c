#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define ID 256

int token;
int tval;

void E(void);
void T(void);
void F(void);
void puttoken(int);
void gettoken(void);
void error(void);

void E(void) {
	T();
	while (token == '+') {
		gettoken();
		T();
		puttoken('+');
	}
}

void T(void) {
	F();
	while (token == '*') {
		gettoken();
		F();
		puttoken('*');
	}
}

void F(void) {
	switch (token) {
	case ID:
		puttoken(ID);
		gettoken();
		break;
	case '(':
		gettoken();
		E();
		if (token == ')') {
			gettoken();
		}
		else {
			error();
		}
		break;
	default:
		error();
	}
}

void main(void) {
	gettoken();
	E();
	if (token != EOF) {
		error();
	}
}

void puttoken(int token) {
	if (token == ID) {
		printf("%d ", tval);
	}
	else if (token == EOF) {
		printf("\n");
	}
	else {
		printf("%c ", token);
	}
}

void error() {
	fflush(stdout);
	if (token == ID) {
		fprintf(stderr, "\nError occurs when reading token %d.\n", tval);
	}
	else {
		fprintf(stderr, "\nError occurs when reading token '%c'.\n", token);
	}
	exit(1);
}

void gettoken(void) {
	int ch;
	while ((ch = getchar()) == ' ' || ch == '\t') { // skip white spaces
		continue;
	}
	if (isdigit(ch)) {
		tval = 0;
		do {
			tval *= 10;
			tval += ch - '0';
		} while (isdigit(ch = getchar()));
		ungetc(ch, stdin);
		token = ID;
		return;
	}
	else {
		switch (ch) {
		case '+':
		case '*':
		case '(':
		case ')':
			token = ch;
			return;
		case '\n':
		case '\r':
		case EOF:
			token = EOF;
			return;
		default:
			fprintf(stderr, "incorrect char: %c\n", ch);
			exit(1);
		}
	}
}