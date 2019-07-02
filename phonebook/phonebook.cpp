#include "phonebook.h"

void phoneBook::getdata()
{
	cout << "\n\t\tEnter Name : ";
	cin >> name;
	cout << "\n\t\tEnter Phone Num. : ";
	cin >> phonenum;
}
void phoneBook::showdata()
{
	cout << "\n";
	cout << "\t\t\t " << name;
	cout << "\t" << phonenum << endl;
}