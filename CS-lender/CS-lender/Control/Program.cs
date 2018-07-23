using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

using CS_lender.Model;
using CS_lender.View;

namespace CS_lender.Control
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            MessageBox.Show("You are about to play a super simple Slenderman clone." + Environment.NewLine
                + "Use WASD to find all the papers. You are not bad at the game, it is just unfair." + Environment.NewLine
                + "If you please, look at the code behind it, and we can talk all about it on my interview.");
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            World world = new World(15, 15);
            MapLoader.loadMap(world);
            Application.Run(new GameWindow(world));
        }
    }
}
