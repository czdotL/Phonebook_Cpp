#include "contactlist.h"
#include <iostream>
#include <cstring>

ContactList::ContactList()
    : contacts(new Contact*[10]), db(0), cap(10) { }


size_t ContactList::getDb() const {
    return db;
}

Contact* ContactList::getContactAt(size_t idx) const {
    if (idx < db)
        return contacts[idx];
    return nullptr;
}


ContactList::~ContactList() {
    for (size_t i = 0; i < db; ++i) {
        delete contacts[i];
    }
    delete[] contacts;
}

void ContactList::expand() {
    size_t newCap = cap * 2;
    Contact** newContacts = new Contact*[newCap];
    for (size_t i = 0; i < db; ++i) {
        newContacts[i] = contacts[i];
    }
    delete[] contacts;
    contacts = newContacts;
    cap = newCap;
}

void ContactList::add(Contact* c) {
    if (db == cap) {
        expand();
    }
    contacts[db++] = c;
}

void ContactList::remove(const char* vn, const char* kn, const char* tel) {
    for (size_t i = 0; i < db; ++i) {
        if (contacts[i]->matches(vn, kn, tel)) {
            delete contacts[i];
            for (size_t j = i; j < db - 1; ++j) {
                contacts[j] = contacts[j + 1];
            }
            --db;
            return;
        }
    }
    std::cerr << "Hiba: Nem található ilyen kontakt!" << std::endl;
}

void ContactList::edit(const char* vn, const char* kn, const char* tel,
                       const char* bn, const char* c, const char* ms, const char* ps) {
    for (size_t i = 0; i < db; ++i) {
        if (contacts[i]->matches(vn, kn, tel)) {
            contacts[i]->update(bn, c, ms, ps);
            return;
        }
    }
    std::cerr << "Hiba: Nem található ilyen kontakt!" << std::endl;
}

void ContactList::list() const {
    for (size_t i = 0; i < db; ++i) {
        contacts[i]->print();
    }
}

void ContactList::search(const char* field, const char* value) const {
    for (size_t i = 0; i < db; ++i) {
        if (strcmp(field, "vezeteknev") == 0 && strcmp(contacts[i]->getVezeteknev(), value) == 0) {
            contacts[i]->print();
        } else if (strcmp(field, "keresztnev") == 0 && strcmp(contacts[i]->getKeresztnev(), value) == 0) {
            contacts[i]->print();
        } else if (strcmp(field, "tel") == 0 &&
                   (strcmp(contacts[i]->getMunkaSzam(), value) == 0 ||
                    strcmp(contacts[i]->getPrivatSzam(), value) == 0)) {
            contacts[i]->print();
        }
    }
}