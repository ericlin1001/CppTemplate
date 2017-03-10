all:compile run

compile:main.cpp
	g++ -o main main.cpp

run:main
	cat input.txt|./main

