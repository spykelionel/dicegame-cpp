#include <iostream>
#include <string.h>
#include <vector>
#include <random>
#include <ctime>

using namespace std;

// forward declaration
class Player;
class Human;
class System;
class DiceGame;
class Die;
class Util;

struct CurrentPlayer
{
    string name;
};

struct Turn
{
    int turn;
    int points;
};
class Player
{
private:
    string name;
    int points;
    vector<Turn> accumulatedPoints;

public:
    Player(string name) : name(name)
    {
        points = 100;
    }
    Player()
    {
        points = 100;
        // give it an
        accumulatedPoints.assign({});
    }
    virtual void play()
    {
        cout << "Player " << name << " is playing." << endl;
    }
    void bet(int x)
    {
        if (x <= points)
        {
            cout << "Player placed a bet of " << x << endl;
            points -= x;
        }
        else
        {
            cout << "Not enough points to place bet" << endl;
        }
    }

    int getPoints() const { return points; }
    void addPoints(int point)
    {
        points += point;
    }
    string getName() { return name; }
    void setTurn(Turn turn)
    {
        accumulatedPoints.push_back(turn);
    }
    vector<Turn> getAccumumaltedPoints()
    {
        return accumulatedPoints;
    }
};

class Human : public Player
{
private:
    string name;

public:
    Human(string name) : name(name), Player(name) {}
    Human() {}
    string getName() { return name; }
};

class System : public Player
{
private:
    string name;

public:
    System(string name = "Computer") : name(name), Player(name) {}
};

class Util
{
public:
    // Function to determine the suffix for ordinal numbers
    static string getOrdinalSuffix(int number)
    {
        if (number >= 11 && number <= 13)
        {
            return "th";
        }
        else
        {
            switch (number % 10)
            {
            case 1:
                return "st";
            case 2:
                return "nd";
            case 3:
                return "rd";
            default:
                return "th";
            }
        }
    }
};

class Die
{
private:
    int faceValue;

public:
    Die() {}
    void roll(Player *player, int turnNumber)
    {
        try
        {
            Turn turn;
            int value = 0;
            // role a die 3 times.
            for (int i = 1; i <= 3; i++)
            {
                string suffix = Util::getOrdinalSuffix(i);
                int fv = rand() % 6 + 1;
                value += fv;
                cout << "Rolling " << i << suffix << " Time."
                     << " Face Value: " << fv << endl;
            }
            turn.points = value;
            turn.turn = turnNumber;
            player->setTurn(turn);
        }
        catch (const exception &e)
        {
            cerr << e.what() << '\n';
        }
    }
    int getFaceValue()
    {
        return this->faceValue;
    }
};

class DiceGame
{
private:
    Player *player;
    Human human;
    System sys;
    Die *die;

public:
    // make sure player is not pointing to any memory location.
    // It points to nothing.
    DiceGame() : player(nullptr), die(nullptr)
    {
    }
    void init()
    {
        /**
         * 1. Get player name.
         * 2. Ask player to roll a die.
         * 3. Add the points to player's points
         *
         * Part 2:
         * 1. Ask player to roll a die.
         * 2. Ask system to roll a die too.
         * 3. Add player's points to the one who won.
         */

        // default set player as human
        // player = new Human("Lionel");
        // sys = new System();
        player = new Human("Lionel");

        die = new Die();

        bool quit = false;
        int choice = 0, turn = 0, i = 0;
        while (!quit)
        {
            turn++;
            cout << "Player " << i % 2 + 1 << " roll a dice. \nRolling a die.." << endl;
            die->roll();
            const int faceValue = die->getFaceValue();
            die->roll();
            const int faceValue2 = die->getFaceValue();
            die->roll();
            const int faceValue3 = die->getFaceValue();
            player->addPoints(faceValue);
            player->setPoints(player->getName(), turn, (faceValue + faceValue2 + faceValue3));
            cout << "Rolled a die with value: " << faceValue << " " << faceValue2 << " " << faceValue3 << endl;
            cout << "Roll again? 0. NO, 1. YES: ";
            cin >> choice;
            if (choice == 0)
            {
                quit = true;
                // cout << "Points" << player->getPoints() << endl;
                displayStats(player);
            }
            i++;
        }
    }
    void displayStats(Player *player)
    {
        for (auto p : player->getPlayers())
        {
            cout << "Turn: " << p.turn << "Name: " << p.name << " Points: " << p.points << endl;
        }
    }

    ~DiceGame()
    {
        delete player;
        delete die;
        // delete human;
        // delete sys;
    }
};

int main()
{
    srand((unsigned)time(NULL));
    DiceGame game;
    game.init();

    return 0;
}
