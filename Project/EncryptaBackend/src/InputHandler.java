/**
 * Created by ikrukov on 12/5/2015.
 * The main entry point for all input and output operations of Encrypta
 */
import java.io.BufferedOutputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.FileSystems;
import java.util.ArrayList;

abstract class InputHandler
{
    /**
     * This main method is to satisfy IKVM's .net executable generation.
     * I initially tried to export my code to a .net DLL, but I then realized that I would have had
     * to go through a complex process of registering the DLL as a COM interface and use strange compiler annotations everywhere
     * @param args See the passEncryptedData method's parameters for each variable stored in the string array
     */
    public static void main(String[] args)
    {
        //System.out.println("DEBUG: " + Arrays.toString(args));
        passEncryptedData(args[0], args[1], args[2].equals("1"), args[3].equals("1"));
    }

/**
     * The main method that is called by my frontend code to get the encrypted expression
     * This method writes to a file called "return" which my frontend code could then read.
     * @param expression The expression to encrypt
     * @param key A list of operations to perform on the data
     * @param isEncrypting Whether or not the data is being encrypted or decrypted
     * @param isFile Whether or not expression is a file path
     */
    private static void passEncryptedData(String expression, String key, boolean isEncrypting, boolean isFile)
    {
       // try {
            /*
            BufferedOutputStream returnFile = new BufferedOutputStream(new FileOutputStream("return"));
            if(isFile)
            returnFile.write(createEvaluatedFile(expression, key, isEncrypting));
            else
            returnFile.write(getEvaluatedExpression(expression, key, isEncrypting));
            returnFile.close();
            */
            if(isFile)
                System.out.println(createEvaluatedFile(expression, key, isEncrypting));
            else
                System.out.println(getEvaluatedExpression(expression, key, isEncrypting));
        //} catch (IOException e) {
           // e.printStackTrace();
        //}
    }

    /**
     * @param expression The string to manipulate
     * @param key A list of operations to perform on the expression
     * @param isEncrypting Whether or not the expression is being encrypted
     */
    public static String getEvaluatedExpression(String expression, String key,  boolean isEncrypting)
    {
        String[] functions = handleKey(sanitizeKey(key), "\\|");
        String encryptedExpression = expression;
        String module = "";
        for (int i = isEncrypting ? 0 : functions.length - 1; i < functions.length && isEncrypting || i >= 0 && !isEncrypting;)
        {
            //set the module if another one is specified, otherwise use the previously defined module in the key
            String function;
            if(functions[i].contains(":")) {
                module = functions[i].substring(0, functions[i].indexOf(":"));
                function = functions[i].substring(functions[i].indexOf(":") + 1);
            }
            else if(isEncrypting)
                function = functions[i];
            else
            {
                int moduleIndex = 0;
                for(int j = 0; j < i; j++)
                    if(functions[i].contains(":"))
                        moduleIndex = j;
                module = functions[moduleIndex].substring(0, functions[moduleIndex].indexOf(":"));
                function = functions[i];
            }
            if(module.equals("") && !isEncrypting)
            { //find a previously referenced module if going backwards
                for (int j = i - 1; j >= 0; j--)
                {
                    if (functions[j].contains(":"))
                        module = functions[j].substring(0, functions[j].indexOf(":"));
                }
            }
            switch (module) {
                case ("obfu"):
                    encryptedExpression = ModObfuscate.performOperation(encryptedExpression, function, isEncrypting);
                    break;
                case ("steg"):
                    try {
                        encryptedExpression = ModSteganography.performOperation(encryptedExpression, function, isEncrypting);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    break;
                case ("encr"):
                    encryptedExpression = ModEncryption.performOperation(encryptedExpression, function, isEncrypting);
                    break;
                case ("other"):
                    encryptedExpression = ModOther.performOperation(encryptedExpression, function, isEncrypting);
                    break;
                default:
                    System.err.println("Unknown module: " + module);
                    break;
            }
            if(isEncrypting)
                i++;
            else
                i--;
        }
        return encryptedExpression;
    }

    public static byte[] getEvaluatedExpression(byte[] fileData, String filePath, String key,  boolean isEncrypting)
    {
        String[] functions = handleKey(sanitizeKey(key), "\\|");
        ArrayList<Byte> encryptedData = new ArrayList<Byte>();
        for(int i = 0; i < fileData.length; i++)
            encryptedData.add(fileData[i]);
        String module = "";
        for (int i = isEncrypting ? 0 : functions.length - 1; i < functions.length && isEncrypting || i >= 0 && !isEncrypting;)
        {
            //set the module if another one is specified, otherwise use the previously defined module in the key
            String function;
            if(functions[i].contains(":")) {
                module = functions[i].substring(0, functions[i].indexOf(":"));
                function = functions[i].substring(functions[i].indexOf(":") + 1);
            }
            else
                function = functions[i];
            if(module.equals("") && !isEncrypting)
            { //find a previously referenced module if going backwards
                for (int j = i - 1; j >= 0; j--)
                {
                    if (functions[j].contains(":"))
                        module = functions[j].substring(0, functions[j].indexOf(":"));
                }
            }

            byte[] temp = null;
            switch (module) {
                case ("obfu"):
                    temp = ModObfuscate.performOperation(Converter.convertToPrimative(encryptedData), function, isEncrypting);
                    encryptedData.clear();
                    for(int j = 0; j < temp.length; j++) //load return array into the arraylist
                           encryptedData.add(temp[j]);
                    break;
                case ("steg"):
                    try {
                        temp = ModSteganography.performOperation(Converter.convertToPrimative(encryptedData), function, isEncrypting);
                        encryptedData.clear();
                        for(int j = 0; j < temp.length; j++) //load return array into the arraylist
                            encryptedData.add(temp[j]);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    break;
                case ("encr"):
                    temp = ModEncryption.performOperation(Converter.convertToPrimative(encryptedData), function, isEncrypting);
                    encryptedData.clear();
                    for(int j = 0; j < temp.length; j++) //load return array into the arraylist
                        encryptedData.add(temp[j]);
                    break;
                case ("other"):
                    temp = ModOther.performOperation(Converter.convertToPrimative(encryptedData), function, isEncrypting);
                    encryptedData.clear();
                    for(int j = 0; j < temp.length; j++) //load return array into the arraylist
                        encryptedData.add(temp[j]);
                    break;
                default:
                    System.err.println("Unknown module: " + module);
                    break;
            }
            if(isEncrypting)
                i++;
            else
                i--;
        }
        return Converter.convertToPrimative(encryptedData);
    }



    public static String createEvaluatedFile(String filePath, String key , boolean isEncrypting)
    {
        key = sanitizeKey(key);
        String returnFilePath = filePath + ".crypt";
        try
        {
            byte[] data = Files.readAllBytes(FileSystems.getDefault().getPath("", filePath));
            byte[] newData = getEvaluatedExpression(data, filePath, key, isEncrypting); //evaluate the file data

            BufferedOutputStream evaluatedFile = new BufferedOutputStream(new FileOutputStream(returnFilePath)); //write to a .crypt file
            evaluatedFile.write(newData);
            evaluatedFile.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return returnFilePath;
    }


    public static String[] handleKey(String key, String delimeter)
    {
        return key.split(delimeter);
    }

    /**
     * @param key An expression to sanitize(avoiding anything in quotes, change to lower case and trim
     * @return A key that has been sanitized
     */
    private static String sanitizeKey(String key)
    {
        String sanitized = key;
        for(int i = 0; i < key.length(); i++)
        {
            if(sanitized.charAt(i) == '"') //avoid anything in quotes within the key
                i = sanitized.indexOf('"', i + 1);
            if(sanitized.charAt(i) == ' ')  //truncate any visible spaces
                sanitized = sanitized.substring(0, i) + sanitized.substring(i + 1, sanitized.length());
            sanitized = sanitized.substring(0, i) + sanitized.substring(i, i + 1).toLowerCase() + sanitized.substring(i + 1, sanitized.length());
            //turn characters not in quotes to lower case.
        }
        return sanitized;
    }
}
