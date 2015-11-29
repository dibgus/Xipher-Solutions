#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>
#include <iterator>
#include "ModObfuscate.h"
#include "EncryptaBackend.h"
#include "ModSteganography.h"
//below imports are currently debug
#include <iostream>
#include <fstream>
#include <wchar.h>
#include <assert.h>
#include <locale>
using namespace std;
//	: display wcout messages in the frontend (popupbox)
	wstring InputHandler::handleExpression(wstring expression, wstring key, bool encrypting)
	{
		key = sanitizeInput(key);
		if (key.length() == 0)
			return expression;
		wstring* functions = splitKey(key);
		wstring encrypted = expression;
		//std::wcout << sizeof(functions); sizeof a wstring pointer that points to an array produces invalid results.
		wstring module = L"";
		if (encrypting)
			for (int i = 0; i < InputHandler::getKeyLength(key); i++)
			{
				if (functions[i].find(L":") != wstring::npos) //if there is no module specified, assumes previous.
					module = functions[i].substr(0, functions[i].find(L":"));
				//std::wcout << "DEBUG: " << module;
				//std::wcout << "DEBUG: " << functions[i].substr(functions[i].find(":") + 1);
				if (module == L"")
				{
					std::wcout << L"NO MODULE SPECIFIED: " << functions[i] << "\n";
					continue;
				}
				if (module == L"obfu")
					encrypted = ModObfuscate::interpretInput(encrypted, functions[i].substr(functions[i].find(L":") + 1), encrypting);
				else if (module == L"steg")
					//encrypted = L"wizards";
					encrypted = ModSteganography::interpretInput(encrypted, functions[i].substr(functions[i].find(L":") + 1), encrypting);
					//std::wcout << ModSteganography::interpretInput(encrypted, functions[i].substr(functions[i].find(":") + 1), encrypting) << "\n";
				else if (module == L"cenc")
					std::wcout << "Encryption not implemented" << "\n";
				else if (module == L"pass")
					std::wcout << "Password protection not implemented" << "\n";
				else if (module == L"comp")
					std::wcout << "Compression not implemented" << "\n";
				else
					std::wcout << "Module not found: " << module.c_str() << "\n";
			}
		else //not encrypting
			for (int i = InputHandler::getKeyLength(key) - 1; i >= 0; i--)
			{
				if (functions[i].find(L":") != wstring::npos) //if there is no module specified, assumes previous.
					module = functions[i].substr(0, functions[i].find(L":"));
				if (module == L"")
				{ //find a previously referenced module
					for (int j = i - 1; j >= 0; j--)
					{
						if (functions[j].find(L":") != wstring::npos)
						{
							module = functions[j].substr(0, functions[j].find(L":"));
							if(encrypting) break;
						}
					}
					if (module == L"")
					{
						std::wcout << "NO MODULE SPECIFIED: " << functions[i] << " AND BACKWARDS\n";
						break;
					}
				}
				if (module == L"obfu")
					encrypted = ModObfuscate::interpretInput(encrypted, functions[i].substr(functions[i].find(L":") + 1), encrypting);
				else if (module == L"steg") //steg module calls for end of interpretation of the rest of the key (may change this later)
				{
					encrypted = ModSteganography::interpretInput(expression, functions[i].substr(functions[i].find(L":") + 1), encrypting);
					break;
				}
				else if (module == L"cenc")
					std::wcout << "Encryption not implemented";
				else if (module == L"pass")
					std::wcout << "Password protection not implemented";
				else if (module == L"comp")
					std::wcout << "Compression not implemented";
				else
					std::wcout << "Module not found: " << module;
			}
		return encrypted;
	}

	void InputHandler::getEncrypted(wstring expression, wstring key, bool isFile) //int length may be a problem later
	{
		if(!isFile)
		{
			//UTF-16 ISSUE HAS BEEN ISOLATED TO WOFSTREAM!!
			assert(expression.find(L"Ž") != wstring::npos);
			wstring encrypted = InputHandler::handleExpression(expression, key, true);
			wofstream output("return", ios::binary);
			output << encrypted.c_str();
			//output << "resultant: " << expression;
			output.close();
		}
		else
		{
			wofstream status("return", ios::binary);
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
			status << "Encrypted to " << outFile.c_str();
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
	void InputHandler::getDecrypted(wstring expression, wstring key, bool isFile) //int length may be a problem later
	{
		if (!isFile)
		{
			wstring decrypted = InputHandler::handleExpression(expression, key, false);
			wofstream output("return", ios::binary);
			std::locale::global(std::locale(""));
			output << decrypted.c_str();
			//output << "resultant: " << expression;
			output.close();
		}
		else
		{
			wofstream status("return", ios::binary);
			vector<wchar_t> fileData;
			fileData.reserve(getFileSize(expression));
			wifstream fileInStream(expression);
			int i = 0;
			fileData.assign(istreambuf_iterator<wchar_t>(fileInStream), istreambuf_iterator<wchar_t>());
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
			status << "Decrypted to " << outFile.c_str(); // conversion issue
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
		wifstream file(path, ios::binary);
		streampos start, end;
		start = file.tellg(); //file read already start on starting index
		file.seekg(0, ios::end);
		end = file.tellg();
		file.seekg(end - start, ios::beg); //seek back to start for file read.
		return end - start;
	}

	wstring* InputHandler::splitKey(wstring key)
	{
		int i = 0;
		wstring* functions = new wstring[getKeyLength(key)];
		while (key.length() > 0)
		{
			if (key.find(L"|") != wstring::npos)
				functions[i] = key.substr(0, key.find(L"|"));
			else
			{
				functions[i] = key;
				break;
			}
			key = key.substr(key.find(L"|") + 1);
			i++;
		}
		return functions;
	}
	int InputHandler::getKeyLength(wstring key)
	{
		int amount = 1;
		if (key.find(L"|") != wstring::npos)
			for (int i = 0; i < key.length(); i++)
			{
				if (key[i] == '|')
					amount++;
			}
		return amount;
	}
	wstring InputHandler::sanitizeInput(wstring expression)
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
		wstring expression; wstring key;
		std::wcout << "Enter an expression: ";
		std::getline(std::wcin, expression);
		std::wcout << "\nEnter a key: ";
		std::getline(std::wcin, key);
		wstring encrypted = InputHandler::handleExpression(expression, key, false);
		std::wcout << encrypted << "\n";
		std::wcout << "Enter File: ";
		std::getline(std::wcin, expression);
		InputHandler::getEncrypted(expression, key, true);
		std::wcout << "\n" << "Saved to .crypt file in source folder";
	}