import java.util.ArrayList;

/**
 * Created by ikrukov on 12/11/2015.
 * The converter class is used primarily to convert data to a binary format (There are some methods that rely on this)
 */
class Converter {
    /**
     * A method geared towards converting integers to their binary equivalents for some functions such as XOR and LSB steganography
     * @param value the value to convert to binary
     * @return A binary string representing value
     */
    public static String intToBinaryString(int value)
    {
        String inBinary = "";
        int bit = InputHandler.UTF16MODE ? 15 : 7;
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
    private static int binaryStringToInt(String binaryString)
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
        int bits = InputHandler.UTF16MODE ? 16 : 8;
        for(int i = 0; (i + 1) * bits + 1 < binaryString.length(); i++)
        {
            evaluated += (char)binaryStringToInt(binaryString.substring(i * bits, (i + 1) * bits)); //takes 2 bytes and converts it to a char
        }
        return evaluated;
    }

    public static byte[] convertToPrimative(ArrayList<Byte> toConvert)
    {
        byte[] primative = new byte[toConvert.size()];
        for(int i = 0; i < toConvert.size(); i++)
            primative[i] = toConvert.get(i);
        return primative;
    }
    public static byte[] convertToPrimative(Byte[] toConvert)
    {
        byte[] primative = new byte[toConvert.length];
        for(int i = 0; i < toConvert.length; i++)
            primative[i] = toConvert[i];
        return primative;
    }

    public static byte[] binaryStringToByteArray(String binaryString)
    {
        ArrayList<Byte> data = new ArrayList<Byte>();
        String binarySegment = "";
        for(int i = 0; i < binaryString.length(); i++)
        {
            binarySegment += binaryString.charAt(i);
            if(binarySegment.length() % 8 == 0)
            {
                data.add((byte)binaryStringToInt(binarySegment));
                binarySegment = "";
            }
        }
        return convertToPrimative((Byte[])data.toArray());
    }
}
