/**
 * Created by ikrukov on 12/5/2015.
 * The module for Obfuscation
 * Obfuscation is the process of scrambling data to make it harder to read
 * It is not as strong as encryption, but adds an extra layer of security.
 * Functions: rev|crc=#|evo|tnc=#*#|skh|xor=""
 */

public class ModObfuscate  {
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

    public static String xorCipher(String expression, String xorKey)
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

    public static String skipHop(String expression)
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

    public static String caesarCipher(String expression, int shift)
    {
        String evaluated = "";
        for(int i = 0; i < expression.length(); i++)
            evaluated += (char)(expression.charAt(i) + shift);
        return evaluated;
    }

    public static String reverseExpression(String expression)
    {
        String evaluated = "";
        for(int i = expression.length() - 1; i >= 0; i--)
            evaluated += expression.charAt(i);
        return evaluated;
    }

    public static String everyOther(String expression, boolean encrypting)
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

    public static String transpositionCipher(String expression, String parameters, boolean encrypting)
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

}
