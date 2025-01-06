using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace gdi_2
{
    internal class Explosion
    {
        SolidBrush brush;
        int PosX, PosY;
        public bool isExplosion;
        

        public Explosion()
        {
            brush = new SolidBrush(Color.OrangeRed);
            isExplosion = false;
        }

        public void Create(int x, int y)
        {
            isExplosion = true;
            PosX = x; PosY = y;
        }

        public bool IsCreated()
        {
            return isExplosion;
        }

        public void Remove()
        {
            isExplosion = false;
        }

        internal int GetPosX()
        {
            return PosX;
        }

        internal int GetPosY()
        {
            return PosY;
        }

        public void Draw(Graphics g)
        {
            if (isExplosion)
            {
                g.FillEllipse(brush, PosX, PosY, 20, 20);
            }
        }
    }
}
