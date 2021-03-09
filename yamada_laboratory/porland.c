#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "calculator.h"



void push(int x, struct stack* s) {
	//printf("x: %d\n", x);
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
	print_formula(&porland_formula);
	//printf("s.top: %d\n", s.top);
	for (int formula_p = 0; formula_p < porland_formula.length; formula_p++) {
		key = porland_formula.type[formula_p];
		switch (key) {
		case NUM:
			//printf("%d\n", atoi(porland_formula.formula[formula_p]));
			push(atoi(porland_formula.formula[formula_p]), &s);
			//printf("s.data[0]: %d\n", s.data[0]);
			//printf("s.data[1]: %d\n", s.data[1]);
			//printf("s.top: %d\n", s.top);
			break;
		case PLUS:
			x = pop(&s);
			printf("x: %d", x);
			y = pop(&s);
			printf("y: %d", y);
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
		printf("s.data[0]: %d\n", s.data[0]);
		printf("s.data[1]: %d\n", s.data[1]);
		printf("s.top: %d\n", s.top);
	}
	//printf("%d\n", s.data[0]);
	return s.data[0];
}