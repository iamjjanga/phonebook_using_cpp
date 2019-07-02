#include <conio.h>
#include "account.h"
#include "phonebook.h"
using namespace std;

#define ESC 27
#define RETURN 13

extern void CheckPassword();
extern void ChangePassword();

void new_record();
void display_record();
void search_choice();
void search_by_name();
void search_by_phonenum();
void incorrect_Choice();
void _delete();
void remove_file();
int record_size();
int menu();

phoneBook book;

int record_num = 0;

int main() {
	// console
	system("mode con cols=80 lines=40");

	// certification
	CheckPassword();
	
	int choice, exiter = 0;

	while (1) {
		cout << "\n\n\t\t*************CPP PHONE BOOK*************\n\n";
		cout << "\t\t Choice 1. Add New Record.\n\n";
		cout << "\t\t Choice 2. Show All Record.\n\n";
		cout << "\t\t Choice 3. Search (by Tele Num or Name).\n\n";
		cout << "\t\t Choice 4. Delete Record.\n\n";
		cout << "\t\t Choice 5. Change Your Acoount Password.\n\n";
		cout << "\t\t Choice 6. Exit this Program.\n";
		cout << "\n\n\t\t***************************************\n\n";
		cout << "\t\t Which one You want to choose  : ";
		
		record_num = record_size();	// check count of data input
		cin >> choice;

		switch (choice) {
		case 1:
			new_record();
			break;
		case 2:
			display_record();
			break;
		case 3:
			search_choice();
			break;
		case 4:
			_delete();
			break;
		case 5:
			ChangePassword();
			break;
		case 6:
			cout << "\n\n\n\n\t\tTHANKS FOR USING PHONEBOOK PROGRAM \n\n\n\t\tHAVE A NICE DAY!\n\n";
			return 0;
		default:
			incorrect_Choice();
		}
	}
}

/* 
add new record
(input : name, phonenumber)
*/
void new_record() {
	ofstream fout;

	fout.open("phonebook_log.dat", ios::app | ios::out);
	if (fout.fail()) {
		cout << "new_record file open failed.\n";
		exit(1);
	}

	book.getdata();
	record_num++;
	fout.write((char *)&book, sizeof(book));
	system("cls");
	cout << " \n\n\t\tRecord Enter Success!!!!";
	fout.close();
};

void display_record() {
	ifstream fin;
	fin.open("phonebook_log.dat", ios::in | ios::binary);
	if (fin.fail() || record_num == 0) {
		system("cls");
		cout << "\n\n\t\t\tNo record exist. Please Make first.\n";
		Sleep(1000);
		system("cls");
		return;
	}
	cout << "\n\n\t\t Records in Phone Book:\n";
	fin.read((char *)&book, sizeof(book));
	system("cls");
	cout << "\n\n\t\t\t--------- RECORDS ---------";
	cout << "\n\n\t\t\t " << "Name" << "\t" << "Phone Number\n";
	cout << "\t\t\t---------------------------\n";
	while (!(fin.eof())) {
		book.showdata();
		fin.read((char *)&book, sizeof(book));
		cout << "\t\t";
	}
	cout << "\t---------------------------";
	cout << "\n\n\t\t\t" << record_num << " Records are founded";
	
	cout << "\n\n\t\t\tGo to menu PRESS ENTER Key!";
	if (menu() == RETURN)
		return;
};

void search_choice() {
	int choice;

	system("cls");
	cout << "\n\n\t\t Choice 1. Search by name";
	cout << "\n\n\t\t Choice 2. Search by Telephone number";
	cout << "\n\n\n\t\t Which path do you want to search?  : ";
	cin >> choice;

	do {
		switch (choice) {
		case 1:
			search_by_name();
			break;
		case 2:
			search_by_phonenum();
			break;
		default:
			cout << "please choose 1 or 2....";
		}
		cout << "\n\n\t\t\tGo to menu -> PRESS ESC Key!\n\t\t\tKeep Going -> PRESS ENTER Key!";
	} while (!(menu() == ESC));
};

void search_by_name() {
	fstream fin;
	char temp[15];
	int flag;

	fin.open("phonebook_log.dat", ios::in | ios::binary);
	system("cls");
	cout << "\n\n\n\t\t\tEnter Name : ";
	cin >> temp;
	
	fin.read((char *)&book, sizeof(book));
	fin.seekg(0, ios::beg);
	flag = 0;
	while (!fin.eof()) {
		if (strcmp(temp, book.getname()) == 0) {
			flag = 1;		// if target match is succeed, flag is on
			cout << "\n\t\t\tName\tPhone Num.\n";
			book.showdata();
			break;
		}
		fin.read((char *)&book, sizeof(book));
	}
	fin.close();
	if (flag == 0)
		cout << "\n\n\t\t\t--- SORRY... That NAME Not found---\n";
};

void search_by_phonenum() {
	fstream fin;
	char number[15];
	int flag;

	fin.open("phonebook_log.dat", ios::in | ios::binary);
	system("cls");
	cout << "\n\n\n\t\t\tEnter Phone number : ";
	cin >> number;
	fin.seekg(0, ios::beg);

	flag = 0;
	fin.read((char *)&book, sizeof(book));
	while (!fin.eof()) {
		if (strcmp(number, book.getphone()) == 0) {
			flag = 1;
			cout << "\n\t\t\tName\tPhone Num.\n";
			book.showdata();
			break;
		}
		fin.read((char *)&book, sizeof(book));
	}

	fin.close();
	if (flag == 0)
		cout << "\n\n\t\t\t-----That NUMBER Not found-----\n";
};

void incorrect_Choice() {
	cout << "\n\n\t\t\t INCORRECT CHOICE \n\n\t\t\t   TRY AGAIN\n\n ";
	cout << "\7";
	system("pause");
	system("cls");
};

void _delete() {
	ifstream fin;
	ofstream fout;
	int flag = 0, correct = 1, exp;
	char temp[20];
	char choose;
	
	while (correct) {
		system("cls");
		cout << "\n\n\t\t Remove all data [y/n]? ";
		cin >> choose;
		switch (choose) {
		case 'y':
		case 'Y':
			remove_file();
			return;
		case 'n':
		case 'N':
			correct = 0;
			break;
		default:
			cout << "\n\n\t\t You type wrong choice...";
			Sleep(1000);
		}
	}

	fin.open("phonebook_log.dat", ios::in | ios::binary);
	fout.open("phonebook_log_temp.dat", ios::out | ios::binary);
	cout << "\n\n\t\t Input Name to Remove  : ";
	cin >> temp;

	// search line to delete
	for(int i = 0; i < record_num; i++){
		fin.read((char *)&book, sizeof(book));
		if (strcmp(temp, book.getname()) == 0) {
			flag = 1;
			continue;
		}
		fout.write((char *)&book, sizeof(book));
	}
	if(flag == 1)
		record_num--;
	else {
		cout << "\n\n\n\t\t\t No matched Name in Phonebook!.... Go to menu";
		Sleep(1000);
		system("cls");
		return;
	}
	
	fin.close();
	fout.close();

	try {
		if (exp = remove("phonebook_log.dat"))
			throw exp;
	}
	catch (int exp) {
		system("cls");
		cout << "\n\n\t\t\tremove failed....";
		Sleep(1000);
		exit(1);
	}
	try {
		if (exp = rename("phonebook_log_temp.dat", "phonebook_log.dat"))
			throw exp;
	}
	catch (int exp) {
		system("cls");
		cout << "\n\n\t\t\trename failed....";
		Sleep(1000);
		exit(1);
	}

	cout << "\n\n\n\t\t Delete Success!";
	Sleep(1000);
	system("cls");
}

void remove_file() {
	if (!remove("phonebook_log.dat"))
		cout << "\n\n\n\t\t\tremove file success!";
	else
		cout << "\n\n\n\t\t\tremove file failed!.";
	Sleep(1000);
	system("cls");
	record_num = 0;
}


int menu() {
	char c = 0;
	getchar();
	while (1) {
		if (_kbhit()) {
			if (!(c = _getch()))
				c = _getch();
			break;
		}
	}
	system("cls");

	if (c == ESC)
		return ESC;
	else if (c == RETURN)
		return RETURN;
	else
		return 0;
	
}

int record_size() {
	long size;
	fstream fp;
	fp.open("phonebook_log.dat", ios::in | ios::binary);
	fp.seekg(0, ios::end);
	size = fp.tellg() / 35;

	return size;
}