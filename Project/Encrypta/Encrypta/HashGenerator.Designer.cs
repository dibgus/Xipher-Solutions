namespace WindowsFormsApplication1
{
    partial class HashGenerator
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
            this.btnGenerate = new System.Windows.Forms.Button();
            this.txtHash = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.txtSeed = new System.Windows.Forms.TextBox();
            this.btnHelp = new System.Windows.Forms.Button();
            this.nudLength = new System.Windows.Forms.NumericUpDown();
            this.ckbxCopyClipboard = new System.Windows.Forms.CheckBox();
            ((System.ComponentModel.ISupportInitialize)(this.nudLength)).BeginInit();
            this.SuspendLayout();
            // 
            // btnGenerate
            // 
            this.btnGenerate.Location = new System.Drawing.Point(118, 180);
            this.btnGenerate.Name = "btnGenerate";
            this.btnGenerate.Size = new System.Drawing.Size(131, 35);
            this.btnGenerate.TabIndex = 0;
            this.btnGenerate.Text = "Generate Hash";
            this.btnGenerate.UseVisualStyleBackColor = true;
            this.btnGenerate.Click += new System.EventHandler(this.btnGenerate_Click);
            // 
            // txtHash
            // 
            this.txtHash.Location = new System.Drawing.Point(23, 220);
            this.txtHash.Name = "txtHash";
            this.txtHash.ReadOnly = true;
            this.txtHash.Size = new System.Drawing.Size(383, 26);
            this.txtHash.TabIndex = 1;
            this.txtHash.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(19, 93);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(67, 20);
            this.label1.TabIndex = 2;
            this.label1.Text = "Length: ";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(19, 137);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(100, 20);
            this.label2.TabIndex = 4;
            this.label2.Text = "Force Seed: ";
            // 
            // txtSeed
            // 
            this.txtSeed.Location = new System.Drawing.Point(118, 137);
            this.txtSeed.Name = "txtSeed";
            this.txtSeed.Size = new System.Drawing.Size(192, 26);
            this.txtSeed.TabIndex = 5;
            // 
            // btnHelp
            // 
            this.btnHelp.Location = new System.Drawing.Point(255, 182);
            this.btnHelp.Name = "btnHelp";
            this.btnHelp.Size = new System.Drawing.Size(38, 33);
            this.btnHelp.TabIndex = 6;
            this.btnHelp.Text = "?";
            this.btnHelp.UseVisualStyleBackColor = true;
            this.btnHelp.Click += new System.EventHandler(this.btnHelp_Click);
            // 
            // nudLength
            // 
            this.nudLength.Location = new System.Drawing.Point(118, 93);
            this.nudLength.Name = "nudLength";
            this.nudLength.Size = new System.Drawing.Size(90, 26);
            this.nudLength.TabIndex = 7;
            this.nudLength.Value = new decimal(new int[] {
            5,
            0,
            0,
            0});
            // 
            // ckbxCopyClipboard
            // 
            this.ckbxCopyClipboard.AutoSize = true;
            this.ckbxCopyClipboard.Location = new System.Drawing.Point(249, 95);
            this.ckbxCopyClipboard.Name = "ckbxCopyClipboard";
            this.ckbxCopyClipboard.Size = new System.Drawing.Size(157, 24);
            this.ckbxCopyClipboard.TabIndex = 8;
            this.ckbxCopyClipboard.Text = "Copy to clipboard";
            this.ckbxCopyClipboard.UseVisualStyleBackColor = true;
            // 
            // HashGenerator
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(429, 269);
            this.Controls.Add(this.ckbxCopyClipboard);
            this.Controls.Add(this.nudLength);
            this.Controls.Add(this.btnHelp);
            this.Controls.Add(this.txtSeed);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.txtHash);
            this.Controls.Add(this.btnGenerate);
            this.Name = "HashGenerator";
            this.Text = "Hash Generator";
            ((System.ComponentModel.ISupportInitialize)(this.nudLength)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnGenerate;
        private System.Windows.Forms.TextBox txtHash;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox txtSeed;
        private System.Windows.Forms.Button btnHelp;
        private System.Windows.Forms.NumericUpDown nudLength;
        private System.Windows.Forms.CheckBox ckbxCopyClipboard;
    }
}