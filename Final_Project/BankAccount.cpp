#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <time.h>
#include "BankAccount.h"

using namespace std;

BankAccount::BankAccount()
{
	double read_balance;
	ifstream account_file;
	account_file.open("AccountInfo/Bank_Balance.txt" , ios::in);
	if (account_file.is_open()) {
		account_file >> fixed >> setprecision(4) >> read_balance;
		balance = read_balance;
	//	cout << "Bank balance has been read!\n";
	}
	else {
		cout << "Cannot read bank account balance!\n";
	}
	account_file.close();
}

BankAccount::~BankAccount()
{
	double write_balance = balance;
	ofstream account_file;
	account_file.open("AccountInfo/Bank_Balance.txt" , ios::out);
	if (account_file.is_open()) {
		account_file << fixed << setprecision(4) << write_balance;
	//	cout << "Bank balance has been writen!\n";
	}
	else {
		cout << "Cannot read bank account balance!\n";
	}
	account_file.close();
}

void BankAccount::WriteBalanceBack()
{
	double write_balance = balance;
	ofstream account_file;
	account_file.open("AccountInfo/Bank_Balance.txt", ios::out);
	if (account_file.is_open()) {
		account_file << fixed << setprecision(4) << write_balance;
		//	cout << "Bank balance has been writen!\n";
	}
	else {
		cout << "Cannot read bank account balance!\n";
	}
	account_file.close();
}

void BankAccount::Deposit(double input)
{
	balance += input;
}

void BankAccount::Withdraw(double input)
{
	balance -= input;
}

double BankAccount::CheckBanalce() const
{
	return balance;
}

void BankAccount::WriteHistory(string input_event, double input_amount)
{
	time_t t;
	time(&t);
	struct tm buf;
	localtime_s(&buf, &t);
	//cout << "local time: " << buf.tm_year + 1900 << "/" << buf.tm_mon + 1 << "/" << buf.tm_mday << " " 
	//	<< buf.tm_hour  << ":" << buf.tm_min << ":" << buf.tm_sec << endl;

	ofstream history;
	history.open("AccountInfo/Bank_History.txt", ios::app);
	if (history.is_open()) {
		history	<< left << setw(20) << input_event;
		history << left << setw(20) << fixed << setprecision(4) << input_amount;
		history << buf.tm_year + 1900 << "/" << buf.tm_mon + 1 << "/" << buf.tm_mday << " "
			<< buf.tm_hour << ":" << buf.tm_min << ":" << left << setw(10) << buf.tm_sec;
		history << left << setw(20) << CheckBanalce();
		history << endl;
//		cout << "Bank record has been writen!\n";
	}
	else {
		cout << "Cannot write bank record balance!\n";
	}
	history.close();
}

void BankAccount::PrintHistory() const
{
	ifstream history;
	string fileinput;
	history.open("AccountInfo/Bank_history.txt", ios::in);
	if (history.is_open()) {
		cout << setw(20) << left << "EVENT"
			<< setw(20) << left << "AMOUNT" 
			<< setw(24) << left << "TIME & DATE" 
			<< setw(20) << left << "BALANCE" << endl;
		while (getline(history, fileinput)) {
			cout << fileinput << endl; //print every line
		}
		cout << endl;
		
	//	cout << "Bank balance has been read!\n";
	}
	else {
		cout << "Cannot print bank account balance!\n";
	}
	history.close();
}

