#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>
#define PI 3.1415926535
#define P2 (PI/2)
#define P3 (3*PI/2)

float px, py, pdx, pdy, pa;

void drawPlayer()
{
    glColor3f(1,1,0);
    glPointSize(8);
    glBegin(GL_POINTS);
    glVertex2i(px,py); // NOLINT(*-narrowing-conversions)
    glEnd();

    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2i(px, py); // NOLINT(*-narrowing-conversions)
    glVertex2i(px+pdx*5, py+pdy*5); // NOLINT(*-narrowing-conversions)
    glEnd();
}

int mapX=8, mapY=8, mapS=64;
int map[]=
{
    1,1,1,1,1,1,1,1,
    1,0,1,0,0,0,0,1,
    1,0,1,0,0,1,0,1,
    1,0,0,0,0,0,0,1,
    1,0,0,1,0,0,0,1,
    1,0,0,1,0,0,0,1,
    1,0,0,0,0,1,0,1,
    1,1,1,1,1,1,1,1,
};

void drawMap2D() {
    for (int y = 0; y<mapY;y++)
    {
        for (int x = 0; x<mapX;x++)
        {
            if (map[y*mapX+x]==1) {glColor3f(1,1,1);} else {glColor3f(0,0,0);}
            const int xo = x * mapS;
            const int yo = y * mapS;
            glBegin(GL_QUADS);
            glVertex2i(xo      +1, yo        +1);
            glVertex2i(xo      +1, yo+mapS   -1);
            glVertex2i(xo+mapS -1, yo+mapS   -1);
            glVertex2i(xo+mapS -1, yo        +1);
            glEnd();
        }
    }
}

float dist(float ax, float ay, float bx, float by, float ang)
{
    return ( sqrt( (bx-ax)*(bx-ax) + (by-ay)*(by-ay) ) );
}

void drawRays3D()
{
    int r, mx, my, mp, dof; float rx, ry, ra, xo, yo;
    ra = pa;
    for (r=0; r<1; r++)
    {
        //---Check Horizontal Lines---

        dof=0;
        float disH=100000, hx=px, hy=py;
        float aTan=-1/tan(ra);

        //TODO Add detailed explaintion here.

        if (ra>PI) { ry = (((int)py>>6)<<6) - 0.0001;     rx = (py-ry) * aTan + px;     yo = -64;     xo = -yo * aTan;    } // Looking up.
        if (ra<PI) { ry = (((int)py>>6)<<6) + 64;         rx = (py-ry) * aTan + px;     yo = 64;      xo = -yo * aTan;    } // Looking down.
        if (ra==0 || ra==PI) { rx = px; ry = py; dof = 8; } // Looking lef or right.

        while (dof<8)
        {
            mx=(int) (rx)>>6; my=(int) (ry)>>6; mp=my*mapX+mx;
            if (mp>0 && mp<mapX*mapY && map[mp]==1)
            {
                hx=rx; hy=ry; disH=dist(px,py,hx,hy, ra);
                dof=8;
            } // Hit a wall.
            else { rx+=xo; ry+=yo; dof+=1;} // Next line.
        }

        //---Check Vertical Lines---

        dof=0;
        float disV=100000, vx=px, vy=py;
        float nTan=-tan(ra);

        if (ra>P2 && ra<P3) { rx = (((int)px>>6)<<6) - 0.0001;     ry = (px-rx) * nTan + py;     xo = -64;     yo = -xo * nTan;    } // Looking left.
        if (ra<P2 || ra>P3) { rx = (((int)px>>6)<<6) + 64;         ry = (px-rx) * nTan + py;     xo = 64;      yo = -xo * nTan;    } // Looking right.
        if (ra==0 || ra==PI) { rx = px; ry = py; dof = 8; } // Looking up or down.

        while (dof<8)
        {
            mx=(int) (rx)>>6; my=(int) (ry)>>6; mp=my*mapX+mx;
            if (mp>0 && mp<mapX*mapY && map[mp]==1)
            {
                vx=rx; vy=ry; disV=dist(px,py,vx,vy, ra);
                dof=8;
            } // Hit a wall.
            else { rx+=xo; ry+=yo; dof+=1;} // Next line.
        }

        if (disV < disH) { rx=vx; ry=vy; }
        if (disH < disV) { rx=hx; ry=hy; }

        glColor3f(1,0,0);
        glLineWidth(1);
        glBegin(GL_LINES);
        glVertex2i(px, py);
        glVertex2i(rx, ry);
        glEnd();
    }

}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawMap2D();
    drawRays3D();
    drawPlayer();
    glutSwapBuffers();
}

void buttons(unsigned char key, int x, int y)
{
    if (key=='a') { pa-=0.1; if ( pa < 0    ) { pa+=2*PI; } pdx=std::cos(pa)*5; pdy=std::sin(pa)*5; }
    if (key=='d') { pa+=0.1; if ( pa > 2*PI ) { pa-=2*PI; } pdx=std::cos(pa)*5; pdy=std::sin(pa)*5; }
    if (key=='w') { px+=pdx; py+=pdy; }
    if (key=='s') { px-=pdx; py-=pdy; }
    glutPostRedisplay();
}

void init()
{
    glClearColor(0.3, 0.3, 0.3, 0);
    gluOrtho2D(0.0, 1024.0, 512.0, 0.0);
    px=300; py=300; pdx=std::cos(pa)*5; pdy=std::sin(pa)*5;
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1024, 512);
    glutCreateWindow("Wolfenstein 3D Engine");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(buttons);
    glutMainLoop();
}