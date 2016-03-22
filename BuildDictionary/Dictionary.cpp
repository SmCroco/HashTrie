/*
 * Dictionary.cpp
 *
 *  Created on: 2016年3月14日
 *      Author: smallcroco
 */

#include "Dictionary.h"
#include <iostream>
#include <string.h>

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

		ifstream infile(path.c_str());

		if (infile.is_open()) {

			infile.seekg(0, ios::beg);
			char word[200] = {0};
			memset(word, 0, 200*sizeof(char));
			while (!infile.eof()) {
				infile.getline(word, 200);
				for (int i = 0; (word[i] != '\r' && word[i] != 0); i++) {
					this->trie->insert(word[i]);
				}

				this->trie->setWordEnd();
				memset(word, 0, 200*sizeof(char));
			}
		} else {
			cout<<"词库文件打开失败"<<endl;
		}

		infile.close();
}

void Dictionary::ReadFile(const char* content, long length) {

	char c = 0;

	for (int len = 0; len<length; len++) {

		// 查找一个字符
		c = content[len];
		int d = trie->find(c);

		switch (d) {

		case 0: { // trie树没有找到以此字符开始的词
		}break;

		case 1: { // trie树找到一个以此字符结尾的词，继续往下查找
			cout<<c<<endl;

			char word[200] = {0};
			word[0] = c;

			int i = 1;
			continueMatchContent((content+len+1), (length-len-1), word, i);

		} break;

		case 2: { // trie树找到一个以此字符开始的关键词, 继续往下查找
			char word[200] = {0};
			word[0] = c;

			int i = 1;
			continueMatchContent((content + len+1), length-(len+1), word, i);

		}
		}
	}
}
void Dictionary::ReadFile(string path) {
	// 打开文件流
	file.open(path.c_str());

	// 判断文件是否打开成功
	if (file.is_open()) {

		// 循环读取文件中的一个字符
		char c = 0;
		while ((c = file.get()) != EOF) {
			// 查找一个字符
			int d = trie->find(c);

			switch (d) {

			case 0: { // trie树没有找到以此字符开始的词
			}break;

			case 1: { // trie树找到一个以此字符结尾的词，继续往下查找
				cout<<c<<endl;

				char word[200] = {0};
				word[0] = c;

				int i = 1;

				// 记录当前位置
				long l = file.tellg();

				continueMatchFile(word, i);

				// 返回先前位置
				file.seekg(l, ios::beg);
			} break;

			case 2: { // trie树找到一个以此字符开始的关键词, 继续往下查找
				char word[200] = {0};
				word[0] = c;

				int i = 1;
				// 记录当前位置
				long l = file.tellg();

				continueMatchFile(word, i);

				// 返回先前位置
				file.seekg(l, ios::beg);
			}
			}
		}

		file.close();
	} else {
		cout<<"读取文件内容失败"<<endl;
	}


}

/*
 * @Function Name: continueMatch
 * @Parameter [in, out] char* word: 用来存放匹配成功的字符
 * @Parameter [in] int i: 用来偏移word的下标
 * @Description:
 */
void Dictionary::continueMatchFile(char* word, int i) {

	char c = 0;
	while ( (c = file.get()) != EOF) {

		int location = trie->find(c);

		switch(location) {
		case 0: { // 此次查找结束
			return;
		}
		case 1: { // 找到一个关键词, 然后继续往下找下一个词
			word[i] = c;
			cout<<word<<endl;

			i++;
		} break;
		case 2: { // 匹配成功，继续往下匹配
			word[i] = c;
			i++;
		}
		}

	}
}

void Dictionary::continueMatchContent(const char* content, long length, char* word, int i){
	char c = 0;
	for(int len=0; len<length; len++) {
		c = content[len];
		int d = trie->find(c);

		switch(d) {
		case 0:{ // 此次查找结束
			return;
		}

		case 1:{ // 找到一个关键词, 然后继续往下找下一个词
			word[i] = c;
			cout<<word<<endl;

			i++;
		} break;

		case 2:{ // 匹配成功，继续往下匹配
			word[i] = c;
			i++;
		}
		}
	}
}
