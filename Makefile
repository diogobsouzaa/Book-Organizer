all: main

run:
	./main

main: main.o list.o funcoes.o
	gcc -o main main.o list.o funcoes.o

main.o: main.c
	gcc -o main.o -c main.c

list.o: list.c
	gcc -o list.o -c list.c

funcoes.o: funcoes.c
	gcc -o funcoes.o -c funcoes.c

clean:
	rm -f *.o
	rm -f main

remove_data:
	rm -f dados/*.txt
