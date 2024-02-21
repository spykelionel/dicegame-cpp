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

    /**
     * Convert vector to array
     */
    template <typename T>
    static T **convertVectorToArray(const std::vector<T *> vec)
    {
        int size = vec.size();
        T **arr = new T *[size]; // Allocate memory for array of pointers

        for (int i = 0; i < size; ++i)
            arr[i] = vec[i];

        return arr;
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
    vector<Player *> players;
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

        string name = "";
        char option = ' ';

        // logic for playing game.
        bool quit = false;
        int choice = 0, turn = 0, i = 0;

        while (option != 'q')
        {

            displayOptions();
            cin >> option;
            switch (option)
            {
            case 'r':
                // register player
                cout << "Enter player's name: ";
                cin >> name;
                registerPlayer(name);
                break;
            case 's':
                // show statistics for the game.
                displayStats();
                break;
            case 'p':
                // play a game
                playGame();
                break;
            case 'q':
                option = 'q';
                break;
            default:
                cout << "Invalid Option.";
                break;
            }
        }
    void playGame()
    {
        bool quit = false;
        int choice = 0, turn = 0, i = 0;
        cout << "Playing the game......" << endl;
        while (!quit)
        {

            if (players.size() == 0)
            {
                cout << "Players must be at least 2." << endl;
                break;
            }
            else if (players.size() < 2 && players.size() >= 1)
            {
                cout << "You are now playing with the computer." << endl;
                players.push_back((new System()));
            }
            if (i % 2 == 0)
                turn++;
            cout << "Player " << i % 2 + 1 << " " << players.at(i % 2)->getName() << ".\nRolling a die.." << endl;
            cout << "Enter 1 to roll: ";
            cin >> choice;
            die->roll(players.at(i % 2), turn);
            if (choice == 0)
            {
                quit = true;
                Player **p = Util::convertVectorToArray(players);
                displayStats(p, players.size());
                delete[] p;
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
