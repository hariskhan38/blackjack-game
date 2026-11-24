#include <SFML/Graphics.hpp>
#include <string>
#include "game.h"

using namespace std;

sf::RenderWindow window;
sf::Font font;
sf::Color gold(212, 175, 55);
sf::Color dark(0, 100, 55);
sf::Vector2f mouse;
bool click = false;

// Deck and hands (the functions from game.cpp fill these)
string ranks[52], suits[52];
int values[52];
int playerCards[52], dealerCards[52];
int playerCount, dealerCount, nextCard;


// Drawing a rectangle
void box(float x, float y, float w, float h, sf::Color fill)
{
    sf::RectangleShape shape(sf::Vector2f(w, h));
    shape.setPosition(x, y);
    shape.setFillColor(fill);
    shape.setOutlineColor(gold);
    shape.setOutlineThickness(2);
    window.draw(shape);
}

// Drawing text (x is the center if center is true)
void text(sf::String words, int size, sf::Color color, float x, float y, bool center)
{
    sf::Text t(words, font, size);
    t.setFillColor(color);
    if (center)
        t.setOrigin(t.getLocalBounds().left + t.getLocalBounds().width / 2, 0);
    t.setPosition(x, y);
    window.draw(t);
}

// Drawing a button, returns true when it is clicked
bool button(string label, float x, float y, float w, float h)
{
    box(x, y, w, h, dark);
    text(label, 18, sf::Color::White, x + w / 2, y + h / 2 - 12, true);

    return click && mouse.x > x && mouse.x < x + w && mouse.y > y && mouse.y < y + h;
}

// Drawing one hand: a panel with its cards
void drawHand(string name, int cards[], int count, float y, bool hideSecond)
{
    box(40, y, 820, 150, dark);
    text(name, 20, gold, 60, y + 8, false);

    for (int i = 0; i < count; i++)
    {
        float x = 60 + i * 80;
        int c = cards[i];
        sf::Color color = sf::Color::Black;
        sf::String symbol = L"\x2660";

        if (suits[c] == "Hearts" || suits[c] == "Diamonds")
            color = sf::Color(220, 50, 30);
        if (suits[c] == "Hearts")
            symbol = L"\x2665";
        if (suits[c] == "Diamonds")
            symbol = L"\x2666";
        if (suits[c] == "Clubs")
            symbol = L"\x2663";

        if (hideSecond && i == 1)
        {
            box(x, y + 38, 75, 105, dark);
            text("21", 30, gold, x + 37, y + 70, true);
        }
        else
        {
            box(x, y + 38, 75, 105, sf::Color(245, 245, 240));
            text(ranks[c], 20, color, x + 8, y + 42, false);
            text(symbol, 40, color, x + 37, y + 73, true);
        }
    }
}


void runGui(int& balance, int& highScore, int& totalRounds, int& wins, int& losses)
{
    // Big window (85% of the screen height), the game is drawn 900 x 600 and scaled
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    unsigned int height = desktop.height * 85 / 100;

    window.create(sf::VideoMode(height * 3 / 2, height), "Blackjack",
        sf::Style::Titlebar | sf::Style::Close);
    window.setView(sf::View(sf::FloatRect(0, 0, 900, 600)));
    window.setPosition(sf::Vector2i((int)(desktop.width - window.getSize().x) / 2, 10));
    window.setFramerateLimit(60);

    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf"))
        return;

    // 0 = welcome, 1 = bet, 2 = table, 3 = result,
    // 4 = high score, 5 = statistics, 6 = how to play
    int screen = 0;
    int bet = 100;
    int result = 0;
    int playerScore = 0, dealerScore = 0;
    bool blackjack = false;

    string titles[7] = {
        "WELCOME TO BLACKJACK", "PLACE YOUR BET", "BLACKJACK TABLE", "ROUND RESULT",
        "HIGH SCORE", "GAME STATISTICS", "HOW TO PLAY"
    };

    while (window.isOpen())
    {
        click = false;
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                click = true;
        }
        mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        window.clear(sf::Color(0, 150, 80));
        box(15, 15, 870, 570, sf::Color(0, 150, 80));
        text(titles[screen], 34, gold, 450, 25, true);
        box(100, 78, 700, 1, gold);


        // Welcome screen (menu)
        if (screen == 0)
        {
            box(300, 95, 300, 455, dark);
            text("21", 56, gold, 450, 100, true);
            text("THE CLASSIC CARD GAME", 16, sf::Color::White, 450, 172, true);
            text("SAVED BALANCE", 14, gold, 450, 205, true);
            text(to_string(balance) + " CHIPS", 26, sf::Color::White, 450, 222, true);

            if (button("CONTINUE GAME", 320, 275, 260, 36))
            {
                if (balance <= 0)
                    balance = 1000;
                screen = 1;
            }
            if (button("NEW GAME", 320, 319, 260, 36))
            {
                balance = 1000;
                screen = 1;
            }
            if (button("HOW TO PLAY", 320, 363, 260, 36))
                screen = 6;
            if (button("HIGH SCORE", 320, 407, 260, 36))
                screen = 4;
            if (button("STATISTICS", 320, 451, 260, 36))
                screen = 5;
            if (button("EXIT", 320, 495, 260, 36))
                window.close();
        }

        // Bet screen
        else if (screen == 1)
        {
            if (bet > balance)
                bet = balance;

            box(250, 130, 400, 90, dark);
            text("AVAILABLE CHIPS", 18, gold, 450, 143, true);
            text(to_string(balance), 32, sf::Color::White, 450, 172, true);
            text("SELECT YOUR BET", 20, gold, 450, 265, true);
            text(to_string(bet) + " CHIPS", 30, sf::Color::White, 450, 315, true);

            if (button("-", 250, 310, 80, 50) && bet > 50)
                bet = bet - 50;
            if (button("+", 570, 310, 80, 50) && bet + 50 <= balance)
                bet = bet + 50;
            if (button("BACK TO MENU", 325, 480, 250, 50))
                screen = 0;

            if (button("DEAL CARDS", 275, 400, 350, 55))
            {
                startRound(ranks, suits, values, playerCards, playerCount,
                    dealerCards, dealerCount, nextCard);

                playerScore = calculateScore(playerCards, playerCount, values, ranks);
                dealerScore = calculateScore(dealerCards, dealerCount, values, ranks);
                blackjack = (playerScore == 21);
                screen = 2;
            }
        }

        // Table screen
        else if (screen == 2)
        {
            drawHand("DEALER", dealerCards, dealerCount, 150, true);
            drawHand("PLAYER", playerCards, playerCount, 310, false);

            box(620, 350, 220, 95, dark);
            text("SCORE: " + to_string(playerScore), 22, sf::Color::White, 635, 355, false);
            text("BALANCE: " + to_string(balance), 16, gold, 635, 390, false);
            text("BET: " + to_string(bet), 16, gold, 635, 415, false);

            bool done = blackjack;

            if (!done && button("HIT", 560, 480, 140, 50))
            {
                dealCard(playerCards, playerCount, nextCard);
                playerScore = calculateScore(playerCards, playerCount, values, ranks);
                done = (playerScore >= 21);
            }
            if (!done && button("STAND", 720, 480, 140, 50))
                done = true;

            if (done)
            {
                while (dealerMustDraw(dealerScore, playerScore, nextCard))
                {
                    dealCard(dealerCards, dealerCount, nextCard);
                    dealerScore = calculateScore(dealerCards, dealerCount, values, ranks);
                }

                bool dealerBlackjack = (dealerScore == 21 && dealerCount == 2);

                result = getResult(playerScore, dealerScore, blackjack, dealerBlackjack);
                updateResult(result, bet, balance, totalRounds, wins, losses);

                if (balance > highScore)
                    highScore = balance;
                saveData(balance, highScore);

                screen = 3;
            }
        }

        // Result screen
        else if (screen == 3)
        {
            if (result == 1)
                text("YOU WIN", 36, sf::Color(120, 255, 120), 450, 95, true);
            else if (result == -1)
                text("YOU LOSE", 36, sf::Color(230, 90, 60), 450, 95, true);
            else
                text("DRAW", 36, gold, 450, 95, true);

            drawHand("DEALER", dealerCards, dealerCount, 150, false);
            drawHand("PLAYER", playerCards, playerCount, 310, false);

            text("SCORE: " + to_string(dealerScore), 22, sf::Color::White, 700, 215, false);
            text("SCORE: " + to_string(playerScore), 22, sf::Color::White, 700, 375, false);
            text("BALANCE: " + to_string(balance), 24, gold, 450, 480, true);

            if (button("PLAY AGAIN", 250, 525, 190, 50))
                screen = (balance > 0) ? 1 : 0;
            if (button("MAIN MENU", 460, 525, 190, 50))
                screen = 0;
        }

        // High score, statistics and rules screens (text comes from game.cpp / main.cpp)
        else
        {
            string info = rulesText();

            if (screen == 4)
                info = highScoreText(highScore);
            if (screen == 5)
                info = statisticsText(totalRounds, wins, losses);

            box(150, 110, 600, 340, dark);
            text(info, (screen == 6) ? 20 : 30, sf::Color::White, 180, 135, false);

            if (button("BACK TO MENU", 325, 490, 250, 50))
                screen = 0;
        }

        window.display();
    }
}