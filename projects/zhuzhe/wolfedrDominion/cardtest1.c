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
    if (s->deckCount[0] >= 3) {
        printf("Draw 3 cards from deck:\n");
        printf("Num of Hand cards increases by 2 (after discard):\t");
        customAssert(test_s->handCount[0] - s->handCount[0], 2);
        printf("Draw deck decreases by 3:\t");
        customAssert(s->deckCount[0] - test_s->deckCount[0], 3);
        printf("Discard pile does not change:\t");
        customAssert(test_s->discardCount[0] - s->discardCount[0], 0);
    }

    // 2) Less than 3 cards from the deck. Shuffle discard pile to add to the deck
    else if (s->deckCount[0] < 3 && (s->deckCount[0] + s->discardCount[0]) >= 3) {
        printf("Draw 3 cards from deck and discard pile:\n");
        printf("Num of Hand cards increases by 2 (after discard):\t");
        customAssert(test_s->handCount[0] - s->handCount[0], 2);
        printf("Empty discard pile:\t");
        customAssert(test_s->discardCount[0], 0);

        int draw_deck_count_expected = s->deckCount[0] + s->discardCount[0] - 3;
        printf("Deck decreases by %d:\t", draw_deck_count_expected);
        customAssert(test_s->deckCount[0], draw_deck_count_expected);
    }

    // 3) Less than 3 cards from the deck and discard pile combined. Draw as many as possible
    else {

        int num_card_drawn_expected = s->deckCount[0] + s->discardCount[0];
        printf("Draw %d cards from deck and discard pile:\n", num_card_drawn_expected);
        printf("Num of Hand cards increases by %d (after discard):\t", num_card_drawn_expected-1);
        customAssert(test_s->handCount[0] - s->handCount[0], num_card_drawn_expected-1);

        printf("Discard pile becomes empty:\t");
        customAssert(test_s->discardCount[0], 0);

        printf("Draw deck becomes empty:\t");
        customAssert(test_s->deckCount[0], 0);

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

    printf("-------------------------Testing: Smithy-------------------------\n\n");
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
        s->hand[0][0] = smithy;

        // Case 1. There are no less than 3 cards in the Deck
        memcpy(test_s, s, sizeof(struct gameState));

        int bonus = 0;
        cardEffect(smithy, 0, 0, 0, test_s, 0, &bonus);
        testSmithyDrawnCard(s, test_s);
        testSmithyOther(s, test_s, numPlayers);
        printf("\n");

        // Case 2. There are 2 cards in the deck and 2 cards in the Discard pile
        s->deckCount[0] = 2;
        s->discardCount[0] = 2;
        s->discard[0][0] = 5;
        s->discard[0][1] = 10;
        memcpy(test_s, s, sizeof(struct gameState));

        cardEffect(smithy, 0, 0, 0, test_s, 0, &bonus);
        testSmithyDrawnCard(s, test_s);
        testSmithyOther(s, test_s, numPlayers);
        printf("\n"); 

        // Case 3. 2 cards in the deck and no card in the Discard pile
        s->deckCount[0] = 2;
        s->discardCount[0] = 0;
        memcpy(test_s, s, sizeof(struct gameState));

        cardEffect(smithy, 0, 0, 0, test_s, 0, &bonus);
        testSmithyDrawnCard(s, test_s);
        testSmithyOther(s, test_s, numPlayers);
        printf("\n"); 
    }

    printf("Total Number of Failures: %d\n\n", numFailure);
    return 0;
}