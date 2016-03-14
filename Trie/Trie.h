/*
 * Trie.h
 *
 *  Created on: 2016年3月14日
 *      Author: smallcroco
 */

#ifndef TRIE_TRIE_H_
#define TRIE_TRIE_H_

#include "TrieNode.h"

class Trie {
public:
	Trie();
	~Trie();

	bool insert(const wchar_t* character);

	void setWordEnd();

	ST_trieNode* find(ST_trieNode* node);

private:
	ST_trieNode * root;	// 树的根结点
	ST_trieNode * word_end; // 用于构造词语时指向词语结尾标志
};

#endif /* TRIE_TRIE_H_ */
