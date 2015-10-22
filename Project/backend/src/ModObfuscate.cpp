/*
 * ModObfuscate.cpp
 *
 *  Created on: Oct 22, 2015
 *      Author: ikrukov
 */

#include "ModObfuscate.h"
#include <string>
using namespace std;

class ModObfuscate
{
public:
	static std::string doFlag (std::string, std::string);
private:
	static String skipHop (string);
	static string caesar (string, int);
	static string transposition (string, int, int);

};

	//flags in a cipher will be passed to doFlag for interpretation (they will split it
	//into methods to run and any additional arguments (see prototype for example))
	static string ModObfuscate::doFlag(string expression, string flag)
	{

	}
	static string ModObfuscate::skipHop(string expression)
	{
		string ans = "";
		for(string::size_type i = 1; i < expression.length(); i += 2)
			ans += ans[i] + ans[i - 1];
		return ans;
	}

	static string ModObfuscate::caesar(string expression, int modifier)
	{
		char letters[] = expression;
		string ans = "";
		for(int i = 0; i < sizeof(letters); i++)
		{
			ans += (letters[i] + modifier);
		}
		return ans;
	}

	int main()
		{
			string in;
			std::cout << "Enter an expression: ";
			std::cin >> in;
			std::cout << ModObfuscate::skipHop(in);
			std::cout << ModObfuscate::caesar(in, 1);
		}

