
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


// Displaying game instructions
void showRules()
{
    cout << "\nBLACKJACK RULES\n";

    cout << "1. Try to get a score as close to 21 as possible.\n";
    cout << "2. Do not go above 21.\n";
    cout << "3. Number cards have their face value.\n";
    cout << "4. J, Q and K are worth 10 points.\n";
    cout << "5. An Ace is worth 1 or 11 points.\n";
    cout << "6. Choose Hit to take another card or Stand to stop.\n";
    cout << "7. The dealer draws until reaching at least 17.\n";
    cout << "8. The higher score wins. Equal scores mean a draw.\n";
}


// Playing one round
int playRound(int balance)
{
    return balance;
}



// MAIN FUNCTION
int main()
{
    srand((unsigned int)time(0));

    int balance = 1000;
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
        cout << "3. Exit\n";

        cout << "Choose an option: ";

        choice = getNumber();


        if (choice == 1)
        {
            balance = playRound(balance);
        }

        else if (choice == 2)
        {
            showRules();
        }

        else if (choice == 3)
        {
            cout << "\nThanks for playing Blackjack!\n";

            cout << "Final chip balance: " << balance << endl;

            break;
        }

        else
        {
            cout << "Invalid option. Please choose 1, 2 or 3.\n";
        }
    }

    return 0;
}
