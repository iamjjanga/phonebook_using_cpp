#include "account.h"

account acc;

char in_pw[8];

void CheckPassword() {
	char check_pw[8];
	fstream pw_fin;
	acc.SetPassword();

	for (int i = 0; i < 3; i++) {
		cout << "\n\n\n\t\tEnter password:";
		cin >> check_pw;
		
		if (strcmp(check_pw, acc.GetPassword()) != 0) {
			cout << " \n\n\t\t\tIncorrect password\n\n\t\t";
			getchar();
			Sleep(1000);
			system("cls");
			Sleep(1000);
		}
		else { // password target success
			system("cls");
			return;
		}
		if (i == 2) {// last chance failed.;
			cout << "\n\n\n\t\t\t Incorrect 3 times. Are you sniffing now? \n\n\t\t";
			exit(1);
		}
	}
}

void ChangePassword()
{
	system("cls");
	char old_pw[8];

	while (1) {
		cout << "\n\n\n\t\t\tEnter old password: ";
		cin >> old_pw;
		if (strcmp(old_pw, acc.GetPassword()) != 0)
		{
			cout << " \n\n\t\t\tIncorrect password\n\n\t\t";
			getchar();
			cout << "\tTry Again";
			system("cls");
		}
		else
		{
			cout << "\n\n\t\t\tEnter New Password: ";
			char new_pw[8];
			cin >> new_pw;
			ofstream pw_fout;
			pw_fout.open("password.txt");
			pw_fout << new_pw;
			cout << "\n\n\t\t\tPASSWORD CHANGED SUCESSFULLY!!!!\n\n";
			Sleep(1000);
			system("cls");
			return;
		}
	}
}