

all:
	gcc sidh.c bigint.c -lm -O3 -Wall -Wpedantic

c++:
	g++ -O3 sidh.cpp bigint.c -lm
