//
//  Deck.c
//  lab6_blackjack
//
//  Created by Cody Schrank on 4/15/17.
//  Copyright © 2017 CodySchrank. All rights reserved.
//

#include "Deck.h"

Card Deck[52];

Card ace = {.face = "A", .value = 0};

Card two = {.face = "2", .value = 2};

Card three = {.face = "3", .value = 3};

Card four = {.face = "4", .value = 4};

Card five = {.face = "5", .value = 5};

Card six = {.face = "6", .value = 6};

Card seven = {.face = "7", .value = 7};

Card eight = {.face = "8", .value = 8};

Card nine = {.face = "9", .value = 9};

Card ten = {.face = "10", .value = 10};

Card jack = {.face = "J", .value = 10};

Card queen = {.face = "Q", .value = 10};

Card king = {.face = "K", .value = 10};

void shuffleDeck(int firstShuffle) {
    if(firstShuffle) {
        srand((unsigned int)time(NULL));
    }
    
    Card cards[13] = {ace,two,three,four,five,six,seven,eight,nine,ten,jack,queen,king};
    
    int total = 0, cardUsed[13] = {0};
    while(total != 52) {
        int r = rand() % 13;
        Card cardPicked = cards[r];
        
        if(cardUsed[r] < 4) {
            Deck[total] = cardPicked;
            cardUsed[r]++;
            total++;
        }
    }

}











