using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace gdi_2
{
    internal class enemyBullet
    {
        int PosX { get; set; }
        int PosY { get; set; }
        SolidBrush brush;
        int perimeter;
        Point[] points;
        public bool exists;
        //public int shootTime;

        public enemyBullet()
        {
            brush = new SolidBrush(Color.Red);
            perimeter = 7;
            points =new Point[4];
            exists = false;
            //shootTime = new Random().Next(16, 29);
        }

        public void Draw(Graphics g)
        {
            g.FillPolygon(brush, points);
        }

        public void Create(int enemyX, int enemyY)
        {
            PosX = enemyX - 5;
            PosY = enemyY + 20;
            points[0] = new Point(PosX, PosY);
            points[1] = new Point(PosX + perimeter, PosY);
            points[2] = new Point(PosX + perimeter, PosY + perimeter);
            points[3] = new Point(PosX, PosY + perimeter);
            exists = true;
        }

        public void Move()
        {
            PosY = PosY + 5;
        }

    }
}
