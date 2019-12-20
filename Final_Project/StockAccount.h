#pragma once
#include <string>
#include "Account.h"
#include "StockLinkList.h"
using namespace std;

class StockAccount :	
	public Account	
{
	friend class StockLinkList;
public:
	StockAccount();
	double CheckSharePrice(string input_name);
	void WriteHistory(string input_event, string input_stock_name,
		double input_amount, double input_stock_unit_price);
	void PrintHistory() const;	// print history
private:
	string aim_file;
};

