all:compile run

compile:main.cpp
	g++ -DMakefile_Debug1 -o main main.cpp

run:main
	cat input.txt|./main



