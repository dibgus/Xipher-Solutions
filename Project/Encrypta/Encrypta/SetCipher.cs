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
    public partial class SetCipher : MetroForm
    {
        public SetCipher()
        {
            InitializeComponent();
        }

        private void btnApply_Click(object sender, EventArgs e)
        {
            Program.cipher = txtCipher.Text;
            MessageBox.Show("Your changes have been applied");
            //dialog box for applied
        }

        private void btnHelp_Click(object sender, EventArgs e)
        {
            MessageBox.Show("A cipher is also known as the key that you will encrypt your data.\nCurrently, you can separate operations with an \"|\"\n\nHere is an example: \"obfu:rev|crc=10|evo|steg:pix\"\nCurrent Modules(put these first, options follow each module): \n\nsteg:\n\tpix\n\tcos\nobfu:\n\trev\n\tcrc=#\n\ttnc=#*#\n\tevo\n\tskh", "Help");
            //dialog box for help
        }

        private void btnOk_Click(object sender, EventArgs e)
        {
            Program.cipher = txtCipher.Text;
            Close();
        }

        private void SetCipher_Load(object sender, EventArgs e)
        {
            txtCipher.Text = Program.cipher;
            txtFilePath.Text = Program.mediaFilePath;
        }

        private void btnSelectFile_Click(object sender, EventArgs e)
        {
            OpenFileDialog fileInput = new OpenFileDialog();
            if (fileInput.ShowDialog() == DialogResult.OK)
            {
                Program.mediaFilePath = fileInput.FileName;
                txtFilePath.Text = Program.mediaFilePath;
            }
        }

        private void btnGenerateHash_Click(object sender, EventArgs e)
        {
            new HashGenerator().Show();
        }

        private void btnHashCipher_Click(object sender, EventArgs e)
        {
            txtCipher.Text = BackendHandler.encryptExpression(txtCipher.Text, "encr:basic");
            ckbxIsHash.Checked = true;
        }

        private void ckbxIsHash_CheckedChanged(object sender, EventArgs e)
        {
            Program.cipherIsHash = ckbxIsHash.Checked;
        }
    }
}
