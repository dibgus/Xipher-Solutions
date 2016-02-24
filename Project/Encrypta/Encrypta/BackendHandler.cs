using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Runtime.InteropServices;
using System.Diagnostics;
using System.Windows.Forms;

namespace WindowsFormsApplication1
{
    class BackendHandler
    {
        public static Process currentBackendProcess;
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
            #region Create headless backend exe process
            Process backend = createBackendProcess("\"" + expression + "\" \"" + key + "\" 1 " + (Program.usingFile ? "1" : "0"));
            backend.Start();
            backend.WaitForExit();
            #endregion
            //getEncrypted(expressionData, keyData, Program.usingFile);
            String errors = backend.StandardError.ReadToEnd();
            if(!errors.Equals(""))
            {
                if (MessageBox.Show("An error occured during your last encryption run. Display the message?", "Error", MessageBoxButtons.YesNo) == DialogResult.Yes)
                    MessageBox.Show(errors, "Error Details");
            }
            return backend.StandardOutput.ReadToEnd();
            /*
            string encrypted;
            using (StreamReader read = new StreamReader(File.OpenRead("return"), Encoding.Default, true))
                encrypted = read.ReadToEnd();
            File.Delete("return");
            return encrypted;
            */
        }

        private static Process createBackendProcess(String args)
        {
            Process backend = new Process();
            backend.StartInfo.FileName = "java.exe";
            backend.StartInfo.Arguments = "-jar EncryptaBackend.jar " + args;
            backend.StartInfo.UseShellExecute = false;
            backend.StartInfo.CreateNoWindow = true;
            backend.StartInfo.WindowStyle = ProcessWindowStyle.Hidden;
            backend.StartInfo.LoadUserProfile = true;
            backend.StartInfo.RedirectStandardError = true;
            backend.StartInfo.RedirectStandardInput = true;
            backend.StartInfo.RedirectStandardOutput = true;
            currentBackendProcess = backend;
            return backend;
        }

        public static String hashCipher(String cipher)
        {
            Process backendProcess = createBackendProcess("\"" + cipher + "\" \"encr:basic=I#&)*FaKL(~SWOq!mL_=+|obfu:rev|comp:\"");
            backendProcess.Start();
            backendProcess.WaitForExit();
            return backendProcess.StandardOutput.ReadToEnd();
        }

        public static String decryptExpression(String ciphertext, String key)
        {
            //using (FileStream stream = File.Create("return")) { } //create file and close stream 
            if (key.Contains("steg") && !key.Contains(Program.mediaFilePath)) //check if file is specified in key
                key += "=" + Program.mediaFilePath;
            //getDecrypted(ciphertextData, keyData, Program.usingFile);
            #region Create headless backend exe process
            Process backend = createBackendProcess("\"" + ciphertext + "\" \"" + key + "\" 0 " + (Program.usingFile ? "1" : "0"));
            backend.Start();
            backend.WaitForExit();
            #endregion
            String errors = backend.StandardError.ReadToEnd();
            if (!errors.Equals(""))
            {
                if (MessageBox.Show("An error occured during your last encryption run. Display the message?", "Error", MessageBoxButtons.YesNo) == DialogResult.Yes)
                    MessageBox.Show(errors, "Error Details");
            }
        
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
