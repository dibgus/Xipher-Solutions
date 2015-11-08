
#include "CImg.h"
#include <string>
#include "ModSteganography.h"
#include <cstdlib>
#include <stdlib.h>
using namespace std;
using namespace cimg_library;
string ModSteganography::interpretInput(string expression, string flag, bool encrypting)
{
	string ans = expression;
	if (flag == "pix")
	{
		string outFile = expression.substr(0, expression.find(".")) + "steg" + expression.substr(expression.find(".")); //outputs to image file with "steg" attached on
		//TODO: make user pass the output file
		string bits = flag.substr(flag.find("=") + 1, flag.length());
		ans = encrypting ? hideInPixels(expression, outFile, atoi(bits.c_str())) : extractPixels(expression, atoi(bits.c_str()));
	}
	else if (flag == "cos")
	{

	}
	return ans;
}

string ModSteganography::hideInCosCurve(string expression, string souceImage)
{
	return "";
}

string ModSteganography::hideInPixels(string expression, string sourceImage, short inBits)
{	
	CImg<unsigned char> storage(sourceImage.c_str());
	cimg_forXY(storage, x, y)
	{
		storage(x, y);
	}
	return "";
}

string ModSteganography::extractPixels(string path, short inBits)
{
	return "";
}

string ModSteganography::extractCosCurve(string path)
{
	return "";
}
