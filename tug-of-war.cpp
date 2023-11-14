// Tug Of War - Given a list of player weights, determine the best balance
// of two tug of war teams such that the differen in number of players is
// no more than one, and the combined weights of both teams is a close as
// possible.
#include <algorithm>
#include <climits>
#include <cmath>
#include <list>
#include <iostream>
using namespace std;

// For printing a list of int's.
void print (int n) { cout << ' ' << n; }

// A function object for calculating the sum of a list of int's.
class Sum {
private:
	int _sum;
public:
	Sum () { _sum = 0; }
	void operator() (int n) { _sum += n; }
	int sum () const { return _sum; }
};

// A class for solving the problem.
class TugOfWar {
private:
	class Solution {
	public:
		list<int> a; // List of weights for team A
		list<int> b; // List of weights for team B
		size_t max_list_size; // The max size of a team

		// Find the difference in weights of the two teams.
		int diff () const {
			// Return a big number if no teams have any members (starting
			// condition)
			if (!a.size() && !b.size())
				return INT_MAX;
			return abs(
				for_each(a.begin(), a.end(), Sum()).sum() -
				for_each(b.begin(), b.end(), Sum()).sum());
		}
		// Determine if the current solution is feasible; neither team may
		// exceed the max number of participants.
		bool feasible () const
			{ return a.size() <= max_list_size && b.size() <= max_list_size; }
	};
	list<int> players; // The participants in the contest.
	Solution best; // The best solution found so far.
	Solution current; // The current solution in search of the best.
	void find_solution (list<int>::const_iterator i); // Finds the solution.
public:
	TugOfWar (const list<int> player_weights);
};

int main () {
	list<int> l1 = { 200, 150, 175, 202, 110, 132, 180 };
	list<int> l2 = { 135, 170, 155, 165, 190, 210, 140, 115, 165, 160 };
	(TugOfWar(l1));
}

// The constructor set up, finds, and prints the solution.
TugOfWar::TugOfWar (const list<int> player_weights) {
	players = player_weights; // Weights of participants.

	// Print the list of players and sum of all weights.
	cout << "Players:";
	for_each(players.begin(), players.end(), print);
	cout << " (" << for_each(players.begin(), players.end(), Sum()).sum() <<
		")" << endl << endl;

	// Determine max number of participants on a team.
	best.max_list_size = current.max_list_size = (players.size() + 1) / 2;

	// Find a solution.
	find_solution(players.begin());

	// Print team A
	cout << "Team A:";
	for_each(best.a.begin(), best.a.end(), print);
	cout << " (" << for_each(best.a.begin(), best.a.end(), Sum()).sum() <<
		")" << endl;

	// Print team B
	cout << "Team B:";
	for_each(best.b.begin(), best.b.end(), print);
	cout << " (" << for_each(best.b.begin(), best.b.end(), Sum()).sum() <<
		")" << endl;
}

// Find a solution. Parameter is an iterator to the current participant
// (weight of participant) in the given list of weights.
void TugOfWar::find_solution (list<int>::const_iterator i) {

	// If the end iterator, we have a feasible solution. Check to see if it
	// is better than the best found so far. If better, we have a new best
	// solution.
	if (i == players.end()) {
		if (current.diff() < best.diff())
			best = current;
		return;
	}

	// Add participant to team A
	current.a.push_back(*i);
	i++;
	// If solution is feasible, expand the solution to next participant.
	if (current.feasible())
		find_solution(i);
	// Add participant to team B and remove from A
	current.b.push_back(current.a.back());
	current.a.pop_back();
	// If solution is feasible, expand the solution to next participant.
	if (current.feasible())
		find_solution(i);
	// Remove participant from team B
	current.b.pop_back();
}