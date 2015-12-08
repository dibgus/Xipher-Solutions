/**
 * Created by ikrukov on 12/7/2015.
 * A class whose intention is to house a main method that can be called in an executable for backend code testing
 */
import java.util.Scanner;
public class BackendTester {
    public static void main(String[] args)
    {
        Scanner input = new Scanner(System.in);
        System.out.println("Enter an expression: ");
        String expression = input.nextLine();
        System.out.println("Enter a key: ");
        String key = input.nextLine();
        System.out.println(InputHandler.getEvaluatedExpression(expression, key, true));
    }

}
