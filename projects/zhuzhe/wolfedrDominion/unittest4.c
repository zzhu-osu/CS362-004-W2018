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

// Test Function: int isGameOver(struct gameState *s)
int main() {

    printf("-------------------------Testing: isGameOver()-------------------------\n\n");
    int k[10] = {7,8,9,10,11,12,13,14,15,16};
    srand(time(NULL));
    int seed = rand();
    struct gameState* s = malloc(sizeof(struct gameState));

    int numPlayers;

    for (numPlayers = 2; numPlayers <= 4; numPlayers++) {
        initializeGame(numPlayers, k, seed, s);
        int i, j;
        for (i=0; i<numPlayers; i++) {
            printf("numPlayers = %d, player = %d:\n", numPlayers, i);

            // case 1: Province cards depleted; Other supply piles not empty
            printf("Province cards depleted; Other supply piles not empty:\t");
            s->supplyCount[province] = 0;
            for (j=0; j<25; j++) {
                if (j != province && s->supplyCount[j] == 0) {
                    s->supplyCount[j] = 1;
                }
            }
            customAssert(isGameOver(s), 1);

            // case 2: No empty supply pile
            printf("No empty supply pile:\t");
            for (j=0; j<25; j++) {
                if (s->supplyCount[j] == 0) {
                    s->supplyCount[j] = 1;
                }
            }
            customAssert(isGameOver(s), 0);

            // case 3: Exactly 1 supply pile is empty (other than Province pile)
            printf("Exactly 1 supply pile is empty (other than Province pile):\t");
            int a_supply_pile_on_table = -1;
            for (j=0; j<25; j++) {
                if (a_supply_pile_on_table < 0 && s->supplyCount[j] >= 0) {
                    a_supply_pile_on_table = j;
                }
                else if (s->supplyCount[j] == 0) {
                    s->supplyCount[j] = 1;
                }
            }
            s->supplyCount[a_supply_pile_on_table] = 0;
            customAssert(isGameOver(s), 0);

            // case 4: Exactly 2 supply piles empty (other than Province pile)
            printf("Exactly 2 supply piles empty (other than Province pile):\t");
            a_supply_pile_on_table = -1;
            int b_supply_pile_on_table = -1;
            for (j=0; j<25; j++) {
                if (j != province && a_supply_pile_on_table < 0 && s->supplyCount[j] >= 0) {
                    a_supply_pile_on_table = j;
                }
                else if (j != province && a_supply_pile_on_table >= 0 && b_supply_pile_on_table < 0
                    && s->supplyCount[j] >= 0) {
                    b_supply_pile_on_table = j;
                }
                else if (s->supplyCount[j] == 0) {
                    s->supplyCount[j] = 1;
                }
            }
            s->supplyCount[a_supply_pile_on_table] = 0;
            s->supplyCount[b_supply_pile_on_table] = 0;
            customAssert(isGameOver(s), 0);
            //printf("a=%d, b=%d\n", a_supply_pile_on_table, b_supply_pile_on_table);

            // case 5: Exactly 3 supply piles empty (other than Province pile)
            printf("Exactly 3 supply piles empty (other than Province pile):\t");
            a_supply_pile_on_table = -1, b_supply_pile_on_table = -1;
            int c_supply_pile_on_table = -1;
            for (j=0; j<25; j++) {
                if (j != province && a_supply_pile_on_table < 0 && s->supplyCount[j] >= 0) {
                    a_supply_pile_on_table = j;
                }
                else if (j != province && a_supply_pile_on_table >= 0 && b_supply_pile_on_table < 0
                    && s->supplyCount[j] >= 0) {
                    b_supply_pile_on_table = j;
                }
                else if (j != province && a_supply_pile_on_table >= 0 && b_supply_pile_on_table >= 0
                    && c_supply_pile_on_table < 0 && s->supplyCount[j] >= 0) {
                    c_supply_pile_on_table = j;
                }
                else if (s->supplyCount[j] == 0) {
                    s->supplyCount[j] = 1;
                }
            }
            s->supplyCount[a_supply_pile_on_table] = 0;
            s->supplyCount[b_supply_pile_on_table] = 0;
            s->supplyCount[c_supply_pile_on_table] = 0;
            customAssert(isGameOver(s), 1);
            //printf("a=%d, b=%d, c=%d\n", a_supply_pile_on_table, b_supply_pile_on_table, c_supply_pile_on_table);

            // case 6: Exactly 4 supply piles empty (other than Province pile)
            printf("Exactly 4 supply piles empty (other than Province pile):\t");
            for (j=0; j<25; j++) {
                if (s->supplyCount[j] == 0) {
                    s->supplyCount[j] = 1;
                }
            }
            s->supplyCount[8] = 0;
            s->supplyCount[9] = 0;
            s->supplyCount[10] = 0;
            s->supplyCount[11] = 0;
            customAssert(isGameOver(s), 1);

        }
        printf("\n");
    }

    printf("Total Number of Failures: %d\n\n", numFailure);
    return 0;
}