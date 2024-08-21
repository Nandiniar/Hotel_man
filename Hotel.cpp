#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <string>

using namespace std;

void intro()
{
    cout << "\n\n\tC++ Project On Hotel Management System";
    cout << "\n\n\t\t\t\tMADE BY";
    cout << "\n*************************************";
    cout << "\n||\t\t\tNandini Arora\t\t\t||";
    cout << "\n*************************************";
}

void head()
{
    system("cls"); // Use this for Windows
    cout << "*************************************\n";
    cout << "||\t\tXYZ Group of Hotels\t\t||\n";
    cout << "*************************************\n";
}

void time()
{
    int i = 0;
    cout << "\n\n\nConnecting to Server\nSyncing Data";
    while (i < 10)
    {
        cout << ".";
        ++i;
    }
    cout << "\n";
}

class hotel
{
private:
    int room_no;
    char name[30];
    char address[50];
    char phone[15];
    int days;
    float fare;

public:
    void main_menu();
    void add();
    void display();
    void rooms();
    void edit();
    int check(int);
    void modify(int);
    void delete_rec(int);
};

// New Functions for Registration and Login
void register_user();
bool login_user();

void hotel::main_menu()
{
    int choice = 0;
    while (choice != 5)
    {
        system("cls"); // Use this for Windows
        head();
        cout << "\n\t\t\tMAIN MENU";
        cout << "\n\n1. Book A Room";
        cout << "\n2. Customer Record";
        cout << "\n3. Rooms Allotted";
        cout << "\n4. Edit Record";
        cout << "\n5. Exit";
        cout << "\n\nEnter Your Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            add();
            break;
        case 2:
            display();
            break;
        case 3:
            rooms();
            break;
        case 4:
            edit();
            break;
        case 5:
            break;
        default:
            cout << "\n\nWrong choice...!!! Press any key to continue...!!";
            cin.get();
            cin.ignore();
        }
    }
}

void hotel::add()
{
    system("cls"); // Use this for Windows
    head();
    int r, flag;
    ofstream fout("Record.dat", ios::app);
    cout << "\nEnter Customer Details";
    cout << "\n----------------------";
    cout << "\n\nRoom no: ";
    cin >> r;
    flag = check(r);
    if (flag)
    {
        cout << "\nSorry, Room is already booked.";
    }
    else
    {
        room_no = r;
        cout << "Name: ";
        cin.ignore(); // to ignore the newline character left by previous input
        cin.getline(name, 30);
        cout << "Address: ";
        cin.getline(address, 50);
        cout << "Phone No: ";
        cin.getline(phone, 15);
        cout << "No of Days to Checkout: ";
        cin >> days;
        fare = days * 900; // Default price per day
        fout.write((char *)this, sizeof(hotel));
        cout << "\nRoom is booked...!!!";
    }

    cout << "\nPress any key to continue.....!!";
    cin.get();
    cin.ignore();
    fout.close();
}

void hotel::display()
{
    system("cls"); // Use this for Windows
    head();
    ifstream fin("Record.dat", ios::in);
    int r, flag = 0;
    cout << "\nEnter room no: ";
    cin >> r;
    while (fin.read((char *)this, sizeof(hotel)))
    {
        if (room_no == r)
        {
            system("cls"); // Use this for Windows
            head();
            cout << "\nCustomer Details";
            cout << "\n----------------";
            cout << "\n\nRoom no: " << room_no;
            cout << "\nName: " << name;
            cout << "\nAddress: " << address;
            cout << "\nPhone no: " << phone;
            cout << "\nDays: " << days;
            cout << "\nTotal Fare: " << fare;
            flag = 1;
            break;
        }
    }
    if (!flag)
        cout << "\nSorry, Room no. not found or vacant....!!";
    cout << "\n\nPress any key to continue....!!";
    cin.get();
    cin.ignore();
    fin.close();
}

void hotel::rooms()
{
    system("cls"); // Use this for Windows
    head();
    ifstream fin("Record.dat", ios::in);
    cout << "\nList Of Rooms Allotted";
    cout << "\n----------------------";
    while (fin.read((char *)this, sizeof(hotel)))
    {
        cout << "\nRoom no: " << room_no;
        cout << "\nName: " << name;
        cout << "\nAddress: " << address;
        cout << "\nPhone: " << phone;
        cout << "\nDays: " << days;
        cout << "\nTotal: " << fare;
        cout << "\n**********************************";
    }
    cout << "\n\n\nPress any key to continue.....!!";
    cin.get();
    cin.ignore();
    fin.close();
}

void hotel::edit()
{
    system("cls"); // Use this for Windows
    head();
    int choice, r;
    cout << "\nEDIT MENU";
    cout << "\n---------";
    cout << "\n\n1. Modify Customer Record";
    cout << "\n2. Delete Customer Record";
    cout << "\nEnter your choice: ";
    cin >> choice;

    system("cls"); // Use this for Windows
    head();
    cout << "\nEnter room no: ";
    cin >> r;
    switch (choice)
    {
    case 1:
        modify(r);
        break;
    case 2:
        delete_rec(r);
        break;
    default:
        cout << "\nWrong Choice.....!!";
    }
    cout << "\nPress any key to continue....!!!";
    cin.get();
    cin.ignore();
}

int hotel::check(int r)
{
    int flag = 0;
    ifstream fin("Record.dat", ios::in);
    while (fin.read((char *)this, sizeof(hotel)))
    {
        if (room_no == r)
        {
            flag = 1;
            break;
        }
    }

    fin.close();
    return flag;
}

void hotel::modify(int r)
{
    system("cls"); // Use this for Windows
    head();
    long pos;
    int flag = 0;
    fstream file("Record.dat", ios::in | ios::out | ios::binary);
    while (file.read((char *)this, sizeof(hotel)))
    {
        pos = file.tellg();
        if (room_no == r)
        {
            cout << "\nEnter New Details";
            cout << "\n-----------------";
            cout << "\nName: ";
            cin.ignore();
            cin.getline(name, 30);
            cout << "Address: ";
            cin.getline(address, 50);
            cout << "Phone no: ";
            cin.getline(phone, 15);
            cout << "Days: ";
            cin >> days;
            fare = days * 900;
            file.seekg(pos - sizeof(hotel));
            file.write((char *)this, sizeof(hotel));
            cout << "\nRecord is modified....!!";
            flag = 1;
            break;
        }
    }

    if (!flag)
        cout << "\nSorry, Room no. not found or vacant...!!";
    file.close();
}

void hotel::delete_rec(int r)
{
    system("cls"); // Use this for Windows
    head();
    int flag = 0;
    char ch;
    ifstream fin("Record.dat", ios::in);
    ofstream fout("temp.dat", ios::out);
    while (fin.read((char *)this, sizeof(hotel)))
    {
        if (room_no == r)
        {
            cout << "\nName: " << name;
            cout << "\nAddress: " << address;
            cout << "\nPhone No: " << phone;
            cout << "\nDays: " << days;
            cout << "\nTotal Fare: " << fare;
            cout << "\n\nDo you want to delete this record (y/n): ";
            cin >> ch;
            if (ch == 'n')
                fout.write((char *)this, sizeof(hotel));
            flag = 1;
        }
        else
        {
            fout.write((char *)this, sizeof(hotel));
        }
    }

    fin.close();
    fout.close();
    if (!flag)
    {
        cout << "\nSorry, room no. not found or vacant...!!";
    }
    else
    {
        remove("Record.dat");
        rename("temp.dat", "Record.dat");
    }
}

// New function to register a user
void register_user()
{
    string username, password;
    ofstream fout("users.dat", ios::app);

    cout << "\n\n\t\t\t\tRegister a New User";
    cout << "\n\n\t\t\t\tUsername => ";
    cin >> username;
    cout << "\n\t\t\t\tPassword => ";
    cin >> password;

    fout << username << " " << password << endl;
    fout.close();

    cout << "\n\n\t\t\tRegistration Successful! Press any key to continue...";
    cin.get();
    cin.ignore();
}

// New function to login a user
bool login_user()
{
    string username, password, id, pass;
    ifstream fin("users.dat");

    cout << "\n\n\t\t\t\tLogin";
    cout << "\n\n\t\t\t\tUsername => ";
    cin >> id;
    cout << "\n\t\t\t\tPassword => ";
    cin >> pass;
    time();

    while (fin >> username >> password)
    {
        if (username == id && password == pass)
        {
            cout << "\n\n\t\t\t!!!Login Successful!!!";
            fin.close();
            return true;
        }
    }

    fin.close();
    cout << "\n\n\t\t\t!!!INVALID CREDENTIALS!!!";
    cin.get();
    return false;
}

// MARK:- Main() Function Here =>

int main()
{
    hotel h;
    system("cls"); // Use this for Windows
    intro();
    time();
    cout << "\n\n\nPress any key to continue....!!";
    cin.get();

    int choice;
    bool logged_in = false;

    while (!logged_in)
    {
        system("cls"); // Use this for Windows
        head();
        cout << "\n\n1. Register";
        cout << "\n2. Login";
        cout << "\n3. Exit";
        cout << "\n\nEnter Your Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            register_user();
            break;
        case 2:
            logged_in = login_user();
            break;
        case 3:
            exit(0);
            break;
        default:
            cout << "\n\nWrong choice...!!! Press any key to continue...!!";
            cin.get();
            cin.ignore();
        }
    }

    system("cls"); // Use this for Windows
    h.main_menu();

    return 0;
}
