/**
 * Created by ikrukov on 12/5/2015.
 * The main entry point for all input and output operations of Encrypta
 */
import java.io.*;

public abstract class InputHandler {
    /**
     * The main method that is called by my frontend code to get the encrypted expression
     * This method writes to a file called "return" which my frontend code could then read.
     * @param expression The expression to encrypt
     * @param key A list of operations to perform on the data
     * @param isEncrypting Whether or not the data is being encrypted or decrypted
     * @param isFile Whether or not expression is a file path
     */
    public static void passEncryptedData(String expression, String key, boolean isEncrypting, boolean isFile)
    {
        try {
            FileWriter returnFile = new FileWriter("return");
            if(isFile)
            returnFile.write(createEvaluatedFile(expression, key, isEncrypting));
            else
            returnFile.write(getEvaluatedExpression(expression, key, isEncrypting));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * @param expression The string to manipulate
     * @param key A list of operations to perform on the data
     * @param isEncrypting Whether or not the data is being encrypted
     */
    public static String getEvaluatedExpression(String expression, String key, boolean isEncrypting) {
        key = sanitizeKey(key);
        return evaluateData(expression, handleKey(key, "|"), isEncrypting);
    }

    public static String evaluateData(String data, String[] functions,  boolean isEncrypting)
    {
        String encryptedExpression = data;
        String module = "";
        for (int i = 0; i < functions.length; i++) {
            //set the module if another one is specified, otherwise use the previously defined module in the key
            String function;
            if(functions[i].contains(":")) {
                module = functions[i].substring(0, functions[i].indexOf(":"));
                function = functions[i].substring(functions[i].indexOf(":") + 1);
            }
            else
                function = functions[i];

            switch (module) {
                case ("obfu"):
                    encryptedExpression = ModObfuscate.performOperation(encryptedExpression, function, isEncrypting);
                    break;
                case ("steg"):
                    encryptedExpression = ModSteganography.performOperation(encryptedExpression, function, isEncrypting);
                    break;
                case ("encr"):
                    encryptedExpression = ModEncryption.performOperation(encryptedExpression, function, isEncrypting);
                    break;
                default:
                    System.out.println("ERROR IN MODULE SPECIFICATION: " + module);
                    break;
            }
        }
        return encryptedExpression;
    }


    public static String createEvaluatedFile(String filePath, String key , boolean isEncrypting)
    {
        key = sanitizeKey(key);
        String returnFilePath = filePath + ".crypt";
        String fileData = ""; //the raw file data that will be modified
        try {
            BufferedReader inputFile = new BufferedReader(new FileReader(filePath));
            while(inputFile.read() > 0)
            {
                fileData += inputFile.readLine();
            }
        } catch (Exception e) { //IOException or FileNotFound
            e.printStackTrace();
        }
        String newData = evaluateData(fileData, handleKey(key, "|"), isEncrypting); //evaluate the file data
        try {
            BufferedWriter evaluatedFile = new BufferedWriter(new FileWriter(returnFilePath)); //write to a .crypt file
            evaluatedFile.write(newData);
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
            sanitized = sanitized.substring(0, i) + (sanitized.charAt(i) + 'Z' - 'z' ) + sanitized.substring(i, sanitized.length());
            //turn characters not in quotes to lower case.
        }
        return sanitized;
    }

}
