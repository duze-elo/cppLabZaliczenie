//
// Created by meowm on 10.06.2023.
//

#include "samochod.h"

using namespace std;

samochod::samochod(int id, string prod, string mod, int cen, bool av) {
    identyfikator = id;
    producent = prod;
    model = mod;
    cena = cen;
    dostepnosc = av;
}

int samochod::getID() {
    return identyfikator;
}

string samochod::getProducent() {
    return producent;
}

string samochod::getModel() {
    return model;
}

int samochod::getCena() {
    return cena;
}

bool samochod::getDostepnosc() {
    return dostepnosc;
}

void samochod::setID(int id) {
    this->identyfikator = id;
}

void samochod::setProducer(string prod) {
    this->producent = prod;
}

void samochod::setModel(string mod) {
    this->model = mod;
}

void samochod::setCena(int cen) {
    this->cena = cen;
}

void samochod::setDostepnosc(bool dost) {
    this->dostepnosc = dost;
}