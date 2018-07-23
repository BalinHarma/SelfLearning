using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CS_lender.Model
{
    public class Obstacle : PhysicalObject
    {
        public Obstacle(Tile originTile, string name, int sizeX, int sizeY) : base(originTile, name, sizeX, sizeY)
        {
            depthLayer = 2;
        }

        public override bool allowedCollision(PhysicalObject callingPhysicalObject)
        {
            if (callingPhysicalObject is Obstacle || callingPhysicalObject is Player)
            {
                return false;
            }
            return true;
        }
    }
}