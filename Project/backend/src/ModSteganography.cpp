
#include <string>
#include "ModSteganography.h"
#include <cstdlib>
#include <stdlib.h>
 //image manipulation library
using namespace std;
wstring ModSteganography::interpretInput(wstring expression, wstring flag, bool encrypting)
{
	wstring ans = expression;
	if (flag == L"pix")
	{
		wstring outFile = expression.substr(0, expression.find(L".")) + L"steg" + expression.substr(expression.find(L".")); //outputs to image file with "steg" attached on
		//TODO: make user pass the output file
		wstring bits = flag.substr(flag.find(L"=") + 1, flag.length());
		ans = encrypting ? hideInPixels(expression, outFile, atoi((char*)bits.c_str())) : extractPixels(expression, atoi((char*)bits.c_str()));
	}
	else if (flag == L"cos")
	{

	}
	return ans;
}

wstring ModSteganography::hideInCosCurve(wstring expression, wstring souceImage)
{
	return L"";
}

wstring ModSteganography::hideInPixels(wstring expression, wstring sourceImage, short inBits)
{	//TODO: implement more complex versions of this method that deal with different start index. increments, special keys...
	
	return L"";
}

wstring ModSteganography::extractPixels(wstring path, short inBits)
{
	return L"";
}

wstring ModSteganography::extractCosCurve(wstring path)
{
	return L"";
}
