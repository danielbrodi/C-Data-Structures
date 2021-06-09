
#include <graphics.h>
#include <stdio.h>
#include <time.h>
  

void crackers()
{
    
    setfillstyle(SOLID_FILL, RED);
    line(80, 680, 130, 680);
    line(80, 680, 105, 630);
    line(105, 630, 130, 680);
    floodfill(105, 650, 15);
  
   
    setfillstyle(SOLID_FILL, BLUE);
    line(300, 680, 350, 680);
    line(300, 680, 325, 630);
    line(325, 630, 350, 680);
    floodfill(325, 650, 15);
  
  
    setfillstyle(SOLID_FILL, BROWN);
    line(500, 680, 550, 680);
    line(500, 680, 525, 630);
    line(525, 630, 550, 680);
    floodfill(525, 650, 15);
  
    setfillstyle(SOLID_FILL, GREEN);
    line(700, 680, 750, 680);
    line(700, 680, 725, 630);
    line(725, 630, 750, 680);
    floodfill(725, 650, 15);
  
   
    setfillstyle(SOLID_FILL, CYAN);
    line(920, 680, 970, 680);
    line(920, 680, 945, 630);
    line(945, 630, 970, 680);
    floodfill(945, 650, 15);
}
  

void fire()
{
    int v = 625, u = 630, g = 630, h = 625,
        a = 325, n = 325, e = 325, x = 320, j = 330;
    int b = 525, m = 525, f = 525, y = 520,
        k = 530, c = 725, i = 725, o = 725,
        z = 720, l = 730;
    int t = 630, s = 625;
  

    crackers();
  

    while (h != 435) {
        crackers();
  
      
        line(n, g, n, h);
        line(m, u, m, v);
        line(o, u, o, v);
        line(a, u, x, v);
        line(b, u, y, v);
        line(c, u, z, v);
        line(e, t, j, s);
        line(f, t, k, s);
        line(i, t, l, s);
  

        a = a - 10;
        x = x - 10;
        u = u - 10;
        v = v - 10;
        g = g - 10;
        h = h - 10;
        b = b - 10;
        y = y - 10;
        c = c - 10;
        z = z - 10;
        t = t - 10;
        s = s - 10;
        e = e + 10;
        f = f + 10;
        i = i + 10;
        j = j + 10;
        k = k + 10;
        l = l + 10;
  

        delay(30);
    }
}
  

void mess()
{
    
    settextstyle(8, 0, 5);
  
   
    outtextxy(200, 350, "HAPPY"
                        " BIRTHDAY TO "
                        "ANYONE....");
}
  

void launch()
{
    int q1 = 630, q2 = 590;
  

    while (q2 != 330) {
     
        cleardevice();

        fire();
        mess();
  

        line(105, q1, 105, q2);
        line(945, q1, 945, q2);
  

        q1 = q1 - 20;
        q2 = q2 - 20;
  

        fire();
        mess();
  

        delay(30);
    }
}
  

void main()
{
    int gd = DETECT, gm;
  

    initgraph(&gd, &gm, "C:\\"
                        "turboc3\\bgi");
  

    launch();
  

    setfillstyle(SOLID_FILL, WHITE);
    circle(105, 370, 20);
    floodfill(104, 371, 15);
    floodfill(106, 371, 15);
  

    setfillstyle(SOLID_FILL, WHITE);
    circle(945, 370, 20);
    floodfill(944, 371, 15);
    floodfill(946, 371, 15);
  

    getch();
  

    closegraph();
  
    return 0;
}
