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
            MessageBox.Show("A cipher is also known as the key that you will encrypt your data.\nCurrently, you can separate operations with an \"|\"\nCurrent Operations include: <LIST>","Help");
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
        }
    }
}
