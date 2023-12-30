#include "Contacts.h"
void Contacts::setLastName(string l)
{
	_lastName = l;
}
void Contacts::setFirstName(string f)
{
	_firstName = f;
}
bool Contacts::setPhone(string p)
{
	bool OK = validatePhone(p);
	if (OK)
		_phone = p;
	return(OK);
}
string Contacts::getLastName()
{
	return _lastName;
}
string Contacts::getFirstName()
{
	return _firstName;
}
string Contacts::getPhone()
{
	return _phone;
}
void Contacts::display()
{
	cout << "Name: " << _lastName << ", " << _firstName << " Phone: "
		<< _phone << endl;
}