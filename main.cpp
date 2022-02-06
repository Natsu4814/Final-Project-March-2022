#include "header.h"
#include "structs.cpp"

char yn;

int main()
{
start:
    Coffee_Shop s1;
    char yn;
    cin >> yn;
    if(yn == 'y'|| yn == 'Y')
    {
        if(s1.logIn() == true)
        {
            
        }
        else
        {
            goto start;
        }
    }
    else{}
}