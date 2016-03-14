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

using namespace std;

class Dictionary {
public:
	Dictionary();
	~Dictionary();

	void InitDictionary(string path);
	void InitDictionary();

private:
	Trie* trie;
};

#endif /* BUILDDICTIONARY_DICTIONARY_H_ */
