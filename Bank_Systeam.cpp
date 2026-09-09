#include <bits/stdc++.h>
using namespace std;
const string ClientsFileName = "Clients.txt";
const string UserFileName = "Users.txt";
enum enPermission
{
    epAdmin = -1,
    epShowClients = 1,
    epAddClient = 2,
    epDeleteClient = 4,
    epUpdateClient = 8,
    epFindClient = 16,
    epTransactions = 32,
    epManageUsers = 64

};

void ShowMainMenu();
void ShowTransactionsMenu();
void ShowMangeUsersMenu();

struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;
};

struct sUsers
{
    string UserName;
    string PassWord;
    short Access;
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

sUsers ConvertLinetoRecordUsers(string Line, string Separator = "#//#")
{

    sUsers User;
    vector<string> vUserData;

    vUserData = SplitString(Line, Separator);

    User.UserName = vUserData[0];
    User.PassWord = vUserData[1];
    User.Access = stoi(vUserData[2]);

    return User;
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
string ConvertRecordToLineUsers(sUsers User, string Separator = "#//#")
{

    string stClientRecord = "";

    stClientRecord += User.UserName + Separator;
    stClientRecord += User.PassWord + Separator;
    stClientRecord += to_string(User.Access) + Separator;

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
bool UserExistsByUserName(string UserName, string FileName)
{

    vector<sUsers> vUsers;

    fstream MyFile;
    MyFile.open(FileName, ios::in); // read Mode

    if (MyFile.is_open())
    {

        string Line;
        sUsers User;

        while (getline(MyFile, Line))
        {

            User = ConvertLinetoRecordUsers(Line);
            if (User.UserName == UserName)
            {
                MyFile.close();
                return true;
            }

            vUsers.push_back(User);
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

short AddPermission(char Per, short Value)
{
    short ans = 0;
    if (Per == 'y' || Per == 'Y')
    {
        ans += Value;
    }
    return ans;
}

short PermissionToAdd()
{
    short PermissionValue = 0;
    char ans;

    cout << "\nDo You Want To Give The User Full Access? y/n ";
    cin >> ans;
    if (ans == 'y' || ans == 'Y')
    {
        return -1;
    }

    cout << "\nAccess To Show Clients List? y/n ";
    cin >> ans;
    PermissionValue += AddPermission(ans, epShowClients);

    cout << "Access To Add New Client? y/n ";
    cin >> ans;
    PermissionValue += AddPermission(ans, epAddClient);

    cout << "Access To Delete Client? y/n ";
    cin >> ans;
    PermissionValue += AddPermission(ans, epDeleteClient);

    cout << "Access To Update Client? y/n ";
    cin >> ans;
    PermissionValue += AddPermission(ans, epUpdateClient);

    cout << "Access To Find Client? y/n ";
    cin >> ans;
    PermissionValue += AddPermission(ans, epFindClient);

    cout << "Access To Transactions Menu? y/n ";
    cin >> ans;
    PermissionValue += AddPermission(ans, epTransactions);

    cout << "Access To Manage Users Menu? y/n ";
    cin >> ans;
    PermissionValue += AddPermission(ans, epManageUsers);

    return PermissionValue;
}

sUsers ReadNewUser()
{
    sUsers User;

    cout << "Enter UserName? ";

    getline(cin >> ws, User.UserName);

    while (UserExistsByUserName(User.UserName, UserFileName))
    {
        cout << "\nUser with [" << User.UserName << "] already exists, Enter another UserName? ";
        getline(cin >> ws, User.UserName);
    }

    cout << "Enter PassWord? ";
    getline(cin, User.PassWord);

    cout << "Enter User Access? ";
    User.Access = PermissionToAdd();

    return User;
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

vector<sUsers> LoadUsersDataFromFile(string FileName)
{

    vector<sUsers> vUsers;

    fstream MyFile;
    MyFile.open(FileName, ios::in); // read Mode

    if (MyFile.is_open())
    {

        string Line;
        sUsers User;

        while (getline(MyFile, Line))
        {

            User = ConvertLinetoRecordUsers(Line);

            vUsers.push_back(User);
        }

        MyFile.close();
    }

    return vUsers;
}

void PrintClientRecordLine(sClient Client)
{

    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}
void PrintUserRecordLine(sUsers User)
{

    cout << "| " << setw(15) << left << User.UserName;
    cout << "| " << setw(10) << left << User.PassWord;
    cout << "| " << setw(40) << left << User.Access;
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
void ShowAllUsersScreen()
{

    vector<sUsers> vUsers = LoadUsersDataFromFile(UserFileName);

    cout << "\n\t\t\t\t\vUsers List (" << vUsers.size() << ") User(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;

    cout << "| " << left << setw(15) << "UsersName";
    cout << "| " << left << setw(10) << "PassWord";
    cout << "| " << left << setw(40) << "Access";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;

    if (vUsers.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else

        for (sUsers User : vUsers)
        {

            PrintUserRecordLine(User);
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
void PrintUserCard(sUsers User)
{
    cout << "\nThe following are the User details:\n";
    cout << "-----------------------------------";
    cout << "\nUserName:     " << User.UserName;
    cout << "\nPassWord:      " << User.PassWord;
    cout << "\nAccess:        " << User.Access;
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
bool FindUserByUserName(string UserName, vector<sUsers> vUsers, sUsers &Users)
{

    for (sUsers C : vUsers)
    {

        if (C.UserName == UserName)
        {
            Users = C;
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

sUsers ChangeUserRecord(string UserName)
{
    sUsers User;

    User.UserName = UserName;

    cout << "\n\nEnter PassWord? ";
    getline(cin >> ws, User.PassWord);

    cout << "Enter Access? ";
    cin >> User.Access;

    return User;
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

bool MarkUserForDeleteByUserName(string UserName, vector<sUsers> &vUsers)
{

    for (sUsers &C : vUsers)
    {

        if (C.UserName == UserName)
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
vector<sUsers> SaveUsersDataToFile(string FileName, vector<sUsers> vUsers)
{

    fstream MyFile;
    MyFile.open(FileName, ios::out); // overwrite

    string DataLine;

    if (MyFile.is_open())
    {

        for (sUsers C : vUsers)
        {

            if (C.MarkForDelete == false)
            {
                // we only write records that are not marked for delete.
                DataLine = ConvertRecordToLineUsers(C);
                MyFile << DataLine << endl;
            }
        }

        MyFile.close();
    }

    return vUsers;
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
void AddNewUser()
{
    sUsers User;
    User = ReadNewUser();
    AddDataLineToFile(UserFileName, ConvertRecordToLineUsers(User));
}

void AddNewUsers()
{

    char AddMore = 'Y';
    do
    {
        // system("cls");
        cout << "Adding New User:\n\n";

        AddNewUser();
        cout << "\nUser Added Successfully, do you want to add more Users? Y/N? ";

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

bool DeleteUserByUserName(string UserName, vector<sUsers> &vUsers)
{

    sUsers User;
    char Answer = 'n';

    if (FindUserByUserName(UserName, vUsers, User))
    {

        PrintUserCard(User);

        cout << "\n\nAre you sure you want delete this User? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            MarkUserForDeleteByUserName(UserName, vUsers);
            SaveUsersDataToFile(UserFileName, vUsers);

            // Refresh Users
            vUsers = LoadUsersDataFromFile(UserFileName);

            cout << "\n\nUser Deleted Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nUser with UserName (" << UserName << ") is Not Found!";
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
bool UpdateUserByAccountNumber(string UserName, vector<sUsers> &vUsers)
{

    sUsers User;
    char Answer = 'n';

    if (FindUserByUserName(UserName, vUsers, User))
    {

        PrintUserCard(User);
        cout << "\n\nAre you sure you want update this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {

            for (sUsers &C : vUsers)
            {
                if (C.UserName == UserName)
                {
                    C = ChangeUserRecord(UserName);
                    break;
                }
            }

            SaveUsersDataToFile(UserName, vUsers);

            cout << "\n\nUser Updated Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nUser with UserName (" << UserName << ") is Not Found!";
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
string ReadUserName()
{
    string UserName = "";

    cout << "\nPlease enter UserName? ";
    cin >> UserName;
    return UserName;
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
void ShowDeleteUserScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDelete User Screen";
    cout << "\n-----------------------------------\n";

    vector<sUsers> vUsers = LoadUsersDataFromFile(UserFileName);
    string UserName = ReadUserName();
    DeleteUserByUserName(UserName, vUsers);
}
void ShowUpdateUserScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate User Info Screen";
    cout << "\n-----------------------------------\n";

    vector<sUsers> vUsers = LoadUsersDataFromFile(UserFileName);
    string UserName = ReadUserName();
    UpdateUserByAccountNumber(UserName, vUsers);
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

void ShowAddNewUsersScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tAdd New Users Screen";
    cout << "\n-----------------------------------\n";

    AddNewUsers();
}
void ShowFindUserScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tFind User Screen";
    cout << "\n-----------------------------------\n";

    vector<sUsers> vUsers = LoadUsersDataFromFile(UserFileName);
    sUsers User;
    string UserName = ReadUserName();
    if (FindUserByUserName(UserName, vUsers, User))
        PrintUserCard(User);
    else
        cout << "\nUser with UserName[" << UserName << "] is not found!";
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
sUsers CurrentUser;

bool CheckUserLogin(sUsers Userlogin)
{
    vector<sUsers> vUsers = LoadUsersDataFromFile(UserFileName);
    for (sUsers &C : vUsers)
    {
        if (Userlogin.UserName == C.UserName)
        {
            if (Userlogin.PassWord == C.PassWord)
            {
                CurrentUser = C;
                return true;
            }
        }
    }
    return false;
}

bool CheckAccessPermission(enPermission Permission)
{
    short op = 0;
    if (CurrentUser.Access == -1)
    {
        return true;
    }
    else
    {

        op = (CurrentUser.Access) & (Permission);
        if (op == 0)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
}

void Login()
{
    sUsers Userlogin;
    cout << "\n-----------------------------------\n";
    cout << "\tLogin Screen";
    cout << "\n-----------------------------------\n";
    cout << "Enter UserName?\n";
    cin >> Userlogin.UserName;
    cout << "Enter PassWord?\n";
    cin >> Userlogin.PassWord;
    while (!CheckUserLogin(Userlogin))
    {
        sUsers Userlogin;
        cout << "\n-----------------------------------\n";
        cout << "\tLogin Screen";
        cout << "\n-----------------------------------\n";
        cout << "Invalid PassWord/UserName\n";
        cout << "Enter UserName?\n";
        cin >> Userlogin.UserName;
        cout << "Enter PassWord?\n";
        cin >> Userlogin.PassWord;
        if (CheckUserLogin(Userlogin))
        {
            break;
        }
    }
    ShowMainMenu();
}
void LogOut()
{
    Login();
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

enum enMangeUsersMenuOptions
{
    eListUsers = 1,
    eAddNewUsers = 2,
    eDeleteUsers = 3,
    eUpdateUsers = 4,
    eFindUsers = 5,
    eMainMenu = 6

};

enum enMainMenuOptions
{
    eListClients = 1,
    eAddNewClient = 2,
    eDeleteClient = 3,
    eUpdateClient = 4,
    eFindClient = 5,
    eShowTransactionsMenu = 6,
    eMangeUsers = 7,
    eLogOut = 8
};

void GoBackToMainMenu()
{
    cout << "\n\nPress any key to go back to Main Menu...";
    system("pause>0");
    ShowMainMenu();
}
void GoBackToMangeUserMenu()
{
    cout << "\n\nPress any key to go back to Main Menu...";
    system("pause>0");
    ShowMangeUsersMenu();
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
    do
    {
        cin >> Choice;
    } while (Choice < 1 || Choice > 4);
    return Choice;
}

void PerformMangeUsersMenuOptin(enMangeUsersMenuOptions MangeUsersMenuOptions)
{
    switch (MangeUsersMenuOptions)
    {
    case enMangeUsersMenuOptions::eListUsers:
    {
        system("cls");
        ShowAllUsersScreen();
        GoBackToMangeUserMenu();
        break;
    }

    case enMangeUsersMenuOptions::eAddNewUsers:
    {
        system("cls");
        ShowAddNewUsersScreen();
        GoBackToMangeUserMenu();
        break;
    }
    case enMangeUsersMenuOptions::eFindUsers:
    {
        system("cls");
        ShowFindUserScreen();
        GoBackToMangeUserMenu();
        break;
    }
    case enMangeUsersMenuOptions::eDeleteUsers:
    {
        system("cls");
        ShowDeleteUserScreen();
        GoBackToMangeUserMenu();
        break;
    }
    case enMangeUsersMenuOptions::eUpdateUsers:
    {
        system("cls");
        ShowUpdateUserScreen();
        GoBackToMangeUserMenu();
        break;
    }
    case enMangeUsersMenuOptions::eMainMenu:
    {
        system("cls");
        ShowMainMenu();
        break;
    }
    }
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
    cout << "Choose what do you want to do? [1 to 8]? ";
    short Choice = 0;
    do
    {
        cin >> Choice;
    } while (Choice < 1 || Choice > 8);
    return Choice;
}

short ReadMangeUsersOption()
{
    cout << "Choose what do you want to do? [1 to 6]? ";
    short Choice = 0;
    do
    {
        cin >> Choice;
    } while (Choice < 1 || Choice > 6);

    return Choice;
}

void ShowAccessDeniedScreen()
{
    system("cls");
    cout << "\n-----------------------------------\n";
    cout << "\tAccess Denied!";
    cout << "\n\tPlease contact your Admin to grant you this permission.";
    cout << "\n-----------------------------------\n";
    GoBackToMainMenu();
}

void PerfromMainMenuOption(enMainMenuOptions MainMenuOption)
{
    switch (MainMenuOption)
    {
    case enMainMenuOptions::eListClients:
        if (CheckAccessPermission(enPermission::epShowClients))
        {
            system("cls");
            ShowAllClientsScreen();
            GoBackToMainMenu();
        }
        else
            ShowAccessDeniedScreen();
        break;

    case enMainMenuOptions::eAddNewClient:
        if (CheckAccessPermission(enPermission::epAddClient))
        {
            system("cls");
            ShowAddNewClientsScreen();
            GoBackToMainMenu();
        }
        else
            ShowAccessDeniedScreen();
        break;

    case enMainMenuOptions::eDeleteClient:
        if (CheckAccessPermission(enPermission::epDeleteClient))
        {
            system("cls");
            ShowDeleteClientScreen();
            GoBackToMainMenu();
        }
        else
            ShowAccessDeniedScreen();
        break;

    case enMainMenuOptions::eUpdateClient:
        if (CheckAccessPermission(enPermission::epUpdateClient))
        {
            system("cls");
            ShowUpdateClientScreen();
            GoBackToMainMenu();
        }
        else
            ShowAccessDeniedScreen();
        break;

    case enMainMenuOptions::eFindClient:
        if (CheckAccessPermission(enPermission::epFindClient))
        {
            system("cls");
            ShowFindClientScreen();
            GoBackToMainMenu();
        }
        else
            ShowAccessDeniedScreen();
        break;

    case enMainMenuOptions::eShowTransactionsMenu:
        if (CheckAccessPermission(enPermission::epTransactions))
        {
            system("cls");
            ShowTransactionsMenu();
        }
        else
            ShowAccessDeniedScreen();
        break;

    case enMainMenuOptions::eMangeUsers:
        if (CheckAccessPermission(enPermission::epManageUsers))
        {
            system("cls");
            ShowMangeUsersMenu();
        }
        else
            ShowAccessDeniedScreen();
        break;

    case enMainMenuOptions::eLogOut:
        system("cls");
        Login();
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
    cout << "\t[7] MangeUsers.\n";
    cout << "\t[8] LogOut.\n";
    cout << "===========================================\n";
    PerfromMainMenuOption((enMainMenuOptions)ReadMainMenuOption());
}
void ShowMangeUsersMenu()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tMange Users Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Show Users List.\n";
    cout << "\t[2] Add New User.\n";
    cout << "\t[3] Delete User.\n";
    cout << "\t[4] Update User Info.\n";
    cout << "\t[5] Find User.\n";
    cout << "\t[6] Main Menu.\n";

    cout << "===========================================\n";
    PerformMangeUsersMenuOptin((enMangeUsersMenuOptions)ReadMangeUsersOption());
}

int main()

{
    Login();
    system("pause>0");
    return 0;
}
