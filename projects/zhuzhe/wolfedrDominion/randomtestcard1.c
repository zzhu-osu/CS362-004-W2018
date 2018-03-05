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

void testSmithyDrawnCard(struct gameState* s, struct gameState* test_s) {
    // 1) Draw all 3 cards from the deck
    if (s->deckCount[s->whoseTurn] >= 3) {
        printf("Draw 3 cards from deck:\n");
        printf("Num of Hand cards increases by 2 (after discard):\t");
        customAssert(test_s->handCount[test_s -> whoseTurn] - s->handCount[s -> whoseTurn], 2);
        printf("Draw deck decreases by 3:\t");
        customAssert(s->deckCount[s -> whoseTurn] - test_s->deckCount[test_s -> whoseTurn], 3);
        printf("Discard pile does not change:\t");
        customAssert(test_s->discardCount[test_s -> whoseTurn] - s->discardCount[s -> whoseTurn], 0);
    }

    // 2) Less than 3 cards from the deck. Shuffle discard pile to add to the deck
    else if (s->deckCount[s -> whoseTurn] < 3 && (s->deckCount[s -> whoseTurn] + s->discardCount[s -> whoseTurn]) >= 3) {
        printf("Draw 3 cards from deck and discard pile:\n");
        printf("Num of Hand cards increases by 2 (after discard):\t");
        customAssert(test_s->handCount[test_s -> whoseTurn] - s->handCount[s -> whoseTurn], 2);
        printf("Empty discard pile:\t");
        customAssert(test_s->discardCount[test_s -> whoseTurn], 0);

        int draw_deck_count_expected = s->deckCount[s -> whoseTurn] + s->discardCount[s -> whoseTurn] - 3;
        printf("Deck decreases by %d:\t", draw_deck_count_expected);
        customAssert(test_s->deckCount[test_s -> whoseTurn], draw_deck_count_expected);
    }

    // 3) Less than 3 cards from the deck and discard pile combined. Draw as many as possible
    else {

        int num_card_drawn_expected = s->deckCount[s -> whoseTurn] + s->discardCount[s -> whoseTurn];
        printf("Draw %d cards from deck and discard pile:\n", num_card_drawn_expected);
        printf("Num of Hand cards increases by %d (after discard):\t", num_card_drawn_expected-1);
        customAssert(test_s->handCount[test_s -> whoseTurn] - s->handCount[s -> whoseTurn], num_card_drawn_expected-1);

        printf("Discard pile becomes empty:\t");
        customAssert(test_s->discardCount[test_s -> whoseTurn], 0);

        printf("Draw deck becomes empty:\t");
        customAssert(test_s->deckCount[test_s -> whoseTurn], 0);

    }
}

void testSmithyOther(struct gameState* s, struct gameState* test_s, int numPlayers) {
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

    printf("-------------------------Random Testing: Smithy-------------------------\n\n");
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
        s->hand[s->whoseTurn][testCardHandPos] = smithy;
        s->supplyCount[smithy] --;

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
        int returnVal = cardEffect(smithy, 0, 0, 0, test_s, testCardHandPos, &bonus);
        testSmithyDrawnCard(s, test_s);
        testSmithyOther(s, test_s, numPlayers);
        
        if (returnVal < 0) {
            printf("Return value error: %d\n", returnVal);
            numFailure++;
        }
            
    }

    printf("Total Number of Failures: %d\n\n", numFailure);
    return 0;
}