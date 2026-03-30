#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Point {
    double x, y;

    Point(double _x = 0, double _y = 0) {
        x = _x;
        y = _y;
    }
};

struct Edge {
    Point startPoint;
    Point endPoint;

    Edge(Point _start, Point _end) {
        startPoint = _start;
        endPoint = _end;
    }

    bool isSameEdge(Edge other) {
        bool matchStraight = (startPoint.x == other.startPoint.x && startPoint.y == other.startPoint.y && endPoint.x == other.endPoint.x && endPoint.y == other.endPoint.y);
        bool matchFlipped = (startPoint.x == other.endPoint.x && startPoint.y == other.endPoint.y && endPoint.x == other.startPoint.x && endPoint.y == other.startPoint.y);
        return matchStraight || matchFlipped;
    }
};

struct Triangle {
    Point v1, v2, v3;

    Triangle(Point _v1, Point _v2, Point _v3) {
        v1 = _v1;
        v2 = _v2;
        v3 = _v3;
    }
    
    bool isPointInsideCircumcircle(Point p) const {
        double x1 = v1.x, y1 = v1.y;
        double x2 = v2.x, y2 = v2.y;
        double x3 = v3.x, y3 = v3.y;

        double D = 2 * (x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2));
        double centerX = ((x1 * x1 + y1 * y1) * (y2 - y3) + (x2 * x2 + y2 * y2) * (y3 - y1) + (x3 * x3 + y3 * y3) * (y1 - y2)) / D;
        double centerY = ((x1 * x1 + y1 * y1) * (x3 - x2) + (x2 * x2 + y2 * y2) * (x1 - x3) + (x3 * x3 + y3 * y3) * (x2 - x1)) / D;
        
        double radiusSquared = pow(x1 - centerX, 2) + pow(y1 - centerY, 2);
        double distanceSquared = pow(p.x - centerX, 2) + pow(p.y - centerY, 2);
        
        return distanceSquared < radiusSquared;
    }
};

vector<Triangle> bowyerWatson(vector<Point> inputPoints) {
    Point sv1(-5000, -5000);
    Point sv2(5000, -5000);
    Point sv3(0, 5000);
    Triangle superTriangle(sv1, sv2, sv3);

    vector<Triangle> mesh;
    mesh.push_back(superTriangle);

    for (int i = 0; i < inputPoints.size(); i++) {
        Point currentPoint = inputPoints[i];
        vector<Triangle> invalidTriangles;

        for (int j = 0; j < mesh.size(); j++) {
            if (mesh[j].isPointInsideCircumcircle(currentPoint)) {
                invalidTriangles.push_back(mesh[j]);
            }
        }

        vector<Edge> holeEdges;
        for (int j = 0; j < invalidTriangles.size(); j++) {
            Triangle tempTri = invalidTriangles[j];
            Edge edges[3] = { Edge(tempTri.v1, tempTri.v2), Edge(tempTri.v2, tempTri.v3), Edge(tempTri.v3, tempTri.v1) };

            for (int e = 0; e < 3; e++) {
                bool isShared = false;
                for (int k = 0; k < invalidTriangles.size(); k++) {
                    if (j == k) continue;
                    Triangle otherTri = invalidTriangles[k];
                    Edge otherEdges[3] = { Edge(otherTri.v1, otherTri.v2), Edge(otherTri.v2, otherTri.v3), Edge(otherTri.v3, otherTri.v1) };
                    for (int oe = 0; oe < 3; oe++) {
                        if (edges[e].isSameEdge(otherEdges[oe])) isShared = true;
                    }
                }
                if (!isShared) holeEdges.push_back(edges[e]);
            }
        }

        vector<Triangle> cleanMesh;
        for (int j = 0; j < mesh.size(); j++) {
            bool isInvalid = false;
            for (int k = 0; k < invalidTriangles.size(); k++) {
                if (mesh[j].v1.x == invalidTriangles[k].v1.x &&
                    mesh[j].v1.y == invalidTriangles[k].v1.y &&
                    mesh[j].v2.x == invalidTriangles[k].v2.x &&
                    mesh[j].v2.y == invalidTriangles[k].v2.y &&
                    mesh[j].v3.x == invalidTriangles[k].v3.x &&
                    mesh[j].v3.y == invalidTriangles[k].v3.y) {
                    isInvalid = true;
                }
            }
            if (!isInvalid) cleanMesh.push_back(mesh[j]);
        }
        mesh = cleanMesh;

        for (int j = 0; j < holeEdges.size(); j++) {
            mesh.push_back(Triangle(holeEdges[j].startPoint, holeEdges[j].endPoint, currentPoint));
        }
    }

    vector<Triangle> finalTriangulation;
    Point superVertices[3] = { Point(-5000, -5000), Point(5000, -5000), Point(0, 5000) };
    
    for (int i = 0; i < mesh.size(); i++) {
        Triangle currentTri = mesh[i];
        bool touchesSuperTriangle = false;
        
        for (int s = 0; s < 3; s++) {
            if ((currentTri.v1.x == superVertices[s].x && currentTri.v1.y == superVertices[s].y) ||
                (currentTri.v2.x == superVertices[s].x && currentTri.v2.y == superVertices[s].y) ||
                (currentTri.v3.x == superVertices[s].x && currentTri.v3.y == superVertices[s].y)) {
                touchesSuperTriangle = true;
            }
        }

        if (!touchesSuperTriangle) {
            finalTriangulation.push_back(currentTri);
        }
    }

    return finalTriangulation;
}

int main() {
    vector<Point> myPoints;
    myPoints.push_back(Point(50, 50));
    myPoints.push_back(Point(100, 200));
    myPoints.push_back(Point(300, 150));
    myPoints.push_back(Point(400, 400));
    myPoints.push_back(Point(150, 350));
    myPoints.push_back(Point(200, 50));

    vector<Triangle> result = bowyerWatson(myPoints);

    cout << "Total Triangles: " << result.size() << endl;
    for (int i = 0; i < result.size(); i++) {
        cout << "Triangle " << i + 1 << ": "
             << "(" << result[i].v1.x << "," << result[i].v1.y << ") "
             << "(" << result[i].v2.x << "," << result[i].v2.y << ") "
             << "(" << result[i].v3.x << "," << result[i].v3.y << ")" << endl;
    }

    return 0;
}