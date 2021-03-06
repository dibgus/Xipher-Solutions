﻿namespace WindowsFormsApplication1
{
    partial class SetCipher
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.txtCipher = new System.Windows.Forms.TextBox();
            this.btnApply = new System.Windows.Forms.Button();
            this.btnHelp = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.btnOk = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            this.txtFilePath = new System.Windows.Forms.TextBox();
            this.btnSelectFile = new System.Windows.Forms.Button();
            this.btnGenerateHash = new System.Windows.Forms.Button();
            this.btnHashCipher = new System.Windows.Forms.Button();
            this.ckbxIsHash = new System.Windows.Forms.CheckBox();
            this.SuspendLayout();
            // 
            // txtCipher
            // 
            this.txtCipher.Location = new System.Drawing.Point(112, 54);
            this.txtCipher.Name = "txtCipher";
            this.txtCipher.ScrollBars = System.Windows.Forms.ScrollBars.Horizontal;
            this.txtCipher.Size = new System.Drawing.Size(266, 26);
            this.txtCipher.TabIndex = 1;
            // 
            // btnApply
            // 
            this.btnApply.Location = new System.Drawing.Point(16, 237);
            this.btnApply.Name = "btnApply";
            this.btnApply.Size = new System.Drawing.Size(122, 39);
            this.btnApply.TabIndex = 2;
            this.btnApply.Text = "Apply";
            this.btnApply.UseVisualStyleBackColor = true;
            this.btnApply.Click += new System.EventHandler(this.btnApply_Click);
            // 
            // btnHelp
            // 
            this.btnHelp.Font = new System.Drawing.Font("Microsoft Sans Serif", 14F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnHelp.Location = new System.Drawing.Point(177, 227);
            this.btnHelp.Name = "btnHelp";
            this.btnHelp.Size = new System.Drawing.Size(41, 50);
            this.btnHelp.TabIndex = 3;
            this.btnHelp.Text = "?";
            this.btnHelp.UseVisualStyleBackColor = true;
            this.btnHelp.Click += new System.EventHandler(this.btnHelp_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(47, 57);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(59, 20);
            this.label1.TabIndex = 4;
            this.label1.Text = "Cipher:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 13F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(22, 9);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(233, 30);
            this.label2.TabIndex = 5;
            this.label2.Text = "Encryption Settings";
            // 
            // btnOk
            // 
            this.btnOk.Location = new System.Drawing.Point(256, 237);
            this.btnOk.Name = "btnOk";
            this.btnOk.Size = new System.Drawing.Size(122, 39);
            this.btnOk.TabIndex = 8;
            this.btnOk.Text = "Ok";
            this.btnOk.UseVisualStyleBackColor = true;
            this.btnOk.Click += new System.EventHandler(this.btnOk_Click);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(17, 94);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(89, 20);
            this.label4.TabIndex = 9;
            this.label4.Text = "Media File: ";
            // 
            // txtFilePath
            // 
            this.txtFilePath.Location = new System.Drawing.Point(112, 91);
            this.txtFilePath.Name = "txtFilePath";
            this.txtFilePath.ReadOnly = true;
            this.txtFilePath.Size = new System.Drawing.Size(185, 26);
            this.txtFilePath.TabIndex = 10;
            // 
            // btnSelectFile
            // 
            this.btnSelectFile.Location = new System.Drawing.Point(303, 88);
            this.btnSelectFile.Name = "btnSelectFile";
            this.btnSelectFile.Size = new System.Drawing.Size(75, 37);
            this.btnSelectFile.TabIndex = 11;
            this.btnSelectFile.Text = "Select";
            this.btnSelectFile.UseVisualStyleBackColor = true;
            this.btnSelectFile.Click += new System.EventHandler(this.btnSelectFile_Click);
            // 
            // btnGenerateHash
            // 
            this.btnGenerateHash.Location = new System.Drawing.Point(16, 165);
            this.btnGenerateHash.Name = "btnGenerateHash";
            this.btnGenerateHash.Size = new System.Drawing.Size(122, 66);
            this.btnGenerateHash.TabIndex = 12;
            this.btnGenerateHash.Text = "Hash Generator";
            this.btnGenerateHash.UseVisualStyleBackColor = true;
            this.btnGenerateHash.Click += new System.EventHandler(this.btnGenerateHash_Click);
            // 
            // btnHashCipher
            // 
            this.btnHashCipher.Location = new System.Drawing.Point(256, 165);
            this.btnHashCipher.Name = "btnHashCipher";
            this.btnHashCipher.Size = new System.Drawing.Size(122, 66);
            this.btnHashCipher.TabIndex = 13;
            this.btnHashCipher.Text = "Create Hash From Cipher";
            this.btnHashCipher.UseVisualStyleBackColor = true;
            this.btnHashCipher.Click += new System.EventHandler(this.btnHashCipher_Click);
            // 
            // ckbxIsHash
            // 
            this.ckbxIsHash.AutoSize = true;
            this.ckbxIsHash.Location = new System.Drawing.Point(134, 130);
            this.ckbxIsHash.Name = "ckbxIsHash";
            this.ckbxIsHash.Size = new System.Drawing.Size(156, 24);
            this.ckbxIsHash.TabIndex = 14;
            this.ckbxIsHash.Text = "Cipher is Hashed";
            this.ckbxIsHash.UseVisualStyleBackColor = true;
            this.ckbxIsHash.CheckedChanged += new System.EventHandler(this.ckbxIsHash_CheckedChanged);
            // 
            // SetCipher
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(401, 304);
            this.Controls.Add(this.ckbxIsHash);
            this.Controls.Add(this.btnHashCipher);
            this.Controls.Add(this.btnGenerateHash);
            this.Controls.Add(this.btnSelectFile);
            this.Controls.Add(this.txtFilePath);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.btnOk);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.btnHelp);
            this.Controls.Add(this.btnApply);
            this.Controls.Add(this.txtCipher);
            this.Name = "SetCipher";
            this.Load += new System.EventHandler(this.SetCipher_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox txtCipher;
        private System.Windows.Forms.Button btnApply;
        private System.Windows.Forms.Button btnHelp;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button btnOk;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox txtFilePath;
        private System.Windows.Forms.Button btnSelectFile;
        private System.Windows.Forms.Button btnGenerateHash;
        private System.Windows.Forms.Button btnHashCipher;
        private System.Windows.Forms.CheckBox ckbxIsHash;
    }
}