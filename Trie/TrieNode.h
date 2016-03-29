/*
 * TrieNode.h
 *
 *  Created on: 2016年3月11日
 *      Author: smallcroco
 */

#ifndef TRIE_TRIENODE_H_
#define TRIE_TRIENODE_H_

#include <hash_map>

using namespace __gnu_cxx;

union character {
	struct Bit {
		unsigned char byte7:1;
		unsigned char byte6:1;
		unsigned char byte5:1;
		unsigned char byte4:1;
		unsigned char byte3:1;
		unsigned char byte2:1;
		unsigned char byte1:1;
		unsigned char byte0:1;
	}byBit;
	char byChar;
};

struct ST_trieNode {
	long key;	// 汉字的utf-8编码, 作为哈希表的节点
	char value[6]; // 汉字的值
	hash_map<long, ST_trieNode*> hash; // 哈希表
    bool isEnd; // 关键词的结尾标记
    long count; // 以该字结尾的词的个数
    ST_trieNode * parent; // 指向父结点
    ST_trieNode * faile; // 指向匹配失败后的失败结点
};

#endif /* TRIE_TRIENODE_H_ */
