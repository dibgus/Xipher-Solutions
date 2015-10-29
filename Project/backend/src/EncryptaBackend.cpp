
#include <iostream>
#include <string>
#include <cstring>
#include "ModObfuscate.h"
#include "EncryptaBackend.h"
//tmp
#include <iostream>
#include <fstream>
using namespace std;

//extern "C" __declspec(dllexport)
	string InputHandler::encryptExpression(string expression, string key)
	{
		if (key.length() == 0)
			return expression;

		string* functions = splitKey(key);
		string encrypted = "";
		for (int i = 0; i < sizeof(functions); i++)
		{
			string module = functions[i].substr(0, functions[i].find(":"));
			if (module == "obfus")
				encrypted = ModObfuscate::interpretInput(expression, functions[i].substr(functions[i].find(":") + 1));
			else if (module == "steg")
				std::cout << "Steganograpy not implemented";
			else if (module == "cenc")
				std::cout << "Encryption not implemented";
			else
				std::cout << "Module not found: " << module;
		}
		return encrypted;
	}
	void InputHandler::getEncrypted(const char *expression, const char *key, char *returnBuffer, int bufferLength) //int length may be a problem later
	{ 
		string encrypted = InputHandler::encryptExpression(string(expression), string(key));
		ofstream output;
		output.open("debug.txt");
		output << encrypted;
		output.close();
		//instantiate new strings from constants for manipulation
		for (int i = 0; i < encrypted.length(); i++)
		{
			if (i >= bufferLength) //idea: ditch the idea of writing to buffers to transfer data and write the return results to temporary files which could be read and discarded
			{
				returnBuffer[0] = 'E';
				returnBuffer[1] = 'R';
				returnBuffer[2] = 'R';
				break;
			}
			returnBuffer[i] = encrypted[i];
		}
	}

	string* InputHandler::splitKey(string key)
	{
		int amount = 1;
		string::size_type i;
		for (i = 0; i < key.length(); i++)
		{
			if (key[i] == '|')
				amount++;
		}
		i = 0;
		string* functions = new string[amount];
		while (key.length() > 0)
		{
			if (key.find("|") != string::npos)
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
	int main() //test function
	{
		string expression; string key;
		std::cout << "Enter an expression: ";
		std::getline(std::cin, expression);
		std::cout << "\nEnter a key: ";
		std::getline(std::cin, key);
		std::cout << InputHandler::encryptExpression(expression, key);
	}