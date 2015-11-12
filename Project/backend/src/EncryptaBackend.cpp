#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <iterator>
#include "ModObfuscate.h"
#include "EncryptaBackend.h"
#include "ModSteganography.h"
//#include "ModSteganography.h"
//below imports are currently debug
#include <iostream>
#include <fstream>
#include <wchar.h>
using namespace std;
//TODO: display wcout messages in the frontend (popupbox)
//>>IDEA: Create log file area for frontend for debugging
	wstring InputHandler::handleExpression(wstring expression, string key, bool encrypting)
	{
		key = sanitizeInput(key);
		if (key.length() == 0)
			return expression;
		string* functions = splitKey(key);
		wstring encrypted = expression;
		//std::wcout << sizeof(functions); sizeof a wstring pointer that points to an array produces invalid results.
		string module = "";
		if (encrypting)
			for (int i = 0; i < InputHandler::getKeyLength(key); i++)
			{
				if (functions[i].find(":") != string::npos) //if there is no module specified, assumes previous.
					module = functions[i].substr(0, functions[i].find(":"));
				//std::wcout << "DEBUG: " << module;
				//std::wcout << "DEBUG: " << functions[i].substr(functions[i].find(":") + 1);
				if (module == "")
				{
					std::cout << "NO MODULE SPECIFIED: " << functions[i] << "\n";
					continue;
				}
				if (module == "obfu")
					encrypted = ModObfuscate::interpretInput(encrypted, functions[i].substr(functions[i].find(":") + 1), encrypting);
				else if (module == "steg")
					encrypted = ModSteganography::interpretInput(encrypted, functions[i].substr(functions[i].find(":") + 1), encrypting);
					//std::wcout << ModSteganography::interpretInput(encrypted, functions[i].substr(functions[i].find(":") + 1), encrypting) << "\n";
				else if (module == "cenc")
					std::wcout << "Encryption not implemented" << "\n";
				else if (module == "pass")
					std::wcout << "Password protection not implemented" << "\n";
				else if (module == "comp")
					std::wcout << "Compression not implemented" << "\n";
				else
					std::wcout << "Module not found: " << module.c_str() << "\n";
			}
		else //not encrypting
			for (int i = InputHandler::getKeyLength(key) - 1; i >= 0; i--)
			{
				if (functions[i].find(":") != wstring::npos) //if there is no module specified, assumes previous.
					module = functions[i].substr(0, functions[i].find(":"));
				if (module == "")
				{ //find a previously referenced module
					for (int j = i - 1; j >= 0; j--)
					{
						if (functions[j].find(":") != wstring::npos)
						{
							module = functions[j].substr(0, functions[j].find(":"));
							if(encrypting) break;
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
				else if (module == "steg") //steg module calls for end of interpretation of the rest of the key (may change this later)
				{
					//encrypted = ModSteganography::interpretInput(expression, functions[i].substr(functions[i].find(":") + 1), encrypting);
					break;
				}
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
	void InputHandler::getEncrypted(const wchar_t *expression, const char *key, bool isFile) //int length may be a problem later
	{ 
		if(!isFile)
		{
			wstring encrypted = InputHandler::handleExpression(wstring(expression), string(key), true);
			wofstream output("return");
			output << encrypted;
			output.close();
		}
		else
		{
			wofstream status("return");

			vector<wchar_t> fileData;
			fileData.reserve(getFileSize(expression));
			wifstream fileInStream(expression, ios::binary);
			int i = 0;
			fileData.assign(istreambuf_iterator<wchar_t>(fileInStream),
				istreambuf_iterator<wchar_t>());
			//fileInStream.read(fileData.data, fileInStream.end); //read file into buffer
			fileInStream.close();
			wstring toEncrypt = L"";
			for (int i = 0; i < fileData.size(); i++)
				toEncrypt.push_back(fileData[i]);
			wstring encryptedData = InputHandler::handleExpression(toEncrypt, key, true);
			wstring outFile = expression;
			outFile += L".crypt";
			wofstream encryptedFile(outFile, ios::binary);
			encryptedFile << encryptedData;
			encryptedFile.close();
			
			status << "Encrypted to " << outFile;
			status.close();
		}
		//instantiate new wstrings from constants for manipulation
		/* DEPRECIATED CODE: wstrings are now passed via reading/writing.
		for (int i = 0; i < encrypted.length(); i++)
		{ //TODO: Fix buffer length checking (Prior implementation would produce false terminations when the buffer still had room)
			/*
			if (bufferlen >= i)
			{
				returnBuffer[0] = '!';
				break;
			}
			returnBuffer[i] = encrypted[i];
		}*/
	}
	void InputHandler::getDecrypted(const wchar_t *expression, const char *key, bool isFile) //int length may be a problem later
	{
		if (!isFile)
		{
			wstring encrypted = InputHandler::handleExpression(wstring(expression), string(key), false);
			wofstream output("return");
			output << encrypted;
			output.close();
		}
		else
		{
			wofstream status("return");

			vector<wchar_t> fileData;
			fileData.reserve(getFileSize(expression));
			wifstream fileInStream(expression, ios::binary);
			int i = 0;
			fileData.assign(istreambuf_iterator<wchar_t>(fileInStream),
				istreambuf_iterator<wchar_t>());
			fileInStream.close();
			wstring toDecrypt = L"";
			for (int i = 0; i < fileData.size(); i++)
				toDecrypt.push_back(fileData[i]);
			wstring decryptedData = InputHandler::handleExpression(toDecrypt, key, true);
			wstring outFile = expression;
			if (outFile.find(L".crypt") != wstring::npos)
				outFile = outFile.substr(0, outFile.find(L".crypt")); //truncate the .crypt extension
			wofstream decryptedFile(outFile, ios::binary);
			decryptedFile.write(decryptedData.c_str(), decryptedData.length());
			//decryptedFile << encryptedData;
			decryptedFile.close();	
			status << "Decrypted to " << outFile;
			status.close();
		}
		//instantiate new wstrings from constants for manipulation
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
	long InputHandler::getFileSize(wstring path)
	{
		ifstream file(path, ios::binary);
		streampos start, end;
		start = file.tellg(); //file read already start on starting index
		file.seekg(0, ios::end);
		end = file.tellg();
		file.seekg(end - start, ios::beg); //seek back to start for file read.
		return end - start;
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
			{ //avoids the issue of if wstrings need to preserve spaces in quotes.
				i = expression.find('"', i + 1);
			}
			//upper to lower case
			if (expression[i] <= 'Z' && expression[i] >= 'A')//since ASCII is nicely organized, there is a common difference between lowercase and uppercase wchar_ts.
				expression[i] = expression[i] - ('Z' - 'z');
			if (expression[i] == ' ') //trims spaces to reduce issue of "hello " not being equal to "hello"
				expression = expression.substr(0, i) + expression.substr(i + 1, expression.length());
		}
		return expression;
	}
	int main() //test function
	{
		//in order to use this function:
		//"g++ -o Backendtest -Wall <.cpp files associated with the project>"
		//This generates an executable for the application and the main method runs.
		wstring expression; string key;
		std::cout << "Enter an expression: ";
		std::getline(std::wcin, expression);
		std::cout << "\nEnter a key: ";
		std::getline(std::cin, key);
		wstring encrypted = InputHandler::handleExpression(expression, key, false);
		std::wcout << encrypted << "\n";
		std::cout << "Enter File: ";
		std::getline(std::wcin, expression);
		InputHandler::getEncrypted(expression.c_str(), key.c_str(), true);
		std::cout << "\n" << "Saved to .crypt file in source folder";
	}