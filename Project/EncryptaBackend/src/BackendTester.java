/**
 * Created by ikrukov on 12/7/2015.
 * A class whose intention is to house a main method that can be called in an executable for backend code testing
 */
import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Paths;
import java.util.Scanner;
//VV TEMPORARY IMPORTS FOR TESTING VV
import java.awt.*;
class BackendTester {
    public static void main(String[] args)
    {
        Scanner input = new Scanner(System.in);
        String expression = "";
        while(true)
        {
            System.out.println("Enter mode:\n1: Files\n2: Strings\n3: Help\n4: Custom Function\n5: Custom Function 2\n<ANYKEY>: Quit");
            String opt = input.nextLine();
            if(opt.charAt(0) == '1')
            {
                System.out.println("Enter a file path: ");
                String path = input.nextLine();
                System.out.println("Enter a key: ");
                String key = input.nextLine();
                String encrypted = InputHandler.createEvaluatedFile(path, key, true);
                //File outFile = new File(path + ".crypt");
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
                if(encrypted.contains("Data has been stored in")) //detects if steganography was run
                    System.out.println(InputHandler.getEvaluatedExpression(encrypted.substring(encrypted.indexOf("c")), key, false));
                else
                    System.out.println(InputHandler.getEvaluatedExpression(encrypted, key, false));
            }
            else if(opt.charAt(0) == '3')
            {
                System.out.println("Key Format:\tMODULE:FUNCTION=PARAMS\nModules: steg, pix, encr, obfu, other");
            }
            else if(opt.charAt(0) == '4')
            {
                String testImage = "C:\\users\\ikrukov\\desktop\\woop.png";
                String key = "steg:pix=";
                String testData = "These are words that I would like to store with Steganography";
                System.out.println(InputHandler.getEvaluatedExpression(testData, key + testImage, true));
                String encrypted = "C:\\users\\ikrukov\\desktop\\woopencrypted.png";
                System.out.println(InputHandler.getEvaluatedExpression(encrypted, key + encrypted, false));
                //enter test code
            }
            else if(opt.charAt(0) == '5')
                imageComparer("C:\\users\\ikrukov\\desktop\\woop.png", "C:\\users\\ikrukov\\desktop\\woopencrypted.png");
            else break;
        }
    }

    /**
     * will likely keep this method for presentation purposes
     * Just a simple method that performs image subtraction to get diffs between images
     * @param path1
     * @param path2
     */
    public static void imageComparer(String path1, String path2)
    {
        try {
            BufferedImage img1 = ImageIO.read(new File(path1));
            BufferedImage img2 = ImageIO.read(new File(path2));
            BufferedImage diff = new BufferedImage(img1.getWidth(), img1.getHeight(), img1.getType());
            System.out.println("loop");
            for(int y = 0; y < img1.getHeight(); y++)
                for(int x = 0; x < img1.getWidth(); x++)
                {
                    diff.setRGB(x, y, img1.getRGB(x, y) - img2.getRGB(x, y));
                }
            System.out.println("compared!");
            ImageIO.write(diff, path1.substring(path1.lastIndexOf(".") + 1), new File(path1 + ".diff"));
            System.out.println("saved");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}