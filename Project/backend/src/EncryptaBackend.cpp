
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
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
	void InputHandler::getEncrypted(const char *expression, const char *key, bool isFile) //int length may be a problem later
	{ 
		string encrypted = InputHandler::handleExpression(string(expression), string(key), true);
		if(!isFile)
		{
			ofstream output("return");
			output << encrypted;
			output.close();
		}
		else
		{
			fstream input(expression, ios::binary | ios::out);
			vector<char> fileData;
			long fileSize = InputHandler::getFileSize(expression);
			input.read((char*)&fileData, fileSize);
			string expression = "";
			for (int i = 0; i < fileData.size(); i++)
			{
				expression.push_back(fileData[i]);
			}
			string answer = InputHandler::handleExpression(expression, key, true);
			string fileSave = expression;  fileSave += ".crypt"; //creates a file where encrypted data will be stored (.crypt)
			fstream output(fileSave, ios::binary | ios::in);
			output.write((char*)&expression, expression.length());
			output.close();
			ofstream status("return");
			output << "Encrypted to " << fileSave;
			status.close();
		}
		//instantiate new strings from constants for manipulation
		/* DEPRECIATED CODE: Strings are now passed via reading/writing.
		for (int i = 0; i < encrypted.length(); i++)
		{ //TODO: Fix buffer length checking (Prior implementation would produce false terminations when the buffer still had room)
			/*
			if (bufferlen >= i)
			{
				returnBuffer[0] = '!';
				break;
			}
			returnBuffer[i] = encrypted[i];
		}
		*/
	}
	void InputHandler::getDecrypted(const char *expression, const char *key, bool isFile) //int length may be a problem later
	{
		if (!isFile)
		{
			string encrypted = InputHandler::handleExpression(string(expression), string(key), false);
			ofstream output("return");
			output << encrypted;
			output.close();
		}
		else
		{
			fstream input(expression, ios::binary | ios::out);
			vector<char> fileData;
			long fileSize = InputHandler::getFileSize(expression);
			input.read((char*)&fileData, fileSize);
			string expression = "";
			for (int i = 0; i < fileData.size(); i++)
			{
				expression.push_back(fileData[i]);
			}
			string answer = InputHandler::handleExpression(expression, key, false);
			string fileSave = expression;  fileSave += ".crypt"; //creates a file where encrypted data will be stored (.crypt)
			fstream output(fileSave, ios::binary | ios::in);
			output.write((char*) &expression, expression.length());
			output.close();
			ofstream status("return");
			output << "Encrypted to " << fileSave;
			status.close();
		}
		//instantiate new strings from constants for manipulation
		/* DEPRECIATED: REPLACED WITH FILE READING AND WRITING
		for (int i = 0; i < encrypted.length(); i++)
		{ //TODO: Fix buffer length checking (Prior implementation would produce false terminations when the buffer still had room)
			/*if (bufferlen >= i)
			{
				returnBuffer[0] = '!'; //notifies outofboundserror in writing to buffer
				break;
			}
			returnBuffer[i] = encrypted[i];
		}*/
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
		for (int i = 0; i < expression.length(); i++)
		{
			if (expression[i] == '"')
			{ //avoids the issue of if strings need to preserve spaces in quotes.
				i = expression.find('"', i + 1);
			}
			//upper to lower case
			if (expression[i] <= 'Z' && expression[i] >= 'A')//since ASCII is nicely organized, there is a common difference between lowercase and uppercase chars.
				expression[i] = expression[i] - ('Z' - 'z');
			if (expression[i] == ' ') //trims spaces to reduce issue of "hello " not being equal to "hello"
				expression = expression.substr(0, i) + expression.substr(i + 1, expression.length());
		}
		return expression;
		//TODO: Implement dis
	}
	long InputHandler::getFileSize(string path)
	{
		struct stat filestat; //stat allows me to get file information
		int rc = stat(path.c_str(), &filestat);
		return rc == 0 ? filestat.st_size : -1; //error check line
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
		string encrypted = InputHandler::handleExpression(expression, key, false);
		std::cout << encrypted << "\n";
		std::cout << "Enter File: ";
		std::getline(std::cin, expression);
		InputHandler::getEncrypted(expression, key, true);
		std::cout << "\n" << "Saved to .crypt file in source folder";
	}