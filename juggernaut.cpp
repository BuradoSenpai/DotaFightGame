#include "juggernaut.h"

void Juggernaut::drawMenu()
{
    cout << "1 - Attack" << endl;
    if (this->bladeFuryCd > 0)
        cout << "2 - Blade Fury (" << this->bladeFuryCd << ")[" << this->bladeFuryManacost << "]" << endl;
    else
    {
        if (this->isActiveBladeFury)
            cout << "2 - Blade Fury <<<" << this->bladeFuryDuration-this->bladeFuryCounter << ">>>" << endl;
        else
            cout << "2 - Blade Fury [" << this->bladeFuryManacost << "]" << endl;
    }
    if (this->healingWardCd > 0)
        cout << "3 - Healing Ward (" << this->healingWardCd << ")[" << this->healingWardManacost << "]" << endl;
    else
        cout << "3 - Healing Ward [" << this->healingWardManacost << "]" << endl;
    if (this->omnislashCd > 0)
        cout << "4 - Omnislash (" << this->omnislashCd << ")[" << this->omnislashManacost << "]" << endl;
    else
        cout << "4 - Omnislash [" << this->omnislashManacost << "]" << endl;
    if (this->refreshSkillCd > 0)
        cout << "5 - Fortification (" << this->refreshSkillCd << ")" << endl;
    else
        cout << "5 - Fortification" << endl;
}

void Juggernaut::skillSelectionMenu(Hero *hero)
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
            if (selection != '1' && this->isActiveBladeFury)
            {
                cout << "You can use only Attack now!" << endl;
                _getch();
                system("cls");
                continue;
            }
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
                    if (this->bladeFuryCd > 0)
                    {
                        cout << "You can't use this ability now! Countdown is " << this->bladeFuryCd << "." << endl;
                        _getch();
                        system("cls");
                    }
                    else
                    {
                        if (this->MP() >= this->bladeFuryManacost)
                        {
                            this->bladeFury(hero);
                            _try = false;
                        }
                        else
                        {
                            cout << "You haven't enough mana!" << endl;
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
                    if (this->healingWardCd > 0)
                    {
                        cout << "You can't use this ability now! Countdown is " << this->healingWardCd << "." << endl;
                        _getch();
                        system("cls");
                    }
                    else
                    {
                        if (this->MP() >= this->healingWardManacost)
                        {
                            this->healingWard();
                            _try = false;
                        }
                        else
                        {
                            cout << "You haven't enough mana!" << endl;
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
                    if (this->omnislashCd > 0)
                    {
                        cout << "You can't use this ability now! Countdown is " << this->omnislashCd << "." << endl;
                        _getch();
                        system("cls");
                    }
                    else
                    {
                        if (this->MP() >= this->omnislashManacost)
                        {
                            this->omnislash(hero);
                            _try = false;
                        }
                        else
                        {
                            cout << "You haven't enough mana!" << endl;
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
            if (this->HP() < (int)this->getMaxHP()/100*30 && this->healingWardCd == 0 &&
                    this->MP() >= this->healingWardManacost)
                skill = 3;
            if (hero->HP() <= this->omnislashDamage*this->omnislashDuration && this->omnislashCd == 0
                    && this->MP() >= this->omnislashManacost)
                skill = 4;

            switch (skill)
            {
            case 1 :
                this->attack(hero);
                _try = false;
                break;
            case 2:
                if (!this->isSilenced() && this->bladeFuryCd == 0 && this->MP() >= this->bladeFuryManacost)
                {
                    this->bladeFury(hero);
                    _try = false;
                }
                break;
            case '3':
                if (!this->isSilenced() && this->healingWardCd == 0 && this->MP() >= this->healingWardManacost)
                {
                    this->healingWard();
                    _try = false;
                }
                break;
            case '4':
                if (!this->isSilenced() && this->omnislashCd == 0 && this->MP() >= this->omnislashCd)
                {
                    this->omnislash(hero);
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

void Juggernaut::refreshCds()
{
    this->bladeFuryCd = 0;
    this->healingWardCd = 0;
    this->omnislashCd = 0;
}

void Juggernaut::updateOwnChars()
{
    this->updateBladeFury();
    this->updateHealingWard();
    this->updateBladeDance();
}

void Juggernaut::updateCountdowns()
{
    if (this->bladeFuryCd > 0)
        this->bladeFuryCd--;
    if (this->healingWardCd > 0)
        this->healingWardCd--;
    if (this->omnislashCd > 0)
        this->omnislashCd--;
}

void Juggernaut::bladeFury(Hero *hero)
{
    if (!hero->haveImmune())
    {
        int resist = this->bladeFuryDamage/100*hero->getMagicResist();
        int damage = this->bladeFuryDamage - resist;
        hero->getDamagePerTerms(this->bladeFuryDuration, damage);
    }
    this->becomeImmuneToMagic(this->bladeFuryDuration);
    this->payMana(this->bladeFuryManacost);
    this->isActiveBladeFury = true;

    if (native)
        cout << "You have used Blade Fury on " << hero->Name() << "!" << endl;
    else
        cout << this->Name() << " has used Blade Fury on you!" << endl;
}

void Juggernaut::updateBladeFury()
{
    if (this->bladeFuryCounter < this->bladeFuryDuration && this->isActiveBladeFury)
        this->bladeFuryCounter++;
    else
    {
        if (this->isActiveBladeFury)
        {
            this->isActiveBladeFury = false;
            this->bladeFuryCounter = 0;
            this->bladeFuryCd = this->bladeFuryCdDefault;
        }
    }
}

void Juggernaut::healingWard()
{
    this->isActiveHealingWard = true;
    this->payMana(this->healingWardManacost);
    this->healingWardCd = this->healingWardCdDefault;

    if (native)
        cout << "You have used Healing Ward!" << endl;
    else
        cout << this->Name() << " has used Healing Ward!" << endl;
}

void Juggernaut::updateHealingWard()
{
    this->healingWardHeal = (this->getMaxHP()-this->HP())/100*3;
    if (this->healingWardCounter < this->healingWardDuration && this->isActiveHealingWard)
    {
        this->healingWardCounter++;
        this->heal(this->healingWardHeal);
    }
    else
    {
        if (this->isActiveHealingWard)
        {
            this->isActiveHealingWard = false;

        }
    }
}

void Juggernaut::updateBladeDance()
{
    if (!this->isActiveBladeDance)
    {
        this->critical_chance += this->bladeDanceCriticalChance;
        this->critical_damage += this->bladeDanceCriticalHit;
        this->isActiveBladeDance = true;
    }
}

void Juggernaut::omnislash(Hero *hero)
{
    this->payMana(this->omnislashManacost);
    this->omnislashCd = this->omnislashCdDefault;
    int damage = this->omnislashDamage-hero->getArmor();
    hero->getDamage(damage*this->omnislashDuration);

    if (native)
        cout << "You have used Omnislash on " << hero->Name() << "!" << endl;
    else
        cout << this->Name() << " has used Omnislash on you!" << endl;
}
