#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <encrypt.h>
#include <dir.h>
#include <conio.h>
#include <hero.h>
#include <cstdlib>
#include <windows.h>
#include <time.h>
#include <random>

using namespace std;

class Account
{
    typedef unsigned int ui;
    #define loginFilePath "C:\\Dota Fight\\Account\\loginData.txt"
public:
    Account();
    ~Account();

    void start();
    void Lvl();
    void lvlPoints();
    void saveData();
    void addHeroes();
    void update();
    void fillAccHeroes(vector<Hero *> heroArray);
    vector<int> getID();
    void endInit();
    void settingsForm();
    void writeGameVersion(long ver, string type);
    bool readGameVersion(long ver, string type);
    vector<Hero *> getHeroes();
    string getNickname();

    struct statistic {
        int wins;
        int loses;
        int games;
        double winrate;
    };

    int getWinsCount();
    int getLosesCount();
    int getGamesCount();
    double getWinrate();

    void addWin();
    void addLose();

    void writeStats();
    void readStats();


private:
    string login;
    string *password;
    string getLogin;
    string getPassword;
    vector<int> IDs;
    vector<Hero*> heroes;

    statistic * state = new statistic;

    string nickname;

    int lvl;
    int pLvl;

    void printLoginForm();
    void printGameMenuForm();
    void signIn();
    void signUp();
    void succedLogin();
    void fillProfile();
    void clearAccount();
    void changeNickname();
    void changePassword();
    string getLastSessionLogin();
    void upLvl();

    void addGame();
    void changeWinrate();

    // List of levels max points
     enum {
         LVL_TWO = 300,
         LVL_THREE = 500,
         LVL_FOUR = 1000,
         LVL_FIVE = 1700,
         LVL_SIX = 2500,
         LVL_SEVEN = 4000,
         LVL_EIGHT = 6000,
         LVL_NINE = 10000,
         LVL_TEN = 20000
     };
};

#endif // ACCOUNT_H
