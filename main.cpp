#include <iostream>
#include <cstdlib>
#include <ctime>
#include "game.h"

using namespace std;

// Taking valid numeric input
int getNumber()
{
    int number;

    while (!(cin >> number))
    {
        cin.clear();
        cin.ignore(1000, '\n');

        cout << "Please enter a number: ";
    }

    return number;
}


// Text of the game instructions (used by the console and the window)
string rulesText()
{
    return "1. Try to get a score as close to 21 as possible.\n"
        "2. Do not go above 21.\n"
        "3. Number cards have their face value.\n"
        "4. J, Q and K are worth 10 points.\n"
        "5. An Ace is worth 1 or 11 points.\n"
        "6. Choose Hit to take another card or Stand to stop.\n"
        "7. The dealer draws until reaching at least 17.\n"
        "8. The higher score wins. Equal scores mean a draw.\n";
}


// Displaying game instructions
void showRules()
{
    cout << "\nBLACKJACK RULES\n";

    cout << rulesText();
}


// Playing one round
int playRound(int balance, int& totalRounds, int& wins, int& losses)
{
    if (balance <= 0)
    {
        cout << "You have no chips left. You cannot place another bet.\n";
        return balance;
    }

    int bet;

    cout << "\nYour chip balance: " << balance << endl;
    cout << "Enter your bet (1 to " << balance << "): ";

    // Checking the bet
    while (true)
    {
        bet = getNumber();

        if (bet >= 1 && bet <= balance)
            break;

        cout << "Invalid bet. Enter an amount from 1 to "
            << balance << ": ";
    }


    // Deck arrays
    string ranks[52];
    string suits[52];
    int values[52];

    // Player and dealer card arrays
    int playerCards[52];
    int dealerCards[52];

    int playerCount = 0;
    int dealerCount = 0;

    int nextCard = 0;


    // Creating and shuffling deck
    createDeck(ranks, suits, values);
    shuffleDeck(ranks, suits, values);


    // Dealing two cards to player and dealer

    playerCards[playerCount] = nextCard;
    playerCount++;
    nextCard++;

    dealerCards[dealerCount] = nextCard;
    dealerCount++;
    nextCard++;

    playerCards[playerCount] = nextCard;
    playerCount++;
    nextCard++;

    dealerCards[dealerCount] = nextCard;
    dealerCount++;
    nextCard++;


    // Displaying initial cards
    cout << "\nYour cards:\n";

    showPlayerHand(playerCards, playerCount, ranks, suits);

    int playerScore = calculateScore(
        playerCards, playerCount, values, ranks
    );

    cout << "Your score: " << playerScore << endl;


    cout << "\nDealer's cards:\n";

    showDealerHand(
        dealerCards, dealerCount, ranks, suits, true
    );

    cout << "Dealer's visible score: "
        << values[dealerCards[0]] << endl;


    // Checking initial Blackjack
    bool playerBlackjack = (playerScore == 21 && playerCount == 2);

    if (playerBlackjack)
        cout << "Blackjack!\n";


    // PLAYER'S TURN

    while (playerScore < 21)
    {
        cout << "\n1. Hit\n";
        cout << "2. Stand\n";

        cout << "Choose an option: ";

        int action = getNumber();


        if (action == 1)
        {
            // Giving another card
            playerCards[playerCount] = nextCard;
            playerCount++;
            nextCard++;

            cout << "\nYou received: ";

            showCard(
                playerCards[playerCount - 1], ranks, suits
            );

            cout << endl;


            // Updating score
            playerScore = calculateScore(
                playerCards, playerCount, values, ranks
            );

            cout << "Your score: " << playerScore << endl;

            if (playerScore > 21)
                cout << "You went over 21. You busted!\n";
        }

        else if (action == 2)
        {
            break;
        }

        else
        {
            cout << "Invalid option. Choose 1 or 2.\n";
        }


        if (nextCard >= 52)
            break;
    }


    // DEALER'S TURN

    cout << "\nDealer reveals the cards:\n";

    showDealerHand(
        dealerCards, dealerCount, ranks, suits, false
    );


    int dealerScore = calculateScore(
        dealerCards, dealerCount, values, ranks
    );

    bool dealerBlackjack = (dealerScore == 21 && dealerCount == 2);

    cout << "Dealer's score: " << dealerScore << endl;


    // Dealer draws until reaching 17
    while (playerScore <= 21 && dealerScore < 17 && nextCard < 52)
    {
        dealerCards[dealerCount] = nextCard;
        dealerCount++;
        nextCard++;

        cout << "Dealer draws: ";

        showCard(
            dealerCards[dealerCount - 1], ranks, suits
        );

        cout << endl;


        dealerScore = calculateScore(
            dealerCards, dealerCount, values, ranks
        );

        cout << "Dealer's score: " << dealerScore << endl;
    }


    // FINAL RESULTS

    cout << "\nFINAL RESULTS\n";

    cout << "Your score: " << playerScore << endl;
    cout << "Dealer's score: " << dealerScore << endl;


    totalRounds++;

    if (playerScore > 21)
    {
        cout << "You lose this round.\n";

        balance = balance - bet;
        losses++;
    }

    else if (playerBlackjack && !dealerBlackjack)
    {
        cout << "You win with Blackjack!\n";

        balance = balance + bet;
        wins++;
    }

    else if (dealerBlackjack && !playerBlackjack)
    {
        cout << "Dealer has Blackjack. You lose this round.\n";

        balance = balance - bet;
        losses++;
    }

    else if (dealerScore > 21)
    {
        cout << "Dealer busted. You win!\n";

        balance = balance + bet;
        wins++;
    }

    else if (playerScore > dealerScore)
    {
        cout << "You win this round!\n";

        balance = balance + bet;
        wins++;
    }

    else if (playerScore == dealerScore)
    {
        cout << "It's a draw. Your bet is returned.\n";
    }

    else
    {
        cout << "Dealer wins this round.\n";

        balance = balance - bet;
        losses++;
    }


    cout << "Updated chip balance: " << balance << endl;

    return balance;
}


// Console version of the game menu
void runConsole(int& balance, int& highScore,
    int& totalRounds, int& wins, int& losses)
{
    int choice;


    // Main menu
    while (true)
    {
        cout << "\n==============================\n";
        cout << "       BLACKJACK GAME\n";
        cout << "==============================\n";

        cout << "Chip balance: " << balance << endl;

        cout << "1. Play Game\n";
        cout << "2. How to Play\n";
        cout << "3. View High Score\n";
        cout << "4. Game Statistics\n";
        cout << "5. Exit\n";

        cout << "Choose an option: ";

        choice = getNumber();


        if (choice == 1)
        {
            balance = playRound(
                balance, totalRounds, wins, losses
            );

            // Updating highest score
            if (balance > highScore)
                highScore = balance;

            // Saving data after every round
            saveData(balance, highScore);
        }

        else if (choice == 2)
        {
            showRules();
        }

        else if (choice == 3)
        {
            showHighScore(highScore);
        }

        else if (choice == 4)
        {
            showStatistics(totalRounds, wins, losses);
        }

        else if (choice == 5)
        {
            saveData(balance, highScore);

            cout << "\nThanks for playing Blackjack!\n";
            cout << "Final chip balance: " << balance << endl;

            break;
        }

        else
        {
            cout << "Invalid option. Please choose 1 to 5.\n";
        }
    }

}


// MAIN FUNCTION
int main()
{
    srand((unsigned int)time(0));

    int balance;
    int highScore;

    // Loading previous game data
    loadData(balance, highScore);

    if (balance > highScore)
        highScore = balance;


    // Game statistics
    int totalRounds = 0;
    int wins = 0;
    int losses = 0;


    runGui(balance, highScore, totalRounds, wins, losses);

    saveData(balance, highScore);

    return 0;

}