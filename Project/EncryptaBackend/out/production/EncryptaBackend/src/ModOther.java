/**
 * Created by ikrukov on 1/14/2016.
 */
import java.util.zip.*;

public class ModOther {
    public static String performOperation(String expression, String flag, boolean encrypting)
    {
        String evaluated = "";
        String[] command = InputHandler.handleKey(flag, "="); //splits passed command into the main command and any cipher/etc that should be used
        switch(command[0])
        {
            case "compress":

                break;
            default:
                System.err.println("Could not find other operation: " + command[0]);
                break;
        }
        return evaluated;
    }

    public static String compressExpression(String expression)
    {
        /*
        String compressed = "";
        ZipOutputStream outputStream = new
        return compressed.
        */
        return "";
    }

}
