#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

struct Point3D {
    double x, y, z;

    Point3D(double x = 0, double y = 0, double z = 0) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
};

struct Square {
    Point3D p1, p2, p3, p4;

    Square(Point3D p1, Point3D p2, Point3D p3, Point3D p4) {
        this->p1 = p1;
        this->p2 = p2;
        this->p3 = p3;
        this->p4 = p4;
    }
};

void translateRight(Square &square) {
    square.p1.x += 2.0;
    square.p2.x += 2.0;
    square.p3.x += 2.0;
    square.p4.x += 2.0;
}

void rotate45(Square &square) {

    double angle = 45.0 * M_PI / 180.0;
    double sinA = sin(angle);
    double cosA = cos(angle);

    double centerX = (square.p1.x + square.p2.x + square.p3.x + square.p4.x) / 4.0;
    double centerY = (square.p1.y + square.p2.y + square.p3.y + square.p4.y) / 4.0;

    double x1 = square.p1.x - centerX;
    double y1 = square.p1.y - centerY;

    square.p1.x = x1 * cosA - y1 * sinA + centerX;
    square.p1.y = x1 * sinA + y1 * cosA + centerY;

    double x2 = square.p2.x - centerX;
    double y2 = square.p2.y - centerY;

    square.p2.x = x2 * cosA - y2 * sinA + centerX;
    square.p2.y = x2 * sinA + y2 * cosA + centerY;

    double x3 = square.p3.x - centerX;
    double y3 = square.p3.y - centerY;

    square.p3.x = x3 * cosA - y3 * sinA + centerX;
    square.p3.y = x3 * sinA + y3 * cosA + centerY;

    double x4 = square.p4.x - centerX;
    double y4 = square.p4.y - centerY;

    square.p4.x = x4 * cosA - y4 * sinA + centerX;
    square.p4.y = x4 * sinA + y4 * cosA + centerY;
}

void scaleSquare(Square &square) {

    double scaleFactor = 2.0;

    double centerX = (square.p1.x + square.p2.x + square.p3.x + square.p4.x) / 4.0;
    double centerY = (square.p1.y + square.p2.y + square.p3.y + square.p4.y) / 4.0;
    double centerZ = (square.p1.z + square.p2.z + square.p3.z + square.p4.z) / 4.0;

    square.p1.x = centerX + (square.p1.x - centerX) * scaleFactor;
    square.p1.y = centerY + (square.p1.y - centerY) * scaleFactor;
    square.p1.z = centerZ + (square.p1.z - centerZ) * scaleFactor;

    square.p2.x = centerX + (square.p2.x - centerX) * scaleFactor;
    square.p2.y = centerY + (square.p2.y - centerY) * scaleFactor;
    square.p2.z = centerZ + (square.p2.z - centerZ) * scaleFactor;

    square.p3.x = centerX + (square.p3.x - centerX) * scaleFactor;
    square.p3.y = centerY + (square.p3.y - centerY) * scaleFactor;
    square.p3.z = centerZ + (square.p3.z - centerZ) * scaleFactor;

    square.p4.x = centerX + (square.p4.x - centerX) * scaleFactor;
    square.p4.y = centerY + (square.p4.y - centerY) * scaleFactor;
    square.p4.z = centerZ + (square.p4.z - centerZ) * scaleFactor;
}

int main() {

    ifstream inputFile("file.txt");
    string line;
    vector<Point3D> vertexList;

    if (inputFile.is_open()) {

        while (getline(inputFile, line)) {

            stringstream ss(line);
            string tag;
            ss >> tag;

            if (tag == "v") {
                double x, y, z;
                ss >> x >> y >> z;
                vertexList.push_back(Point3D(x, y, z));
            }
        }

        inputFile.close();
    }

    if (vertexList.size() >= 4) {

        Square mySquare(vertexList[0], vertexList[1], vertexList[2], vertexList[3]);

        cout << "Initial: " << mySquare.p1.x << ", " << mySquare.p1.y << endl;

        translateRight(mySquare);
        cout << "Translation: " << mySquare.p1.x << endl;

        rotate45(mySquare);
        cout << "Rotation: " << mySquare.p1.x << ", " << mySquare.p1.y << endl;

        scaleSquare(mySquare);
        cout << "Scaling: " << mySquare.p1.x << ", " << mySquare.p1.y << endl;

    } else {
        cout << "Error: Not enough vertices" << endl;
    }

    return 0;
}