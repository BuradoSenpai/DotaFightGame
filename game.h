#ifndef GAME_H
#define GAME_H

#include <account.h>
#include <conio.h>
#include <alchemist.h>
#include <lifestealer.h>
#include <facelessvoid.h>
#include <juggernaut.h>

class Game {

public:
    Game(Account *acc);
    Game() {}
    virtual ~Game();

    void start();
    void printMenu();

    void getHeroList(vector<Hero*> list);
    void getAllHeroList(vector<Hero*> list);

    void startDefaultGame(Hero *player, Hero *enemy);

    void showHeroesAcc() {
        for (int i(0); i < this->heroes.size(); i++)
        {
            this->heroes[i]->init();
            cout << this->heroes[i]->Name() << endl;
        }
    }

private:
    Account *account;
    vector<Hero*> heroes;
    vector<Hero *> allHeroes;

    void playMenu();
    void defaultGameModeMenu();
    void selectHero();
    Hero *getRandomHero(vector<Hero *> list);

    void settingsMenu();
    void profileMenu();
};

#endif // GAME_H
