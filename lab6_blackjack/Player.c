//
//  Player.c
//  lab6_blackjack
//
//  Created by Cody Schrank on 4/16/17.
//  Copyright © 2017 CodySchrank. All rights reserved.
//

#include "Player.h"

void initPlayers(Player *player, Player *dealer) {
    player -> name = "player";
    player -> chips = 100;
    player -> numberOfWins = 0;
    player -> arrayPosition = 0;
    
    dealer -> name = "dealer";
    dealer -> chips = 1000000;
    dealer -> numberOfWins = 0;
    dealer -> arrayPosition = 0;
}

void resetCards(Player *player, Player *dealer) {
    player -> arrayPosition = 0;
    memset(player -> cards, 0, 10);
    
    dealer -> arrayPosition = 0;
    memset(dealer -> cards, 0, 10);
}

void betWinnings(Player *player, int bet) {
    int totalChips = player -> chips;
    totalChips += bet;
    
    player -> chips = totalChips;
}
