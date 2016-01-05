/**
 * Created by ikrukov on 12/7/2015.
 * A class whose intention is to house a main method that can be called in an executable for backend code testing
 */
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;
class BackendTester {
    public static void main(String[] args)
    {
        Scanner input = new Scanner(System.in);
        String expression = "";
        while(true)
        {
            System.out.println("Enter mode:\n1: Files\n2: Strings\n3: Exit");
            String opt = input.nextLine();
            if(opt.charAt(0) == '1')
            {
                System.out.println("Enter a file path: ");
                String path = input.nextLine();
                System.out.println("Enter a key: ");
                String key = input.nextLine();
                String encrypted = InputHandler.createEvaluatedFile(path, key, true);
                File outFile = new File(path + ".crypt");
                try {
                    FileWriter writer = new FileWriter(outFile);
                    writer.write(encrypted);
                    writer.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            else if(opt.charAt(0) == '2')
            {
                System.out.println("Enter an expression: ");
                String inString = input.nextLine();
                if (!inString.equals("!p")) //!P specifies you want to use the last test string
                    expression = inString;
                else System.out.println("Assuming String: " + expression);
                System.out.println("Enter a key: ");
                String key = input.nextLine();
                String encrypted = InputHandler.getEvaluatedExpression(expression, key, true);
                System.out.println(encrypted);
                System.out.println(InputHandler.getEvaluatedExpression(encrypted, key, false));
            }
            else break;
        }
    }
}