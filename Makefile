all:
	gcc -Wall -o bin/main.out src/*.c src/data_structs/*.c example/*.c -lm
