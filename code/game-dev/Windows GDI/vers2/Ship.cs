namespace gdi_2
{
    internal class Ship
    {
        //public int x, y;

        public int PosX { get; set; }
        public int PosY { get; set; }

        Point[] points;
        SolidBrush brush;
        Pen pen;

        public Ship()
        {
            points = new Point[3];
            brush = new SolidBrush(Color.White);
            pen = new Pen(Color.Black);
        }
        public void Draw(Graphics g)
        {
            points[0].X = PosX;
            points[0].Y = PosY;

            points[1].X = PosX - 30;
            points[1].Y = PosY + 30;

            points[2].X = PosX + 30;
            points[2].Y = PosY + 30;

            g.FillPolygon(brush, points);
            g.DrawPolygon(pen, points);
        }

    }
}
