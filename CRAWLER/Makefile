# myApp makefile2
CC = gcc
CFLAGS = -Wall -pedantic -std=c11  


# my project details
LIBFLAG = -lcurl -lm
EXEC = crawler
OBJS = ./src/hashtable.o ./src/list.o web.o
SRCS = ./src/crawler.c ./src/hashtable.c ./src/list.c ./src/web.c

# luckily, make has comments too!  

crawler: $(SRCS)
	$(CC) $(CFLAGS) -o crawler $(SRCS) $(LIBFLAG)

debug: $(SRCS)
	$(CC) $(CFLAGS) -g -ggdb -c $(SRCS)
	$(CC) $(CFLAGS) -g -ggdb -o $(EXEC) $(OBJS)

test:
	mkdir testHold/
	testCrawl.sh
	rm -rf testHold/

force:
	touch ./src/crawler.c
	make

clean:
	rm *.o

