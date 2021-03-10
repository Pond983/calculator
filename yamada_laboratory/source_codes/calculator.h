#pragma once

#define True 1
#define False 0

#define MAX_INPUT_SIZE 100
#define MAX_DIGIT 10
#define MAX_TYPE_LENGTH 10
#define TEST 0

#define NUM			1
#define PLUS		2
#define MINUS		3
#define MULTIPLE	4
#define DIVIDE		5
#define RIGHT_BRACKET	6
#define LEFT_BRACKET	7
#define END				8

struct formula {
    char formula[MAX_INPUT_SIZE][MAX_DIGIT];
    int type[MAX_INPUT_SIZE];
    int length;
};

struct stack {
    int top;
    int data[MAX_INPUT_SIZE];
};

void get_line(char* input);
void strip(char* input, char* stripped_input);
void parse(char* stripped_input, struct formula* parsed_input);
void add_formula(struct formula* parsed_input, char* str, int type);
void print_array(char* array);
void print_formula(struct formula* formula);
struct formula lexical_analyser(char *input);

struct formula syntatic_analyser(struct formula input);

void push(int x, struct stack* s);
int pop(struct stack* s);
void init_stack(struct stack s);
int calc_porland(struct formula porland_formula);

int test(void);



