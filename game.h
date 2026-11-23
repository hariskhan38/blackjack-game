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

void loadData(int& balance, int& highScore);

void saveData(int balance, int highScore);

void showHighScore(int highScore);

void showStatistics(int totalRounds, int wins, int losses);

void dealCard(int hand[], int& handCount, int& nextCard);

void startRound(string ranks[], string suits[], int values[],
    int playerCards[], int& playerCount,
    int dealerCards[], int& dealerCount, int& nextCard);

bool dealerMustDraw(int dealerScore, int playerScore, int nextCard);

int getResult(int playerScore, int dealerScore,
    bool playerBlackjack, bool dealerBlackjack);

void updateResult(int result, int bet, int& balance,
    int& totalRounds, int& wins, int& losses);

string highScoreText(int highScore);

string statisticsText(int totalRounds, int wins, int losses);

string rulesText();   // written in main.cpp

// Written in gui.cpp (SFML window)
void runGui(int& balance, int& highScore,
    int& totalRounds, int& wins, int& losses);

#endif