#include <fstream>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <time.h>
#include "StockAccount.h"
#include <iomanip>
using namespace std;

StockAccount::StockAccount()
{
	srand((unsigned)time(NULL));
	int aim =  rand() % 2 + 1;
	aim_file = "StockInfo/Result_";
	aim_file.append(to_string(aim));
	aim_file.append(".txt");
//	fstream StockInfo;
//	StockInfo.open(aim_file, ios::in);
//	cout << aim_file;
}

double StockAccount::CheckSharePrice(string input_name)
{
	string stock_name;
	double stock_unit_price;
	string date;
	double output_price;
	ifstream stock_info;
	stock_info.open(aim_file, ios::in);
	if (stock_info.is_open()) {
		while (stock_info >> stock_name >> stock_unit_price >> date) {
			if (stock_name == input_name) {
				output_price = stock_unit_price;
				return output_price;
			}
		}		
		return -1;
	}
	else {
		cout << "Stock information cannot read!\n";
	}
	return -2;
}

void StockAccount::WriteHistory(string input_event, string input_stock_name, double input_amount, double input_stock_unit_price)
{
	time_t t;
	time(&t);
	struct tm buf;
	localtime_s(&buf, &t);
	//cout << "local time: " << buf.tm_year + 1900 << "/" << buf.tm_mon + 1 << "/" << buf.tm_mday << " " 
	//	<< buf.tm_hour  << ":" << buf.tm_min << ":" << buf.tm_sec << endl;

	ofstream history;
	history.open("AccountInfo/Stock_History.txt", ios::app);
	if (history.is_open()) {
		history << left << setw(10) << input_event;
		history << left << setw(15) << input_stock_name;
		history << left << setw(10) << input_amount;
		history << left << setw(15) << fixed << setprecision(4) << input_stock_unit_price;
		history << left << setw(15) << fixed << setprecision(4) << input_amount * input_stock_unit_price;
		history << buf.tm_year + 1900 << "/" << buf.tm_mon + 1 << "/" << buf.tm_mday << " "
			<< buf.tm_hour << ":" << buf.tm_min << ":" << left << setw(10) << buf.tm_sec;
		history << endl;
//		cout << "Bank record has been writen!\n";
	}
	else {
		cout << "Cannot write bank record balance!\n";
	}
	history.close();
}

void StockAccount::PrintHistory() const
{
	ifstream history;
	string fileinput;
	history.open("AccountInfo/Stock_history.txt", ios::in);
	if (history.is_open()) {
		cout << setw(10) << left << "EVENT"
			<< setw(15) << left << "CompSymbol"
			<< setw(10) << left << "Number"
			<< setw(15) << left << "PricePerShare"
			<< setw(15) << left << "TotalValue"
			<< setw(26) << left << "TIME & DATE" << endl;
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
