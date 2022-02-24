#include "header.h"
#include "system.cpp"

struct Type_Coffee
{
    string coffee_name;
    double price_m;
    double price_l;
};

struct Type_Topping
{
    string topping;
    double price;
};

class Coffee_Shop
{
    vector<Type_Coffee> types_coffee;
    vector<Type_Topping> types_topping;
    string login;
    string password;
public:  
    Coffee_Shop()
    {
        login = "admin";
        password = "admin";
    }
    void add_coffee_type(string coffee_name, double price_m, double price_l)
    {
        Type_Coffee new_type;
        new_type.coffee_name = coffee_name;
        new_type.price_m = price_m;
        new_type.price_l = price_l;
        types_coffee.push_back(new_type);
    }
    
    void add_topping_type(string topping, double price)
    {
        Type_Topping new_type;
        new_type.topping = topping;
        new_type.price = price;
        types_topping.push_back(new_type);
    }
    
    vector<Type_Coffee> get_coffee_types()
    {
        return types_coffee;
    }
    
    vector<Type_Topping> get_topping_types()
    {
        return types_topping;
    }

    bool log_in(string login, string password)
    {
        if(this->login == login && this->password == password)
            return true;
        return false;
    }
};

struct Guest_BIO
{
    string name;
    string phone_number;
    int count;
};

class Guests
{
    vector<Guest_BIO> guests;
public:
    bool sign_up(string name, string phone_number)
    {
        Guest_BIO new_guest;
        new_guest.name = name;
        new_guest.phone_number = phone_number;
        new_guest.count = 0;
        guests.push_back(new_guest);
        return true;
    }

    bool log_in(string phone_number)
    {
        for(int i = 0; i , guests.size(); i++)
        {
            if(guests[i].phone_number == phone_number)
                return true;
        }
        return false;
    }

};

class IO_Manager
{
    My_String string_to_tok;
public:
//Menu saving
    void save_to_file(Coffee_Shop& c1)
    {
        ofstream fin;   
        vector<Type_Coffee> coffee_buffer = c1.get_coffee_types();
        fin.open("coffee.txt");
        for(int i = 0; i < coffee_buffer.size(); i++)
        {
            fin << coffee_buffer[i].coffee_name << " " << coffee_buffer[i].price_m << " " << coffee_buffer[i].price_l;
            if(i < coffee_buffer.size()-1)
                fin << "\n";    
        }
        fin.close();
        //Topping save
        vector<Type_Topping> topping_buffer = c1.get_topping_types();
        fin.open("toppings.txt");
        for(int i = 0; i < topping_buffer.size(); i++)
        {
            fin << topping_buffer[i].topping << " " << topping_buffer[i].price;
            if(i < topping_buffer.size()-1)
                fin << "\n";
        }
    }

    void load_into_menu(Coffee_Shop& c1)
    {
        string line;
        ifstream fout;
        fout.open("coffee.txt");
        while (!fout.eof())
        {
            getline (fout,line); 
            string* strings = string_to_tok.tok(line, ' ');
            string name = strings[0];
            double medium_cup = stod(strings[1]);
            double big_cup = stod(strings[2]);
            c1.add_coffee_type(name, medium_cup, big_cup);
        }
        fout.close();
        fout.open("toppings.txt");
        while(!fout.eof())
        {
            getline(fout, line);
            string* strings = string_to_tok.tok(line, ' ');
            string name = strings[0];
            double price = stod(strings[1]);
            c1.add_topping_type(name, price);
        }
        fout.close();
    }
//User saving
    void save_users()
    {
        ofstream fin;
        fin.open("guests.txt");
            vector<Guests> guests_buffer = 
        fin.close();
    }
};

class Menu_Handler
{
    Coffee_Shop c1;
    Guests g1;
    IO_Manager manager;
    char yes_no;
    //For general use
    string name;
    string phone_number;
public:
    void show_coffee_shop_menu()
    {
        cout << "\t\tMENU:\n";
        cout << "Drinks: \n";
        vector<Type_Coffee> types_coffee = c1.get_coffee_types();
        if(types_coffee.size() == 0)
        {
            cout << "There is no coffee types now\n";
        }
        else
        {
        for(int i = 0; i < types_coffee.size(); i++)
            {
                cout << i+1 << "." << types_coffee.at(i).coffee_name << " M:" << types_coffee.at(i).price_m << " L:" << types_coffee.at(i).price_l << "\n";
            }
        }
        cout << "Toppings: \n";
        vector<Type_Topping> types_topping = c1.get_topping_types();
        if(types_topping.size() == 0)
        {
            cout << "There is no toppings now\n";
        }
        else
        {
            for(int i = 0; i < types_topping.size(); i++)
            {
                cout << i+1 << "." << types_topping.at(i).topping << "\n";
            }
        }
    }
    
    void menu()
    {
        manager.load_into_menu(c1);
        manager.save_to_file(c1);
        cout << "\t\t\t\t\t\t\t\tWelcome\n";
        cout << "> Enter your phone number: ";
        cin >> phone_number;
        login_as_guest(phone_number);

    }

    void login_as_guest(string phone_number)
    {
        int switcher;
        do
        {
            g1.log_in(phone_number);
            if(!g1.log_in(phone_number))
            {
                cout << "> Try again, or register account(1/2): ";
                cin >> switcher;
                if(switcher == 1)
                    break;
                if(switcher == 2)
                {
                    cout << "> Enter your name please: ";
                    cin >> name;
                    g1.sign_up(name, phone_number);
                }
                else
                {
                    cout << "> Invalid number";
                    break;
                }
            }
        } while (!g1.log_in(phone_number));
    }

    bool login_as_admin()
    {
        string login;
        string password;
        cin.ignore();
        cout << "> Enter login: ";
        getline(cin, login);
        cout << "Enter password: ";
        getline(cin, password);
        if(c1.log_in(login, password))
            return true;
        return false;
    }
};