#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "calculator.h"



void push(int x, struct stack* s) {
	s->data[++s->top] = x;
}

int pop(struct stack* s) {
	return s->data[s->top--];
}

void init_stack(struct stack s){
	s.top = -1;
}

int calc_porland(struct formula porland_formula) {
	int key, x, y;
	struct stack s;
	s.top = -1;
	for (int formula_p = 0; formula_p < porland_formula.length; formula_p++) {
		key = porland_formula.type[formula_p];
		switch (key) {
		case NUM:
			push(atoi(porland_formula.formula[formula_p]), &s);
			break;
		case PLUS:
			x = pop(&s);
			y = pop(&s);
			push(y + x, &s);
			break;
		case MINUS:
			x = pop(&s);
			y = pop(&s);
			push(y - x, &s);
			break;
		case MULTIPLE:
			x = pop(&s);
			y = pop(&s);
			push(y * x, &s);
			break;
		case DIVIDE:
			x = pop(&s);
			y = pop(&s);
			push(y / x, &s);
			break;
		default: break;
		}
	}
	return s.data[0];
}