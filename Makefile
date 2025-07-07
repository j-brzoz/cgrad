all:
	gcc -Wall -o bin/main.out src/*.c src/data_structs/*.c src/ml_structs/*.c src/io/*.c example/*.c -lm
