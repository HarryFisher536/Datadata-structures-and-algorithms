// CMP201 AX1.8 The dog adoption problem.
// Author: William Kavanagh
// Partial Framework

#include <map>
#include <vector>
#include <iostream>
#include <thread>
#include <condition_variable>
#include <future>



//// helper function
//// takes a vector of vectors, a person to index the row and then two dogs 1 and 2 to index the column.
//// if the value of dog 1 comes BEFORE dog 2 in the person row of their preference, return true, else, return false.
//// Hint: Use find(iterator, iterator, value).
//bool personPrefersNewDog(std::vector<std::vector<int>> personPref, int person, int dog1, int dog2)
//{
//	for (int i = 0; i < person; i++)
//	{
//		// If m1 comes before m in list of w, then w prefers her
//		// current engagement, don't do anything
//		if (personPref[person][i] == dog2)
//		{
//			return true;
//		}
//
//		// If m comes before m1 in w's list, then free her current
//		// engagement and engage her with m
//		else if (personPref[person][i] == dog1)
//		{
//
//			return false;
//		}
//	}
//}
//
//// helper function
//// takes a map of matches and returns the dog (i.e. the key) of the pair with the passed person as the value.
//int dogMatchedToPerson(int person, std::map<int,int> matches)
//{
//	// Assessed, 1 mark.
//	
//	std::map<int, int> newMap;
//
//	for (int i = 0; i < person; i++)
//	{
//		newMap.insert(std::pair<int, int>(matches[i], person));
//		std::cout << newMap[i];
//	}
//
//	return 0;
//}
//
//std::map<int, int> stableMarriage(std::vector<std::vector<int>> dogPref, std::vector<std::vector<int>> personPref)
//{
//	// Assessed, 3 marks.
//	
//	// Initialise all dogs and people to be free.
//	// create counts of how many proposals each dog has made.
//	
//	// while a dog is free and hasn't proposed to everyone yet.
//	
//		// find the next free dog who still has a person to propose to
//		
//		// find the next person they haven't proposed to.
//		
//		// if the person is free..
//		
//		// Dog proposes to person -- increment proposal.
//		
//		// Either form new match, or compare with current match.
//		
//			// person is not matched, match dog and person
//			
//			// person is already matched to dog2 (use helper function).
//				// person prefers new dog, dog2 is unmatched, dog1 and person make new match.
//				// use helper function.
//				
//	return std::map<int, int>();
//}

int increment(int n) {
	return n + 1;
}

int main()
{

	std::future<int> fut = std::async(increment, 42);
	std::cout << "the result is " << fut.get() << std::endl;

	return 0;



	//// Test 1, from lecture 13A
	//std::vector<std::vector<int>> dogPref = {
	//	{1, 2, 3, 4, 0},
	//	{2, 3, 4, 1, 0},
	//	{2, 3, 1, 0, 4},
	//	{3, 2, 1, 0, 4},
	//	{2, 3, 0, 1, 4}
	//};

	//std::vector<std::vector<int>> peoplePref = {
	//	{1, 3, 2, 4, 0},
	//	{2, 3, 1, 4, 0},
	//	{2, 4, 1, 0, 3},
	//	{1, 2, 3, 0, 4},
	//	{2, 3, 0, 1, 4}
	//};

	//std::map<int, int> matches = stableMarriage(dogPref, peoplePref);

	//std::cout << "Correct result should see matches of D0-P4, D1-P3, D2-P2, D3-P1 and D4-P0.\n";

	//for (auto d : matches)
	//{
	//	std::cout << d.first << " was matched with " << d.second << ", ";
	//}
	//std::cout << "\n";

	//// Test 2
	//dogPref = {
	//	{0, 2, 4, 6, 7, 1, 3, 5},
	//	{1, 3, 2, 0, 4, 5, 6, 7},
	//	{1, 2, 0, 4, 3, 6, 5, 7},
	//	{3, 1, 2, 4, 5, 6, 7, 0},
	//	{2, 0, 3, 1, 5, 7, 6, 4},
	//	{2, 1, 3, 0, 6, 7, 4, 5},
	//	{0, 2, 1, 4, 3, 7, 5, 6},
	//	{2, 3, 0, 1, 5, 7, 6, 4}
	//};

	//peoplePref = {
	//	{6, 7, 3, 1, 2, 4, 5, 0},
	//	{2, 0, 3, 1, 5, 7, 6, 4},
	//	{2, 1, 3, 4, 5, 0, 6, 7},
	//	{6, 0, 4, 2, 7, 1, 3, 5},
	//	{1, 0, 2, 3, 4, 5, 6, 7},
	//	{0, 4, 3, 5, 6, 7, 1, 2},
	//	{0, 3, 7, 5, 2, 1, 4, 6},
	//	{2, 3, 0, 1, 5, 7, 6, 4} 
	//};

	//matches = stableMarriage(dogPref, peoplePref);

	//std::cout << "we are expecting: D0-P4, D1-P2, D2-P1, D3-P5, D4-P3, D5-P6, D6-P0, D7-P7:\n";

	//for (auto d : matches)
	//{
	//	std::cout << d.first << " was matched with " << d.second << ", ";
	//}

	//return 0;
}