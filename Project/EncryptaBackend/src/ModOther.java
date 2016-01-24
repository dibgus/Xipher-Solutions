/**
 * Created by ikrukov on 1/14/2016.
 */
import java.io.*;
import java.nio.file.FileSystems;
import java.nio.file.Files;
import java.util.zip.*;

public class ModOther {
    public static String performOperation(String expression, String flag, boolean encrypting)
    {
        String evaluated = "";
        String[] command = InputHandler.handleKey(flag, "="); //splits passed command into the main command and any cipher/etc that should be used
        switch(command[0])
        {
            case "compress":
                evaluated = encrypting ? compressExpression(expression) : decompressExpression(expression);
                break;
            default:
                System.err.println("Could not find other operation: " + command[0]);
                break;
        }
        return evaluated;
    }

    public static byte[] performOperation(byte[] fileData, String flag, boolean encrypting)
    {
        byte[] evaluated = fileData;
        String[] command = InputHandler.handleKey(flag, "="); //splits passed command into the main command and any cipher/etc that should be used
        switch(command[0])
        {
            case "compress":
                evaluated = encrypting ? compressExpression(fileData) : decompressExpression(fileData);
                break;
            default:
                System.err.println("Could not find other operation: " + command[0]);
                break;
        }
        return evaluated;
    }


    public static String compressExpression(String expression)
    {
        String compressed = "";
        try{
            //write current data to file for manipulation
            BufferedWriter dataWriter = new BufferedWriter(new FileWriter("tempData"));
            dataWriter.write(expression);
            dataWriter.close();

            //create a deflater and compress the data written
            BufferedInputStream fin=new BufferedInputStream(new FileInputStream("tempData"));

            BufferedOutputStream fout = new BufferedOutputStream(new FileOutputStream("tempBuffer"));
            DeflaterOutputStream out=new DeflaterOutputStream(fout);
            int i;
            while((i=fin.read())!=-1){
                out.write((byte)i);
                out.flush();
            }
            fin.close();
            out.close();
            fout.close();
            BufferedReader result = new BufferedReader(new FileReader("tempBuffer"));
            while((i = result.read()) != -1)
                compressed = result.readLine();
            result.close();
        }catch(IOException e){System.out.println(e);}
        return compressed;
        /**
         String compressed = "";
         ByteArrayOutputStream byteStream = new ByteArrayOutputStream();
         byte[] stringData = expression.getBytes();
         try {
         GZIPOutputStream compressor = new GZIPOutputStream(byteStream, stringData.length);
         compressor.write(stringData, 0, stringData.length);
         compressor.close();
         byteStream.close();
         } catch (IOException e) {
         e.printStackTrace();
         }
         return byteStream.toString();
         */
    }

    public static String decompressExpression(String expression)
    {
        String decompressed = "";
        try{
            //write current data to file for manipulation
            BufferedWriter dataWriter = new BufferedWriter(new FileWriter("tempData"));
            dataWriter.write(expression);
            dataWriter.close();

            BufferedInputStream fin=new BufferedInputStream(new FileInputStream("tempData"));
            InflaterInputStream in=new InflaterInputStream(fin);

            FileOutputStream fout=new FileOutputStream("decompress.txt");

            int i;
            while((i=in.read())!=-1){
                fout.write((byte)i);
                fout.flush();
            }

            fin.close();
            fout.close();
            in.close();

            BufferedReader result = new BufferedReader(new FileReader("tempBuffer"));
            while((i = result.read()) != -1)
                decompressed = result.readLine();
            result.close();
            System.out.println(fin.read());
            return decompressed;
        }catch(Exception e){System.out.println(e);}
        return expression;
    }

    public static byte[] compressExpression(byte[] fileData)
    {
        try{
            //write current data to file for manipulation
            BufferedOutputStream dataWriter = new BufferedOutputStream(new FileOutputStream("tempData"));
            dataWriter.write(fileData);
            dataWriter.close();

            //create a deflater and compress the data written
            BufferedInputStream fin=new BufferedInputStream(new FileInputStream("tempData"));

            BufferedOutputStream fout = new BufferedOutputStream(new FileOutputStream("tempBuffer"));
            DeflaterOutputStream out=new DeflaterOutputStream(fout);
            int i;
            while((i=fin.read())!=-1){
                out.write((byte)i);
                out.flush();
            }
            fin.close();
            out.close();
            fout.close();
            return Files.readAllBytes(FileSystems.getDefault().getPath("", System.getProperty("user.dir") + "\\tempBuffer"));
        } catch (IOException e) {
            e.printStackTrace();
        }
        return fileData;
    }

    public static byte[] decompressExpression(byte[] fileData)
    {
        try{
            //write current data to file for manipulation
            BufferedOutputStream dataWriter = new BufferedOutputStream(new FileOutputStream("tempData"));
            dataWriter.write(fileData);
            dataWriter.close();

            FileInputStream fin=new FileInputStream("compress.txt");
            InflaterInputStream in=new InflaterInputStream(fin);

            FileOutputStream fout=new FileOutputStream("decompress.txt");

            int i;
            while((i=in.read())!=-1){
                fout.write((byte)i);
                fout.flush();
            }

            fin.close();
            fout.close();
            in.close();

            return Files.readAllBytes(FileSystems.getDefault().getPath("", System.getProperty("user.dir") + "\\tempBuffer"));
        }catch(Exception e){System.out.println(e);}
        return fileData;
    }

}
