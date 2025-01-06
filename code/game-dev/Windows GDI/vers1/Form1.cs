using Accessibility;
using System.Diagnostics;
using System.Runtime.CompilerServices;
using System.Security.Cryptography;
using System.Drawing;
using System.Reflection.Metadata;

namespace gdi1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }



        Point origin = new Point(0, 0);
        Point[] Bullets = new Point[100];
        Point[] Stars = new Point[10];
        Point[] Planets = new Point[3];
        Color[] PlanetColors = {Color.Pink, Color.Coral, Color.Aquamarine, Color.Beige, Color.Lavender, Color.AliceBlue};
        int BulletCursor = -1;
        int planetDiameter;
        SolidBrush[] brushPlanet = new SolidBrush[3];

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            Graphics g = e.Graphics;

            Color BgColor = new Color();
            BgColor = Color.FromArgb(44, 45, 79);
            SolidBrush brushBG = new SolidBrush(BgColor);
            g.FillRectangle(brushBG, 0, 0, Width, Height);
            
            SolidBrush brushWhite = new SolidBrush(Color.White);
            
            Pen penWhite = new Pen(Color.White);

            
         

            for (int i = 0; i < 9; i++)
            {
                g.FillEllipse(brushWhite, Stars[i].X, Stars[i].Y, 3, 3);
            }

            for (int i = 0; i < 3; i++)
            {
                g.FillEllipse(brushPlanet[i], Planets[i].X, Planets[i].Y, planetDiameter, planetDiameter);
            }

            this.DrawTriangle(g, this.origin, penWhite);
            if (BulletCursor >= 0)
            {
                for (int i = 0; i <= BulletCursor; i++)
                {
                    DrawBullet(g, Bullets[i].X, Bullets[i].Y);
                }

            }


        }

        private void DrawTriangle(Graphics g, Point origin, Pen pen)
        {
            Point[] points = new Point[3];
            points[0] = origin;
            points[1] = new Point(origin.X - 30, origin.Y + 30);
            points[2] = new Point(origin.X + 30, origin.Y + 30);

            g.DrawPolygon(pen, points);
        }

        private void DrawBullet(Graphics g, int x, int y)
        {
            //Debug.WriteLine("Space is pressed");

            Pen penBlack = new Pen(Color.Black);
            SolidBrush brushWhite = new SolidBrush(Color.White);
            int diameter = 10;

            for (int i = 0; i <= BulletCursor; i++)
            {
                g.DrawEllipse(penBlack, Bullets[i].X, Bullets[i].Y, diameter, diameter);
                g.FillEllipse(brushWhite, Bullets[i].X, Bullets[i].Y, diameter, diameter);

            }

        }

        private void Form1_Click(object sender, EventArgs e)
        {
            //System.Windows.Forms.MessageBox.Show("titi");
        }

        private void timer1_Tick(object sender, EventArgs e)
        {

            for (int i = 0; i <= BulletCursor; i++)
            {
                Bullets[i].Y = Bullets[i].Y - 5; 
                if (Bullets[i].Y < 0)
                {
                    Bullets[i].X = -1;
                    Bullets[i].Y = -1;
                }
            }
            this.Invalidate();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            //this.timer1.Start();
            this.origin = new Point(this.Size.Width / 2, this.Size.Height - 100);


            for (int i = 0; i < 3; i++)
            {
                Random rnd = new Random();
                int rndColor = rnd.Next(0, 5);
                brushPlanet[i] = new SolidBrush(PlanetColors[rndColor]);
            }

            Random rndD = new Random();
            planetDiameter = rndD.Next(7, 100);

            for (int i = 0; i < 100; i++)
            {
                Bullets[i].X = -1;
                Bullets[i].Y = -1;
            }

            for (int i = 0; i < 9; i++)
            {
                Random rnd = new Random();
                int rndY = rnd.Next(0, Height);
                int rndX = rnd.Next(0, Width);
                Stars[i].X = rndX;
                Stars[i].Y = rndY;
            }

            for (int i = 0; i < 3; i++)
            {
                Random rnd = new Random();
                int rndY = rnd.Next(0, Height);
                int rndX = rnd.Next(0, Width);

                Planets[i].X = rndX;
                Planets[i].Y = rndY;

            
            }
                
        }

        private void Form1_KeyPress(object sender, KeyPressEventArgs e)
        {

        }

        private void Form1_KeyDown(object sender, KeyEventArgs e)
        {
            Pen penBlack = new Pen(Color.Black);
            System.Windows.Forms.Keys key = (System.Windows.Forms.Keys)e.KeyValue;
            int step = 5;
            switch (key)
            {
                case Keys.Left: origin.X = origin.X - step; break;
                case Keys.Right: origin.X = origin.X + step; break;
                case Keys.Down: origin.Y = origin.Y + step; break;
                case Keys.Up: origin.Y = origin.Y - step; break;
                case Keys.Space:
                    {
                        this.timer1.Start();
                        BulletCursor++;
                        Bullets[BulletCursor].X = origin.X - 5;
                        Bullets[BulletCursor].Y = origin.Y - 20;
                        
                        break;
                    }

            }
            this.Invalidate(true);
        }

        private void Form1_SizeChanged(object sender, EventArgs e)
        {
            this.origin = new Point(this.Size.Width / 2, this.Size.Height - 100);
            this.Invalidate(true);
        }

        private void Form1_KeyUp(object sender, KeyEventArgs e)
        {
            System.Windows.Forms.Keys key = (System.Windows.Forms.Keys)e.KeyValue;
            switch (key)
            {
                case Keys.Space:
                    break;
            }

            this.Invalidate(true);
        }
    }
}