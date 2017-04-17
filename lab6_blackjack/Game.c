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

void GameLoop();
void waitPrint();
void hit();
void dealerPlay();
bool checkWin();
bool checkLose();
void winnerScreen();
void tieScreen();

Player player;
Player dealer;
int deckPosition;
bool playerDone = false;

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
        
        //continue game here;
        
    }
}

void StartRound() {
    int bet;
    playerDone = false;
    printf("Your total number of chips is: %d\n", player.chips);
    printf("What is your bet?\n");
    //FIXME: BUG - Should only be allowed to bet what you have
    scanf(" %d", &bet);
    player.chips -= bet;
    
    waitPrint("Dealing Card To Player...");
    
    printf("It was a: %s\n\n", Deck[deckPosition].face);
    
    hit(&player);
    
    waitPrint("Dealing Card To Dealer...");
    
    printf("It was a: %s\n\n", Deck[deckPosition].face);
    hit(&dealer);
    
    waitPrint("Dealing Card To Player...");
    
    printf("It was a: %s\n\n", Deck[deckPosition].face);
    hit(&player);
    
    waitPrint("Dealing Card To Dealer...");
    
    waitPrint("It was a: *");
    hit(&dealer);
    
    GameLoop(bet);
}

char PrintGame(int bet, bool shouldChoose) {
    waitPrint("\033[2J\033[1;1H");
    
    printf(" /~\\\n");
    printf("( oo|\n");
    printf(" \\=/\n\n");
    
    int i;
    printf("--");
    
    for(i = 0; i < dealer.arrayPosition - 1; i++) { //change to dealer.arrayPosition - 1 when done
        printf("[");
        printf("%s",dealer.cards[i].face);
        printf("]");
    }
    
    if(shouldChoose) {
        printf("[*]--\n");
    } else {
        printf("[%s]--\n", dealer.cards[dealer.arrayPosition - 1].face);
    }
    
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
    
    char choice = '0';
    if(shouldChoose) {
        printf("Press H to hit, Press S to stand, Press D to double down\n");
        
        scanf(" %c",&choice);
    }
    
    return choice;
}

void GameLoop(int bet) {
    char choice;
    
    for(;;) {
        Player winner = {.name = "nil"};
        //TODO:  Check win or lose
        bool win = checkWin(true, &winner);
        bool lose = checkLose(&winner);

        
        if(win && winner.name != NULL) {
            winnerScreen(&winner);
            break;
        } else if (win && winner.name == NULL){ //TODO: tie
            tieScreen();
            break;
        } else if (lose) {
            winnerScreen(&winner);
            break;
        } else {
            choice = PrintGame(bet, true);
            
            switch (choice) {
                case 'h':
                    //TODO: Not done testing
                    waitPrint("Dealing Card To Player...");
                    
                    printf("It was a: %s\n\n", Deck[deckPosition].face);
                    
                    hit(&player);
                    
                    lose = checkLose(&winner);
                    if(lose) {
                        break;
                    }
                    
                    dealerPlay();
                    win = checkWin(false, &winner);
                    if(win) {
                        break;
                    }
                    
                    lose = checkLose(&winner);
                    if(lose) {
                        break;
                    }
                    
                    break;
                
                case 's':
                    playerDone = true;
                    win = checkWin(false, &winner);
                    
                    if(win) {
                        break;
                    }
                    
                    for(;;) {
                        win = checkWin(false, &winner);
                        if(win) {
                            break;
                        }
                        
                        dealerPlay();
                        lose = checkLose(&winner);
                        if(lose) {
                            break;
                        }
                    }
                    
                    PrintGame(bet, false);
                    
                    break;
                    
                case 'd':
                    printf("D");
                    break;
                    
                case 'q':
                    return;
                
                default:
                    break;
            }
                
        }
        
        if(win && winner.name != NULL) {
            winnerScreen(&winner);
            break;
        } else if (win && winner.name == NULL){ //TODO: tie
            tieScreen();
            break;
        } else if (lose) {
            winnerScreen(&winner);
            break;
        }
    }
}


/**

Returns true and points to winner - Someone Won
Returns true and points to NULL - tie
Returns false and points to NULL - Win conditions not met
 
**/
bool checkWin(int firstRound, Player *winner) {
    int playerTotal = 0, dealerTotal = 0;
    
    int i,j;
    
    for(i = 0; i < dealer.arrayPosition; i++) {
        int card = dealer.cards[i].value;
        
        if(card == 0) {
            //MARK: I believe working solution to count Aces
            int shouldBeAceTotal = 0;
            for(j = 0; j < dealer.arrayPosition; j++) {
                shouldBeAceTotal += dealer.cards[j].value;
                if(shouldBeAceTotal > 10) {
                    dealer.cards[i].value = 1;
                } else {
                    dealer.cards[i].value = 11;
                }
            }
        }
        
        dealerTotal += dealer.cards[i].value;
    }
    
    for(i = 0; i < player.arrayPosition; i++) {
        //TODO: Check ACE
        playerTotal += player.cards[i].value;
    }
    
    if(firstRound) {
        if(playerTotal == 21) {
            memcpy (winner, &player, sizeof (player));
            return true;
        } else if (dealerTotal == 21) {
            memcpy (winner, &dealer, sizeof (dealer));
            return true;
        }
    } else {
        if(dealerTotal >= 17 && dealerTotal <= 21 && playerTotal <= 21) {
            if(playerTotal > dealerTotal) {
                memcpy (winner, &player, sizeof (player));
                return true;
            } else if(dealerTotal > playerTotal  && playerDone) {
                memcpy (winner, &dealer, sizeof (dealer));
                return true;
            } else if(playerDone) {
                winner -> name = NULL;
                return true;
            }
        }
    }
    
    return false;
}

/**

Return true if someone loses - point to the winner
Returns false if lose conditions not met - point to NULL
 
**/

bool checkLose(Player *winner) {
    int playerTotal = 0, dealerTotal = 0;
    
    int i;
    
    for(i = 0; i < dealer.arrayPosition; i++) {
        dealerTotal += dealer.cards[i].value;
    }
    
    for(i = 0; i < player.arrayPosition; i++) {
        playerTotal += player.cards[i].value;
    }
    
    if(playerTotal > 21) {
        memcpy (winner, &dealer, sizeof (dealer));
        return true;
    } else if(dealerTotal > 21) {
        memcpy (winner, &player, sizeof (player));
        return true;
    } else {
        return false;
    }
}


void hit(Player *person) {
    //TODO: Check deck overflow
    person -> cards[person -> arrayPosition] = Deck[deckPosition];
    person -> arrayPosition++;
    deckPosition++;
}

void dealerPlay() {
    int dealerTotal = 0;
    
    int i;
    for(i = 0; i < dealer.arrayPosition; i++) {
        
        //TODO: Check ACE
        dealerTotal += dealer.cards[i].value;
    }
    
    if(dealerTotal < 17) {
        waitPrint("Dealing Card To Dealer...");
        
        printf("It was a: %s\n\n", Deck[deckPosition].face);
        hit(&dealer);
    }
}

void winnerScreen(Player *person) {
    printf("%s\n", person -> name);
}

void tieScreen() {
    printf("tie\n");
}

void waitPrint(char *text) {
    printf("%s\n",text);
    struct timespec sleepValue = {0};
    
    sleepValue.tv_nsec = INTERVAL_MS;
    nanosleep(&sleepValue, NULL);
}
