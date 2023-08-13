#include <iostream>
#include <conio.h>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <windows.h>
using namespace std;

struct Bank
{
    int accno;
    char name[50];
    int bal;
    char pass[32];
    const char adminpass[32] = {'a', 'd', 'm', 'i', 'n', '1', '2', '3', '\0'};

public:
    Bank()
    {
        bal = 0;
    }
    void input(int);
    void show();
    int retacc() { return accno; }
    int lacc();
};

struct Transaction
{
    int accno;
    char name[50];
    char type[10];
    int amnt;

public:
    void input(int,char*,char,int);
    void show();
};

void Transaction::input(int tacc,char* tname,char ttype,int mon){
    int i;
    accno=tacc;
    for(i=0;tname[i]!='\0';i++){
        name[i]=tname[i];
    }
    name[i]='\0';
    cout<<name;
    if(ttype=='W'){
        type[0]='W';
        type[1]='i';
        type[2]='t';
        type[3]='h';
        type[4]='d';
        type[5]='r';
        type[6]='a';
        type[7]='w';
        type[8]='\0';
    }
    else if(ttype=='D'){
        type[0]='D';
        type[1]='e';
        type[2]='p';
        type[3]='o';
        type[4]='s';
        type[5]='i';
        type[6]='t';
        type[7]='e';
        type[8]='\0';
    }
    amnt=mon;
}

void Bank::input(int v)
{
    char c;
    cout << "Enter your name" << endl;
    cin.ignore();
    gets(name);
    cout << "Enter the amount of money your wish to deposite to your balance" << endl;
    cin >> bal;
    do
    {
        cout << "\nEnter Password  : ";
        int i = 0;
        char a;
        for (i = 0;;)
        {
            a = getch();
            if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || (a >= '0' && a <= '9'))
            {
                pass[i] = a;
                ++i;
                cout << "*";
            }
            if (a == '\r') // if enter is pressed
            {
                pass[i] = '\0';
                break;
            }
        }
        cout << "\nYou entered : " << pass << endl;
        cout << "Do you want to change your password again? (Y for yes/N for no)  ";
        cin >> c;
    } while (c == 'y' || c == 'Y');
    ++v;
    accno = v;
    cout << "Your account number is : BNK1010" << accno << endl;
}

void Transaction::show()
{
    cout << left << setw(7) << "BNK1010" << left << setw(10) << accno << left << setw(30) << name << left << setw(20) << type << left << setw(10) << amnt<< endl;
}

void Bank::show()
{
    cout << left << setw(7) << "BNK1010" << left << setw(10) << accno << left << setw(30) << name << left << setw(10) << bal << endl;
}

int lacc()
{
    fstream f;
    Bank b;
    int v = 0;
    string p;
    f.open("Customer.txt", ios::in | ios::binary);
    if (f.fail())
    {
        cout << "Can't open file " << endl;
        return 0;
    }
    else
    {
        while (f.read((char *)&b, sizeof(b)))
        {
            if (b.retacc() == max(v, b.retacc()))
            {
                v = b.retacc();
            }
        }
    }
    f.close();
    return v;
}

int main()
{
    int c, chk = 0, v = 0, k, o, t, ini; // Switch case argument
    char ch;                             // Choice for do while lopp
    string a, s, q;                      // Account number input
    Transaction r;
    Bank b;
    fstream f,ft;
    size_t find;
    const char adminpass[32] = {'a', 'd', 'm', 'i', 'n', '1', '2', '3', '\0'};

    system("cls");
    cout << setw(111) << "WELCOME TO AVK INTERNATIONAL BANK" << endl;
    cout << setw(120) << "THIS IS A ONE STOP ATM FOR ALL YOUR BANKING NEEDS" << endl
         << endl;
    for (int i = 0; i < 202; i++)
        cout << "*";
    cout << endl
         << endl;
    do
    {
        cout << "1. Admin Entry to access files" << endl;
        cout << "2. Existing Customer Entry" << endl;
        cout << "3. New Customer Entry" << endl
             << endl;
        cin >> c;
        switch (c)
        {
        case 1:
            cout << "Enter Admin Login Password : ";
            char temp[32], o;
            for (int i = 0;;)
            {
                o = getch();
                if ((o >= 'a' && o <= 'z') || (o >= 'A' && o <= 'Z') || (o >= '0' && o <= '9'))
                {
                    cout << "*";
                    temp[i] = o;
                    ++i;
                }
                if (o == '\r')
                {
                    temp[i] = '\0';
                    break;
                }
            }
            if (!(strcmp(adminpass, temp)))
            {
                cout << endl
                     << endl;
                cout << "Here is the Database" << endl;
                cout << endl
                     << endl;
                cout << left << setw(17) << "ACCOUNT NO." << left << setw(30) << "NAME" << left << setw(10) << "BALANCE" << endl;
                cout << endl;
                f.open("Customer.txt", ios::in | ios::binary);
                while (f.read((char *)&b, sizeof(b)))
                {
                    b.show();
                }
                f.close();
            }
            else
            {
                cout << endl;
                cout << "Incorrect Password " << endl;
            }

            break;

        case 2:
            cout << "Enter your Account Number :\t" << endl;
            cin >> a;
            find = a.find("BNK1010");
            a = a.substr(find + 7);
            k = stoi(a);

            f.open("Customer.txt", ios::in | ios::binary | ios::out);
            ini = f.tellg();
            if (f.fail())
                cout << "Can't open file " << endl;
            else
            {
                int chkacc = 0;
                while (!f.eof())
                {
                    int pos = f.tellg();
                    f.read((char *)&b, sizeof(b));
                    if (f)
                    {
                        if (b.accno == k)
                        {
                            char a;
                            char temp[32];
                            cout << "Enter your password : ";
                            for (int i = 0;;)
                            {
                                a = getch();
                                if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || (a >= '0' && a <= '9'))
                                {
                                    cout << "*";
                                    temp[i] = a;
                                    ++i;
                                }
                                if (a == '\r')
                                {
                                    temp[i] = '\0';
                                    break;
                                }
                            }
                            if ((strcmp(b.pass, temp)) == 0)
                            {
                                cout << endl
                                     << endl;
                                b.show();
                                cout << endl
                                     << endl;
                                cout << "What would u like to do today?" << endl
                                     << endl;
                                cout << "1.Withdraw Money\n2.Deposit Money\n3.Transfer Money\n4.Show Transaction History\n";
                                cout<<endl;
                                cin >> t;
                                switch (t)
                                {
                                case 1:
                                    
                                    cout << "Enter the amount that you would like to withdraw : ";
                                    int w;
                                    char temp[32];
                                    cin >> w;
                                    cout << "Confirm by entering your password again : ";
                                    for (int i = 0;;)
                                    {
                                        char a;
                                        a = getch();
                                        if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || (a >= '0' && a <= '9'))
                                        {
                                            cout << "*";
                                            temp[i] = a;
                                            ++i;
                                        }
                                        if (a == '\r')
                                        {
                                            temp[i] = '\0';
                                            break;
                                        }
                                    }
                                    if ((strcmp(b.pass, temp)) == 0)
                                    {
                                        cout << endl
                                             << endl;
                                        cout << "Withdrawing";
                                        for (int i = 0; i < 3; i++)
                                        {
                                            Sleep(500);
                                            cout << ".";
                                        }
                                        cout << endl;
                                        cout << "You have withdrawn : Rs" << w << endl;
                                        cout << endl;
                                        b.bal -= w;
                                        f.seekp(pos);
                                        f.write((char *)&b, sizeof(b));
                                        cout << endl
                                             << endl;
                                        b.show();
                                        ft.open("CustomerTransaction.txt", ios::out | ios::app | ios::binary);
                                        r.input(b.accno,b.name,'W',w);
                                        ft.write((char *)&r, sizeof(r));
                                        ft.close();
                                    }
                                    else{
                                        cout<<"Incorrect Password!";
                                        cout<<endl;
                                    }
                                    break;
                                case 2:
                                    
                                    cout << "Enter the amount that you would like to deposit : ";
                                    cin >> w;
                                    cout << "Confirm by entering your password again : ";
                                    for (int i = 0;;)
                                    {
                                        char a;
                                        a = getch();
                                        if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || (a >= '0' && a <= '9'))
                                        {
                                            cout << "*";
                                            temp[i] = a;
                                            ++i;
                                        }
                                        if (a == '\r')
                                        {
                                            temp[i] = '\0';
                                            break;
                                        }
                                    }
                                    if ((strcmp(b.pass, temp)) == 0)
                                    {
                                        cout << endl
                                             << endl;
                                        cout << "Depositing";
                                        for (int i = 0; i < 3; i++)
                                        {
                                            Sleep(1000);
                                            cout << ".";
                                        }
                                        cout << endl;
                                        cout << "You have deposit : Rs" << w << endl;
                                        cout << endl;
                                        b.bal += w;
                                        f.seekp(pos);
                                        f.write((char *)&b, sizeof(b));
                                        cout << endl
                                             << endl;
                                        cout << "Your money has been succesfully deposited!!!";
                                        cout << endl
                                             << endl;
                                        b.show();
                                        ft.open("CustomerTransaction.txt", ios::out | ios::app | ios::binary);
                                        r.input(b.accno,b.name,'D',w);
                                        ft.write((char *)&r, sizeof(r));
                                        ft.close();
                                    }
                                    else{
                                        cout<<"Incorrect Password!";
                                        cout<<endl;
                                    }
                                    break;
                                case 3:
                                    cout << "Enter the Account u want to transfer to : ";
                                    cin >> q;
                                    k = q[q.length() - 1] - 48;
                                    f.seekp(ini);
                                    while (!f.eof())
                                    {
                                        int here = f.tellg();
                                        f.read((char *)&b, sizeof(b));
                                        if (f)
                                        {
                                            if (b.accno == k)
                                            {
                                                cout << b.name << " is the account name" << endl;
                                                cout << "Are you sure? (Y for yes/N for no) : ";
                                                cin >> ch;
                                                if (ch == 'y' || ch == 'Y')
                                                {
                                                    cout << "Enter the amount you want to transfer : ";
                                                    cin >> w;
                                                    b.bal += w;
                                                    f.seekp(here);
                                                    f.write((char *)&b, sizeof(b));
                                                    cout << "Transfering";
                                                    for (int i = 0; i < 3; i++)
                                                    {
                                                        Sleep(1000);
                                                        cout << ".";
                                                    }
                                                    cout << endl
                                                         << endl;
                                                    f.seekp(pos);
                                                    f.read((char *)&b, sizeof(b));
                                                    b.bal -= w;
                                                    f.seekp(pos);
                                                    f.write((char *)&b, sizeof(b));
                                                    cout << endl
                                                         << endl;

                                                    cout << "Your money has been succesfully tranferred!!!";
                                                    cout << endl
                                                         << endl;
                                                    b.show();
                                                }
                                                else
                                                {
                                                    cout << "Exiting..." << endl;
                                                    break;
                                                }
                                            }
                                        }
                                    }
                                    break;

                                case 4:
                                    cout<<"Please confirm your password once again : ";
                                    for (int i = 0;;)
                                    {
                                        char a;
                                        a = getch();
                                        if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || (a >= '0' && a <= '9'))
                                        {
                                            cout << "*";
                                            temp[i] = a;
                                            ++i;
                                        }
                                        if (a == '\r')
                                        {
                                            temp[i] = '\0';
                                            break;
                                        }
                                    }
                                    cout<<endl;
                                    if ((strcmp(b.pass, temp)) == 0)
                                    {
                                        cout << endl
                                             << endl;
                                        
                                        ft.open("CustomerTransaction.txt", ios::in | ios::binary);
                                        while (ft.read((char *)&r, sizeof(r)))
                                        {
                                            if(r.accno==b.accno)
                                                r.show();
                                        }
                                        ft.close();
                                    }
                                    else{
                                        cout<<"Incorrect Password!";
                                        cout<<endl;
                                    }
                                    break;

                                default:
                                    cout << "Invalid Output" << endl;
                                    break;
                                }
                                chkacc = 1;
                                break;
                            }
                            else
                            {
                                cout << endl
                                     << endl;
                                cout << "Incorrect Password" << endl;
                                chkacc = 1;
                                break;
                            }
                        }
                    }
                }
                if (chkacc == 0)
                    cout << "Account not Found" << endl;
            }
            f.close();

            getch();
            break;
        case 3:
            v = lacc();
            f.open("Customer.txt", ios::out | ios::app | ios::binary);
            b.input(v);
            f.write((char *)&b, sizeof(b));
            f.close();
            cout << "\n\nCongratulations! You have opened a new account with us" << endl;
            b.show();
            break;

        default:
            cout << "Invalid Choice";
            break;
        }
        cout << "\n\nIf you would like to continue this session, please enter 'Y'. Else 'N'" << endl;
        cin >> ch;
        system("cls");
    } while (ch == 'Y' || ch == 'y');
    return 0;
}
