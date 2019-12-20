#pragma once
#include <iostream>
using namespace std;

class Node {
	friend class StockLinkList;
	friend class User;
public:
	Node(string& input_name, int input_amount) :
		stock_name(input_name), amount(input_amount) {
		this->next = NULL;
		this->prev = NULL;
	}
private:
	string stock_name;
	int amount;
	Node* next;
	Node* prev;
};
