#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"
#include "time.h"


#define RANDOMTEST_DEBUG 1

int numFailure = 0;

void customAssert(int a, int b) {
    if (a != b) {
        if (RANDOMTEST_DEBUG)
            printf("ERROR: %d is not equal to %d!\n\n", a, b);
        numFailure++;
    }
    else {
        if (RANDOMTEST_DEBUG)
            printf("PASSED\n");
    }
}

void testAdventurerDrawnCard(struct gameState* s, struct gameState* test_s) {
    // Count the number of treasure cards from the deck and/or discard pile

    int num_treasure = 0; int i;
    for (i=0; i < s->deckCount[s -> whoseTurn]; i++) {
        if (s->deck[s -> whoseTurn][i] == copper || s->deck[s -> whoseTurn][i] == gold
            || s->deck[s -> whoseTurn][i] == silver) {
            num_treasure++;
        }
    }
    for (i=0; i < s->discardCount[s -> whoseTurn]; i++) {
        if (s->discard[s -> whoseTurn][i] == copper || s->discard[s -> whoseTurn][i] == gold
            || s->discard[s -> whoseTurn][i] == silver) {
            num_treasure++;
        }
    }

    // 1) Draw 2 treasure cards
    if (num_treasure >= 2) {
        if (RANDOMTEST_DEBUG) {
            printf("Draw 2 treasure cards from deck:\n");
            printf("Num of Hand cards increases by 1 (after removing the played card):\t");
        }
        
        customAssert(test_s->handCount[test_s -> whoseTurn] - s->handCount[s -> whoseTurn], 1);

        if (RANDOMTEST_DEBUG) {
            printf("Total number of cards in draw deck and discard pile decreases by 2\n");
            printf("(after discarding the revealed non-treasure cards):\t");
        }
        customAssert(s->discardCount[s -> whoseTurn] + s->deckCount[s -> whoseTurn]
            - test_s->discardCount[test_s -> whoseTurn] - test_s->deckCount[test_s -> whoseTurn], 2);

        if (RANDOMTEST_DEBUG)
            printf("Drawn cards in hand should be treasure cards:\t");
        
        if ( (test_s->hand[test_s -> whoseTurn][ test_s->handCount[test_s -> whoseTurn]-1 ] != copper &&
            test_s->hand[test_s -> whoseTurn][ test_s->handCount[test_s -> whoseTurn]-1 ] != gold &&
            test_s->hand[test_s -> whoseTurn][ test_s->handCount[test_s -> whoseTurn]-1 ] != silver) ||
            (test_s->hand[test_s -> whoseTurn][ test_s->handCount[test_s -> whoseTurn]-2 ] != copper &&
            test_s->hand[test_s -> whoseTurn][ test_s->handCount[test_s -> whoseTurn]-2 ] != gold &&
            test_s->hand[test_s -> whoseTurn][ test_s->handCount[test_s -> whoseTurn]-2 ] != silver) ) {
                if (RANDOMTEST_DEBUG)
                    printf("ERROR: Drawn card is not a treasure card: %d %d\n", test_s->hand[test_s -> whoseTurn][ test_s->handCount[test_s -> whoseTurn]-1 ],
                        test_s->hand[test_s -> whoseTurn][ test_s->handCount[test_s -> whoseTurn]-2 ]);
                numFailure++;
            }
        else {
            if (RANDOMTEST_DEBUG)
                printf("PASSED\n");
        }
    }

    /*
    // 2) Less than 2 treasure cards from the deck and discard pile combined. Draw as many as possible
    else {
        if (RANDOMTEST_DEBUG) {
            printf("Draw %d treasure card(s) from deck and discard pile:\n", num_treasure);
            printf("Num of Hand cards increases by %d (after removing the played card):\t", num_treasure -1);
        }
        
        customAssert(test_s->handCount[test_s -> whoseTurn] - s->handCount[s -> whoseTurn], num_treasure -1);

        if (RANDOMTEST_DEBUG) {
        printf("Total number of cards in draw deck and discard pile decreases by %d\n", num_treasure);
        printf("(after discarding the revealed non-treasure cards):\t");
        }
        customAssert(s->discardCount[s -> whoseTurn] + s->deckCount[s -> whoseTurn]
            - test_s->discardCount[test_s -> whoseTurn] - test_s->deckCount[test_s -> whoseTurn], num_treasure);

        if (num_treasure == 1) {
            if (RANDOMTEST_DEBUG)
                printf("Drawn card in hand should be a treasure card:\t");
            if (test_s->hand[test_s -> whoseTurn][ test_s->handCount[test_s -> whoseTurn]-1 ] != copper &&
                test_s->hand[test_s -> whoseTurn][ test_s->handCount[test_s -> whoseTurn]-1 ] != gold &&
                test_s->hand[test_s -> whoseTurn][ test_s->handCount[test_s -> whoseTurn]-1 ] != silver) {
                if (RANDOMTEST_DEBUG)
                    printf("ERROR: Drawn card is not a treasure card: %d\n", test_s->hand[test_s -> whoseTurn][ test_s->handCount[test_s -> whoseTurn]-1 ]);
                numFailure++;
            }
            else {
                if (RANDOMTEST_DEBUG)
                    printf("PASSED\n");
            }
        }
        
    }
    */
}

void testAdventurerOther(struct gameState* s, struct gameState* test_s, int numPlayers) {
    if (RANDOMTEST_DEBUG)
        printf("Test other state variables that shouldn't change:\n");
    int i;
    for (i=0; i<=treasure_map; i++) {
        if (RANDOMTEST_DEBUG)
            printf("supplyCount[%d]:\t", i);
        customAssert(test_s->supplyCount[i], s->supplyCount[i]);
        if (RANDOMTEST_DEBUG)
            printf("embargoTokens[%d]:\t", i);
        customAssert(test_s->embargoTokens[i], s->embargoTokens[i]);
    }
    if (RANDOMTEST_DEBUG)
        printf("numActions:\t");
    customAssert(test_s->numActions, s->numActions);
    if (RANDOMTEST_DEBUG)
        printf("numBuys:\t");
    customAssert(test_s->numBuys, s->numBuys);
    
    int player;

    for (player=0; player<numPlayers; player++) {
        if (player != s -> whoseTurn) {
            if (RANDOMTEST_DEBUG) {
                printf("Other player #%d: \n", player);
                printf("handCount:\t");
            }
            
            customAssert(test_s->handCount[player], s->handCount[player]);
            if (RANDOMTEST_DEBUG)
                printf("deckCount:\t");
            customAssert(test_s->deckCount[player], s->deckCount[player]);
            if (RANDOMTEST_DEBUG)
                printf("discardCount:\t");
            customAssert(test_s->discardCount[player], s->discardCount[player]);
        }
        
    }
}

int main() {

    printf("-------------------------Random Testing: Adventurer-------------------------\n\n");
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
        s->hand[s->whoseTurn][testCardHandPos] = adventurer;
        s->supplyCount[adventurer] --;

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

        if (RANDOMTEST_DEBUG) {
            printf("\n\nNew Test Case:\n");
            printf("numPlayers: %d\n", numPlayers);
            printf("numHandCards: %d\n", numHandCards(s));
            printf("deckCount(): %d\n", s->deckCount[s -> whoseTurn]);
            printf("discardCount(): %d\n", s->discardCount[s -> whoseTurn]);
        }

        // Make sure 2 or more treasure cards in deck & discard pile combined.
        // Otherwise, the original dominion.c program crashes
        int num_treasure = 0;
        for (i=0; i < s->deckCount[s -> whoseTurn]; i++) {
            if (s->deck[s -> whoseTurn][i] == copper || s->deck[s -> whoseTurn][i] == gold
                || s->deck[s -> whoseTurn][i] == silver) {
                num_treasure++;
            }
        }
        for (i=0; i < s->discardCount[s -> whoseTurn]; i++) {
            if (s->discard[s -> whoseTurn][i] == copper || s->discard[s -> whoseTurn][i] == gold
                || s->discard[s -> whoseTurn][i] == silver) {
                num_treasure++;
            }
        }

        if (num_treasure < 2) { // skip the tests for this case; otherwise the dominion.c program crashes
            printf("Error: The original dominion.c code doesn't properly handle the situation - less than 2 treasure cards available");
            numFailure++;
            continue;
        }

        // Begin the tests
        memcpy(test_s, s, sizeof(struct gameState));

        
        int bonus = 0;
        int returnVal = cardEffect(adventurer, 0, 0, 0, test_s, testCardHandPos, &bonus);
        testAdventurerDrawnCard(s, test_s);
        testAdventurerOther(s, test_s, numPlayers);
        
        if (returnVal < 0) {
            if (RANDOMTEST_DEBUG)
                printf("Return value error: %d\n", returnVal);
            numFailure++;
        }
            
    }

    printf("Total Number of Failures: %d\n\n", numFailure);
    return 0;
}