#include "header.h"
#include "system.cpp"

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

	int log_in(string phone_number)
	{
		for(int i = 0; i , guests.size(); i++)
		{
			if(guests.at(i).phone_number == phone_number)
				return i;
		}
		return -1;
	}

	vector<Guest_BIO> get_guests_vector()
	{
		return guests;
	}
};

class Receipt
{
	string person_name;
	string coffee_name;
	double price;
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

class IO_Manager
{
	My_String string_to_tok;
	vector<Type_Coffee> coffee_buffer;
	vector<Type_Topping> topping_buffer;
	vector<Guest_BIO> people_buffer;
public:
	IO_Manager()
	{

	}
//Menu saving
	void save_to_file(Coffee_Shop c1)
	{
		ofstream fout;   
		coffee_buffer = c1.get_coffee_types();
		fout.open("coffee.txt");
		for(int i = 0; i < coffee_buffer.size(); i++)
		{
			fout << coffee_buffer.at(i).coffee_name << " " << coffee_buffer.at(i).price_m << " " << coffee_buffer.at(i).price_l;
			if(i < coffee_buffer.size()-1)
				fout << "\n";    
		}
		fout.close();
		//Topping save
		topping_buffer = c1.get_topping_types();
		fout.open("toppings.txt");
		for(int i = 0; i < topping_buffer.size(); i++)
		{
			fout << topping_buffer.at(i).topping << " " << topping_buffer.at(i).price;
			if(i < topping_buffer.size()-1)
				fout << "\n";
		}
	}

	void load_into_menu(Coffee_Shop& c1)
	{
		string line;
		ifstream fin;
		string* strings;
		string name;
		fin.open("coffee.txt");
		while (!fin.eof())
		{
			getline (fin,line); 
			strings = string_to_tok.tok(line, ' ');
			name = strings[0];
			double medium_cup = stod(strings[1]);
			double big_cup = stod(strings[2]);
			c1.add_coffee_type(name, medium_cup, big_cup);
		}
		fin.close();
		fin.open("toppings.txt");
		while(!fin.eof())
		{
			getline(fin, line);
			strings = string_to_tok.tok(line, ' ');
			name = strings[0];
			double price = stod(strings[1]);
			c1.add_topping_type(name, price);
		}
		fin.close();
	}
//Operations with users
	void save_users(Guests& g1)
	{
		people_buffer = g1.get_guests_vector();
		ofstream fout;
		fout.open("guests.txt");
			for(int i = 0; i < people_buffer.size(); i++)
			{
				fout << people_buffer.at(i).name << " " << people_buffer.at(i).phone_number;
				if(i < topping_buffer.size()-1)
					fout << "\n";
			}
		fout.close();
	}
	void load_users(Guests g1)
	{
		string line;
		string phone_number;
		string name;
		ifstream fin;
		string* strings;
		fin.open("guests.txt");
		while(!fin.eof())
		{
			getline(fin, line);
			strings = string_to_tok.tok(line, ' ');
			name = strings[0];
			phone_number = strings[1];
			g1.sign_up(name, phone_number);
		}
	}
};

class Menu_Handler
{
	Coffee_Shop c1;
	Guests g1;
	IO_Manager manager;
	char yes_no;

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
		manager.load_users(g1);
		cout << "\t\t\t\t\t\t\t\tWelcome\n";
		cout << "> Enter your phone number: ";
		cin >> phone_number;
		Guest_BIO *new_guest = login_as_guest(phone_number);
		
	}

	Guest_BIO* login_as_guest(string phone_number)
	{
		manager.load_users(g1);
		int switcher;
		vector<Guest_BIO> guest_box = g1.get_guests_vector();
		int guest_number;
		do
		{
			guest_number = g1.log_in(phone_number);
			if(guest_number >= 0)
			{
				Guest_BIO *ptr = &guest_box[guest_number];
				return ptr;
			}
			if(g1.log_in(phone_number) == -1)
			{
				cout << "> Try again, or register account(1/2): ";
				cin >> switcher;
				if(switcher == 1)
				{
					break;
				}
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
		} while (g1.log_in(phone_number)==-1);
	}

	bool login_as_admin()
	{
		string login;
		string password;
		do
		{
		cin.ignore();
		cout << "> Enter login: ";
		getline(cin, login);
		cout << "Enter password: ";
		getline(cin, password);
		if(c1.log_in(login, password))
		{
			return true;
		}
		}while(!c1.log_in(login, password));
	}
};
