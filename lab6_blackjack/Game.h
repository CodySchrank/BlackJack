//
//  Game.h
//  lab6_blackjack
//
//  Created by Cody Schrank on 4/16/17.
//  Copyright © 2017 CodySchrank. All rights reserved.
//

#ifndef Game_h
#define Game_h

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "Deck.h"
#include "Player.h"

void StartGame();
void StartRound();
char PrintGame(int, bool);

#endif /* Game_h */
