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

void testGardens(struct gameState* s, struct gameState* test_s) {
    
        printf("Num of Hand cards decreases by 1 (after removing the played card):\t");
        customAssert(s->handCount[0] - test_s->handCount[0], 1);
        int expected_score_increase = (test_s->handCount[0] + test_s->deckCount[0]
            + test_s->discardCount[0] ) / 10;
        printf("Score for player 0 increases by %d:\t", expected_score_increase);
        customAssert(scoreFor(0, test_s) - scoreFor(0, s), expected_score_increase);

}

void testGardensOther(struct gameState* s, struct gameState* test_s, int numPlayers) {
    printf("Test other state variables that shouldn't change:\n");
    int i;
    for (i=0; i<=treasure_map; i++) {
        printf("supplyCount[%d]:\t", i);
        customAssert(test_s->supplyCount[i], s->supplyCount[i]);
        printf("embargoTokens[%d]:\t", i);
        customAssert(test_s->embargoTokens[i], s->embargoTokens[i]);
    }
    printf("numActions:\t");
    customAssert(test_s->numActions, s->numActions);
    printf("numBuys:\t");
    customAssert(test_s->numBuys, s->numBuys);
    
    int player;

    for (player=1; player<numPlayers; player++) {
        printf("Other player #%d: \n", player);
        printf("handCount:\t");
        customAssert(test_s->handCount[player], s->handCount[player]);
        printf("deckCount:\t");
        customAssert(test_s->deckCount[player], s->deckCount[player]);
        printf("discardCount:\t");
        customAssert(test_s->discardCount[player], s->discardCount[player]);
    }
}

int main() {

    printf("-------------------------Testing: Gardens-------------------------\n\n");
    int k[10] = {7,8,9,10,11,12,13,14,15,16};
    srand(time(NULL));
    
    struct gameState* s = malloc(sizeof(struct gameState));
    struct gameState* test_s = malloc(sizeof(struct gameState));

    int numPlayers;

    for (numPlayers = 2; numPlayers <= 4; numPlayers++) {
        int seed = rand();
        initializeGame(numPlayers, k, seed, s);
        //printf("numHandCards: %d\n", numHandCards(s));
        //printf("handCard(0): %d\n", handCard(0,s));
        //printf("deckCount(0): %d\n", s->deckCount[0]);
        //printf("discardCount(0): %d\n", s->discardCount[0]);

        s->whoseTurn = 0;
        s->hand[0][0] = gardens;

        memcpy(test_s, s, sizeof(struct gameState));

        int bonus = 0;
        int status = cardEffect(gardens, 0, 0, 0, test_s, 0, &bonus);
        printf("Function status check:\t");
        customAssert(status, 0);
        testGardens(s, test_s);
        testGardensOther(s, test_s, numPlayers);
        printf("\n");

        
    }

    printf("Total Number of Failures: %d\n\n", numFailure);
    return 0;
}