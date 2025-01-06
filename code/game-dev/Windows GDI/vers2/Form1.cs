using System.Drawing;
using Accessibility;
using System.Diagnostics;
using System.Runtime.CompilerServices;
using System.Security.Cryptography;
using System.Security.Policy;

namespace gdi_2

{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();

            stars = new Star[10];
            for (int i = 0; i < 10; i++)
            {
                stars[i] = new Star(Width, Height);
            }

            planets = new Planet[3];
            for (int i = 0; i < 3; i++)
            {
                planets[i] = new Planet(Width, Height);
            }

            ship = new Ship();

            bullets = new Bullet[BULLET_MAX];
            for (int i = 0; i < BULLET_MAX; i++)
            {
                bullets[i] = new Bullet();
                bullets[i].PosX = -1;
                bullets[i].PosY = -1;
            }

            bulletNumber = -1;
            enemyNumber = 3;
            explosionNumber = enemyNumber;

            enemies = new List<Enemy>();
            explosions = new List<Explosion>();

            for (int i = 0; i < enemyNumber; i++)
            {
                explosions.Add(new Explosion());
                enemies.Add(new Enemy());
            }

            timer2Counter = 1;
            maxHeight = 25;
            minHeight = 175;
        }


        Bullet[] bullets = null;
        Star[] stars = null;
        Planet[] planets = null;
        Ship ship;
        const int BULLET_MAX = 5;
        int bulletNumber;
        List<Enemy> enemies;
        List<Explosion> explosions;
        int enemyNumber;
        int explosionNumber;
        int timer2Counter;
        int maxHeight, minHeight;
       

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            Graphics g = e.Graphics;


            Color backgroundColor;
            backgroundColor = Color.FromArgb(44, 45, 79);

            SolidBrush backgroundBrush = new SolidBrush(backgroundColor);


            g.FillRectangle(backgroundBrush, 0, 0, Width, Height);

            if (stars != null)
            {
                for (int i = 0; i < 9; i++)
                {
                    stars[i].Draw(g);
                }
            }

            if (planets != null)
            {
                for (int i = 0; i < 3; i++)
                {
                    planets[i].Draw(g);
                }
            }

            ship.Draw(g);

            for (int i = 0; i <= bulletNumber; i++)
            {
                bullets[i].Draw(g);
            }

            for (int i = 0; i < enemyNumber; i++)
            {
                enemies[i].Draw(g);
            }

            for (int i = 0; i <  explosionNumber; i++)
            {
                explosions[i].Draw(g);
            }

        }

        private void Form1_Load(object sender, EventArgs e)
        {
            ship.PosX = Width / 2;
            ship.PosY = Height - 100;
            //Debug.WriteLine(Width);

            for (int i = 0; i < enemyNumber; i++)
            {
                enemies[i].SetOrigin((i + 1) * Width / 4, 100);
            }
            timer2.Start();
        }


        private void Form1_KeyDown(object sender, KeyEventArgs e)
        {
            System.Windows.Forms.Keys key = (System.Windows.Forms.Keys)e.KeyValue;
            int step = 5;

            switch (key)
            {
                case Keys.Left:
                    {
                        this.Invalidate(new Rectangle(
                            ship.PosX - 40,
                            ship.PosY,
                            80,
                            80));

                        ship.PosX = ship.PosX - step;

                        this.Invalidate(new Rectangle(
                            ship.PosX - 40,
                            ship.PosY,
                            80,
                            80));

                        break;
                    }
                case Keys.Right:
                    {
                        this.Invalidate(new Rectangle(
                            ship.PosX - 40,
                            ship.PosY,
                            80,
                            80));

                        ship.PosX = ship.PosX + step;

                        this.Invalidate(new Rectangle(
                            ship.PosX - 40,
                            ship.PosY,
                            80,
                            80));

                        break;
                    }
                case Keys.Space:
                    {
                        this.timer1.Start();

                        if (bulletNumber + 1 >= BULLET_MAX)
                        {
                            for (int i = 0; i < BULLET_MAX; i++)
                            {
                                if (bullets[i].PosX == bullets[i].PosY && bullets[i].PosX == -1)
                                {
                                    bullets[i].PosX = ship.PosX - 5;
                                    bullets[i].PosY = ship.PosY - 20;
                                    break;
                                }
                            }
                        }
                        else
                        {
                            bulletNumber++;
                            bullets[bulletNumber].PosX = ship.PosX - 5;
                            bullets[bulletNumber].PosY = ship.PosY - 20;
                        }
                        //                        Debug.WriteLine(bulletNumber);

                        break;
                    }
                case Keys.Q:
                    {

                        break;
                    }

            }
            //            this.Invalidate(true);
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            for (int i = 0; i <= bulletNumber; i++)
            {
                this.Invalidate(new Rectangle(
                    bullets[i].PosX - 10,
                    bullets[i].PosY - 10,
                    25,
                    25));

                bullets[i].PosY = bullets[i].PosY - 5;

                if (bullets[i].PosY < 0)
                {
                    bullets[i].PosX = -1;
                    bullets[i].PosY = -1;
                }
                this.Invalidate(new Rectangle(
                    bullets[i].PosX - 10,
                    bullets[i].PosY - 10,
                    25,
                    25));
            }

        }

        private void timer2_Tick(object sender, EventArgs e)
        {
            if (enemyNumber > 0)
            {
                if (enemies[0].GetPosX() < 40 || enemies[enemyNumber - 1].GetPosX() > Width - 80)
                {
                    for (int i = 0; i < enemyNumber; i++)
                    {
                        enemies[i].ChangeDirection();
                    }
                }

                if (enemies[0].GetPosY() <= maxHeight || enemies[0].GetPosY() >= minHeight)
                {
                    for (int i = 0; i < enemyNumber; i++)
                    {
                        enemies[i].ChangeVertical();
                    }
                }

                for (int i = 0; i < enemyNumber; i++)
                {
                    this.Invalidate(new Rectangle(
                    enemies[i].GetPosX() - 40,
                    enemies[i].GetPosY() - 40,
                    80,
                    80));

                    enemies[i].Move();

                    this.Invalidate(new Rectangle(
                    enemies[i].GetPosX() - 40,
                    enemies[i].GetPosY() - 40,
                    80,
                    80));
                }

                for (int i = 0; i < enemyNumber; i++)
                {
                    for (int j = 0; j < bulletNumber; j++)
                    {
                        if (enemyNumber == 0)
                        {
                            break;
                        }
                        enemies[i].CheckCollision(bullets[j]);

                        if (bullets[i].PosY != -1 && bullets[i].PosX != -1 && enemies[i].GetCollision())
                        {
                            explosions[i].Create(enemies[i].GetPosX(), enemies[i].GetPosY() - 7);
                            enemies.RemoveAt(i);
                            bullets[j].PosX = -1;
                            bullets[j].PosY = -1;
                            enemyNumber--;

                            break;
                        }
                    }
                }

                for (int i = 0; i < enemyNumber; i++)
                {
                    enemies[i].Shoot();
                }
            }

            timer2Counter++;
            if (timer2Counter == 30)
            {
                for (int i = 0; i < explosionNumber; i++)
                {
                    explosions[i].Remove();

                    this.Invalidate(new Rectangle(
                    explosions[i].GetPosX() - 40,
                    explosions[i].GetPosY() - 40,
                    80,
                    80));
                }

                timer2Counter = 1;

            }
        }
    }
}