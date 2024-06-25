namespace Drakensang_Injector
{
    partial class Settings
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Settings));
            this.passwordTextBox = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.saveBtn = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.dllTextBox = new System.Windows.Forms.TextBox();
            this.showPasswordBtn = new System.Windows.Forms.Button();
            this.searchDllBtn = new System.Windows.Forms.Button();
            this.dllFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.searchExeBtn = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.exeTextBox = new System.Windows.Forms.TextBox();
            this.exeFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.serverComboBox = new System.Windows.Forms.ComboBox();
            this.label4 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // passwordTextBox
            // 
            this.passwordTextBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.passwordTextBox.Location = new System.Drawing.Point(91, 12);
            this.passwordTextBox.Name = "passwordTextBox";
            this.passwordTextBox.Size = new System.Drawing.Size(486, 23);
            this.passwordTextBox.TabIndex = 0;
            this.passwordTextBox.UseSystemPasswordChar = true;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.label1.Location = new System.Drawing.Point(10, 15);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(73, 17);
            this.label1.TabIndex = 1;
            this.label1.Text = "Password:";
            // 
            // saveBtn
            // 
            this.saveBtn.Location = new System.Drawing.Point(500, 107);
            this.saveBtn.Name = "saveBtn";
            this.saveBtn.Size = new System.Drawing.Size(146, 26);
            this.saveBtn.TabIndex = 5;
            this.saveBtn.Text = "save settings";
            this.saveBtn.UseVisualStyleBackColor = true;
            this.saveBtn.Click += new System.EventHandler(this.saveBtn_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.label2.Location = new System.Drawing.Point(10, 44);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(61, 17);
            this.label2.TabIndex = 4;
            this.label2.Text = "Dll Path:";
            // 
            // dllTextBox
            // 
            this.dllTextBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.dllTextBox.Location = new System.Drawing.Point(91, 41);
            this.dllTextBox.Name = "dllTextBox";
            this.dllTextBox.Size = new System.Drawing.Size(486, 23);
            this.dllTextBox.TabIndex = 3;
            // 
            // showPasswordBtn
            // 
            this.showPasswordBtn.Location = new System.Drawing.Point(583, 12);
            this.showPasswordBtn.Name = "showPasswordBtn";
            this.showPasswordBtn.Size = new System.Drawing.Size(63, 23);
            this.showPasswordBtn.TabIndex = 10;
            this.showPasswordBtn.Text = "show";
            this.showPasswordBtn.UseVisualStyleBackColor = true;
            this.showPasswordBtn.Click += new System.EventHandler(this.showPasswordBtn_Click);
            // 
            // searchDllBtn
            // 
            this.searchDllBtn.Location = new System.Drawing.Point(583, 41);
            this.searchDllBtn.Name = "searchDllBtn";
            this.searchDllBtn.Size = new System.Drawing.Size(63, 23);
            this.searchDllBtn.TabIndex = 11;
            this.searchDllBtn.Text = "search";
            this.searchDllBtn.UseVisualStyleBackColor = true;
            this.searchDllBtn.Click += new System.EventHandler(this.searchDllBtn_Click);
            // 
            // dllFileDialog
            // 
            this.dllFileDialog.FileName = "fileDialog";
            this.dllFileDialog.Filter = "DLL Files|*.dll";
            this.dllFileDialog.Title = "Select your cheat";
            // 
            // searchExeBtn
            // 
            this.searchExeBtn.Location = new System.Drawing.Point(583, 70);
            this.searchExeBtn.Name = "searchExeBtn";
            this.searchExeBtn.Size = new System.Drawing.Size(63, 23);
            this.searchExeBtn.TabIndex = 14;
            this.searchExeBtn.Text = "search";
            this.searchExeBtn.UseVisualStyleBackColor = true;
            this.searchExeBtn.Click += new System.EventHandler(this.searchExeBtn_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.label3.Location = new System.Drawing.Point(10, 73);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(75, 17);
            this.label3.TabIndex = 13;
            this.label3.Text = "DSO Path:";
            // 
            // exeTextBox
            // 
            this.exeTextBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.exeTextBox.Location = new System.Drawing.Point(91, 70);
            this.exeTextBox.Name = "exeTextBox";
            this.exeTextBox.Size = new System.Drawing.Size(486, 23);
            this.exeTextBox.TabIndex = 12;
            // 
            // exeFileDialog
            // 
            this.exeFileDialog.FileName = "fileDialog";
            this.exeFileDialog.Filter = "EXE Files|*.exe";
            this.exeFileDialog.Title = "Select your drakensang path";
            // 
            // serverComboBox
            // 
            this.serverComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.serverComboBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.serverComboBox.FormattingEnabled = true;
            this.serverComboBox.Items.AddRange(new object[] {
            "Server 1",
            "Server 2",
            "Server 3",
            "Server 4",
            "Server 5",
            "Server 6"});
            this.serverComboBox.Location = new System.Drawing.Point(165, 109);
            this.serverComboBox.Name = "serverComboBox";
            this.serverComboBox.Size = new System.Drawing.Size(156, 24);
            this.serverComboBox.TabIndex = 15;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.label4.Location = new System.Drawing.Point(10, 112);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(149, 17);
            this.label4.TabIndex = 16;
            this.label4.Text = "Server Position in List:";
            // 
            // Settings
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(658, 145);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.serverComboBox);
            this.Controls.Add(this.searchExeBtn);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.exeTextBox);
            this.Controls.Add(this.searchDllBtn);
            this.Controls.Add(this.showPasswordBtn);
            this.Controls.Add(this.saveBtn);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.dllTextBox);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.passwordTextBox);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "Settings";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Settings";
            this.Load += new System.EventHandler(this.Settings_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox passwordTextBox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button saveBtn;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox dllTextBox;
        private System.Windows.Forms.Button showPasswordBtn;
        private System.Windows.Forms.Button searchDllBtn;
        private System.Windows.Forms.OpenFileDialog dllFileDialog;
        private System.Windows.Forms.Button searchExeBtn;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox exeTextBox;
        private System.Windows.Forms.OpenFileDialog exeFileDialog;
        private System.Windows.Forms.ComboBox serverComboBox;
        private System.Windows.Forms.Label label4;
    }
}