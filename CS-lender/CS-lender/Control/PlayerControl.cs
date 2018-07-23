using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using CS_lender.View;
using CS_lender.Model;

namespace CS_lender.Control
{
    public class PlayerControl
    {
        private GameWindow gameWindow;
        private Player player;

        public PlayerControl(GameWindow gameWindow, Player player)
        {
            this.gameWindow = gameWindow;
            this.player = player;
            gameWindow.KeyDown += PlayerKeyDown;
        }

        private void PlayerKeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.W)
            {
                if (player.originTile.Y > 0)
                {
                    player.move(0, -1);
                }
            }
            else if (e.KeyCode == Keys.D)
            {
                if (player.originTile.X < player.originTile.world.sizeX -1)
                {
                    player.move(1, 0);
                }
            }
            else if (e.KeyCode == Keys.S)
            {
                if (player.originTile.Y < player.originTile.world.sizeY - 1)
                {
                    player.move(0, 1);
                }
            }
            else if (e.KeyCode == Keys.A)
            {
                if (player.originTile.X > 0)
                {
                    player.move(-1, 0);
                }
            }
        }
    }
}
