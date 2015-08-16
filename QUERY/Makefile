# myApp makefile

CC = gcc
CFlAGS = -Wall -pedantic -std=c11

# my project details
LIBFLAG = -lm

EXEC = query
OBJS = rank.o 
SRCS = ./src/query.c  ./src/rank.c 
MAIN = ./src/query.c



UTILDIR=../util/
UTILFLAG=-ltseutil -static
UTILLIB=$(UTILDIR)libtseutil.a 
UTILC=$(UTILDIR)file.c $(UTILDIR)web.c $(UTILDIR)hash.c
UTILH=$(UTILC:.c=.h) $(UTILDIR)common.h

query: $(SRCS) $(UTILLIB)
	$(CC) $(CFLAGS) -o query $(SRCS) -L$(UTILDIR) $(UTILFLAG) -I$(UTILDIR)
debug: $(SRCS)
	$(CC) $(CFLAGS) -g -ggdb -c $(SRCS)
	$(CC) $(CFLAGS) -g -ggdb -o $(EXEC) $(MAIN) $(OBJS)
$(UTILLIB): $(UTILC) $(UTILH)
	cd $(UTILDIR); make
clean:
	rm -f *.o
	rm -f ./src/*.o
      
