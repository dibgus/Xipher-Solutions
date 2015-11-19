#include <iostream>
#include <string>
#include <cstring>
#include <wchar.h>
#include <locale>
#include <codecvt>
#include <assert.h>
using namespace std;
	class InputHandler
	{ 
		public:
			//this method manages encryption: cannot be invoked directly because std::wstring cannot be managed by C#
			static wstring handleExpression(wstring expression, wstring key, bool encrypting);
			//this is the outward-facing method that writes to a buffer that C# can read from.
			static void getEncrypted(wstring expression, wstring key, bool isFile);
			static void getDecrypted(wstring encrypted, wstring key, bool isFile);
			static string wstringToString(wstring utf16);
			static string charToBinary(wchar_t toConvert);
		private:
			static wstring sanitizeInput(wstring expression); //just sets to lowercase and removes whitespaces
			static wstring* splitKey(wstring key);
			static int getKeyLength(wstring key);
			static long getFileSize(wstring path);
	};

	//exporting of function encryptExpression without decorative name
	//ISSUE: CANNOT USE METHODS WITH wstringS RETURNING: CRASHES APP << fixed with wstringBuilder and pointers
	extern "C" __declspec(dllexport) void getEncrypted(char *expression, char *key, bool isFile)
	{
		/*
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		wstring utf16expression = converter.from_bytes(expression);
		wstring utf16key = converter.from_bytes(key);
		*/
		const string utf8expression = expression;
		const string utf8key = key;
		wstring utf16expression(utf8expression.begin(), utf8expression.end());
		wstring utf16key(utf8key.begin(), utf8key.end());
		InputHandler::getEncrypted(utf16expression, utf16key, isFile);
		//InputHandler::getEncrypted(wstring(expression), wstring(key), isFile);
	}
	extern "C" __declspec(dllexport) void getDecrypted(const char *encrypted, const char *key, bool isFile)
	{
		const string utf8encrypted = encrypted;
		const string utf8key = key;
		wstring utf16encrypted(utf8encrypted.begin(), utf8encrypted.end());
		wstring utf16key(utf8key.begin(), utf8key.end());
		InputHandler::getDecrypted(utf16encrypted, utf16key, isFile);
		//InputHandler::getDecrypted(utf16encrypted, utf16key, isFile);
	}

	//BELOW ARE TESTING METHODS
	string bar()
	{ //another test case for if i can invoke methods not explicitly exported
		return "b";
	}

	extern "C" __declspec(dllexport) int test(const wchar_t* s)
	{ //test method for DLL export: Realized issues with wstrings here
		return bar()[0] * s[0];
	}
	/*
	extern "C" __declspec(dllexport) void wstringtest(const wchar_t* s, wchar_t* buffer, int bufferLength)
	{
		for (int i = 0; i < sizeof(s); i++)
		{
			if (bufferLength <= i)
				break;
			buffer[i] = s[i];
		}
	}
	*/