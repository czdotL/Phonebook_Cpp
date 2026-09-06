#ifndef CONTACT_H
#define CONTACT_H

#include <cstddef>

class Contact {
private:
    char* vezeteknev;
    char* keresztnev;
    char* becenev;
    char* cim;
    char* munka_szam;
    char* privat_szam;

public:
    Contact(const char* vn, const char* kn, const char* bn, const char* c, const char* ms, const char* ps);
    ~Contact();

    void print() const;
    void toCSV(char* buffer, size_t size) const;
    void update(const char* bn, const char* c, const char* ms, const char* ps);
    bool matches(const char* vn, const char* kn, const char* tel) const;

    const char* getVezeteknev() const;
    const char* getKeresztnev() const;
    const char* getMunkaSzam() const;
    const char* getPrivatSzam() const;
};

#endif
