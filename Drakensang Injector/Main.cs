using System;
using System.Diagnostics;
using System.IO;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Windows.Forms;

namespace Drakensang_Injector {
    public partial class Main : Form {
        string configFile = "dsoloader.config",
            dllPath = "",
            clientPassword = "",
            clientPath = "",
            clientServer = "";
        int exitId = 0;

        const int MOUSEEVENTF_LEFTDOWN = 0x02;
        const int MOUSEEVENTF_LEFTUP = 0x04;
        const int PROCESS_CREATE_THREAD = 0x0002;
        const int PROCESS_QUERY_INFORMATION = 0x0400;
        const int PROCESS_VM_OPERATION = 0x0008;
        const int PROCESS_VM_WRITE = 0x0020;
        const int PROCESS_VM_READ = 0x0010;


        [DllImport("user32.dll", SetLastError = true)]
        static extern bool SetCursorPos(int x, int y);

        [DllImport("user32.dll", SetLastError = true)]
        static extern bool mouse_event(uint dwFlags, int dx, int dy, int dwData, int dwExtraInfo);

        [DllImport("kernel32.dll", SetLastError = true)]
        static extern IntPtr OpenProcess(uint dwDesiredAccess, int bInheritHandle, uint dwProcessId);

        [DllImport("kernel32.dll", SetLastError = true)]
        static extern int CloseHandle(IntPtr hObject);

        [DllImport("kernel32.dll", SetLastError = true)]
        static extern IntPtr GetProcAddress(IntPtr hModule, string lpProcName);

        [DllImport("kernel32.dll", SetLastError = true)]
        static extern IntPtr GetModuleHandle(string lpModuleName);

        [DllImport("kernel32.dll", SetLastError = true)]
        static extern IntPtr VirtualAllocEx(IntPtr hProcess, IntPtr lpAddress, IntPtr dwSize, uint flAllocationType, uint flProtect);

        [DllImport("kernel32.dll", SetLastError = true)]
        static extern int WriteProcessMemory(IntPtr hProcess, IntPtr lpBaseAddress, byte[] buffer, uint size, int lpNumberOfBytesWritten);

        [DllImport("kernel32.dll", SetLastError = true)]
        static extern IntPtr CreateRemoteThread(IntPtr hProcess, IntPtr lpThreadAttribute, IntPtr dwStackSize, IntPtr lpStartAddress,
            IntPtr lpParameter, uint dwCreationFlags, IntPtr lpThreadId);

        public Main() {
            InitializeComponent();
        }

        private void updateFromConfig() {
            if (File.Exists(configFile)) {
                string configText = File.ReadAllText(configFile);
                try
                {
                    clientPassword = configText.Split('|')[0];
                    dllPath = configText.Split('|')[1];
                    clientPath = configText.Split('|')[2];
                    clientServer = configText.Split('|')[3];
                } catch {
                    MessageBox.Show("Your config file is malformed and cant be loaded! Please delete it and start the injector again.");
                    Application.Exit();
                }
            }
        }

        private void startGameBtn_Click(object sender, EventArgs e) {
            if (clientPath == String.Empty) {
                MessageBox.Show("Client path is null");
                return;
            }

            ProcessStartInfo dsoInfo = new ProcessStartInfo(clientPath);
            dsoInfo.WindowStyle = ProcessWindowStyle.Maximized;
            dsoInfo.Arguments = "-x86_64";
            Process.Start(dsoInfo);

            if (clientPassword == String.Empty) {
                MessageBox.Show("Client password is null");
                return;
            }

            Thread.Sleep(1700);

            SetCursorPos(721, 209);
            Thread.Sleep(500);

            mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, Cursor.Position.X, Cursor.Position.Y, 0, 0);
            Thread.Sleep(300);

            SendKeys.SendWait(clientPassword);
            Thread.Sleep(300);

            SendKeys.SendWait("{ENTER}");

            if (clientServer == String.Empty) {
                MessageBox.Show("Client server is null");
                return;
            }

            Thread.Sleep(600);
            switch (clientServer) {
                case "Server 2": {
                        SetCursorPos(795, 366);
                        break;
                    }
                case "Server 3": {
                        SetCursorPos(795, 392);
                        break;
                    }
                case "Server 4": {
                        SetCursorPos(795, 423);
                        break;
                    }
                case "Server 5": {
                        SetCursorPos(795, 451);
                        break;
                    }
                case "Server 6": {
                        SetCursorPos(795, 488);
                        break;
                    }
                default: {
                        SetCursorPos(795, 330);
                        break;
                    }
            }

            Thread.Sleep(1500);

            mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, Cursor.Position.X, Cursor.Position.Y, 0, 0);
            Thread.Sleep(300);

        }

        private void exitCorrectlyBtn_Click(object sender, EventArgs e)
        {
            if (exitId == 0) {
                MessageBox.Show("Game is not running");
                return;
            }

            try {
                Process proc = Process.GetProcessById(exitId);
                proc.Kill();
                MessageBox.Show("Game process killed successfully!");
            } catch (ArgumentException) {
                MessageBox.Show("Process was already killed.");
            }
        }

        private void injectBtn_Click(object sender, EventArgs e) {
            try {
                if (!File.Exists(dllPath)) {
                    MessageBox.Show("Incorrect dll path.");
                    return;
                }

                Process droProc = Process.GetProcessesByName("dro_client64")[0];

                if(droProc == null) {
                    MessageBox.Show("Can't find \"dro_client64\", please open the game.");
                    return;
                }
                exitId = droProc.Id;
                uint pid = (uint)droProc.Id;

                IntPtr procHandle = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_WRITE | PROCESS_VM_READ, 1, pid);
                if (procHandle == IntPtr.Zero) {
                    MessageBox.Show("OpenProcess failed.");
                    return;
                }

                IntPtr llaAddress = GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");

                if (llaAddress == IntPtr.Zero) {
                    MessageBox.Show("Failed to get LoadLibraryA.");
                    return;
                }

                IntPtr lpAddress = VirtualAllocEx(procHandle, (IntPtr)null, (IntPtr)dllPath.Length, (0x1000 | 0x2000), 0X40);

                if (lpAddress == IntPtr.Zero) {
                    MessageBox.Show("VirtualAllocEx failed.");
                    return;
                }

                byte[] dllBytes = Encoding.ASCII.GetBytes(dllPath);

                if (WriteProcessMemory(procHandle, lpAddress, dllBytes, (uint)dllBytes.Length, 0) == 0) {
                    MessageBox.Show("WriteProcessMemory failed.");
                    return;
                }

                if (CreateRemoteThread(procHandle, IntPtr.Zero, IntPtr.Zero, llaAddress, lpAddress, 0, IntPtr.Zero) == IntPtr.Zero) {
                    MessageBox.Show("CreateRemoteThread failed. Make sure the game is running.");
                    return;
                }

                CloseHandle(procHandle);
                MessageBox.Show("Injected successfully!");
            }
            catch (Exception ex) {
                MessageBox.Show("Could not inject! Error: " + ex.Message);
            }
        }

        private void settingsBtn_Click(object sender, EventArgs e)
        {
            Settings settings = new Settings();
            this.Enabled = false;
            settings.ShowDialog();
            updateFromConfig();
            this.Enabled = true;
        }

        private void Main_Load(object sender, EventArgs e)
        {
            updateFromConfig();
        }
    }
}
