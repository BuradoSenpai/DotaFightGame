#include "facelessvoid.h"



void FacelessVoid::drawMenu()
{
    cout << "1 - Attack" << endl;
    if (this->timeWalkCd > 0)
        cout << "2 - Time Walk (" << this->timeWalkCd << ")" << "[" << this->timeWalkManacost << "]" << endl;
    else
        cout << "2 - Time Walk [" << this->timeWalkManacost << "]" << endl;
    if (this->freezeCd > 0)
        cout << "3 - Time Dilation (" << this->freezeCd << ")" << "[" << this->freezeManacost << "]" << endl;
    else
        cout << "3 - Time Dilation [" << this->freezeManacost << "]" << endl;
    if (this->chronosphereCd > 0)
        cout << "4 - Chronosphere (" << this->chronosphereCd << ")" << "[" << this->chronosphereManacost << "]" << endl;
    else
        cout << "4 - Chronosphere [" << this->chronosphereManacost << "]" << endl;
    if (this->refreshSkillCd > 0)
        cout << "5 - Fortification (" << this->refreshSkillCd << ")" << endl;
    else
        cout << "5 - Fortification" << endl;
}

void FacelessVoid::skillSelectionMenu(Hero *hero)
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
            switch (selection)
            {
            case '1':
                this->attack(hero);
                _try = false;
                break;
            case '2':
                if (!this->isSilenced())
                {
                    if (this->timeWalkCd > 0)
                    {
                        cout << "You can't use this ability now! Countdown is " << this->timeWalkCd << "." << endl;
                        _getch();
                        system("cls");
                    }
                    else
                    {
                        if (this->MP() >= this->timeWalkManacost)
                        {
                            this->timeWalk();
                            _try = false;
                        }
                        else
                        {
                            cout << "You haven't enough mana! (" << this->timeWalkManacost-this->MP() << ")" << endl;
                            _getch();
                            system("cls");
                        }
                    }
                }
                else
                {
                    cout << "You are silenced!" << endl;
                    _getch();
                    system("cls");
                }
                break;
            case '3':
                if (!this->isSilenced())
                {
                    if (this->freezeCd > 0)
                    {
                        cout << "You can't use this ability now! Countdown is " << this->freezeCd << "." << endl;
                        _getch();
                        system("cls");
                    }
                    else
                    {
                        if (this->MP() >= this->freezeManacost)
                        {
                            this->timeDilation(hero);
                            _try = false;
                        }
                        else
                        {
                            cout << "You haven't enough mana! (" << this->freezeManacost-this->MP() << ")" << endl;
                            _getch();
                            system("cls");
                        }
                    }
                }
                else
                {
                    cout << "You are silenced!" << endl;
                    _getch();
                    system("cls");
                }
                break;
            case '4':
                if (!this->isSilenced())
                {
                    if (this->chronosphereCd > 0)
                    {
                        cout << "You can't use this ability now! Countdown is " << this->chronosphereCd << "." << endl;
                        _getch();
                        system("cls");
                    }
                    else
                    {
                        if (this->MP() >= this->chronosphereManacost)
                        {
                            this->chronosphere(hero);
                            _try = false;
                        }
                        else
                        {
                            cout << "You haven't enough mana! (" << this->chronosphereManacost-this->MP() << ")" << endl;
                            _getch();
                            system("cls");
                        }
                    }
                }
                else
                {
                    cout << "You are silenced!" << endl;
                    _getch();
                    system("cls");
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
        bool _try = true;
        this->printThisAndEnemy(hero, this);
        cout << endl << endl;
        while (_try)
        {
            int skill;
            skill = rand()%5 + 1;

            if (rand()%100 < 90 && this->isActiveChronosphere)
                skill = 1;

            switch (skill)
            {
            case 1:
                this->attack(hero);
                _try = false;
                break;
            case 2:
                if (!this->isSilenced() && this->timeWalkCd == 0 && this->MP() >= this->timeWalkManacost)
                {
                    this->timeWalk();
                    _try = false;
                }
                break;
            case 3:
                if (!this->isSilenced() && this->freezeCd == 0 && this->MP() >= this->freezeManacost)
                {
                    this->timeDilation(hero);
                    _try = false;
                }
                break;
            case 4:
                if (!this->isSilenced() && this->chronosphereCd == 0 && this->MP() >= this->chronosphereManacost)
                {
                    this->chronosphere(hero);
                    _try = false;
                }
                break;
            case 5:
                if ((this->HP() < (int)((this->getMaxHP()-this->HP())/100*90) && this->MP() <
                        (int)((this->getMaxMP()-this->MP())/100*90))
                        && (this->refreshSkillCd == 0 ) && (!this->isSilenced()))
                {
                    this->refreshSkill();
                    _try = false;
                }
                break;
            }
        }
    }
}

void FacelessVoid::refreshCds()
{
    this->timeWalkCd = 0;
    this->freezeCd = 0;
    this->chronosphereCd = 0;
}

void FacelessVoid::updateOwnChars()
{
    this->updateTimeWalkHP();
    this->updateTimeLockPassive();
    this->updateChronosphere();
}

void FacelessVoid::updateCountdowns()
{
    if (this->timeWalkCd > 0)
        this->timeWalkCd--;
    if (this->freezeCd > 0)
        this->freezeCd--;
    if (this->chronosphereCd > 0)
        this->chronosphereCd--;
}

void FacelessVoid::updateFirst()
{
    if (!this->isCheckedInfoTimeWalk)
    {
        this->timeWalkPassiveGetInfoHp = this->HP();
        this->isCheckedInfoTimeWalk = true;
    }
}

void FacelessVoid::timeWalk()
{
    this->setHP(this->timeWalkPassiveGetInfoHp);
    this->payMana(this->timeWalkManacost);
    this->timeWalkCd = this->timeWalkCdDefault;
    if (native)
        cout << "You have used Time Walk!" << endl;
    else
        cout << this->Name() << " has used Time Walk!" << endl;
}

void FacelessVoid::updateTimeWalkHP()
{
    if (this->timeWalkPassiveGetInfoHpCounter == 3)
    {
        this->timeWalkPassiveGetInfoHp = this->HP();
        this->timeWalkPassiveGetInfoHpCounter = 0;
    }
    else
        this->timeWalkPassiveGetInfoHpCounter++;
}

void FacelessVoid::timeDilation(Hero *hero)
{
    this->freezeDamage = static_cast<int>(this->DPS() + this->freezeDPSreduction/100*5);

    hero->getDamage(this->freezeDamage);
    if (!hero->haveImmune())
        hero->dpsReductionForTime(this->freezeDPSreductionDuration, this->freezeDPSreduction);

    this->payMana(this->freezeManacost);
    this->freezeCd = this->freezeCdDefault;

    if (native)
        cout << "You have used Time Dilation on " << hero->Name() << "!" << endl;
    else
        cout << this->Name() << " has used Time Dilation on you!" << endl;
}

void FacelessVoid::updateTimeLockPassive()
{
    if (!this->isActiveTimeLock)
    {
        this->bash_chance += this->timeLockBushChance;
        this->isActiveTimeLock = true;
    }
}

void FacelessVoid::chronosphere(Hero *hero)
{
    hero->beDisabled(this->chronosphereDuration);
    this->payMana(this->chronosphereManacost);
    this->chronosphereCd = this->chronosphereCdDafault;
    this->isActiveChronosphere = true;

    if (native)
        cout << "You have used Chronosphere!" << endl;
    else
        cout << this->Name() << " has used Chronosphere!" << endl;
}

void FacelessVoid::updateChronosphere()
{
    if (this->chronosphereCounter < this->chronosphereDuration && this->isActiveChronosphere)
        this->chronosphereCounter++;
    else
    {
        if (this->isActiveChronosphere)
        {
            this->chronosphereCounter = 0;
            this->isActiveChronosphere = false;
        }
    }
}
