#include <iostream>

#include "lphashtable.h"
#include "schashtable.h"
#include "dhhashtable.h"

#include "textfile.h"
#include <vector>

using namespace std;

vector<string> parseText(string fileName, SCHashTable<string, int>& h);
void printVec(std::vector<string> text);
void printHash(SCHashTable<string, int>& ht);

int main() {
	std::cout << "This main file is for you to write and run your own test cases." << std::endl;
	std::cout << "To run the provided test cases, run `./test`" << std::endl;
	// feel free to insert manual test cases here

    //TESTS FOR SC HASH

    //manual tests for insert
	SCHashTable<string, int> hashTable(32);
    SCHashTable<string, int> hT2(32);
    SCHashTable<string, int> hT3(32);
    vector<string> easy = parseText("tests/textEasy.txt", hashTable);
    vector<string> hard = parseText("tests/textHard.txt", hT2);
    vector<string> text_long = parseText("tests/textLong.txt", hT3);
    printVec(easy);
    printHash(hashTable);
    
    //test find
    cout << hashTable.find("are") << endl;

    //test remove

    hashTable.remove("belong");
    cout << hashTable.find("belong") << endl;
    printHash(hashTable);

	return 0;
}

vector<string> parseText(string fileName, SCHashTable<string, int>& h) {
    TextFile infile(fileName);

    vector<string> text; 

	while (infile.good()) {
		string word = infile.getNextWord();
        if (word == "are") {
            h.insert(word, 69);
        }
        else {
            h.insert(word, 0);
        }
        text.push_back(word);
	}
	h.insert("__SENTINEL__", 0);

    return text;
}

void printVec(std::vector<string> text) {
    for (size_t i = 0; i < text.size(); ++i) {
        cout << text.at(i) << " ";
    }
    cout << endl;
}

void printHash(SCHashTable<string, int>& ht) {
    for(SCHashTable<string,int>::iterator it = ht.begin(); it != ht.end(); ++it )
        cout << it->first << " ";
    cout << endl;
}

