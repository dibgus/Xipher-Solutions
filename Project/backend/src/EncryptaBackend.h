#include <iostream>
#include <string>
#include <cstring>
using namespace std;
	class InputHandler
	{ 
		public:
			//this method manages encryption: cannot be invoked directly because std::string cannot be managed by C#
			static string handleExpression(string expression, string key, bool encrypting);
			//this is the outward-facing method that writes to a buffer that C# can read from.
			static void getEncrypted(const char *expression, const char *key, char *returnBuffer, long bufferlen);
			static void getDecrypted(const char *encrypted, const char *key, char *returnBuffer, long bufferlen);
		private:
			static string sanitizeInput(string expression); //just sets to lowercase and removes whitespaces
			static string* splitKey(string key);
			static int getKeyLength(string key);
	};

	//exporting of function encryptExpression without decorative name
	//ISSUE: CANNOT USE METHODS WITH STRINGS RETURNING: CRASHES APP << fixed with StringBuilder and pointers
	extern "C" __declspec(dllexport) void getEncrypted(const char *expression, const char *key, char *returnBuffer, long bufferlen)
	{
		InputHandler::getEncrypted(expression, key, returnBuffer, bufferlen);
	}
	extern "C" __declspec(dllexport) void getDecrypted(const char *encrypted, const char *key, char *returnBuffer, long bufferlen)
	{
		InputHandler::getDecrypted(encrypted, key, returnBuffer, bufferlen);
	}

	//BELOW ARE TESTING METHODS
	string bar()
	{ //another test case for if i can invoke methods not explicitly exported
		return "b";
	}

	extern "C" __declspec(dllexport) int test(const char* s)
	{ //test method for DLL export: Realized issues with strings here
		return bar()[0] * s[0];
	}
	/*
	extern "C" __declspec(dllexport) void stringtest(const char* s, char* buffer, int bufferLength)
	{
		for (int i = 0; i < sizeof(s); i++)
		{
			if (bufferLength <= i)
				break;
			buffer[i] = s[i];
		}
	}
	*/