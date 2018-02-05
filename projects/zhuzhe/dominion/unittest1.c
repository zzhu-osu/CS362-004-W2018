#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"
#include "time.h"

int numFailure = 0;

void customAssert(int a, int b) {
    if (a != b) {
        printf("ERROR: %d is not equal to %d!\n\n", a, b);
        numFailure++;
    }
    else {
        printf("PASSED\n");
    }
}

// Test Function: int whoseTurn(struct gameState *state)
int main() {

    printf("Testing: whoseTurn()\n\n");
    int k[10] = {7,8,9,10,11,12,13,14,15,16};
    srand(time(NULL));
    int seed = rand();
    struct gameState* s = malloc(sizeof(struct gameState));

    int numPlayers;

    for (numPlayers = 2; numPlayers <= 4; numPlayers++) {
        initializeGame(numPlayers, k, seed, s);
        int i;
        for (i=0; i<numPlayers; i++) {
            s->whoseTurn = i;
            printf("numPlayers = %d, i = %d:\t", numPlayers, i);
            customAssert(whoseTurn(s), i);
        }
    }

    printf("Total Number of Failures: %d\n\n", numFailure);
    return 0;
}