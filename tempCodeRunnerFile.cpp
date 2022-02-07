#include "header.h"
#include "structs.cpp"

char yn;

int main()
{
    Coffee_Shop s1;
    Guest g1;
    cout << "Are you a new user/admin(n/a): ";
    char yn;
    cin >> yn;
    if(yn == 'a'|| yn == 'A')
    {
        if(s1.logIn() == true)
        {
            s1.make_choise();
        }
    }
    else
    {
        g1.show_menu();
    }
}