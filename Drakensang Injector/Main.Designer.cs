namespace Drakensang_Injector
{
    partial class Main
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Main));
            this.injectBtn = new System.Windows.Forms.Button();
            this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.settingsBtn = new System.Windows.Forms.Button();
            this.startGameBtn = new System.Windows.Forms.Button();
            this.exitCorrectlyBtn = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // injectBtn
            // 
            this.injectBtn.Location = new System.Drawing.Point(211, 16);
            this.injectBtn.Name = "injectBtn";
            this.injectBtn.Size = new System.Drawing.Size(90, 30);
            this.injectBtn.TabIndex = 2;
            this.injectBtn.Text = "inject cheat";
            this.injectBtn.UseVisualStyleBackColor = true;
            this.injectBtn.Click += new System.EventHandler(this.injectBtn_Click);
            // 
            // openFileDialog
            // 
            this.openFileDialog.FileName = "fileDialog";
            this.openFileDialog.Filter = "DLL Files|*.dll";
            this.openFileDialog.Title = "Select your cheat";
            // 
            // settingsBtn
            // 
            this.settingsBtn.Location = new System.Drawing.Point(10, 16);
            this.settingsBtn.Name = "settingsBtn";
            this.settingsBtn.Size = new System.Drawing.Size(90, 30);
            this.settingsBtn.TabIndex = 6;
            this.settingsBtn.Text = "settings";
            this.settingsBtn.UseVisualStyleBackColor = true;
            this.settingsBtn.Click += new System.EventHandler(this.settingsBtn_Click);
            // 
            // startGameBtn
            // 
            this.startGameBtn.Location = new System.Drawing.Point(111, 16);
            this.startGameBtn.Name = "startGameBtn";
            this.startGameBtn.Size = new System.Drawing.Size(90, 30);
            this.startGameBtn.TabIndex = 7;
            this.startGameBtn.Text = "auto start";
            this.startGameBtn.UseVisualStyleBackColor = true;
            this.startGameBtn.Click += new System.EventHandler(this.startGameBtn_Click);
            // 
            // exitCorrectlyBtn
            // 
            this.exitCorrectlyBtn.Location = new System.Drawing.Point(310, 16);
            this.exitCorrectlyBtn.Name = "exitCorrectlyBtn";
            this.exitCorrectlyBtn.Size = new System.Drawing.Size(90, 30);
            this.exitCorrectlyBtn.TabIndex = 8;
            this.exitCorrectlyBtn.Text = "exit correctly";
            this.exitCorrectlyBtn.UseVisualStyleBackColor = true;
            this.exitCorrectlyBtn.Click += new System.EventHandler(this.exitCorrectlyBtn_Click);
            // 
            // Main
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(413, 63);
            this.Controls.Add(this.exitCorrectlyBtn);
            this.Controls.Add(this.startGameBtn);
            this.Controls.Add(this.settingsBtn);
            this.Controls.Add(this.injectBtn);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "Main";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Drakensang Loader";
            this.Load += new System.EventHandler(this.Main_Load);
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.Button injectBtn;
        private System.Windows.Forms.OpenFileDialog openFileDialog;
        private System.Windows.Forms.Button settingsBtn;
        private System.Windows.Forms.Button startGameBtn;
        private System.Windows.Forms.Button exitCorrectlyBtn;
    }
}

