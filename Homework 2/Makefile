# Makefile

all: env test

env: env.c
	gcc -o env -std=c99 -Wall -O1  env.c
	gcc -o test -std=c99 -Wall -O1  test.c

clean:
	rm -f env
	rm -f test
