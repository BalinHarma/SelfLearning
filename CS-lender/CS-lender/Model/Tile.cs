using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CS_lender.Model
{

    public class Tile
    {
        public string name { get; private set; }
        public int X { get; private set; }
        public int Y { get; private set; }
        public World world { get; private set; }
        public List<PhysicalObject> physicalObjects { get; private set; }

        public Tile(int X, int Y, World world, string name)
        {
            this.X = X;
            this.Y = Y;
            this.world = world;
            this.name = name;
            physicalObjects = new List<PhysicalObject>();
        }

        public Tile getNeighbouringTile(int X, int Y)
        {
            return world.tiles[this.X + X, this.Y + Y];
        }

        public int getManhattanDistance(Tile otherTile)
        {

            return Math.Abs(X - otherTile.X) + Math.Abs(Y - otherTile.Y);
        }

        public static Tile getRandomTile(World world)
        {
            Random random = new Random();
            int x = random.Next(world.sizeX);
            int y = random.Next(world.sizeY);
            return world.tiles[x, y];
        }

        public override string ToString()
        {
            return "tile: " + X.ToString() + "," + Y.ToString();
        }
    }
}