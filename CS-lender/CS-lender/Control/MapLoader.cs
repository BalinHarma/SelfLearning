using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Resources;

using CS_lender.Model;

namespace CS_lender.Control
{
    /// <summary>
    /// This class' responsibility is to load in maps from files.
    /// TODO better xml map specification and loading...
    /// </summary>
    public static class MapLoader
    {
        private static string mapString = Properties.Resources.map;

        /// <summary>
        /// Loads the map from a text file, into the passed in world.
        /// </summary>
        /// <param name="world"></param>
        public static void loadMap(World world)
        {
            string name;
            int sizeX;
            int sizeY;
            int tileX;
            int tileY;
            
            string[] lines = mapString.Split("\r\n".ToCharArray(), StringSplitOptions.RemoveEmptyEntries);
            foreach (string line in lines)
            {
                string[] words = line.Split(" ".ToCharArray(), StringSplitOptions.RemoveEmptyEntries);
                name = words[0];
                sizeX = int.Parse(words[1]);
                sizeY = int.Parse(words[2]);
                tileX = int.Parse(words[3]);
                tileY = int.Parse(words[4]);
                new Obstacle(world.tiles[tileX, tileY], name, sizeX, sizeY);
            }
        }
        
	
    }
}