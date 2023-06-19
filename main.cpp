#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <vector>

#include "klient.h"
#include "samochod.h"
#include "zamowienie.h"

using namespace std;

void displayMenuShop() {
    cout << "======== MENU SKLEPU ========" << endl;
    cout << "1. Panel klienta" << endl;
    cout << "2. Pokaz auta" << endl;
    cout << "3. Zloz zamowienie" << endl;
    cout << "4. Wyloguj sie" << endl;
}

void displayMenuLogin() {
    cout << "======== MENU LOGOWANIA ========" << endl;
    cout << "1. Logowanie" << endl;
    cout << "2. Rejestracja" << endl;
    cout << "3. Wyjscie" << endl;
}

void displayMenuUser() {
    cout << "========= MENU KLIENTA =========" << endl;
    cout << "1. Informacje o uzytkowniku" << endl;
    cout << "2. Edycja klienta" << endl;
    cout << "3. Usuwanie konta" << endl;
    cout << "4. Moje zamowienia" << endl;
    cout << "5. Powrot do menu sklepu" << endl;
}

void userInfo(klient klient1) {
    cout << "======Informacje klienta======" << endl;
    string passSlice = klient1.getPass().substr(0, 2);
    int passHashFill = klient1.getPass().length() - 2;
    string passHash = passSlice + string(passHashFill, '*');

    cout << "Identyfikator: " << klient1.getID() << endl;
    cout << "Haslo: " << passHash << endl;
    cout << "Imie: " << klient1.getImie() << endl;
    cout << "Nazwisko: " << klient1.getNazwisko() << endl;
    switch (klient1.getPlec()) {
        case 0:
            cout << "Plec: Niesprecyzowana" << endl;
            break;
        case 1:
            cout << "Plec: Mezczyzna" << endl;
            break;
        case 2:
            cout << "Plec: Kobieta" << endl;
            break;
        default:
            cout << "Blad wyswietlania plci!" << endl;
            break;
    }
    cout << "Adres dostawy: " << klient1.getAdres() << endl;
    cout << endl;
}

void createNewKlient() {
    string pass, imie, nazwisko, adres;
    plec pl;

    int maxId = 0;
    ifstream file("klienci.txt");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        int clientId;
        string password, dump;

        ss >> clientId;
        getline(ss, dump, ';');
        getline(ss, dump, ';');
        getline(ss, dump, ';');
        getline(ss, dump, ';');
        getline(ss, dump, ';');
        getline(ss, dump);

        if (maxId < clientId) {
            maxId = clientId;
        }
    }
    file.close();

    int id = maxId + 1;

    cout << "Podaj haslo: ";
    cin >> pass;
    cout << "Podaj imie: ";
    cin >> imie;
    cout << "Podaj nazwisko: ";
    cin >> nazwisko;
    int plecValue;
    cout << "Wybierz plec (0 - Niesprecyzowana, 1 - Mezczyzna, 2 - Kobieta): ";
    cin >> plecValue;
    if (plecValue != 0) {
        if (plecValue != 1) {
            if (plecValue != 2) {
                cout << "Prosze o wprowadzenie poprawnel plci" << endl;
                cout << "Wybierz plec (0 - Niesprecyzowana, 1 - Mezczyzna, 2 - Kobieta): ";
                cin >> plecValue;
            }
        }
    }

    pl = static_cast<plec>(plecValue);
    cout << "Podaj adres dostawy: ";
    cin.ignore();
    getline(cin, adres);
    cout << endl;

    ofstream outfile("klienci.txt", ios::app);
    if (outfile.is_open()) {
        outfile << id << ";"
                << pass << ";"
                << imie << ";"
                << nazwisko << ";"
                << static_cast<int>(pl) << ";"
                << adres << endl;
        outfile.close();
        cout << "Konto zostalo utworzone." << endl;
        cout << "Dane logowania" << endl;
        cout << "Identyfikator: " << id << endl;
        cout << "Haslo: " << pass << endl << endl;
    } else {
        cout << "Blad otwarcia pliku." << endl;
    }
}

bool checkIfExist(int id) {
    ifstream file("klienci.txt");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        int clientId;
        ss >> clientId;
        if (clientId == id) {
            return true;
        }
    }
    return false;
}

bool checkPassword(int id, const string &pass) {
    ifstream file("klienci.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            int clientId;
            string password, imie, nazwisko, plecStr, adres, dump;

            ss >> clientId;
            getline(ss, dump, ';');
            getline(ss, password, ';');
            getline(ss, imie, ';');
            getline(ss, nazwisko, ';');
            getline(ss, plecStr, ';');
            getline(ss, adres);

            if (clientId == id && password == pass) {
                file.close();
                return true;
            }
        }
        file.close();
    } else {
        cout << "B³¹d otwarcia pliku." << endl;
    }
    return false;
}

klient getClientData(int id) {
    ifstream file("klienci.txt");
    if (file.is_open()) {
        int clientId;
        string line;
        while (getline(file, line, ';')) {
            clientId = stoi(line);
            string pass, imie, nazwisko, plecStr, adres;
            getline(file, pass, ';');
            getline(file, imie, ';');
            getline(file, nazwisko, ';');
            getline(file, plecStr, ';');
            getline(file, adres);

            if (clientId == id) {
                file.close();

                plec klientPlec;
                if (plecStr == "0") {
                    klientPlec = null;
                } else if (plecStr == "1") {
                    klientPlec = mezczyzna;
                } else if (plecStr == "2") {
                    klientPlec = kobieta;
                } else {
                    cout << "Blad konwersji plci!" << endl;
                    return klient(0, "", "", "", null, "");
                }

                return klient(clientId, pass, imie, nazwisko, klientPlec, adres);
            }
        }
        file.close();
    } else {
        cout << "Blad otwarcia pliku." << endl;
    }
    return klient(0, "", "", "", null, "");
}

void editKlientAccount(int id) {
    ifstream file("klienci.txt");
    ofstream tempFile("temp.txt");

    if (file.is_open() && tempFile.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            int clientId;
            string pass, imie, nazwisko, plecStr, adres;
            ss >> clientId;
            getline(ss, pass, ';');
            getline(ss, imie, ';');
            getline(ss, nazwisko, ';');
            getline(ss, plecStr, ';');
            getline(ss, adres);

            if (clientId == id) {
                cout << "Edycja danych klienta o ID: " << id << endl;
                cout << "Nowe haslo: ";
                cin >> pass;
                cout << "Nowe imie: ";
                cin >> imie;
                cout << "Nowe nazwisko: ";
                cin >> nazwisko;
                cout << "Nowa plec (1 - Mezczyzna, 2 - Kobieta): ";
                int plecValue;
                cin >> plecValue;
                plecStr = to_string(plecValue);
                cout << "Nowy adres dostawy: ";
                cin.ignore();
                getline(cin, adres);

                tempFile << id << ";" << pass << ";" << imie << ";" << nazwisko << ";" << plecStr << ";" << adres
                         << endl;
            } else {
                tempFile << line << endl;
            }
        }

        file.close();
        tempFile.close();

        if (remove("klienci.txt") == 0 && rename("temp.txt", "klienci.txt") == 0) {
            cout << "Dane klienta zostaly zaktualizowane." << endl;
        } else {
            cout << "Blad aktualizacji danych klienta." << endl;
        }
    } else {
        cout << "Blad otwarcia pliku." << endl;
    }
}

void deleteKlientAccount(int id) {
    ifstream file("klienci.txt");
    if (file.is_open()) {
        ofstream tempFile("temp.txt");
        if (tempFile.is_open()) {
            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                int clientId;
                ss >> clientId;
                if (clientId != id) {
                    tempFile << line << endl;
                }
            }
            file.close();
            tempFile.close();

            if (remove("klienci.txt") != 0) {
                cout << "Blad usuwania konta." << endl;
            } else {
                if (rename("temp.txt", "klienci.txt") != 0) {
                    cout << "Blad usuwania konta." << endl;
                } else {
                    cout << "====Konto zostalo usuniete====" << endl;
                }
            }
        } else {
            cout << "Blad otwarcia pliku tymczasowego." << endl;
        }
    } else {
        cout << "Blad otwarcia pliku." << endl;
    }
}

void showAvailableCars(vector<samochod> &samochody) {
    cout << "=======Lista samochodow=======" << endl;
    int size = samochody.size();
    for (auto &s: samochody) {
        cout << "ID: " << s.getID() << endl;
        cout << "Producent: " << s.getProducent() << endl;
        cout << "Model: " << s.getModel() << endl;
        cout << "Cena: " << s.getCena() << endl;
        cout << "VAT: " << s.getCena() * 0.24 << endl;
        cout << "Dostepnose: ";
        if (s.getDostepnosc() == 1) {
            cout << "tak" << endl;
        } else if (s.getDostepnosc() == 0) {
            cout << "nie" << endl;
        } else {
            cout << "blad" << endl;
        }
        cout << "==============================" << endl;
    }
}

vector<samochod> wczytajSamochodyZPliku(const string &nazwaPliku) {
    vector<samochod> samochody;

    ifstream plik(nazwaPliku);
    if (plik.is_open()) {
        string linia;
        while (getline(plik, linia)) {
            stringstream ss(linia);
            string pole;

            int id;
            string producent, model, dump;
            int cena;
            int dostepnoscInt;

            ss >> id;
            getline(ss, dump, ';');
            getline(ss, producent, ';');
            getline(ss, model, ';');
            ss >> cena;
            getline(ss, dump, ';');
            ss >> dostepnoscInt;
            getline(ss, dump, ';');

            bool dostepnosc = (dostepnoscInt == 1);

            samochod samochod(id, producent, model, cena, dostepnosc);
            samochody.push_back(samochod);
        }
        plik.close();
    } else {
        cout << "Blad otwarcia pliku." << endl;
    }

    return samochody;
}

string getCurrentDate() {
    time_t currentTime = time(nullptr);

    tm *localTime = localtime(&currentTime);

    int year = localTime->tm_year + 1900;
    int month = localTime->tm_mon + 1;
    int day = localTime->tm_mday;

    stringstream ss;
    ss << year << "-" << month << "-" << day;
    string currentDate = ss.str();

    return currentDate;
}

void newOrder(int idKlienta, int idAuta, const string &dataZamowienia, platnosc sposobPlatnosci) {
    int maxId = 0;
    ifstream zamowienie("zamowienia.txt");
    string line;
    while (getline(zamowienie, line)) {
        stringstream ss(line);
        int zamowienieId;
        string password, dump;

        ss >> zamowienieId;
        getline(ss, dump, ';');
        getline(ss, dump, ';');
        getline(ss, dump, ';');
        getline(ss, dump, ';');
        getline(ss, dump, ';');
        getline(ss, dump);

        if (maxId < zamowienieId) {
            maxId = zamowienieId;
        }
    }
    zamowienie.close();
    int idZamowienia = maxId + 1;

    ofstream file("zamowienia.txt", ios::app);
    if (file.is_open()) {
        file << idZamowienia << ";"
             << idKlienta << ";"
             << idAuta << ";"
             << dataZamowienia << ";"
             << sposobPlatnosci << endl;

        file.close();
        cout << "Zamowienie zostalo zlozone." << endl;
    } else {
        cout << "Blad otwarcia pliku." << endl;
    }
}

void zmienDostepnoscAuta(vector<samochod> &samochody, int idAuta, bool nowaDostepnosc) {
    for (auto &samochod: samochody) {
        if (samochod.getID() == idAuta) {
            samochod.setDostepnosc(nowaDostepnosc);
            break;
        }
    }
}

void updateCars(vector<samochod> &samochody) {
    ofstream file("samochody.txt");
    if (file.is_open()) {
        for (samochod samochod: samochody) {
            file << samochod.getID() << ";"
                 << samochod.getProducent() << ";"
                 << samochod.getModel() << ";"
                 << samochod.getCena() << ";"
                 << samochod.getDostepnosc() << endl;
        }
        file.close();
    } else {
        cout << "Blad otwarcia pliku." << endl;
    }
}

void displayOrdersByClient(klient &klientZalogowany) {
    cout << "=======Twoje zamowienia=======" << endl;
    ifstream file("zamowienia.txt");
    if (file.is_open()) {
        string line;
        bool found = false;

        while (getline(file, line)) {
            stringstream ss(line);
            zamowienie order(0, 0, 0, "", gotowka);

            int id, idKlienta, idAuta;
            string dataZamowienia, dump;
            int sposobPlatnosci;

            ss >> id;
            getline(ss, dump, ';');
            ss >> idKlienta;
            getline(ss, dump, ';');
            ss >> idAuta;
            getline(ss, dump, ';');
            getline(ss, dataZamowienia, ';');
            ss >> sposobPlatnosci;

            if (idKlienta == klientZalogowany.getID()) {
                found = true;
                cout << "ID zamowienia: " << id << endl;
                cout << "ID klienta: " << idKlienta << endl;
                cout << "ID auta: " << idAuta << endl;
                cout << "Data zamowienia: " << dataZamowienia << endl;
                cout << "Sposob platnosci: ";
                if (sposobPlatnosci == 0) {
                    cout << "gotowka" << endl;
                } else if (sposobPlatnosci == 1) {
                    cout << "przelew" << endl;
                } else if (sposobPlatnosci == 2) {
                    cout << "czek" << endl;
                } else {
                    cout << "niesprecyzowana" << endl;
                }
                cout << "==============================" << endl << endl;
            }
        }

        file.close();

        if (!found) {
            cout << "Brak zamowien dla tego klienta." << endl;
        }
    } else {
        cout << "Blad otwarcia pliku." << endl;
    }
}

int main() {
    int choiceL = 0;
    int choiceS = 0;
    int choiceU = 0;
    string aktualnaData;

    vector<samochod> listaSamochodow = wczytajSamochodyZPliku("samochody.txt");

    klient klientZalogowany(0, "", "", "", null, "");
    samochod samochodTemp(0, "", "", 0, false);
    zamowienie zamowienieTemp(0, 0, 0, "", gotowka);

    int id = 0;
    string pass = " ";

    do {
        displayMenuLogin();
        cout << "Wybierz opcje: ";
        cin >> choiceL;
        cout << endl;
        switch (choiceL) {
            case 1:
                cout << "======Formularz logowania=====" << endl;
                cout << "Podaj identyfikator: ";
                cin >> id;
                if (checkIfExist(id)) {
                    cout << "Podaj haslo: ";
                    cin >> pass;
                    cout << endl;
                    if (checkPassword(id, pass)) {
                        do {
                            klientZalogowany = getClientData(id);
                            displayMenuShop();
                            cout << "Wybierz opcje: ";
                            cin >> choiceS;
                            cout << endl;

                            switch (choiceS) {
                                case 1:
                                    do {
                                        displayMenuUser();
                                        cout << "Wybierz opcje: ";
                                        cin >> choiceU;
                                        cout << endl;

                                        switch (choiceU) {
                                            case 1:
                                                userInfo(klientZalogowany);
                                                break;
                                            case 2:
                                                editKlientAccount(klientZalogowany.getID());
                                                cout << "=====Nastapilo wylogowanie====" << endl;
                                                choiceU = 5;
                                                choiceS = 4;
                                                break;
                                            case 3:
                                                deleteKlientAccount(klientZalogowany.getID());
                                                cout << "=====Nastapilo wylogowanie====" << endl;
                                                choiceU = 5;
                                                choiceS = 4;
                                                break;
                                            case 4:
                                                displayOrdersByClient(klientZalogowany);
                                                break;
                                            case 5:
                                                break;
                                            default:
                                                cout << "Nieprawidlowa opcja. Wybierz ponownie." << endl;
                                                break;
                                        }
                                    } while (choiceU != 5);
                                    break;
                                case 2:
                                    showAvailableCars(listaSamochodow);
                                    break;
                                case 3:
                                    int idA;
                                    int sposobPlatnosciValue;
                                    platnosc plat;
                                    aktualnaData = getCurrentDate();
                                    cout << "Podaj Identyfikator auta" << endl;
                                    cin >> idA;
                                    cout << "Wybierz sposob platnosci:" << endl << "0 - Gotowka, 1 - przelew, 2 - czek"
                                         << endl;
                                    cin >> sposobPlatnosciValue;
                                    plat = static_cast<platnosc>(sposobPlatnosciValue);
                                    newOrder(klientZalogowany.getID(), idA, aktualnaData, plat);
                                    zmienDostepnoscAuta(listaSamochodow, idA, 0);
                                    updateCars(listaSamochodow);
                                    break;
                                case 4:
                                    cout << "Pomyslnie wylogowano" << endl;
                                    break;
                                default:
                                    cout << "Nieprawidlowa opcja. Wybierz ponownie." << endl;
                                    break;
                            }
                            cout << endl;
                        } while (choiceS != 4);
                    } else {
                        cout << "Bledne haslo!" << endl;
                    }
                } else {
                    cout << "Nie znaleziono konta o takim identyfikatorze!" << endl;
                }
                break;
            case 2:
                cout << "====Formularz rejestracyjny===" << endl;
                createNewKlient();
                break;
            case 3:
                cout << "Wyjscie z programu" << endl;
                break;
            default:
                cout << "Nieprawidlowa opcja. Wybierz ponownie." << endl;
                break;
        }
    } while (choiceL != 3);

    return 0;
}
