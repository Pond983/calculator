#!/bin/sh

gcc -o calculator ./source_codes/main.c ./source_codes/lexical_analyser.c ./source_codes/syntatic_analyser.c ./source_codes/porland.c ./source_codes/test.c
./calculator