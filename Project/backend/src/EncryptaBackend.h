#include <iostream>
#include <string>
#include <cstring>
#include <wchar.h>
using namespace std;
	class InputHandler
	{ 
		public:
			//this method manages encryption: cannot be invoked directly because std::wstring cannot be managed by C#
			static wstring handleExpression(wstring expression, string key, bool encrypting);
			//this is the outward-facing method that writes to a buffer that C# can read from.
			static void getEncrypted(const wchar_t *expression, const char *key, bool isFile);
			static void getDecrypted(const wchar_t *encrypted, const char *key, bool isFile);
		private:
			static string sanitizeInput(string expression); //just sets to lowercase and removes whitespaces
			static string* splitKey(string key);
			static int getKeyLength(string key);
			static long getFileSize(wstring path);
	};

	//exporting of function encryptExpression without decorative name
	//ISSUE: CANNOT USE METHODS WITH wstringS RETURNING: CRASHES APP << fixed with wstringBuilder and pointers
	extern "C" __declspec(dllexport) void getEncrypted(const wchar_t *expression, const char *key, bool isFile)
	{
		InputHandler::getEncrypted(expression, key, isFile);
	}
	extern "C" __declspec(dllexport) void getDecrypted(const wchar_t *encrypted, const char *key, bool isFile)
	{
		InputHandler::getDecrypted(encrypted, key, isFile);
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