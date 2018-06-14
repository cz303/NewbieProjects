using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Forms;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace NixieWPF
{
    /// <summary>
    /// Логика взаимодействия для Window1.xaml
    /// </summary>
    public partial class Window1 : Window
    {
        public Window1(double MainWidth, double Opacity)
        {
            InitializeComponent();
            this.sliderSize.Value = MainWidth;
            this.sliderOpacity.Value = Opacity;
            this.AlwaysTop.IsChecked = Properties.Settings.Default.TopWindow;
            this.AutoStart.IsChecked = Properties.Settings.Default.AStart;
            this.SoundH.IsChecked = Properties.Settings.Default.SH;
            this.SoundM.IsChecked = Properties.Settings.Default.SM;
            this.SoundS.IsChecked = Properties.Settings.Default.SS;
            this.Topmost = AlwaysTop.IsChecked.Value;

            if (Properties.Settings.Default.fon == "./Resources/fon2.png")
                SecondBG.IsChecked = true;
            else
                SecondBG.IsChecked = false;
        }

        public static implicit operator Form(Window1 v)
        {
            throw new NotImplementedException();
        }

        private void window_Loaded(object sender, RoutedEventArgs e)
        {
             
        }

        private void sliderSize_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            MainWindow.ControlWidth.Data = this.sliderSize.Value;
            MainWindow.ControlWidth.DoIT();
        }

        private void sliderOpacity_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            MainWindow.ControlOpacity.Data = this.sliderOpacity.Value;
            MainWindow.ControlOpacity.DoIT();
        }

        private void AlwaysTop_Click(object sender, RoutedEventArgs e)
        {
            Properties.Settings.Default.TopWindow = AlwaysTop.IsChecked.Value;
            System.Windows.Application.Current.MainWindow.Topmost = AlwaysTop.IsChecked.Value;
            this.Topmost = AlwaysTop.IsChecked.Value;
        }

        private void AutoStart_Click(object sender, RoutedEventArgs e)
        {
            Properties.Settings.Default.AStart = AutoStart.IsChecked.Value;

            RegistryKey registryKey = Registry.CurrentUser.OpenSubKey("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", true);
            if (AutoStart.IsChecked.Value)
            {
                registryKey.SetValue("NixieClock", System.Reflection.Assembly.GetExecutingAssembly().Location);
            }
            else
            {
                registryKey.DeleteValue("NixieClock");
            }

        }

        private void SoundH_Click(object sender, RoutedEventArgs e)
        {
            Properties.Settings.Default.SH = SoundH.IsChecked.Value;
        }

        private void SoundM_Click(object sender, RoutedEventArgs e)
        {
            Properties.Settings.Default.SM = SoundM.IsChecked.Value;
        }

        private void SoundS_Click(object sender, RoutedEventArgs e)
        {
            Properties.Settings.Default.SS = SoundS.IsChecked.Value;
        }

        private void checkBox_Click(object sender, RoutedEventArgs e)
        {
            if (SecondBG.IsChecked == true)
                Properties.Settings.Default.fon = "./Resources/fon2.png";
            else
                Properties.Settings.Default.fon = "./Resources/fon.png";
        }
    }
}
