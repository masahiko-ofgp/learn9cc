learn9cc: learn9cc.c

test: learn9cc
	./test.sh

clean:
	rm -f learn9cc *.o *~ tmp*
