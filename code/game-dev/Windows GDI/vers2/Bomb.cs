using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace gdi_2
{
    internal class Bomb
    {
        int perimeter;
        SolidBrush brush;
        Pen pen;
        Color colorBrush;
        Color colorPen;

        public int PosX { get; set; }
        public int PosY { get; set; }

        public Bomb()
        {
            colorBrush = Color.FromArgb(153, 14, 74);
            colorPen = Color.FromArgb(99, 13, 24);
            perimeter = 40;
            brush = new SolidBrush(colorBrush);
            pen = new Pen(colorPen);
        }

        public void Draw(Graphics g)
        {
            g.FillEllipse(brush, PosX, PosY, perimeter, perimeter);
            g.DrawEllipse(pen, PosX, PosY, perimeter, perimeter);
        }
    }
}
