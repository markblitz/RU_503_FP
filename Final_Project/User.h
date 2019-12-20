#pragma once
#include "StockLinkList.h"
#include "StockAccount.h"
#include "BankAccount.h"
class User
{
	friend class StockLinkList;
public:

	~User();

	void DisplayStockPrice();
	void DisplayCurrentProtfolio();
	void BuyShare();
	void SellShare();
	void Plot();
	void ViewStockHistory();

	void ViewBankBalance();
	void Deposit();
	void Withdraw();
	void PrintBankHistory();

	void SelectionSort();
	void BubbleSort();
	void WriteTotalValue();

private:
	StockLinkList stock_list;
	StockAccount stock_info;
	BankAccount bank_info;
};

