# Bank Management System

A console-based bank management system built in C++ as part of Course 7. The program manages client records through a menu-driven interface, with all data persisted in a flat text file using a custom `#//#` delimiter format.

---

## Features

| Option | Description |
|--------|-------------|
| [1] Show Client List | Display all clients in a formatted table |
| [2] Add New Client | Add a client with unique account number validation |
| [3] Delete Client | Confirm and permanently remove a client record |
| [4] Update Client | Overwrite a client's details and save changes |
| [5] Find Client | Search by account number and view client card |
| [6] Exit | Close the program |

---

## Client Record Structure

Each record stores the following fields, serialized using `#//#` as a delimiter:

```
AccountNumber #//# PinCode #//# Name #//# Phone #//# Balance
```

---

## Project Structure

```
BankSystem/
├── main.cpp
├── HeaderFiles/
│   ├── BankLibrary.h
│   └── MyInputLibrary.h
└── Clients.txt
```

---

## How to Run

```bash
g++ main.cpp -o BankSystem
./BankSystem
```

---

## Coming Soon — Transactions Menu

The next version will introduce a dedicated transactions screen with **Deposit** and **Withdraw** operations, allowing real-time balance updates persisted directly to the file.

---

## Course

**Course 7** — Programming Advices by Mohammed Abu-Hadhoud
