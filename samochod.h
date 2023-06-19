//
// Created by meowm on 10.06.2023.
//

#ifndef CPPLABZALICZENIE_SAMOCHOD_H
#define CPPLABZALICZENIE_SAMOCHOD_H

#include "string"

using namespace std;

class samochod {
private:
    int identyfikator;
    string producent;
    string model;
    int cena;
    bool dostepnosc;
public:
    samochod(int id, string prod, string mod, int cen, bool av);

    int getID();

    string getProducent();

    string getModel();

    int getCena();

    bool getDostepnosc();

    void setID(int id);

    void setProducer(string prod);

    void setModel(string mod);

    void setCena(int cen);

    void setDostepnosc(bool dost);
};


#endif //CPPLABZALICZENIE_SAMOCHOD_H
