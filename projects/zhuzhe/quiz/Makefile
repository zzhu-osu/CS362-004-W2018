all: testme

run: testme
	./testme

testme: testme.o
	gcc testme.o -o testme

testme.o: testme.c
	gcc -O3 -c testme.c

clean:
	rm *.o