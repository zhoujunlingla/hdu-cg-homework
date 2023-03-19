#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

void drawLine(int x1, int y1, int x2, int y2)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    glBegin(GL_POINTS);

    while (true) {
        glVertex2i(x1, y1);

        if ((x1 == x2) && (y1 == y2)) {
            break;
        }

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }

    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 0.0, 0.0); // 设置绘制颜色为红色
    glPointSize(2.0); // 设置点大小为2

    drawLine(50, 50, 200, 200); // 画一条从 (50, 50) 到 (200, 200) 的线段

    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bresenham Line");
    glClearColor(1.0, 1.0, 1.0, 0.0); // 设置背景颜色为白色
    gluOrtho2D(0.0, 400.0, 0.0, 400.0); // 设置坐标系范围
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
