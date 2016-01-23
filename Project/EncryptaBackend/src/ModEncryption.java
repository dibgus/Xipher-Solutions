/**
 * Created by ikrukov on 1/2/2016.
 * The module for Encryption
 * Using the Jasypt library for encryption operations.
 */
import org.jasypt.digest.StandardByteDigester;
import org.jasypt.digest.StandardStringDigester;
import org.jasypt.encryption.pbe.StandardPBEByteEncryptor;
import org.jasypt.util.text.*; //preset strong and basic preset operations
class ModEncryption {
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
            case "digest":
                if(encrypting)
                    evaluated = digestData(expression, Integer.parseInt(command[1]));
                else
                    System.err.println("(Encryption)Error: Cannot decrypt data which has been irreversably encrypted with digest");
            default:
                System.err.println("Could not find encryption operation: " + command[0]);
                break;
        }
        return evaluated;
    }

    public static byte[] performOperation(byte[] fileData, String flag, boolean encrypting)
    {
        String[] command = InputHandler.handleKey(flag, "="); //splits passed command into the main command and any cipher/etc that should be used
        switch(command[0])
        {
            case "basic":
                return encrypting ? useBasicEncryption(fileData, command[1]) : useBasicDecryption(fileData, command[1]);
            case "strong":
                try
                {
                    return encrypting ? useStrongEncryption(fileData, command[1]) : useStrongDecryption(fileData, command[1]);
                } catch (org.jasypt.exceptions.EncryptionOperationNotPossibleException e) {
                    System.err.println("ERROR: JCE utilities are not installed on this machine, cannot use strong");
                    e.printStackTrace();
                }
                break;
            case "digest":
                if(encrypting)
                    return digestData(fileData, Integer.parseInt(command[1]));
                else
                {
                    System.err.println("(Encryption)Error: Cannot decrypt data which has been irreversably encrypted with digest");
                    return fileData;
                }
                default:
                    System.err.println("Could not find encryption operation: " + command[0]);
                    break;
        }
        return fileData;
    }

    private static String useBasicEncryption(String expression, String hash)
    {
        BasicTextEncryptor encryptor = new BasicTextEncryptor();
        encryptor.setPassword(hash);
        return encryptor.encrypt(expression);
    }

    private static String useStrongEncryption(String expression, String hash)
    {
        StrongTextEncryptor encryptor = new StrongTextEncryptor();
        encryptor.setPassword(hash);
        return encryptor.encrypt(expression);
    }
    private static String useBasicDecryption(String expression, String hash)
    {
        BasicTextEncryptor decryptor = new BasicTextEncryptor();
        decryptor.setPassword(hash);
        return decryptor.decrypt(expression);
    }

    private static String useStrongDecryption(String expression, String hash)
    {
        StrongTextEncryptor decryptor = new StrongTextEncryptor();
        decryptor.setPassword(hash);
        return decryptor.decrypt(expression);
    }

    private static String digestData(String expression, int iterations)
    {
        StandardStringDigester digester = new StandardStringDigester();
        digester.setAlgorithm("SHA-1");
        digester.setIterations(iterations);
        return digester.digest(expression);
    }

/* Encryption for files */
    private static byte[] useBasicEncryption(byte[] fileData, String hash)
    {
        StandardPBEByteEncryptor encryptor = new StandardPBEByteEncryptor();
        encryptor.setPassword(hash);
        encryptor.setAlgorithm("AES-128");
        return encryptor.encrypt(fileData);
    }

    private static byte[] useStrongEncryption(byte[] fileData, String hash)
    {
        StandardPBEByteEncryptor encryptor = new StandardPBEByteEncryptor();
        encryptor.setPassword(hash);
        encryptor.setAlgorithm("AES");
        return encryptor.encrypt(fileData);
    }
    private static byte[] useBasicDecryption(byte[] fileData, String hash)
    {
        StandardPBEByteEncryptor decryptor = new StandardPBEByteEncryptor();
        decryptor.setPassword(hash);
        decryptor.setAlgorithm("AES-128");
        return decryptor.decrypt(fileData);
    }

    private static byte[] useStrongDecryption(byte[] fileData, String hash)
    {
        StandardPBEByteEncryptor decryptor = new StandardPBEByteEncryptor();
        decryptor.setPassword(hash);
        decryptor.setAlgorithm("AES-128");
        return decryptor.decrypt(fileData);
    }

    private static byte[] digestData(byte[] expression, int iterations)
    {
        StandardByteDigester digester = new StandardByteDigester();
        digester.setAlgorithm("SHA-1");
        digester.setIterations(iterations);
        return digester.digest(expression);
    }

}
