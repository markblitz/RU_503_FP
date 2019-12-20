#pragma once
#include <string>
#include "Account.h"
using namespace std;

class BankAccount :
	public Account
{
public:

	BankAccount();	// read balance from txt
	~BankAccount();	// store balance to txt

	void WriteBalanceBack();
	void Deposit(double);	// add money
	void Withdraw(double);	// steal money
	double CheckBanalce() const;	// check what left

	void WriteHistory(string input_event, double input_amount);
	void PrintHistory() const;	// print history

private:

	double balance;
};

