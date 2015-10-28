/*
 * ModObfuscate.cpp
 *
 *  Created on: Oct 22, 2015
 *      Author: ikrukov
 */
#include "ModObfuscate.h"
#include <string>
#include <iostream>
#include <cstring>
#include <stdlib.h>
using namespace std;
class ModObfuscate
{
public:
	static string interpretInput (string, std::string);
//private:
	//TODO C++ more
	static string skipHop (string);
	static string reverse (string);//best with expressions in binary
	static string caesar (string, int);
	static string transposition (string, int, int);
};
	//fus:sh|rev|crc=10|trans=3x3
	//flags in a cipher will be passed to doFlag for interpretation (they will split it
	//into methods to run and any additional arguments (see prototype for example))
	string ModObfuscate::interpretInput(string expression, string flag)
	{
		string encrypted = "";
		string option = "";
		string parameters = "";
		if(flag.find("=") == std::string::npos) //if there is no equal sign
		{
			option = flag;
		}
		else
		{//substrings in C++ are weird: (START_INDEX, LENGTH) are the parameters for substring.
			option = flag.substr(0, flag.find("=") - 1);
			parameters = flag.substr(flag.find("=") + 1);
		}
		switch(option)
		{ //these are all of the poorly acronymed flags: very much subject to change (especially when I begin combining ciphers more)
		case "skh": encrypted = skipHop(expression); break;
		case "rev": encrypted = reverse(expression); break;
		case "crc":
			std::stringstream convert(parameters);
			int shift; convert >> shift; //convert string to int
			encrypted = caesar(expression, shift);
			break;
		case "trn":
			std::stringstream convert(parameters.substr(0, parameters.find("*")));
			//filters to * delimeter (signifies an x by y array or x*y)
			int x; convert >> x;
			convert(parameters.substr(parameters.find("*") + 1));
			int y; convert >> y;
			encrypted = transposition(expression, x, y);
			break;
		}
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
		for(string::size_type i = 1; i < expression.length(); i+=2)
		{
			ans.push_back(expression[i]);
			ans.push_back(expression[i - 1]);
			//I used to get random symbols instead of scrambling:
			//ÜÑÜ“‰Ü“??”ÙØç is an example of "this is a test"
			//push_back in std::string appends characters to the ends of strings
		}
		if(expression.length() % 2 == 1)
			ans.push_back(expression[expression.length() - 1]);
		//fix for odd length expressions (for loop breaks before reaching last char)
		return ans;
	}
	string ModObfuscate::reverse(string expression)
	{
		string ans = "";
		//for loop originally had string::size_type iteration, but size can't decrement negative
		for(int i = expression.length() - 1; i >= 0; i--)
			ans.push_back(expression[i]);
		return ans;
	}

	string ModObfuscate::caesar(string expression, int modifier)
	{ //shifts the values of each character by modifier
		string ans = "";
		for(string::size_type i = 0; i < expression.length(); i++)
		{
			ans += (expression[i] + modifier);
		}
		return ans;
	}

	string ModObfuscate::transposition(string expression, int xSize, int ySize)
	{ //loads string into a matrix and returns an obfuscated string
		while(xSize * ySize < expression.length()) //While I need to adjust the size of the array to fit in data...
		{
			xSize++; ySize++;
		}
		char transposed[ySize][xSize];
		string::size_type i = 0; //index of string
		unsigned int charAverage = 0; //basis for salt character generation (if string isn't long enough for array)
		for(i = 0; i < expression.length(); i++)
			charAverage += (int)expression[i];
		charAverage /= expression.length();
		i = 0;
		for(string::size_type j = 0; j < sizeof(transposed) / sizeof(transposed[0]); j++) //y dim
		{ //have to do size / size because sizeof of a 2d array returns all possible indices (4 by 4 matrix returns 16)
			for(string::size_type k = 0; k < sizeof(transposed[j]); k++, i++) //x dim
			{
				if(i < expression.length()) //length check
					transposed[j][k] = (char)expression[i];
				else if (i == expression.length()) //otherwise if JUST switched, add a delimiter
					transposed[j][k] = (char)3000; //TODO change this delimiter to make it harder to frequency analyze
				else //otherwise add salt characters
					transposed[j][k] = (char)rand() % 12 + charAverage - 6; //random number from charAverage - 6 to charAverage + 6
				//cout << transposed[j][k]; - debug line
			}
		}
		//cout << "\n"; - debugline
		//loaded. now to read it back into an answer
		string ans = "";
		for(string::size_type j = 0; j < sizeof(transposed[0]); j++) //y dim
		{
			for(string::size_type k = 0; k < sizeof(transposed) / sizeof(transposed[0]); k++) //x dim
			{ //read is flipped
				ans.push_back(transposed[k][j]);
			}
		}
		return ans;
	}
	int main()
		{
			string in = "";
			std::cout << "Enter an expression: ";
			std::getline(std::cin, in); //Runtime error?
			std::cout << ModObfuscate::skipHop(in) << "\n";
			std::cout << ModObfuscate::reverse(in) << "\n";
			std::cout << ModObfuscate::caesar(in, 1) << "\n";
			std::cout << ModObfuscate::transposition(in, 4, 4);
		}
