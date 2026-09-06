#include "contact.h"
#include <iostream>
#include <cstring>
#include <cstdio>

namespace {
    char* copyStr(const char* src) {
        if (!src) return nullptr;
        size_t len = std::strlen(src) + 1;
        char* dest = new char[len];
        std::strcpy(dest, src);
        return dest;
    }
}

Contact::Contact(const char* vn, const char* kn, const char* bn, const char* c, const char* ms, const char* ps) {
    vezeteknev = copyStr(vn);
    keresztnev = copyStr(kn);
    becenev = copyStr(bn);
    cim = copyStr(c);
    munka_szam = copyStr(ms);
    privat_szam = copyStr(ps);
}

Contact::~Contact() {
    delete[] vezeteknev;
    delete[] keresztnev;
    delete[] becenev;
    delete[] cim;
    delete[] munka_szam;
    delete[] privat_szam;
}

void Contact::print() const {
    std::cout << "Nev: " << vezeteknev << " " << keresztnev
              << ", Becenev: " << becenev
              << ", Cim: " << cim
              << ", Munka: " << munka_szam
              << ", Privat: " << privat_szam
              << std::endl;
}

void Contact::toCSV(char* buffer, size_t size) const {
    std::snprintf(buffer, size, "%s,%s,%s,%s,%s,%s",
                  vezeteknev, keresztnev, becenev, cim, munka_szam, privat_szam);
}

void Contact::update(const char* bn, const char* c, const char* ms, const char* ps) {
    if (bn && bn[0] != '\0') {
        delete[] becenev;
        becenev = copyStr(bn);
    }
    if (c && c[0] != '\0') {
        delete[] cim;
        cim = copyStr(c);
    }
    if (ms && ms[0] != '\0') {
        delete[] munka_szam;
        munka_szam = copyStr(ms);
    }
    if (ps && ps[0] != '\0') {
        delete[] privat_szam;
        privat_szam = copyStr(ps);
    }
}


bool Contact::matches(const char* vn, const char* kn, const char* tel) const {
    if (strcmp(vezeteknev, vn) != 0 || strcmp(keresztnev, kn) != 0)
        return false;

    if (tel == nullptr || tel[0] == '\0')  // üres telefonszám ne egyezzen
        return false;

    return strcmp(munka_szam, tel) == 0 || strcmp(privat_szam, tel) == 0;
}

const char* Contact::getVezeteknev() const {
    return vezeteknev;
}

const char* Contact::getKeresztnev() const {
    return keresztnev;
}

const char* Contact::getMunkaSzam() const {
    return munka_szam;
}

const char* Contact::getPrivatSzam() const {
    return privat_szam;
}