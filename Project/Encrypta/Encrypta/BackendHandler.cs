﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
namespace WindowsFormsApplication1
{
    class BackendHandler
    {
        [DllImport("Backend.dll")]
        public static extern void getEncrypted(string expression, string key, StringBuilder returnBuffer, long bufferlen);
        [DllImport("Backend.dll")]
        public static extern void getDecrypted(string expression, string key, StringBuilder returnBuffer, long bufferlen);
        [DllImport("Backend.dll")]
        public static extern int test(string s);

        public static String encryptExpression(String expression, String key)
        {
            StringBuilder encryptedBuffer = new StringBuilder(expression.Length * 10);
            //creates a stringbuilder pointer(mutable) that my DLL can use to write the string.
            getEncrypted(expression, key, encryptedBuffer, expression.Length * 10);
            //TODO: fix StringBuilder buffer size issues(look into how to make it resizeable?)
            //TODO: fix issue where random characters are sometimes returned at the end of the string
            return encryptedBuffer.ToString();
        }
        public static String decryptExpression(String ciphertext, String key)
        {
            StringBuilder decryptedBuffer = new StringBuilder(ciphertext.Length);
            getDecrypted(ciphertext, key, decryptedBuffer, ciphertext.Length);
            return decryptedBuffer.ToString();
        }
    }
}
