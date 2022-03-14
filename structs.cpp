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
		int num = 0;
		string to_replace = "_";
		Guest_BIO new_guest;
		for(int i = 0; i < name.size(); i++)
		{
			if(name.at(i) == ' ')
			{
				num = i;
			}
		}
		name.replace(num, 1, to_replace);
		new_guest.name = name;
		new_guest.phone_number = phone_number;
		new_guest.count = 0;
		guests.push_back(new_guest);
		return true;
	}

	int log_in(string phone_number)
	{
		for(int i = 0; i < guests.size(); i++)
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
	string topping_name;
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
};

class IO_Manager
{
	My_String string_to_tok;
	vector<Type_Coffee> coffee_buffer;
	vector<Type_Topping> topping_buffer;
	vector<Guest_BIO> people_buffer;
public:
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
//Menu loading	
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
//User saving
	void save_users(Guests g1)
	{
		people_buffer = g1.get_guests_vector();
		ofstream fout;
		fout.open("guests.txt");
			for(int i = 0; i < people_buffer.size(); i++)
			{
				fout << people_buffer.at(i).name << " " << people_buffer.at(i).phone_number;
				if(i < people_buffer.size()-1)
					fout << "\n";
			}
		fout.close();
	}
//User loading	
	void load_users(Guests &g1)
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

	int switcher;

	string coffee_name;
	double price_m;
	double price_l;

	string topping_name;
	double price;
	
	string name;
	string phone_number;
	string password;
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
		if(phone_number == "admin")
		{
			cin.ignore();
			cout << "Enter password: ";
			getline(cin, password);
			if(password == "admin")
			{
				do
				{					
					cout << "Coffee or topping(1/2): ";
					cin >> switcher;
					if(switcher == 1)
					{
						cin.ignore();
						cout << "Enter name of coffee: ";
						getline(cin, coffee_name);
						cout << "Enter price for medium cup: ";
						cin >> price_m;
						cout << "Enter price fo large cup: ";
						cin >> price_l;
						c1.add_coffee_type(coffee_name, price_m, price_l);
						manager.save_to_file(c1);
					}
					else if(switcher == 2)
					{
						cin.ignore();
						cout << "Enter name of topping: ";
						getline(cin, topping_name);
						cout << "Enter price for it: ";
						cin >> price;
						c1.add_topping_type(topping_name, price);
						manager.save_to_file(c1);
					}
					else
					{
						cout << "Invalid value";
						yes_no = false;
					}
				} while (yes_no == false);
			}
		}
		else
		{
			Guest_BIO *new_guest = login_as_guest(g1, phone_number);
			show_coffee_shop_menu();
		}
	}

	Guest_BIO* login_as_guest(Guests g1 ,string phone_number)
	{
		vector<Guest_BIO> guest_box = g1.get_guests_vector();
		int guest_number;
		guest_number = g1.log_in(phone_number);
		Guest_BIO *ptr;
		if(guest_number >= 0)
		{
			ptr = &guest_box[guest_number];
		}
		else if(guest_number == -1)
		{
			cin >> switcher;
			if(switcher == 1)
			{
				char yn = 'n';
				do
				{
					getline(cin, phone_number);
					guest_number = g1.log_in(phone_number);
					if(guest_number >= 0)
					{
						ptr = &guest_box[guest_number];
					}
					if(guest_number == -1)
					{
						cout << "Would you like to try again or sing up(1/2): ";
						cin >> switcher;
						if(switcher == 1)
						{
							yn == 'y';
						}		
					}	
				} while(yn == 'y');
			}
			if(switcher == 2)
			{
				cout << "Enter your name: ";
				cin.ignore();
				string name;
				getline(cin, name);
				cout << "Enter your phone number";
				getline(cin, phone_number);
				g1.sign_up(name, phone_number);
				guest_number = g1.log_in(phone_number);
				ptr = &guest_box[guest_number];
				manager.save_users(g1);
			}		
		}
		return ptr;
	}
};
