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
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.menSettings = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuSettingsInput = new System.Windows.Forms.ToolStripMenuItem();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.lblInput = new System.Windows.Forms.Label();
            this.btnEncrypt = new System.Windows.Forms.Button();
            this.Label1 = new System.Windows.Forms.Label();
            this.txtEncrypted = new System.Windows.Forms.TextBox();
            this.btnSetCipher = new System.Windows.Forms.Button();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(24, 24);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menSettings});
            this.menuStrip1.Location = new System.Drawing.Point(20, 60);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(438, 33);
            this.menuStrip1.TabIndex = 3;
            this.menuStrip1.Text = "menSettings";
            // 
            // menSettings
            // 
            this.menSettings.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnuSettingsInput});
            this.menSettings.Name = "menSettings";
            this.menSettings.Size = new System.Drawing.Size(88, 29);
            this.menSettings.Text = "Settings";
            // 
            // mnuSettingsInput
            // 
            this.mnuSettingsInput.Name = "mnuSettingsInput";
            this.mnuSettingsInput.Size = new System.Drawing.Size(211, 30);
            this.mnuSettingsInput.Text = "Input Type";
            this.mnuSettingsInput.Click += new System.EventHandler(this.mnuSettingsInput_Click);
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(169, 63);
            this.textBox1.Multiline = true;
            this.textBox1.Name = "textBox1";
            this.textBox1.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.textBox1.Size = new System.Drawing.Size(297, 75);
            this.textBox1.TabIndex = 4;
            // 
            // lblInput
            // 
            this.lblInput.AutoSize = true;
            this.lblInput.Location = new System.Drawing.Point(25, 109);
            this.lblInput.Name = "lblInput";
            this.lblInput.Size = new System.Drawing.Size(138, 20);
            this.lblInput.TabIndex = 5;
            this.lblInput.Text = "Enter a Sentence:";
            // 
            // btnEncrypt
            // 
            this.btnEncrypt.Location = new System.Drawing.Point(332, 144);
            this.btnEncrypt.Name = "btnEncrypt";
            this.btnEncrypt.Size = new System.Drawing.Size(134, 51);
            this.btnEncrypt.TabIndex = 6;
            this.btnEncrypt.Text = "Encrypt";
            this.btnEncrypt.UseVisualStyleBackColor = true;
            // 
            // Label1
            // 
            this.Label1.AutoSize = true;
            this.Label1.Location = new System.Drawing.Point(74, 204);
            this.Label1.Name = "Label1";
            this.Label1.Size = new System.Drawing.Size(89, 20);
            this.Label1.TabIndex = 7;
            this.Label1.Text = "Encrypted: ";
            // 
            // txtEncrypted
            // 
            this.txtEncrypted.Location = new System.Drawing.Point(169, 201);
            this.txtEncrypted.Multiline = true;
            this.txtEncrypted.Name = "txtEncrypted";
            this.txtEncrypted.ReadOnly = true;
            this.txtEncrypted.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.txtEncrypted.Size = new System.Drawing.Size(297, 75);
            this.txtEncrypted.TabIndex = 8;
            // 
            // btnSetCipher
            // 
            this.btnSetCipher.Location = new System.Drawing.Point(169, 144);
            this.btnSetCipher.Name = "btnSetCipher";
            this.btnSetCipher.Size = new System.Drawing.Size(134, 51);
            this.btnSetCipher.TabIndex = 9;
            this.btnSetCipher.Text = "Set Cipher";
            this.btnSetCipher.UseVisualStyleBackColor = true;
            // 
            // frmMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(478, 335);
            this.Controls.Add(this.btnSetCipher);
            this.Controls.Add(this.txtEncrypted);
            this.Controls.Add(this.Label1);
            this.Controls.Add(this.btnEncrypt);
            this.Controls.Add(this.lblInput);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "frmMain";
            this.Text = "Encrypta";
            this.Load += new System.EventHandler(this.frmMain_Load);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem menSettings;
        private System.Windows.Forms.ToolStripMenuItem mnuSettingsInput;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Label lblInput;
        private System.Windows.Forms.Button btnEncrypt;
        private System.Windows.Forms.Label Label1;
        private System.Windows.Forms.TextBox txtEncrypted;
        private System.Windows.Forms.Button btnSetCipher;
    }
}

