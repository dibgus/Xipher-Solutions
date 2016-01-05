/**
 * Created by ikrukov on 1/2/2016.
 * The module for Encryption
 * Using the Jasypt library for encryption operations.
 */
import org.jasypt.util.text.*; //preset strong and basic preset operations

public class ModEncryption {
    public static String performOperation(String expression, String flag, boolean encrypting)
    {
        String evaluated = "";
        String[] command = InputHandler.handleKey(flag, "="); //splits passed command into the main command and any cipher/etc that should be used
        switch(command[0])
        {
            case "basic":
                evaluated = encrypting ? useBasicEncryption(expression, command[1]) : useBasicDecryption(expression, command[1]);
                break;
            case "strong":
                try
                {
                    evaluated = encrypting ? useStrongEncryption(expression, command[1]) : useStrongDecryption(expression, command[1]);
                } catch (org.jasypt.exceptions.EncryptionOperationNotPossibleException e) {
                    System.err.println("ERROR: JCE utilities are not installed on this machine, cannot use strong");
                    e.printStackTrace();
                }
                break;
            default:
                System.err.println("Could not find encryption operation: " + command[0]);
                break;
        }
        return evaluated;
    }

    public static String useBasicEncryption(String expression, String hash)
    {
        BasicTextEncryptor encryptor = new BasicTextEncryptor();
        encryptor.setPassword(hash);
        return encryptor.encrypt(expression);
    }

    public static String useStrongEncryption(String expression, String hash)
    {
        StrongTextEncryptor encryptor = new StrongTextEncryptor();
        encryptor.setPassword(hash);
        return encryptor.encrypt(expression);
    }
    public static String useBasicDecryption(String expression, String hash)
    {
        BasicTextEncryptor decryptor = new BasicTextEncryptor();
        decryptor.setPassword(hash);
        return decryptor.decrypt(expression);
    }

    public static String useStrongDecryption(String expression, String hash)
    {
        StrongTextEncryptor decryptor = new StrongTextEncryptor();
        decryptor.setPassword(hash);
        return decryptor.decrypt(expression);
    }
}
