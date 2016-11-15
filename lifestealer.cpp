#include "lifestealer.h"


void Lifestealer::drawMenu()
{
    cout << "1 - Attack" << endl;
    if (this->rageCd > 0)
        cout << "2 - Rage (" << this->rageCd << ")" << "[" << this->rageManacost << "]" << endl;
    else
        cout << "2 - Rage [" << this->rageManacost << "]" << endl;
    if (this->openWoundsCd > 0)
        cout << "3 - Open Wounds (" << this->openWoundsCd << ")" << "[" << this->openWoundsManacost << "]" << endl;
    else
        cout << "3 - Open Wounds [" << this->openWoundsManacost << "]" << endl;
    if (this->MIcd > 0)
        cout << "4 - Monster Instincts (" << this->MIcd << ")" << "[" << this->MImanacost << "]\n";
    else
        cout << "4 - Monster Instincts [" << this->MImanacost << "]" << endl;
    if (this->refreshSkillCd > 0)
        cout << "5 - Fortification (" << this->refreshSkillCd << ")" << endl;
    else
        cout << "5 - Fortification" << endl;
}

void Lifestealer::skillSelectionMenu(Hero *hero)
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
                    if (this->rageCd > 0)
                    {
                        cout << "You can't use this ability now! Countdown is " << this->rageCd << "." << endl;
                        _getch();
                        system("cls");
                    }
                    else
                    {
                        if (this->MP() >= this->rageManacost)
                        {
                            this->rage();
                            _try = false;
                        }
                        else
                        {
                            cout << "You haven't enough mana! (" << this->rageManacost-this->MP() << ")" << endl;
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
                    if (this->openWoundsCd > 0)
                    {
                        cout << "You can't use this ability now! Countdown is " << this->openWoundsCd << "." << endl;
                        _getch();
                        system("cls");
                    }
                    else
                    {
                        if (this->MP() >= this->openWoundsManacost)
                        {
                            this->openWounds(hero);
                            _try = false;
                        }
                        else
                        {
                            cout << "You haven't enough mana! (" << this->openWoundsManacost-this->MP() << ")" << endl;
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
                    if (this->MIcd > 0)
                    {
                        cout << "You can't use this ability now! Countdown is " << this->MIcd << ".";
                        _getch();
                        system("cls");
                    }
                    else
                    {
                        if (this->MP() >= this->MImanacost)
                        {
                            this->monsterInstincts(hero);
                            _try = false;
                        }
                        else
                        {
                            cout << "You haven't enough mana! (" << this->MImanacost-this->MP() << ")";
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
                    system("cls");
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
            int skill = rand()%5 + 1;
            if (skill == 4)
                skill = 1;
            switch (skill)
            {
            case 1:
                this->attack(hero);
                _try = false;
                break;
            case 2:
                if (!this->isSilenced() && !this->isActiveRage && this->rageCd == 0 && this->MP() >= this->rageManacost)
                {
                    this->rage();
                    _try = false;
                }
                break;
            case 3:
                if (!this->isSilenced() && !this->isActiveOpenWounds && this->openWoundsCd == 0
                        && this->MP() >= this->openWoundsManacost)
                {
                    this->openWounds(hero);
                    _try = false;
                }
                break;
            case 4:
                if (!this->isSilenced() && !this->isActiveMonsterInstincts
                        && this->MIcd == 0 && this->MP() >= this->MImanacost)
                {
                    this->monsterInstincts(hero);
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

void Lifestealer::refreshCds()
{
    this->rageCd = 0;
    this->openWoundsCd = 0;
    this->MIcd = 0;
}

void Lifestealer::updateOwnChars()
{
    this->updateRage();
    this->updatePassiveLifesteal();
    this->updateOpenWounds();
    this->updateMonsterInstincts();
}

void Lifestealer::updateCountdowns()
{
    if (this->rageCd > 0)
        this->rageCd--;
    if (this->openWoundsCd > 0)
        this->openWoundsCd--;
    if (this->MIcd > 0)
        this->MIcd--;
}

void Lifestealer::rage()
{
    if (!this->isActiveRage)
    {
        this->ASbuffCount = 1;
        this->isActiveRage = true;
    }
    else
        this->ASbuffCount = 2;

    this->increaseAS(this->rageExtraAS);
    this->becomeImmuneToMagic(this->rageDuration);
    this->payMana(this->rageManacost);
    this->rageCd = this->rageCdDefault;
    if (native)
        cout << "You have used Rage!" << endl;
    else
        cout << "Lifestealer has used Rage!" << endl;
}

void Lifestealer::updateRage()
{
    if (this->rageCounter < this->rageDuration && this->isActiveRage)
        this->rageCounter++;
    else
    {
        if (this->isActiveRage)
        {
            this->rageCounter = 0;
            this->isActiveRage = false;
            this->lowAS(this->rageExtraAS*this->ASbuffCount);
        }
    }
}

void Lifestealer::updatePassiveLifesteal()
{
    if (!this->isGottenLifesteal)
    {
        this->attack_vamp += this->lifestealPercent;
        this->isGottenLifesteal = true;
    }

}

void Lifestealer::openWounds(Hero *hero)
{
    if (!this->isActiveOpenWounds)
    {
        this->LSbuffCount = 1;
        this->isActiveOpenWounds = true;
    }
    else
        this->LSbuffCount = 2;

    if (!hero->haveImmune())
        hero->armorReductionForTime(this->openWoundsDuration, this->openWoundsArmorReduction);
    this->payMana(this->openWoundsManacost);
    this->openWoundsCd = this->openWoundsCdDefault;
    this->attack_vamp += this->openWoundsExtraLifesteal;
    this->openWoundsCounter = 0;
    if (native)
        cout << "You have used Open Wounds!" << endl;
    else
        cout << "Lifestealer has used OpenWounds" << endl;
}

void Lifestealer::updateOpenWounds()
{
    if ((this->openWoundsCounter < this->openWoundsDuration) && this->isActiveOpenWounds)
        this->openWoundsCounter++;
    else
    {
        if (this->isActiveOpenWounds)
        {
            this->openWoundsCounter = 0;
            this->isActiveOpenWounds = false;
            this->loseAttackVamp(this->openWoundsExtraLifesteal*this->LSbuffCount);
        }
    }
}

void Lifestealer::monsterInstincts(Hero *hero)
{
    if (!isActiveMonsterInstincts)
    {
        this->isActiveMonsterInstincts = true;
        presentDamage = this->DPS();
        this->monsterInstinctsAScount = 1;
        this->temp_damage_ulti = static_cast<int> (hero->HP()/100*this->MIaddDamageAmount);
    }
    else
    {
        this->monsterInstinctsAScount = 2;
    }
    this->improveDPS(this->temp_damage_ulti);
    this->payMana(this->MImanacost);
    this->MIcd = this->monsterInstinctsCdDefault;
    hero->getDamage(this->MIdamage);

    if (native)
        cout << "You've used Monster's Instincts to " << hero->Name() << "!" << endl;
    else
        cout << this->Name() << " has used Monster's Instincts to you!" << endl;
}

void Lifestealer::updateMonsterInstincts()
{
    if ((this->monsterInstinctsCounter < this->monsterInstinctsDuration) && this->isActiveMonsterInstincts)
        this->monsterInstinctsCounter++;
    else
    {
        if (this->isActiveMonsterInstincts)
        {
            this->monsterInstinctsCounter = 0;
            this->isActiveMonsterInstincts = false;
            this->loosen(this->temp_damage_ulti*this->monsterInstinctsAScount);
            this->temp_damage_ulti = 0;
        }
    }
}
