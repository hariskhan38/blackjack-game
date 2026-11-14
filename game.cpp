
#include <iostream>
#include <cstdlib>
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

