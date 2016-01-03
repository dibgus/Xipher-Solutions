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
    public partial class HashGenerator : MetroForm
    {
        public HashGenerator()
        {
            InitializeComponent();
        }

        private void btnGenerate_Click(object sender, EventArgs e)
        {
            String hash = "";
            int seed = 0;
            Random generator;
            if(txtSeed.Text.Equals(""))
                generator = new Random();
            else
            {
                if(!int.TryParse(txtSeed.Text, out seed))
                {
                    for (int i = 0; i < txtSeed.Text.Length; i++)
                        seed += txtSeed.Text.ToCharArray()[i];
                }
                generator = new Random(seed);
            }
            for (int i = 0; i < int.Parse(nudLength.Text); i++)
                hash += (char)(generator.Next(33,122));
            if (ckbxCopyClipboard.Checked)
                Clipboard.SetText(hash);
            txtHash.Text = hash;
        }

        private void btnHelp_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Hashes are sorts of passwords that you can use to protect your data.\nThis utility is best used when using the encryption module when specifying a password for your encrypted data.\nLeaving a blank seed will result in a random seed, and may be more secure.");
        }
    }
}
