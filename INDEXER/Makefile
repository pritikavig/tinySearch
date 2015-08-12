# myApp makefile

CC = gcc
CFlags = -Wall -pedantic -std=c11

# my project details
LIBFLAG = -lcurl -lm
EXEC = index
OBJS = file.o web.o hashIndex.o
SRCS = ./src/buildIndex.c ./src/file.c ./src/web.c ./src/hash.c

index: $(SRCS)
	$(CC) $(CFLAGS) -o index $(SRCS) $(LIBFLAG)
test:
	BATS.sh
clean:
	rm -f *.o
      