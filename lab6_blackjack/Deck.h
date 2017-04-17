//
//  Deck.h
//  lab6_blackjack
//
//  Created by Cody Schrank on 4/15/17.
//  Copyright © 2017 CodySchrank. All rights reserved.
//

#ifndef Deck_h
#define Deck_h

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef struct Card {
    char *face;
    int value;
} Card ;

extern Card Deck[52];

void shuffleDeck();

#endif /* Deck_h */
