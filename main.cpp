#include <iostream>
#include <string.h>

using namespace std;

// forward declaration
class Player;
class HumanPlayer;
class System;

class Player {
    private:
        string name;
    public:
    Player(string pName): name(pName) {}
    virtual void play() {
        cout <<"Player "<<name<<" is playing."<<endl;
    }
};

class HumanPlayer: public Player {
    private: string name;
    public:
        HumanPlayer(string name):name(name), Player(name){}

};

class System: public Player {
    private: string name;
    public:
        System(string name="Computer"): name(name), Player(name){}
};

int main()
{
    System sys;
    sys.play();
    return 0;
}
