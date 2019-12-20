#include <iostream>
#include <iomanip>
#include <fstream>
#include <time.h>
#include <engine.h>


#include "User.h"
#pragma comment( lib, "libmx.lib" )   
#pragma comment( lib, "libmex.lib" )   
#pragma comment( lib, "libeng.lib" )
#include <yvals.h>
#if (_MSC_VER >= 1600)
#define __STDC_UTF_16__
#endif
#include "mex.h" 
using namespace std;

User::~User()
{
//	WriteTotalValue();
}

void User::DisplayStockPrice()
{
	cout << "Please enter the stock symbol: ";
	string stock_sym;
	cin >> stock_sym;
	double stock_price;
	stock_price = stock_info.CheckSharePrice(stock_sym);
	if (stock_price == -1) {
		cout << "Symbol not found!\n\n";
	}
	else {
		cout << "Company symbol and price per share are: \n"
			<< left << setw(10) << stock_sym << "$" << setw(10) << stock_price << endl << endl;
	}
	
}

void User::DisplayCurrentProtfolio()
{
	cout << "Cash balance: $" << bank_info.CheckBanalce() << endl;
	double total_stock_value = 0;
	if (stock_list.size() == 0) {
		cout << "\nThe stock lisk is empty!\n\n";
	}
	else {
		Node* currentPtr = stock_list.list_head;		
		cout << left << setw(20) << "\nCompanySymbol" << setw(10) << "Number"
			<< setw(20) << "PricePerShare" << setw(20) << "TotalValue" << endl;
		while (currentPtr != NULL) {
			cout << setw(19) << currentPtr->stock_name << setw(10) << currentPtr->amount
				<< "$" << setw(19) << stock_info.CheckSharePrice(currentPtr->stock_name) 
				<< "$" << setw(20) << currentPtr->amount * stock_info.CheckSharePrice(currentPtr->stock_name) << endl;
			total_stock_value += currentPtr->amount * stock_info.CheckSharePrice(currentPtr->stock_name);
			currentPtr = currentPtr->next;
		}
		cout << "The stock list ends here.\n";
		
	}
	cout << "Total portfolio value: $" << total_stock_value + bank_info.CheckBanalce() << endl << endl;
}

void User::BuyShare()
{
	// ask inputs
	cout << "Please enter the stock symbol you want to buy: ";
	string input_stock_name;
	cin >> input_stock_name;
	double stock_price;
	stock_price = stock_info.CheckSharePrice(input_stock_name);
	if (stock_price == -1) {	// if the stock name not found, return and ask again
		cout << "Symbol not found!\n"
			<< "Transaction cancelled!\n\n";
		return;
	}
	cout << "Please enter the amount of shares you want to buy: ";
	int input_stock_amount;
	cin >> input_stock_amount;
	cout << "Please enter the maximun price you are willing to pay: $";
	double input_max_price;
	cin >> input_max_price;
	cout << "You want to buy " << input_stock_amount << " " << input_stock_name
		<< " shares with max willing price $" << input_max_price << "." << endl;

	// check qualification
	if (stock_price * input_stock_amount > bank_info.CheckBanalce()) {
		cout << "Your bank banalce $" << bank_info.CheckBanalce() 
			<< " is not enough for this transaction!\n"
			<< "Transaction cancelled!\n\n";
		return;
	}
	if (stock_price > input_max_price) {
		cout << "There is no available price for your willing price!\n"
			<< "Transaction cancelled!\n\n";
		return;
	}

	// transaction does
	bank_info.Withdraw(input_stock_amount * stock_price);
	bank_info.WriteHistory("Buy Share", input_stock_amount * stock_price);
	stock_list.AddShare(input_stock_name, input_stock_amount);
	stock_info.WriteHistory("Buy", input_stock_name, input_stock_amount, stock_price);
	cout << "Your likst may need sorted, please choose:\n1. Selection sort\n2. Bubble sort\nyour choice: ";
	int user_input;
	cin >> user_input;
	switch (user_input) {
	case 1:
		SelectionSort();
		break;
	case 2:
		BubbleSort();
		break;
	default:
		cout << "Invalid input, Selection sort is used!\n";
		SelectionSort();
		break;
	}
	stock_list.WriteListBack();
	WriteTotalValue();

	cout << "Transaction succeed!\nYou bought " << input_stock_amount << " " << input_stock_name
		<< " shares with unit price $" << stock_price
		<< ", total spend is $" << stock_price * input_stock_amount << ".\n\n";
}

void User::SellShare()
{
	// ask inputs and chekc qualification
	cout << "Please enter the stock symbol you want to sell: ";
	string input_stock_name;
	cin >> input_stock_name;
	if (!stock_list.is_in_list(input_stock_name)) {
		cout << "You may not have certain share!\nTranscation cancelled!\n\n";
		return;
	}
	cout << "Please enter the amount you want to sell: ";
	int input_sell_amount;
	cin >> input_sell_amount;
	if (!stock_list.is_enough(input_stock_name, input_sell_amount)) {
		cout << "You mau not have enough shares to sell!\nTranscation cancelled!\n\n";
		return;
	}
	cout << "Please enter the minimum price you want to sell this share; ";
	double input_min_price;
	cin >> input_min_price;
	double stock_price = stock_info.CheckSharePrice(input_stock_name);
	if (input_min_price > stock_price) {
		cout << "There is no available price!\nTranscation cancelled!\n\n";
		return;
	}

	// sell goes
	stock_list.SubShare(input_stock_name, input_sell_amount);
	stock_info.WriteHistory("Sell", input_stock_name, input_sell_amount, stock_price);
	bank_info.Deposit(input_sell_amount * stock_price);
	bank_info.WriteHistory("Sell Share", input_sell_amount * stock_price);
	cout << "Your likst may need sorted, please choose:\n1. Selection sort\n2. Bubble sort\nyour choice: ";
	int user_input;
	cin >> user_input;
	switch (user_input) {
	case 1:
		SelectionSort();
		break;
	case 2:
		BubbleSort();
		break;
	default:
		cout << "Invalid input, Selection sort is used!\n";
		SelectionSort();
		break;
	}
	stock_list.WriteListBack();
	WriteTotalValue();

	cout << "Transaction succeed!\nYou sold " << input_sell_amount << " " << input_stock_name
		<< " shares with unit price $" << stock_price
		<< ", total gain is $" << stock_price * input_sell_amount << ".\n\n";
}

void User::Plot()
{
	Engine* m_pEngine;
	m_pEngine = engOpen(NULL);
	if (m_pEngine == NULL)
	{
		cout << "Error: Not Found"
			<< endl;
		exit(1);
	}
	engEvalString(m_pEngine, "A=readtable('C:/Users/000/source/repos/markblitz/RU_503_FP/Final_Project/AccountInfo/Stock_Value.txt');");
	engEvalString(m_pEngine, "plot(A.Var1, A.Var2)");
	system("pause");
	engEvalString(m_pEngine, "close;"); // Closes the matlab engine
	return;

}

void User::ViewStockHistory()
{
	stock_info.PrintHistory();
}

void User::ViewBankBalance()
{
	double bankbalance;
	bankbalance = bank_info.CheckBanalce();
	cout << "You have bank balance: $" << fixed << setprecision(4) << bankbalance << "!\n\n";
}

void User::Deposit()
{
	cout << "Please enter the amount of money you want to deposit: $";
	double input_money_amount;
	cin >> input_money_amount;
	bank_info.Deposit(input_money_amount);
	bank_info.WriteHistory("Deposit", input_money_amount);
	cout << "Transaction succeed!\n\n";
}

void User::Withdraw()
{
	cout << "Please enter the amount of money you want to withdraw: $";
	double input_money_amount;
	cin >> input_money_amount;
	bank_info.Withdraw(input_money_amount);
	bank_info.WriteHistory("Withdraw", input_money_amount);
	cout << "Transaction succeed!\n\n";
}

void User::PrintBankHistory()
{
	bank_info.PrintHistory();
	cout << "stock history:\n";
	stock_info.PrintHistory();
}

void User::SelectionSort()
{
	Node* sort_start = stock_list.list_head;
	Node* itptr;
	Node* max;
	while (sort_start != stock_list.list_tail) {
		itptr = sort_start;
		max = sort_start;
		while (itptr != NULL) {
			if ((stock_info.CheckSharePrice(itptr->stock_name) * itptr->amount) >
				(stock_info.CheckSharePrice(max->stock_name) * max->amount)) {
				max = itptr;
			}
			itptr = itptr->next;
		}
		stock_list.SwapNode(max, sort_start);
		sort_start = sort_start->next;
	}
}

void User::BubbleSort()
{
	int swapped = 1;
	while (swapped = 1) {	
	//	cout << swapped;
		Node* sort1 = stock_list.list_head;
		Node* sort2 = stock_list.list_head->next;
		for (int i = 0; i < stock_list.list_size - 1; i++) {
			swapped = 0;
		//	cout << swapped;
			if ((sort1->amount * stock_info.CheckSharePrice(sort1->stock_name)) <
				(sort2->amount * stock_info.CheckSharePrice(sort2->stock_name))) {
				stock_list.SwapNode(sort1, sort2);
				swapped = 1;
			//	cout << swapped;
			}
			sort1 = sort1->next;
			sort2 = sort2->next;
		}
	}
}

void User::WriteTotalValue()
{
	time_t t;
	time(&t);
	struct tm buf;
	localtime_s(&buf, &t);
	ofstream stock_file;
	stock_file.open("AccountInfo/Stock_Value.txt", ios::app);
	if (stock_file.is_open()) {
		Node* currentPrt = stock_list.list_head;
		double total_value = 0;
		for (int i = 0; i < stock_list.list_size; i++) {
			total_value += currentPrt->amount * stock_info.CheckSharePrice(currentPrt->stock_name);
			currentPrt = currentPrt->next;
		}
		total_value += bank_info.CheckBanalce();
		stock_file << buf.tm_year + 1900 << "/" << buf.tm_mon + 1 << "/" << buf.tm_mday << " "
			<< buf.tm_hour << ":" << buf.tm_min << ":" << left << setw(10) << buf.tm_sec << ",";
		stock_file << total_value << endl;
	}
	else {

		cout << "Stock infomation cannot write!\n";
	}
	stock_file.close();
}
