#pragma once
#include <iostream>
using namespace std;
#include "Node.h"
#include "StockAccount.h"

class StockLinkList
{
	friend class User;
	friend class StockAccount;
public:
	StockLinkList();
	~StockLinkList();
	void WriteListBack();
	int size() const;
	bool is_in_list(string& );
	bool is_enough(string&, int);
	void AddNode(Node* newPtr);
	void DeleteNode(Node* thisPtr);
	void SwapNode(Node* node1, Node* node2);
	void AddShare(string input_stock_name, int input_amount);
	void SubShare(string input_stock_name, int input_amount);

private:
	Node* list_head;
	Node* list_tail;
	int list_size;
};

