#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <algorithm>
// 定义一个表示点的结构体
struct Point {
    int x, y;
};

// 存储多边形顶点的向量
std::vector<Point> polygon_vertices;

// 比较函数，根据y值对点进行排序
bool compareY(Point a, Point b) {
    return a.y < b.y;
}

// 初始化OpenGL
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 640, 0, 480);
}

// 显示回调函数
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    // 绘制多边形
    glBegin(GL_LINE_LOOP);
    for (auto vertex : polygon_vertices) {
        glVertex2i(vertex.x, vertex.y);
    }
    glEnd();

    // 对多边形顶点按照y值进行排序
    std::sort(polygon_vertices.begin(), polygon_vertices.end(), compareY);

    // 扫描线算法
    for (int current_y = polygon_vertices.front().y; current_y <= polygon_vertices.back().y; ++current_y) {
        std::vector<int> intersections;

        // 查找交点
        for (size_t i = 0, j = polygon_vertices.size() - 1; i < polygon_vertices.size(); j = i++) {
            if ((polygon_vertices[i].y > current_y) != (polygon_vertices[j].y > current_y)) {
                int intersection_x = (polygon_vertices[i].x + (current_y - polygon_vertices[i].y) * (polygon_vertices[j].x - polygon_vertices[i].x) / (polygon_vertices[j].y - polygon_vertices[i].y));
                intersections.push_back(intersection_x);
            }
        }

        // 对交点进行排序
        std::sort(intersections.begin(), intersections.end());

        // 绘制扫描线
        glBegin(GL_LINES);
        for (size_t i = 0; i < intersections.size(); i += 2) {
            glVertex2i(intersections[i], current_y);
            glVertex2i(intersections[i + 1], current_y);
        }
        glEnd();
    }

    glFlush();
}

int main(int argc, char** argv) {
    // 输入多边形顶点
    int n;
    std::cout << "请输入多边形顶点数: ";
    std::cin >> n;
    std::cout << "请依次输入多边形顶点（x, y）: " << std::endl;

    for (int i = 0; i < n; ++i) {
        Point vertex;
        std::cin >> vertex.x >> vertex.y;
        polygon_vertices.push_back(vertex);
    }

    // 初始化
    // 初始化GLUT并设置窗口属性
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("多边形扫描转换算法");

    // 设置OpenGL回调函数
    init();
    glutDisplayFunc(display);

    // 进入GLUT事件处理循环
    glutMainLoop();

    return 0;
}
