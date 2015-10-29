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
using WindowsFormsApplication1;

namespace WindowsFormsApplication1
{
    public partial class Input : MetroForm
    {
        public Input()
        {
            InitializeComponent();
        }

        private void Input_Load(object sender, EventArgs e)
        {
            if (Program.usingFile) rbtnFile.Checked = true; else rbtnString.Checked = true;
        }

        private void btnSubmit_Click(object sender, EventArgs e)
        {
            Program.usingFile = rbtnFile.Checked;
            Close();
        }

        private void Input_FormClosed(object sender, FormClosedEventArgs e)
        {
            btnSubmit_Click(sender, e);
        }
    }
}
