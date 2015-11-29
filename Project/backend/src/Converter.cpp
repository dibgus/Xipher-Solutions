#include "Converter.h"
#include <string>
#include <cmath>
#include <locale>
#include <codecvt>
using namespace std;
string Converter::wstringToString(wstring utf16)
{
	typedef std::codecvt_utf8<wchar_t> convert_type;
	std::wstring_convert<convert_type, wchar_t> converter;
	std::string converted = converter.to_bytes(utf16);
	return converted;
}
string Converter::charToBinary(wchar_t toConvert)
{
	int charVal = (int)toConvert;
	string ans = "";
	int bit = 15;
	while (bit >= 0)
	{
		if (pow(2, bit) < charVal)
		{
			charVal -= pow(2, bit);
			ans.push_back('1');
		}
		else if (pow(2, bit) == charVal)
		{
			ans.push_back('1');
			for (int i = 0; i < bit - 1; i++)
				ans.push_back('0');
			break;
		}
		else ans.push_back('0');
		bit--;
	}

	return ans;
}