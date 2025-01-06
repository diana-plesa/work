using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace gdi_2
{
    internal class Enemy
    {
        int PosX { get; set; }
        int PosY { get; set; }

        Point[] points;
        SolidBrush brush;
        Pen pen;
        public bool goingRight;
        public bool goingUp;
        bool collided;
        enemyBullet[] bullets;
        int timer;

        public Enemy()
        {
            points = new Point[3];
            brush = new SolidBrush(Color.Red);
            pen = new Pen(Color.Red);
            goingRight = true;
            goingUp = true;
            collided = false;
            bullets = new enemyBullet[3];
            timer = 1;

            for (int i = 0; i < bullets.Length; i++)
            {
                bullets[i] = new enemyBullet();
            }
        }

        internal int GetPosX()
        {
            return PosX;
        }
        internal int GetPosY()
        {
            return PosY;
        }

        internal bool GetCollision()
        {
            return collided;
        }


        public void SetOrigin(int x , int y)
        {
            PosX = x;
            PosY = y;
        }

        public void ChangeDirection()
        {
            goingRight = !goingRight;
        }

        public void ChangeVertical()
        {
            goingUp = !goingUp;
        }

        public void Move()
        {
            if (goingRight)
                PosX = PosX + 5;
            else 
                PosX = PosX - 5;

            if (goingUp)
                PosY = PosY - 5;
            else 
                PosY = PosY + 5;
        }

        public void Shoot()
        {
            for (int i = 0; i < bullets.Length; i++)
            {
                while (timer < 20)
                {
                    timer++;
                }

                bullets[i].Create(PosX, PosY);
                timer = 1;
                for (int j = 0; j < bullets.Length; j++)
                {
                    if (bullets[j].exists == true)
                        bullets[j].Move();
                }
            }
        }


        public void CheckCollision(Bullet bullet)
        {
            if (bullet.PosX >= PosX - 15 && bullet.PosX <= PosX + 15 && bullet.PosY >= PosY - 15 && bullet.PosY <= PosY + 15)
            {
                collided = true;
            }
        }
        public void Draw(Graphics g)
        {

            points[0].X = PosX;
            points[0].Y = PosY;

            points[1].X = PosX - 15;
            points[1].Y = PosY - 15;

            points[2].X = PosX + 15;
            points[2].Y = PosY - 15;

            g.DrawPolygon(pen, points);
            g.FillPolygon(brush, points);

            for (int i = 0; i < bullets.Length; i++)
            {
                if (bullets[i].exists == true) bullets[i].Draw(g);
            }

        }

       
    }
}
