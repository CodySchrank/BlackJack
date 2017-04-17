//
//  Game.c
//  lab6_blackjack
//
//  Created by Cody Schrank on 4/16/17.
//  Copyright © 2017 CodySchrank. All rights reserved.
//

#include "Game.h"

/** Half a second of delay **/
#define NANO_SECOND_MULTIPLIER  1000000
const long INTERVAL_MS = 500 * NANO_SECOND_MULTIPLIER;
/** **/

void waitPrint();
void GameLoop();

Player player;
Player dealer;
int deckPosition;

void StartGame() {
    printf("Welcome to Black Jack!  I hope you brought alot of money.\n\n");
    printf("Press any key to start the game.  Press Q to quit\n");
    char choice;
    
    scanf(" %c", &choice);
    
    if(choice == 'q' || choice == 'Q') {
        return;
    } else {
        shuffleDeck(1);
        initPlayers(&player, &dealer);
        deckPosition = 0;
        
        StartRound();
    }
}

void StartRound() {
    int bet;
    printf("Your total number of chips is: %d\n", player.chips);
    printf("What is your bet?\n");
    //FIXME: BUG - Should only be allowed to bet what you have
    scanf(" %d", &bet);
    player.chips -= bet;
    
    waitPrint("Dealing Card To Player...");
    
    player.cards[player.arrayPosition] = Deck[deckPosition];
    printf("It was a: %s\n\n", Deck[deckPosition].face);
    player.arrayPosition++;
    deckPosition++;
    
    waitPrint("Dealing Card To Dealer...");
    
    dealer.cards[dealer.arrayPosition] = Deck[deckPosition];
    printf("It was a: %s\n\n", Deck[deckPosition].face);
    dealer.arrayPosition++;
    deckPosition++;
    
    waitPrint("Dealing Card To Player...");
    
    player.cards[player.arrayPosition] = Deck[deckPosition];
    printf("It was a: %s\n\n", Deck[deckPosition].face);
    player.arrayPosition++;
    deckPosition++;
    
    waitPrint("Dealing Card To Dealer...");
    
    dealer.cards[dealer.arrayPosition] = Deck[deckPosition];
    dealer.arrayPosition++;
    deckPosition++;
    
    waitPrint("It was a: *");
    
    GameLoop(bet);
}

char PrintGame(int bet) {
    waitPrint("\033[2J\033[1;1H");
    
    printf(" /~\\\n");
    printf("( oo|\n");
    printf(" \\=/\n\n");
    
    int i;
    printf("--");
    for(i = 0; i < dealer.arrayPosition - 1; i++) {
        printf("[");
        printf("%s",dealer.cards[i].face);
        printf("]");
    }
    printf("[*]--\n");
    printf("\n\n\n\n\n");
    
    printf("--");
    for(i = 0; i < player.arrayPosition; i++) {
        printf("[");
        printf("%s",player.cards[i].face);
        printf("]");
    }
    
    printf("--\n");
    printf("Your Bet: %d\n", bet);
    printf("Chips: %d\n", player.chips);
    printf("Press H to hit, Press S to stand, Press X to split, Press D to double down\n");
    
    char choice;
    scanf(" %c",&choice);
    
    return choice;
}

void GameLoop(int bet) {
    char choice;
    for(;;) {
        choice = PrintGame(bet);
        
        switch (choice) {
            case 'h':
                printf("here");
                break;
            
            case 's':
                printf("S");
                break;
                
            case 'x':
                printf("X");
                break;
                
            case 'd':
                printf("D");
                break;
                
            case 'q':
                //MARK: No idea if this works
                return;
            
            default:
                break;
        }
    }
    
}

void waitPrint(char *text) {
    printf("%s\n",text);
    struct timespec sleepValue = {0};
    
    sleepValue.tv_nsec = INTERVAL_MS;
    nanosleep(&sleepValue, NULL);
}
