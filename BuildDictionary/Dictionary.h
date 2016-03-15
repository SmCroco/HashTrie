/*
 * Dictionary.h
 *
 *  Created on: 2016年3月14日
 *      Author: smallcroco
 */

#ifndef BUILDDICTIONARY_DICTIONARY_H_
#define BUILDDICTIONARY_DICTIONARY_H_

#include "Trie.h"
#include <string>
#include <fstream>

using namespace std;

class Dictionary {
public:
	Dictionary();
	~Dictionary();

	void InitDictionary(string path);
	void InitDictionary();

	void ReadFile(string path);
	void ReadFile(const char* content, long length);

public:
	void continueMatchFile(char* word, int i);
	void continueMatchContent(const char* content, long length, char* word, int i);

public:
	Trie* trie;
	ifstream file;
};

#endif /* BUILDDICTIONARY_DICTIONARY_H_ */
