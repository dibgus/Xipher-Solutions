#include <string>
using namespace std;
class ModSteganography
{
public:
	static string interpretInput(string expression, string flag, bool encrypting); //expression should be the path to the image if encrypting
private:
	static string hideInPixels(string expression, string sourceImage, short inBits); //inBits signifies the amount of least significant bits to store data in (i.e 1 = hard to notice; 8 = random noise)
	static string hideInCosCurve(string expression, string souceImage); //TODO: research storage of data in JPEG cosine curves (and see if manipulation is possible in CImg.
	static string extractPixels(string path, short inBits);
	static string extractCosCurve(string path);
};