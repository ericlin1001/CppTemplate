all:compile run

compile:main.cpp
	g++ -std=c++11 -DMakefile_Debug1 -o main main.cpp

run:main
	cat input.txt|./main

.PHONY:run

