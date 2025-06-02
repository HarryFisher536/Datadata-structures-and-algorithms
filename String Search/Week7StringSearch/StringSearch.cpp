// CMP201.2022 AX1.5 String Search,
// Author: William Kavanagh
// Partial Framework

#include <string>
#include <iostream>
#include <vector>

const int ALPHABET_SIZE = 255;		// characters.

/*
* INPUT: pattern as string, length of pattern as in, int array of size alphabet to be filled.
* values in array should be -1 (if not in the pattern) or the index position of a character in the pattern.
* PERFORMANCE: O(m+n) (this is a hint as to what is provided).
*/
void badCharHeur(std::string pattern, int length, int in_pattern[ALPHABET_SIZE])
{
	// Assessed [1]: Information is provided in lecture 7B
	int i;

	for (i = 0; i < ALPHABET_SIZE; i++)
	{
		in_pattern[i] = -1;
	}


	for (i = 0; i < length; i++)
	{
		in_pattern[(int) pattern[i]] = i;
	}

	
}

/*
* INPUT: A text to search through and a pattern to search for.
* Returns a structure with the indexes of the first character of each occurence of the pattern in the text. Empty if none.
* PERFORMANCE: Boyer-Moore-Horspool should run in O(mn) in the worst-case and should be sublinear in the average case.
*/
std::vector<int> BMH(std::string text, std::string pattern)
{
	// Assessed [2]: Information is provided in lecture 7B
	// complete TODO statements to finish implementation.

	int pattern_len = pattern.size();
	int text_len = text.size();
	int shift_position = 0;		// possible position for first char of pattern


	// TODO: Create results structure
	// TODO: Create bad character heuristic lookup structure
	// TODO: Fill bad character heuristic lookup.


	int BadChar[ALPHABET_SIZE];

	badCharHeur(pattern, pattern_len, BadChar);


	while (shift_position <= text_len - pattern_len)
	{
		// while we are still looking over the text
		int characters_unmatched = pattern_len- 1;	

		while (characters_unmatched >= 0 && pattern[characters_unmatched] == text[shift_position + characters_unmatched])
		{
			// While the pattern matches the text (going backwards)
			// TODO: Reduce the number of characters still to be matched.
			characters_unmatched--;

		}

		// TODO: If the pattern has been matched
		
			// TODO: Add shift position to results
			if (shift_position + pattern_len < text_len)
			{
				// TODO: Uncomment below once the bad character structure exists, you may need to change <badChar> if you use a different name.
				shift_position += pattern_len - BadChar[text[shift_position + pattern_len]];
			}

			else
			{
				shift_position++;
			}
		

		// TODO: Uncomment below when If statement above is implemented.
		//else
		{
			// Pattern not matched, shift along by at least 1.
			// TODO: 'shift_position += max(1, unmatched_characters � badChar[text[shift_position + characters_unmatched]])'
		}
	}
	// TODO: Return the results structure
	return std::vector<int>();	// TODO: Remove when implementation complete.
}

/*
* INPUT: pattern as string, length of pattern as in, pointer to array to be used as LPS structure.
* For each character in the pattern, fill the LPS structure with the length of the longest proper prefix-suffix,
*/
void computeLPS(std::string pat, int M, int* lps)
{
	// UNASSESSED: Information is provided in lecture 7C
	int len = 0;
	lps[0] = 0;
	int i = 1;
	while (i < M)
	{
		if (pat[i] == pat[len])
		{
			len++;
			lps[i] = len;
			i++;
		}
		else
		{
			if (len != 0) len = lps[len - 1];
			else
			{
				lps[i] = 0;
				i++;
			}
		}
	}
}

/*
* INPUT: A text to search through and a pattern to search for.
* Returns a structure with the indexes of the first character of each occurence of the pattern in the text. Empty if none.
* PERFORMANCE: O(m+h) in the worst case and similar in the average case.
*/
std::vector<int> KMP(std::string text, std::string pattern)
{
	// ASSESSED [2]: Information is provided in lecture 7C
	return std::vector<int>();
}


/*
* Main included for testing only. This may not be sufficient for getting full marks, do your own testing also.
* Delete or comment out before submission or [-1].
*/
int main()
{
	// TEST BAD CHARACTER HEURISTIC
	int badChar[ALPHABET_SIZE];
	badCharHeur("string", 6, badChar);
	std::cout << "### TEST 1\nTesting bad character heuristic table. \nExpecting mostly -1 with appropriate values for 'string', e.g.: g = 5 and t = 1:\n";
	for (int i = 65; i < 123; i++)	// Only comparing char values from 65 to 123 so we get alphabetical characters. Expand to 0..255 if you want to see the others.
	{
		std::cout << static_cast<char>(i) << " | " << badChar[i] << ",\t\t";
		if (i % 8 == 0) std::cout << "\n";		// new line every so often
	}
	
	// TEST BMH
	std::string text = "there was once a fox called foxxy mcfox in a little fox house for foxes";
	std::string pattern = "fox";
	std::vector<int> r = BMH(text, pattern);
	std::cout << "\n\n### TEST 2\nTesting BMH algorithm with the following:\ntext: " << text << "\npattern: " << pattern << "\nexpecting: 17, 28, 36, 52 and 66\n";
	for (int res : r)
	{
		std::cout << "> Pattern found to occur at position: " << res << "\n";
	}

	// TEST LPS TABLE
	std::cout << "\n\n### TEST 3\nTesting LPS table with the pattern 'AAABAAA'\nexpecting: [0, 1, 2, 0, 1, 2, 3]\n[";
	std::string lpsTest = "AAABAAA";
	int* lps = new int[lpsTest.length()];
	computeLPS(lpsTest, lpsTest.length(), lps);
	for (int i = 0; i < lpsTest.size()-1; i++)
	{
		std::cout << lps[i] << ",";
	}
	std::cout << lps[lpsTest.size()-1] << "]\n";

	// TEST KMP
	text = "AAABBAAABAAABAAA";
	pattern = "AAABAAA";
	std::cout << "\n\n### TEST 4\nTesting KMP with:\npattern: " << pattern << "\ntext: " << text << "\nexpecting 5 and 9\n";
		
	std::vector<int> r2 = KMP(text, pattern);
	for (int x : r2)
	{
		std::cout << "> Pattern found to occur at position: " << x << "\n";
	}
	
	return 0;
}