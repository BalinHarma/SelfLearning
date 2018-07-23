using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CS_lender.Model
{
    public class Paper : PhysicalObject
    {
        public Paper(Tile originTile, string name, int sizeX, int sizeY) : base(originTile, name, sizeX, sizeY)
        {
            depthLayer = 3;
        }

        public override bool allowedCollision(PhysicalObject callingPhysicalObject)
        {
            if (callingPhysicalObject is Paper)
            {
                return false;
            }
            return true;
        }
    }
}