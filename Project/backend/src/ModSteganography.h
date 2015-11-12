#include <string>
using namespace std;
class ModSteganography
{
public:
	static wstring interpretInput(wstring expression, string flag, bool encrypting); //expression should be the path to the image if encrypting
private:
	static wstring hideInPixels(wstring expression, wstring sourceImage, short inBits); //inBits signifies the amount of least significant bits to store data in (i.e 1 = hard to notice; 8 = random noise)
	static wstring hideInCosCurve(wstring expression, wstring souceImage); //TODO: research storage of data in JPEG cosine curves (and see if manipulation is possible in CImg.
	static wstring extractPixels(wstring path, short inBits);
	static wstring extractCosCurve(wstring path);
};