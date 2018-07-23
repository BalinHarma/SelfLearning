using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CS_lender.Model
{
    /// <summary>
    /// Represents a set of tiles composing a concrete game level.
    /// Note to self: Learned here the important difference between [][] and [,].
    /// </summary>
    public class World
    {
        public int sizeX { get; private set; }
        public int sizeY { get; private set; }
        public Tile[,] tiles { get; private set; }
        public Player player { get; private set; }
        public SlenderMan slenderMan { get; private set; }

        public World(int sizeX, int sizeY)
        {
            this.sizeX = sizeX;
            this.sizeY = sizeY;
            tiles = new Tile[sizeX,sizeY];
            for (int i = 0; i < sizeX; i++)
            {
                for (int j = 0; j < sizeY; j++)
                {
                    tiles[i, j] = new Tile(i, j, this, "grass1");
                }
            }
            // place actors
            player = new Player(tiles[6, 6], "player1", 1, 1);
            slenderMan = new SlenderMan(tiles[6, 6], "slenderman", 1, 1);
            player.PlayerMoved += slenderMan.OnMoved;

            // place papers
            int papers = 0;
            do
            {
                Tile newTile = Tile.getRandomTile(this);
                try
                {
                    new Paper(newTile, "paper1", 1, 1);
                    papers++;
                }
                catch (Exception)
                {
                }
            } while (papers < 8);
        }

    }
}