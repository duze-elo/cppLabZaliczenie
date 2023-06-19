//
// Created by meowm on 8.06.2023.
//

#include "klient.h"

klient::klient(int id, string pass, string im, string naz, plec pl, string adr) {
    identyfikator = id;
    haslo = pass;
    imie = im;
    nazwisko = naz;
    piec = pl;
    adres = adr;
}

int klient::getID() {
    return identyfikator;
}

string klient::getPass() {
    return haslo;
}

string klient::getImie() {
    return imie;
}

string klient::getNazwisko() {
    return nazwisko;
}

plec klient::getPlec() {
    return piec;
}

string klient::getAdres() {
    return adres;
}
