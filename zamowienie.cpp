//
// Created by meowm on 13.06.2023.
//

#include "zamowienie.h"

using namespace std;

zamowienie::zamowienie(int id, int idK, int idA, string dataZ, platnosc sposP) {
    identyfikator = id;
    idKlienta = idK;
    idAuta = idA;
    dataZamowienia = dataZ;
    sposobPlatnosci = sposP;
}

int zamowienie::getID() {
    return identyfikator;
}

int zamowienie::getIdKlienta() {
    return idKlienta;
}

int zamowienie::getIdAuta() {
    return idAuta;
}

string zamowienie::getDataZamowienia() {
    return dataZamowienia;
}

platnosc zamowienie::getSposobPlatnosci() {
    return sposobPlatnosci;
}