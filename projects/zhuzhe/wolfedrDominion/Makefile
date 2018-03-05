CFLAGS = -Wall -fpic --coverage -lm

all: playdom player randomTests runRandomTests unitTests runUnitTests

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/


unitTests: unittest1.c unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c dominion.o rngs.o
	gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
	gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
	gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
	gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
	gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)

randomTests: randomtestadventurer.c randomtestcard1.c randomtestcard2.c dominion.o rngs.o
	gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
	gcc -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o $(CFLAGS)
	gcc -o randomtestcard2 -g  randomtestcard2.c dominion.o rngs.o $(CFLAGS)

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

#runtests: testDrawCard 
#	./testDrawCard &> unittestresult.out
#	gcov dominion.c >> unittestresult.out
#	cat dominion.c.gcov >> unittestresult.out

runRandomTests:
	rm -f *.gcda
	./randomtestadventurer > randomtestadventurer.out
	gcov -bf randomtestadventurer.c >> randomtestadventurer.out
	cat randomtestadventurer.c.gcov >> randomtestadventurer.out
	gcov -bf dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out
	rm -f *.gcda
	./randomtestcard1 > randomtestcard1.out
	gcov -bf randomtestcard1.c >> randomtestcard1.out
	cat randomtestcard1.c.gcov >> randomtestcard1.out
	gcov -bf dominion.c >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out
	rm -f *.gcda
	./randomtestcard2 > randomtestcard2.out
	gcov -bf randomtestcard2.c >> randomtestcard2.out
	cat randomtestcard2.c.gcov >> randomtestcard2.out
	gcov -bf dominion.c >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out
	rm -f *.gcda

runUnitTests:
	rm -f *.gcda
	./unittest1 > unittestresults.out
	gcov -bf dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	rm -f *.gcda
	./unittest2 >> unittestresults.out
	gcov -bf dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	rm -f *.gcda
	./unittest3 >> unittestresults.out
	gcov -bf dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	rm -f *.gcda
	./unittest4 >> unittestresults.out
	gcov -bf dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	rm -f *.gcda
	./cardtest1 >> unittestresults.out
	gcov -bf dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	rm -f *.gcda
	./cardtest2 >> unittestresults.out
	gcov -bf dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	rm -f *.gcda
	./cardtest3 >> unittestresults.out
	gcov -bf dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	rm -f *.gcda
	./cardtest4 >> unittestresults.out
	gcov -bf dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	rm -f *.gcda

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)


clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out \
	testDrawCard testDrawCard.exe unittest? unittest?.exe cardtest? cardtest?.exe
