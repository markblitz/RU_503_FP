#pragma once
#include "Account.h"
class BankAccount :
	public Account
{
public:

	BankAccount();	// read balance from txt
	~BankAccount();	// store balance to txt

	void Deposit(double);	// add money
	void Withdraw(double);	// steal money
	double Check_Banalce() const;	// check what left

	void Write_History(int input_type, double input_amount);
	void Print_History() const;	// print history

private:

	double balance;
};

