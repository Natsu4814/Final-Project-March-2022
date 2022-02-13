#include "header.h"

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
//Global:

////
class Coffee_Shop
{
    vector<Type_Coffee> types_coffee;
    vector<Type_Topping> types_topping;
    string login;
    string password;
public:
    void make_choise()
    {
        cout << "> Choose position from menu: ";
        int number;
        cin >> number;
        Type_Coffee chosen_coffee;
        chosen_coffee = types_coffee[number - 1];
        cout << chosen_coffee.coffee_name;
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
    bool log_in()
    {
        tryAgain:
        cout << "Enter login: ";
        string lg;
        getline(cin, lg);
        cout << "Enter password: ";
        string pw;
        getline(cin, pw);
        if(login == lg && password == pw)
            return true;
        else
        {
            goto tryAgain;
        }
    }
    vector<Type_Coffee> get_coffee_types()
    {
        return types_coffee;
    }
    vector<Type_Topping> get_topping_types()
    {
        return types_topping;
    }
};

struct Guest_BIO
{
    string name;
    string phone_number;
    int count = 0;
};

class Guest
{
    Coffee_Shop c1;
    vector<Guest_BIO> guests;
public:
    void show_menu()
    {
        vector<Type_Coffee> types_coffee;
        vector<Type_Topping> types_topping;
        types_coffee = c1.get_coffee_types();
        types_topping = c1.get_topping_types();
        cout << "\t\tMENU:\n";
        cout << "Drinks: \n";
        if(types_coffee.size() == 0)
        {
            cout << "There is no coffee types now\n";
        }
        else
        {
        for(int i = 0; i < types_coffee.size(); i++)
            {
                cout << i+1 << "." << types_coffee.at(i).coffee_name << "For M:" << types_coffee.at(i).price_m << "  For L:" << types_coffee.at(i).price_l << "\n";
            }
        }
        cout << "Toppings: \n";
        if(types_topping.size() == 0)
        {
            cout << "There is no toppings now\n";
        }
        else
        {
            for(int i = 0; i < types_topping.size(); i++)
            {
                cout << i+1 << "." << types_topping.at(i).topping;
            }
        }
    }
    void sing_up()
    {
        cout << "> Enter your name: ";
        string name;
        getline(cin, name);
        cout << "> Enter your phone number: ";
        string phone;
        getline(cin, phone);
        Guest_BIO new_guest;
        new_guest.name = name;
        new_guest.phone_number = phone;
        for(int i = 0; i < guests.size(); i++)
        {
            if(guests.at(i).phone_number == new_guest.phone_number)
            {
                cout << "User with such phone number is already exists\n";
                return;
            }
        }
        guests.push_back(new_guest);
    }
    bool log_in()
    {
        char yn;
        do
        {
            cout << "> Enter phone number: ";
            string buff;
            getline(cin, buff);
            for(int i = 0; i < guests.size(); i++)
            {
                if(guests.at(i).phone_number == buff)
                    return true;
                else
                    break;
            }
            cout << "> Would you like to retry(y/n): ";
            cin >> yn;
        } while(yn ==  'y' || yn == 'Y');
    }
};

class IO_Manager
{
    Coffee_Shop c1; 
public:
    void save_to_file()
    {
        
    }
    void load_from_menu()
    {
        string line;
        ifstream fout("text.txt"); 
        if (fout.is_open())
        {
            while ( getline (fout,line) )
            {
                cout << line << '\n';
            }
            fout.close();
        }
        else cout << "Unable to open file"; 
    }
};