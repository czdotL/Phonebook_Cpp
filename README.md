# Phone Book Application

A simple, command-line phone book manager written in C++ as homework (NHF4) for the *Fundamentals of Programming 2.* course. The program reads commands from standard input, manipulates an in-memory contact list, and can load/save contacts from/to CSV files. No STL containers are used — all dynamic data structures (arrays, strings) are managed manually with `new[]`/`delete[]`.

Full design documentation (task specification, class design, diagram, algorithms, testing notes) is available in [`docs/DOCUMENTATION.md`](docs/DOCUMENTATION.md).

## Features

- `ADD` — add a new contact (last name, first name, nickname, address, work number, private number)
- `DELETE` — delete a contact by exact name + phone number match
- `EDIT` — update selected fields of an existing contact
- `LIST` — print all contacts
- `SEARCH` — search contacts by name or phone number
- `LOAD` — import contacts from a CSV file
- `SAVE` — export contacts to a CSV file
- Duplicate detection on `ADD` and `LOAD`
- Robust error handling: all errors are written to `stderr`, normal output to `stdout`

See [`docs/DOCUMENTATION.md`](docs/DOCUMENTATION.md) for the exact command syntax and CSV format.

## Building

The project is plain C++ with no external dependencies beyond the standard library. Headers live in `include/`, implementation files in `src/`, so point the compiler at both with `-Iinclude`:

```bash
g++ -std=c++17 -Wall -Iinclude -o phonebook src/main.cpp src/phonebookapp.cpp src/contactlist.cpp src/contact.cpp src/filehandler.cpp
```

## Running

Commands are read from standard input, so the program can be used interactively or in batch mode:

```bash
./phonebook < examples/standard_input.txt
```

Or interactively:

```bash
./phonebook
ADD Smith,John,,,+3611234567,
LIST
```

## Memory-leak checking

`memtrace.h` / `memtrace.cpp` provide a lightweight allocation tracker used during development to verify that every `new[]` is matched by a `delete[]`.

## Repository structure

```
.
├── include/                 # public headers
│   ├── contact.h
│   ├── contactlist.h
│   ├── filehandler.h
│   ├── phonebookapp.h
│   └── memtrace.h
├── src/                      # implementation files
│   ├── contact.cpp
│   ├── contactlist.cpp
│   ├── filehandler.cpp
│   ├── phonebookapp.cpp
│   ├── memtrace.cpp
│   └── main.cpp
├── tests/                    # unit tests (gtest_lite based)
│   └── gtest_lite.h
├── examples/                 # sample batch input
│   └── standard_input.txt
├── docs/
│   ├── DOCUMENTATION.md
│   └── specifikáció.pdf     # original Hungarian specification
├── .gitignore
└── README.md
```

> Note: `prog` (the compiled binary) should not be committed to the repository — it is excluded via `.gitignore`; rebuild it locally instead. A `tests/main_test.cpp` file exercising `ContactList` with `gtest_lite` is referenced in the specification but not yet part of this repository.

## License

Educational project — no license specified.
"# Phonebook" 
