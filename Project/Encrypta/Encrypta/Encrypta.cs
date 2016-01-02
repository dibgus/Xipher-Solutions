﻿using System;
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
        public void updateVisuals()
        {
            if(Program.usingFile)
            {
                txtInput.Visible = false;
                txtPath.Visible = true;
                btnSelectFile.Visible = true;
            }
            else
            {
                txtInput.Visible = true;
                txtPath.Visible = false;
                btnSelectFile.Visible = false;
            }
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
            if (Program.isEncrypting)
                txtEncrypted.Text = BackendHandler.encryptExpression(Program.usingFile ? txtPath.Text : txtInput.Text, Program.cipher);
            else
                txtEncrypted.Text = BackendHandler.decryptExpression(Program.usingFile ? txtPath.Text : txtInput.Text, Program.cipher);

            if (ckbxCopyClipboard.Checked)
                Clipboard.SetText(txtEncrypted.Text);
        }

        private void btnInput_Click(object sender, EventArgs e)
        {
            new Input().ShowDialog();
        } //PInvokeStackImbalance

        private void btnToggleEncryption_Click(object sender, EventArgs e)
        {
            Program.isEncrypting = !Program.isEncrypting;
            lblInput.Text = Program.isEncrypting ? "Item to encrypt: " : "Item to decrypt: ";
            btnEncrypt.Text = Program.isEncrypting ? "Encrypt" : "Decrypt";
        }

        private void btnSelectFile_Click(object sender, EventArgs e)
        {
            OpenFileDialog fileInput = new OpenFileDialog();
            if (fileInput.ShowDialog() == DialogResult.OK)
            {
                Program.filePath = fileInput.FileName;
                txtPath.Text = Program.filePath;
            }
        }
    }
}
