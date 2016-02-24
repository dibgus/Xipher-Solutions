
/**
 * Created by ikrukov on 12/5/2015.
 * The module for Steganography
 * Steganography is the process of storing information in a discrete format
 */
import javax.imageio.ImageIO;
import javax.sound.sampled.*;
import java.awt.Color;
import java.awt.image.BufferedImage;
import java.io.*;
class ModSteganography {
    public static String performOperation(String expression, String flag, boolean encrypting) throws IOException
    {
        String evaluated = "";
        String[] command = InputHandler.handleKey(flag, "="); //command[0] -> the command to be run; command[1] -> parameters
        switch(command[0])
        {
            case "pix":
                if(encrypting)
                    evaluated = storeInLSB(expression, command[1]);
                else
                    evaluated = extractLSB(expression); //assumes that expression is a file path
                break;
            case "cos":
                if(encrypting)
                    evaluated = storeInCosCurve(expression, command[1]);
                else
                    evaluated = extractCosCurve(expression);
                break;
            case "audio":
                if(encrypting)
                    evaluated = storeInAudio(expression, command[1]);
                else
                    evaluated = extractAudioData(expression);
                break;
            default:
                System.err.println("Could not find steganography operation: " + command[0]);
                break;
        }

        return evaluated; //if encrypting, then this method will return a message about where the image is stored.
    }

    private static String storeInAudio(String expression, String filePath){
        /*
        String binaryString = "";
        for(int i = 0; i < expression.length(); i++)
            binaryString += Converter.intToBinaryString(expression.charAt(i));
        try {
            File audioFile = new File(filePath);
            DataInputStream in =  new DataInputStream(new FileInputStream(audioFile));
            byte[] audioData = new byte[(int)audioFile.length()];
            in.readFully(audioData);
            in.close();
            for(int i = 0; i < binaryString.length(); i++)
            {
                byte lsb = (byte)(audioData[i] % 2);
                audioData[i] = (byte)(audioData[i] - lsb + lsb ^ ((binaryString.charAt(i) == '1') ? 1 : 0));
                //test way to use LSB methods
            }
            DataOutputStream out = new DataOutputStream(new FileOutputStream(filePath + ".crypt"));
            out.write(audioData);
            out.close();
        } catch (FileNotFoundException e){
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
        */
        //AudioInputStream input = new AudioInputStream(new DataLine.Info(new Class<?>, AudioSystem.getAudioFileFormat(new File(filePath))));
        String binaryData = "";
        for(int i = 0; i < expression.length(); i++)
            binaryData += Converter.intToBinaryString(expression.charAt(i));

        try {
            AudioInputStream input = AudioSystem.getAudioInputStream(new File(filePath));
            byte[] audioFileBuffer = new byte[(int)new File(filePath).length()];
            int bytesPerFrame = input.getFormat().getFrameSize(); //gets the amount of bytes representing a frame(smallest unit of sound)
            if(bytesPerFrame == AudioSystem.NOT_SPECIFIED)
                bytesPerFrame = 1; //no defined frame length
            int totalFramesRead = 0;
            int bytesRead = 0;

            while((bytesRead = input.read(audioFileBuffer)) != -1)
            {
                totalFramesRead += bytesRead / bytesPerFrame;
            }
            System.out.println(bytesPerFrame);
            byte[] stubBuffer = audioFileBuffer.clone();
            for(int i = bytesPerFrame - 1; i < binaryData.length(); i+= bytesPerFrame)
            {
                audioFileBuffer[i] = (byte)LSBHandler.insertLSB(audioFileBuffer[i], (byte)(binaryData.charAt(i) - 48));
                stubBuffer[i] = 20;
            }
            audioFileBuffer = LSBHandler.writePadding((byte)32, audioFileBuffer, binaryData.length() * bytesPerFrame, bytesPerFrame);
            //writes manipulated audio file to <FILENAME>steg.<EXTENSION>
            String outFile = filePath.substring(0, filePath.indexOf(".")) + "steg" + filePath.substring(filePath.indexOf("."));
            String stubFile = filePath.substring(0, filePath.indexOf(".")) + "stub" + filePath.substring(filePath.indexOf("."));
            BufferedInputStream headerReader = new BufferedInputStream(new FileInputStream(filePath));
            //AudioSystem.write(input, AudioFileFormat.Type.WAVE,
              //      new File(outFile));
            //above line was intended to write the header of a WAVE file, but the header seemed to be wrong
            //now write the audio data stored in the buffer...
            BufferedOutputStream out = new BufferedOutputStream(new FileOutputStream(outFile));
            BufferedOutputStream stub = new BufferedOutputStream(new FileOutputStream(stubFile));
            byte[] header = new byte[44]; //44 is the length of a .WAV header
            headerReader.read(header, 0, 44);
            headerReader.close();
            out.write(header);
            stub.write(header);
            out.write(audioFileBuffer);
            stub.write(stubBuffer);
            out.close();
            input.close();
            stub.close();
            headerReader.close();
            return "Data has been stored in audio file: " + outFile;
        } catch (UnsupportedAudioFileException | IOException e) {
            e.printStackTrace();
        }
        return "Something happened...";
    }

    private static String extractAudioData(String expression) {
        String extracted = ""; //expression will be the file path
        AudioInputStream input;
        try {
            input = AudioSystem.getAudioInputStream(new File(expression));
            byte[] audioFileBuffer = new byte[(int)new File(expression).length()];
            int bytesPerFrame = input.getFormat().getFrameSize(); //gets the amount of bytes representing a frame(smallest unit of sound)
            if(bytesPerFrame == AudioSystem.NOT_SPECIFIED)
                bytesPerFrame = 1; //no defined frame length
            int totalFramesRead = 0;
            int bytesRead;
            while((bytesRead = input.read(audioFileBuffer)) != -1) {
                totalFramesRead += bytesRead / bytesPerFrame;
            }
            if(totalFramesRead == 0)
            {
                System.err.println("ERROR: No data in file read");
                return expression;
            }

            String binaryDataRepresentation = "";
            int terminateBits = 0;
            for(int i = bytesPerFrame - 1; i < audioFileBuffer.length && terminateBits < 32; bytesPerFrame++)
            {
                byte lsb = (byte)(audioFileBuffer[i] % 2);
                binaryDataRepresentation += Math.abs(lsb);
                if(lsb == 0)
                    terminateBits++;
                else
                    terminateBits = 0;
                //checks if at least 16 bits have been written, and then checks if there is a null termination (16 zeroes)
            }
            if(terminateBits >= 32)
                binaryDataRepresentation = binaryDataRepresentation.substring(0, binaryDataRepresentation.length() - terminateBits);
            //truncate the null termination
            input.close();
            extracted = Converter.binaryStringToString(binaryDataRepresentation);
        } catch (UnsupportedAudioFileException | IOException e) {
            e.printStackTrace();
        }


        return extracted;
    }

    /**
     * Hides data in an image's least significant bits in order to create an image with minimal visual difference.
     * (Small tweaks to RGB values)
     * @param expression The data that will be stored into the image
     * @param filePath The path to the actual image
     * @return A message that states that
     * @throws IOException: The image specified in filePath does not exist
     * @throws IOException: The application could not successfully find the provided image's extension (or it is unsupported by ImageIO)
     */
    private static String storeInLSB(String expression, String filePath) throws IOException
    {
        BufferedImage storageImage = ImageIO.read(new File(filePath));
        BufferedImage debugImage = ImageIO.read(new File(filePath));
        String expressionBinary = "";
        for(int i = 0; i < expression.length(); i++)
            expressionBinary += Converter.intToBinaryString(expression.charAt(i));
        int component = 0; //0 to R, 1 to G, 2 to B
        if(storageImage.getWidth() * storageImage.getHeight() < expressionBinary.length())
            return "ERROR: Storage image was not large enough to store the expression";
        int x = 0, y = 0; //image coords that are being read
            for (int i = 0; i < expressionBinary.length(); i++, component++) {
                if (component == 3) {
                    x++;
                    if (x >= storageImage.getWidth()) {
                        x = 0;
                        y++;
                    }
                    component = 0;
                }
                Color modPixel = new Color(storageImage.getRGB(x, y));
                byte lsb = (byte) (expressionBinary.charAt(i) - 48); //converts a character of 1 or 0 to the equivalent integer value
                switch (component) { //each component tests if the last bit is the same as the bit that is being stored, otherwise it changes that bit
                    case 0: //red
                        if (lsb != modPixel.getRed() % 2)
                            storageImage.setRGB(x, y, new Color(LSBHandler.insertLSB(modPixel.getRed(), lsb), modPixel.getGreen(), modPixel.getBlue()).getRGB());
                    case 1: //green
                        if (lsb != modPixel.getGreen() % 2)
                            storageImage.setRGB(x, y, new Color(modPixel.getRed(), LSBHandler.insertLSB(modPixel.getGreen(), lsb), modPixel.getBlue()).getRGB());
                        break;
                    case 2: //blue
                        if (lsb != modPixel.getBlue() % 2)
                            storageImage.setRGB(x, y, new Color(modPixel.getRed(), modPixel.getGreen(), LSBHandler.insertLSB(modPixel.getBlue(), lsb)).getRGB());
                        break;
                }
                debugImage.setRGB(x, y, new Color(255, 0, 0).getRGB());
                //storageImage.setRGB(x, y, new Color(0, 8, 255).getRGB()); //DEBUG LINE
            }
        //now add a null term
        for(int i =0; i < 15; i++)
        {
            if(component == 3)
            {
                if(x >= storageImage.getWidth())
                {
                    x = 0;
                    y++;
                }
                component = 0;
            }
            Color modPixel = new Color(storageImage.getRGB(x, y));
            switch(component) { //set lsb of each component to zero
                case 0: //red
                    storageImage.setRGB(x, y, new Color(modPixel.getRed() - modPixel.getRed() % 2, modPixel.getGreen(), modPixel.getBlue()).getRGB());
                    break;
                case 1: //green
                        storageImage.setRGB(x, y, new Color(modPixel.getRed(), modPixel.getGreen() - modPixel.getGreen() % 2, modPixel.getBlue()).getRGB());
                        break;
                case 2: //blue
                    storageImage.setRGB(x, y, new Color(modPixel.getRed(), modPixel.getGreen(), modPixel.getBlue() - modPixel.getBlue() % 2).getRGB());
                    break;
            }

        }
        File sourceImage = new File(filePath.substring(0, filePath.lastIndexOf(".")) + "encrypted." + filePath.substring(filePath.lastIndexOf(".") + 1));
        //creates a new file called <IMAGENAME>encrypted.<ORIGINALEXTENSION>
        File debugFile = new File(filePath.substring(0, filePath.lastIndexOf(".")) + "stub." + filePath.substring(filePath.lastIndexOf(".") + 1));
        String extension = filePath.substring(filePath.lastIndexOf(".") + 1, filePath.length());
        ImageIO.write(storageImage, extension, sourceImage);
        ImageIO.write(debugImage, extension, debugFile);
        return "Data has been stored in " + sourceImage.getPath();
    }

    private static String extractLSB(String filePath) throws IOException
    {
        String binaryExtracted = "";
        BufferedImage source = ImageIO.read(new File(filePath));
        short numNullTerm = 0; //Increments every time a 0 is found and resets at a 1 to terminate the loop early
        short component = 0; //0 R 1 G 2 B
        ImageLoop:
        for(int y = 0; y <= source.getHeight(); y++)
        {
            for(int x = 0; x <= source.getWidth(); x++)
            {
                if(component >= 3)
                    component = 0;
                if(numNullTerm == 16)
                    break ImageLoop;
                short lsb = 0;
                Color readPixel = new Color(source.getRGB(x, y));
                switch(component)
                {
                    case 0:
                        lsb = (short)(readPixel.getRed() % 2);
                        break;
                    case 1:
                        lsb = (short)(readPixel.getGreen() % 2);
                        break;
                    case 2:
                        lsb = (short)(readPixel.getBlue() % 2);
                        break;
                }
                if(lsb == 0)
                    numNullTerm++;
                binaryExtracted += lsb;
                component++;
            }
        }
        return Converter.binaryStringToString(binaryExtracted);
    }

    //TODO rewrite stuff
    public static byte[] performOperation(byte[] fileData, String flag, boolean encrypting) throws IOException
    {
        String storedMessage = ""; //printed if the user stores data in the image instead of extracting to a file format
        String[] command = InputHandler.handleKey(flag, "="); //command[0] -> the command to be run; command[1] -> parameters
        switch(command[0])
        {
            case "pix":
                if(encrypting)
                    storedMessage = storeInLSB(fileData, command[1]);
                else
                    return extractLSB(command[1], true); //assumes that expression is a file path
                break;
            case "cos":
                if(encrypting)
                    storedMessage = storeInCosCurve(command[1]  , command[1]);
                else
                    storedMessage = extractCosCurve(command[1]);

            default:
                System.err.println("Could not find steganography operation: " + command[0]);
                break;
        }

        System.out.println(storedMessage);
        return null; //if encrypting, then this method will return a message about where the image is stored.
    }

    private static String storeInLSB(byte[] fileData, String filePath) throws IOException
    {
        BufferedImage storageImage = ImageIO.read(new File(filePath));
        String expressionBinary = "";
        for(int i = 0; i < fileData.length; i++)
            expressionBinary += Converter.intToBinaryString(fileData[i]);
        int component = 0; //0 to R, 1 to G, 2 to B
        if(storageImage.getWidth() * storageImage.getHeight() < expressionBinary.length())
            return "ERROR: Storage image was not large enough to store the expression";
        int x = 0, y = 0; //image coords that are being read
        for(int i = 0; i < expressionBinary.length(); i++, component++)
        {
            if(component == 3)
            {
                if(x >= storageImage.getWidth())
                {
                    x = 0;
                    y++;
                }
                component = 0;
            }
            Color modPixel = new Color(storageImage.getRGB(x, y));
            byte lsb = (byte)(expressionBinary.charAt(i) - 48); //converts a character of 1 or 0 to the equivalent integer value
            switch(component) { //each component tests if the last bit is the same as the bit that is being stored, otherwise it changes that bit
                case 0: //red
                    if(lsb != modPixel.getRed() % 2)
                        storageImage.setRGB(x, y, new Color(LSBHandler.insertLSB(modPixel.getRed(), lsb), modPixel.getGreen(), modPixel.getBlue()).getRGB());
                    break;
                case 1: //green
                    if(lsb != modPixel.getGreen() % 2)
                        storageImage.setRGB(x, y, new Color(modPixel.getRed(), LSBHandler.insertLSB(modPixel.getGreen(), lsb), modPixel.getBlue()).getRGB());
                    break;
                case 2: //blue
                    if(lsb != modPixel.getBlue() % 2)
                        storageImage.setRGB(x, y, new Color(modPixel.getRed(), modPixel.getGreen(), LSBHandler.insertLSB(modPixel.getBlue(), lsb)).getRGB());
                    break;
            }
        }
        //now add a null term
        for(int i =0; i < 15; i++)
        {
            if(component == 3)
            {
                if(x >= storageImage.getWidth())
                {
                    x = 0;
                    y++;
                }
                component = 0;
            }
            Color modPixel = new Color(storageImage.getRGB(x, y));
            switch(component) { //set lsb of each component to zero
                case 0: //red
                    storageImage.setRGB(x, y, new Color(LSBHandler.insertLSB(modPixel.getRed(), (byte)0), modPixel.getGreen(), modPixel.getBlue()).getRGB());
                    break;
                case 1: //green
                    storageImage.setRGB(x, y, new Color(modPixel.getRed(), LSBHandler.insertLSB(modPixel.getGreen(), (byte)0), modPixel.getBlue()).getRGB());
                    break;
                case 2: //blue
                    storageImage.setRGB(x, y, new Color(modPixel.getRed(), modPixel.getGreen(), LSBHandler.insertLSB(modPixel.getBlue(), (byte)0)).getRGB());
                    break;
            }

        }
        File sourceImage = new File(filePath.substring(0, filePath.lastIndexOf(".")) + "encrypted." + filePath.substring(filePath.lastIndexOf(".") + 1));
        //creates a new file called <IMAGENAME>encrypted.<ORIGINALEXTENSION>
        String extension = filePath.substring(filePath.lastIndexOf(".") + 1, filePath.length());
        ImageIO.write(storageImage, extension, sourceImage);
        return "Data has been stored in " + sourceImage.getPath();
    }

    //for file data
    private static byte[] extractLSB(String filePath, boolean isFile) throws IOException
    {
        String binaryExtracted = "";
        BufferedImage source = ImageIO.read(new File(filePath));
        short numNullTerm = 0; //Increments every time a 0 is found and resets at a 1 to terminate the loop early
        short component = 0; //0 R 1 G 2 B
        ImageLoop:
        for(int y = 0; y <= source.getHeight(); y++)
        {
            for(int x = 0; x <= source.getWidth(); x++)
            {
                if(component >= 3)
                    component = 0;
                if(numNullTerm == 16)
                    break ImageLoop;
                short lsb = 0;
                Color readPixel = new Color(source.getRGB(x, y));
                switch(component)
                {
                    case 0:
                        lsb = (short)(readPixel.getRed() % 2);
                        break;
                    case 1:
                        lsb = (short)(readPixel.getGreen() % 2);
                        break;
                    case 2:
                        lsb = (short)(readPixel.getBlue() % 2);
                        break;
                }
                if(lsb == 0)
                    numNullTerm++;
                binaryExtracted += lsb;
                component++;
            }
        }
        return Converter.binaryStringToByteArray(binaryExtracted);
    }

    //TODO implement methods involving cosine curves (may be more complex than I think it will be
    private static String storeInCosCurve(String expression, String filePath)
    {

        return "";
    }
    private static String extractCosCurve(String expression)
    {

        return "";
    }


}
