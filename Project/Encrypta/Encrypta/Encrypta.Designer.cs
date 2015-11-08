namespace WindowsFormsApplication1
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
            this.ckbxCopyClipboard = new System.Windows.Forms.CheckBox();
            this.button1 = new System.Windows.Forms.Button();
            this.btnToggleEncryption = new System.Windows.Forms.Button();
            this.btnSelectFile = new System.Windows.Forms.Button();
            this.txtPath = new System.Windows.Forms.TextBox();
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
            this.lblInput.Size = new System.Drawing.Size(123, 20);
            this.lblInput.TabIndex = 5;
            this.lblInput.Text = "Item to encrypt: ";
            // 
            // btnEncrypt
            // 
            this.btnEncrypt.Location = new System.Drawing.Point(349, 216);
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
            this.btnSetCipher.Location = new System.Drawing.Point(177, 216);
            this.btnSetCipher.Name = "btnSetCipher";
            this.btnSetCipher.Size = new System.Drawing.Size(133, 51);
            this.btnSetCipher.TabIndex = 9;
            this.btnSetCipher.Text = "Set Cipher";
            this.btnSetCipher.UseVisualStyleBackColor = true;
            this.btnSetCipher.Click += new System.EventHandler(this.btnSetCipher_Click);
            // 
            // btnInput
            // 
            this.btnInput.Location = new System.Drawing.Point(177, 159);
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
            // ckbxCopyClipboard
            // 
            this.ckbxCopyClipboard.AutoSize = true;
            this.ckbxCopyClipboard.Location = new System.Drawing.Point(11, 186);
            this.ckbxCopyClipboard.Name = "ckbxCopyClipboard";
            this.ckbxCopyClipboard.Size = new System.Drawing.Size(160, 24);
            this.ckbxCopyClipboard.TabIndex = 12;
            this.ckbxCopyClipboard.Text = "Copy to Clipboard";
            this.ckbxCopyClipboard.UseVisualStyleBackColor = true;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(27, 130);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 50);
            this.button1.TabIndex = 13;
            this.button1.Text = "Test Func";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // btnToggleEncryption
            // 
            this.btnToggleEncryption.Location = new System.Drawing.Point(349, 159);
            this.btnToggleEncryption.Name = "btnToggleEncryption";
            this.btnToggleEncryption.Size = new System.Drawing.Size(134, 51);
            this.btnToggleEncryption.TabIndex = 14;
            this.btnToggleEncryption.Text = "Toggle";
            this.btnToggleEncryption.UseVisualStyleBackColor = true;
            this.btnToggleEncryption.Click += new System.EventHandler(this.btnToggleEncryption_Click);
            // 
            // btnSelectFile
            // 
            this.btnSelectFile.Location = new System.Drawing.Point(391, 74);
            this.btnSelectFile.Name = "btnSelectFile";
            this.btnSelectFile.Size = new System.Drawing.Size(105, 35);
            this.btnSelectFile.TabIndex = 15;
            this.btnSelectFile.Text = "Select File...";
            this.btnSelectFile.UseVisualStyleBackColor = true;
            this.btnSelectFile.Visible = false;
            this.btnSelectFile.Click += new System.EventHandler(this.btnSelectFile_Click);
            // 
            // txtPath
            // 
            this.txtPath.Location = new System.Drawing.Point(169, 78);
            this.txtPath.Name = "txtPath";
            this.txtPath.ReadOnly = true;
            this.txtPath.Size = new System.Drawing.Size(216, 26);
            this.txtPath.TabIndex = 16;
            this.txtPath.Visible = false;
            // 
            // frmMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(545, 364);
            this.Controls.Add(this.txtPath);
            this.Controls.Add(this.btnSelectFile);
            this.Controls.Add(this.btnToggleEncryption);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.ckbxCopyClipboard);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.btnInput);
            this.Controls.Add(this.btnSetCipher);
            this.Controls.Add(this.txtEncrypted);
            this.Controls.Add(this.Label1);
            this.Controls.Add(this.btnEncrypt);
            this.Controls.Add(this.lblInput);
            this.Controls.Add(this.txtInput);
            this.Name = "frmMain";
            this.Text = "`";
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
        private System.Windows.Forms.CheckBox ckbxCopyClipboard;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button btnToggleEncryption;
        private System.Windows.Forms.Button btnSelectFile;
        private System.Windows.Forms.TextBox txtPath;
    }
}

