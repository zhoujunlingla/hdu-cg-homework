#include <GL/glut.h>
#include <stack>

using namespace std;

void regionFill(int x, int y, float* fillColor, float* bgColor) {
    stack<pair<int, int>> s;
    s.push(make_pair(x, y));
    while (!s.empty()) {
        pair<int, int> p = s.top();
        s.pop();
        int i = p.first, j = p.second;
        float pixelColor[3];
        glReadPixels(i, j, 1, 1, GL_RGB, GL_FLOAT, pixelColor);
        if (pixelColor[0] == bgColor[0] && pixelColor[1] == bgColor[1] && pixelColor[2] == bgColor[2]) {
            glColor3fv(fillColor);
            glBegin(GL_POINTS);
            glVertex2i(i, j);
            glEnd();
            s.push(make_pair(i+1, j));
            s.push(make_pair(i-1, j));
            s.push(make_pair(i, j+1));
            s.push(make_pair(i, j-1));
        }
    }
}

void display() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(0.0, 0.0);
    glVertex2f(0.0, 100.0);
    glVertex2f(100.0, 100.0);
    glVertex2f(100.0, 0.0);
    glEnd();
    glFlush();
    float fillColor[] = {0.0, 1.0, 0.0};
    float bgColor[] = {1.0, 1.0, 1.0};
    regionFill(50, 50, fillColor, bgColor);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Region Fill");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 400.0, 0.0, 400.0);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
