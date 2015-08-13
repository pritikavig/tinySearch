# myApp makefile

CC = gcc
CFlags = -Wall -pedantic -std=c11

# my project details
LIBFLAG = -lcurl -lm
EXEC = index
OBJS = file.o web.o hash.o
SRCS = ./src/buildIndex.c ./src/file.c ./src/web.c ./src/hash.c
MAIN = ./src/buildIndex.c
index: $(SRCS)
	$(CC) $(CFLAGS) -o index $(SRCS) $(LIBFLAG)
debug: $(SRCS)
	$(CC) $(CFLAGS) -g -ggdb -c $(SRCS)
	$(CC) $(CFLAGS) -g -ggdb -o $(EXEC) $(MAIN) $(OBJS)

test:
	BATS.sh
clean:
	rm -f *.o
      
