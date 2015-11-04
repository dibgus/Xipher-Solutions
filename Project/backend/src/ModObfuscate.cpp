
#include "ModObfuscate.h"
#include <string>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <stdlib.h>
using namespace std;

	//obfus:sh|obfus:rev|crc=10|trn=3*3
	//flags in a cipher will be passed to doFlag for interpretation (they will split it
	//into methods to run and any additional arguments (see prototype for example))
	string ModObfuscate::interpretInput(string expression, string flag, bool encrypting)
	{
		string encrypted = "";
		string option = "";
		string parameters = "";
		if (flag.find("=") == std::string::npos) //if there is no equal sign
		{
			option = flag;
		}
		else
		{
			option = flag.substr(0, flag.find("="));
			parameters = flag.substr(flag.find("=") + 1);
		}
		//these are all of the poorly acronymed flags: very much subject to change (especially when I begin combining ciphers more)
		if (option == "skh")
			encrypted = skipHop(expression);
		else if (option == "rev")
			encrypted = reverse(expression);
		else if (option == "evo")
			encrypted = everyOther(expression, encrypting);
		else if (option == "crc")
		{
			int shift = 1;
			if (parameters != "")
				atoi(parameters.c_str());
			encrypted = caesar(expression, encrypting ? shift : -shift);
		}
		else if (option == "tnc")
		{
			//filters to * delimeter (signifies an x by y array or x*y)
			int x = 1; int y = 1;
			if (parameters != "")
			{
				x = atoi(parameters.substr(0, parameters.find("*")).c_str());
				y = atoi(parameters.substr(parameters.find("*") + 1).c_str());
			}
			encrypted = transposition(expression, x, y, encrypting);
		}
		else
			std::cout << "Option not found: " << option << "\n";
		return encrypted;
	}
	/*
	string ModObfuscate::skipHop(string expression)
	{
		string ans = "";
		for(string::size_type i = 1; i < expression.length(); i += 2)
		{
			ans = ans + expression[i] + expression[i-1];
		}
		if(expression.length() % 2 == 1)
			ans += (char)expression[expression.length() - 1];
		return ans;
	}
	Produces broken results; I wonder if I could use the output if reversible...
	*/
	string ModObfuscate::skipHop(string expression)
	{ //simple method that scrambles letters (nevermore to enevmrroe)
		string ans = "";
		for (string::size_type i = 1; i < expression.length(); i += 2)
		{
			ans.push_back(expression[i]);
			ans.push_back(expression[i - 1]);
			//I used to get random symbols instead of scrambling:
			//ÜÑÜ“‰Ü“??”ÙØç is an example of "this is a test"
			//push_back in std::string appends characters to the ends of strings
		}
		if (expression.length() % 2 == 1)
			ans.push_back(expression[expression.length() - 1]);
		//fix for odd length expressions (for loop breaks before reaching last char)
		return ans;
	}
	string ModObfuscate::reverse(string expression)
	{
		string ans = "";
		//for loop originally had string::size_type iteration, but size can't decrement negative
		for (int i = expression.length() - 1; i >= 0; i--)
			ans.push_back(expression[i]);
		return ans;
	}

	string ModObfuscate::caesar(string expression, int modifier)
	{ //shifts the values of each character by modifier
		string ans = "";
		for (string::size_type i = 0; i < expression.length(); i++)
		{
			ans += (expression[i] + modifier);
		}
		return ans;
	}

	string ModObfuscate::transposition(string expression, int xSize, int ySize, bool encrypting)
	{ //loads string into a matrix and returns an obfuscated string
		while (xSize * ySize < expression.length()) //While I need to adjust the size of the array to fit in data...
		{
			xSize++; ySize++;
		}
		//declare the array: C++ doesn't like non-constants when declaring arrays
		//I can't do char transposed[xSize][ySize];
		char** transposed = new char*[xSize];
		for (int i = 0; i < xSize; i++)
			transposed[i] = new char[ySize];
		string::size_type i = 0; //index of string
		unsigned int charAverage = 0; //basis for salt character generation (if string isn't long enough for array)
		for (i = 0; i < expression.length(); i++)
			charAverage += (int)expression[i];
		charAverage /= expression.length();
		i = 0;
		//sizeof pointers never works D:
		for (string::size_type j = 0; j < xSize; j++) //y dim
		{ //have to do size / size because sizeof of a 2d array returns all possible indices (4 by 4 matrix returns 16)
			for (string::size_type k = 0; k < ySize; k++, i++) //x dim
			{
				if (i < expression.length()) //length check
					transposed[j][k] = (char)expression[i];
				else if (i == expression.length()) //otherwise if JUST switched, add a delimiter
					transposed[j][k] = (char)3000; //TODO change this delimiter to make it harder to frequency analyze
				else //otherwise add salt characters
					transposed[j][k] = (char)rand() % 12 + charAverage - 6; //random number from charAverage - 6 to charAverage + 6
				//cout << transposed[j][k]; - debug line
			}
		}
		//cout << "\n"; - debugline
		//loaded. now to read it back into an 
		string ans = "";
		for (string::size_type j = 0; j < ySize; j++) //y dim
		{
			for (string::size_type k = 0; k < xSize; k++) //x dim
			{ //read is flipped
				ans.push_back(transposed[k][j]);
			}
		}
		//now I have to manually deconstruct the array
		for (int i = 0; i < xSize; i++)
			delete[] transposed[i];
		delete[] transposed;
		return ans;
	}

	string ModObfuscate::everyOther(string expression, bool encrypting)
	{
		string ans = "";
		if (encrypting)
		{
			for (string::size_type i = 0; i < expression.length(); i += 2)
				ans.push_back(expression[i]);
			for (string::size_type i = 1; i < expression.length(); i += 2)
				ans.push_back(expression[i]);
		}
		else
		{
			for (string::size_type i = 0; i < expression.length() / 2; i++)
			{
				ans.push_back(expression[i]);
				ans.push_back(expression[i + expression.length() / 2]);
			}
		}
		return ans;
	}
	/*
	int main()
	{
		string in = "";
		std::cout << "Enter an expression: ";
		std::getline(std::cin, in);
		std::cout << ModObfuscate::interpretInput(in, "skh") << "\n";
		std::cout << ModObfuscate::interpretInput(in, "rev") << "\n";
		std::cout << ModObfuscate::interpretInput(in, "crc=1") << "\n";
		std::cout << ModObfuscate::interpretInput(in, "trn=4*4") << "\n";
		std::cout << "Enter a key: ";
		string key = "";
		std::getline(std::cin, key);
		std::cout << ModObfuscate::interpretInput(in, key);
	}
	*/
