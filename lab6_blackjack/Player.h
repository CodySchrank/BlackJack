//
//  Player.h
//  lab6_blackjack
//
//  Created by Cody Schrank on 4/16/17.
//  Copyright © 2017 CodySchrank. All rights reserved.
//

#ifndef Player_h
#define Player_h

#include <stdio.h>
#include <string.h>
#include "Deck.h"

typedef struct Player {
    char *name;
    int chips;
    int numberOfWins;
    int arrayPosition;
    Card cards[10];
} Player ;

void initPlayers();
void resetCards();
void betWinnings();

#endif /* Player_h */
