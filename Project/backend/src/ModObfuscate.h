/*
 * ModObfuscate.h
 *
 *  Created on: Oct 22, 2015
 *      Author: ikrukov
 */

#ifndef MODOBFUSCATE_H_
#define MODOBFUSCATE_H_
#include <string>
#include <iostream>
#include <cstring>
using namespace std;
	class ModObfuscate
	{
	public:
		static wstring interpretInput(wstring, string, bool);
		private:
		static wstring skipHop(wstring);
		static wstring reverse(wstring);//best with expressions in binary
		static wstring caesar(wstring, int);
		static wstring transposition(wstring, int, int, bool);
		static wstring everyOther(wstring, bool);
	};

	//exporting of function interpretInput without decorative name
	/*
	extern "C" __declspec(dllexport) wstring interpretInput(wstring expression, wstring flag)
	{
		return ModObfuscate::interpretInput(expression, flag);
	
	*/
#endif /* MODOBFUSCATE_H_ */
