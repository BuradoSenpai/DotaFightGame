#include <game.h>

Game::Game(Account * acc)
{
    this->account = acc;
    system("title Dota 2 Fight");
    srand(time(NULL));
}

Game::~Game()
{

}

void Game::printMenu()
{
    system("cls");
    cout << "1 - Play" << endl;
    cout << "2 - Profile" << endl;
    cout << "3 - Settings" << endl;
    cout << "4 - Exit" << endl;
    bool _try = true;

    while (_try)










    {
        cout << "Select: ";
        char selection;
        cin >> selection;
        cin.get();
        switch (selection)
        {
        case '1':
            this->playMenu();
            break;
        case '2':
            this->profileMenu();
            break;
        case '3':
            this->settingsMenu();
            break;
        case '4':
            std::exit(0);
            this->account->saveData();
            break;
        default:
            continue;
        }
    }
}

void Game::getHeroList(vector<Hero *> list)
{
    this->heroes = list;
}

void Game::getAllHeroList(vector<Hero *> list)
{
    this->allHeroes = list;
}

void Game::startDefaultGame(Hero *player, Hero *enemy)
{
    player->init();
    enemy->init();

    system("cls");
    player->is_natived(1);
    enemy->is_natived(0);
    player->updateFirst();
    enemy->updateFirst();
    srand(time(NULL));

    bool step = 0;
    int step_counter = 0;
    do
    {
        player->updateMaxValuesHPMP();
        enemy->updateMaxValuesHPMP();
        if (!(step%2))
            player->skillSelectionMenu(enemy);
        else
            enemy->skillSelectionMenu(player);

        _getch();
        system("cls");

        step = !step;
        step_counter++;
        player->update(step);
        enemy->update(step);

        if (step_counter == 10)
        {
            step_counter = 0;
            player->improveDPS(10);
            player->improveArmor(2);
            enemy->improveDPS(10);
            enemy->improveArmor(2);
        }

        if (player->HP() <= 0 || enemy->HP() <= 0)
            break;

    } while (true);

    if (player->HP() > 0 && enemy->HP() <= 0)
    {
        cout << player->Name() << " has won!" << endl;
        this->account->addWin();
        this->account->writeStats();
    }
    else if (player->HP() <= 0 && enemy->HP() > 0)
    {
        cout << enemy->Name() << " has won!" << endl;
        this->account->addLose();
        this->account->writeStats();
    }

    _getch();
    system("cls");

}

void Game::playMenu()
{
    system("cls");
    srand(time(NULL));

    bool _try = true;

    Hero *hero;
    Hero *enemy;

    while (_try)
    {
        for (int i(0); i < this->heroes.size(); i++)
        {
            cout << i+1 << " - " << heroes[i]->Name() << endl;
        }
        cout << this->heroes.size()+1 << " - Random" << endl;
        cout << endl;
        cout << "Pick a hero: ";

        int selection;
        cin >> selection;

        if (selection < 1 || selection > this->heroes.size() + 1)
        {
            system("cls");
            continue;
        }

        int hero_rand;
        if (selection == this->heroes.size() + 1)
        {
            hero_rand = rand()%this->heroes.size();
            hero = this->heroes[hero_rand];
        }
        else
            hero = this->heroes[selection-1];

        bool _new_try = true;
        while(_new_try)
        {
            /*  Pointers are common in both vectors.
             *  It may do so, there could be problem.
             *  "Hero" and "Enemy" can take same object (pointer).
             *  If it happens, the object will be out of control.
             *
             *  This code checks if they are same object.
             *  If it is, "Enemy" will take other pointer.
             *  Else game will start without this problem.
             *  Thank you for attention! :)
             */
            int enemy_rand = rand()%this->allHeroes.size();
            enemy = this->allHeroes[enemy_rand];

            if (enemy->getID() == hero->getID())
                continue;
            else
                _new_try = false;
        }

        this->startDefaultGame(hero, enemy);
    }
}

Hero *Game::getRandomHero(vector<Hero *> list)
{
    srand(time(NULL));
    int hero = rand()%list.size();
    return list[hero];
}

void Game::settingsMenu()
{
    system("cls");
    cout << "1 - Account's settings" << endl;
}

void Game::profileMenu()
{
    system("cls");
    bool _try = true;
    while (_try)
    {
        cout << "Nickname: " << this->account->getNickname() << endl;
        cout << "Wins: " << this->account->getWinsCount() << endl;
        cout << "Loses: " << this->account->getLosesCount() << endl;
        cout << "Games: " << this->account->getGamesCount() << endl;
        cout << "Winrate: " << this->account->getWinrate() << "%" << endl;

        cout << endl;

        cout << "1 - My heroes" << endl;
        cout << "2 - All Heroes" << endl;
        cout << "3 - Back" << endl;
        cout << "Select: ";
        char selection;
        cin >> selection;
        cin.get();
        switch (selection)
        {
        case '1':
            system("cls");
            for (int i(0); i < this->heroes.size(); i++)
                cout << i+1 << " - " << this->heroes[i]->Name() << endl;
            _getch();
            _try = false;
            this->profileMenu();
            break;
        case '2':
            system("cls");
            for (int i(0); i < this->allHeroes.size(); i++)
                cout << i+1 << " - " << this->allHeroes[i]->Name() << endl;
            _getch();
            _try = false;
            this->profileMenu();
            break;
        case '3':
            this->printMenu();
            _try = false;
            return;
            break;
        default:
            system("cls");
        }
    }
}

void Game::start()
{
    this->account->readStats();
    for (int i(0); i < this->allHeroes.size(); i++)
        this->allHeroes[i]->init();
    this->printMenu();
}
