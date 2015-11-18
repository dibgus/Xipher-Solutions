
#include <string>
#include "ModSteganography.h"
#include "EncryptaBackend.cpp"
#include <cstdlib>
#include <stdlib.h>
#include <opencv2/highgui/highgui.hpp>	 //image manipulation library: in order to compile, you have to install this
using namespace std;
using namespace cv;
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
	Mat storage = cv::imread(InputHandler::wstringToString(sourceImage)); //read in the source image
	int imagePos = 0;
	for (int i = 0; i < expression.length(); i++)
	{

		char toStore = expression[i];
	}
	cv::imwrite(InputHandler::wstringToString(sourceImage) + ".e", storage);
	return L"Expression has been stored in " + sourceImage;
}

wstring ModSteganography::extractPixels(wstring path, short inBits)
{
	return L"";
}

wstring ModSteganography::extractCosCurve(wstring path)
{
	return L"";
}
