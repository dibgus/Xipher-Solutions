using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApplication1
{
    public partial class SetCipher : Form
    {
        public SetCipher()
        {
            InitializeComponent();
        }

        private void btnApply_Click(object sender, EventArgs e)
        {
            Program.cipher = txtCipher.Text;
            //dialog box for 
        }

        private void btnHelp_Click(object sender, EventArgs e)
        {
            //dialog box for help
        }
    }
}
