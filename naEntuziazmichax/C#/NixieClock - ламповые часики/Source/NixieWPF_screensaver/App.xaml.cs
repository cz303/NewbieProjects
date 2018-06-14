using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Interop;

namespace NixieWPF
{
    /// <summary>
    /// Логика взаимодействия для App.xaml
    /// </summary>
    public partial class App : Application
    {

        App()
        {
            InitializeComponent();
        }

        [STAThread]
        static void Main(string[] args)
        {
            if (args.Length > 0)
            {
                string firstArgument = args[0].ToLower().Trim();
                string secondArgument = null;

                // Handle cases where arguments are separated by colon.
                // Examples: /c:1234567 or /P:1234567
                if (firstArgument.Length > 2)
                {
                    secondArgument = firstArgument.Substring(3).Trim();
                    firstArgument = firstArgument.Substring(0, 2);
                }
                else if (args.Length > 1)
                    secondArgument = args[1];

                if (firstArgument == "/c")           // Configuration mode
                {
                    App app = new App();
                    Window1 window = new Window1();
                    app.Run(window);
                }
                else if (firstArgument == "/p")      // Preview mode
                {
                    App app = new App();
                    Int32 previewHandle = Convert.ToInt32(secondArgument);
                    IntPtr previewWndHandle = new IntPtr(previewHandle);

                    WindowBlack window = new WindowBlack(previewWndHandle);
                   // MainWindow window = new MainWindow(previewWndHandle);
                    app.Run(window);
                }
                else if (firstArgument == "/s")      // Full-screen mode
                {
                    App app = new App();
                    WindowBlack window = new WindowBlack();
                    app.Run(window);
                }
                else    // Undefined argument
                {
                    System.Windows.MessageBox.Show("Sorry, but the command line argument \"" + firstArgument +
                        "\" is not valid.", "Nixie ScreenSaver", MessageBoxButton.OK); 
                }
            }

            else    // No arguments - treat like /c
            {
                //            App app = new App();
                //            WindowBlack window = new WindowBlack(2);
                //            app.Run(window);
                // System.Windows.MessageBox.Show("Sorry, but the command line is empty", "Nixie ScreenSaver", MessageBoxButton.OK);
                App app = new App();
                Window1 window = new Window1();
                app.Run(window);
            }  
        }


    }
}
