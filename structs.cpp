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

vector<Type_Coffee> types_coffee;
vector<Type_Topping> types_topping;

class Coffee_Shop
{
    string login = "admin";
    string password = "admin";
public:
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

    bool logIn()
    {
        cout << "Enter login: ";
        string lg;
        cin >> lg;
        cout << "Enter password: ";
        string pw;
        cin >> pw;
        if(login == lg && password == pw)
            return true;
        else
        {
            return false;
        }
    }
};

class Guest
{
public:
    void show_menu()
    {
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
        void make_choise()
    {
        cout << "> Choose position from menu: ";
        int number;
        cin >> number;
        Type_Coffee chosen_coffee;
        chosen_coffee = types_coffee[number - 1];
        cout << chosen_coffee.coffee_name;
    }
};