#include "filehandler.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>

FileHandler::FileHandler() {}
FileHandler::~FileHandler() {}

void FileHandler::loadContacts(const char* filename, ContactList& list) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Hiba: Nem sikerult megnyitni a fajlt: " << filename << std::endl;
        return;
    }

    std::string line;
while (std::getline(file, line)) {
    if (line.empty()) continue; // üres sor kihagyása

    std::stringstream ss(line);
    std::string fields[6];
    Contact* c = nullptr;  // <<< ide került a deklaráció

    for (int i = 0; i < 6; ++i) {
        if (!std::getline(ss, fields[i], ',')) {
            std::cerr << "Hiba: Hibas mezoszam! 6 mezo elvart." << std::endl;
            goto next_line;
        }
    }

    // Ellenőrizzük, hogy van-e legalább egy telefonszám
    if (fields[4].empty() && fields[5].empty()) {
        std::cerr << "Hiba: Legalabb egy telefonszamot meg kell adni!" << std::endl;
        goto next_line;
    }

    // Allokalas es hozzaadas
    c = new Contact(fields[0].c_str(), fields[1].c_str(), fields[2].c_str(),
                    fields[3].c_str(), fields[4].c_str(), fields[5].c_str());
    list.add(c);

next_line:
    continue;
}
    file.close();
}

void FileHandler::saveContacts(const char* filename, const ContactList& list) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Hiba: Nem sikerult megnyitni a fajlt: " << filename << std::endl;
        return;
    }

    char buffer[512];
    for (size_t i = 0; i < list.getDb(); ++i) {
        Contact* c = list.getContactAt(i);
        if (c) {
            c->toCSV(buffer, sizeof(buffer));
            file << buffer << "\n";
        }
    }
    file.close();
}