/*
 * Trie.cpp
 *
 *  Created on: 2016年3月14日
 *      Author: smallcroco
 */

#include "Trie.h"

using namespace __gnu_cxx;

Trie::Trie() {
	// TODO Auto-generated constructor stub

	this->root = new ST_trieNode();
	this->root->count = 0;
	this->root->faile = (ST_trieNode*)0;
	this->root->isEnd = false;
	this->root->key = 0;
	this->root->value = L' ';
	this->root->parent = (ST_trieNode*)0;

	this->word_end = root;
}

Trie::~Trie() {
	// TODO Auto-generated destructor stub

}

/*
 * @Function Name: insert
 * @Parameter [in] ST_trieNode*: trie树的一个结点
 * @Parameter [in] bool: 标志一个关键词是否结束
 * @Description: 将关键词的中一个字插入trie树中的一个结点, 并标记关键词是否插入完成
 * @Return Value: 新开辟的节点则返回true，原来已经有的节点则返回false
 */
bool Trie::insert(const wchar_t* character) {

	long key = (long)character;
	hash_map<long, ST_trieNode*>::iterator it;
	it = word_end->hash.find(key);
	if (it == word_end->hash.end()) {

		ST_trieNode * node = new ST_trieNode();
		node->key = key;
		node->value = *character;
		node->isEnd = false;
		node->parent = word_end;
		node->faile = NULL;
		word_end->hash.insert(hash_map<long, ST_trieNode*>::value_type(node->key, node));
		word_end = node;

		return true;
	} else {
		word_end = it->second;

		return false;
	}
}

ST_trieNode* Trie::find(ST_trieNode* node) {

	return NULL;
}

void Trie::setWordEnd() {
	word_end->isEnd = true;

	word_end = root;
}
