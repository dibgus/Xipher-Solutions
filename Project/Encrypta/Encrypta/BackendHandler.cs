using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
namespace WindowsFormsApplication1
{
    class BackendHandler
    {
        [DllImport("C:\\Users\\ikrukov\\Desktop\\Xipher-Solutions\\Project\\Encrypta\\Encrypta\\Backend.dll")]
        public static extern void getEncrypted(string expression, string key, StringBuilder returnBuffer, int bufferLength);
        [DllImport("C:\\Users\\ikrukov\\Desktop\\Xipher-Solutions\\Project\\Encrypta\\Encrypta\\Backend.dll")]
        public static extern int test(string s);

        public static String encryptExpression(String cipher, String key)
        {
            StringBuilder encryptedBuffer = new StringBuilder(cipher.Length * 10 + 3);
            //creates a stringbuilder pointer(mutable) that my DLL can use to write the string. (minlength 3 for if ERR occurs)
            getEncrypted(cipher, key, encryptedBuffer, encryptedBuffer.Length);
            return encryptedBuffer.ToString();
        }
        public static String decryptExpression(String cipher, String encrypted)
        {

            return "";
        }
    }
}
