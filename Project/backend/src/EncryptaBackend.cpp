//============================================================================
// Name        : EncryptaBackend.cpp
// Author      : Ivan Krukov
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <cstring>
#include "ModObfuscate.h"
#include "EncryptaBackend.h"
using namespace std;


string InputHandler::encryptExpression(string expression, string key)
{
	string* functions = splitKey(key);
	string encrypted = "";
	for(int i = 0; i < sizeof(functions); i++)
	{
		string module = functions[i].substr(0, functions[i].find(":"));
		if(module == "obfus")
			encrypted = ModObfuscate::interpretInput(expression, functions[i].substr(functions[i].find(":") + 1));
		else if(module == "steg")
			std::cout << "Steganograpy not implemented";
		else if(module == "cenc")
			std::cout << "Encryption not implemented";
		else
			std::cout << "Module not found: " << module;
	}
	return encrypted;
}

string* InputHandler::splitKey(string key)
{
	int amount = 1;
	int i;
	for(i = 0; i < key.length(); i++)
	{
		if(key[i] == '|')
			amount++;
	}
	i = 0;
	string functions[amount];
	while(key.length() > 0)
	{
		if(key.find("|") != string::npos)
			functions[i] = key.substr(0, key.find("|"));
		else
		{
			functions[i] = key;
			break;
		}
		key = key.substr(key.find("|") + 1);
		i++;
	}
	return functions;
}

