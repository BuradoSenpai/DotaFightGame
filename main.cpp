#include <iostream>
#include <account.h>
#include <conio.h>
#include <game.h>


using namespace std;

int main()
{
    long gameVersion = 0.1l;
    string gameType = "Alpha";

    Account * acc = new Account();
    acc->start();
    acc->endInit();
    Game * game = new Game(acc);

    vector<Hero*> heroes;
    heroes.push_back(new Alchemist("C:\\Dota Fight\\Heroes\\Alchemist.ini",1));
    heroes.push_back(new Lifestealer("C:\\Dota Fight\\Heroes\\Lifestealer.ini",2));
    heroes.push_back(new FacelessVoid("C:\\Dota Fight\\Heroes\\Faceless Void.ini",3));
    heroes.push_back(new Juggernaut("C:\\Dota Fight\\Heroes\\Juggernaut.ini",4));

    acc->fillAccHeroes(heroes);

    game->getHeroList(acc->getHeroes());
    game->getAllHeroList(heroes);
    game->start();

    return 0;
}
