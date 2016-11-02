#ifndef ALCHEMIST_H
#define ALCHEMIST_H

#include <hero.h>

class Alchemist : public Hero
{
public:
    Alchemist(string path, int id) : Hero(path, id) {

        this->acidSprayCd = 0;
        this->acidSprayCdDefault = 22;
        this->acidSprayDuration = 16;
        this->acidSprayDamage = 15;
        this->acidSpayArmorReduction = 3;
        this->acidSprayManacost = 130;

        this->unstableConcoctionCd = 0;
        this->unstableConcoctionCdDefault = 16;
        this->unstableConcoctionDamage = 290;
        this->unstableConcoctionDuration = 5;
        this->unstableConcoctionManacost = 120;
        this->unstableConcoctionCounter = 0;
        this->isActivedUnstableConcontion = false;

        this->greevilsPowerAmount = 5;
        this->greevilsPowerGetDPS = 5;
        this->greevilsPowerHeal = 10;

        this->chemicalRageCd = 0;
        this->chemicalRageCdDefault = 45;
        this->chemicalRageDuration = 25;
        this->chemicalRageManacost = 100;
        this->chemicalRageHpRegen = 75;
        this->chemicalRageMpRegen = 8;
        this->chemicalRageCounter = 0;
        this->isActiveChemicalRage = false;
    }

    void drawMenu() override;
    void skillSelectionMenu(Hero *hero) override;
    void refreshCds() override;

    void acidSpray(Hero *hero);

    void unstableConcoction(Hero *hero);
    void useUnstableConcoction();
    void throwUnstableConcoction(Hero *hero);
    void makeUnstableConcoction();
    void updateUnstableConcontion();

    void updateGreevilsPower();

    void chemicalRage();
    void updateChemicalRage();

    //void update(bool &step) override;
    void updateOwnChars() override;
    void updateCountdowns() override;

private:

    //other
    int extraDamage;

    //active
    int acidSprayCd;
    int acidSprayCdDefault;
    int acidSprayDuration;
    int acidSprayDamage;
    int acidSpayArmorReduction;
    int acidSprayManacost;

    //active
    int unstableConcoctionCd;
    int unstableConcoctionCdDefault;
    int unstableConcoctionDuration;
    int unstableConcoctionBushDuration;
    int unstableConcoctionDamage;
    int unstableConcoctionManacost;
    int unstableConcoctionCounter;
    int unstableConcoctionBotCounter;
    bool isActivedUnstableConcontion;
    bool isThrowedUnstableConcoction;

    //passive
    int greevilsPowerAmount;
    int greevilsPowerGetDPS;
    int greevilsPowerHeal;

    //active ultimate
    int chemicalRageCd;
    int chemicalRageCdDefault;
    int chemicalRageDuration;
    int chemicalRageManacost;
    int chemicalRageHpRegen;
    int chemicalRageMpRegen;
    int chemicalRageCounter;
    bool isActiveChemicalRage;

};

#endif // ALCHEMIST_H
