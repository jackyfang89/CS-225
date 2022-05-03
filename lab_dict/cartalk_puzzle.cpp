/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
																		 const string& word_list_fname) {
	vector<std::tuple<std::string, std::string, std::string>> ret;

	/* Your code goes here! */

	//open file for reading and read line by line
	ifstream wordsFile(word_list_fname);
	string line;
	if (wordsFile.is_open()) {
		while (getline(wordsFile, line)) {
			//check if word itself, word without first char, and
			//word with second char removed are all homophones
			if (line.size() < 2) {
				continue;
			}

			string a = line.substr(1);
			string b = line.substr(0, 1) + line.substr(2);

			if (d.homophones(line, a) && d.homophones(line, b)) {
				ret.push_back(std::make_tuple(line, a, b));
			}
		}
	}

	return ret;
}
