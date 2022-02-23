#include "header.h"
#include "structs.cpp"

char yes_no;

int main()
{
    Coffee_Shop c1;
    IO_Manager manager;
    manager.load_into_menu(c1);
    c1.show_menu();
    manager.save_to_file(c1);
}