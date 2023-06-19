//
// Created by meowm on 13.06.2023.
//

#ifndef CPPLABZALICZENIE_ZAMOWIENIE_H
#define CPPLABZALICZENIE_ZAMOWIENIE_H

#include "string"

using namespace std;

enum platnosc {
    gotowka = 0,
    przelew = 1,
    czek = 2,
};

class zamowienie {
private:
    int identyfikator;
    int idKlienta;
    int idAuta;
    string dataZamowienia;
    platnosc sposobPlatnosci;
public:
    zamowienie(int id, int idK, int idA, string dataZ, platnosc sposP);

    int getID();

    int getIdKlienta();

    int getIdAuta();

    string getDataZamowienia();

    platnosc getSposobPlatnosci();
};


#endif //CPPLABZALICZENIE_ZAMOWIENIE_H
