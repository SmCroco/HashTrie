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

	sum = 0;
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

		// 用来标记每一个UTF8字符占几个字节
		int n = 0;

		// 记录每一个UTF8字符的unicode编码
		long char_encode = 0;

		// 循环读取文件中的字符
		character value[6];

		char word[200] = { 0 };
		memset(word, 0, 200 * sizeof(char));
		while (!infile.eof()) {
			infile.getline(word, 200);
			for (int i = 0; (word[i] != '\r' && word[i] != 0);) {
//					this->trie->insert(word[i]);
				value[0].byChar = word[i];
				i += 1;

				// 获取utf8单个字符的长度
				n = getCharacterLen(value[0]);

				switch (n) {
				case 1: {

					// utf8的字符编码
					char_encode = value[0].byChar;

					this->trie->insert(char_encode, 1, value);
				}
					break;

				case 2: {

					value[1].byChar = word[i];
					i += 1;

					// utf8的字符编码
					char_encode = ((value[0].byChar & 0x1f) << 6)
							+ (value[1].byChar & 0x3f);

					this->trie->insert(char_encode, 2, value);
				}
					break;

				case 3: {
					value[1].byChar = word[i];
					i += 1;
					value[2].byChar = word[i];
					i += 1;

					// utf8的字符编码
					char_encode = ((value[0].byChar & 0x0f) << 12)
							+ ((value[1].byChar & 0x3f) << 6)
							+ (value[2].byChar & 0x3f);

					this->trie->insert(char_encode, 3, value);
				}
					break;

				case 4: {
					value[1].byChar = word[i];
					i += 1;
					value[2].byChar = word[i];
					i += 1;
					value[3].byChar = word[i];
					i += 1;

					// utf8的字符编码
					char_encode = ((value[0].byChar & 0x07) << 18)
							+ ((value[1].byChar & 0x3f) << 12)
							+ ((value[2].byChar & 0x3f) << 6)
							+ (value[3].byChar & 0x3f);
					this->trie->insert(char_encode, 4, value);
				}
					break;

				case 5: {
					value[1].byChar = word[i];
					i += 1;
					value[2].byChar = word[i];
					i += 1;
					value[3].byChar = word[i];
					i += 1;
					value[4].byChar = word[i];
					i += 1;

					// utf8的字符编码
					char_encode = ((value[0].byChar & 0x03) << 24)
							+ ((value[1].byChar & 0x3f) << 18)
							+ ((value[2].byChar & 0x3f) << 12)
							+ ((value[3].byChar & 0x3f) << 6)
							+ (value[4].byChar & 0x3f);
					this->trie->insert(char_encode, 5, value);
				}
					break;

				case 6: {
					value[1].byChar = word[i];
					i += 1;
					value[2].byChar = word[i];
					i += 1;
					value[3].byChar = word[i];
					i += 1;
					value[4].byChar = word[i];
					i += 1;
					value[5].byChar = word[i];
					i += 1;

					// utf8的字符编码
					char_encode = ((value[0].byChar & 0x1) << 30)
							+ ((value[1].byChar & 0x3f) << 24)
							+ ((value[2].byChar & 0x3f) << 18)
							+ ((value[3].byChar & 0x3f) << 12)
							+ ((value[4].byChar & 0x3f) << 6)
							+ (value[5].byChar & 0x3f);

					this->trie->insert(char_encode, 6, value);
				}
					break;

				default: {
					cout << "字符不正确" << endl;
				}
				}
			}

			this->trie->setWordEnd();
			memset(word, 0, 200 * sizeof(char));
			sum += 1;
		}

		cout<<sum<<endl;
		infile.close();
	} else {
		cout << "词库文件打开失败" << endl;
	}


}

void Dictionary::ReadFile(const char* content, long length) {

	// UTF-8编码
	long encode = 0;
	int n = 0;
	for (int len = 0; len < length; ) {

		character value[6];
		value[0].byChar = content[len];
		len += 1;

		n = getCharacterLen(value[0]);
		switch(n) {

		case 1: {
			// utf8的字符编码
			encode = value[0].byChar;
		}
			break;

		case 2: {
//				value[1].byChar = file.get();
			value[1].byChar = content[len];
			len += 1;
			// utf8的字符编码
			encode = ((value[0].byChar & 0x1f) << 6)
					+ (value[1].byChar & 0x3f);
		}
			break;

		case 3: {
//				value[1].byChar = file.get();
//				value[2].byChar = file.get();
			value[1].byChar = content[len];
			len += 1;
			value[2].byChar = content[len];
			len += 1;
			// utf8的字符编码
			encode = ((value[0].byChar & 0x0f) << 12)
					+ ((value[1].byChar & 0x3f) << 6)
					+ (value[2].byChar & 0x3f);
		}
			break;

		case 4: {
//				value[1].byChar = file.get();
//				value[2].byChar = file.get();
//				value[3].byChar = file.get();
			value[1].byChar = content[len];
			len += 1;
			value[2].byChar = content[len];
			len += 1;
			value[3].byChar = content[len];
			len += 1;
			// utf8的字符编码
			encode = ((value[0].byChar & 0x07) << 18)
					+ ((value[1].byChar & 0x3f) << 12)
					+ ((value[2].byChar & 0x3f) << 6)
					+ (value[3].byChar & 0x3f);
		}
			break;

		case 5: {
//				value[1].byChar = file.get();
//				value[2].byChar = file.get();
//				value[3].byChar = file.get();
//				value[4].byChar = file.get();
			value[1].byChar = content[len];
			len += 1;
			value[2].byChar = content[len];
			len += 1;
			value[3].byChar = content[len];
			len += 1;
			value[4].byChar = content[len];
			len += 1;
			// utf8的字符编码
			encode = ((value[0].byChar & 0x03) << 24)
					+ ((value[1].byChar & 0x3f) << 18)
					+ ((value[2].byChar & 0x3f) << 12)
					+ ((value[3].byChar & 0x3f) << 6)
					+ (value[4].byChar & 0x3f);
		}
			break;

		case 6: {
//				value[1].byChar = file.get();
//				value[2].byChar = file.get();
//				value[3].byChar = file.get();
//				value[4].byChar = file.get();
//				value[5].byChar = file.get();
			value[1].byChar = content[len];
			len += 1;
			value[2].byChar = content[len];
			len += 1;
			value[3].byChar = content[len];
			len += 1;
			value[4].byChar = content[len];
			len += 1;
			value[5].byChar = content[len];
			len += 1;
			// utf8的字符编码
			encode = ((value[0].byChar & 0x1) << 30)
					+ ((value[1].byChar & 0x3f) << 24)
					+ ((value[2].byChar & 0x3f) << 18)
					+ ((value[3].byChar & 0x3f) << 12)
					+ ((value[4].byChar & 0x3f) << 6)
					+ (value[5].byChar & 0x3f);
		}
			break;

		default: {
			cout << "字符不正确" << endl;
		}
		}

		int d = trie->find(encode);
		if (d != 0) {
			continueMatchContent((content + len ), (length - len));
		}
	}
}
void Dictionary::ReadFile(string path) {
	// 打开文件流
	file.open(path.c_str());

	// 判断文件是否打开成功
	if (file.is_open()) {

		// UTF-8编码
		long encode = 0;
		int n = 0;

		// 循环读取文件中的一个字符
		string s;
		int i = 0;
		character value[6];
		for(s; getline(file,s); ) {
			i = 0;
			while(s[i] != '\r' && s[i] != 0) {
				value[0].byChar = s[i];
				i+=1;
			n = getCharacterLen(value[0]);
			switch(n) {
			case 1: {
				// utf8的字符编码
				encode = value[0].byChar;
			}
				break;

			case 2: {
//				value[1].byChar = file.get();
				value[1].byChar = s[i];
				i += 1;
				// utf8的字符编码
				encode = ((value[0].byChar & 0x1f) << 6)
						+ (value[1].byChar & 0x3f);
			}
				break;

			case 3: {
//				value[1].byChar = file.get();
//				value[2].byChar = file.get();
				value[1].byChar = s[i];
				i+=1;
				value[2].byChar = s[i];
				i+=1;
				// utf8的字符编码
				encode = ((value[0].byChar & 0x0f) << 12)
						+ ((value[1].byChar & 0x3f) << 6)
						+ (value[2].byChar & 0x3f);
			}
				break;

			case 4: {
//				value[1].byChar = file.get();
//				value[2].byChar = file.get();
//				value[3].byChar = file.get();
				value[1].byChar = s[i];
				i+=1;
				value[2].byChar = s[i];
				i+=1;
				value[3].byChar = s[i];
				i+=1;
				// utf8的字符编码
				encode = ((value[0].byChar & 0x07) << 18)
						+ ((value[1].byChar & 0x3f) << 12)
						+ ((value[2].byChar & 0x3f) << 6)
						+ (value[3].byChar & 0x3f);
			}
				break;

			case 5: {
//				value[1].byChar = file.get();
//				value[2].byChar = file.get();
//				value[3].byChar = file.get();
//				value[4].byChar = file.get();
				value[1].byChar = s[i];
				i+=1;
				value[2].byChar = s[i];
				i+=1;
				value[3].byChar = s[i];
				i+=1;
				value[4].byChar = s[i];
				i+=1;
				// utf8的字符编码
				encode = ((value[0].byChar & 0x03) << 24)
						+ ((value[1].byChar & 0x3f) << 18)
						+ ((value[2].byChar & 0x3f) << 12)
						+ ((value[3].byChar & 0x3f) << 6)
						+ (value[4].byChar & 0x3f);
			}
				break;

			case 6: {
//				value[1].byChar = file.get();
//				value[2].byChar = file.get();
//				value[3].byChar = file.get();
//				value[4].byChar = file.get();
//				value[5].byChar = file.get();
				value[1].byChar = s[i];
				i+=1;
				value[2].byChar = s[i];
				i+=1;
				value[3].byChar = s[i];
				i+=1;
				value[4].byChar = s[i];
				i+=1;
				value[5].byChar = s[i];
				i += 1;
				// utf8的字符编码
				encode = ((value[0].byChar & 0x1) << 30)
						+ ((value[1].byChar & 0x3f) << 24)
						+ ((value[2].byChar & 0x3f) << 18)
						+ ((value[3].byChar & 0x3f) << 12)
						+ ((value[4].byChar & 0x3f) << 6)
						+ (value[5].byChar & 0x3f);
			}
				break;

			default: {
				cout << "字符不正确" << endl;
			}

			}

			// 查找一个字符
			int d = trie->find(encode);

			switch (d) {
			case 0: { // trie树没有找到以此字符开始的词
			}
				break;

			case 1: { // trie树找到一个以此字符结尾的词，继续往下查找

				// 记录当前位置
//				long l = file.tellg();

				continueMatchFile(s, i);

				// 返回先前位置
//				file.seekg(l, ios::beg);
			}
				break;

			case 2: { // trie树找到一个以此字符开始的关键词, 继续往下查找
				// 记录当前位置
//				long l = file.tellg();

				continueMatchFile(s, i);

				// 返回先前位置
//				file.seekg(l, ios::beg);
			}
			}
		}
		}

		file.close();
	} else {
		cout << "读取文件内容失败" << endl;
	}

}

/*
 * @Function Name: continueMatch
 * @Parameter [in, out] char* word: 用来存放匹配成功的字符
 * @Parameter [in] int i: 用来偏移word的下标
 * @Description:
 */
void Dictionary::continueMatchFile(string s, int i) {

	long encode = 0;
	int n = 0;
	character value[6];
	while (s[i] != '\r'){
		value[0].byChar = s[i];
		i+=1;

		n = getCharacterLen(value[0]);

		// 获取字符编码
		switch(n) {
			case 1: {
				// utf8的字符编码
				encode = value[0].byChar;
			}
				break;

			case 2: {
				value[1].byChar = s[i];
				i+=1;
				// utf8的字符编码
				encode = ((value[0].byChar & 0x1f) << 6)
						+ (value[1].byChar & 0x3f);
			}
				break;

			case 3: {
				value[1].byChar = s[i];
				i+=1;
				value[2].byChar = s[i];
				i+=1;
				// utf8的字符编码
				encode = ((value[0].byChar & 0x0f) << 12)
						+ ((value[1].byChar & 0x3f) << 6)
						+ (value[2].byChar & 0x3f);
			}
				break;

			case 4: {
				value[1].byChar = s[i];
				i+=1;
				value[2].byChar = s[i];
				i+=1;
				value[3].byChar = s[i];
				i+=1;
				// utf8的字符编码
				encode = ((value[0].byChar & 0x07) << 18)
						+ ((value[1].byChar & 0x3f) << 12)
						+ ((value[2].byChar & 0x3f) << 6)
						+ (value[3].byChar & 0x3f);
			}
				break;

			case 5: {
				value[1].byChar = s[i];
				i+=1;
				value[2].byChar = s[i];
				i+=1;
				value[3].byChar = s[i];
				i+=1;
				value[4].byChar = s[i];
				i+=1;
				// utf8的字符编码
				encode = ((value[0].byChar & 0x03) << 24)
						+ ((value[1].byChar & 0x3f) << 18)
						+ ((value[2].byChar & 0x3f) << 12)
						+ ((value[3].byChar & 0x3f) << 6)
						+ (value[4].byChar & 0x3f);
			}
				break;

			case 6: {
				value[1].byChar = s[i];
				i+=1;
				value[2].byChar = s[i];
				i+=1;
				value[3].byChar = s[i];
				i+=1;
				value[4].byChar = s[i];
				i+=1;
				value[5].byChar = s[i];
				i += 1;
				// utf8的字符编码
				encode = ((value[0].byChar & 0x1) << 30)
						+ ((value[1].byChar & 0x3f) << 24)
						+ ((value[2].byChar & 0x3f) << 18)
						+ ((value[3].byChar & 0x3f) << 12)
						+ ((value[4].byChar & 0x3f) << 6)
						+ (value[5].byChar & 0x3f);
			}
				break;

			default: {
				cout << "字符不正确" << endl;
			}
		}

		// 查找字符
		int location = trie->find(encode);

		if (location == 0) {
			return ;
		}

	}
}

void Dictionary::continueMatchContent(const char* content, long length) {
	long encode = 0;
	int n = 0;
	character value[6];
	for (int len = 0; len < length; ) {
		value[0].byChar = content[len];
		len += 1;

		n = getCharacterLen(value[0]);
		switch(n) {
		case 1: {
			// utf8的字符编码
			encode = value[0].byChar;
		}
			break;

		case 2: {
			value[1].byChar = content[len];
			len += 1;
			// utf8的字符编码
			encode = ((value[0].byChar & 0x1f) << 6)
					+ (value[1].byChar & 0x3f);
		}
			break;

		case 3: {
			value[1].byChar = content[len];
			len += 1;
			value[2].byChar = content[len];
			len += 1;
			// utf8的字符编码
			encode = ((value[0].byChar & 0x0f) << 12)
					+ ((value[1].byChar & 0x3f) << 6)
					+ (value[2].byChar & 0x3f);
		}
			break;

		case 4: {
			value[1].byChar = content[len];
			len += 1;
			value[2].byChar = content[len];
			len += 1;
			value[3].byChar = content[len];
			len += 1;
			// utf8的字符编码
			encode = ((value[0].byChar & 0x07) << 18)
					+ ((value[1].byChar & 0x3f) << 12)
					+ ((value[2].byChar & 0x3f) << 6)
					+ (value[3].byChar & 0x3f);
		}
			break;

		case 5: {
			value[1].byChar = content[len];
			len += 1;
			value[2].byChar = content[len];
			len += 1;
			value[3].byChar = content[len];
			len += 1;
			value[4].byChar = content[len];
			len += 1;
			// utf8的字符编码
			encode = ((value[0].byChar & 0x03) << 24)
					+ ((value[1].byChar & 0x3f) << 18)
					+ ((value[2].byChar & 0x3f) << 12)
					+ ((value[3].byChar & 0x3f) << 6)
					+ (value[4].byChar & 0x3f);
		}
			break;

		case 6: {
			value[1].byChar = content[len];
			len += 1;
			value[2].byChar = content[len];
			len += 1;
			value[3].byChar = content[len];
			len += 1;
			value[4].byChar = content[len];
			len += 1;
			value[5].byChar = content[len];
			len += 1;
			// utf8的字符编码
			encode = ((value[0].byChar & 0x1) << 30)
					+ ((value[1].byChar & 0x3f) << 24)
					+ ((value[2].byChar & 0x3f) << 18)
					+ ((value[3].byChar & 0x3f) << 12)
					+ ((value[4].byChar & 0x3f) << 6)
					+ (value[5].byChar & 0x3f);
		}
			break;

		default: {
			cout << "字符不正确" << endl;
		}
		}

		int d = trie->find(encode);

		if (d == 0) {
			return ;
		}

	}
}

int Dictionary::getCharacterLen(character c) {

	if (c.byBit.byte0 == 0) {
		return 1;
	}

	if (c.byBit.byte0 == 1 && c.byBit.byte1 == 1 && c.byBit.byte2 == 0) {
		return 2;
	}

	if (c.byBit.byte0 == 1 && c.byBit.byte1 == 1 && c.byBit.byte2 == 1
			&& c.byBit.byte3 == 0) {
		return 3;
	}

	if (c.byBit.byte0 == 1 && c.byBit.byte1 == 1 && c.byBit.byte2 == 1
			&& c.byBit.byte3 == 1 && c.byBit.byte4 == 0) {
		return 4;
	}

	if (c.byBit.byte0 == 1 && c.byBit.byte1 == 1 && c.byBit.byte2 == 1
			&& c.byBit.byte3 == 1 && c.byBit.byte4 == 1 && c.byBit.byte5 == 0) {
		return 5;
	}

	if (c.byBit.byte0 == 1 && c.byBit.byte1 == 1 && c.byBit.byte2 == 1
			&& c.byBit.byte3 == 1 && c.byBit.byte4 == 1 && c.byBit.byte5 == 1
			&& c.byBit.byte6 == 0) {
		return 6;
	}

	return 0;
}
