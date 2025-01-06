using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace gdi_2
{
    internal class Bullet
    {
        int perimeter;
        SolidBrush brush;
        Pen pen;

        public int PosX { get; set; }
        public int PosY { get; set; }

        public Bullet()
        {
            brush = new SolidBrush(Color.White);
            pen = new Pen(Color.Black);
            Ship ship = new Ship();
            perimeter = 10;
            //PosX = ship.PosX;
            //PosY = ship.PosY - 5;
        }

        public void Draw(Graphics g)
        {
            if (PosX >= 0 && PosY >= 0)
            {
                g.FillEllipse(brush, PosX, PosY, perimeter, perimeter);
                g.DrawEllipse(pen, PosX, PosY, perimeter, perimeter);
            }

        }

    }
}
