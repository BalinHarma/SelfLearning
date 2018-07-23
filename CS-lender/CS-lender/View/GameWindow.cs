using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Drawing;

using CS_lender.Model;
using CS_lender.Control;

namespace CS_lender.View
{
    /// <summary>
    /// Class responsible for the game window's graphical representation,
    /// written by hand to practice as opposed to using VS window designer.
    /// /// </summary>
    public class GameWindow : Form
    {
        private World world;
        private GameScreen gameScreen;
        private PlayerControl playerControl;

        public GameWindow(World world)
        {
            this.world = world;
            playerControl = new PlayerControl(this, world.player);
            world.slenderMan.SlenderManMoved += OnMoved;
            InitGUI();

        }

        private void InitGUI()
        {
            Name = "CS-lender";
            Text = "CS-lender";
            Size = new Size(GlobalConstants.defaultResolutionX, GlobalConstants.defaultResolutionY);
            StartPosition = FormStartPosition.CenterScreen;

            gameScreen = new GameScreen(world);
            Controls.Add(gameScreen);
            gameScreen.renderFrame();
        }
        public void OnMoved(SlenderMan sender)
        {
            gameScreen.renderFrame();
            if (sender.originTile == world.player.originTile)
            {
                MessageBox.Show("You have lost... but what is losing anyway?");
                Application.Exit();
            }
            if (world.player.papers==8)
            {
                MessageBox.Show("You have won! Yaay!");
                Application.Exit();
            }
        }
    }
}