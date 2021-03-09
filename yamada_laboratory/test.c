// テスト駆動開発によるテスト用ファイル
// calculator.hのTESTの値を1にすることで使用可能

#include <stdio.h>
#include <string.h>
#include "calculator.h"

int test(void) {
	char string_buf[MAX_INPUT_SIZE];
	struct formula formula_buf;
	struct formula answer_formula_buf;
	struct stack sample_stack;
	sample_stack.top = -1;
	printf("Start test\n");

	strip("  1 2     3 \t \t \t \n", string_buf);
	if (strcmp(string_buf, "123") != 0) {
		return True;
	}

	parse("1+2-3*4/5", &formula_buf);
	char collect_array1[][MAX_DIGIT] = { "1", "+", "2", "-", "3", "*", "4", "/", "5" };
	for (int i = 0; i < 9; i++) {
		if (strcmp(formula_buf.formula[i], collect_array1[i]) != 0) {
			printf("%d: %d\n", i, strcmp(formula_buf.formula[i], collect_array1[i]));
			print_formula(&formula_buf);
			return True;
		}
	}

	parse("123+456", &formula_buf);
	char collect_array2[][MAX_DIGIT] = { "123", "+", "456" };
	for (int i = 0; i < 3; i++) {
		if (strcmp(formula_buf.formula[i], collect_array2[i]) != 0) {
			return True;
		}
	}

	parse("1+(2*3-(4-5))", &formula_buf);
	char collect_array3[][MAX_DIGIT] = { "1", "+", "(", "*", "3", "-", "(", "4", "-", "5", ")", ")" };
	for (int i = 0; i < 3; i++) {
		if (strcmp(formula_buf.formula[i], collect_array3[i]) != 0) {
			return True;
		}
	}

	formula_buf.length = 0;
	add_formula(&formula_buf, "1", NUM);
	if (formula_buf.length != 1 || formula_buf.type[0] != NUM || strcmp(formula_buf.formula[0], "1") != 0) {
		return True;
	}

	strcpy_s(formula_buf.formula[0], MAX_DIGIT, "1");
	strcpy_s(formula_buf.formula[1], MAX_DIGIT, "+");
	strcpy_s(formula_buf.formula[2], MAX_DIGIT, "1");
	formula_buf.type[0] = NUM;
	formula_buf.type[1] = PLUS;
	formula_buf.type[2] = NUM;
	formula_buf.length = 3;
	answer_formula_buf = syntatic_analyser(formula_buf);
	if (answer_formula_buf.length != 3 || formula_buf.type[0] != NUM ||
		formula_buf.type[1] != NUM || formula_buf.type[2] != PLUS ||
		strcmp(formula_buf.formula[0], "1") != 0 ||
		strcmp(formula_buf.formula[1], "1") != 0 ||
		strcmp(formula_buf.formula[2], "+") != 0) 
	{
		print_formula(&answer_formula_buf);
		return False;
	}

	init_stack(sample_stack);
	if (sample_stack.top != -1) {
		printf("stack top: %d\n", sample_stack.top);
		return False;
	}

	init_stack(sample_stack);
	push(1, &sample_stack);
	if (sample_stack.data[0] != 1 || sample_stack.top != 0) {
		return False;
	}

	init_stack(sample_stack);
	push(1, &sample_stack);
	if (pop(&sample_stack) != 1) {
		return False;
	}


	strcpy_s(formula_buf.formula[0], MAX_DIGIT, "1");
	strcpy_s(formula_buf.formula[1], MAX_DIGIT, "1");
	strcpy_s(formula_buf.formula[2], MAX_DIGIT, "+");
	formula_buf.type[0] = NUM;
	formula_buf.type[1] = NUM;
	formula_buf.type[2] = PLUS;
	formula_buf.length = 3;
	int answer = calc_porland(formula_buf);
	if (answer != 2){
		printf("answer is %d\n", answer);
		return True;
	}

	return False;
}