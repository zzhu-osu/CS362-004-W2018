#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"

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

// Test Function: int getCost(int cardNumber)
int main() {

    printf("\nTesting: getCost()\n\n");

    printf("curse: ");
    customAssert(getCost(curse), 0);

    printf("estate: ");
    customAssert(getCost(estate), 2);

    printf("duchy: ");
    customAssert(getCost(duchy), 5);

    printf("province: ");
    customAssert(getCost(province), 8);

    printf("copper: ");
    customAssert(getCost(copper), 0);

    printf("silver: ");
    customAssert(getCost(silver), 3);

    printf("gold: ");
    customAssert(getCost(gold), 6);

    printf("adventurer: ");
    customAssert(getCost(adventurer), 6);

    printf("council_room: ");
    customAssert(getCost(council_room), 5);
    
    printf("feast: ");
    customAssert(getCost(feast), 4);

    printf("gardens: ");
    customAssert(getCost(gardens), 4);

    printf("mine: ");
    customAssert(getCost(mine), 5);

    printf("remodel: ");
    customAssert(getCost(remodel), 4);

    printf("smithy: ");
    customAssert(getCost(smithy), 4);

    printf("village: ");
    customAssert(getCost(village), 3);

    printf("baron: ");
    customAssert(getCost(baron), 4);

    printf("Total Number of Failures: %d\n\n", numFailure);
    return 0;
}