
#include <iostream>
#include <string>
#include <cstring>
#include "ModObfuscate.h"
#include "EncryptaBackend.h"
//below imports are currently debug
#include <iostream>
#include <fstream>
using namespace std;

//TODO: display cout messages in the frontend (popupbox)
	string InputHandler::handleExpression(string expression, string key, bool encrypting)
	{
		key = sanitizeInput(key);
		if (key.length() == 0)
			return expression;
		string* functions = splitKey(key);
		string encrypted = expression;
		//std::cout << sizeof(functions); sizeof a string pointer that points to an array produces invalid results.
		string module = "";
		if (encrypting)
			for (int i = 0; i < InputHandler::getKeyLength(key); i++)
			{
				if (functions[i].find(":") != string::npos) //if there is no module specified, assumes previous.
					module = functions[i].substr(0, functions[i].find(":"));
				//std::cout << "DEBUG: " << module;
				//std::cout << "DEBUG: " << functions[i].substr(functions[i].find(":") + 1);
				if (module == "")
				{
					std::cout << "NO MODULE SPECIFIED: " << functions[i] << "\n";
					continue;
				}
				if (module == "obfu")
					encrypted = ModObfuscate::interpretInput(encrypted, functions[i].substr(functions[i].find(":") + 1), encrypting);
				else if (module == "steg")
					std::cout << "Steganograpy not implemented" << "\n";
				else if (module == "cenc")
					std::cout << "Encryption not implemented" << "\n";
				else if (module == "pass")
					std::cout << "Password protection not implemented" << "\n";
				else if (module == "comp")
					std::cout << "Compression not implemented" << "\n";
				else
					std::cout << "Module not found: " << module << "\n";
			}
		else //not encrypting
			for (int i = InputHandler::getKeyLength(key) - 1; i >= 0; i--)
			{
				if (functions[i].find(":") != string::npos) //if there is no module specified, assumes previous.
					module = functions[i].substr(0, functions[i].find(":"));
				if (module == "")
				{ //find a previously referenced module
					for (int j = i - 1; j >= 0; j--)
					{
						if (functions[j].find(":") != string::npos)
						{
							module = functions[j].substr(0, functions[j].find(":"));
							break;
						}
					}
					if (module == "")
					{
						std::cout << "NO MODULE SPECIFIED: " << functions[i] << " AND BACKWARDS\n";
						break;
					}
				}
				if (module == "obfu")
					encrypted = ModObfuscate::interpretInput(encrypted, functions[i].substr(functions[i].find(":") + 1), encrypting);
				else if (module == "steg")
					std::cout << "Steganograpy not implemented";
				else if (module == "cenc")
					std::cout << "Encryption not implemented";
				else if (module == "pass")
					std::cout << "Password protection not implemented";
				else if (module == "comp")
					std::cout << "Compression not implemented";
				else
					std::cout << "Module not found: " << module;
			}
		return encrypted;
	}
	void InputHandler::getEncrypted(const char *expression, const char *key, char *returnBuffer, long bufferlen) //int length may be a problem later
	{ 
		string encrypted = InputHandler::handleExpression(string(expression), string(key), true);
		ofstream output;
		output.open("debug.txt");
		output << encrypted;
		output.close();
		//instantiate new strings from constants for manipulation
		for (int i = 0; i < encrypted.length(); i++)
		{ //TODO: Fix buffer length checking (Prior implementation would produce false terminations when the buffer still had room)
			/*
			if (bufferlen >= i)
			{
				returnBuffer[0] = '!';
				break;
			}*/
			returnBuffer[i] = encrypted[i];
		}
	}
	void InputHandler::getDecrypted(const char *expression, const char *key, char *returnBuffer, long bufferlen) //int length may be a problem later
	{
		string encrypted = InputHandler::handleExpression(string(expression), string(key), false);
		ofstream output;
		output.open("debug.txt");
		output << encrypted;
		output.close();
		//instantiate new strings from constants for manipulation
		for (int i = 0; i < encrypted.length(); i++)
		{ //TODO: Fix buffer length checking (Prior implementation would produce false terminations when the buffer still had room)
			/*if (bufferlen >= i)
			{
				returnBuffer[0] = '!';
				break;
			}*/
			returnBuffer[i] = encrypted[i];
		}
	}

	string* InputHandler::splitKey(string key)
	{
		int i = 0;
		string* functions = new string[getKeyLength(key)];
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
	int InputHandler::getKeyLength(string key)
	{
		int amount = 1;
		if (key.find("|") != string::npos)
			for (int i = 0; i < key.length(); i++)
			{
				if (key[i] == '|')
					amount++;
			}
		return amount;
	}
	string InputHandler::sanitizeInput(string expression)
	{
		return expression;
		//TODO: Implement dis
	}
	int main() //test function
	{
		//in order to use this function:
		//"g++ -o Backendtest -Wall <.cpp files associated with the project>"
		//This generates an executable for the application and the main method runs.
		string expression; string key;
		std::cout << "Enter an expression: ";
		std::getline(std::cin, expression);
		std::cout << "\nEnter a key: ";
		std::getline(std::cin, key);
		string encrypted = InputHandler::handleExpression(expression, key, true);
		std::cout << encrypted << "\n";
		std::cout << InputHandler::handleExpression(encrypted, key, false) << "\n";
	}