#include <iostream>
#include <string>
#include <cstring>
using namespace std;
	class InputHandler
	{ 
		public:
			//this method manages encryption: cannot be invoked directly because std::string cannot be managed by C#
			static string encryptExpression(string expression, string key);
			//this is the outward-facing method that writes to a buffer that C# can read from.
			static void getEncrypted(const char *expression, const char *key, char *returnBuffer, int bufferLength);
		private:
			static string* splitKey(string key);
	};

	string bar()
	{ //another test case for if i can invoke methods not explicitly exported
		return "b";
	}

	//exporting of function encryptExpression without decorative name
	//ISSUE: CANNOT USE METHODS WITH STRINGS RETURNING: CRASHES APP
	extern "C" __declspec(dllexport) void getEncrypted(const char *expression, const char *key, char *returnBuffer, int bufferLength)
	{
		InputHandler::getEncrypted(expression, key, returnBuffer, bufferLength);
	}
	extern "C" __declspec(dllexport) int test(const char* s)
	{ //test method for DLL export: Realized issues with strings here
		return bar()[0] * s[0];
	}
	extern "C" __declspec(dllexport) void stringtest(const char* s, char* buffer, int bufferLength)
	{
		for (int i = 0; i < sizeof(s); i++)
		{
			if (bufferLength <= i)
				break;
			buffer[i] = s[i];
		}
	}