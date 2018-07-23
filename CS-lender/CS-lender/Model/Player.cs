using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CS_lender.Model
{
    public class Player : PhysicalObject
    {
        public int papers { get; private set; }

        public delegate void MovedHandler(Player source);
        public event MovedHandler PlayerMoved;

        public Player(Tile originTile, string name, int sizeX, int sizeY) : base(originTile, name, sizeX, sizeY)
        {
            depthLayer = 1;
        }

        public override bool allowedCollision(PhysicalObject callingPhysicalObject)
        {
            if (callingPhysicalObject is Obstacle)
            {
                return false;
            }
            return true;
        }

        public void move(int X, int Y)
        {
            Tile newTile = originTile.getNeighbouringTile(X, Y);

            // check if move is legit
            bool allowedMove = true;
            Paper paper = null;
            foreach (PhysicalObject phObject in newTile.physicalObjects)
            {
                if (phObject.allowedCollision(this) == false)
                {
                    allowedMove = false;
                }
                if (phObject is Paper)
                {
                    paper = phObject as Paper;
                }
            }
            if (paper != null)
            {
                pickUp(paper);
            }
            if (allowedMove == false)
            {
                return;
            }
            // execute move
            originTile.physicalObjects.Remove(this);
            originTile = newTile;
            originTile.physicalObjects.Add(this);
            // notify subscribers (intended subscriber is slenderman)
            onPlayerMoved();
        }

        protected virtual void onPlayerMoved()
        {
            // Note to self: this is just syntactic sugar for first checking if(PlayerMoved =! null)
            PlayerMoved?.Invoke(this);
        }

        private void pickUp(Paper pickUp)
        {
            papers++;
            pickUp.originTile.physicalObjects.Remove(pickUp);
            onPlayerMoved();
        }
    }
}