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
        /*
        //[DllImport("Backend.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.StdCall)]
        DEPRECATED DLL USAGE
        [DllImport("Backend.dll")]
        public static extern void getEncrypted(StringBuilder expression, StringBuilder key, bool isFile);
        [DllImport("Backend.dll")]
        public static extern void getDecrypted(StringBuilder expression, StringBuilder key, bool isFile);
        */
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
            //using (FileStream stream = File.Create("return")) { } //create file and close stream automatically
            if (key.Contains("steg") && !key.Contains(Program.mediaFilePath)) //check if file is specified in key
                key += "=" + Program.mediaFilePath;
            Boolean isDebugging = false;
            #region Create headless backend exe process
            Process backend = new Process();
            backend.StartInfo.FileName = "backend.exe";
            backend.StartInfo.Arguments = "\"" + expression + "\" \"" + key + "\" 1 " + (Program.usingFile ? "1" : "0");
            backend.StartInfo.UseShellExecute = false;
            backend.StartInfo.CreateNoWindow = true;
            backend.StartInfo.WindowStyle = ProcessWindowStyle.Hidden;
            backend.StartInfo.LoadUserProfile = true;
            backend.StartInfo.RedirectStandardError = true;
            backend.StartInfo.RedirectStandardInput = true;
            backend.StartInfo.RedirectStandardOutput = true;
            backend.Start();
            backend.WaitForExit();
            if (isDebugging)
                return backend.StandardError.ReadToEnd();
            #endregion
            //getEncrypted(expressionData, keyData, Program.usingFile);
            return backend.StandardOutput.ReadToEnd();
            /*
            string encrypted;
            using (StreamReader read = new StreamReader(File.OpenRead("return"), Encoding.Default, true))
                encrypted = read.ReadToEnd();
            File.Delete("return");
            return encrypted;
            */
        }
        public static String decryptExpression(String ciphertext, String key)
        {
            //using (FileStream stream = File.Create("return")) { } //create file and close stream 
            if (key.Contains("steg") && !key.Contains(Program.mediaFilePath)) //check if file is specified in key
                key += "=" + Program.mediaFilePath;
            Boolean isDebugging = false;
            //getDecrypted(ciphertextData, keyData, Program.usingFile);
            #region Create headless backend exe process
            Process backend = new Process();
            backend.StartInfo.FileName = "backend.exe";
            backend.StartInfo.Arguments = "\"" + ciphertext + "\" \"" + key + "\" 1 " + (Program.usingFile ? "1" : "0");
            backend.StartInfo.UseShellExecute = false;
            backend.StartInfo.CreateNoWindow = !isDebugging;
            backend.StartInfo.WindowStyle = !isDebugging ? ProcessWindowStyle.Hidden : ProcessWindowStyle.Normal;
            backend.StartInfo.LoadUserProfile = true;
            backend.StartInfo.RedirectStandardError = true;
            backend.StartInfo.RedirectStandardInput = true;
            backend.StartInfo.RedirectStandardOutput = true;
            backend.Start();
            backend.WaitForExit();
            #endregion
            if (isDebugging)
                return backend.StandardError.ReadToEnd();

            return backend.StandardOutput.ReadToEnd();
            /*
            string decrypted;
            using (StreamReader read = new StreamReader(File.OpenRead("return"), Encoding.Default, true))
                decrypted = read.ReadToEnd();
            File.Delete("return");
            return decrypted;
            */
        }
    }
}
