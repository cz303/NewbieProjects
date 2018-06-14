using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Interop;
using System.Windows.Media;
using System.Windows.Media.Imaging;


namespace NixieWPF
{
    /// <summary>
    /// Логика взаимодействия для WindowBlack.xaml
    /// </summary>
    /// 


    public partial class WindowBlack : Window
    {

        [DllImport("user32.dll")]
        static extern IntPtr SetParent(IntPtr hWndChild, IntPtr hWndNewParent);

        [DllImport("user32.dll")]
        static extern int SetWindowLong(IntPtr hWnd, int nIndex, IntPtr dwNewLong);

        [DllImport("user32.dll", SetLastError = true)]
        static extern int GetWindowLong(IntPtr hWnd, int nIndex);

        [DllImport("user32.dll")]
        static extern bool GetClientRect(IntPtr hWnd, out System.Drawing.Rectangle lpRect);


        private System.Drawing.Point mouseLocation;
        short nscreen;
        bool IsPreviewMode = false;

        IntPtr PreviewWndHandle;

        public WindowBlack()
        {
            InitializeComponent();

            nscreen = 1;
            this.Cursor = Cursors.None;

            this.Loaded += new RoutedEventHandler(MainWindow_Loaded);
        }

        public WindowBlack(IntPtr PreviewHandle)
        {
            InitializeComponent();
            PreviewWndHandle = PreviewHandle;

            

            nscreen = 2;
            this.Cursor = Cursors.None;

            this.Loaded += new RoutedEventHandler(MainWindow_Loaded);
        }

        private void Window_MouseMove(object sender, MouseEventArgs e)
        {
            if (!IsPreviewMode)
            {
                if (!mouseLocation.IsEmpty)
                {
                    if (Math.Abs(mouseLocation.X - System.Windows.Forms.Control.MousePosition.X) > 7 ||
                    Math.Abs(mouseLocation.Y - System.Windows.Forms.Control.MousePosition.Y) > 7)
                        Application.Current.Shutdown();
                }
                mouseLocation = System.Windows.Forms.Control.MousePosition;
            }
        }


        void MainWindow_Loaded(object sender, RoutedEventArgs e)
        {
            if (nscreen == 2)
            {
              WindowInteropHelper helper = new WindowInteropHelper(this);
              IntPtr ptr = helper.Handle;

                
                             SetParent(ptr, PreviewWndHandle);
/*
                              helper = new WindowInteropHelper(this.Owner);
                              MessageBox.Show(helper.Handle + "," + PreviewWndHandle);

                              // Make this a child window so it will close when the parent dialog closes
                              // GWL_STYLE = -16, WS_CHILD = 0x40000000
                              SetWindowLong(ptr, -16, new IntPtr(GetWindowLong(ptr, -16) | 0x40000000));
              */
                // Place our window inside the parent  

                SetWindowLong(ptr, -16, new IntPtr(GetWindowLong(ptr, -16) | 0x40000000));

                Rectangle ParentRect;
                GetClientRect(PreviewWndHandle, out ParentRect);

                this.Topmost = false;
                this.Top = 0;
                this.Left = 0;
                this.Width = ParentRect.Width;
                this.Height = ParentRect.Height;


                IsPreviewMode = true;
             //   MessageBox.Show(this.Left.ToString() + " " + this.Top.ToString() + " " + this.Width.ToString() + " " + this.Height.ToString());

                MainWindow Clock = new MainWindow(PreviewWndHandle);
            //    MainWindow Clock = new MainWindow(this.Left, this.Top, ParentRect.Height, ParentRect.Width);
                Clock.Show(); 
            }
            else
            {
                foreach (System.Windows.Forms.Screen screen in System.Windows.Forms.Screen.AllScreens)
                {
                MainWindow screensaver = new MainWindow(screen.Bounds.Left, screen.Bounds.Top, screen.Bounds.Height, screen.Bounds.Width);
                screensaver.Show();
                }
                this.WindowState = WindowState.Normal;
                this.Left = System.Windows.Forms.SystemInformation.VirtualScreen.Left;
                this.Top = System.Windows.Forms.SystemInformation.VirtualScreen.Top;
                this.Width = System.Windows.Forms.SystemInformation.VirtualScreen.Width;
                this.Height = System.Windows.Forms.SystemInformation.VirtualScreen.Height;
            }
        }


        private void Window_Activated_1(object sender, EventArgs e)
        {
            
        }

        private void Window_KeyDown(object sender, KeyEventArgs e)
        {
            if (!IsPreviewMode) 
                Application.Current.Shutdown();
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            if (IsPreviewMode)
                Application.Current.Shutdown();
        }

        private void Window_GiveFeedback(object sender, GiveFeedbackEventArgs e)
        {

        }
    }
}
