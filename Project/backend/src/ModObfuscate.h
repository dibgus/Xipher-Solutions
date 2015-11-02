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
		static string interpretInput(string, string, bool);
		private:
		static string skipHop(string);
		static string reverse(string);//best with expressions in binary
		static string caesar(string, int);
		static string transposition(string, int, int, bool);
		static string everyOther(string, bool);
	};

	//exporting of function interpretInput without decorative name
	/*
	extern "C" __declspec(dllexport) string interpretInput(string expression, string flag)
	{
		return ModObfuscate::interpretInput(expression, flag);
	
	*/
#endif /* MODOBFUSCATE_H_ */
