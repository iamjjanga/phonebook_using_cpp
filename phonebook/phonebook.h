#pragma once
#include <iostream>
#include <string.h>
using namespace std;

class phoneBook {
	char name[20], phonenum[15];
public:
	void getdata();
	void showdata();
	char *getname() {
		return name;
	}
	char *getphone() {
		return phonenum; 
	}
};