#include <stdio.h>
#include <string.h>

#include "calculator.h"

struct formula input_formula;
struct formula porland_formula;
int position;

void E(void);
void T(void);
void F(void);

void puttoken(char *tmp_formula, int tmp_type) {
	strcpy_s(porland_formula.formula[porland_formula.length], MAX_DIGIT, tmp_formula);
	porland_formula.type[porland_formula.length] = tmp_type;
	porland_formula.length++;
}

void E(void) {
	T();
	while (input_formula.type[position] == PLUS || input_formula.type[position] == MINUS) {
		if (input_formula.type[position] == PLUS) {
			position++;
			T();
			puttoken("+", PLUS);
		}
		else {
			position++;
			T();
			puttoken("-", MINUS);
		}
	}
}

void T(void) {
	F();
	while (input_formula.type[position] == MULTIPLE || input_formula.type[position] == DIVIDE) {
		if (input_formula.type[position] == MULTIPLE) {
			position++;
			F();
			puttoken("*", MULTIPLE);
		}
		else {
			position++;
			F();
			puttoken("/", DIVIDE);
		}
	}
}

void F(void) {
	switch (input_formula.type[position]) {
	case NUM:
		puttoken(input_formula.formula[position], input_formula.type[position]);
		position++;
		break;
	case LEFT_BRACKET:
		position++;
		E();
		if (input_formula.type[position] == RIGHT_BRACKET) {
			position++;
		}
		break;
	default:
		break;
	}
}

struct formula syntatic_analyser(struct formula input) {
	input_formula = input;
	porland_formula.length = 0;
	position = 0;
	E();
	return porland_formula;
}