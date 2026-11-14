
#ifndef GAME_H
#define GAME_H

#include <string>
using namespace std;

// Function declarations
void createDeck(string ranks[], string suits[], int values[]);
void shuffleDeck(string ranks[], string suits[], int values[]);

void showCard(int cardNumber, string ranks[], string suits[]);

void showPlayerHand(int hand[], int handCount, string ranks[], string suits[]);

void showDealerHand(int hand[], int handCount, string ranks[], string suits[], bool hideSecondCard);

int calculateScore(int hand[], int handCount, int values[], string ranks[]);

#endif
