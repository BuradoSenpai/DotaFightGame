#include "hero.h"

Hero::Hero(string heroFilePath, int id)
{
    this->filePath = heroFilePath;
    this->id = id;
}

Hero::~Hero()
{

}

void Hero::attackVamp(int damage)
{
    this->heal(static_cast<int>((damage/100)*this->getAttackVamp()));
}

void Hero::skillVamp(int damage)
{
    int default_vamp = (damage/100)*this->getSkillVamp();
    int magic_vamp = (this->getMaxMP()/100)*5;
    if (default_vamp != 0)
        this->heal(default_vamp*magic_vamp);
}

void Hero::upLvl()
{

}

void Hero::getLvlPoints(int count)
{
    this->pLvl += count;
}

void Hero::updateFireAndBush(bool &step)
{
    if (is_burned)
    {
        this->getDamage(this->burn_damage);
    }
    if (is_bushed)
    {
        if (!this->isDisabled())
            step = !step;
    }
    if (burn_duration > 0)
        burn_duration--;
    if (bush_duration > 0)
        bush_duration--;
    if (burn_duration == 0)
        is_burned = false;
    if (bush_duration == 0)
        is_bushed = false;
    //cout << step << endl;
}

void Hero::updateSilenceDebuff()
{
    if (this->silence_duration > 0)
        this->silence_duration--;
    if (this->silence_duration == 0 && this->is_silenced)
        this->is_silenced = false;
}

void Hero::updateImmuneToMagicBuff()
{
    if (this->immune_duration > 0)
        this->immune_duration--;
    if (this->have_immune && this->immune_duration == 0)
        this->have_immune = false;
}

void Hero::updateDisableDebuff(bool &step)
{
    if (this->is_disabled)
    {
        if (!this->isBushed())
            step = !step;
    }
    if (disable_duration > 0)
        disable_duration--;
    if (disable_duration == 0 && is_disabled)
        is_disabled = false;
}

void Hero::useRegeneration()
{
    if (this->HP() < (int)this->getMaxHP())
        this->hp += this->hpRegen();
    if (this->MP() < (int)this->getMaxMP())
        this->mp += this->mpRegen();
}

void Hero::selectSkill(int skill, Hero *hero)
{
    cout << "It's an abstract class! You can't use skills!" << endl;
    hero->getID();
    int *temp = new int(skill);
    delete temp;
}

void Hero::drawMenu()
{
    cout << "It's an virtual object" << endl;
}

void Hero::skillSelectionMenu(Hero *hero)
{
    hero->getID();
}

void Hero::init()
{
    ifstream file(this->filePath);
    file >> this->name;
    file >> this->hp;
    file >> this->max_hp;
    file >> this->hp_regen;
    file >> this->mp;
    file >> this->max_mp;
    file >> this->mp_regen;
    file >> this->dmg;
    file >> this->armor;
    file >> this->attack_speed;
    file >> this->attack_vamp;
    file >> this->skill_vamp;
    file >> this->critical_chance;
    file >> this->critical_damage;
    file >> this->bash_chance;
    file >> this->miss_chance;
    file.close();

    this->armorReductionDuration = 0;
    this->armorReductionPower = 0;
    this->presentArmor = 0;

    this->dpsReductionDuration = 0;
    this->dpsReductionPower = 0;
    this->presentDPS = 0;

    this->burn_damage = 0;
    this->burn_duration = 0;
    this->bush_duration = 0;
    this->is_burned = false;
    this->is_bushed = false;
    this->presentArmor = this->armor;
    this->presentDPS = this->DPS();

    this->refreshSkillCd = 0;
    this->refreshSkillCdDefault = 50;

    this->magicResist = 25;
}

string Hero::getFilePath()
{
    return this->filePath;
}

void Hero::beBurned(int duration, int damage)
{
    this->burn_duration = duration;
    this->burn_damage = damage;
    this->is_burned = true;
}

void Hero::beBushed(int duration)
{
    this->bush_duration += duration;
    this->is_bushed = true;
}

void Hero::beSilenced(int sec)
{
    this->is_silenced = true;
    this->silence_duration = sec;
}

void Hero::becomeImmuneToMagic(int sec)
{
    this->have_immune = true;
    this->immune_duration = sec;
}

void Hero::beDisabled(int sec)
{
    this->is_disabled = true;
    this->disable_duration = sec;
}

void Hero::attack(Hero *hero)
{
    srand(time(NULL));
    int damage = 0;
    int critical_hits = 0;
    bool is_missed = false;
    bool bushed = false;
    int bushDamage = static_cast<int>(this->DPS()/100*5);
    for (int i(0); i < (int)this->SA(); i++)
    {
        if (rand()%100 > (int)hero->getMissChance())
        {
            if (rand()%100 < (int)this->getCriticalChance())
            {
                damage += (this->DPS()*this->getCriticalDamage())-hero->getArmor();
                critical_hits += 1;
            }
            else
                damage += this->DPS()-hero->getArmor();
            if (rand()%100 < (int)this->getBashChance())
                bushed = true;
            this->attackCounterAllTime++;
        }
        else
        {
            is_missed = true;
            if (native)
                cout << "You missed " << hero->Name() << "!" << endl;
            else
                cout << this->Name() << " missed you!" << endl;
        }
    }
    if (!is_missed)
    {
        if (bushed)
        {
            if (native)
                cout << "You bushed the enemy!" << endl;
            else
                cout << this->Name() << " bushed you" << endl;
            damage += bushDamage;
            hero->beBushed(1);
        }

        hero->getDamage(damage);
        this->attackVamp(damage);
        if (critical_hits == 1)
            cout << "Critical hit!" << endl;
        else if (critical_hits > 1)
            cout << "Critical hit! x" << critical_hits << endl;
        if (native)
            cout << "You have done " << damage << " damage to " << hero->Name() << "!" << endl;
        else
            cout << this->Name() << " has done " << damage << " damage to you!" << endl;
    }
}

void Hero::updateHP()
{
    if (this->hp < 0)
        this->hp = 0;
}

void Hero::armorReductionForTime(int sec, int pow)
{
    if (!(this->armorReductionDuration > 0))
        this->presentArmor = static_cast<int>(this->armor);
    else
        this->presentArmor = static_cast<int>(this->armor+pow);
    this->armorReductionDuration = sec;
    this->armorReductionPower = pow;
    this->armor -= pow;
}

void Hero::updateArmorReduction()
{
    if (this->armorReductionDuration > 0)
        this->armorReductionDuration--;
    else
        this->armor = this->presentArmor;
}

void Hero::dpsReductionForTime(int sec, int pow)
{
    if (!(this->dpsReductionDuration > 0))
        this->presentDPS = static_cast<int>(this->dmg);
    else
        this->presentDPS = static_cast<int>(this->dmg+pow);
    this->dpsReductionDuration = sec;
    this->dpsReductionPower = pow;
    this->loosen(pow);
}

void Hero::getDamagePerTerms(int sec, int pow)
{
    this->damagePerTerm = pow;
    this->damagePerTermDuration = sec;
    this->isActiveDamagePerTerm = true;
}

void Hero::updateDamagePerTerm()
{
    if (this->damagePerTermDuration > 0)
        this->damagePerTermDuration--;
    else
        this->isActiveDamagePerTerm = false;
    if (this->isActiveDamagePerTerm)
    {
        this->getDamage(this->damagePerTerm);
    }
}

void Hero::updateDpsReduction()
{
    if (this->dpsReductionDuration > 0)
        this->dpsReductionDuration--;
    else
        this->dmg = this->presentDPS;
}

void Hero::updateMaxValuesHPMP()
{
    if (this->HP() > (int)this->getMaxHP())
        this->hp = static_cast<int>(this->max_hp);
    if (this->MP() > (int)this->getMaxMP())
        this->mp = static_cast<int>(this->max_mp);
}

void Hero::updateOwnChars()
{

}

void Hero::update(bool &step)
{
    this->useRegeneration();
    this->updateArmorReduction();
    this->updateDpsReduction();
    this->updateFireAndBush(step);
    this->updateDamagePerTerm();
    this->updateCountdowns();
    this->updateSilenceDebuff();
    this->updateImmuneToMagicBuff();
    this->updateDisableDebuff(step);
    this->updateRefreshCd();
    this->updateOwnChars();
    this->updateHP();
}

void Hero::updateCountdowns()
{
    //cout << "It's an virtual object" << endl;
}

void Hero::updateFirst()
{

}

void Hero::printThisAndEnemy(Hero *player, Hero *enemy)
{
    cout << player->Name() << ": \t\t\t\t\t\t\t " << enemy->Name() << ":" << endl;
    cout << "HP: " << player->HP() << "/" << player->getMaxHP() << " \t\t\t\t\t\t\t" << "HP: " << enemy->HP() << "/" << enemy->getMaxHP() << endl;
    cout << "MP: " << player->MP() << "/" << player->getMaxMP() << " \t\t\t\t\t\t\t" << "MP: " << enemy->MP() << "/" << enemy->getMaxMP() << endl;
    cout << "DPS: " << player->DPS() << " \t\t\t\t\t\t\t" << "DPS: " << enemy->DPS() << endl;
    cout << "Armor: " << player->getArmor() << " \t\t\t\t\t\t\t" << "Armor: " << enemy->getArmor() << endl;


    if (player->isBurned() || player->isBushed() || enemy->isBurned() || enemy->isBushed() || player->isSilenced() || enemy->isSilenced())
    {
        cout << endl;

        if (player->isSilenced() && !enemy->isSilenced())
            cout << "Silence: " << player->silenceDuration() << "s" << endl;
        else if (!player->isSilenced() && enemy->isSilenced())
            cout << "\t\t\t\t\t\t\t\tSilence: " << enemy->silenceDuration() << "s" << endl;
        else if (player->isSilenced() && enemy->isSilenced())
        {
            cout << "Silence: " << player->silenceDuration() << "s ";
            cout << "\t\t\t\t\t\t\tSilence: " << enemy->silenceDuration() << "s" << endl;
        }

        if (player->isBurned() && player->isBushed() && enemy->isBurned() && enemy->isBushed())
        {
            cout << "Bush: " << player->getBushDuration() << "s \t\t\t\t\t\t\tBush: " << enemy->getBushDuration() << "s" << endl;
            cout << "Burn: " << player->getBurnDuration() << "s \t\t\t\t\t\t\tBurn: " << enemy->getBurnDuration() << "s" << endl;
        }
        else if (!player->isBurned() && player->isBushed() && enemy->isBurned() && enemy->isBushed())
        {
            cout << "Bush: " << player->getBushDuration() << "s \t\t\t\t\t\t\tBush: " << enemy->getBushDuration() << "s" << endl;
            cout << "\t\t\t\t\t\t\t\tBurn: " << enemy->getBurnDuration() << "s" << endl;
        }
        else if (player->isBurned() && !player->isBushed() && enemy->isBurned() && enemy->isBushed())
        {
            cout << "\t\t\t\t\t\t\t\tBush: " << enemy->getBushDuration() << "s" << endl;
            cout << "Burn: " << player->getBurnDuration() << "s \t\t\t\t\t\t\tBurn: " << enemy->getBurnDuration() << "s" << endl;
        }
        else if (player->isBurned() && player->isBushed() && !enemy->isBurned() && enemy->isBushed())
        {
            cout << "Bush: " << player->getBushDuration() << "s \t\t\t\t\t\t\tBush: " << enemy->getBushDuration() << "s" << endl;
            cout << "Burn: " << player->getBurnDuration() << "s" << endl;
        }
        else if (player->isBurned() && player->isBushed() && enemy->isBurned() && !enemy->isBushed())
        {
            cout << "Bush: " << player->getBushDuration() << "s" << endl;
            cout << "Burn: " << player->getBurnDuration() << "s \t\t\t\t\t\t\tBurn: " << enemy->getBurnDuration() << "s" << endl;
        }
        else if (!player->isBurned() && !player->isBushed() && enemy->isBurned() && enemy->isBushed())
        {
            cout << "\t\t\t\t\t\t\t\tBush: " << enemy->getBushDuration() << "s" << endl;
            cout << "\t\t\t\t\t\t\t\tBurn: " << enemy->getBurnDuration() << "s" << endl;
        }
        else if (!player->isBurned() && player->isBushed() && !enemy->isBurned() && enemy->isBushed())
            cout << "Bush: " << player->getBushDuration() << "s \t\t\t\t\t\t\tBush: " << enemy->getBushDuration() << "s" << endl;
        else if (!player->isBurned() && player->isBushed() && enemy->isBurned() && !enemy->isBushed())
        {
            cout << "Bush: " << player->getBushDuration() << "s \t\t\t\t\t\t\tBush: " << enemy->getBushDuration() << "s" << endl;
            cout << "\t\t\t\t\t\t\t\tBurn: " << enemy->getBurnDuration() << "s" << endl;
        }
        else if (player->isBurned() && !player->isBushed() && !enemy->isBurned() && enemy->isBushed())
            cout << "Burn: " << player->getBurnDuration() << "s \t\t\t\t\t\t\tBush: " << enemy->getBushDuration() << "s" << endl;
        else if (player->isBurned() && !player->isBushed() && enemy->isBurned() && !enemy->isBushed())
            cout << "Burn: " << player->getBurnDuration() << "s \t\t\t\t\t\t\tBurn: " << enemy->getBurnDuration() << "s" << endl;
        else if (player->isBurned() && player->isBushed() && !enemy->isBurned() && !enemy->isBushed())
        {
            cout << "Bush: " << player->getBushDuration() << "s" << endl;
            cout << "Burn: " << player->getBurnDuration() << "s" << endl;
        }
        else if (player->isBurned() && !player->isBushed() && !enemy->isBurned() && !enemy->isBushed())
            cout << "Burn: " << player->getBurnDuration() << "s" << endl;
        else if (!player->isBurned() && player->isBushed() && !enemy->isBurned() && !enemy->isBushed())
            cout << "Bush: " << player->getBushDuration() << "s" << endl;
        else if (!player->isBurned() && !player->isBushed() && enemy->isBurned() && !enemy->isBushed())
            cout << "\t\t\t\t\t\t\t\tBurn: " << enemy->getBurnDuration() << "s" << endl;
        else if (!player->isBurned() && !player->isBushed() && !enemy->isBurned() && enemy->isBushed())
            cout << "\t\t\t\t\t\t\t\tBush: " << enemy->getBushDuration() << "s" << endl;
    }
}

void Hero::refreshCds()
{

}

void Hero::refreshManaAndHp()
{
    int notEnoughHP = static_cast<int> (this->getMaxHP()-this->HP());
    int notEnoughMP = static_cast<int> (this->getMaxMP()-this->MP());
    int percentOfHeal = static_cast<int> ((notEnoughHP/100)*30);
    int percentOfPoolMP = static_cast<int> ((notEnoughMP/100)*35);
    this->heal(percentOfHeal);
    this->getMana(percentOfPoolMP);
}

void Hero::refreshSkill()
{
    this->refreshCds();
    this->refreshManaAndHp();
    this->refreshSkillCd = this->refreshSkillCdDefault;
    if (native)
        cout << "You've used fortification" << endl;
    else
        cout << this->Name() << " has used fortification" << endl;
}

void Hero::updateRefreshCd()
{
    if (this->refreshSkillCd > 0)
        this->refreshSkillCd--;
}
