using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace gdi_2
{
    internal class Planet
    {
        public int diameter;
        public Color color;
        int x, y, cursor;

        Color[] colorArray = new Color[]
        {
                Color.Aquamarine, Color.Pink, Color.Beige, Color.PaleGreen, Color.Lavender
        };
        public Planet(int width, int height)
        {
            Random rnd = new Random();
            diameter = rnd.Next(10, 200);
            cursor = rnd.Next(0, 5);
            color = colorArray[cursor];
            x = rnd.Next(0, width);
            y = rnd.Next(0, height);
        }

        public void Draw(Graphics g)
        {
            SolidBrush brush = new SolidBrush(color);
            g.FillEllipse(brush, x, y, diameter, diameter);
        }
    }
}
