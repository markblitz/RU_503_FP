#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "BankAccount.h"

using namespace std;

BankAccount::BankAccount()
{
	double read_balance;
	ifstream account_info;
	account_info.open("AccountInfo/Account_Balance.txt");
	if (account_info.is_open()) {
		account_info >> fixed >> setprecision(4) >> read_balance;
		balance = read_balance;
		cout << "Bank balance has been read!\n";
	}
	else {
		cout << "Cannot read bank account balance!\n";
	}
	account_info.close();
}

BankAccount::~BankAccount()
{
	double write_balance = balance;
	ofstream account_info;
	account_info.open("AccountInfo/Account_Balance.txt");
	if (account_info.is_open()) {
		account_info << fixed << setprecision(4) << write_balance;
		cout << "Bank balance has been writen!\n";
	}
	else {
		cout << "Cannot read bank account balance!\n";
	}
	account_info.close();
}

void BankAccount::Deposit(double input)
{
	balance += input;
}

void BankAccount::Withdraw(double input)
{
	balance -= input;
}

double BankAccount::Check_Banalce() const
{
	return balance;
}
