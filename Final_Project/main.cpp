#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "User.h"
#include "StockAccount.h"
#include "StockLinkList.h"
#include "Node.h"

using namespace std;

void WelcomeMenu();
void BankMenu();
void StockMenu();

int main() {
	User Bi;
	while (true) {
		WelcomeMenu();
		int user_choise_1;
		cin >> user_choise_1;
		cout << endl;

		switch (user_choise_1) {
		case 1:
		{
			// access stock account
			while (true) {

				StockMenu();
				int user_choise_2;
				cin >> user_choise_2;
				cout << endl;

				switch (user_choise_2) {
				case 1: 
				{
					Bi.DisplayStockPrice();
					continue;
				}

				case 2: 
				{
					Bi.DisplayCurrentProtfolio();
					continue;
				}

				case 3: 
				{
					Bi.BuyShare();
					continue;
				}

				case 4: 
				{
					Bi.SellShare();
					continue;
				}				
				
				case 5: 
				{
					Bi.Plot();
					continue;
				}				
				
				case 6: 
				{
					Bi.ViewStockHistory();
					continue;
				}

				case 7:
					break;

				default:
					cout << "invalid input!\n";
					continue;

				}
				break;
			}
			continue;
		}

		case 2:
		{
			// access bank account
			while (true) {

				BankMenu();
				int user_choise_2;
				cin >> user_choise_2;
				cout << endl;

				switch (user_choise_2) {
				case 1:
				{
					Bi.ViewBankBalance();
					continue;
				}

				case 2:
				{
					Bi.Deposit();
					continue;
				}

				case 3:
				{
					Bi.Withdraw();
					continue;
				}

				case 4:
				{
					Bi.PrintBankHistory();
					continue;
				}

				case 5:
					break;

				default:
					cout << "Invalid input!\n\n";
					continue;
				}
				break;
			}
			continue;
		}

		case 3:
			break;

		default:
			cout << "invalid input!\n\n";
			continue;
		}
		break;
	}
	return 0;
}

void WelcomeMenu()
{
	cout << "Welcome to the Account Management System.\n"
		<< "Please select an account to access:\n"
		<< "1. Stock Portfolio Account\n"
		<< "2. Bank Account\n"
		<< "3. Exit\n"
		<< "Your choice is: ";
}

void BankMenu()
{
	cout << "Please select an option:\n"
		<< "1. View account balance\n"
		<< "2. Deposit money\n"
		<< "3. Withdraw money\n"
		<< "4. Print out history\n"
		<< "5. Return to previous menu\n"
		<< "Your choice is: ";
}

void StockMenu()
{
	cout << "Please select an option:\n"
		<< "1. Display the price for a stock symbol\n"
		<< "2. Display the current portfolio\n"
		<< "3. Buy shares\n"
		<< "4. Sell shares\n"
		<< "5. View a graph for the portfolio value\n"
		<< "6. View transaction history\n"
		<< "7. Return to previous menu\n"
		<< "Your choice is: ";
}
