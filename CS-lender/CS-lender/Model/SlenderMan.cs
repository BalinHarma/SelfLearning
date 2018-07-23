using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CS_lender.Model
{
    public class SlenderMan : PhysicalObject
    {
        private int step;
        private int oneStepAway;
        Random random = new Random();

        public delegate void MovedHandler(SlenderMan sender);
        public event MovedHandler SlenderManMoved;

        public SlenderMan(Tile originTile, string name, int sizeX, int sizeY) : base(originTile, name, sizeX, sizeY)
        {
            depthLayer = 3; // should be underlayed the Obstacles.. but debugging, it is overlayed.
            step = 0;
            oneStepAway = 0;
        }

        public override bool allowedCollision(PhysicalObject callingPhysicalObject)
        {
            return true; // slenderman can be anywhere...
        }

        public void OnMoved(Player source)
        {
            move(source);
            // notify subscribers (intended subscriber is the graphical renderer [gameScreen here])
            SlenderManMoved?.Invoke(this);
        }

        private void move(Player player)
        {
            Tile newTile;
            Tile playerTile = player.originTile;
            // count how many steps has the player made, on every 5th step, move completely randomly
            step++;
            if (step % 5 == 0)
            {
                newTile = Tile.getRandomTile(originTile.world);
            }
            else if (player.papers < 2) // if less than 2 papers, min distance is 5
            {
                do
                {
                    newTile = Tile.getRandomTile(originTile.world);
                } while (playerTile.getManhattanDistance(newTile) < 5);
            }
            else if (player.papers < 4) // if less than 4 papers, max distance is 5
            {
                do
                {
                    newTile = Tile.getRandomTile(originTile.world);
                } while (playerTile.getManhattanDistance(newTile) > 5);
            }
            else if (player.papers < 6) // if less than 6 papers, max distance is 4...
            {
                do
                {
                    newTile = Tile.getRandomTile(originTile.world);
                } while (playerTile.getManhattanDistance(newTile) > 4);
            }
            else // if more or equal to 6 papers, max distance is 3
            {
                do
                {
                    newTile = Tile.getRandomTile(originTile.world);
                } while (playerTile.getManhattanDistance(newTile) > 3);
            }
            // if one step away for more than 3 steps, 
            // take another chance at catching the player based on how many papers it has
            oneStepAway = playerTile.getManhattanDistance(newTile) == 1 ? oneStepAway+1 : 0;
            if (oneStepAway > 3)
            {
                switch (player.papers)
                {
                    case 2:
                    case 3:
                        if (random.Next(4) == 0) // 25% chance to catch...
                            newTile = player.originTile;
                        break;
                    case 4:
                    case 5:
                        if (random.Next(2) == 0) // 50% chance to catch...
                            newTile = player.originTile;
                        break;
                    case 6:
                    case 7:
                    case 8:
                        if (random.Next(3) < 2) // 66% chance to catch
                            newTile = player.originTile;
                        System.Windows.Forms.MessageBox.Show("final tile: " + playerTile.getManhattanDistance(newTile).ToString());

                        break;
                }
            }
            originTile.physicalObjects.Remove(this);
            originTile = newTile;
            newTile.physicalObjects.Add(this);

        }


    }
}