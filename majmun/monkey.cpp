#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <cstdio>
using namespace std;

struct Vec3 {
    double xCoord, yCoord, zCoord;
};

struct Mat3 {
    double values[3][3] = {0};
   
    Vec3 apply(Vec3 vec) {
        return {
            values[0][0]*vec.xCoord + values[0][1]*vec.yCoord + values[0][2]*vec.zCoord,
            values[1][0]*vec.xCoord + values[1][1]*vec.yCoord + values[1][2]*vec.zCoord,
            values[2][0]*vec.xCoord + values[2][1]*vec.yCoord + values[2][2]*vec.zCoord
        };
    }
};

Mat3 multiplyMatrices(Mat3 first, Mat3 second) {
    Mat3 result;
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            for (int idx = 0; idx < 3; idx++)
                result.values[row][col] += first.values[row][idx] * second.values[idx][col];
    return result;
}

int main() {
    ifstream inFile("monkey.obj");
    ofstream outFile("new_monkey.obj");
    string currentLine;

    if (!inFile.is_open()) return 1;

    const double PI_VAL = 3.141592653589793;
    double angleX = 45.0 * PI_VAL / 180.0;
    double angleY = 27.0 * PI_VAL / 180.0;
    double angleZ = 10.0 * PI_VAL / 180.0;

    Mat3 rotX = {{{1, 0, 0}, {0, cos(angleX), -sin(angleX)}, {0, sin(angleX), cos(angleX)}}};  
    Mat3 rotY = {{{cos(angleY), 0, sin(angleY)}, {0, 1, 0}, {-sin(angleY), 0, cos(angleY)}}};
    Mat3 rotZ = {{{cos(angleZ), -sin(angleZ), 0}, {sin(angleZ), cos(angleZ), 0}, {0, 0, 1}}};
   
    Mat3 scaleMat = {{{1.5, 0, 0}, {0, -1.0, 0}, {0, 0, 1.0}}};

    Mat3 finalMatrix = multiplyMatrices(scaleMat, multiplyMatrices(rotZ, multiplyMatrices(rotY, rotX)));

    while (getline(inFile, currentLine)) {
        if (currentLine.size() > 2 && currentLine[0] == 'v' && currentLine[1] == ' ') {
            Vec3 vertex;
           
            if (sscanf(currentLine.c_str(), "v %lf %lf %lf", &vertex.xCoord, &vertex.yCoord, &vertex.zCoord) == 3) {
                Vec3 transformedVertex = finalMatrix.apply(vertex);

                outFile << "v " << fixed << setprecision(4)
                        << transformedVertex.xCoord << " "
                        << transformedVertex.yCoord << " "
                        << transformedVertex.zCoord << "\n";
            }
        } else {
            outFile << currentLine << "\n";
        }
    }

    inFile.close();
    outFile.close();
    return 0;
}