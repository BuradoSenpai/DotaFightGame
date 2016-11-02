#ifndef JUGGERNAUT_H
#define JUGGERNAUT_H

#include <hero.h>

class Juggernaut : public Hero
{
public:
    Juggernaut(string path, int id) : Hero(path, id)
    {
        this->bladeFuryCd = 0;
        this->bladeFuryCdDefault = 20;
        this->bladeFuryDamage = 100;
        this->bladeFuryDuration = 5;
        this->bladeFuryCounter = 0;
        this->bladeFuryManacost = 110;
        this->isActiveBladeFury = false;

        this->healingWardCd = 0;
        this->healingWardCdDefault = 40;
        this->healingWardDuration = 10;
        this->healingWardCounter = 0;
        this->healingWardHeal = 0;
        this->healingWardManacost = 140;
        this->isActiveHealingWard = false;

        this->bladeDanceCriticalChance = 25;
        this->bladeDanceCriticalHit = 2;
        this->isActiveBladeDance = false;

        this->omnislashCd = 0;
        this->omnislashCdDefault = 60;
        this->omnislashDuration = 4;
        this->omnislashDamage = 70;
        this->omnislashManacost = 200;
    }

    void drawMenu() override;
    void skillSelectionMenu(Hero *hero) override;
    void refreshCds() override;
    void updateOwnChars() override;
    void updateCountdowns() override;

    void bladeFury(Hero *hero);
    void updateBladeFury();

    void healingWard();
    void updateHealingWard();

    void updateBladeDance();

    void omnislash(Hero *hero);

private:
    //active
    int bladeFuryCd;
    int bladeFuryCdDefault;
    int bladeFuryDuration;
    int bladeFuryCounter;
    int bladeFuryDamage;
    int bladeFuryManacost;
    bool isActiveBladeFury;

    //active
    int healingWardCd;
    int healingWardCdDefault;
    int healingWardDuration;
    int healingWardCounter;
    int healingWardManacost;
    int healingWardHeal;
    bool isActiveHealingWard;

    //passive
    int bladeDanceCriticalChance;
    int bladeDanceCriticalHit;
    bool isActiveBladeDance;

    //active
    int omnislashCd;
    int omnislashCdDefault;
    int omnislashDamage;
    int omnislashManacost;
    int omnislashDuration;

    //other
};

#endif // JUGGERNAUT_H
