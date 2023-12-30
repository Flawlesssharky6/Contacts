#pragma once
#include <iostream>
#include <string>
using namespace std;
class Contacts
{
private:
	string _lastName;
	string _firstName;
	string _phone;
	bool validatePhone(string p)  //This is private, not accessible
	{							  // outside class
		bool OK = true;
		for (int i = 0; i < p.length(); i++)
		{
			if ((i == 3 || i == 7) && p[i] != '-')
				OK = false;
			else if ((i != 3 && i != 7) && !isdigit(p[i]))
				OK = false;
		}
		return OK;
	}
public:
	void setLastName(string l);
	void setFirstName(string f);
	bool setPhone(string p);
	string getLastName();
	string getFirstName();
	string getPhone();
	void display();
};
