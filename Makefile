CFLAGS=-Wall -std=c11
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

learn9cc: $(OBJS)
	$(CC) -o learn9cc $(OBJS) $(LDFLAGS)

$(OBJS): learn9cc.h

test: learn9cc
	./learn9cc -test
	./test.sh

clean:
	rm -f learn9cc *.o *~ tmp*
