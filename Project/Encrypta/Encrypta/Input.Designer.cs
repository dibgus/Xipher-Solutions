namespace WindowsFormsApplication1
{
    partial class Input
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
            this.rbtnFile = new System.Windows.Forms.RadioButton();
            this.label1 = new System.Windows.Forms.Label();
            this.rbtnString = new System.Windows.Forms.RadioButton();
            this.btnSubmit = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // rbtnFile
            // 
            this.rbtnFile.AutoSize = true;
            this.rbtnFile.Location = new System.Drawing.Point(35, 62);
            this.rbtnFile.Name = "rbtnFile";
            this.rbtnFile.Size = new System.Drawing.Size(59, 24);
            this.rbtnFile.TabIndex = 5;
            this.rbtnFile.Text = "File";
            this.rbtnFile.UseVisualStyleBackColor = true;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(35, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(103, 20);
            this.label1.TabIndex = 4;
            this.label1.Text = "Data Format:";
            // 
            // rbtnString
            // 
            this.rbtnString.AutoSize = true;
            this.rbtnString.Checked = true;
            this.rbtnString.Location = new System.Drawing.Point(35, 32);
            this.rbtnString.Name = "rbtnString";
            this.rbtnString.Size = new System.Drawing.Size(103, 24);
            this.rbtnString.TabIndex = 3;
            this.rbtnString.TabStop = true;
            this.rbtnString.Text = "Sentence";
            this.rbtnString.UseVisualStyleBackColor = true;
            // 
            // btnSubmit
            // 
            this.btnSubmit.Location = new System.Drawing.Point(63, 92);
            this.btnSubmit.Name = "btnSubmit";
            this.btnSubmit.Size = new System.Drawing.Size(75, 34);
            this.btnSubmit.TabIndex = 6;
            this.btnSubmit.Text = "Update";
            this.btnSubmit.UseVisualStyleBackColor = true;
            this.btnSubmit.Click += new System.EventHandler(this.btnSubmit_Click);
            // 
            // Input
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(188, 138);
            this.Controls.Add(this.btnSubmit);
            this.Controls.Add(this.rbtnFile);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.rbtnString);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.MaximizeBox = false;
            this.Name = "Input";
            this.Text = "Input";
            this.TopMost = true;
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Input_FormClosed);
            this.Load += new System.EventHandler(this.Input_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.RadioButton rbtnFile;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.RadioButton rbtnString;
        private System.Windows.Forms.Button btnSubmit;
    }
}