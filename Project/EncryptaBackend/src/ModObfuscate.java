/**
 * Created by ikrukov on 12/5/2015.
 * The module for Obfuscation
 * Obfuscation is the process of scrambling data to make it harder to read
 * It is not as strong as encryption, but adds an extra layer of security.
 * Functions: rev|crc=#|evo|tnc=#*#|skh|xor=""
 */
//TODO: FIX Caesar cipher with bytes, transposition cipher?
import java.util.ArrayList;
class ModObfuscate  {
    public static String performOperation(String expression, String flag, boolean encrypting)
    {
        String encrypted = expression;
        String[] command = InputHandler.handleKey(flag, "="); //command[0] -> the command to be run; command[1] -> parameters
        switch(command[0])
        {
            case "rev":
                encrypted = reverseExpression(expression);
                break;
            case "crc":
                encrypted = caesarCipher(expression, encrypting ? Integer.parseInt(command[1]) : -1 * Integer.parseInt(command[1]));
                break;
            case "evo":
                encrypted = everyOther(expression, encrypting);
                break;
            case "tnc":
                encrypted = transpositionCipher(expression, command[1], encrypting);
                break;
            case "skh":
                encrypted = skipHop(expression);
                break;
            case "xor":
                encrypted = xorCipher(expression, command[1]);
                break;
            default:
                System.err.println("Could not find obfuscation function: " + command[0]);
                break;
        }
        return encrypted;
    }

    public static byte[] performOperation(byte[] fileData, String flag, boolean encrypting)
    {
        byte[] encrypted = fileData;
        String[] command = InputHandler.handleKey(flag, "="); //command[0] -> the command to be run; command[1] -> parameters
        switch(command[0])
        {
            case "rev":
                encrypted = reverseExpression(fileData);
                break;
            case "crc":
                encrypted = caesarCipher(fileData, encrypting ? Integer.parseInt(command[1]) : -1 * Integer.parseInt(command[1]));
                break;
            case "evo":
                encrypted = everyOther(fileData, encrypting);
                break;
            case "tnc":
                encrypted = transpositionCipher(fileData, command[1], encrypting);
                break;
            case "skh":
                encrypted = skipHop(fileData);
                break;
            case "xor":
                encrypted = xorCipher(fileData, command[1]);
                break;
            default:
                System.err.println("Could not find obfuscation function: " + command[0]);
                break;
        }
        return encrypted;
    }

    private static String xorCipher(String expression, String xorKey)
    {
        String binaryKey = "";
        for(int i = 0; i < xorKey.length(); i++)
            binaryKey += Converter.intToBinaryString(xorKey.charAt(i));
        String binaryExpression = "";
        for(int i = 0; i < expression.length(); i++)
            binaryExpression += Converter.intToBinaryString(expression.charAt(i));
        int keyIndex = 0; //the index the key will be reading, this loops through constantly throughout
        String evaluatedBinary = "";
        for(int i = 0; i < binaryExpression.length(); i++) {
            if (binaryExpression.charAt(i) == '1' && binaryKey.charAt(keyIndex) == '1')
                evaluatedBinary += '0';
            else if(binaryExpression.charAt(i) == '1' || binaryKey.charAt(keyIndex) == '1')
                evaluatedBinary += '1';
            else
                evaluatedBinary += '0';
            keyIndex++;
            if (keyIndex >= binaryKey.length())
                keyIndex = 0;
        }
        return Converter.binaryStringToString(evaluatedBinary);
    }

    private static String skipHop(String expression)
    {
        String evaluated = "";
        for(int i = 1; i < expression.length(); i+=2)
        {
            evaluated += expression.charAt(i) + "" + expression.charAt(i - 1);
        }
        if(expression.length() % 2 == 1) //if String is odd length
            evaluated += expression.charAt(expression.length() - 1);
        return evaluated;
    }

    private static String caesarCipher(String expression, int shift)
    {
        String evaluated = "";
        for(int i = 0; i < expression.length(); i++)
            evaluated += (char)(expression.charAt(i) + shift);
        return evaluated;
    }

    private static String reverseExpression(String expression)
    {
        String evaluated = "";
        for(int i = expression.length() - 1; i >= 0; i--)
            evaluated += expression.charAt(i);
        return evaluated;
    }

    private static String everyOther(String expression, boolean encrypting)
    {
        String evaluated = "";
        if (encrypting)
        {
            for(int i = 0; i < expression.length(); i += 2)
                evaluated += expression.charAt(i);
            for(int i = 1; i < expression.length(); i+= 2)
                evaluated += expression.charAt(i);
        }
        else
        {
            for (int i = 0; i < expression.length() / 2; i++)
            {
                if (expression.length() % 2 == 0)
                    evaluated += expression.charAt(i) + "" + expression.charAt(i + expression.length() / 2);
                else
                    evaluated += expression.charAt(i) + "" + expression.charAt(i + expression.length() / 2 + 1);
            }
            if(expression.length() % 2 == 1)
                evaluated += expression.charAt(expression.length() / 2); //fix for odd length expressions
        }
        return evaluated;
    }

    private static String transpositionCipher(String expression, String parameters, boolean encrypting)
    {
        String evaluated = "";
        int x = Integer.parseInt(parameters.split("\\*")[0]), y = Integer.parseInt(parameters.split("\\*")[1]);
        while(x * y < expression.length())
        { x++; y++; }
        long charAverage = 0; //the average will be used to salt the end of the string
        for(int i = 0; i < expression.length(); i++)
            charAverage += expression.charAt(i);
        charAverage /= expression.length();
        char[][] transposed = new char[x][y];
        int i = 0;
        readImage:
        for(int j= 0; j < x; j++) //j -> x, k -> y
        {
            for(int k = 0; k < y; k++, i++)
            {
                if(i < expression.length())
                {
                    transposed[j][k] = expression.charAt(i);
                }
                else if(i == expression.length() && encrypting)
                    transposed[j][k] = (char)3000; //TODO don't hardcode this
                else if(encrypting)
                    transposed[j][k] = (char)(Math.random() * 12 - 6 + charAverage); // +/- 6 values from charAverage
                else
                    break readImage;
            }
        }
        //now to read back
        for(int j = 0; j < y; j++)
            for(int k = 0; k < x; k++)
                evaluated += transposed[k][j];

        if(!encrypting && evaluated.indexOf((char)3000) != -1)
            evaluated = evaluated.substring(0, evaluated.indexOf((char)3000)); //TODO don't hardcode this
        return evaluated;
    }

    /* BYTE VERSIONS OF THE ABOVE METHODS FOR FILE MANIPULATION */

    private static byte[] xorCipher(byte[] fileData, String xorKey)
    {
        byte[] evaluated = new byte[fileData.length];
        int keyIndex = 0; //the index the key will be reading, this loops through constantly throughout
        for(int i = 0; i < fileData.length; i++) {
            evaluated[i] = (byte)(fileData[i] ^ (byte)xorKey.charAt(keyIndex)); //bitwise xor operator
            keyIndex++;
            if (keyIndex >= xorKey.length())
                keyIndex = 0;
        }
        return evaluated;
    }

    private static byte[] skipHop(byte[] fileData)
    {
        byte[] evaluated =  new byte[fileData.length];
        int index = 0;
        for(int i = 1; i < fileData.length; i+=2)
        {
            evaluated[index] = fileData[i];
            index++;
            evaluated[index] = fileData[i - 1];
            index++;
        }
        if(fileData.length % 2 == 1) //if bytearray is odd length
            evaluated[index] = fileData[fileData.length - 1];
        return evaluated;
    }

    private static byte[] caesarCipher(byte[] fileData, int shift)
    {
        shift %= Byte.MAX_VALUE;
        byte[] evaluated = new byte[fileData.length];
        int index = 0;
        for(int i = 0; i < fileData.length; i++, index++)
        {
            if(shift + fileData[i] > Byte.MAX_VALUE || shift + fileData[i] < Byte.MIN_VALUE)
                evaluated[index] = (byte)((fileData[i] + shift) % Byte.MAX_VALUE);
            else
            evaluated[index] = (byte)(fileData[i] + shift);
            //evaluated[index] = (byte)(fileData[i] << shift); lossy
        }
        return evaluated;
    }

    private static byte[] reverseExpression(byte[] fileData)
    {
        byte[] evaluated = new byte[fileData.length];
        int index = 0;
        for(int i = fileData.length - 1; i >= 0; i--, index++)
            evaluated[index] =  fileData[i];
        return evaluated;
    }

    private static byte[] everyOther(byte[] fileData, boolean encrypting)
    {
        byte[] evaluated = new byte[fileData.length];
        int index = 0;
        if (encrypting)
        {
            for(int i = 0; i < fileData.length; i += 2, index++)
                evaluated[index] += fileData[i];
            for(int i = 1; i < fileData.length; i+= 2, index++)
                evaluated[index] += fileData[i];
        }
        else
        {
            for (int i = 0; i < fileData.length / 2; i++, index+= 2)
            {
                if (fileData.length % 2 == 0) {
                    evaluated[index] = fileData[i];
                    evaluated[index + 1] = fileData[i + fileData.length / 2];
                }
                else
                {
                    evaluated[index] += fileData[i];
                    evaluated[index + 1] = fileData[i + fileData.length / 2 + 1];
                }
            }
            if(fileData.length % 2 == 1)
                evaluated[index] += fileData[fileData.length / 2]; //fix for odd lengthed data
        }
        return evaluated;
    }

    private static final int TRANSBUFFERSIZE = 8;
    private static byte[] transpositionCipher(byte[] fileData, String parameters, boolean encrypting)
    {
        ArrayList<Byte> evaluated = new ArrayList<Byte>();
        int x = Integer.parseInt(parameters.split("\\*")[0]), y = Integer.parseInt(parameters.split("\\*")[1]);
        while(x * y < fileData.length + TRANSBUFFERSIZE)
        { x++; y++; }
        byte[][] transposed = new byte[x][y];
        int i = 0;
        int bufferWritten = 0;
        readFile:
        for(int j= 0; j < x; j++) //j -> x, k -> y
        {
            for(int k = 0; k < y; k++, i++)
            {
                if(i < fileData.length)
                {
                    transposed[j][k] = fileData[i];
                }
                else if(i >= fileData.length && encrypting && bufferWritten < TRANSBUFFERSIZE)
                {
                    transposed[j][k] = 0;
                    bufferWritten++;
                }

                else if(encrypting)
                    transposed[j][k] = (byte)(Math.random() * 128);
                else
                    break readFile;
            }
        }
        //now to read back
        for(int j = 0; j < y; j++)
            for(int k = 0; k < x; k++)
                evaluated.add(transposed[k][j]);
        if(!encrypting) {
            //get index of the beginning of the null terminating buffer
            int nullcheck = 0;
            for(i = 0; i < evaluated.size() && nullcheck < TRANSBUFFERSIZE; i++)
            {
                nullcheck = evaluated.get(i) == 0 ? nullcheck + 1 : 0; // increments the null terminator check

            }
            evaluated = new ArrayList<>(evaluated.subList(0, i - TRANSBUFFERSIZE)); //get the list with the transposed removed
        }
        return Converter.convertToPrimative(evaluated);
    }


}
