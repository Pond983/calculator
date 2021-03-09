#include <stdio.h>
#include <string.h>
#include "calculator.h"

int main(void) {
	
	if (TEST) {
		if (test()) {
			printf("Error exist!\n");
		}
		else {
			printf("All clear\n");
		}
	}

	char input[MAX_INPUT_SIZE];
	input[0] = '\0';
	struct formula input_formula;
	struct formula porland_formula;
	while (strcmp(input, "quit") != 0) {
		printf("> ");
		get_line(input);
		input_formula = lexical_analyser(input);
		porland_formula = syntatic_analyser(input_formula);
		printf("%d\n", calc_porland(porland_formula));
	}
	return 0;
}