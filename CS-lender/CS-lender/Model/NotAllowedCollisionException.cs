using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CS_lender.Model
{
    class NotAllowedCollisionException : ApplicationException
    {
        public NotAllowedCollisionException(string message) : base (message)
        {
            
        }
    }
}
