#include <bits/stdc++.h>
using namespace std;
const string ClientsFileName = "Clients.txt";

void ShowMainMenu();
void ShowTransactionsMenu();

struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;
};

vector<string> SplitString(string S1, string Delim)
{

    vector<string> vString;

    short pos = 0;
    string sWord; // define a string variable

    // use find() function to get the position of the delimiters
    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos); // store the word
        if (sWord != "")
        {
            vString.push_back(sWord);
        }

        S1.erase(0, pos + Delim.length()); /* erase() until position and move to next word. */
    }

    if (S1 != "")
    {
        vString.push_back(S1); // it adds last word of the string.
    }

    return vString;
}

sClient ConvertLinetoRecord(string Line, string Separator = "#//#")
{

    sClient Client;
    vector<string> vClientData;

    vClientData = SplitString(Line, Separator);

    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]); // cast string to double

    return Client;
}

string ConvertRecordToLine(sClient Client, string Separator = "#//#")
{

    string stClientRecord = "";

    stClientRecord += Client.AccountNumber + Separator;
    stClientRecord += Client.PinCode + Separator;
    stClientRecord += Client.Name + Separator;
    stClientRecord += Client.Phone + Separator;
    stClientRecord += to_string(Client.AccountBalance);

    return stClientRecord;
}

bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{

    vector<sClient> vClients;

    fstream MyFile;
    MyFile.open(FileName, ios::in); // read Mode

    if (MyFile.is_open())
    {

        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {

            Client = ConvertLinetoRecord(Line);
            if (Client.AccountNumber == AccountNumber)
            {
                MyFile.close();
                return true;
            }

            vClients.push_back(Client);
        }

        MyFile.close();
    }

    return false;
}

sClient ReadNewClient()
{
    sClient Client;

    cout << "Enter Account Number? ";

    getline(cin >> ws, Client.AccountNumber);

    while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName))
    {
        cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Account Number? ";
        getline(cin >> ws, Client.AccountNumber);
    }

    cout << "Enter PinCode? ";
    getline(cin, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;
}

vector<sClient> LoadClientsDataFromFile(string FileName)
{

    vector<sClient> vClients;

    fstream MyFile;
    MyFile.open(FileName, ios::in); // read Mode

    if (MyFile.is_open())
    {

        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {

            Client = ConvertLinetoRecord(Line);

            vClients.push_back(Client);
        }

        MyFile.close();
    }

    return vClients;
}

void PrintClientRecordLine(sClient Client)
{

    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}

void PrintClientRecordBalanceLine(sClient Client)
{

    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}

void ShowAllClientsScreen()
{

    vector<sClient> vClients = LoadClientsDataFromFile(ClientsFileName);

    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;

    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;

    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else

        for (sClient Client : vClients)
        {

            PrintClientRecordLine(Client);
            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;
}

void ShowTotalBalances()
{

    vector<sClient> vClients = LoadClientsDataFromFile(ClientsFileName);

    cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;

    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;

    double TotalBalances = 0;

    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else

        for (sClient Client : vClients)
        {

            PrintClientRecordBalanceLine(Client);
            TotalBalances += Client.AccountBalance;

            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;
    cout << "\t\t\t\t\t   Total Balances = " << TotalBalances;
}

void PrintClientCard(sClient Client)
{
    cout << "\nThe following are the client details:\n";
    cout << "-----------------------------------";
    cout << "\nAccount Number: " << Client.AccountNumber;
    cout << "\nPin Code     : " << Client.PinCode;
    cout << "\nName         : " << Client.Name;
    cout << "\nPhone        : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.AccountBalance;
    cout << "\n-----------------------------------\n";
}

bool FindClientByAccountNumber(string AccountNumber, vector<sClient> vClients, sClient &Client)
{

    for (sClient C : vClients)
    {

        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }
    return false;
}

sClient ChangeClientRecord(string AccountNumber)
{
    sClient Client;

    Client.AccountNumber = AccountNumber;

    cout << "\n\nEnter PinCode? ";
    getline(cin >> ws, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector<sClient> &vClients)
{

    for (sClient &C : vClients)
    {

        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }
    }

    return false;
}

vector<sClient> SaveClientsDataToFile(string FileName, vector<sClient> vClients)
{

    fstream MyFile;
    MyFile.open(FileName, ios::out); // overwrite

    string DataLine;

    if (MyFile.is_open())
    {

        for (sClient C : vClients)
        {

            if (C.MarkForDelete == false)
            {
                // we only write records that are not marked for delete.
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;
            }
        }

        MyFile.close();
    }

    return vClients;
}

void AddDataLineToFile(string FileName, string stDataLine)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {

        MyFile << stDataLine << endl;

        MyFile.close();
    }
}

void AddNewClient()
{
    sClient Client;
    Client = ReadNewClient();
    AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));
}

void AddNewClients()
{
    char AddMore = 'Y';
    do
    {
        // system("cls");
        cout << "Adding New Client:\n\n";

        AddNewClient();
        cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";

        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');
}

bool DeleteClientByAccountNumber(string AccountNumber, vector<sClient> &vClients)
{

    sClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {

        PrintClientCard(Client);

        cout << "\n\nAre you sure you want delete this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
            SaveClientsDataToFile(ClientsFileName, vClients);

            // Refresh Clients
            vClients = LoadClientsDataFromFile(ClientsFileName);

            cout << "\n\nClient Deleted Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }
}

bool UpdateClientByAccountNumber(string AccountNumber, vector<sClient> &vClients)
{

    sClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {

        PrintClientCard(Client);
        cout << "\n\nAre you sure you want update this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {

            for (sClient &C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }
            }

            SaveClientsDataToFile(ClientsFileName, vClients);

            cout << "\n\nClient Updated Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }
}

bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector<sClient> &vClients)
{

    char Answer = 'n';

    cout << "\n\nAre you sure you want perfrom this transaction? y/n ? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {

        for (sClient &C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance += Amount;
                SaveClientsDataToFile(ClientsFileName, vClients);
                cout << "\n\nDone Successfully. New balance is: " << C.AccountBalance;

                return true;
            }
        }

        return false;
    }
}

string ReadClientAccountNumber()
{
    string AccountNumber = "";

    cout << "\nPlease enter AccountNumber? ";
    cin >> AccountNumber;
    return AccountNumber;
}

void ShowDeleteClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDelete Client Screen";
    cout << "\n-----------------------------------\n";

    vector<sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    DeleteClientByAccountNumber(AccountNumber, vClients);
}

void ShowUpdateClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate Client Info Screen";
    cout << "\n-----------------------------------\n";

    vector<sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    UpdateClientByAccountNumber(AccountNumber, vClients);
}

void ShowAddNewClientsScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tAdd New Clients Screen";
    cout << "\n-----------------------------------\n";

    AddNewClients();
}

void ShowFindClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tFind Client Screen";
    cout << "\n-----------------------------------\n";

    vector<sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
    sClient Client;
    string AccountNumber = ReadClientAccountNumber();
    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
        PrintClientCard(Client);
    else
        cout << "\nClient with Account Number[" << AccountNumber << "] is not found!";
}

void ShowEndScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tProgram Ends :-)";
    cout << "\n-----------------------------------\n";
}

void ShowDepositScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDeposit Screen";
    cout << "\n-----------------------------------\n";

    sClient Client;

    vector<sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();

    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
        AccountNumber = ReadClientAccountNumber();
    }

    PrintClientCard(Client);

    double Amount = 0;
    cout << "\nPlease enter deposit amount? ";
    cin >> Amount;

    DepositBalanceToClientByAccountNumber(AccountNumber, Amount, vClients);
}

void ShowWithDrawScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tWithdraw Screen";
    cout << "\n-----------------------------------\n";

    sClient Client;

    vector<sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();

    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
        AccountNumber = ReadClientAccountNumber();
    }

    PrintClientCard(Client);

    double Amount = 0;
    cout << "\nPlease enter withdraw amount? ";
    cin >> Amount;

    // Validate that the amount does not exceeds the balance
    while (Amount > Client.AccountBalance)
    {
        cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance << endl;
        cout << "Please enter another amount? ";
        cin >> Amount;
    }

    DepositBalanceToClientByAccountNumber(AccountNumber, Amount * -1, vClients);
}

void ShowTotalBalancesScreen()
{

    ShowTotalBalances();
}

enum enTransactionsMenuOptions
{
    eDeposit = 1,
    eWithdraw = 2,
    eShowTotalBalance = 3,
    eShowMainMenu = 4
};

enum enMainMenuOptions
{
    eListClients = 1,
    eAddNewClient = 2,
    eDeleteClient = 3,
    eUpdateClient = 4,
    eFindClient = 5,
    eShowTransactionsMenu = 6,
    eExit = 7
};

void GoBackToMainMenu()
{
    cout << "\n\nPress any key to go back to Main Menu...";
    system("pause>0");
    ShowMainMenu();
}
void GoBackToTransactionsMenu()
{
    cout << "\n\nPress any key to go back to Transactions Menu...";
    system("pause>0");
    ShowTransactionsMenu();
}
short ReadTransactionsMenuOption()
{
    cout << "Choose what do you want to do? [1 to 4]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}

void PerfromTransactionsMenuOption(enTransactionsMenuOptions TransactionMenuOption)
{
    switch (TransactionMenuOption)
    {
    case enTransactionsMenuOptions::eDeposit:
    {
        system("cls");
        ShowDepositScreen();
        GoBackToTransactionsMenu();
        break;
    }

    case enTransactionsMenuOptions::eWithdraw:
    {
        system("cls");
        ShowWithDrawScreen();
        GoBackToTransactionsMenu();
        break;
    }

    case enTransactionsMenuOptions::eShowTotalBalance:
    {
        system("cls");
        ShowTotalBalancesScreen();
        GoBackToTransactionsMenu();
        break;
    }

    case enTransactionsMenuOptions::eShowMainMenu:
    {

        ShowMainMenu();
    }
    }
}

void ShowTransactionsMenu()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tTransactions Menu Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Deposit.\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] Total Balances.\n";
    cout << "\t[4] Main Menu.\n";
    cout << "===========================================\n";
    PerfromTransactionsMenuOption((enTransactionsMenuOptions)ReadTransactionsMenuOption());
}

short ReadMainMenuOption()
{
    cout << "Choose what do you want to do? [1 to 7]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}

void PerfromMainMenuOption(enMainMenuOptions MainMenuOption)
{
    switch (MainMenuOption)
    {
    case enMainMenuOptions::eListClients:
    {
        system("cls");
        ShowAllClientsScreen();
        GoBackToMainMenu();
        break;
    }
    case enMainMenuOptions::eAddNewClient:
        system("cls");
        ShowAddNewClientsScreen();
        GoBackToMainMenu();
        break;

    case enMainMenuOptions::eDeleteClient:
        system("cls");
        ShowDeleteClientScreen();
        GoBackToMainMenu();
        break;

    case enMainMenuOptions::eUpdateClient:
        system("cls");
        ShowUpdateClientScreen();
        GoBackToMainMenu();
        break;

    case enMainMenuOptions::eFindClient:
        system("cls");
        ShowFindClientScreen();
        GoBackToMainMenu();
        break;

    case enMainMenuOptions::eShowTransactionsMenu:
        system("cls");
        ShowTransactionsMenu();
        break;

    case enMainMenuOptions::eExit:
        system("cls");
        ShowEndScreen();
        break;
    }
}

void ShowMainMenu()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tMain Menu Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Transactions.\n";
    cout << "\t[7] Exit.\n";
    cout << "===========================================\n";
    PerfromMainMenuOption((enMainMenuOptions)ReadMainMenuOption());
}

int main()

{
    ShowMainMenu();
    system("pause>0");
    return 0;
}
