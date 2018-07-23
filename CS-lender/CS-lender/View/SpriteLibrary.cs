using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Resources;

namespace CS_lender.View
{
    /// <summary>
    /// Responsible for loading the sprite image files into a dictionary.
    /// </summary>
    public static class SpriteLibrary
    {
        private static Dictionary<string, Image> sprites = new Dictionary<string, Image>();

        public static Image getSpriteByName(string name)
        {
            if (sprites.ContainsKey(name) == false)
            {
                sprites.Add(name, (Image)Properties.Resources.ResourceManager.GetObject(name));
                if (sprites[name] == null)
                {
                    System.Windows.Forms.MessageBox.Show("Warning, sprite not found with name: " + name);
                }
            }
            return sprites[name];

        }
    }
}