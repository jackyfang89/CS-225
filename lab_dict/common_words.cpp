/**
 * @file common_words.cpp
 * Implementation of the CommonWords class.
 *
 * @author Zach Widder
 * @date Fall 2014
 */

#include "common_words.h"

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

using std::cout;
using std::endl;
using std::feof;
using std::ifstream;
using std::string;
using std::vector;

string remove_punct(const string& str) {
	string ret;
	std::remove_copy_if(str.begin(), str.end(), std::back_inserter(ret),
						[](int c) { return std::ispunct(c); });
	return ret;
}

CommonWords::CommonWords(const vector<string>& filenames) {
	// initialize all member variables
	init_file_word_maps(filenames);
	init_common(filenames);
}

void CommonWords::init_file_word_maps(const vector<string>& filenames) {
	// make the length of file_word_maps the same as the length of filenames
	file_word_maps.resize(filenames.size());

	// go through all files
	for (size_t i = 0; i < filenames.size(); ++i) {
		// get the corresponding vector of words that represents the current
		// file
		vector<string> words = file_to_vector(filenames[i]);
		/* Your code goes here! */
		map<string, unsigned int> curr;
		for (string& word : words) {
			if (curr.find(word) != curr.end()) {
				curr[word]++;
			}
			else {
				curr[word] = 1;
			}
		}

		file_word_maps[i] = curr;
	}
}

void CommonWords::init_common(const vector<string>& filenames) {
	/* Your code goes here! */

	for (auto& map : file_word_maps) {
		for (auto& pair : map) {
			if (common.find(pair.first) != common.end()) {
				common[pair.first]++;
			}
			else {
				common[pair.first] = 1;
			}
		}
	}
}

/**
 * @param n The number of times to word has to appear.
 * @return A vector of strings. The vector contains all words that appear
 * in each file >= n times.
 */
vector<string> CommonWords::get_common_words(unsigned int n) const {
	vector<string> out;
	/* Your code goes here! */

	//get words that appear in every file
	for (auto& pair : common) {
		if (pair.second == file_word_maps.size()) {
			out.push_back(pair.first);
		}
	}
	//remove words that appear < n times
	vector<string>::iterator it = out.begin();
	for (; it != out.end();) {
		bool found = false;
		for (auto& map : file_word_maps) {
			if (map.find(*it)->second < n) {
				found = true;
				it = out.erase(it);
				break;
			}
		}
		if (!found) {
			++it;
		}
	}
	return out;
}

/**
 * Takes a filename and transforms it to a vector of all words in that file.
 * @param filename The name of the file that will fill the vector
 */
vector<string> CommonWords::file_to_vector(const string& filename) const {
	ifstream words(filename);
	vector<string> out;

	if (words.is_open()) {
		std::istream_iterator<string> word_iter(words);
		while (!words.eof()) {
			out.push_back(remove_punct(*word_iter));
			++word_iter;
		}
	}
	return out;
}
