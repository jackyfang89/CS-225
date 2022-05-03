/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::ifstream;
using std::string;
using std::vector;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename) {
	//open file for reading
	ifstream infile(filename);
	if (infile.is_open()) {
		string word;
		while (getline(infile, word)) {
			//sort the string by character
			string temp = word;
			std::sort(temp.begin(), temp.end());
			if (dict.find(temp) != dict.end()) {
				dict[temp].push_back(word);
			}
			else {
				dict[temp] = vector<string>(1, word);
			}
		}
	}
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words) {
	/* Your code goes here! */
	for (string word : words) {
		string temp = word;
		std::sort(temp.begin(), temp.end());
		if (dict.find(temp) != dict.end()) {
			dict[temp].push_back(word);
		}
		else {
			dict[temp] = vector<string>(1, word);
		}
	}
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const {
	/* Your code goes here! */
	string temp = word;
	std::sort(temp.begin(), temp.end());
	if (dict.find(temp) != dict.end()) {
		return dict.find(temp)->second;
	}
	return vector<string>();
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const {
	/* Your code goes here! */
	if (dict.size() != 0) {
		vector<vector<string>> ans;
		for (auto e : dict) {
			if (e.second.size() > 1) {
				ans.push_back(e.second);
			}
		}
		return ans;
	}
	return vector<vector<string>>();
}
