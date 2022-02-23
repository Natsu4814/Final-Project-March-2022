#include "header.h"

class My_String : std::string
{

    int count = 1;
    std::string* strs;
public:
    std::string* tok(std::string str ,char delim)
    {
        int len_of_str = str.length();
        int len_of_part = 0;
        int start_of_for = 0;
        for (int i = 0; i < len_of_str; i++)
        {
            if (str[i] == delim)
                count += 1;
        }
        strs = new std::string[count];


        do
        {
            len_of_part++;
        } while (str[len_of_part] != delim);


        for(int q = 0; q < count;q++)
        { 

            for (int i = start_of_for; i < start_of_for + len_of_part; i++)
            {
                strs[q] += str[i];
            }
            start_of_for = start_of_for + len_of_part + 1;
            len_of_part = 0;
            for (int i = start_of_for; i < len_of_str; i++)
            {
                if (str[i] != delim)
                    len_of_part++;
                else if(str[i] == delim) break;
            }
        }

        return strs;
    }

    std::string* return_strs()
    {
        return strs;
    }

    void print()
    {
        for (int i = 0; i < count; i++)
            std::cout << strs[i] << " ";
    }
    
    ~My_String()
    {
        delete[] strs;
    }
};

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
                cout << i+1 << "." << types_coffee.at(i).coffee_name << " M:" << types_coffee.at(i).price_m << " L:" << types_coffee.at(i).price_l << "\n";
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
};

struct Guest_BIO
{
    string name;
    string phone_number;
    int count = 0;
};

class Guest
{
    vector<Guest_BIO> guests;
public:

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
    My_String string_to_tok;
public:
    void save_to_file(Coffee_Shop& c1)
    {   
        vector<Type_Coffee> coffee_buffer = c1.get_coffee_types();
        ofstream fin;
        fin.open("coffee.txt");
        for(int i = 0; i < coffee_buffer.size(); i++)
        {
            fin << "\n" << coffee_buffer[i].coffee_name << " " << coffee_buffer[i].price_m << " " << coffee_buffer[i].price_l;
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
    }
};