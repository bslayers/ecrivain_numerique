all: clean main

run: main
	@./main

main.o: main.c hachage.h
	gcc -c main.c -o main.o

functions.o: hachage.c hachage.h
	gcc -c $< -o $@

main: main.o hachage.o
	gcc $^ -o $@

clean:
	@rm -rf main
	@rm -rf *.o
	@clear