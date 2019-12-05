#include <iostream>
#include <fstream>
#include <iomanip>
#include "BankAccount.h"

using namespace std;

int main() {

	BankAccount user;
	cout << fixed << setprecision(4) << user.Check_Banalce() << endl;
	user.Deposit(123.211);
	cout << fixed << setprecision(4) << user.Check_Banalce() << endl;
	user.Withdraw(1302.15);
	cout << fixed << setprecision(4) << user.Check_Banalce() << endl;




	return 0;
}