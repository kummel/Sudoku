CC = gcc
CFLAGS = -g 
CMORE = -lpthread 
ALL: main.o dica.o completa.o verificacao.o main

all: $(CMORE) $(ALL)

main.o: main.c main.h 
dica.o: dica.c dica.h
verificacao.o: verificacao.c verificacao.h
completa.o: completa.h completa.c
main: $(CMORE) main.o dica.o completa.o verificacao.o

clean:
	rm -f *~ *.o $(ALL)
