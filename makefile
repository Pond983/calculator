objects = main.o lexical_analyser.o syntatic_analyser.o porland.o test.o

calculator : $(objects)
	gcc -o calculator $(objects)

main.o : ./source_codes/main.c ./source_codes/calculator.h
	gcc -c ./source_codes/main.c
lexical_analyser.o : ./source_codes/lexical_analyser.c ./source_codes/calculator.h
	gcc -c ./source_codes/lexical_analyser.c
syntatic_analyser.o : ./source_codes/syntatic_analyser.c ./source_codes/calculator.h
	gcc -c ./source_codes/syntatic_analyser.c
porland.o : ./source_codes/porland.c ./source_codes/calculator.h
	gcc -c ./source_codes/porland.c
test.o : ./source_codes/test.c ./source_codes/calculator.h
	gcc -c ./source_codes/test.c

clean :
	rm calculator $(objects)
