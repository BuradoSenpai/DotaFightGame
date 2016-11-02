#ifndef FACELESSVOID_H
#define FACELESSVOID_H

#include <hero.h>

class FacelessVoid : public Hero
{
public:
    FacelessVoid(string path, int id) : Hero(path,id)
    {

        this->timeWalkPassiveGetInfoHpCounter = 0;
        this->timeWalkPassiveGetInfoHp = 0;
        this->timeWalkCd = 0;
        this->timeWalkCdDefault = 10;
        this->timeWalkManacost = 50;
        this->isCheckedInfoTimeWalk = false;

        this->freezeCd = 0;
        this->freezeCdDefault = 16;
        this->freezeDPSreduction = 30;
        this->freezeDPSreductionDuration = 7;
        this->freezeManacost = 112;
        this->freezeDamage = 0;

        this->isActiveTimeLock = false;
        this->timeLockBushChance = 20;

        this->chronosphereCd = 0;
        this->chronosphereCdDafault = 30;
        this->chronosphereCounter = 0;
        this->chronosphereDuration = 4;
        this->chronosphereManacost = 200;
        this->isActiveChronosphere = false;
    }

    void drawMenu() override;
    void skillSelectionMenu(Hero *hero) override;
    void refreshCds() override;
    void updateOwnChars() override;
    void updateCountdowns() override;
    void updateFirst() override;

    void timeWalk();
    void updateTimeWalkHP();
    void timeDilation(Hero *hero);
    void updateTimeLockPassive();
    void chronosphere(Hero *hero);
    void updateChronosphere();

private:

    //active
    int timeWalkPassiveGetInfoHp;
    int timeWalkPassiveGetInfoHpCounter;
    int timeWalkCd;
    int timeWalkCdDefault;
    int timeWalkManacost;
    bool isCheckedInfoTimeWalk;

    //active
    int freezeDPSreduction;
    int freezeDPSreductionDuration;
    int freezeCd;
    int freezeCdDefault;
    int freezeManacost;
    int freezeDamage;

    //passive
    int timeLockBushChance;
    bool isActiveTimeLock;

    //active
    int chronosphereCd;
    int chronosphereCdDafault;
    int chronosphereManacost;
    int chronosphereDuration;
    int chronosphereCounter;
    bool isActiveChronosphere;
};

#endif // FACELESSVOID_H
