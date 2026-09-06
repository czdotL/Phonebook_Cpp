#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "contactlist.h"

class FileHandler {
public:
    FileHandler();
    ~FileHandler();

    void loadContacts(const char* filename, ContactList& list);
    void saveContacts(const char* filename, const ContactList& list) const;
};

#endif
