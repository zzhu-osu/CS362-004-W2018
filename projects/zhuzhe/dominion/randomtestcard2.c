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

void testVillageDrawnCard(struct gameState* s, struct gameState* test_s) {
    // 1) There is at least one card in the deck or the discard pile
    if (s->deckCount[s->whoseTurn] + s->discardCount[s->whoseTurn] >= 1) {
        printf("Draw 1 card:\n");
        printf("Num of Hand cards doesn't change (after removing the played card):\t");
        customAssert(test_s->handCount[test_s->whoseTurn] - s->handCount[s->whoseTurn], 0);
        printf("Num of deck + discard cards decreases by 1:\t");
        customAssert(s->deckCount[s->whoseTurn] + s->discardCount[s->whoseTurn]
            - test_s->deckCount[test_s->whoseTurn] - test_s->discardCount[test_s->whoseTurn], 1);
    }

    // 2) No card from the deck or the discard pile
    else {
        printf("No card from deck and discard pile:\n");
        printf("Num of Hand cards decreases by 1 (after removing the played card):\t");
        customAssert(s->handCount[s->whoseTurn] - test_s->handCount[test_s->whoseTurn], 1);
        printf("Discard pile doesn't change:\t");
        customAssert(s->discardCount[s->whoseTurn] - test_s->discardCount[test_s->whoseTurn], 0);
    }

    // All: numActions +2
    printf("numActions +2:\t");
    customAssert(test_s->numActions - s->numActions, 2);

}

void testVillageOther(struct gameState* s, struct gameState* test_s, int numPlayers) {
    printf("Test other state variables that shouldn't change:\n");
    int i;
    for (i=0; i<=treasure_map; i++) {
        printf("supplyCount[%d]:\t", i);
        customAssert(test_s->supplyCount[i], s->supplyCount[i]);
        printf("embargoTokens[%d]:\t", i);
        customAssert(test_s->embargoTokens[i], s->embargoTokens[i]);
    }
    printf("numBuys:\t");
    customAssert(test_s->numBuys, s->numBuys);
    
    int player;

    for (player=0; player<numPlayers; player++) {
        if (player != s -> whoseTurn) {
            printf("Other player #%d: \n", player);
            printf("handCount:\t");
            customAssert(test_s->handCount[player], s->handCount[player]);
            printf("deckCount:\t");
            customAssert(test_s->deckCount[player], s->deckCount[player]);
            printf("discardCount:\t");
            customAssert(test_s->discardCount[player], s->discardCount[player]);
        }
    }
}

int main() {

    printf("-------------------------Random Testing: Village-------------------------\n\n");
    int k[10] = {7,8,9,10,11,12,13,14,15,16};
    srand(time(NULL));
    
    struct gameState* s = malloc(sizeof(struct gameState));
    struct gameState* test_s = malloc(sizeof(struct gameState));

    int testTime;

    for (testTime = 1; testTime <= 3000; testTime++) {
        int numPlayers = rand() % 3 + 2;    // 2, 3 or 4
        int seed = rand();
        initializeGame(numPlayers, k, seed, s);

        s->whoseTurn = rand() % numPlayers;

        s->handCount[s->whoseTurn] = rand() % 20 + 1;
        s->deckCount[s->whoseTurn] = rand() % 20;
        s->discardCount[s->whoseTurn] = rand() % 50;

        int i;

        int testCardHandPos = rand() % s->handCount[s->whoseTurn];
        s->hand[s->whoseTurn][testCardHandPos] = village;
        s->supplyCount[village] --;

        for (i=0; i < s->handCount[s->whoseTurn]; i++) {
            if (i != testCardHandPos) {
                do {
                    s->hand[s->whoseTurn][i] = rand() % 17; // Available Cards: 0-16
                    s->supplyCount[s->hand[s->whoseTurn][i]] --;
                }
                while (s->supplyCount[s->hand[s->whoseTurn][i]] < 0);
            }
        }

        for (i=0; i < s->deckCount[s->whoseTurn]; i++) {
            do {
                s->deck[s->whoseTurn][i] = rand() % 17; // Available Cards: 0-16
                s->supplyCount[s->deck[s->whoseTurn][i]] --;
            }
            while (s->supplyCount[s->deck[s->whoseTurn][i]] < 0);
        }

        for (i=0; i < s->discardCount[s->whoseTurn]; i++) {
            do {
                s->discard[s->whoseTurn][i] = rand() % 17; // Available Cards: 0-16
                s->supplyCount[s->discard[s->whoseTurn][i]] --;
            }
            while (s->supplyCount[s->discard[s->whoseTurn][i]] < 0);
        }

        printf("\n\nNew Test Case:\n");
        printf("numPlayers: %d\n", numPlayers);
        printf("numHandCards: %d\n", numHandCards(s));
        printf("deckCount(): %d\n", s->deckCount[s -> whoseTurn]);
        printf("discardCount(): %d\n", s->discardCount[s -> whoseTurn]);
        
        memcpy(test_s, s, sizeof(struct gameState));

        int bonus = 0;
        int returnVal = cardEffect(village, 0, 0, 0, test_s, testCardHandPos, &bonus);
        testVillageDrawnCard(s, test_s);
        testVillageOther(s, test_s, numPlayers);
        
        if (returnVal < 0) {
            printf("Return value error: %d\n", returnVal);
            numFailure++;
        }
            
    }

    printf("Total Number of Failures: %d\n\n", numFailure);
    return 0;
}