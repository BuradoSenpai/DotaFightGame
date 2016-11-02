#ifndef LIFESTEALER_H
#define LIFESTEALER_H

#include <hero.h>

class Lifestealer : public Hero
{
public:
    Lifestealer(string path, int id) : Hero(path,id)
    {

        this->rageCd = 0;
        this->rageCdDefault = 16;
        this->rageDuration = 5;
        this->rageCounter = 0;
        this->rageExtraAS = 1;
        this->rageManacost = 75;
        this->isActiveRage = false;

        this->lifestealPercent = 35;
        this->isGottenLifesteal = false;

        this->openWoundsCd = 0;
        this->openWoundsCdDefault = 16;
        this->openWoundsArmorReduction = 2;
        this->openWoundsExtraLifesteal = 50;
        this->openWoundsDuration = 6;
        this->openWoundsCounter = 0;
        this->openWoundsManacost = 85;
        this->isActiveOpenWounds = false;
        this->isGottenExtraLifesteal = false;

        this->MIcd = 0;
        this->monsterInstinctsCdDefault = 30;
        this->monsterInstinctsDuration = 10;
        this->MImanacost = 120;
        this->MIdamage = 300;
        this->MIaddDamageAmount = 3;
        this->monsterInstinctsCounter = 0;
        this->isActiveMonsterInstincts = false;

        this->ASbuffCount = 0;
    }

    void drawMenu() override;
    void skillSelectionMenu(Hero *hero) override;
    void refreshCds() override;
    void updateOwnChars() override;
    void updateCountdowns() override;

    void rage();
    void updateRage();

    void updatePassiveLifesteal();

    void openWounds(Hero *hero);
    void updateOpenWounds();

    void monsterInstincts(Hero *hero);
    void updateMonsterInstincts();



private:

    //active
    int rageCd;
    int rageCdDefault;
    int rageDuration;
    int rageCounter;
    int rageExtraAS;
    int rageManacost;
    bool isActiveRage;

    //passive
    int lifestealPercent;
    bool isGottenLifesteal;

    //active
    int openWoundsCd;
    int openWoundsCdDefault;
    int openWoundsExtraLifesteal;
    int openWoundsArmorReduction;
    int openWoundsDuration;
    int openWoundsCounter;
    int openWoundsManacost;
    bool isActiveOpenWounds;
    bool isGottenExtraLifesteal;

    //active
    int MIcd;
    int monsterInstinctsCdDefault;
    int monsterInstinctsDuration;
    int MImanacost;
    int MIdamage;
    int MIaddDamageAmount;
    int monsterInstinctsCounter;
    bool isActiveMonsterInstincts;

    //other
    int ASbuffCount;
    int LSbuffCount;

    int monsterInstinctsAScount;
    int presentDamage;
    int temp_damage_ulti;
};

#endif // LIFESTEALER_H
