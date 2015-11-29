#include <string>
#include <cmath>
#include <locale>
#include <codecvt>
using namespace std;
class Converter
{
public:
	static string wstringToString(wstring utf16);
	static string charToBinary(wchar_t toConvert);
};