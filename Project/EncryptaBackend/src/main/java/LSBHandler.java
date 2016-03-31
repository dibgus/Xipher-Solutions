/**
 * Created by ikrukov on 2/16/2016.
 * Handles least significant bit functions in order to make steganography have more consistent methods
 */
public class LSBHandler {

    public static byte getLSB(int b)
    {
        return (byte)Math.abs((b % 2));
    }

    public static byte[] writePadding(byte size, byte[] data, int startIndex, int increment)
    {
        for(int i = startIndex; i <= size; i += increment)
            data[i] = (byte)insertLSB((int)data[i], (byte)0);
        return data;
    }

    public static int insertLSB(int data, byte lsb)
    {
        return (getLSB(data) == lsb ? data : data ^ 1);
    }
}
