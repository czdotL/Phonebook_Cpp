#ifndef CONTACTLIST_H
#define CONTACTLIST_H

#include "contact.h"
#include <cstddef>

class ContactList {
private:
    Contact** contacts;
    size_t db;
    size_t cap;

    void expand();

public:
    ContactList();
    ~ContactList();

    size_t getDb() const;
    Contact* getContactAt(size_t idx) const;

    void add(Contact* c);
    void remove(const char* vn, const char* kn, const char* tel);
    void edit(const char* vn, const char* kn, const char* tel,
              const char* bn, const char* c, const char* ms, const char* ps);
    void list() const;
    void search(const char* field, const char* value) const;
};

#endif
