#include <iostream>
#include <fstream>
#include<cstring>
#include<iomanip>

using namespace std;

class account{
    int accNumber;
    char name[50];
    int Balance;
    char type;
public:
    void create_Account();
    void show_Account() const;
    void withDraw(int amount);
    void Deposit(int amount);
    void report();
    int return_accNo() const;
    int return_Balance() const;
    char return_Type() const;
};

void account::create_Account(){
    system("cls");
    cout<<"\n\t\t\tEnter the account number : ";
    cin>>accNumber;
    cout<<"\n\t\t\tEnter the name of the account holder : ";
    cin.ignore();
    cin.getline(name,50);
    cout<<"\n\t\t\tPlease enter type of account cheque(C)/savings(S): ";
    cin>>type;
    type=toupper(type);
    cout<<"\n\t\t\tEnter the initial amount: ";
    cin>>Balance;
    cout<<"\n\t\t\tAccount created successfully!"<<endl;
}
void account::show_Account() const {
    cout << "\n\t\t\tAccount No. : " << accNumber;
    cout << "\n\t\t\tAccount Holder Name : ";
    cout << name;
    cout << "\n\t\t\tType of Account : " << type;
    cout << "\n\t\t\tBalance amount : " << Balance;
    cout<<endl;
}
void account::report(){
    cout<<name<<setw(14)<<accNumber<<setw(10)<<type<<setw(16)<<Balance<<endl;
}
void account::Deposit(int amount){
    Balance+=amount;
}
void account::withDraw(int amount){
    Balance-=amount;
}
int account::return_accNo() const{
    return accNumber;
}
int account::return_Balance() const{
    return Balance;
}
char account::return_Type() const{
    return type;
}

void createAccount();
void displayAccount(int num);
void deposit(int num);
void withdraw(int num);
void deleteAccount(int num);
void display_All();
int main()
{
    char ch;
    int num;
    do
    {
        system("CLS");
        cout << "\n\n\t\t\t\t======================\n";
        cout << "\t\t\t\tBANK MANAGEMENT SYSTEM";
        cout << "\n\t\t\t\t======================\n";

        cout << "\t\t\t\t    ::MAIN MENU::\n";
        cout << "\n\t\t\t\t1. NEW ACCOUNT";
        cout << "\n\t\t\t\t2. DEPOSIT AMOUNT";
        cout << "\n\t\t\t\t3. WITHDRAW AMOUNT";
        cout << "\n\t\t\t\t4. BALANCE ENQUIRY";
        cout << "\n\t\t\t\t5. ALL ACCOUNT HOLDER LIST";
        cout << "\n\t\t\t\t6. CLOSE AN ACCOUNT";
        cout << "\n\t\t\t\t7. EXIT";
        cout << "\n\n\t\t\t\tSelect Your Option (1-7): ";
        cin>>ch;
        switch(tolower(ch)){
        case '1':
            createAccount();
            break;
        case '2':
            system("CLS");
            cout << "\n\n\t\t\tEnter The account No. : "; cin >> num;
            deposit(num);
            break;
        case '3':
            system("CLS");
            cout << "\n\n\t\t\tEnter The account No. : "; cin >> num;
            withdraw(num);
            break;
        case '4':
            system("CLS");
            cout << "\n\n\t\t\tEnter The account No. : "; cin >> num;
            displayAccount(num);
            break;
        case '5':
            display_All();
            break;
        case '6':
            system("CLS");
            cout << "\n\n\t\t\tEnter The account No. : "; cin >> num;
            deleteAccount(num);
            break;
        case '7':
            system("CLS");
            cout<<"\n\n\t\t\tBrought to you by Phathutshedzo Murovhi"<<endl;
            break;
        default:cout << "\a";
        }
        cin.ignore();
        cin.get();
    } while (ch != '7');
    return 0;
}
void createAccount(){
    account ac;
    ofstream outFile;
    ac.create_Account();
    outFile.open("account.bin", ios::binary | ios::app);
    outFile.write(reinterpret_cast<char*> (&ac), sizeof(account));
    outFile.close();
}
void displayAccount(int num){
    account ac;
    bool flag=false;
    ifstream inFile;
    inFile.open("account.bin", ios::binary);
    if(!inFile){
        cerr<<"\n\n\t\t\tFile could not be open !! Press any Key...";
        return;
    }
    cout << "\tBALANCE DETAILS\n";
    while(inFile.read(reinterpret_cast<char*> (&ac), sizeof(account))){
        if(ac.return_accNo()==num){
            ac.show_Account();
            flag=true;
        }
    }
    inFile.close();
    if(flag==false){
        cout<<"\n\n\t\t\tAccount number does not exist!";
    }
}
void deposit(int num){
    int am;
    bool flag=false;
    account ac;
    fstream inFile;
    inFile.open("account.bin",ios::binary | ios::in | ios::out);
    if(!inFile){
        cerr<<"\n\n\t\t\tFile could not be open !! Press any Key...";
        return;
    }
    cout<<"\n\n\t\t\tHow much do yo want to deposit? :R ";
    cin>>am;
    while(inFile.read(reinterpret_cast<char*> (&ac), sizeof(account))){
        if(ac.return_accNo()==num){
            ac.Deposit(am);
            int pos=(-1)*static_cast<int>(sizeof(ac));
            inFile.seekp(pos,ios::cur);
            inFile.write(reinterpret_cast<char*>(&ac), sizeof(account));
            flag=true;
            cout<<"\n\n\t\t\tamount successfully Deposited"<<endl;
        }
    }
    inFile.close();
    if(flag==false){
        cout<<"\n\n\t\t\tAccount number does not exist!";
    }
}
void withdraw(int num){
    int am;
    bool flag=false;
    account ac;
    fstream inFile;
    inFile.open("account.bin",ios::binary | ios::in | ios::out);
    if(!inFile){
        cerr<<"\n\n\t\t\tFile could not be open !! Press any Key...";
        return;
    }
    cout<<"\n\n\t\t\tHow much do yo want to deposit? :R ";
    cin>>am;
    while(inFile.read(reinterpret_cast<char*> (&ac), sizeof(account))){
        if(ac.return_accNo()==num){
            if(ac.return_Balance()-am <0){
                cout<<"\n\n\t\t\tinsufficient balance!"<<endl;
            }
            else{
                ac.withDraw(am);
                int pos=(-1)*static_cast<int>(sizeof(ac));
                inFile.seekp(pos,ios::cur);
                inFile.write(reinterpret_cast<char*>(&ac), sizeof(account));
                flag=true;
                cout<<"\n\n\t\t\tamount successfully withdrawd"<<endl;
            }
        }
    }
    inFile.close();
    if(flag==false){
        cout<<"\n\n\t\t\tAccount number does not exist!";
    }
}

void display_All(){
    system("cls");
    account ac;
    ifstream inFile;
    inFile.open("account.bin", ios::binary);
    if(!inFile){
        cerr<<"\n\n\t\t\tFile could not be open !! Press any Key...";
        return;
    }
    cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
    cout << "====================================================\n";
    cout << "NAME             A/c no.          Type       Balance\n";
    cout << "====================================================\n";
    while(inFile.read(reinterpret_cast<char*> (&ac), sizeof(account))){
        ac.report();
    }
    inFile.close();
}
void deleteAccount(int num){
    account ac;
    ifstream inFile;
    ofstream outFile;
    inFile.open("account.bin", ios::binary);
    if (!inFile)
    {
        cout << "\n\n\t\t\tFile could not be open !! Press any Key...";
        return;
    }
    outFile.open("Temp.bin", ios::binary);
    inFile.seekg(0, ios::beg);
    while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account)))
    {
        if (ac.return_accNo() != num)
        {
            outFile.write(reinterpret_cast<char*> (&ac), sizeof(account));
        }
    }
    inFile.close();
    outFile.close();
    remove("account.bin");
    rename("Temp.bin", "account.bin");
    cout << "\n\n\t\t\tRecord Deleted ..";
}
