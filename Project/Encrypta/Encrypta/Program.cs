using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace WindowsFormsApplication1
{
    static class Program
    {
        public static bool usingFile = false;
        public static String cipher = "";
        public static bool isEncrypting = true;
        public static frmMain mainForm;
        public static string filePath = "";
        public static string mediaFilePath = "";

        //public static string[] = {"Helo", "hi"};
        /// <summary>
        /// The main entry point for the application.   
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            mainForm = new frmMain();
            Application.Run(mainForm);
        }
    }
}
