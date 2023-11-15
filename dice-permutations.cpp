// Print all permutations of N dice using a backtracking technique.
#include <iostream>
#include <list>
using namespace std;

void print_permutations (const int n_dice);
void print_permutations (const int n_dice, list<int>& current_permutation);

int main () {
	int n; // Number of dice
	cout << "Enter number of dice: ";
	cin >> n;
	print_permutations(n);
}

void print_permutations (const int n_dice) {
	list<int> current_permutation;
	print_permutations(n_dice, current_permutation);
	cout << endl;
}

void print_permutations (const int n_dice, list<int>& current_permutation) {
	if (current_permutation.size() == n_dice) {
		// Print the permutation
		cout << '(';
		bool first = true;
		for (int n : current_permutation) {
			if (!first)
				cout << '-';
			cout << n;
			first = false;
		}
		cout << ')';
		return;
	}

	for (int i = 1; i <= 6; i++) {
		current_permutation.push_back(i);
		print_permutations(n_dice, current_permutation);
		current_permutation.pop_back();
	}
}