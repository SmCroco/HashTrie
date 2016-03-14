/*
 * Dictionary.cpp
 *
 *  Created on: 2016年3月14日
 *      Author: smallcroco
 */

#include "Dictionary.h"
#include <iostream>
#include <fstream>

using namespace std;

Dictionary::Dictionary() {
	// TODO Auto-generated constructor stub

	trie = new Trie();
}

Dictionary::~Dictionary() {
	// TODO Auto-generated destructor stub

	if (trie != NULL) {
		delete trie;
	}
}

void Dictionary::InitDictionary(string path) {

		wifstream infile(path.c_str());

		wstring word;
		while (getline(infile, word)) {
			const wchar_t* p = word.c_str();
			while (p != NULL) {
				this->trie->insert(p);
			}

			this->trie->setWordEnd();
		}
}
