
#include "ModObfuscate.h"
#include <string>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <stdlib.h>
#include <wchar.h>
using namespace std;

	//obfus:sh|obfus:rev|crc=10|trn=3*3
	//flags in a cipher will be passed to doFlag for interpretation (they will split it
	//into methods to run and any additional arguments (see prototype for example))
	wstring ModObfuscate::interpretInput(wstring expression, wstring flag, bool encrypting)
	{	
		wstring encrypted = expression;
		wstring option = L"";
		wstring parameters = L"";
		if (flag.find(L"=") == std::wstring::npos) //if there is no equal sign
		{
			option = flag;
		}
		else
		{
			option = flag.substr(0, flag.find(L"="));
			parameters = flag.substr(flag.find(L"=") + 1);
		}
		//these are all of the poorly acronymed flags: very much subject to change (especially when I begin combining ciphers more)
		if (option == L"skh")
			encrypted = skipHop(expression);
		else if (option == L"rev")
			encrypted = reverse(expression);
		else if (option == L"evo")
			encrypted = everyOther(expression, encrypting);
		else if (option == L"crc")
		{
			int shift = 1;
			if (parameters != L"")
				shift = atoi((char*)parameters.c_str());
			encrypted = caesar(expression, encrypting ? shift : -shift);
		}
		else if (option == L"tnc")
		{
			//filters to * delimeter (signifies an x by y array or x*y)
			int x = 1; int y = 1;
			if (parameters != L"")
			{
				x = atoi((char*)parameters.substr(0, parameters.find(L"*")).c_str());
				y = atoi((char*)parameters.substr(parameters.find(L"*") + 1).c_str());
			}
			encrypted = transposition(expression, x, y, encrypting);
		}
		else
			std::wcout << "Option not found: " << option << "\n";
		return encrypted;
	}
	/*
	wstring ModObfuscate::skipHop(wstring expression)
	{
		wstring ans = "";
		for(wstring::size_type i = 1; i < expression.length(); i += 2)
		{
			ans = ans + expression[i] + expression[i-1];
		}
		if(expression.length() % 2 == 1)
			ans += (wchar_t)expression[expression.length() - 1];
		return ans;
	}
	Produces broken results; I wonder if I could use the output if reversible...
	*/
	wstring ModObfuscate::skipHop(wstring expression)
	{ //simple method that scrambles letters (nevermore to enevmrroe)
		wstring ans = L"";
		for (wstring::size_type i = 1; i < expression.length(); i += 2)
		{
			ans.push_back(expression[i]);
			ans.push_back(expression[i - 1]);
			//I used to get random symbols instead of scrambling:
			//ÜÑÜ“‰Ü“??”ÙØç is an example of "this is a test"
			//push_back in std::wstring appends wchar_tacters to the ends of wstrings
		}
		if (expression.length() % 2 == 1)
			ans.push_back(expression[expression.length() - 1]);
		//fix for odd length expressions (for loop breaks before reaching last wchar_t)
		return ans;
	}
	wstring ModObfuscate::reverse(wstring expression)
	{
		wstring ans = L"";
		//for loop originally had wstring::size_type iteration, but size can't decrement negative
		for (int i = expression.length() - 1; i >= 0; i--)
			ans.push_back(expression[i]);
		return ans;
	}

	wstring ModObfuscate::caesar(wstring expression, int modifier)
	{ //shifts the values of each wchar_tacter by modifier
		wstring ans = L"";
		for (wstring::size_type i = 0; i < expression.length(); i++)
		{
			ans += (expression[i] + modifier);
		}
		return ans;
	}

	wstring ModObfuscate::transposition(wstring expression, int xSize, int ySize, bool encrypting)
	{ //loads wstring into a matrix and returns an obfuscated wstring
		while (xSize * ySize < expression.length()) //While I need to adjust the size of the array to fit in data...
		{
			xSize++; ySize++;
		}
		//declare the array: C++ doesn't like non-constants when declaring arrays
		//I can't do wchar_t transposed[xSize][ySize];
		wchar_t** transposed = new wchar_t*[xSize];
		for (int i = 0; i < xSize; i++)
			transposed[i] = new wchar_t[ySize];
		wstring::size_type i = 0; //index of wstring
		unsigned int charAverage = 0; //basis for salt wchar_tacter generation (if wstring isn't long enough for array)
		for (i = 0; i < expression.length(); i++)
			charAverage += (int)expression[i];
		charAverage /= expression.length();
		i = 0;
		//sizeof pointers never works D:
		for (wstring::size_type j = 0; j < xSize; j++) //y dim
		{ //have to do size / size because sizeof of a 2d array returns all possible indices (4 by 4 matrix returns 16)
			for (wstring::size_type k = 0; k < ySize; k++, i++) //x dim
			{
				if (i < expression.length()) //length check
					transposed[j][k] = (wchar_t)expression[i];
				else if (i == expression.length()) //otherwise if JUST switched, add a delimiter
					transposed[j][k] = (wchar_t)3000; //TODO change this delimiter to make it harder to frequency analyze
				else //otherwise add salt wchar_tacters
					transposed[j][k] = (wchar_t)rand() % 12 + charAverage - 6; //random number from wchar_tAverage - 6 to wchar_tAverage + 6
				//wcout << transposed[j][k]; - debug line
			}
		}
		//wcout << "\n"; - debugline
		//loaded. now to read it back into an 
		wstring ans = L"";
		for (wstring::size_type j = 0; j < ySize; j++) //y dim
		{
			for (wstring::size_type k = 0; k < xSize; k++) //x dim
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

	wstring ModObfuscate::everyOther(wstring expression, bool encrypting)
	{
		wstring ans = L"";
		if (encrypting)
		{
			for (wstring::size_type i = 0; i < expression.length(); i += 2)
				ans.push_back(expression[i]);
			for (wstring::size_type i = 1; i < expression.length(); i += 2)
				ans.push_back(expression[i]);
		}
		else
		{
			for (wstring::size_type i = 0; i < expression.length() / 2; i++)
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
		wstring in = "";
		std::wcout << "Enter an expression: ";
		std::getline(std::cin, in);
		std::wcout << ModObfuscate::interpretInput(in, "skh") << "\n";
		std::wcout << ModObfuscate::interpretInput(in, "rev") << "\n";
		std::wcout << ModObfuscate::interpretInput(in, "crc=1") << "\n";
		std::wcout << ModObfuscate::interpretInput(in, "trn=4*4") << "\n";
		std::wcout << "Enter a key: ";
		wstring key = "";
		std::getline(std::cin, key);
		std::wcout << ModObfuscate::interpretInput(in, key);
	}
	*/
