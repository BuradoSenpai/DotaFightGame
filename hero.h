#ifndef HERO_H
#define HERO_H

#include <fstream>
#include <string>
#include <cmath>
#include <iostream>
#include <conio.h>
#include <vector>
#include <time.h>
#include <random>
#include <iomanip>
#include <encrypt.h>

using namespace std;

class Hero
{
    typedef unsigned int ui;
public:
    Hero() {}
    Hero(string heroFilePath, int id);
    virtual ~Hero();

    virtual string &Name() {
        return this->name;
    }
    virtual int HP() {
        return this->hp;
    }

    virtual int hpRegen() {
        return this->hp_regen;
    }

    virtual ui getMaxHP() {
        return this->max_hp;
    }

    virtual int MP() {
        return this->mp;
    }

    virtual int mpRegen() {
        return this->mp_regen;
    }

    virtual ui getMaxMP() {
        return this->max_mp;
    }

    virtual int DPS() {
        return this->dmg;
    }

    virtual int getArmor() {
        return this->armor;
    }

    virtual ui SA() {
        return this->attack_speed;
    }

    virtual ui getBashChance() {
        return this->bash_chance;
    }

    virtual ui getMissChance() {
        return this->miss_chance;
    }

    virtual void setMissChance(int miss_chance) {
        this->miss_chance = miss_chance;
    }

    virtual int getAttackVamp() {
        return this->attack_vamp;
    }

    virtual void addAttackVamp(int pow) {
        this->attack_vamp += pow;
    }

    virtual void loseAttackVamp(int pow) {
        this->attack_vamp -= pow;
    }

    virtual void attackVamp(int damage);
    virtual void skillVamp(int damage);

    virtual ui getSkillVamp() {
        return this->skill_vamp;
    }

    virtual ui getCriticalChance() {
        return this->critical_chance;
    }

    virtual void setCriticalChance(int chance) {
        this->critical_chance = chance;
    }

    virtual void setCriticalDamage(int damage) {
        this->critical_damage = damage;
    }

    virtual double getCriticalDamage() {
        return this->critical_damage;
    }

    virtual void setName(string name) {
        this->name = name;
    }

    virtual void setHP(int hp) {
        this->hp = hp;
    }

    virtual void setMP(int mp) {
        this->mp = mp;
    }

    virtual void setDPS(int dps) {
        this->dmg = dps;
    }

    virtual void setArmor(int armor) {
        this->armor = armor;
    }

    virtual void setAS(int as) {
        this->attack_speed = as;
    }

    virtual void increaseAS(int pow) {
        this->attack_speed += pow;
    }

    virtual void lowAS(int pow) {
     this->attack_speed -= pow;
    }

    virtual void heal(int pow) {
        this->hp += pow;
    }

    virtual void addHpRegen(int pow) {
        this->hp_regen += pow;
    }

    virtual void addMpRegen(int pow) {
        this->mp_regen += pow;
    }

    virtual void loseHpRegen(int pow) {
        this->hp_regen -= pow;
    }

    virtual void loseMpRegen(int pow) {
        this->mp_regen -= pow;
    }

    virtual void getMana(int pow) {
        this->mp += pow;
    }

    virtual void improveDPS(int pow) {
        this->dmg += pow;
    }

    virtual void improveArmor(int pow) {
        this->armor += pow;
    }

    virtual void getDamage(int pow) {
        this->hp -= pow;
    }

    virtual void payMana(int pow) {
        this->mp -= pow;
    }

    virtual void loosen(int pow) {
        this->dmg -= pow;
    }

    virtual void crashGuard(int pow) {
        this->armor -= pow;
    }

    virtual void is_natived(bool is) {
        this->native = is;
    }

    virtual bool isNative() {
        return this->native;
    }

    virtual bool isBushed() {
        return this->is_bushed;
    }

    virtual bool isBurned() {
        return this->is_burned;
    }

    virtual int getBushDuration() {
        return this->bush_duration;
    }

    virtual int getBurnDuration() {
        return this->burn_duration;
    }
    virtual bool haveImmune() {
        return this->have_immune;
    }
    virtual int immuneDuration() {
        return this->immune_duration;
    }
    virtual bool isSilenced() {
        return this->is_silenced;
    }
    virtual int silenceDuration() {
        return this->silence_duration;
    }
    virtual bool isDisabled() {
        return this->is_disabled;
    }
    virtual int disableDuration() {
        return this->disable_duration;
    }
    virtual int getMagicResist() {
        return this->magicResist;
    }

    virtual void upLvl();
    virtual void getLvlPoints(int count);
    virtual void useRegeneration();
    virtual void selectSkill(int skill, Hero *hero);
    virtual int getID() {
        return this->id;
    }

    virtual void drawMenu();
    virtual void skillSelectionMenu(Hero *hero);

    virtual void init();
    virtual string getFilePath();

    virtual void beBurned(int sec, int damage);
    virtual void beBushed(int sec);
    virtual void beSilenced(int sec);
    virtual void becomeImmuneToMagic(int sec);
    virtual void beDisabled(int sec);
    virtual void attack(Hero *hero);

    virtual void updateHP();
    virtual void armorReductionForTime(int sec, int pow);
    virtual void updateArmorReduction();
    virtual void dpsReductionForTime(int sec, int pow);
    virtual void getDamagePerTerms(int sec, int pow);
    virtual void updateDamagePerTerm();
    virtual void updateDpsReduction();
    virtual void updateMaxValuesHPMP();
    virtual void updateOwnChars();

    virtual void update(bool &step);
    virtual void updateFireAndBush(bool &step);
    virtual void updateSilenceDebuff();
    virtual void updateImmuneToMagicBuff();
    virtual void updateDisableDebuff(bool &step);
    virtual void updateCountdowns();
    virtual void updateFirst();

    virtual void printThisAndEnemy(Hero *player, Hero *enemy);

    virtual void refreshCds();
    virtual void refreshManaAndHp();
    virtual void refreshSkill();
    virtual void updateRefreshCd();

protected:
    string name;
    ui max_hp;
    int hp;
    int hp_regen;
    ui max_mp;
    int mp;
    int mp_regen;
    int dmg;
    int armor;
    int attack_speed;
    int bash_chance;
    int attack_vamp;
    int skill_vamp;
    int miss_chance;
    int critical_chance;
    double critical_damage;

    int magicResist;

    bool is_burned;
    bool is_bushed;
    bool is_silenced;
    bool have_immune;
    bool is_disabled;
    int bush_duration;
    int burn_duration;
    int silence_duration;
    int immune_duration;
    int burn_damage;
    int disable_duration;

    int lvl;
    int pLvl;
    int id;

    bool native;

    string filePath;

    int presentArmor;
    int armorReductionPower;
    int armorReductionDuration;
    int tempTimeArmorReduction;

    int presentDPS;
    int dpsReductionPower;
    int dpsReductionDuration;

    int damagePerTerm;
    int damagePerTermDuration;
    bool isActiveDamagePerTerm;

    int attackCounterAllTime;
    int skillCounterAllTime;

    int refreshSkillCd;
    int refreshSkillCdDefault;

    vector<string> fightMagazine;
};

#endif // HERO_H
#ifndef HERO_H
#define HERO_H


class Hero
{
public:
    Hero();
};

#endif // HERO_H
