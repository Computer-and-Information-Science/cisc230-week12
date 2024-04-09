#include "knapsack.h"
#include <iostream>
using namespace std;

int main () {

	list<Item> items;
	items.push_back(Item(12, 4));
	items.push_back(Item(2, 2));
	items.push_back(Item(1, 2));
	items.push_back(Item(1, 1));
	items.push_back(Item(4, 10));

	cout << "Candidate items: ";
	for (auto item: items)
		cout << item;
	cout << endl;

	Knapsack knap(15);

	cout << "Knapsack items: ";
	cout << knap << endl;
}
