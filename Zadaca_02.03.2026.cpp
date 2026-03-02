#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

struct Point {
    double a, b, c;
    Point(double a = 0, double b = 0, double c = 0) {
        this->a = a;
        this->b = b;
        this->c = c;
    }
};

struct Shape {
    Point p1, p2, p3, p4;
    Shape(Point p1, Point p2, Point p3, Point p4) {
        this->p1 = p1;
        this->p2 = p2;
        this->p3 = p3;
        this->p4 = p4;
    }
};

void shift(Shape &s) {
    s.p1.a += 2.0;
    s.p2.a += 2.0;
    s.p3.a += 2.0;
    s.p4.a += 2.0;
}

void turn(Shape &s) {
    double angle = 45.0 * M_PI / 180.0;
    double sn = sin(angle);
    double cs = cos(angle);

    double mx = (s.p1.a + s.p2.a + s.p3.a + s.p4.a) / 4.0;
    double my = (s.p1.b + s.p2.b + s.p3.b + s.p4.b) / 4.0;

    double dx1 = s.p1.a - mx; double dy1 = s.p1.b - my;
    s.p1.a = dx1 * cs - dy1 * sn + mx;
    s.p1.b = dx1 * sn + dy1 * cs + my;

    double dx2 = s.p2.a - mx; double dy2 = s.p2.b - my;
    s.p2.a = dx2 * cs - dy2 * sn + mx;
    s.p2.b = dx2 * sn + dy2 * cs + my;

    double dx3 = s.p3.a - mx; double dy3 = s.p3.b - my;
    s.p3.a = dx3 * cs - dy3 * sn + mx;
    s.p3.b = dx3 * sn + dy3 * cs + my;

    double dx4 = s.p4.a - mx; double dy4 = s.p4.b - my;
    s.p4.a = dx4 * cs - dy4 * sn + mx;
    s.p4.b = dx4 * sn + dy4 * cs + my;
}

void scale(Shape &s) {
    double val = 2.0;
    double mx = (s.p1.a + s.p2.a + s.p3.a + s.p4.a) / 4.0;
    double my = (s.p1.b + s.p2.b + s.p3.b + s.p4.b) / 4.0;
    double mz = (s.p1.c + s.p2.c + s.p3.c + s.p4.c) / 4.0;

    s.p1.a = mx + (s.p1.a - mx) * val; s.p1.b = my + (s.p1.b - my) * val; s.p1.c = mz + (s.p1.c - mz) * val;
    s.p2.a = mx + (s.p2.a - mx) * val; s.p2.b = my + (s.p2.b - my) * val; s.p2.c = mz + (s.p2.c - mz) * val;
    s.p3.a = mx + (s.p3.a - mx) * val; s.p3.b = my + (s.p3.b - my) * val; s.p3.c = mz + (s.p3.c - mz) * val;
    s.p4.a = mx + (s.p4.a - mx) * val; s.p4.b = my + (s.p4.b - my) * val; s.p4.c = mz + (s.p4.c - mz) * val;
}

int main() {
    ifstream input("file.txt");
    string row;
    vector<Point> nodes;

    if (input.is_open()) {
        while (getline(input, row)) {
            stringstream buffer(row);
            string key;
            buffer >> key;
            if (key == "v") {
                double val1, val2, val3;
                buffer >> val1 >> val2 >> val3;
                nodes.push_back(Point(val1, val2, val3));
            }
        }
        input.close();
    }

    if (nodes.size() >= 4) {
        Shape obj(nodes[0], nodes[1], nodes[2], nodes[3]);

        cout << "Pocetno" << obj.p1.a << ", " << obj.p1.b << endl;

        shift(obj);
        cout << "Translacija" << obj.p1.a << endl;

        turn(obj);
        cout << "Rotacija " << obj.p1.a << ", " << obj.p1.b << endl;

        scale(obj);
        cout << "Homotetija " << obj.p1.a << ", " << obj.p1.b << endl;
    } else {
        cout << "Greska" << endl;
    }

    return 0;
}