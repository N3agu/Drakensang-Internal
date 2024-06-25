using System;
using System.IO;
using System.Windows.Forms;

namespace Drakensang_Injector {
    public partial class Settings : Form {
        string configFile = "dsoloader.config";
        bool showPassword = false;
        public Settings() {
            InitializeComponent();
        }

        private void showPasswordBtn_Click(object sender, EventArgs e) {
            if(showPassword == false) {
                passwordTextBox.UseSystemPasswordChar = false;
                showPasswordBtn.Text = "hide";
                showPassword = true;
            } else {
                passwordTextBox.UseSystemPasswordChar = true;
                showPasswordBtn.Text = "show";
                showPassword = false;
            }
        }

        private void searchDllBtn_Click(object sender, EventArgs e) {
            if (dllFileDialog.ShowDialog() == DialogResult.OK)
                dllTextBox.Text = dllFileDialog.FileName;
        }

        private void saveBtn_Click(object sender, EventArgs e) {
            if (!File.Exists(configFile)) File.Create(configFile).Close();

            if(passwordTextBox.Text == String.Empty || dllTextBox.Text == String.Empty || exeTextBox.Text == String.Empty || serverComboBox.Text == String.Empty) {
                MessageBox.Show("All fields are mandatory!");
                return;
            }

            File.WriteAllText(configFile, passwordTextBox.Text + "|" + dllTextBox.Text + "|" + exeTextBox.Text + "|" + serverComboBox.Text);
            MessageBox.Show("Settings updated");
            this.Close();
        }

        private void Settings_Load(object sender, EventArgs e) {
            serverComboBox.SelectedIndex = 0;
            if (File.Exists(configFile)) {
                string configText = File.ReadAllText(configFile);
                passwordTextBox.Text = configText.Split('|')[0];
                dllTextBox.Text = configText.Split('|')[1];
                exeTextBox.Text = configText.Split('|')[2];
                switch (configText.Split('|')[3]) {
                    case "Server 2": {
                            serverComboBox.SelectedIndex = 1;
                            break;
                        }
                    case "Server 3": {
                            serverComboBox.SelectedIndex = 2;
                            break;
                        }
                    case "Server 4": {
                            serverComboBox.SelectedIndex = 3;
                            break;
                        }
                    case "Server 5": {
                            serverComboBox.SelectedIndex = 4;
                            break;
                        }
                    case "Server 6": {
                            serverComboBox.SelectedIndex = 5;
                            break;
                        }
                    default: {
                            serverComboBox.SelectedIndex = 0;
                            break;
                        }
                }

            }
        }

        private void searchExeBtn_Click(object sender, EventArgs e) {
            if (exeFileDialog.ShowDialog() == DialogResult.OK)
                exeTextBox.Text = exeFileDialog.FileName;
        }
    }
}
