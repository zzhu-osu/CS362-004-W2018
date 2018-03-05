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

void testAdventurerDrawnCard(struct gameState* s, struct gameState* test_s) {
    // Count the number of treasure cards from the deck and/or discard pile

    int num_treasure = 0; int i;
    for (i=0; i < s->deckCount[0]; i++) {
        if (s->deck[0][i] == copper || s->deck[0][i] == gold || s->deck[0][i] == silver) {
            num_treasure++;
        }
    }
    for (i=0; i < s->discardCount[0]; i++) {
        if (s->discard[0][i] == copper || s->discard[0][i] == gold || s->discard[0][i] == silver) {
            num_treasure++;
        }
    }

    // 1) Draw 2 treasure cards
    if (num_treasure >= 2) {
        printf("Draw 2 treasure cards from deck:\n");
        printf("Num of Hand cards increases by 1 (after removing the played card):\t");
        customAssert(test_s->handCount[0] - s->handCount[0], 1);
        printf("Total number of cards in draw deck and discard pile decreases by 2\n");
        printf("(after discarding the revealed non-treasure cards):\t");
        customAssert(s->discardCount[0] + s->deckCount[0] - test_s->discardCount[0] - test_s->deckCount[0], 2);

        printf("Drawn cards in hand should be treasure cards:\t");
        if ( (test_s->hand[0][ test_s->handCount[0]-1 ] != copper &&
            test_s->hand[0][ test_s->handCount[0]-1 ] != gold &&
            test_s->hand[0][ test_s->handCount[0]-1 ] != silver) ||
            (test_s->hand[0][ test_s->handCount[0]-2 ] != copper &&
            test_s->hand[0][ test_s->handCount[0]-2 ] != gold &&
            test_s->hand[0][ test_s->handCount[0]-2 ] != silver) ) {
                printf("ERROR: Drawn card is not a treasure card: %d %d\n", test_s->hand[0][ test_s->handCount[0]-1 ],
                    test_s->hand[0][ test_s->handCount[0]-2 ]);
                numFailure++;
            }
        else {
            printf("PASSED\n");
        }
    }


    // 2) Less than 2 treasure cards from the deck and discard pile combined. Draw as many as possible
    else {

        printf("Draw %d treasure card(s) from deck and discard pile:\n", num_treasure);
        printf("Num of Hand cards increases by %d (after removing the played card):\t", num_treasure -1);
        customAssert(test_s->handCount[0] - s->handCount[0], num_treasure -1);

        printf("Total number of cards in draw deck and discard pile decreases by %d\n", num_treasure);
        printf("(after discarding the revealed non-treasure cards):\t");
        customAssert(s->discardCount[0] + s->deckCount[0] - test_s->discardCount[0] - test_s->deckCount[0], num_treasure);

        if (num_treasure == 1) {
            printf("Drawn card in hand should be a treasure card:\t");
            if (test_s->hand[0][ test_s->handCount[0]-1 ] != copper &&
                test_s->hand[0][ test_s->handCount[0]-1 ] != gold &&
                test_s->hand[0][ test_s->handCount[0]-1 ] != silver) {
                printf("ERROR: Drawn card is not a treasure card: %d\n", test_s->hand[0][ test_s->handCount[0]-1 ]);
                numFailure++;
            }
            else {
                printf("PASSED\n");
            }
        }
        
    }
}

void testAdventurerOther(struct gameState* s, struct gameState* test_s, int numPlayers) {
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

    printf("-------------------------Testing: Adventurer-------------------------\n\n");
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
        s->hand[0][0] = adventurer;

        // Case 1. There are no less than 2 treasure cards in the Deck
        s->deckCount[0] = 5;
        s->deck[0][3] = silver;
        s->deck[0][4] = gold;
        memcpy(test_s, s, sizeof(struct gameState));

        int bonus = 0;
        cardEffect(adventurer, 0, 0, 0, test_s, 0, &bonus);
        testAdventurerDrawnCard(s, test_s);
        testAdventurerOther(s, test_s, numPlayers);
        printf("\n");

        // Case 2. There are 1 treasure card in the deck and 1 treasure card in the Discard pile
        s->deckCount[0] = 3;
        s->deck[0][0] = gardens,
        s->deck[0][1] = silver,
        s->deck[0][2] = village,

        s->discardCount[0] = 2;
        s->discard[0][0] = gold;
        s->discard[0][1] = council_room;
        memcpy(test_s, s, sizeof(struct gameState));

        cardEffect(smithy, 0, 0, 0, test_s, 0, &bonus);
        testAdventurerDrawnCard(s, test_s);
        testAdventurerOther(s, test_s, numPlayers);
        printf("\n"); 

        // Case 3. 1 treasure card in the deck and no card in the Discard pile
        s->discardCount[0] = 0;
        memcpy(test_s, s, sizeof(struct gameState));

        cardEffect(smithy, 0, 0, 0, test_s, 0, &bonus);
        testAdventurerDrawnCard(s, test_s);
        testAdventurerOther(s, test_s, numPlayers);
        printf("\n"); 
    }

    printf("Total Number of Failures: %d\n\n", numFailure);
    return 0;
}