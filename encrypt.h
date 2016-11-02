#ifndef ENCRYPT_H
#define ENCRYPT_H

#include <iostream>
#include <string>
#include <fstream>


using namespace std;

namespace func {

inline string getEncryptedText(string a)
{
    char *text = new char[a.size() + 1];
    std::copy(a.begin(), a.end(), text);
    text[a.size()] = '\0';
    for (unsigned int i(0); i < a.size(); i++)
    {
        switch (text[i])
        {
        case 'Q': text[i] = 'M'; break;
        case 'W': text[i] = 'N'; break;
        case 'E': text[i] = 'B'; break;
        case 'R': text[i] = 'V'; break;
        case 'T': text[i] = 'C'; break;
        case 'Y': text[i] = 'X'; break;
        case 'U': text[i] = 'Z'; break;
        case 'I': text[i] = 'L'; break;
        case 'O': text[i] = 'K'; break;
        case 'P': text[i] = 'J'; break;
        case 'A': text[i] = 'H'; break;
        case 'S': text[i] = 'G'; break;
        case 'D': text[i] = 'F'; break;
        case 'F': text[i] = 'D'; break;
        case 'G': text[i] = 'S'; break;
        case 'H': text[i] = 'A'; break;
        case 'J': text[i] = 'P'; break;
        case 'K': text[i] = 'O'; break;
        case 'L': text[i] = 'I'; break;
        case 'Z': text[i] = 'U'; break;
        case 'X': text[i] = 'Y'; break;
        case 'C': text[i] = 'T'; break;
        case 'V': text[i] = 'R'; break;
        case 'B': text[i] = 'E'; break;
        case 'N': text[i] = 'W'; break;
        case 'M': text[i] = 'Q'; break;
        case 'q': text[i] = 'm'; break;
        case 'w': text[i] = 'n'; break;
        case 'e': text[i] = 'b'; break;
        case 'r': text[i] = 'v'; break;
        case 't': text[i] = 'c'; break;
        case 'y': text[i] = 'x'; break;
        case 'u': text[i] = 'z'; break;
        case 'i': text[i] = 'l'; break;
        case 'o': text[i] = 'k'; break;
        case 'p': text[i] = 'j'; break;
        case 'a': text[i] = 'h'; break;
        case 's': text[i] = 'g'; break;
        case 'd': text[i] = 'f'; break;
        case 'f': text[i] = 'd'; break;
        case 'g': text[i] = 's'; break;
        case 'h': text[i] = 'a'; break;
        case 'j': text[i] = 'p'; break;
        case 'k': text[i] = 'o'; break;
        case 'l': text[i] = 'i'; break;
        case 'z': text[i] = 'u'; break;
        case 'x': text[i] = 'y'; break;
        case 'c': text[i] = 't'; break;
        case 'v': text[i] = 'r'; break;
        case 'b': text[i] = 'e'; break;
        case 'n': text[i] = 'w'; break;
        case 'm': text[i] = 'q'; break;
        case ' ': text[i] = '-'; break;
        case '-': text[i] = ' '; break;
        case '.': text[i] = ','; break;
        case ',': text[i] = '.'; break;
        case '0': text[i] = '9'; break;
        case '1': text[i] = '8'; break;
        case '2': text[i] = '7'; break;
        case '3': text[i] = '6'; break;
        case '4': text[i] = '5'; break;
        case '5': text[i] = '4'; break;
        case '6': text[i] = '3'; break;
        case '7': text[i] = '2'; break;
        case '8': text[i] = '1'; break;
        case '9': text[i] = '0'; break;
        case '!': text[i] = '?'; break;
        case '?': text[i] = '!'; break;
        }
    }
    string str = text;
    delete [] text;
    return str;
}

inline void initFiles()
{
    ofstream interestingLogins("C:\\Dota Fight\\Other\\caVsihP.txt");
    interestingLogins << getEncryptedText("burado") << endl;
    interestingLogins << getEncryptedText("senpai") << endl;
    interestingLogins << getEncryptedText("imbalance") << endl;
    interestingLogins << getEncryptedText("C++") << endl;
    interestingLogins << getEncryptedText("vuiko") << endl;
    interestingLogins << getEncryptedText("kazah") << endl;
    interestingLogins.close();

    ofstream alchemistFile("C:\\Dota Fight\\Heroes\\Alchemist.ini");
    alchemistFile << "Alchemist" << endl;
    alchemistFile << 3507 << endl;
    alchemistFile << 3507 << endl;
    alchemistFile << 1 << endl;
    alchemistFile << 765 << endl;
    alchemistFile << 765 << endl;
    alchemistFile << 1 << endl;
    alchemistFile << 54 << endl;
    alchemistFile << 2 << endl;
    alchemistFile << 1 << endl;
    alchemistFile << 0 << endl;
    alchemistFile << 0 << endl;
    alchemistFile << 2 << endl;
    alchemistFile << 1.2 << endl;
    alchemistFile << 1 << endl;
    alchemistFile << 1 << endl;
    alchemistFile.close();

    ofstream lifestealerFile("C:\\Dota Fight\\Heroes\\Lifestealer.ini");
    lifestealerFile << "Lifestealer" << endl;
    lifestealerFile << 3201 << endl;
    lifestealerFile << 3201 << endl;
    lifestealerFile << 2 << endl;
    lifestealerFile << 522 << endl;
    lifestealerFile << 522 << endl;
    lifestealerFile << 1 << endl;
    lifestealerFile << 71 << endl;
    lifestealerFile << 4 << endl;
    lifestealerFile << 1 << endl;
    lifestealerFile << 0 << endl;
    lifestealerFile << 0 << endl;
    lifestealerFile << 2 << endl;
    lifestealerFile << 1.2 << endl;
    lifestealerFile << 1 << endl;
    lifestealerFile << 1 << endl;
    lifestealerFile.close();

    ofstream facelessVoidFile("C:\\Dota Fight\\Heroes\\Faceless Void.ini");
    facelessVoidFile << "FacelessVoid" << endl;
    facelessVoidFile << 3312 << endl;
    facelessVoidFile << 3212 << endl;
    facelessVoidFile << 1 << endl;
    facelessVoidFile << 642 << endl;
    facelessVoidFile << 642 << endl;
    facelessVoidFile << 1 << endl;
    facelessVoidFile << 87 << endl;
    facelessVoidFile << 3 << endl;
    facelessVoidFile << 1 << endl;
    facelessVoidFile << 0 << endl;
    facelessVoidFile << 0 << endl;
    facelessVoidFile << 2 << endl;
    facelessVoidFile << 1.2 << endl;
    facelessVoidFile << 1 << endl;
    facelessVoidFile << 1 << endl;
    facelessVoidFile.close();

    ofstream juggernautFile("C:\\Dota Fight\\Heroes\\Juggernaut.ini");
    juggernautFile << "Juggernaut" << endl;
    juggernautFile << 2870 << endl;
    juggernautFile << 2870 << endl;
    juggernautFile << 2 << endl;
    juggernautFile << 620 << endl;
    juggernautFile << 620 << endl;
    juggernautFile << 1 << endl;
    juggernautFile << 65 << endl;
    juggernautFile << 2 << endl;
    juggernautFile << 1 << endl;
    juggernautFile << 0 << endl;
    juggernautFile << 0 << endl;
    juggernautFile << 2 << endl;
    juggernautFile << 1.2 << endl;
    juggernautFile << 1 << endl;
    juggernautFile << 1 << endl;
    juggernautFile.close();
}

}
#endif // ENCRYPT_H
