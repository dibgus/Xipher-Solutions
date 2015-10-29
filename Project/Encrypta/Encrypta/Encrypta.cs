using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using MetroFramework.Components;
using MetroFramework.Forms;
using MetroFramework.Drawing;
using MetroFramework.Controls;

namespace WindowsFormsApplication1
{
    public partial class frmMain : MetroForm
    {
        public frmMain()
        {
            InitializeComponent();
        }

        private void frmMain_Load(object sender, EventArgs e)
        {
         
        }

        private void mnuSettingsInput_Click(object sender, EventArgs e)
        {
            new Input().ShowDialog();
        }

        private void btnSetCipher_Click(object sender, EventArgs e)
        {
            new SetCipher().ShowDialog();
        }

        private void btnEncrypt_Click(object sender, EventArgs e)
        {
            txtEncrypted.Text = BackendHandler.encryptExpression(txtInput.Text, Program.cipher);
            if (ckbxCopyClipboard.Checked) Clipboard.SetText(txtEncrypted.Text);
        }

        private void btnInput_Click(object sender, EventArgs e)
        {
            new Input().ShowDialog();
        } //PInvokeStackImbalance

        private void button1_Click(object sender, EventArgs e)
        {//test button for DLL's
         txtEncrypted.Text = BackendHandler.test("hdg").ToString();
        }
    }
}
