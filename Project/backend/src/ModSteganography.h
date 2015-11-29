#include <string>
using namespace std;
class ModSteganography
{
public:
	static wstring interpretInput(wstring expression, wstring flag, bool encrypting); //expression should be the path to the image if encrypting
private:
	static wstring hideInPixels(wstring expression, wstring sourceImage);
	static wstring hideInCosCurve(wstring expression, wstring souceImage); //TODO: research storage of data in JPEG cosine curves (and see if manipulation is possible in CImg.
	static wstring extractPixels(wstring path);
	static wstring extractCosCurve(wstring path);
};		