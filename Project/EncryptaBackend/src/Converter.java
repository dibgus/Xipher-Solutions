/**
 * Created by ikrukov on 12/11/2015.
 * The converter class is used primarily to convert data to a binary format (There are some methods that rely on this)
 */
public class Converter {
    /**
     * A method geared towards converting integers to their binary equivalents for some functions such as XOR and LSB steganography
     * @param value the value to convert to binary
     * @return A binary string representing value
     */
    public static String intToBinaryString(int value)
    {
        String inBinary = "";
        int bit = 15; //16 bits for UTF-16 related string stuff
        while (bit >= 0)
        {
            if (Math.pow(2, bit) < value)
            {
                value -= Math.pow(2, bit);
                inBinary += "1";
            }
            else if (Math.pow(2, bit) == value)
            {
                inBinary += "1";
                for (int i = 0; i < bit - 1; i++)
                    inBinary += "0";
                break;
            }
            else inBinary += "0";
            bit--;
        }
        if(value % 2 == 0) inBinary += "0"; //odd number fix
        return inBinary;
    }

    /**
     * A method geared towards converting binary strings back into their integer representations for functions such as LSB steganography and xor obfuscation
     * @param binaryString A string which represents a binary sequence
     * @return The integer representation of the binary string
     */
    public static int binaryStringToInt(String binaryString)
    {
        int value = 0;
        for(int i = binaryString.length() - 1; i >= 0; i--)
        {
            if(!binaryString.contains("1")) return 0;
            if(binaryString.charAt(i) == '1')
                value += Math.pow(2, binaryString.length() - i - 1);
        }
        return value;
    }
    public static String binaryStringToString(String binaryString)
    {
        String evaluated = "";
        for(int i = 0; (i + 1) * 16 < binaryString.length(); i++)
        {
            evaluated += (char)binaryStringToInt(binaryString.substring(i * 16, (i + 1) * 16)); //takes 2 bytes and converts it to a char
        }
        return evaluated;
    }



}
