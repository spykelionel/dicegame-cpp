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

struct CurrentPlayer
{
    string name;
};

class Player
{
private:
    string name;
    vector<string> players;
    int points;

public:
    Player(string name) : name(name)
    {
        points = 100;
    }
    Player()
    {
        points = 100;
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

    void addPlayer(string name)
    {
        players.push_back(name);
    }

    vector<string> getPlayers()
    {
        return players;
    }

    int getPoints() const { return points; }
};

class Human : public Player
{
private:
    string name;

public:
    Human(string name) : name(name), Player(name) {}
};

class System : public Player
{
private:
    string name;

public:
    System(string name = "Computer") : name(name), Player(name) {}
};

class Die
{
private:
    int faceValue;

public:
    void roll()
    {
        faceValue = getRandomNumber();
    }
    int getFaceValue()
    {
        return faceValue;
    }
    int getRandomNumber()
    {
        mt19937 rng(time(0));
        uniform_int_distribution<int> distribution(1, 6);
        return distribution(rng);
    }
};

class DiceGame
{
private:
    Player player;
    Die die;

public:
    void init()
    {
        // default set player as human
        player = Human("Lionel");
    }
    void displayStats() {}
};

int main()
{
    Player player;
    cout << "Before placing a bet" << endl;
    cout << player.getPoints() << endl;
    player.bet(58);
    cout << "After placing a bet." << endl;
    cout << player.getPoints() << endl;
    return 0;
}
