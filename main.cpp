#include "header.h"
#include "structs.cpp"

char yn;

int main()
{
start:
    Coffee_Shop shop;
    Coffee_Shop_Admin s1;
    Guest g1;
    cout << "> Are you admin(y/n): ";
    char yn;
    cin >> yn;
    if(yn == 'y'|| yn == 'Y')
    {
        if(s1.logIn() == true)
        {
            do
            {
                cout << "> Enter name: ";
                string name;
                getline(cin, name);
                cout << "> Enter price for medium cup: ";
                int price_m;
                cout << "> Enter price for large cup: ";
                int price_l;
                s1.add_coffee_type(name, price_m,  price_l);
                cout << "> Would you liek to continue(y/n): ";
                cin >> yn;
            } while(yn == 'y');
            goto start;
        }
    }
    else
    {
        g1.show_menu();
        shop.make_choise();
    }
}