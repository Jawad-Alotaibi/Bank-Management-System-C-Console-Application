#include <iostream>
#include "../HeaderFiles/MyInputLibrary.h"
#include "../HeaderFiles/BankLibrary.h"
#include <string>
#include <fstream>

using namespace std;

void printMenuScreen();
void showTransactionScreen();

struct stClient
{
    string accountNumber;
    string pinCode;
    string name;
    string phone;
    double accountBalance;
    bool markForDelete = false;
};

enum enMainMenuOptions
{
    ShowClientList = 1,
    AddNewClient = 2,
    DeleteClient = 3,
    UpdateClient = 4,
    FindClient = 5,
    Transaction = 6,
    Exit = 7,
};

enum enTransactionsOptions
{
    Deposit = 1,
    Withdraw = 2,
    TotalBalances = 3,
    MainMenu = 4,
};

stClient convertLineToRecord(string line, string delm = "#//#")
{
    stClient client; // declare a structure

    vector<string> vClientData = splitString(line, delm);

    // Validate that we have all required fields
    if (vClientData.size() < 5)
    {
        // Return empty client if line is malformed
        client.accountNumber = "";
        client.pinCode = "";
        client.name = "";
        client.phone = "";
        client.accountBalance = 0;
        return client;
    }

    client.accountNumber = vClientData[0];
    client.pinCode = vClientData[1];
    client.name = vClientData[2];
    client.phone = vClientData[3];

    try
    {
        client.accountBalance = stod(vClientData[4]); // string to double conversion function in c++ called stod
    }
    catch (const invalid_argument &e)
    {
        client.accountBalance = 0;
    }

    return client;
}
vector<stClient> loadClientDataFromFile(string FileName)
{
    fstream file;

    string line = "";
    vector<stClient> vClients;

    file.open(FileName, ios::in);

    if (file.is_open())
    {
        while (getline(file, line))
        {
            vClients.push_back(convertLineToRecord(line));
        }

        file.close();
    }

    return vClients;
}

bool checkAccountNumberExsist(string accountNumber, string fileName)
{
    vector<stClient> vClients = loadClientDataFromFile(fileName);
    for (stClient &c : vClients)
    {
        if (accountNumber == c.accountNumber)
        {
            return true;
        }
    }
    return false;
}

stClient readNewClient()
{
    stClient client;

    cout << "Enter Account Number? ";
    getline(cin >> ws, client.accountNumber); // cleans leftover '\n', then reads, then consumes '\n'  → buffer clean
    while (checkAccountNumberExsist(client.accountNumber, FILENAME))
    {
        cout << "\nClient with Account Number (" << client.accountNumber << ") is already exsist!" << endl;

        cout << "Enter Account Number? ";
        getline(cin >> ws, client.accountNumber); // cleans leftover '\n', then reads, then consumes '\n'  → buffer clean
    }
    cout << "Enter PinCode? ";
    getline(cin, client.pinCode); // reads, then consumes '\n' → buffer clean

    cout << "Enter Name? ";
    getline(cin, client.name); // reads, then consumes '\n' → buffer clean

    cout << "Enter Phone? ";
    getline(cin, client.phone); // reads, then consumes '\n' → buffer clean

    cout << "Enter Account Balance? ";
    cin >> client.accountBalance; // reads value, leaves '\n' ⚠️

    return client;
}
stClient changeClientRecord(string accountNumber)
{
    stClient client;
    client.accountNumber = accountNumber;

    cout << "Enter PinCode? ";
    getline(cin >> ws, client.pinCode); // reads, then consumes '\n' → buffer clean

    cout << "Enter Name? ";
    getline(cin, client.name); // reads, then consumes '\n' → buffer clean

    cout << "Enter Phone? ";
    getline(cin, client.phone); // reads, then consumes '\n' → buffer clean

    cout << "Enter Account Balance? ";
    cin >> client.accountBalance; // reads value, leaves '\n' ⚠️

    return client;
}

string convertRecordToLine(stClient clientData, string delm = "#//#")
{
    // string s1 = "";
    // s1 += clientData.accountNumber + delm;
    // s1 += clientData.pinCode + delm;
    // s1 += clientData.name + delm;
    // s1 += clientData.phone;
    // s1 += to_string(clientData.accountBalance);

    return (string)clientData.accountNumber + delm + clientData.pinCode + delm +
           clientData.name + delm + clientData.phone + delm + to_string(clientData.accountBalance);
    ;
}

void printClientCard(stClient client)
{
    int width = 18; // Adjust this number based on your longest label

    cout << endl
         << "The following are client details" << endl
         << endl;
    cout << left << setw(width) << "Account Number:" << client.accountNumber << endl;
    cout << left << setw(width) << "Pin Code:" << client.pinCode << endl;
    cout << left << setw(width) << "Name:" << client.name << endl;
    cout << left << setw(width) << "Phone:" << client.phone << endl;
    cout << left << setw(width) << "Account Balance:" << client.accountBalance << endl;
}

void addClientToFile(string fileName, string line)
{
    fstream file;
    file.open(FILENAME, ios::out | ios::app);

    if (file.is_open())
    {
        file << line << endl;
    }
    file.close();
}

void addNewClient()
{
    stClient client;
    client = readNewClient();
    addClientToFile(FILENAME, convertRecordToLine(client));
}
void addClients()
{
    char wannaAddUser = 'y';

    do
    {
        addNewClient();
        cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";
        cin >> wannaAddUser;
    } while (toupper(wannaAddUser) == 'Y');
}

void printAllClientsHeader(int clientsNumber)
{
    cout << "________________________________________________________________________________________" << endl;
    cout << "\t\tClients list (" << clientsNumber << ") Client(s)." << endl;
    cout << "________________________________________________________________________________________" << endl;
}

void printTotalBalancesHeader(int clientsNumber)
{
    cout << "________________________________________________________________________________________" << endl;
    cout << "\t\tBalances list (" << clientsNumber << ") Client(s)." << endl;
    cout << "________________________________________________________________________________________" << endl;
}

void printClientRecord(stClient client)
{
    cout << "| " << left << setw(10) << client.accountNumber;
    cout << "| " << left << setw(10) << client.pinCode;
    cout << "| " << left << setw(40) << client.name;
    cout << "| " << left << setw(10) << client.phone;
    cout << "| " << left << setw(10) << client.accountBalance;
}

void printTotalBalanceRecord(stClient client)
{
    cout << "| " << left << setw(10) << client.accountNumber;
    cout << "| " << left << setw(40) << client.name;
    cout << "| " << left << setw(10) << client.accountBalance;
}
void printClientsDetails(vector<stClient> clients)
{

    cout << "| Account Number";
    cout << " | Pin Code";
    cout << left << setw(40) << " | Client Name";
    cout << left << setw(10) << " | Phone";
    cout << left << setw(10) << " | Balance";
    cout << endl
         << "________________________________________________________________________________________" << endl;

    for (stClient &client : clients)
    {
        printClientRecord(client);
        cout << endl;
    }
}

void printTotalBalancesDetails(vector<stClient> clients)
{
    int totalBalances = 0;
    cout << "| Account Number";
    cout << left << setw(40) << " | Client Name";
    cout << left << setw(10) << " | Balance";
    cout << endl
         << "________________________________________________________________________________________" << endl;

        for (stClient &client : clients)
        {
            printTotalBalanceRecord(client);
            totalBalances += client.accountBalance;
            cout << endl;
        }

        cout << "\n\t\tTotal Balances = " << totalBalances << endl;
}

void printAllClients(vector<stClient> clients)
{
    
    printAllClientsHeader(clients.size());
    printClientsDetails(clients);
}

void printTotalBalancesClients(vector<stClient> clients)
{
    if (clients.size() == 0)
    {
        cout << "No Clients Available in the system" << endl;
        return;
    }
    printTotalBalancesHeader(clients.size());
    printTotalBalancesDetails(clients);
}

bool findClientByAccountNumber(string accountNumber, stClient &client)
{
    vector<stClient> vClients = loadClientDataFromFile(FILENAME);

    for (stClient &c : vClients)
    {
        if (c.accountNumber == accountNumber)
        {
            client = c;
            return true;
        }
    }
    return false;
}

bool findClientByAccountNumberWithoutLoadingFromFile(string accountNumber, vector<stClient> vClients, stClient &client)
{
    for (stClient &c : vClients)
    {
        if (c.accountNumber == accountNumber)
        {
            client = c;
            return true;
        }
    }
    return false;
}

void saveClientsToFile(string FileName, vector<stClient> vClients)
{
    fstream file;
    file.open(FileName, ios::out); // Open in output mode to overwrite the file

    if (file.is_open())
    {
        for (stClient &client : vClients)
        {
            file << convertRecordToLine(client) << endl;
        }
        file.close();
    }
}

void saveClientsMarkedToDeleteToFile(string fileName, vector<stClient> vClients)
{
    fstream file;
    file.open(FILENAME, ios::out); // Open in output mode to overwrite the file

    if (file.is_open())
    {
        for (stClient &client : vClients)
        {
            if (client.markForDelete == false)
            {
                file << convertRecordToLine(client) << endl;
            }
        }
        file.close();
    }
}

bool markClientForDeleteByAccountNumber(string accountNumber, vector<stClient> &vClients)
{
    for (stClient &c : vClients)
    {
        if (c.accountNumber == accountNumber)
        {
            c.markForDelete = true;
            return true;
        }
    }
    return false;
}

bool deleteClientByAccountNumber(string accountNumber, vector<stClient> &vClients)
{
    stClient client;
    char answer = 'n';

    if (findClientByAccountNumberWithoutLoadingFromFile(accountNumber, vClients, client))
    {
        printClientCard(client);

        cout << "\n\nAre you sure you want to delete this client with this account Number " << client.accountNumber << " y/n ?";
        cin >> answer;

        if (toupper(answer) == 'Y')
        {
            // Mark client for delete
            markClientForDeleteByAccountNumber(accountNumber, vClients);
            saveClientsMarkedToDeleteToFile(FILENAME, vClients);

            // Refresh the vector with the new clients without the clients marked for delete
            vClients = loadClientDataFromFile(FILENAME);
            cout << "\n\nClient Deleted Successfully." << endl;
        }
        else
            cout << "Deleting Was Canceld\n";
        return false;
    }
    else
        cout << "Client with Account Number (" << accountNumber << ") Not Found!" << endl;

    return false;
}

void clearConsole()
{
    cout << "\033[2J\033[1;1H";
    // system("clear");
}

void getBackToTransactionsScreen()
{
    cout << "\nPress any key to get Back to Transactions Menu...";
    cin.ignore();
    cin.get();
    showTransactionScreen();
}

void getBackToMenuScreen()
{
    cout << "\nPress any key to get Back to Main Menu...";
    cin.ignore();
    cin.get();
    printMenuScreen();
}
bool updateClientByAccountNumber(string accountNumber, vector<stClient> &vClients)
{
    stClient client;
    char answer = 'n';

    if (findClientByAccountNumberWithoutLoadingFromFile(accountNumber, vClients, client))
    {
        printClientCard(client);

        cout << "Are you sure you wanna update this client? Y/N" << endl
             << endl;
        cin >> answer;

        if (toupper(answer) == 'Y')
        {
            for (stClient &c : vClients)
            {
                if (c.accountNumber == accountNumber)
                {
                    c = changeClientRecord(accountNumber);
                    break;
                }
            }
            saveClientsToFile(FILENAME, vClients);
            cout << "\n\nClient Updates Successfully." << endl;
            return true;
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << accountNumber
             << ") is Not Found!" << endl;
    }
    return false;
}
void showDeleteScreen()
{
    cout << "===============================================================================" << endl;
    cout << "\t\tDelete Client Screen\n";
    cout << "===============================================================================" << endl;
    vector<stClient> vClients = loadClientDataFromFile(FILENAME);
    string accountNumber = MyInputLibrary::readString("Please Account Number? ");
    deleteClientByAccountNumber(accountNumber, vClients);
}

void showUpdateScreen()
{
    cout << "===============================================================================" << endl;
    cout << "\t\tUpdate Client Screen\n";
    cout << "===============================================================================" << endl;
    vector<stClient> vClients = loadClientDataFromFile(FILENAME);
    string accountNumber = MyInputLibrary::readString("Please Account Number? ");
    updateClientByAccountNumber(accountNumber, vClients);
}

void showClientsScreen()
{
    vector<stClient> vClients = loadClientDataFromFile(FILENAME);
    printAllClients(vClients);
}

void showTotalBalancesScreen()
{
    vector<stClient> vClients = loadClientDataFromFile(FILENAME);
    printTotalBalancesClients(vClients);
}

void addClientsScreen()
{
    cout << "===============================================================================" << endl;
    cout << "\t\tAdd Client Screen\n";
    cout << "===============================================================================" << endl;
    addClients();
}

void showfindClientScreen()
{

    cout << "===============================================================================" << endl;
    cout << "\t\tFind Client Screen\n";
    cout << "===============================================================================" << endl;
    stClient client;
    string accountNumber = MyInputLibrary::readString("Please Enter Account Number? ");
    if (findClientByAccountNumber(accountNumber, client))
    {
        printClientCard(client);
    }
    else
    {
        cout << "\nClient with Account Number (" << accountNumber
             << ") is Not Found!" << endl;
    }
}

void deposiByAccountNumber(double amount, string accountNumber, vector<stClient> &vClients)
{

    char performTransaction;
    cout << "\n\n ARE YOU SURE YOU WANNA PERFORM THIS TRANSACITON? y/n ";
    cin >> performTransaction;
    if (toupper(performTransaction) == 'Y')
    {
        for (stClient &client : vClients)
        {
            if (accountNumber == client.accountNumber)
            {
                client.accountBalance += amount;
                cout << "Done Successfully, new balance " << client.accountBalance << ".\n";
                break;
            }
        }
        saveClientsToFile(FILENAME, vClients);
    }
}

void showDespositScreen()
{
    cout << "===============================================================================" << endl;
    cout << "\t\tDeposit Screen\n";
    cout << "===============================================================================" << endl;

    vector<stClient> vClients = loadClientDataFromFile(FILENAME);
    stClient client;
    string accountNumber = MyInputLibrary::readString("Enter The Account Number you wanna Deposit ");
    while (!findClientByAccountNumber(accountNumber, client))
    {
        cout << "Client with [" << accountNumber << "] Does not exsists.\n";

        accountNumber = MyInputLibrary::readString("Enter The Account Number you wanna Deposit");
    }

    printClientCard(client);

    double amount = stod(MyInputLibrary::readString("Enter the deposit amount? "));
    deposiByAccountNumber(amount, accountNumber, vClients);

    getBackToTransactionsScreen();
}

void showWithdrawScreen()
{
    cout << "===============================================================================" << endl;
    cout << "\t\tWithdraw Screen\n";
    cout << "===============================================================================" << endl;

    vector<stClient> vClients = loadClientDataFromFile(FILENAME);
    stClient client;
    string accountNumber = MyInputLibrary::readString("Enter The Account Number you wanna withdraw ");
    // validate that the account number exsist
    while (!findClientByAccountNumber(accountNumber, client))
    {
        cout << "Client with [" << accountNumber << "] Does not exsists.\n";

        accountNumber = MyInputLibrary::readString("Enter The Account Number you wanna withdraw ");
    }

    printClientCard(client);

    double amount = stod(MyInputLibrary::readString("Enter the withdraw amount? "));
    while (amount > client.accountBalance)
    {
        amount = stod(MyInputLibrary::readString("Amount exceeds the balance, you can withdraw up to :  " + to_string(client.accountBalance) + "\nEnter valid amount "));
    }
    deposiByAccountNumber(amount * -1, accountNumber, vClients);
    getBackToTransactionsScreen();
}

void listTotalBalances()
{
}

void switchingBetweenTransactionScreens(enTransactionsOptions option)
{
    switch (option)
    {
    case enTransactionsOptions::Deposit:
        clearConsole();
        showDespositScreen();
        getBackToTransactionsScreen();
        break;
    case enTransactionsOptions::Withdraw:
        clearConsole();
        showWithdrawScreen();
        getBackToTransactionsScreen();
        break;
    case enTransactionsOptions::TotalBalances:
        clearConsole();
        showTotalBalancesScreen();
        getBackToTransactionsScreen();
        break;
    case enTransactionsOptions::MainMenu:
        clearConsole();
        printMenuScreen();
        break;

    default:
        cout << "Your Enter Wrong Choice enter valid choice from the menu" << endl;
        getBackToTransactionsScreen();
        break;
    }
}
void showTransactionScreen()
{
    clearConsole();
    cout << "===============================================================================" << endl;
    cout << "\t\tTransactions Menu Screen\n";
    cout << "===============================================================================" << endl;
    cout << "[1] Deposit." << endl;
    cout << "[2] Withdraw." << endl;
    cout << "[3]Total Balances." << endl;
    cout << "[4] Main Menu." << endl;
    cout << "===============================================================================" << endl;
    enTransactionsOptions option = (enTransactionsOptions)MyInputLibrary::readInRange(1, 4, "Please Enter Number between [1 to 4]?");
    switchingBetweenTransactionScreens(option);
}

void showExitScreen()
{
    cout << "===============================================================================" << endl;
    cout << "\t\tProgram Ends Hope to See you again):\n";
    cout << "===============================================================================" << endl;
}

void switchingBetweenMainMenuScreens(enMainMenuOptions option)
{
    switch (option)
    {
    case enMainMenuOptions::ShowClientList:
        clearConsole();
        showClientsScreen();
        getBackToMenuScreen();

        break;
    case enMainMenuOptions::AddNewClient:
        clearConsole();
        addClientsScreen();
        getBackToMenuScreen();
        break;
    case enMainMenuOptions::DeleteClient:
        clearConsole();
        showDeleteScreen();
        getBackToMenuScreen();

        break;
    case enMainMenuOptions::UpdateClient:
        clearConsole();
        showUpdateScreen();
        getBackToMenuScreen();

        break;
    case enMainMenuOptions::FindClient:
        clearConsole();
        showfindClientScreen();
        getBackToMenuScreen();
        break;
    case enMainMenuOptions::Transaction:
        clearConsole();
        showTransactionScreen();
        getBackToMenuScreen();
        break;
    case enMainMenuOptions::Exit:
        clearConsole();
        showExitScreen();
        break;
    default:
        cout << "Invalid Option\n";
        break;
    }
}
void printMenuScreen()
{
    clearConsole();
    cout << "===============================================================================" << endl;
    cout << "\t\tMain Menu Screen\n";
    cout << "===============================================================================" << endl;
    cout << "[1] Show Client List." << endl;
    cout << "[2] Add New Client." << endl;
    cout << "[3] Delete Client." << endl;
    cout << "[4] Update Client." << endl;
    cout << "[5] Find Client." << endl;
    cout << "[6] Transactions." << endl;
    cout << "[7] Exit." << endl;
    cout << "===============================================================================" << endl;
    enMainMenuOptions option = (enMainMenuOptions)MyInputLibrary::readInRange(1, 7, "Please Enter Number between [1 to 7]?");
    switchingBetweenMainMenuScreens(option);
}

int main()
{
    printMenuScreen();
}
