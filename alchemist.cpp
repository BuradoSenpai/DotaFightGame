#include "alchemist.h"

void Alchemist::drawMenu()
{
    cout << "1 - Attack" << endl;
    if (this->acidSprayCd > 0)
        cout << "2 - Acid Spray (" << this->acidSprayCd << ")" << "[" << this->acidSprayManacost << "]" << endl;
    else
        cout << "2 - Acid Spray " << "[" << this->acidSprayManacost << "]" << endl;
    if (!this->isActivedUnstableConcontion)
    {
        if (this->unstableConcoctionCd > 0)
            cout << "3 - Unstable Concontion (" << this->unstableConcoctionCd << ")" << "[" << this->unstableConcoctionManacost << "]" << endl;
        else
            cout << "3 - Unstable Concontion " << "[" << this->unstableConcoctionManacost << "]" << endl;
    }
    else
        cout << "3 - Unstable Concontion Throw " << "<<" << this->unstableConcoctionDuration-this->unstableConcoctionCounter << ">>" << endl;
    if (this->chemicalRageCd > 0)
        cout << "4 - Chemical Rage (" << this->chemicalRageCd << ")" << "[" << this->chemicalRageManacost << "]" << endl;
    else
        cout << "4 - Chemical Rage " << "[" << this->chemicalRageManacost << "]" << endl;
    if (this->refreshSkillCd > 0)
        cout << "5 - Fortification (" << this->refreshSkillCd << ")" << endl;
    else
        cout << "5 - Fortification" << endl;
}

void Alchemist::skillSelectionMenu(Hero *hero)
{
    if (native)
    {
        bool _try = true;
        while (_try)
        {
            this->printThisAndEnemy(this,hero);
            cout << endl;
            this->drawMenu();
            char selection;
            cout << "Select ability: ";
            cin >> selection;
            cin.get();
            cout << endl;
            switch (selection) {
            case '1':
                this->attack(hero);
                _try = false;
                break;
            case '2':
                if (!this->isSilenced())
                {
                    if (this->acidSprayCd > 0)
                    {
                        cout << "You can't use this ability now! Countdown is " << this->acidSprayCd << "." << endl;
                        _getch();
                        system("cls");
                    }
                    else
                    {
                        if (this->MP() >= this->acidSprayManacost)
                        {
                            this->acidSpray(hero);
                            _try = false;
                        }
                        else
                        {
                            cout << "You haven't enought mana! (" << this->acidSprayManacost-this->MP() << ")" << endl;
                            _getch();
                            system("cls");
                        }
                    }
                }
                else
                {
                    cout << "You are silenced!" << endl;
                    _getch();
                    system("csl");
                }
                break;
            case '3':
                if (!this->isSilenced())
                {
                    if (!this->isActivedUnstableConcontion)
                    {
                        if (this->unstableConcoctionCd > 0)
                        {
                            cout << "You can't use this ability now! Countdown is " << this->unstableConcoctionCd << "." << endl;
                            _getch();
                            system("cls");
                        }
                        else
                        {
                            if (this->MP() >= this->unstableConcoctionManacost)
                            {
                                this->useUnstableConcoction();
                                _try = false;
                            }
                            else
                            {
                                cout << "You haven't enough mana! (" << this->unstableConcoctionManacost-this->MP() << ")" << endl;
                                _getch();
                                system("cls");
                            }
                        }
                    }
                    else
                    {
                        this->throwUnstableConcoction(hero);
                        _try = false;
                    }
                }
                else
                {
                    cout << "You are silenced!" << endl;
                    _getch();
                    system("csl");
                }
                break;
            case '4':
                if (!this->isSilenced())
                {
                    if (!this->isActiveChemicalRage)
                    {
                        if (this->chemicalRageCd > 0)
                        {
                            cout << "You can't use this ability now! Countdown is " << this->chemicalRageCd << "." << endl;
                            _getch();
                            system("cls");
                        }
                        else
                        {
                            if (this->MP() >= this->chemicalRageManacost)
                            {
                                this->chemicalRage();
                                _try = false;
                            }
                            else
                            {
                                cout << "You haven't enough mana! (" << this->chemicalRageManacost-this->MP() << ")" << endl;
                                _getch();
                                system("cls");
                            }
                        }
                    }
                    else
                    {
                        cout << "You have already used this ability!" << endl;
                        _getch();
                        system("cls");
                    }
                }
                else
                {
                    cout << "You are silenced!" << endl;
                    _getch();
                    system("csl");
                }
                break;
            case '5':
                if (!this->isSilenced())
                {
                    if (this->refreshSkillCd > 0)
                    {
                        cout << "You can't use this ability now! Countdown is " << this->refreshSkillCd << "." << endl;
                        _getch();
                        system("cls");
                    }
                    else
                    {
                        this->refreshSkill();
                        _try = false;
                    }
                }
                else
                {
                    cout << "You are silenced!" << endl;
                    _getch();
                    system("csl");
                }
                break;
            default:
                system("cls");
                break;
            }
        }
    }
    else
    {
        //srand(time(NULL));
        bool _try = true;
        this->printThisAndEnemy(hero, this);
        cout << endl << endl;
        while (_try)
        {
            int skill;
            if ((this->HP() <= (int)this->getMaxHP()/100*30) && !this->isActiveChemicalRage && this->chemicalRageCd == 0)
            {
                skill = 4;
            }
            else
                skill = rand()%5 + 1;

            switch (skill) {
            case 1:
                this->attack(hero);
                _try = false;
                break;
            case 2:
                if ((this->acidSprayCd == 0 && this->MP() >= this->acidSprayManacost) && (this->unstableConcoctionCounter < 4)
                        && (!this->isSilenced()))
                {
                    if (!hero->haveImmune())
                        this->acidSpray(hero);
                    else
                        cout << hero->Name() << " has immune to magic!" << endl;
                    _try = false;
                }
                break;
            case 3:
                if (this->isActivedUnstableConcontion)
                {
                    this->throwUnstableConcoction(hero);
                    _try = false;
                }
                else
                {
                    if (this->unstableConcoctionCd == 0 && this->unstableConcoctionManacost && (!this->isSilenced()))
                    {
                        this->useUnstableConcoction();
                        _try = false;
                    }
                }
                break;
            case 4:
                if ((!this->isActiveChemicalRage) && (this->MP() >= this->chemicalRageManacost) &&
                        (this->chemicalRageCd == 0) && (this->unstableConcoctionCd < 4) &&
                        (this->HP() <= static_cast<int>((this->getMaxHP()/100*50))) && (!this->isSilenced()))
                {
                    this->chemicalRage();
                    _try = false;
                }
                break;
            case 5:
                if ((this->HP() < (int)((this->getMaxHP()-this->HP())/100*90) && this->MP() < (int)((this->getMaxMP()-this->MP())/100*90))
                        && (this->refreshSkillCd ==0) && (this->unstableConcoctionCd < 4) && (!this->isSilenced()))
                {
                    this->refreshSkill();
                    _try = false;
                }
                break;
            }
        }
    }
}

void Alchemist::refreshCds()
{
    this->acidSprayCd = 0;
    this->unstableConcoctionCd = 0;
    this->chemicalRageCd = 0;
}

void Alchemist::acidSpray(Hero *hero)
{
    if (!hero->haveImmune())
        hero->armorReductionForTime(this->acidSprayDuration, this->acidSpayArmorReduction);
    hero->beBurned(this->acidSprayDuration, this->acidSprayDamage-hero->getArmor());
    this->payMana(this->acidSprayManacost);
    this->acidSprayCd = this->acidSprayCdDefault;
    if (native)
        cout << "You have used Acid Spray at " << hero->Name() << "!" << endl;
    else
        cout << "Achemist has used Acid Spray at you!" << endl;
}

void Alchemist::useUnstableConcoction()
{
    this->payMana(this->unstableConcoctionManacost);
    makeUnstableConcoction();
    if (native)
        cout << "You've made Unstable Concontion!" << endl;
    else
        cout << "Achemist has made Unstable Concontion!" << endl;
}

void Alchemist::throwUnstableConcoction(Hero *hero)
{
    if (this->isActivedUnstableConcontion)
    {
        if (!hero->haveImmune())
            hero->beBushed(this->unstableConcoctionCounter);
        int resistArmor = static_cast<int> (this->unstableConcoctionDamage/100*this->magicResist);
        hero->getDamage(this->unstableConcoctionDamage-resistArmor);
        this->unstableConcoctionCd = this->unstableConcoctionCdDefault;
        this->isThrowedUnstableConcoction = true;
        if (native)
            cout << "You threw Unstable Concontion at " << hero->Name() << "!" << endl;
        else
            cout << "Alchemist threw Unstable Concontion at you!" << endl;
    }
}

void Alchemist::makeUnstableConcoction()
{
    this->isThrowedUnstableConcoction = false;
    this->isActivedUnstableConcontion = true;
    this->unstableConcoctionCounter = 0;
}

void Alchemist::updateUnstableConcontion()
{
    if (this->unstableConcoctionCounter < this->unstableConcoctionDuration && this->isActivedUnstableConcontion)
        this->unstableConcoctionCounter++;
    if (this->isThrowedUnstableConcoction)
    {
        this->isActivedUnstableConcontion = false;
        this->unstableConcoctionCounter = 0;

    }
    if (this->isActivedUnstableConcontion && this->unstableConcoctionCounter == this->unstableConcoctionDuration)
    {
        this->beBushed(this->unstableConcoctionCounter);
        this->getDamage(this->unstableConcoctionDamage);
        this->isThrowedUnstableConcoction = true;
        this->unstableConcoctionCd = this->unstableConcoctionCdDefault;
    }
}

void Alchemist::updateGreevilsPower()
{
    if (this->attackCounterAllTime == 5)
    {
        this->attackCounterAllTime = 0;
        this->extraDamage += this->greevilsPowerGetDPS;
        this->dmg += this->greevilsPowerGetDPS;
        this->hp += this->greevilsPowerHeal;
    }
}

void Alchemist::unstableConcoction(Hero *hero)
{
    if (!this->isActivedUnstableConcontion)
        this->useUnstableConcoction();
    else
        this->throwUnstableConcoction(hero);
}

void Alchemist::updateCountdowns()
{
    if (this->acidSprayCd > 0)
        this->acidSprayCd--;
    if (this->unstableConcoctionCd > 0 && !this->isActivedUnstableConcontion)
        this->unstableConcoctionCd--;
    if (this->chemicalRageCd > 0)
        this->chemicalRageCd--;
}


void Alchemist::chemicalRage()
{
    this->addHpRegen(this->chemicalRageHpRegen);
    this->addMpRegen(this->chemicalRageMpRegen);
    this->payMana(this->chemicalRageManacost);
    this->chemicalRageCd = this->chemicalRageCdDefault;
    this->isActiveChemicalRage = true;
    if (native)
        cout << "You've used Chemical Rage!" << endl;
    else
        cout << "Alchemist has used Chemical Rage!" << endl;
}

void Alchemist::updateChemicalRage()
{
    if (this->chemicalRageCounter < this->chemicalRageDuration && this->isActiveChemicalRage)
        this->chemicalRageCounter++;
    else if (this->chemicalRageCounter == this->chemicalRageDuration && this->isActiveChemicalRage)
    {
        this->chemicalRageCounter = 0;
        this->isActiveChemicalRage = false;
        this->loseHpRegen(this->chemicalRageHpRegen);
        this->loseMpRegen(this->chemicalRageMpRegen);
    }
}

void Alchemist::updateOwnChars()
{
    this->updateGreevilsPower();
    this->updateUnstableConcontion();
    this->updateChemicalRage();
}
