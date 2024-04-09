#include <algorithm>
#include <iostream>
#include <list>

// An item that may be include in a knapsack
class Item {
protected:
	int wgt, val;
public:
	// Item requires weight and value for initialization
	Item (int w, int v) : wgt(w), val(v) { }
	// Accessor function
	int value () const { return val; }
	int weight () const { return wgt; }
	// For removal of an item from a knapsack
	bool operator== (const Item& itm) const
		{ return wgt == itm.wgt && val == itm.val; }
};

std::ostream& operator<< (std::ostream& os, const Item& itm) {
	os << "[w:" << itm.weight() << ";v:" << itm.value() << "]";
	return os;
}

// A knapsack for holding items
class Knapsack {
protected:
	int cap, val, wgt;
	std::list<Item> itms;
public:
	// Knapsack requires capacity for initialization
	Knapsack (int c);
	// Accessor functions
	int capacity () const { return cap; }
	int value () const { return val; }
	int weight () const { return wgt; }
	const std::list<Item>& items () const { return itms; }
	// Add an item to the knapsack, throws exception if item exceeds capacity
	void add (const Item& itm);
	// Remove an item from the knapsack, throws exception if item not found
	void remove (const Item& itm);
};

Knapsack::Knapsack (int c) {
	// Initialize capacity, value, and weight
	cap = c;
	val = wgt = 0;
}

void Knapsack::add (const Item& itm) {
	// Check if adding item will exceed capacity
	if (wgt + itm.weight() > cap)
		throw 1;
	// Add item, update value and weight
	itms.push_back(itm);
	val += itm.value();
	wgt += itm.weight();
}

void Knapsack::remove (const Item& itm) {
	// Find item to be removed
	std::list<Item>::iterator i = std::find(itms.begin(), itms.end(), itm);
	// If not found throw an exception
	if (i == itms.end())
		throw 2;
	// Remove the item, and update value and weight
	itms.erase(i);
	val -= itm.value();
	wgt -= itm.weight();
}

std::ostream& operator<< (std::ostream& os, const Knapsack& k) {
	os << "[c:" << k.capacity() << ";w:" << k.weight() << ";v:" <<
		k.value() << ";i:[";
	int count = 0;
	for (std::list<Item>::const_iterator i = k.items().begin();
			i != k.items().end(); i++)
		os << (count++ ? ";" : "") << *i;
	os << "]]";
	return os;
}
