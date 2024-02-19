#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

// forward declaration
class Player;
class Human;
class System;

struct CurrentPlayer
{
    string name;
};

class Player
{
private:
    string name;
    vector<string> players;

public:
    Player(string name) : name(name) {}
    Player() {}
    virtual void play()
    {
        cout << "Player " << name << " is playing." << endl;
    }
    void bet(int x)
    {
    }

    void addPlayer(string name)
    {
        players.push_back(name);
    }

    vector<string> getPlayers()
    {
        return players;
    }
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
    void roll() {}
    int getFaceValue()
    {
        return faceValue;
    }
};

int main()
{
    System sys;
    Player player;
    sys.play();
    player.addPlayer("Lionel");
    player.addPlayer("Spyke");

    for (int i = 0; i < player.getPlayers().size(); i++)
    {
        cout << player.getPlayers().at(i) << endl;
    }
    return 0;
}
