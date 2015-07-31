# myApp makefile2
CC = gcc
CFLAGS = -Wall -pedantic -std=c11 


# my project details
LIBFLAG = -lcurl -lm
EXEC = crawler
OBJS = hashtable.o list.o web.o
SRCS = crawler.c hashtable.c list.c web.c

# luckily, make has comments too!  

crawler: $(SRCS)
	$(CC) $(CFLAGS) -o crawler $(SRCS) $(LIBFLAG)

debug: $(SRCS)
	$(CC) $(CFLAGS) -g -ggdb -c $(SRCS)
	$(CC) $(CFLAGS) -g -ggdb -o $(EXEC) $(OBJS)

test:
	testCrawl.sh

# clean:
#         rm -f *~
#         rm -f *#
#         rm -f ./myApp
#         rm -f *.o
#         cd $(UTILDIR); make clean 
#remove the .gch