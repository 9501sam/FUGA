ALL: main test

game.o: game.c game.h
	gcc -c game.c

main: main.c game.o
	gcc -c main.c -lm
	gcc -o main main.o game.o -lm

test: game.o test.c
	gcc -c test.c -lm
	gcc -o test test.o game.o -lm
	./test

run: main
	./main
clean:
	$(RM) main test *o
