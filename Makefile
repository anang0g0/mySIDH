
all:
	gcc sidh.c bigint.c -lm -O3 -Wall -Wextra -Wpedantic
