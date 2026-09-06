#ifndef PHONEBOOKAPP_H
#define PHONEBOOKAPP_H

#include "contactlist.h"
#include "filehandler.h"
#include <string>

class PhoneBookApp {
private:
    ContactList contacts;
    FileHandler fileHandler;

public:
    PhoneBookApp();
    ~PhoneBookApp();

    void run();
    void processCommand(const std::string& command);
};

#endif
