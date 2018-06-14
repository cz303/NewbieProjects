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
        public Window1()
        {
            InitializeComponent();

            if (Properties.Settings.Default.fon == "./Resources/fon2.png")
                AutoStart.IsChecked = true;
            else
                AutoStart.IsChecked = false;

            this.SoundH.IsChecked = Properties.Settings.Default.SH;
            this.SoundM.IsChecked = Properties.Settings.Default.SM;
            this.SoundS.IsChecked = Properties.Settings.Default.SS;
        }

        public static implicit operator Form(Window1 v)
        {
            throw new NotImplementedException();
        }

        private void window_Loaded(object sender, RoutedEventArgs e)
        {
             
        }

        private void AutoStart_Click(object sender, RoutedEventArgs e)
        {
            if(AutoStart.IsChecked == true)
                Properties.Settings.Default.fon = "./Resources/fon2.png";
            else
                Properties.Settings.Default.fon = "./Resources/fon.png";
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

        private void window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            Properties.Settings.Default.Save();
        }
    }
}
