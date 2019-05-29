learn9cc:
	gcc main.c parse.c codegen.c container.c -o learn9cc

test: learn9cc
	./learn9cc -test
	./test.sh

clean:
	rm -f learn9cc *.o *~ tmp*
