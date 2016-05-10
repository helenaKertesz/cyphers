CC=gcc
CFLAGS=-Wall -Werror
OBJS=enigma.o runEnigma.o

enigma: $(OBJS)
	$(CC) -o enigma $(OBJS)

enigma.o: enigma.c
runEnigma.o: runEnigma.c

clean:
	rm $(OBJS) enigma
