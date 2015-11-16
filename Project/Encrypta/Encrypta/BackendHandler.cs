using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Runtime.InteropServices;
using System.Diagnostics;
namespace WindowsFormsApplication1
{
    class BackendHandler
    { 
        [DllImport("Backend.dll", CallingConvention = CallingConvention.StdCall)]
        public static extern void getEncrypted(StringBuilder expression, StringBuilder key, bool isFile);
        [DllImport("Backend.dll", CallingConvention = CallingConvention.StdCall)]
        public static extern void getDecrypted(StringBuilder expression, StringBuilder key, bool isFile);
        [DllImport("Backend.dll")]
        public static extern int test(string s);
        /*
        public static String encryptExpression(String expression, String key)
        {
            string encryptedBuffer = new string(expression.Length * 10);
            //creates a string pointer(mutable) that my DLL can use to write the string.
            getEncrypted(expression, key, encryptedBuffer, expression.Length * 10);
            //TODO: fix string buffer size issues(look into how to make it resizeable?)
            //TODO: fix issue where random characters are sometimes returned at the end of the string
            return encryptedBuffer.ToString();
        }
        public static String decryptExpression(String ciphertext, String key)
        {
            string decryptedBuffer = new string(ciphertext.Length);
            getDecrypted(ciphertext, key, decryptedBuffer, ciphertext.Length);
            return decryptedBuffer.ToString();
        }
        */
        public static String encryptExpression(String expression, String key)
        {
            using (FileStream stream = File.Create("return")) { } //create file and close stream automatically
            StringBuilder expressionData = new StringBuilder(expression);
            StringBuilder keyData = new StringBuilder(key);
            getEncrypted(expressionData, keyData, Program.usingFile);
            string encrypted;
            using (StreamReader read = new StreamReader(File.OpenRead("return")))
                encrypted = read.ReadToEnd();
            File.Delete("return");
            return encrypted;
        }
        public static String decryptExpression(String ciphertext, String key)
        {
            using (FileStream stream = File.Create("return")) { } //create file and close stream 
            StringBuilder ciphertextData = new StringBuilder(ciphertext);
            StringBuilder keyData = new StringBuilder(key);
            getDecrypted(ciphertextData, keyData, Program.usingFile);
            string decrypted;
            using (StreamReader read = new StreamReader(File.OpenRead("return")))
                decrypted = read.ReadToEnd();
            File.Delete("return");
            return decrypted;
        }
    }
}
