// This program manages an inventory system.

#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<iomanip>

using namespace std;

class Part
{
	public:
		int part_number;
		string description;
		int quantity;
		double unitprice;
};

// This function will read the file and organize the information in the array.
Part part_list(string strng);

// This function will be used to print the item number, item name, item quantity, and item price.
void print_parts(Part [], int);

// This function will let the user add a new item to the inventory.
void new_part(Part [], int&);

// This function will let the user modify a item in the inventory.
void modify_part(Part [], int);

int main()
{
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);
	
	Part array[100];	// this is the array to hold objects.
	int count = 0;		// this is count to tell how many different parts in array.
	float total = 0;
	string strng;
	ofstream out_file;
	
	ifstream in_file("inventory.txt");
	if(in_file.fail())
	{
		cout<< "Input file could not be opened! Terminating program..." << endl;
		exit(1);
	}
	// This is used to create the array from the file.
	while(!in_file.eof())
	{
		getline(in_file, strng);
		
		if(strng.length() > 0)
		{
			array[count] = part_list(strng);
			count++;
		}
		
	}
	
	int input = 0;
	while(cin.good() && input != 5)
	{
		// This is the menu for the user to read
		cout<< "Please enter the value of the task you want to perform: " << endl;
		cout<< "1) Print parts" << endl;
		cout<< "2) Enter a new part" << endl;
		cout<< "3) Modify a part" << endl;
		cout<< "4) Print total" << endl;
		cout<< "5) Exit program" << endl;
		cout<< "Your choice: ";
		cin >> input;
		cout<< endl;
		
		switch(input)
		{
			case 1:
				print_parts(array, count);
				cout<< endl;
				break;
				
			case 2:
				cin.ignore();
				new_part(array, count);
				break;
				
			case 3:
				cin.ignore();
				modify_part(array, count);
				break;
					
			case 4:				
				// This calculates the total price for all units in the system
				cout<< "Total cost of inventory: $";
				for(int j = 0; j < count; j++)
				{
					total = (array[j].unitprice * array[j].quantity) + total;
				}
				
				cout<< total << endl << endl;
				total = 0;
				break;
					
			case 5:
				// This writes the array with the changes made onto the file.
				out_file.open("inventory.txt");
				if(out_file.fail())
				{
					cout<< "Output file could not be opened! Terminating program..." << endl;
					exit(1);
				}
				
				for(int x = 0; x < count; x++)
				{
					out_file << right << setw(0)  << array[x].part_number;
					out_file << " ";
					out_file << left  << setw(2)  << array[x].description;
					out_file << right << setw(4)  << array[x].quantity;
					out_file << right << setw(10) << array[x].unitprice << endl;
				}
				
				in_file.close();
				out_file.close();
				
				return 0;
				
			default:
				cout<< "Invalid choice." << endl;
		}
	
	}

}

Part part_list(string strng)
{
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);
				
	int i = 0;
	Part list[100];
	
	list[i].part_number = atoi(strng.c_str());
	list[i].description = strng.substr(2, 15);
	
	string temp;
	int tempp;
	temp = strng.substr(17, 4);
	tempp = atoi(temp.c_str());
	list[i].quantity = tempp;
	
	string temp1;
	int tempp1;
	temp1 = strng.substr(26, 7);
	tempp1 = atof(temp1.c_str());
	list[i].unitprice = tempp1;
	
	i++;
	
	return list[ i-1 ];

}

void print_parts(Part array[], int count)
{
	if(count == 0)
	{
		cout<< "Empty Inventory.\n" << endl;
		return;
	}
	
	for(int i = 0; i < count; i++)
	{
		cout<< array[i].part_number << " " << array[i].description;
		cout<< right << setw(4) << array[i].quantity;
		cout<< right << setw(4) << "$" << array[i].unitprice << endl;
		cout<< endl;
	}
	
}

void new_part(Part array[], int& count)
{	
	array[count].part_number = count + 1;
	
	cout<< "New part description: ";
	getline(cin, array[count].description);
	array[count].description.resize(15,' ');
	
	cout<< "New part quantity: ";
	cin >> array[count].quantity;
	
	cout<< "New part unit price: ";
	cin >> array[count].unitprice;
	cout<< endl;
		
	count++;
}

void modify_part(Part array[], int count)
{	
	int x = 0;
	
	cout<< "Enter part number to modify: ";
	cin >> x;
	
	if(x <= count)
	{
		x--;
	
		cout<< array[x].part_number << " " << array[x].description << array[x].quantity;
		cout<< "    $" << array[x].unitprice << endl << endl;
		cin.ignore();
		
		cout<< "Enter item: ";
		getline(cin, array[x].description);
		array[x].description.resize(15,' ');
		
		cout<< "Enter quantity: ";
		cin >> array[x].quantity;
		
		cout<< "Enter cost: ";
		cin >> array[x].unitprice;
		cout<< endl;
	}
	else
	{
		cout<< "That part does not exist." << endl;
		cout<< "The available parts are: 0 - " << count << endl << endl;
	}
}
