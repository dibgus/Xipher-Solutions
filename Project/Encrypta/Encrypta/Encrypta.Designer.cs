﻿namespace WindowsFormsApplication1
{
    partial class frmMain
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
            this.txtInput = new System.Windows.Forms.TextBox();
            this.lblInput = new System.Windows.Forms.Label();
            this.btnEncrypt = new System.Windows.Forms.Button();
            this.Label1 = new System.Windows.Forms.Label();
            this.txtEncrypted = new System.Windows.Forms.TextBox();
            this.btnSetCipher = new System.Windows.Forms.Button();
            this.btnInput = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // txtInput
            // 
            this.txtInput.Location = new System.Drawing.Point(169, 78);
            this.txtInput.Multiline = true;
            this.txtInput.Name = "txtInput";
            this.txtInput.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.txtInput.Size = new System.Drawing.Size(327, 75);
            this.txtInput.TabIndex = 4;
            // 
            // lblInput
            // 
            this.lblInput.AutoSize = true;
            this.lblInput.Location = new System.Drawing.Point(23, 81);
            this.lblInput.Name = "lblInput";
            this.lblInput.Size = new System.Drawing.Size(138, 20);
            this.lblInput.TabIndex = 5;
            this.lblInput.Text = "Enter a Sentence:";
            // 
            // btnEncrypt
            // 
            this.btnEncrypt.Location = new System.Drawing.Point(378, 216);
            this.btnEncrypt.Name = "btnEncrypt";
            this.btnEncrypt.Size = new System.Drawing.Size(134, 51);
            this.btnEncrypt.TabIndex = 6;
            this.btnEncrypt.Text = "Encrypt";
            this.btnEncrypt.UseVisualStyleBackColor = true;
            this.btnEncrypt.Click += new System.EventHandler(this.btnEncrypt_Click);
            // 
            // Label1
            // 
            this.Label1.AutoSize = true;
            this.Label1.Location = new System.Drawing.Point(72, 276);
            this.Label1.Name = "Label1";
            this.Label1.Size = new System.Drawing.Size(89, 20);
            this.Label1.TabIndex = 7;
            this.Label1.Text = "Encrypted: ";
            // 
            // txtEncrypted
            // 
            this.txtEncrypted.Location = new System.Drawing.Point(169, 273);
            this.txtEncrypted.Multiline = true;
            this.txtEncrypted.Name = "txtEncrypted";
            this.txtEncrypted.ReadOnly = true;
            this.txtEncrypted.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.txtEncrypted.Size = new System.Drawing.Size(343, 75);
            this.txtEncrypted.TabIndex = 8;
            // 
            // btnSetCipher
            // 
            this.btnSetCipher.Location = new System.Drawing.Point(169, 216);
            this.btnSetCipher.Name = "btnSetCipher";
            this.btnSetCipher.Size = new System.Drawing.Size(133, 51);
            this.btnSetCipher.TabIndex = 9;
            this.btnSetCipher.Text = "Set Cipher";
            this.btnSetCipher.UseVisualStyleBackColor = true;
            this.btnSetCipher.Click += new System.EventHandler(this.btnSetCipher_Click);
            // 
            // btnInput
            // 
            this.btnInput.Location = new System.Drawing.Point(269, 159);
            this.btnInput.Name = "btnInput";
            this.btnInput.Size = new System.Drawing.Size(133, 51);
            this.btnInput.TabIndex = 10;
            this.btnInput.Text = "Input Settings";
            this.btnInput.UseVisualStyleBackColor = true;
            this.btnInput.Click += new System.EventHandler(this.btnInput_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 16F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(4, 13);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(143, 37);
            this.label2.TabIndex = 11;
            this.label2.Text = "Encrypta";
            // 
            // frmMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(545, 364);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.btnInput);
            this.Controls.Add(this.btnSetCipher);
            this.Controls.Add(this.txtEncrypted);
            this.Controls.Add(this.Label1);
            this.Controls.Add(this.btnEncrypt);
            this.Controls.Add(this.lblInput);
            this.Controls.Add(this.txtInput);
            this.Name = "frmMain";
            this.Load += new System.EventHandler(this.frmMain_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.TextBox txtInput;
        private System.Windows.Forms.Label lblInput;
        private System.Windows.Forms.Button btnEncrypt;
        private System.Windows.Forms.Label Label1;
        private System.Windows.Forms.TextBox txtEncrypted;
        private System.Windows.Forms.Button btnSetCipher;
        private System.Windows.Forms.Button btnInput;
        private System.Windows.Forms.Label label2;
    }
}

