using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CS_lender.Model
{
    /// <summary>
    /// The base class of all the objects seen and interacted with on the playing field
    /// </summary>
    public abstract class PhysicalObject
    {
        public Tile originTile { get; protected set; }
        public string name { get; private set; }
        public int sizeX { get; private set; }
        public int sizeY { get; private set; }
        public int depthLayer { get; protected set; }

        protected PhysicalObject(Tile originTile, string name, int sizeX, int sizeY)
        {
            this.originTile = originTile;
            this.name = name;
            this.sizeX = sizeX;
            this.sizeY = sizeY;

            List<Tile> touchedTiles = new List<Tile>();

            // check if the object can be placed in the specified tile:
            for (int i = 0; i < sizeX; i++)
            {
                for (int j = 0; j < sizeY; j++)
                {
                    Tile currentTile = originTile.getNeighbouringTile(i, j);
                    touchedTiles.Add(currentTile);
                    foreach (PhysicalObject phObject in currentTile.physicalObjects)
                    {
                        if (phObject.allowedCollision(this) == false)
                        {
                            Exception e = new NotAllowedCollisionException("tile: " + currentTile.ToString());
                            throw e;
                        }
                    }
                }
            }

            // Place the object.
            foreach (Tile tile in touchedTiles)
            {
                tile.physicalObjects.Add(this);
            }


        }

        /// <summary>
        /// returns wether the callingPhysicalObject (the active entity trying to enter a tile) can occupy the same Tile as the "passive" physicalObject already present
        /// </summary>
        /// <param name="callingPhysicalObject"></param>
        /// <returns></returns>
        public abstract bool allowedCollision(PhysicalObject callingPhysicalObject);

    }
}
