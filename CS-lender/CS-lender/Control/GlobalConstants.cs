using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CS_lender.Control
{
    /// <summary>
    /// Class for housing all the globally predefined variables and settings..,
    /// </summary>
    public static class GlobalConstants
    {
        // Note to self: here I learned about expression bodied members, 
        // the two member declarations are exactly the same, the first one is just syntactic sugar.
        public static int defaultResolutionX => 840;
        public static int defaultResolutionY
        {
            get
            {
                return 840;
            }
        }
    }
}