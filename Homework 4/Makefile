all: shell tok

shell: shell.c tok.c
	gcc -o shell -std=c99 -O1 -Wall shell.c
	gcc -o tok -std=c99 -O1 -Wall tok.c

clean:
	rm -f shell.c
	rm -f tok.c
