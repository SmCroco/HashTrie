/*
 * main.cpp
 *
 *  Created on: 2016年3月11日
 *      Author: smallcroco
 */

#include <iostream>
#include <string>
#include "Dictionary.h"

using namespace std;

int main() {

	string path = "test.txt";

	// 初始化词库
	Dictionary dictionary;
	dictionary.InitDictionary(path);

	int a = 1;
	return 0;
}


