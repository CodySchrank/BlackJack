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
        deckPosition = 0;
        initPlayers(&player, &dealer);
        
        
        
        for(;;) {
            resetCards(&player, &dealer);
            StartRound();
        }
    }
}

void StartRound() {
    int bet = -1;
    playerDone = false;
    
    
    printf("Your total number of chips is: %d\n", player.chips);
    printf("What is your bet?\n");
    
    for(;;) {
        scanf(" %d", &bet);
        printf("\n");
        if(bet == -1) {
            char option;
            scanf(" %c", &option);
            printf("\n");
            
            if(option == 'q' || option == 'Q') {
                exit(0);
            } else {
                return;
            }
        
        } else if(bet <= 0) {
            printf("You can't bet that\n");
        } else if(bet > player.chips ) {
            printf("You don't have that much money!\n");
        } else {
            break;
        }
    }
    
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

char PrintGame(int bet, bool shouldChoose, char *text, bool isPlayer) {
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
        printf("[*]--\n\n\n\n\n\n");
    } else {
        printf("[%s]--\n", dealer.cards[dealer.arrayPosition - 1].face);
        
        if(isPlayer) {
            char playerTextUpper[] = "";
            int i = 0;
            
            while(text[i]) {
                playerTextUpper[i] = toupper(text[i]);
                i++;
            }
            
            printf("\n\n---%s WON---\n\n\n", playerTextUpper);
        } else {
            printf("\n\n---%s---\n\n\n", text);
        }
    }
    
    printf("--");
    for(i = 0; i < player.arrayPosition; i++) {
        printf("[");
        printf("%s",player.cards[i].face);
        printf("]");
    }
    
    printf("--\n");
    
    char choice = '0';
    if(shouldChoose) {
        printf("Your Bet: %d\n", bet);
        printf("Chips: %d\n\n", player.chips);
        printf("Press H to hit, Press S to stand, Press D to double down\n");
        
        scanf(" %c",&choice);
    }
    
    return choice;
}

void GameLoop(int bet) {
    char choice;
    bool firstRound = true;
    Player winner = {.name = "nil"};
    bool win = checkWin(true, &winner, bet);
    bool lose = checkLose(&winner, bet);
    
    for(;;) {
        if(win && winner.name != NULL) {
            winnerScreen(&winner);
            break;
        } else if (win && winner.name == NULL){ //tie
            tieScreen();
            break;
        } else if (lose) {
            winnerScreen(&winner);
            break;
        } else {
            choice = PrintGame(bet, true, "", false);
            
            switch (choice) {
                case 'h':
                    waitPrint("Dealing Card To Player...");
                    
                    printf("It was a: %s\n\n", Deck[deckPosition].face);
                    waitPrint("");
                    
                    hit(&player);
                    
                    lose = checkLose(&winner, bet);
                    if(lose) {
                        break;
                    }
                    
                    win = checkWin(false, &winner, bet);
                    if(win) {
                        break;
                    }
                    
                    break;
                
                case 's':
                    playerDone = true;
                    win = checkWin(false, &winner, bet);
                    
                    if(win) {
                        break;
                    }
                    
                    for(;;) {
                        win = checkWin(false, &winner, bet);
                        if(win) {
                            break;
                        }
                        
                        dealerPlay();
                        lose = checkLose(&winner, bet);
                        if(lose) {
                            break;
                        }
                    }
                    
                    break;
                    
                case 'd':
                    if(firstRound) {
                        if(bet * 2 > player.chips) {
                            waitPrint("You don't have enough money");
                            break;
                        } else {
                            player.chips -= bet;
                            bet *= 2;
                        }
                        
                        waitPrint("Dealing Card To Player...");
                        
                        printf("It was a: %s\n\n", Deck[deckPosition].face);
                        waitPrint("");
                        
                        hit(&player);
                        
                        lose = checkLose(&winner, bet);
                        if(lose) {
                            break;
                        }

                        playerDone = true;
                        
                        for(;;) {
                            win = checkWin(false, &winner, bet);
                            if(win) {
                                break;
                            }
                            
                            dealerPlay();
                            lose = checkLose(&winner, bet);
                            if(lose) {
                                break;
                            }
                        }
                        
                        break;
                    } else {
                        printf("You can't double down now.\n");
                        break;
                    }
                
                default:
                    break;
            }
                
        }
        
        if(win && winner.name != NULL) {
            winnerScreen(&winner);
            break;
        } else if (win && winner.name == NULL){ //tie
            tieScreen();
            break;
        } else if (lose) {
            winnerScreen(&winner);
            break;
        }
        
        firstRound = false;
    }
}


/**

Returns true and points to winner - Someone Won
Returns true and points to NULL - tie
Returns false and points to NULL - Win conditions not met
 
**/
bool checkWin(int firstRound, Player *winner, int bet) {
    int playerTotal = 0, dealerTotal = 0;
    
    int i,j;
    
    for(i = 0; i < dealer.arrayPosition; i++) {
        char card = *dealer.cards[i].face;
        int value = dealer.cards[i].value;
        if(strncmp(&card, "A", 1) == 0) {
            int shouldBeAceTotal = 0;
            for(j = 0; j < dealer.arrayPosition; j++) {
                shouldBeAceTotal += dealer.cards[j].value;
                if(shouldBeAceTotal > 10) {
                    value = 1;
                } else {
                    value = 11;
                }
            }
        }
        
        dealerTotal += value;
    }
    
    for(i = 0; i < player.arrayPosition; i++) {
        char card = *player.cards[i].face;
        int value = player.cards[i].value;
        if(strncmp(&card, "A", 1) == 0) {
            int shouldBeAceTotal = 0;
            for(j = 0; j < player.arrayPosition; j++) {
                shouldBeAceTotal += player.cards[j].value;
                if(shouldBeAceTotal > 10) {
                    value = 1;
                } else {
                    value = 11;
                }
            }
        }
        
        playerTotal += value;
    }
    
    if(firstRound) {
        if(playerTotal == 21) {
            bet *= 3;
            betWinnings(&player, bet);
            
            memcpy (winner, &player, sizeof (player));
            return true;
        } else if (dealerTotal == 21) {
            memcpy (winner, &dealer, sizeof (dealer));
            return true;
        }
    } else {
        if(dealerTotal >= 17 && dealerTotal <= 21 && playerTotal <= 21) {
            if(playerTotal > dealerTotal) {
                bet *= 2;
                betWinnings(&player, bet);
            
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

bool checkLose(Player *winner, int bet) {
    int playerTotal = 0, dealerTotal = 0;
    
    int i;
    for(i = 0; i < dealer.arrayPosition; i++) {
        if(strncmp(dealer.cards[i].face, "A", 1) == 0) {
            dealerTotal += 1;
        }
        dealerTotal += dealer.cards[i].value;
    }
    
    for(i = 0; i < player.arrayPosition; i++) {
        if(strncmp(player.cards[i].face, "A", 1) == 0) {
            dealerTotal += 1;
        }
        playerTotal += player.cards[i].value;
    }
    
    if(playerTotal > 21) {
        memcpy (winner, &dealer, sizeof (dealer));
        return true;
    } else if(dealerTotal > 21) {
        bet *= 2;
        betWinnings(&player, bet);
        
        memcpy (winner, &player, sizeof (player));
        return true;
    } else {
        return false;
    }
}


void hit(Player *person) {
    person -> cards[person -> arrayPosition] = Deck[deckPosition];
    person -> arrayPosition++;
    deckPosition++;
    
    if(deckPosition == 52) {
        waitPrint("Please wait...");
        waitPrint("Shuffling Deck...");
        waitPrint("...");
        waitPrint("...");
        printf("\n");
        
        shuffleDeck(0);
        deckPosition = 0;
    }
}

void dealerPlay() {
    int dealerTotal = 0;
    
    int i,j;
    for(i = 0; i < dealer.arrayPosition; i++) {
        char card = *dealer.cards[i].face;
        int value = dealer.cards[i].value;
        
        if(strncmp(&card, "A", 1) == 0) {
            int shouldBeAceTotal = 0;
            for(j = 0; j < dealer.arrayPosition; j++) {
                shouldBeAceTotal += dealer.cards[j].value;
                if(shouldBeAceTotal > 10) {
                    value = 1;
                } else {
                    value = 11;
                }
            }
        }
        dealerTotal += value;
    }
    
    if(dealerTotal < 17) {
        waitPrint("Dealing Card To Dealer...");
        
        printf("It was a: %s\n\n", Deck[deckPosition].face);
        waitPrint("");
        
        hit(&dealer);
    }
}

void winnerScreen(Player *person) {
    if(strcmp(person -> name, player.name) == 0) {
        player.numberOfWins++;
    } else if(strcmp(person -> name, dealer.name) == 0) {
        dealer.numberOfWins++;
    }
    
    PrintGame(0, false, person -> name, true);
    printf("\n\n");
}

void tieScreen() {
    PrintGame(0, false, "TIE", false);
    printf("\n\n");
}

void waitPrint(char *text) {
    printf("%s\n",text);
    struct timespec sleepValue = {0};
    
    sleepValue.tv_nsec = INTERVAL_MS;
    nanosleep(&sleepValue, NULL);
}
