#define __STDC_WANT_LIB_EXT1__ 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "calculator.h"

//void get_line(char* input);
//void strip(char* input, char* stripped_input);
//void parse(char* stripped_input, struct formula *parsed_input);

//void print_array(char* array);
//void print_formula(struct formula* formula);

// 一行分の文字列を読み込む
// 式を受け取るための関数
void get_line(char* input) {
	int c, i;   //getcharの受け取り用変数c、ループ用変数i  

	for (i = 0; i < MAX_INPUT_SIZE - 1 && (c = getchar()) != '\n'; i++)
		input[i] = c;

	input[i] = '\0';
}

//受け取った文字列から空白やタブを外す
void strip(char* input, char* parsed_input) {
	char ch;
	int striped_input_size = 0;
	for (int input_p = 0; input_p <= strlen(input); input_p++) {
		ch = input[input_p];
		//改行文字ならreturn
		if (ch == '\n') {
			break;
		}
		switch (ch) {
		case ' ': break;
		case '\t': break;
		default:
			parsed_input[striped_input_size++] = ch;
		}
	}
	parsed_input[striped_input_size] = '\0';
}

void add_formula(struct formula* parsed_input, char* str, int type) {
	strncpy(parsed_input->formula[parsed_input->length], str, MAX_DIGIT);
	parsed_input->type[parsed_input->length] = type;
	parsed_input->length++;
}

void parse(char* input, struct formula* parsed_input) {
	char ch;
	char buf[MAX_DIGIT];
	parsed_input->length = 0;
	for (int input_p = 0; input_p < strlen(input); input_p++) {
		ch = input[input_p];
		//改行文字ならreturn
		if (ch == '\n') {
			break;
		}
		switch (ch) {
		case '+':
			buf[0] = ch;
			buf[1] = '\0';
			add_formula(parsed_input, buf, PLUS);
			break;
		case '-':
			buf[0] = ch;
			buf[1] = '\0';
			add_formula(parsed_input, buf, MINUS);
			break;
		case '*':
			buf[0] = ch;
			buf[1] = '\0';
			add_formula(parsed_input, buf, MULTIPLE);
			break;
		case '/':
			buf[0] = ch;
			buf[1] = '\0';
			add_formula(parsed_input, buf, DIVIDE);
			break;
		case '(':
			buf[0] = ch;
			buf[1] = '\0';
			add_formula(parsed_input, buf, LEFT_BRACKET);
			break;
		case ')':
			buf[0] = ch;
			buf[1] = '\0';
			add_formula(parsed_input, buf, RIGHT_BRACKET);
			break;
		default:
			if ('0' <= ch && ch <= '9') {
				int end_num_p = input_p;
				while ('0' <= input[end_num_p+1] && input[end_num_p+1] <= '9') {
					end_num_p++;
				}
				int i;
				for (i = 0; i < (end_num_p - input_p + 1); i++) {
					buf[i] = input[input_p + i];
				}
				buf[i] = '\0';
				input_p = end_num_p;
				add_formula(parsed_input, buf, NUM);
			}
			break;
		}
	}
}

void print_array(char* array) {
	for (int i = 0; i < strlen(array); i++) {
		printf("'%c',", array[i]);
	}
}

void print_formula(struct formula* formula) {
	printf("length: %d\n", formula->length);
	for (int i = 0; i < formula->length; i++) {
		printf("%d: '%s'\n", formula->type[i], formula->formula[i]);
	}
}

struct formula lexical_analyser(char *input) {
	char striped_input[MAX_INPUT_SIZE];
	struct formula parsed_input;
	
	strip(input, striped_input);
	parse(striped_input, &parsed_input);
	return parsed_input;
}