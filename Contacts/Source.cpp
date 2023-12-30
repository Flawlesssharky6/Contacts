#include <iostream>
//#include <string>
#include <fstream>
#include <vector>
#include "Contacts.h"
using namespace std;
const char COMMA = ',';
string chopper(string& s, char c);
bool get_data(vector <Contacts>& v);
void displayMenu();
int readOption();
void addContact(vector<Contacts>& v);
void deleteContact(vector<Contacts>& v);
void editContact(vector<Contacts>& v);
void displayContact(vector<Contacts>& v);
void displayList(vector<Contacts>& v);
void shellSort(vector<Contacts>& v);
int binSearch(string key, vector<Contacts>& v);
string getLastName();
void putData(vector<Contacts>& v);
template<class CType>
void swapper(CType& a, CType& b);
int main()
{
	vector<Contacts> contacts;
	int choice;
	if (get_data(contacts))
	{
		do
		{
			displayMenu();
			choice = readOption();
			switch (choice)
			{
			case 1:
				addContact(contacts);
				break;
			case 2:
				deleteContact(contacts);
				break;
			case 3:
				editContact(contacts);
				break;
			case 4:
				displayContact(contacts);
				break;
			case 5:
				displayList(contacts);
				break;
			}
		} while (choice != 6);
	}
	putData(contacts);
	return 0;
}
bool get_data(vector <Contacts>& v)
{
	string fName;
	string lName;
	string phone;
	string lineIn;
	ifstream fin;
	fin.open("contacts.csv");
	bool OK = true;
	if (fin.fail())
	{
		cout << "Unable to open file." << endl;
		OK = false;
	}
	else
	{
		while (getline(fin, lineIn))
		{
			Contacts c;  //Create object of Contacts class
			fName = chopper(lineIn, COMMA);
			lName = chopper(lineIn, COMMA);
			phone = chopper(lineIn, COMMA);
			c.setFirstName(fName);
			c.setLastName(lName);
			c.setPhone(phone);
			v.push_back(c);
		}

		fin.close();
		shellSort(v);
	}
	return OK;
}
string chopper(string& s, char c) //Function bodies go after main
{     //   The string is passed by reference. Function can change it
	string back;
	int loc;
	loc = s.find(c);  //find separating character
	if (loc != -1)  //Is there another separator?
	{
		back = s.substr(0, loc);  //assign 1st field to back
		s = s.substr(loc + 1);   // Remove 1st field
	}
	else //no!
	{
		back = s;
		s = "";
	}
	return back;	//Return 1st field	
}
void displayMenu()
{
	cout << " ---------------------------------------------" << endl;
	cout << " |Contacts List Menu                         |" << endl;
	cout << " |Select a task:                             |" << endl;
	cout << " |  1. Add a contact                         |" << endl;
	cout << " |  2. Delete a contact                      |" << endl;
	cout << " |  3. Edit phone number                     |" << endl;
	cout << " |  4. Display a contact                     |" << endl;
	cout << " |  5. Display list                          |" << endl;
	cout << " |  6. End program                           |" << endl;
	cout << " ---------------------------------------------" << endl << endl;
}
int readOption()
{
	int task = 0;
	do
	{
		cin >> task;
		if (task < 1 || task > 6)
			cout << " Invalid task! Try again!";
	} while (task < 1 || task > 6);
	return task;
}


void addContact(vector<Contacts>& v)
{
	Contacts newContact; //This creates an object of Part class
	string lastName, firstName, phone;
	int i;
	i = v.size() - 1;
	v.resize(v.size() + 1);
	lastName = getLastName();
	newContact.setLastName(lastName);
	while (i >= 0 && lastName < v[i].getLastName())
	{
		v[i + 1] = v[i];
		i--;
	}
	cout << "Enter first name";
	cin >> firstName;
	newContact.setFirstName(firstName);
	do
	{
		cout << "Enter phone: 555-555-5555: ";
		cin >> phone;
	} while (!newContact.setPhone(phone));
	v[i + 1] = newContact;
}
void deleteContact(vector<Contacts>& v)
{
	string lastName;
	int index;
	lastName = getLastName();
	index = binSearch(lastName, v);
	if (index != -1)
	{
		for (int i = index; i < v.size() - 1; i++)
			v[i] = v[i + 1];
		v.resize(v.size() - 1);
	}
	else
		cout << lastName << " not found!" << endl;
}
void editContact(vector<Contacts>& v)
{
	string lastName, phone;
	int index, choice;
	lastName = getLastName();
	index = binSearch(lastName, v);
	if (index != -1)
	{
		cout << "Current values:" << endl;
		v[index].display();
		do
		{
			cout << "Enter new phone: ";
			cin >> phone;
		} while (!(v[index].setPhone(phone)));
	}
	else
		cout << lastName << " not found!";

}
void displayContact(vector<Contacts>& v)
{
	string lastName;
	int index;
	lastName = getLastName();
	index = binSearch(lastName, v);
	if (index != -1)
	{
		v[index].display();
	}
	else
		cout << lastName << " not found!" << endl;
}
void displayList(vector<Contacts>& v)
{
	for (int i = 0; i < v.size(); i++)
	{
		v[i].display();
	}
}
void shellSort(vector<Contacts>& v)
{
	bool flag = true;
	int i, numLength = v.size();
	int d = numLength;
	while (flag || (d > 1))    // bool flag 
	{
		flag = false;  //reset flag to 0 to check for
		// future swaps    
		d = (d + 1) / 2;

		for (i = 0; i < (numLength - d); i++)
		{
			if (v[i + d].getLastName() < v[i].getLastName())
			{
				swapper(v[i], v[i + d]);
				flag = true;     //tells swap has occurred
			}
		}
	}
}
int binSearch(string key, vector<Contacts>& v)
{
	int first = 0, last = v.size() - 1, middle, pos = -1;
	bool found = false;
	while (!found && first <= last)
	{
		middle = (first + last) / 2;
		if (v[middle].getLastName() == key)
		{
			found = true;
			pos = middle;
		}
		else if (v[middle].getLastName() > key)
			last = middle - 1;
		else
			first = middle + 1;
	}
	return pos;
}string getLastName()
{
	string lastName;
	cout << "Enter last name of contact to process: ";
	cin >> lastName;
	return lastName;
}
void putData(vector<Contacts>& v)
{
	ofstream fout;
	fout.open("contacts.csv", ofstream::out);
	for (int i = 0; i < v.size(); i++)
	{
		fout << v[i].getLastName() << COMMA << v[i].getFirstName()
			<< COMMA << v[i].getPhone() << endl;
	}
	fout.close();
}
template<class CType>
void swapper(CType& a, CType& b)
{
	CType temp;
	temp = a;
	a = b;
	b = temp;
}