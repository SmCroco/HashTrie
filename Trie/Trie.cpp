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
	this->root->value = ' ';
	this->root->parent = (ST_trieNode*)0;

	this->word_end = root;

	count = 0;
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
bool Trie::insert(char character) {

	long key = (long)character;
	hash_map<long, ST_trieNode*>::iterator it;
	it = word_end->hash.find(key);
	if (it == word_end->hash.end()) {

		ST_trieNode * node = new ST_trieNode();
		node->key = key;
		node->value = character;
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

/*
 * @Function Name: find
 * @Parameter [in] character: 要查找的char
 * @Description: 通过char的编码去trie中查找
 * ＠Return Value:
 * 		0：返回0表示查找失败
 * 		1：返回1表示关键词结尾
 * 		2：表示查找到了，但还没有到词结尾
 */
int Trie::find(char character) {

	ST_trieNode* value = word_end->hash[character];
	if (value == NULL) {
		word_end = root;
		return 0;
	} else {
		if (value->isEnd) {
			value->count++;
			count += 1;

			word_end = value;

			return 1;
		} else {
			word_end = value;

			return 2;
		}
	}
}

void Trie::setWordEnd() {
	word_end->isEnd = true;

	word_end = root;
}

long Trie::getCount() {
	return count;
}
