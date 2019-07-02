#pragma once
#include <iostream>
#include <fstream>
#include <windows.h>
#include <string.h>
#include <cstring>
using namespace std;

class account
{
	char password[8];
public:
	void SetPassword() {
		fstream fp;
		fp.open("password.txt", ios::in);
		fp.read(password, sizeof(password));
	}
	char* GetPassword() {
		return password;
	}
	void showdata();

};

