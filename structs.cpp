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

class Guest_BIO
{
    string name;
    string phone_number;
    int count;
public:
    bool sign_up(string name, string phone_number)
    {
        this->name = name;
        this->phone_number = phone_number;
        count = 0;
        return true;
    }

    bool log_in(string phone_number)
    {

    }

};

class IO_Manager
{
    My_String string_to_tok;
public:
    void save_to_file(Coffee_Shop& c1)
    {   
        vector<Type_Coffee> coffee_buffer = c1.get_coffee_types();
        ofstream fin;
        fin.open("coffee.txt");
        for(int i = 0; i < coffee_buffer.size(); i++)
            fin << "\n" << coffee_buffer[i].coffee_name << " " << coffee_buffer[i].price_m << " " << coffee_buffer[i].price_l;
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
    }
};

class Menu_Handler
{
    Coffee_Shop c1;
    IO_Manager manager;
    char yes_no;
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
                cout << i+1 << "." << types_topping.at(i).topping;
            }
        }
    }
    
    void menu()
    {
        
    }

    bool login_as_guest(string phone_number)
    {
        cout << "> Log in or sign up(1/2): ";
        int switcher;
        switch(switcher)
        {
        case 1:
            {
                break;
            }
        case 2:
            {
                break;
            }
        }
    }

    bool login_as_admin()
    {
        string login;
        string password;
        cin.ignore();
        getline(cin, login);
        getline(cin, password);
        if(c1.log_in(login, password))
            return true;
        return false;
    }
};