//
// Created by meowm on 8.06.2023.
//

#ifndef CPPLABZALICZENIE_KLIENT_H
#define CPPLABZALICZENIE_KLIENT_H

#include <string>

using namespace std;

enum plec {
    null = 0,
    mezczyzna = 1,
    kobieta = 2,
};

class klient {
private:
    int identyfikator;
    string haslo;
    string imie;
    string nazwisko;
    plec piec;
    string adres;
public:
    klient(int id, string pass, string imie, string nazwisko, plec piec, string adres);

    int getID();

    string getPass();

    string getImie();

    string getNazwisko();

    plec getPlec();

    string getAdres();
};


#endif //CPPLABZALICZENIE_KLIENT_H
