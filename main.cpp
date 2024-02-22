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
        // players.assign({nullptr});
    }
    void init()
    {
        die = new Die();

        string name = "";
        char option = ' ';
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
    }

    void playGame()
    {
        bool quit = false;
        int choice = 0, turn = 0, i = 0;
        cout << "Playing the game......" << endl;
        cout << "Number of players: " << players.size() << endl;
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
            cout << "Player " << i + 1 << " " << players.at(i)->getName() << ".\nRolling a die.." << endl;
            if (players.at(i)->getName() == "Computer")
            {
                die->roll(players.at(i), turn);
            }
            else
            {
                cout << "Enter 1 to roll, or 0 to quit: ";
                cin >> choice;
            }

            if (choice == 0)
            {
                quit = true;
                Player **p = Util::convertVectorToArray(players);
                displayStats(p, players.size());
                delete[] p;
            }
            else
            {
                die->roll(players.at(i), turn);
                cout << "Index: " << i << endl;
                // if (i != players.size() - 1)
                // {
                //     i++;
                // }
                // else
                // {
                //     i = 0;
                // }
                i = i != players.size() - 1 ? i++ : 0;
            }
        }
    }

    void displayOptions()
    {
        cout << endl;
        cout << "r. Register a new player." << endl;
        cout << "s. Show dashboard." << endl;
        cout << "p. Play a game. If only one human is available. The game plays against the Computer." << endl;
        cout << "q. Quit." << endl;
        cout << endl;
    }

    void registerPlayer(string name)
    {
        // set all existing players scores to default score.
        players.push_back((new Human(name)));
    }

    void displayStats()
    {
        cout << endl;
        cout << "Showing statistics for the latest game." << endl;
        for (auto p : players)
        {
            cout << p->getName() << endl;
        }
        cout << endl;
    }

    void displayStats(Player *player[], int size)
    {
        int totalPoints = 0;
        cout << endl;
        for (int i = 0; i < size; i++)
        {
            cout << "Displaying points for: " << player[i]->getName() << endl;
            for (auto p : player[i]->getAccumumaltedPoints())
            {
                string suffix = Util::getOrdinalSuffix(p.turn);
                cout << p.turn << suffix << " Turn."
                     << " Total points: " << p.points << endl;
                totalPoints += p.points;
            }

            cout << "Total points: " << totalPoints << endl;
            // reset totalPoints.
            totalPoints = 0;
        }
        cout << endl;
        // delete player;
    }

    ~DiceGame()
    {
        delete player;
        delete die;
        for (auto p : players)
        {
            delete p;
        }
        // delete &players;
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
