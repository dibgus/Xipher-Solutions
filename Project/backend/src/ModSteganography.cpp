#include <string>
#include "Converter.h"
#include "ModSteganography.h"
#include <cstdlib>
#include <stdlib.h>
#include <opencv2/highgui/highgui.hpp>	 //image manipulation library: in order to compile, you have to install this
#include <opencv2/core/core.hpp>
using namespace std;
using namespace cv;
wstring ModSteganography::interpretInput(wstring expression, wstring flag, bool encrypting)
{
	wstring ans = expression;
	wstring option = L"";
	if (flag.find(L"=") == std::wstring::npos) //if there is no equal sign to specify parameters
		option = flag;
	else
		option = flag.substr(0, flag.find(L"="));

	if (option == L"pix")
	{
		wstring outFile = flag.substr(flag.find(L"=") + 1, flag.length());
		ans = encrypting ? hideInPixels(expression, outFile) : extractPixels(outFile); //extractPixels assumes that the user has specified a file path in passing expression
	}
	else if (option == L"cos")
	{

	}
	return ans;
}

wstring ModSteganography::hideInCosCurve(wstring expression, wstring sourceImage)
{
	return L"";
}

wstring ModSteganography::hideInPixels(wstring expression, wstring sourceImage)
{	//TODO: implement more complex versions of this method that deal with different start index. increments, special keys...
	Mat storage = cv::imread(Converter::wstringToString(sourceImage)); //read in the source image
	int imageX = 0, imageY = 0, component = 0; //imagex and y are coords, component: start by looking at blue;
													   //gets iterated every time a bit is written to the image
	for (int i = 0; i < expression.length(); i++)
	{
		string inBinary = Converter::charToBinary(expression[i]);
		for (int i = 0; i < inBinary.length(); i++, component++) // 0 b 1 g 2 r
		{
			if (component == 3)
			{
				component = 0;
				if (imageX > storage.rows)
				{
					imageX = 0;
					imageY++;
				}
				else imageX++;
				if (imageY > storage.cols)
					return L"ERROR: IMAGE IS NOT LARGE ENOUGH TO STORE DATA";
			}
			Vec3b bgr = storage.at <Vec3b>(imageY, imageX); //backwards from RGB
			int lsb = bgr[component] % 2; //least significant bit
			if (char(lsb + 48) != inBinary[i]) //converts one or zero to character representation of 1 or 0
			{
				if (lsb == 1)
					bgr[component] -= 1; //if the lsb has to be shifted to a zero, remove that bit
				else
					bgr[component] += 1; //if the lsb has to be shifted to a one, add that bit
			}
		}
	}
	//data is now loaded into the image, now to null terminate it with zeroes.
	for (int i = 0; i < 16; i++)
	{
		if (imageX > storage.rows)
		{
			imageX = 0;
			imageY++;
		}
		else imageX++;
		if (imageY > storage.cols)
			return L"ERROR: IMAGE IS NOT LARGE ENOUGH TO BE NULL-TERMINATED";
		Vec3b bgr = storage.at <Vec3b>(imageY, imageX);
		int lsb = bgr[component] % 2;
		if (char(lsb + 48) != '0')
			bgr[component] -= 1; //change to zero if not already
	}
	sourceImage = sourceImage.substr(0, sourceImage.find_last_of(L"\\") + 1) + L"encrypted_" + sourceImage.substr(sourceImage.find_last_of(L"\\") + 1, sourceImage.length());
	cv::imwrite((Converter::wstringToString(sourceImage)), storage); //write final image, temporary .e extension to prevent original image overwriting
	return L"Expression has been stored in " + sourceImage;
}

wstring ModSteganography::extractPixels(wstring path)
{
	bool test = false; if (test) return path;
	wstring result = L"";
	Mat stegImage = cv::imread(Converter::wstringToString(path));
	short component = 0;
	int imageX = 0, imageY = 0;
	while (true)
	{
		short nullTerm = 0; //checks how many sequential zeroes there are for the null terminating character
		int charValue = 0;
		for (int i = 0; i < 16; i++, component++)
		{//pow(2, 16 - i)
			if (component > 2)
			{
				if (imageX > stegImage.rows)
				{
					imageX = 0;
					imageY++;
				}
				else imageX++;
				if (imageY > stegImage.cols)
					return L"READ ERROR: Missing nullterm?";
			}
			Vec3b bgr = stegImage.at <Vec3b>(imageY, imageX);
			if (bgr[component] % 2 == 1)
				charValue += pow(2, 16 - i); //TODO: check if wchar is signed or unsigned (I could be interpreting this wrong if there is a sign bit)
		}
		if (nullTerm == 16) break; //break if null termed
		result.push_back((wchar_t)charValue);
	}
	return result;
}

wstring ModSteganography::extractCosCurve(wstring path)
{
	return L"";
}