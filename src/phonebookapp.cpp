#include "phonebookapp.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <algorithm>

PhoneBookApp::PhoneBookApp() {}
PhoneBookApp::~PhoneBookApp() {}

void PhoneBookApp::run() {
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;
        processCommand(line);
    }
}

void PhoneBookApp::processCommand(const std::string& command) {
    std::string cmd, rest;
    size_t firstSpace = command.find(' ');
    if (firstSpace == std::string::npos) {
        cmd = command;
        rest = "";
    } else {
        cmd = command.substr(0, firstSpace);
        rest = command.substr(firstSpace + 1);
    }
    std::stringstream ss(rest);

if (cmd == "ADD") {
    // Ellenőrizzük, hogy pontosan 5 vessző van (azaz 6 mező)
    int commaCount = std::count(rest.begin(), rest.end(), ',');
    if (commaCount != 5) {
        std::cerr << "Hiba: Hibás mezőszám! 6 mező elvárt." << std::endl;
        return;
    }

    std::string fields[6];
    for (int i = 0; i < 6; ++i) {
        std::getline(ss, fields[i], ',');
    }

    // Legalább egy telefonszám kötelező
    if (fields[4].empty() && fields[5].empty()) {
        std::cerr << "Hiba: Legalább egy telefonszámot meg kell adni!" << std::endl;
        return;
    }

    // Duplikáció ellenőrzés
    for (size_t i = 0; i < contacts.getDb(); ++i) {
        Contact* existing = contacts.getContactAt(i);
        if (existing && existing->matches(fields[0].c_str(), fields[1].c_str(), fields[4].c_str())) {
            std::cerr << "Hiba: Ilyen név és telefonszám már szerepel a listában!" << std::endl;
            return;
        }
        if (existing && existing->matches(fields[0].c_str(), fields[1].c_str(), fields[5].c_str())) {
            std::cerr << "Hiba: Ilyen név és telefonszám már szerepel a listában!" << std::endl;
            return;
        }
    }

    // Új kontakt hozzáadása
    contacts.add(new Contact(
        fields[0].c_str(),
        fields[1].c_str(),
        fields[2].c_str(),
        fields[3].c_str(),
        fields[4].c_str(),
        fields[5].c_str()
    ));
}
 else if (cmd == "DELETE") {
        std::string vn, kn, tel;
        std::getline(ss, vn, ',');
        std::getline(ss, kn, ',');
        std::getline(ss, tel, ',');
        if (vn.empty() || kn.empty() || tel.empty()) {
            std::cerr << "Hiba: Hiányzó mező a DELETE parancsban." << std::endl;
            return;
        }
        contacts.remove(vn.c_str(), kn.c_str(), tel.c_str());
    } else if (cmd == "LIST") {
        contacts.list();
    } else if (cmd == "EDIT") {
        std::string vn, kn, tel;
        std::getline(ss, vn, ',');
        std::getline(ss, kn, ',');
        std::getline(ss, tel, ',');

        std::string bn = "", c = "", ms = "", ps = "";
        bool changed = false;

        std::string token;
        while (std::getline(ss, token, ',')) {
            size_t colon = token.find(":");
            if (colon == std::string::npos) continue;
            std::string field = token.substr(0, colon);
            std::string value = token.substr(colon + 1);

            if (field == "becenev") { bn = value; changed = true; }
            else if (field == "cim") { c = value; changed = true; }
            else if (field == "munka") { ms = value; changed = true; }
            else if (field == "privat") { ps = value; changed = true; }
        }

        if (!changed) {
            std::cerr << "Figyelem: Nem történt módosítás, nem adtál meg mezőt!" << std::endl;
            return;
        }

        contacts.edit(vn.c_str(), kn.c_str(), tel.c_str(),
                      bn.c_str(), c.c_str(), ms.c_str(), ps.c_str());
    } else if (cmd == "SEARCH") {
        std::string field, value;
        std::getline(ss, field, ',');
        std::getline(ss, value, ',');
        if (field.empty() || value.empty()) {
            std::cerr << "Hiba: Hiányzó mező a SEARCH parancsban." << std::endl;
            return;
        }

        if (field == "tel" || field == "vezeteknev" || field == "keresztnev") {
            contacts.search(field.c_str(), value.c_str());
        } else {
            std::cerr << "Hiba: Ismeretlen mező a SEARCH parancsban." << std::endl;
        }
    } else if (cmd == "LOAD") {
        std::string filename;
        std::getline(ss, filename);
        if (filename.empty()) {
            std::cerr << "Hiba: Hiányzó fájlnév a LOAD parancsban." << std::endl;
            return;
        }
        // fájl betöltés - duplikációk kiszűrése egyedi hozzáadás logikával
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Hiba: Nem sikerült megnyitni a fájlt: " << filename << std::endl;
            return;
        }
        std::string line;
        while (std::getline(file, line)) {
        std::stringstream lineStream(line);
        std::string fields[6];
        bool valid = true;

        for (int i = 0; i < 6; ++i) {
            if (!std::getline(lineStream, fields[i], ',')) {
                std::cerr << "Hiba: Hibás sor a fájlban." << std::endl;
                valid = false;
                break;
            }
        }

        if (!valid || (fields[4].empty() && fields[5].empty()))
            continue;

        bool found = false;
        for (size_t i = 0; i < contacts.getDb(); ++i) {
            Contact* existing = contacts.getContactAt(i);
            if (existing->matches(fields[0].c_str(), fields[1].c_str(), fields[4].c_str()) ||
                existing->matches(fields[0].c_str(), fields[1].c_str(), fields[5].c_str())) {
                found = true;
                break;
            }
        }

        if (!found) {
            contacts.add(new Contact(fields[0].c_str(), fields[1].c_str(), fields[2].c_str(),
                                    fields[3].c_str(), fields[4].c_str(), fields[5].c_str()));
        }
    }


        file.close();
    } else if (cmd == "SAVE") {
        std::string filename;
        std::getline(ss, filename);
        if (filename.empty()) {
            std::cerr << "Hiba: Hiányzó fájlnév a SAVE parancsban." << std::endl;
            return;
        }
        fileHandler.saveContacts(filename.c_str(), contacts);
    } else {
        std::cerr << "Hiba: Ismeretlen parancs." << std::endl;
    }
}
