using System;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using WinForms = System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Windows.Interop;
using System.Drawing;

namespace NixieWPF
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>

    public partial class MainWindow : Window
    {
        private DateTime dt;
        string time;
        string temp;
        public bool HS = false, MS = false, SS = false;
        private MediaPlayer player = new MediaPlayer();
        short counter=0, counter2 = 0;
        short rand,rand2;
        double sto = 0.1;
        short [] STime = { 0, 0, 0, 0, 0, 0 };
        Random rnd1;
        private System.Drawing.Point mouseLocation;


        IntPtr PreviewWndHandle;
        [DllImport("winmm.dll")]
        static extern Int32 mciSendString(string command, StringBuilder buffer, int bufferSize, IntPtr hwndCallback);

        [DllImport("user32.dll")]
        static extern IntPtr SetParent(IntPtr hWndChild, IntPtr hWndNewParent);

        [DllImport("user32.dll")]
        static extern int SetWindowLong(IntPtr hWnd, int nIndex, IntPtr dwNewLong);

        [DllImport("user32.dll", SetLastError = true)]
        static extern int GetWindowLong(IntPtr hWnd, int nIndex);

        [DllImport("user32.dll")]
        static extern bool GetClientRect(IntPtr hWnd, out System.Drawing.Rectangle lpRect);


        System.Timers.Timer SetTimer = new System.Timers.Timer(150);
        System.Timers.Timer TickTimer = new System.Timers.Timer(30);
        System.Timers.Timer opacityTimer = new System.Timers.Timer(50);
        System.Timers.Timer EnterTimer = new System.Timers.Timer(50);

        Uri uriBg       =   new Uri(Properties.Settings.Default.fon, UriKind.Relative);
        Uri uriEnter    =   new Uri("./Resources/electricDrone.wav", UriKind.Relative);
        Uri uriExit     =   new Uri("./Resources/shutdown.wav", UriKind.Relative);
        Uri uriSpark    =   new Uri("./Resources/sparks.wav", UriKind.Relative);
        Uri uriTick     =   new Uri("./Resources/relay.wav", UriKind.Relative);
        Uri uriDigit;


        public MainWindow(double L, double T, double H, double W)
        {
            InitializeComponent();

            this.Left = L;
            this.Top = T;
            this.Top = this.Top + H / 3;
            this.Left = this.Left + W / 4.6;
            this.Width = W/1.8;
            this.Height = this.Width / 3.92;
            this.Opacity = 100;
            this.Topmost = true;
            this.Cursor = Cursors.None;

            HS = true; MS = true; SS = true;

            BgImage.Source = new BitmapImage(uriBg);

            Enter();
        }

        public MainWindow(IntPtr Handle)
        {
            InitializeComponent();
            PreviewWndHandle = Handle;

            this.Loaded += new RoutedEventHandler(MainWindow_Loaded1);
        }

        void MainWindow_Loaded1(object sender, RoutedEventArgs e)
        {
            WindowInteropHelper helper = new WindowInteropHelper(this);
            IntPtr ptr = helper.Handle;


            SetParent(ptr, PreviewWndHandle);
            SetWindowLong(ptr, -16, new IntPtr(GetWindowLong(ptr, -16) | 0x40000000));

            Rectangle ParentRect;

            GetClientRect(PreviewWndHandle, out ParentRect);

            this.WindowState = WindowState.Maximized;
            
            this.Top = 0 + ParentRect.Height / 3;
            this.Left = 0;

            this.WindowState = WindowState.Normal;

            this.Width = ParentRect.Width;
            this.Height = this.Width / 3.92;

            this.Topmost = true;
            this.Cursor = Cursors.None;

            

            BgImage.Source = new BitmapImage(uriBg);


            opacityTimer.Elapsed += new System.Timers.ElapsedEventHandler(opacityTimer_Elapsed);
            opacityTimer.AutoReset = true;
            opacityTimer.Enabled = true;
            opacityTimer.Start();
            Tick();

        }

        private void Window_MouseRightButtonUp(object sender, MouseButtonEventArgs e)
        {
            Application.Current.Shutdown();
        }

        private void Window_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if (e.ChangedButton == MouseButton.Left)
                this.DragMove();
        }


        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            Properties.Settings.Default.Save();
        }

        private void MainForm_SizeChanged(object sender, SizeChangedEventArgs e)
        {
            this.Height = this.Width / 3.92;
        }

        #region Clock
        
        private void Tick()
        {

            dt = DateTime.Now;
            time = dt.ToString("HHmmss");

            // Start timers
            TickTimer.Elapsed += new System.Timers.ElapsedEventHandler(TickTimer_Elapsed);
            TickTimer.AutoReset = true;
            TickTimer.Enabled = true;
            TickTimer.Start();

            SetTimer.Elapsed += new System.Timers.ElapsedEventHandler(SetTimer_Elapsed);
            SetTimer.AutoReset = true;
            
            counter = 4;
            //  SetTimer.Enabled = true;
            //  SetTimer.Start();

        }

        private void Stop1()
        {
            EnterTimer.Stop();
            // EnterTimer.Enabled = false; 
            // MessageBox.Show(rand.ToString() + rand2.ToString());
        }

        private void Stop2()
        {
            //SetTimer.Enabled = false; 
            SetTimer.Stop();
        }

        private void Enter()
        {
            dt = DateTime.Now;
            time = dt.ToString("HHmmss");
            sto = 0.5;
            rnd1 = new Random();
            rand = (short)rnd1.Next(6);
            do { rand2 = (short)rnd1.Next(6); }
            while (rand == rand2);

            mciSendString(@"open "+ uriEnter.OriginalString + " type waveaudio alias applause", null, 0, IntPtr.Zero);
            mciSendString(@"play applause", null, 0, IntPtr.Zero);

            EnterTimer.Elapsed += new System.Timers.ElapsedEventHandler(EnterTimer_Elapsed);
            EnterTimer.AutoReset = true;
            EnterTimer.Enabled = true;
            EnterTimer.Start();

            opacityTimer.Elapsed += new System.Timers.ElapsedEventHandler(opacityTimer_Elapsed);
            opacityTimer.AutoReset = true;
            opacityTimer.Enabled = true;
            opacityTimer.Start();
        
        }

        void EnterTimer_Elapsed(object sender, System.Timers.ElapsedEventArgs e)
        {
            // UI controls can only be accessed from main thread so use dispatcher
            Dispatcher.Invoke(System.Windows.Threading.DispatcherPriority.Normal,
                              new Action(
                               delegate ()
                               {
                                   if (counter2 == 0)
                                   {
                                       if (STime[0] != Int16.Parse(time[0].ToString()))
                                       {
                                           STime[1]++; ChangeDigit(1);
                                           if (STime[1] == 10)
                                           {
                                               STime[0]++; ChangeDigit(0); STime[1] = 0;
                                           }
                                       }
                                       else
                                       {

                                           if (STime[1] != Int16.Parse(time[1].ToString()))
                                           {
                                               STime[1]++; ChangeDigit(1);
                                           }
                                       }


                                       if (STime[2] != Int16.Parse(time[2].ToString()))
                                       {
                                           STime[3]++; ChangeDigit(3);
                                           if (STime[3] == 10)
                                           {
                                               STime[2]++; ChangeDigit(2); STime[3] = 0;
                                           }
                                       }
                                       else
                                       {

                                           if (STime[3] != Int16.Parse(time[3].ToString()))
                                           {
                                               STime[3]++; ChangeDigit(3);
                                           }
                                       }


                                       if (STime[4] != Int16.Parse(time[4].ToString()))
                                       {
                                           STime[5]++; ChangeDigit(5);
                                           if (STime[5] == 10)
                                           {
                                               STime[4]++;
                                               if (STime[4] > 5) { STime[4] = 0; }
                                               ChangeDigit(4); STime[5] = 0;
                                           }
                                       }
                                       else
                                       {
                                           if (STime[5] != Int16.Parse(time[5].ToString()))
                                           {
                                               STime[5]++; ChangeDigit(5);
                                           } else
                                           {
                                               dt = DateTime.Now;
                                               time = dt.ToString("HHmmss");
                                           }
                                       }
                                   }
                                   temp = STime[0].ToString() + STime[1].ToString() + STime[2].ToString() + STime[3].ToString() + STime[4].ToString() + STime[5].ToString();
                                   if (temp == time)
                                   {

                                       if (counter2 == 0)
                                       {
                                           counter2++; Tick();
                                       }
                                       STime[5] = Int16.Parse(time[5].ToString()); ChangeDigit(5);
                                       if (STime[5] == 0 || counter == 4)
                                       {
                                           counter = 4;
                                           SetTimer.Enabled = true;
                                           SetTimer.Start();
                                       }

                                       EnterTimer.Interval = 50;
                                       
                                       counter2++;

                                       HS = false; MS = false; SS = false;

                                       if (counter2 == 18 || counter2 == 33)
                                       {
                                           mciSendString(@"open " + uriSpark.OriginalString + " type waveaudio alias applause1", null, 0, IntPtr.Zero);
                                           mciSendString(@"play applause1", null, 0, IntPtr.Zero);
                                       }

                                       if (counter2 > 20 && counter2 < 35)
                                       {
                                           
                                           if (counter2 % 5 == 2)
                                           {
                                               ChangeDigit((short)(rand + 6));
                                               ChangeDigit(rand2);
                                           }
                                           if (counter2 % 2 == 0)
                                           {
                                               
                                               ChangeDigit(rand);
                                               ChangeDigit((short)(rand2 + 6));
                                           }

                                       }
                                           if (counter2 > 35)
                                           {
                                           sto = 1; 
                                           ChangeDigit(rand); ChangeDigit(rand2);

                                           counter2 = 0;
                                           Stop1();
                                           }
                                  }
                               }
                           ));
        }

        void TickTimer_Elapsed(object sender, System.Timers.ElapsedEventArgs e)
        {
            // UI controls can only be accessed from main thread so use dispatcher
            Dispatcher.Invoke(System.Windows.Threading.DispatcherPriority.Normal,
                              new Action(
                               delegate ()
                               {
                                   Tack();
                               }
                           ));
        }

        void SetTimer_Elapsed(object sender, System.Timers.ElapsedEventArgs e)
        {
            // UI controls can only be accessed from main thread so use dispatcher
            Dispatcher.Invoke(System.Windows.Threading.DispatcherPriority.Normal,
                              new Action(
                               delegate ()
                               {
                                   if (counter == 0)
                                   {
                                       if (STime[0] != Int16.Parse(time[0].ToString()))     { STime[0] = Int16.Parse(time[0].ToString()); ChangeDigit(0);}
                                       Stop2(); 
                                   } 

                                   if (counter == 1)
                                   {
                                        if (STime[1] != Int16.Parse(time[1].ToString()))    { STime[1] = Int16.Parse(time[1].ToString()); ChangeDigit(1);}
                                       counter--;
                                   }  
                                   if (counter == 2)
                                   {
                                        if (STime[2] != Int16.Parse(time[2].ToString()))    { STime[2] = Int16.Parse(time[2].ToString()); ChangeDigit(2);}
                                       counter--;
                                   } 
                                   if (counter == 3)
                                   {
                                        if (STime[3] != Int16.Parse(time[3].ToString()))    { STime[3] = Int16.Parse(time[3].ToString()); ChangeDigit(3);}
                                       counter--;
                                   } 
                                   if (counter == 4)
                                   {
                                        if (STime[4] != Int16.Parse(time[4].ToString()))    { STime[4] = Int16.Parse(time[4].ToString()); ChangeDigit(4);}
                                       counter--;
                                   }
                               }
                           ));
        }

        private void Tack()
        {

            dt = DateTime.Now;
            time = dt.ToString("HHmmss");
            sto = 0.1;

            if(counter2==0)
            {
                    HS = Properties.Settings.Default.SH;
                     MS = Properties.Settings.Default.SM;
                    SS = Properties.Settings.Default.SS;
            }

            if (STime[5] != Int16.Parse(time[5].ToString()) )
            {
                STime[5] = Int16.Parse(time[5].ToString()); ChangeDigit(5);
            }

            if (STime[5] == 0 || counter == 4)
            {
                counter = 4;
                SetTimer.Enabled = true;
                SetTimer.Start();
            }
        }

    private void ChangeDigit(short i)
        {
            switch (i)
            {
                case 0: { image_h1.Source = new BitmapImage(GetDigit(STime[0])); image_h1.Opacity = sto; if (HS) { player.Open(uriTick); player.Play(); } break; }
                case 1: { image_h2.Source = new BitmapImage(GetDigit(STime[1])); image_h2.Opacity = sto; if (HS) { player.Open(uriTick); player.Play(); } break; }
                case 2: { image_m1.Source = new BitmapImage(GetDigit(STime[2])); image_m1.Opacity = sto; if (MS) { player.Open(uriTick); player.Play(); } break; }
                case 3: { image_m2.Source = new BitmapImage(GetDigit(STime[3])); image_m2.Opacity = sto; if (MS) { player.Open(uriTick); player.Play(); } break; }
                case 4: { image_s1.Source = new BitmapImage(GetDigit(STime[4])); image_s1.Opacity = sto; if (SS) { player.Open(uriTick); player.Play(); } break; }
                case 5: { image_s2.Source = new BitmapImage(GetDigit(STime[5])); image_s2.Opacity = sto+0.4; if (SS) { player.Open(uriTick); player.Play(); } break; }
                case 6:  { image_h1.Source = null; image_h1.Opacity = sto; break; }
                case 7:  { image_h2.Source = null; image_h2.Opacity = sto; break; }
                case 8:  { image_m1.Source = null; image_m1.Opacity = sto; break; }
                case 9:  { image_m2.Source = null; image_m2.Opacity = sto; break; }
                case 10: { image_s1.Source = null; image_s1.Opacity = sto; break; }
                case 11: { image_s2.Source = null; image_s2.Opacity = sto; break; }
            }
        }

        private void Window_KeyDown(object sender, KeyEventArgs e)
        {
            Application.Current.Shutdown();
        }

        private Uri GetDigit(short d)
        {
            switch (d) { 
                case 0: uriDigit = new Uri("pack://application:,,,/Resources/d_0000_0.png"); break;
                case 1: uriDigit = new Uri("pack://application:,,,/Resources/d_0001_1.png"); break;
                case 2: uriDigit = new Uri("pack://application:,,,/Resources/d_0002_2.png"); break;
                case 3: uriDigit = new Uri("pack://application:,,,/Resources/d_0003_3.png"); break;
                case 4: uriDigit = new Uri("pack://application:,,,/Resources/d_0004_4.png"); break;
                case 5: uriDigit = new Uri("pack://application:,,,/Resources/d_0005_5.png"); break;
                case 6: uriDigit = new Uri("pack://application:,,,/Resources/d_0006_6.png"); break;
                case 7: uriDigit = new Uri("pack://application:,,,/Resources/d_0007_7.png"); break;
                case 8: uriDigit = new Uri("pack://application:,,,/Resources/d_0008_8.png"); break;
                case 9: uriDigit = new Uri("pack://application:,,,/Resources/d_0009_9.png"); break;
                default: uriDigit = new Uri("pack://application:,,,/Resources/d_0000_0.png"); break;
            }
            return uriDigit;
        }


        void opacityTimer_Elapsed(object sender, System.Timers.ElapsedEventArgs e)
        {
            // UI controls can only be accessed from main thread so use dispatcher
            Dispatcher.Invoke(System.Windows.Threading.DispatcherPriority.Normal,
                              new Action(
                               delegate ()
                               {
                                   if (image_h1.Opacity < 0.99) image_h1.Opacity = image_h1.Opacity + 0.05; else image_h1.Opacity = 1;
                                   if (image_h2.Opacity < 0.99) image_h2.Opacity = image_h2.Opacity + 0.05; else image_h2.Opacity = 1;
                                   if (image_m1.Opacity < 0.99) image_m1.Opacity = image_m1.Opacity + 0.05; else image_m1.Opacity = 1;
                                   if (image_m2.Opacity < 0.99) image_m2.Opacity = image_m2.Opacity + 0.05; else image_m2.Opacity = 1;
                                   if (image_s1.Opacity < 0.99) image_s1.Opacity = image_s1.Opacity + 0.05; else image_s1.Opacity = 1;
                                   if (image_s2.Opacity < 0.99) image_s2.Opacity = image_s2.Opacity + 0.05; else image_s2.Opacity = 1;
                               } 
                           ));
        }

        #endregion

        private void Window_MouseMove(object sender, MouseEventArgs e)
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

}

