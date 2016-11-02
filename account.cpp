#include "account.h"

Account::Account() // Constructor
{
    mkdir("C:\\Dota Fight");
    mkdir("C:\\Dota Fight\\Account");
    mkdir("C:\\Dota Fight\\Other");
    mkdir("C:\\Dota Fight\\Heroes");
}

Account::~Account()
{
    delete password;
}

void Account::start()
{
    func::initFiles();
    printLoginForm();
}

void Account::printLoginForm() // Acc's Form
{
    bool _try = true;
    cout << "1 - Sign In (" << getLastSessionLogin() << ")" << endl;
    cout << "2 - Sign Up" << endl;
    cout << "3 - Delete an Account" << endl;
    while (_try) {
        cout << "Select: ";
        int selection;
        cin >> selection;
        cin.get();
        switch (selection)
        {
        case 1: _try = false;
            system("cls"); signIn();
            break;
        case 2: _try = false;
            system("cls"); signUp();
            break;
        case 3: _try = false;
            system("cls"); clearAccount();
            break;
        default: continue;
        }
    }
}

void Account::signUp() // Register Form
{
    if (getLastSessionLogin() != "")
    {
        cout << "You have an account: " << getLastSessionLogin() << endl;
        cout << "If you continue your account will be deleted!" << endl;

        bool _try = true;
        while (_try)
        {
            char selection;
            cout << "Do you want to continue?(y/n) - ";
            cin >> selection;
            cin.get();
            switch (selection)
            {
            case 'y': _try = !_try;
                system("cls"); break;
            case 'n': _try = !_try; system("cls");
                printLoginForm(); return; break;
            default: continue;
            }
        }
    }
    string log;
    string pass;
    cout << "Create a login: ";
    std::getline(cin, log);
    cout << "Create a password: ";
    std::getline(cin, pass);
    std::remove(loginFilePath);
    ofstream createLoginFile(loginFilePath);

    this->login = log;
    this->password = new string(pass);
    IDs.push_back(1);
    IDs.push_back(2);
    IDs.push_back(3);
    IDs.push_back(4);
    IDs.push_back(5);

    log = func::getEncryptedText(log);
    pass = func::getEncryptedText(pass);

    system("cls");

    fillProfile();

    createLoginFile << log << endl;
    createLoginFile << pass << endl;
    createLoginFile << func::getEncryptedText(this->nickname) << endl;
    for (ui i(0); i < IDs.size(); i++)
    {
        createLoginFile << func::getEncryptedText(to_string(IDs[i])) << endl;
    }
    createLoginFile.close();

    system("cls");

    printLoginForm();
}

string Account::getLastSessionLogin() // Returns the login of present account
{
    ifstream file(loginFilePath);
    string log;
    file >> log;
    file.close();
    return func::getEncryptedText(log);
}

void Account::upLvl()
{
    this->lvl++;
    this->pLvl = 0;
    this->addHeroes();
}

void Account::saveData() // Saves the present account's data
{
    std::remove(loginFilePath);
    ofstream saveFile(loginFilePath);
    saveFile << func::getEncryptedText(this->login) << endl;
    saveFile << func::getEncryptedText(*(this->password)) << endl;
    saveFile << func::getEncryptedText(this->nickname) << endl;
    for (ui i(0); i < IDs.size(); i++)
    {
        saveFile << func::getEncryptedText(to_string(IDs[i])) << endl;
    }
    saveFile.close();
    this->writeStats();
}

void Account::succedLogin() // Logins to account
{
    this->login = func::getEncryptedText(this->getLogin);
    this->password = new string(func::getEncryptedText(this->getPassword));
    cout << endl << endl << endl << endl << endl << endl << endl << endl << endl;
    cout << "\t\t\tWelcome to Dota 2 Fight, " << this->nickname << "!";
}

void Account::fillProfile() // Form where it enters a nickname
{
    string str;
    cout << "Create a nickname: ";
    std::getline(cin, str);
    this->nickname = str;
}

void Account::clearAccount() // Deleting account
{
    char selection;
    bool _try = true;
    while (_try)
    {
        cout << "Do you want to delete an account?(y/n) - ";
        cin >> selection;
        cin.get();
        switch (selection) {
        case 'y': _try = false;
            std::remove(loginFilePath);
            cout << "Account was deleted!"; _getch(); system("cls"); printLoginForm();
            break;
        case 'n': _try = false; system("cls"); printLoginForm(); return;
            break;
        default: continue;
        }
    }
}

void Account::changeNickname()
{
    string nick;
    cout << "Create a new nicname: ";
    std::getline(cin, nick);
    system("cls");
    this->nickname = nick;
    saveData();
}

void Account::changePassword()
{
    string pass;
    cout << "Create a new password: ";
    std::getline(cin, pass);
    system("cls");
    this->password = new string(pass);
    saveData();
}

void Account::addHeroes() // Adds 5 heroes
{
    int temp = IDs.size() + 6;
    for (int i(IDs.size()+1); i < temp; i++)
        IDs.push_back(i);
    temp = 0;
}

void Account::update()
{
    if ((this->pLvl == Account::LVL_TWO) && (this->lvl == 1))
        this->upLvl();
    if ((this->pLvl == Account::LVL_THREE) && (this->lvl == 2))
        this->upLvl();
    if ((this->pLvl == Account::LVL_FOUR) && (this->lvl == 3))
        this->upLvl();
    if ((this->pLvl == Account::LVL_FIVE) && (this->lvl == 4))
        this->upLvl();
    if ((this->pLvl == Account::LVL_SIX) && (this->lvl == 5))
        this->upLvl();
    if ((this->pLvl == Account::LVL_SEVEN) && (this->lvl == 6))
        this->upLvl();
    if ((this->pLvl == Account::LVL_EIGHT) && (this->lvl == 7))
        this->upLvl();
    if ((this->pLvl == Account::LVL_NINE) && (this->lvl == 8))
        this->upLvl();
    if ((this->pLvl == Account::LVL_TEN) && (this->lvl >= 9))
        this->upLvl();
}

void Account::fillAccHeroes(vector<Hero *> heroArray) // Gets heroes from ID's vector
{
    for (ui i(0); i < IDs.size(); i++)
    {
        for (ui j(0); j < heroArray.size(); j++)
        {
            if (this->IDs[i] == heroArray[j]->getID())
            {
                this->heroes.push_back(heroArray[j]);
            }
        }
    }
}

vector<int> Account::getID()
{
    return this->IDs;
}

void Account::endInit() // a little function to continue a game
{
    Sleep(3000);
    system("cls");
}

void Account::writeGameVersion(long ver, string type)
{
    ofstream verFile("C:\\Dota Fight\\Other\\version.ini");
    verFile << ver << endl;
    verFile << type << endl;
    verFile.close();
}

bool Account::readGameVersion(long ver, string type)
{
    long tempVer;
    string tempType;
    ifstream verFile("C:\\Dota Fight\\Other\\version.ini");
    verFile >> tempVer;
    verFile >> tempType;
    verFile.close();
    if (tempVer == ver && tempType == type)
        return true;
    else
        return false;
}

vector<Hero *> Account::getHeroes()
{
    return this->heroes;
}

string Account::getNickname()
{
    return this->nickname;
}

void Account::signIn() // Login Form
{
    ifstream fileLogin(loginFilePath);
    string pass;
    string nick;
    fileLogin >> this->getLogin;
    fileLogin >> this->getPassword;
    fileLogin >> nick;
    vector<int> id;
    if (func::getEncryptedText(this->getLogin) != "")
    {
        cout << "Login: " << func::getEncryptedText(this->getLogin) << endl;
        cout << "Password: ";
        std::getline(cin, pass);
        if (func::getEncryptedText(this->getPassword) == pass)
        {
            this->nickname = func::getEncryptedText(nick);
            string temp;
            while (fileLogin >> temp)
            {
                int temp_int = std::atoi(func::getEncryptedText(temp.c_str()).c_str());
                id.push_back(temp_int);
            }
            this->IDs = id;
            system("cls");
            succedLogin();

        }
        else
        {
            cout << "Wrong password!" << endl;
            std::exit(1);
        }
        fileLogin.close();
    }
    else
    {
        bool _try = true;
        while (_try)
        {
            char selection;
            cout << "Account was not found! Do you want to create one? (y/n) - ";
            cin >> selection;
            cin.get();
            switch (selection)
            {
            case 'y': _try = !_try; system("cls"); signUp(); break;
            case 'n': _try = !_try; std::exit(0); break;
            default: continue;
            }
        }
    }
}

int Account::getWinsCount()
{
    return this->state->wins;
}

int Account::getLosesCount()
{
    return this->state->loses;
}

int Account::getGamesCount()
{
    return this->state->games;
}

double Account::getWinrate()
{
    return this->state->winrate;
}

void Account::addWin()
{
    this->state->wins++;
    this->addGame();
    this->changeWinrate();
}

void Account::addLose()
{
    this->state->loses++;
    this->addGame();
    this->changeWinrate();
}

void Account::addGame()
{
    this->state->games++;
}

void Account::changeWinrate()
{
    this->state->winrate = (this->state->wins/(this->state->games))*100;
}

void Account::writeStats()
{
    ofstream statsFile("C:\\Dota Fight\\Account\\GameStat.txt");
    statsFile << this->state->wins << endl;
    statsFile << this->state->loses << endl;
    statsFile << this->state->games << endl;
    this->state->winrate = (this->state->wins/(this->state->games))*100;
    statsFile << this->state->winrate << endl;
    statsFile.close();
}

void Account::readStats()
{
    ifstream statsFile("C:\\Dota Fight\\Account\\GameStat.txt");
    statsFile >> this->state->wins;
    statsFile >> this->state->loses;
    statsFile >> this->state->games;
    statsFile >> this->state->winrate;
    statsFile.close();
}
