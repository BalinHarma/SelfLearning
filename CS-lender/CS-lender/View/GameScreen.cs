using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Drawing;
using System.Resources;
using System.Diagnostics;

using CS_lender.Model;
using CS_lender.Control;

namespace CS_lender.View
{
    /// <summary>
    /// Responsible for rendering the graphical frames of the game.
    /// </summary>
    public class GameScreen : PictureBox
    {
        private World world;

        private int resolutionX;
        private int resolutionY;

        private Bitmap frame;

        public GameScreen(World world)
        {
            this.world = world;
            Size = new Size(GlobalConstants.defaultResolutionX, GlobalConstants.defaultResolutionY);
            resolutionX = GlobalConstants.defaultResolutionX;
            resolutionY = GlobalConstants.defaultResolutionY;
            frame = new Bitmap(resolutionX, resolutionY);
            SizeMode = PictureBoxSizeMode.StretchImage;
            Dock = DockStyle.Fill;
        }

        public void renderFrame()
        {
            Graphics g = Graphics.FromImage(frame);

            Size tileSize = new Size(resolutionX / world.sizeX, resolutionY / world.sizeY);

            SortedDictionary<int, HashSet<PhysicalObject>> phObjectsByLayer = new SortedDictionary<int, HashSet<PhysicalObject>>();

            foreach (Tile tile in world.tiles)
            {
                // Draw background
                Image bg = SpriteLibrary.getSpriteByName(tile.name);
                // Note to self: using only the origin coordinates was not enough because the .Net api divined
                // a DPI to the images, and another to the actual monitor resolution, resulting in resized images, and awkward spaces between them..
                g.DrawImage(bg, 
                            tileSize.Width * tile.X, 
                            tileSize.Height * tile.Y,
                            bg.Width,
                            bg.Height);
                // meanwhile collect physicalObjects from tiles sorted by depth layer.
                foreach(PhysicalObject phObject in tile.physicalObjects)
                {
                    // Note to self: someDictionary.Add(key, value) will throw an exception if key exists, while
                    // someDictionary[key] = value will add the key if nonexistent, or just overwrite it's value if present.
                    // but this is by the by, as I am not adding a value here, just accessing the value (adding to a list)
                    if (phObjectsByLayer.ContainsKey(phObject.depthLayer) == false)
                    {
                        phObjectsByLayer.Add(phObject.depthLayer, new HashSet<Model.PhysicalObject>());
                    }
                    phObjectsByLayer[phObject.depthLayer].Add(phObject);
                }
            }

            // Draw physicalObjects ordered by layer
            foreach (int layer in phObjectsByLayer.Keys)
            {
                foreach (PhysicalObject phObject in phObjectsByLayer[layer])
                {
                    Tile tile = phObject.originTile;
                    Image img = SpriteLibrary.getSpriteByName(phObject.name);

                    g.DrawImage(img,
                            tileSize.Width * tile.X,
                            tileSize.Height * tile.Y,
                            img.Width,
                            img.Height);
                }
            }
            g.Dispose();
            Image = frame;
            

        }
    }
}