/**
 * Created by ikrukov on 12/7/2015.
 * A class whose intention is to house a main method that can be called in an executable for backend code testing
 */
import java.util.Scanner;
public class BackendTester {
    public static void main(String[] args)
    {
        Scanner input = new Scanner(System.in);
        System.out.println("Enter an expression to turn into binary");
        String test = input.nextLine();
        String finals = "";
        for(int i = 0; i < test.length(); i++)
        {
            finals += Converter.intToBinaryString(test.charAt(i));
        }
        System.out.println(finals);
        System.out.println(finals.length() + " " + test.length() * 16);
        System.out.println(Converter.binaryStringToString(finals));
        String expression = "";
        while(true)
        {
            System.out.println("Enter an expression: ");
            String inString = input.nextLine();
            if(!inString.equals("!p")) //!P specifies you want to use the last test string
                expression = inString;
            else System.out.println("Assuming String: " + expression);
            System.out.println("Enter a key: ");
            String key = input.nextLine();
            String encrypted = InputHandler.getEvaluatedExpression(expression, key, true);
            System.out.println(encrypted);
            System.out.println(InputHandler.getEvaluatedExpression(encrypted, key, false));
        }
    }
}