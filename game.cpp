#include <iostream>
#include <cstdlib>
#include <fstream>
#include "game.h"

using namespace std;

// Creating 52 cards
void createDeck(string ranks[], string suits[], int values[])
{
    string rankNames[13] = {
        "A", "2", "3", "4", "5", "6", "7",
        "8", "9", "10", "J", "Q", "K"
    };

    string suitNames[4] = {
        "Hearts", "Diamonds", "Clubs", "Spades"
    };

    int index = 0;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 13; j++)
        {
            ranks[index] = rankNames[j];
            suits[index] = suitNames[i];

            if (j == 0)
                values[index] = 11;
            else if (j >= 10)
                values[index] = 10;
            else
                values[index] = j + 1;

            index++;
        }
    }
}


// Shuffling the cards randomly
void shuffleDeck(string ranks[], string suits[], int values[])
{
    for (int i = 51; i > 0; i--)
    {
        int randomIndex = rand() % (i + 1);

        string tempRank = ranks[i];
        ranks[i] = ranks[randomIndex];
        ranks[randomIndex] = tempRank;

        string tempSuit = suits[i];
        suits[i] = suits[randomIndex];
        suits[randomIndex] = tempSuit;

        int tempValue = values[i];
        values[i] = values[randomIndex];
        values[randomIndex] = tempValue;
    }
}


// Displaying one card
void showCard(int cardNumber, string ranks[], string suits[])
{
    cout << ranks[cardNumber] << " of " << suits[cardNumber];
}


// Displaying player's cards
void showPlayerHand(int hand[], int handCount, string ranks[], string suits[])
{
    for (int i = 0; i < handCount; i++)
    {
        showCard(hand[i], ranks, suits);
        cout << endl;
    }
}


// Displaying dealer's cards
void showDealerHand(int hand[], int handCount,
    string ranks[], string suits[], bool hideSecondCard)
{
    for (int i = 0; i < handCount; i++)
    {
        if (hideSecondCard && i == 1)
            cout << "Hidden card";
        else
            showCard(hand[i], ranks, suits);

        cout << endl;
    }
}


// Calculating the total score
int calculateScore(int hand[], int handCount, int values[], string ranks[])
{
    int total = 0;
    int aceCount = 0;

    for (int i = 0; i < handCount; i++)
    {
        total = total + values[hand[i]];

        if (ranks[hand[i]] == "A")
            aceCount++;
    }

    // Changing Ace from 11 to 1 when necessary
    while (total > 21 && aceCount > 0)
    {
        total = total - 10;
        aceCount--;
    }

    return total;
}


// Loading saved balance and high score
void loadData(int& balance, int& highScore)
{
    balance = 1000;
    highScore = 1000;

    ifstream file("playerData.txt");

    if (file.is_open())
    {
        file >> balance;
        file >> highScore;

        file.close();
    }
}


// Saving balance and high score
void saveData(int balance, int highScore)
{
    ofstream file("playerData.txt");

    if (file.is_open())
    {
        file << balance << endl;
        file << highScore << endl;

        file.close();
    }
}


// Displaying highest score
string highScoreText(int highScore)
{
    return "Highest chip balance: " + to_string(highScore);
}

void showHighScore(int highScore)
{
    cout << "\n===== HIGH SCORE =====\n";

    cout << highScoreText(highScore) << endl;
}


// Displaying game statistics
string statisticsText(int totalRounds, int wins, int losses)
{
    return "Total rounds: " + to_string(totalRounds) + "\n"
        + "Winning rounds: " + to_string(wins) + "\n"
        + "Losing rounds: " + to_string(losses);
}

void showStatistics(int totalRounds, int wins, int losses)
{
    cout << "\n===== GAME STATISTICS =====\n";

    cout << statisticsText(totalRounds, wins, losses) << endl;
}


// Giving the next card of the deck to a hand
void dealCard(int hand[], int& handCount, int& nextCard)
{
    hand[handCount] = nextCard;
    handCount++;
    nextCard++;
}


// Starting a round: new shuffled deck and two cards for each side
void startRound(string ranks[], string suits[], int values[],
    int playerCards[], int& playerCount,
    int dealerCards[], int& dealerCount, int& nextCard)
{
    playerCount = 0;
    dealerCount = 0;
    nextCard = 0;

    createDeck(ranks, suits, values);
    shuffleDeck(ranks, suits, values);

    dealCard(playerCards, playerCount, nextCard);
    dealCard(dealerCards, dealerCount, nextCard);
    dealCard(playerCards, playerCount, nextCard);
    dealCard(dealerCards, dealerCount, nextCard);
}


// Dealer keeps drawing until reaching 17
bool dealerMustDraw(int dealerScore, int playerScore, int nextCard)
{
    return (playerScore <= 21 && dealerScore < 17 && nextCard < 52);
}


// Deciding the result: 1 = player wins, 0 = draw, -1 = player loses
int getResult(int playerScore, int dealerScore,
    bool playerBlackjack, bool dealerBlackjack)
{
    if (playerScore > 21)
        return -1;

    if (playerBlackjack && !dealerBlackjack)
        return 1;

    if (dealerBlackjack && !playerBlackjack)
        return -1;

    if (dealerScore > 21)
        return 1;

    if (playerScore > dealerScore)
        return 1;

    if (playerScore == dealerScore)
        return 0;

    return -1;
}


// Updating balance and statistics after a round
void updateResult(int result, int bet, int& balance,
    int& totalRounds, int& wins, int& losses)
{
    totalRounds++;

    if (result == 1)
    {
        balance = balance + bet;
        wins++;
    }
    else if (result == -1)
    {
        balance = balance - bet;
        losses++;
    }
}