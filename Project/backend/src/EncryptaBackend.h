#include <iostream>
#include <string>
#include <cstring>
using namespace std;
class InputHandler
{
public:
	static string encryptExpression(string expression, string key);
//private:
	static string* splitKey(string key);
};
