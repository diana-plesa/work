using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace gdi_2
{
    internal class Star
    {
        public int diameter, x, y;
        SolidBrush brush = new SolidBrush(Color.White);
        public Star(int width, int height)
        {
            diameter = 3;
            Random rnd = new Random();
            x = rnd.Next(0, width);
            y = rnd.Next(0, height);
        }

        public void Draw(Graphics g)
        {
            g.FillEllipse(brush, x, y, diameter, diameter);
        }

    }
}
