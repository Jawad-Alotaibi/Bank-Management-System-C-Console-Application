# Bank Management System

A console-based bank management system built in C++ as part of Course 7. Manages client records and bank transactions through a menu-driven interface, with all data persisted in a flat text file using a custom `#//#` delimiter format.

---

## Main Menu

| Option | Description |
|--------|-------------|
| [1] Show Client List | Display all clients in a formatted table |
| [2] Add New Client | Add a client with unique account number validation |
| [3] Delete Client | Confirm and permanently remove a client record |
| [4] Update Client | Overwrite a client's details and save changes |
| [5] Find Client | Search by account number and view client card |
| [6] Transactions | Open the transactions menu |
| [7] Exit | Close the program |

## Transactions Menu

| Option | Description |
|--------|-------------|
| [1] Deposit | Add funds to a client's account |
| [2] Withdraw | Deduct funds with balance validation |
| [3] Total Balances | View all accounts with a combined total |
| [4] Main Menu | Return to the main menu |

---

## Client Record Structure

Each record is serialized using `#//#` as a delimiter:

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

## Course

**Course 7** — Programming Advices by Mohammed Abu-Hadhoud
