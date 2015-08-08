# myApp makefile

CC = gcc
CFlags = -Wall -pedantic -std=c11

# my project details
LIBFLAG = -lcurl -lm
EXEC = index
OBJS = file.o web.o hashIndex.o
SRCS = index.c file.c web.c hashIndex.c

index: $(SRCS)
	$(CC) $(CFLAGS) -o index $(SRCS) $(LIBFLAG)
