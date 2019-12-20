#include "StockLinkList.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

StockLinkList::StockLinkList()
{
	list_head = NULL;
	list_tail = NULL;
	list_size = 0;
	string stock_name;
	int stock_amount;
	ifstream stock_file;
	stock_file.open("AccountInfo/Stock_Info.txt", ios::in);
	if (stock_file.is_open()) {
		while (stock_file >> stock_name >> stock_amount) {
		//	cout << stock_name << stock_amount << endl;
			Node* new_stock = new Node(stock_name, stock_amount);
			AddNode(new_stock);
		}
	}
	else {
		cout << "Stock infomation cannot read!\n";
	}
	stock_file.close();
}

StockLinkList::~StockLinkList()
{
	ofstream stock_file;
	stock_file.open("AccountInfo/Stock_Info.txt", ios::out);
	if (stock_file.is_open()) {
		Node* currentPrt = list_head;
		for (int i = 0; i < list_size; i++) {
			stock_file << left << setw(10) << currentPrt->stock_name
				<< setw(10) << currentPrt->amount << endl;
			currentPrt = currentPrt->next;
		}
	}
	else {
		cout << "Stock infomation cannot write!\n";
	}
	stock_file.close();
}

void StockLinkList::WriteListBack()
{
	ofstream stock_file;
	stock_file.open("AccountInfo/Stock_Info.txt", ios::out);
	if (stock_file.is_open()) {
		Node* currentPrt = list_head;
		for (int i = 0; i < list_size; i++) {
			stock_file << left << setw(10) << currentPrt->stock_name
				<< setw(10) << currentPrt->amount << endl;
			currentPrt = currentPrt->next;
		}
	}
	else {
		cout << "Stock infomation cannot write!\n";
	}
	stock_file.close();
}

int StockLinkList::size() const
{
	return list_size;
}

bool StockLinkList::is_in_list(string& input_stock_name)
{
//	cout << "Checking " << input_stock_name;
	Node* currentPtr = list_head;
	while (currentPtr != NULL) {
//		cout << "current name " << currentPtr->stock_name;
		if (currentPtr->stock_name == input_stock_name) {
			return true;
		}
		currentPtr = currentPtr->next;
	}
	return false;
}

bool StockLinkList::is_enough(string& input_stock_name, int input_stock_amount)
{
	Node* currentPtr = list_head;
	while (currentPtr != NULL) {
		if (currentPtr->stock_name == input_stock_name) {
			if (currentPtr->amount >= input_stock_amount) {
				return true;
			}
		}
		currentPtr = currentPtr->next;
	}
	return false;
}

void StockLinkList::AddNode(Node* newPtr)
{
	if (list_size == 0) {
		list_head = list_tail = newPtr;
	}
	else {
		list_tail->next = newPtr;
		newPtr->prev = list_tail;
	//	newPtr->next = NULL;
		list_tail = newPtr;
	}
	list_size++;
}

void StockLinkList::DeleteNode(Node* thisPtr)
{
	if (list_size == 0) {
		cout << "The list is empty!\n";
	}
	else {
		if (thisPtr == list_head) {
			thisPtr->next->prev = NULL;
			list_head = thisPtr->next;
			delete thisPtr;
			list_size--;
			return;
		}
		if (thisPtr == list_tail) {
			thisPtr->prev->next = NULL;
			list_tail = thisPtr->prev;
			delete thisPtr;
			list_size--;
			return;
		}
		thisPtr->prev->next = thisPtr->next;
		thisPtr->next->prev = thisPtr->prev;
		delete thisPtr;
		list_size--;
	}
}

void StockLinkList::SwapNode(Node* node1, Node* node2)
{
/*	if (node1 == nullptr || node2 == nullptr) {
		cout << "Invalid swap!\n\n";
		return;
	}
	else {
		if (node1->next == node2) {
			node1->prev->next = node2;
			node2->next->prev = node1;
			node1->next = node2->next;
			node1->prev = node2;
			node2->next = node1;
			node2->prev = node1->prev;
			return;
		}
		if (node1->prev == node2) {
			node1->next->prev = node2;
			node2->prev->next = node1;
			node2->prev = node1;
			node2->next = node1->next;
			node1->prev = node2->prev;
			node1->next = node2;
			return;
		}
		string temp_name = "";
		Node* temp = new Node(temp_name, 0);
		temp->next = node1->next;
		temp->prev = node1->prev;
		node1->next->prev = node2;
		node1->prev->next = node2;
		node1->prev = node2->prev;
		node1->next = node2->next;
		node2->next->prev = node1;
		node2->prev->next = node1;
		node2->next = temp->next;
		node2->prev = temp->prev;
		delete(temp);
	}
*/
	string temp_name = node1->stock_name;
	int temp_amount = node1->amount;
	node1->stock_name = node2->stock_name;
	node1->amount = node2->amount;
	node2->stock_name = temp_name;
	node2->amount = temp_amount;
}

void StockLinkList::AddShare(string input_stock_name, int input_amount)
{
//	cout << "adding " << input_stock_name << " with # " << input_amount << endl;
	if (list_size == 0) {
		Node* new_share = new Node(input_stock_name, input_amount);
		AddNode(new_share);
	}
	else {
		Node* currentPtr = list_head;
			while (currentPtr != NULL) {
				if (currentPtr->stock_name == input_stock_name) {
					currentPtr->amount += input_amount;
					break;
				}
				currentPtr = currentPtr->next;
			}
			if (currentPtr == NULL) {
				Node* new_node = new Node(input_stock_name, input_amount);
				AddNode(new_node);
			}
	}
}

void StockLinkList::SubShare(string input_stock_name, int input_amount)
{
	if (list_size == 0) {
		cout << "Empty list already!\n";
	}
	else {
		Node* currentPtr = list_head;
		while (currentPtr != NULL) {
			if (currentPtr->stock_name == input_stock_name) {
				currentPtr->amount -= input_amount;
				if (currentPtr->amount <= 0) {
					DeleteNode(currentPtr);
				}
				break;
			}
			currentPtr = currentPtr->next;
		}
	}
}

