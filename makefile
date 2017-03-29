all:compile run

compile:main.cpp
	g++ -std=c++11 -DMakefile_Debug1 -o main main.cpp

run:main
	#./main |less
	./main

.PHONY:run

