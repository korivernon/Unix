# Makefile

all: env

env: env.c
	#gcc -o env -std=c99 -D_XOPEN_SOURCE=600  env.c
	#gcc -o env -std=c99 -D_XOPEN_SOURCE=700  env.c
	#gcc -o env -std=c99 -D_POSIX_C_SOURCE=200112L -D_XOPEN_SOURCE=600 env.c
	gcc -o env -std=c99 -D_POSIX_C_SOURCE=200809L -D_XOPEN_SOURCE=700 env.c

clean:
	rm -f env
