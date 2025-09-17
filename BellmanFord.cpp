#include <iostream>
#include <vector>
#include <fstream>
#include <climits>
#include <cstdlib>
#include <ctime>
using namespace std;

vector<int> bellman_ford(int start, int n, vector<vector<int>> edges) {
    vector<int> distance(n, INT_MAX);
    distance[start] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < edges.size(); j++) {
            int from = edges[j][0];
            int to = edges[j][1];
            int weight = edges[j][2];
            if (distance[from] != INT_MAX && distance[from] + weight < distance[to]) {
                if (i == n - 1) {
                    return vector<int>(1, -1);
                }
                distance[to] = distance[from] + weight;
            }
        }
    }
    return distance;
}

vector<vector<int>> make_graph(int n) {
    vector<vector<int>> edges;
    for (int i = 0; i < n - 1; i++) {
        int weight = (rand() % 101) - 50;
        if (weight == 0) weight = 1;
        edges.push_back(vector<int>{i, i + 1, weight});
    }
    for (int i = 0; i < 7; i++) {
        int from = rand() % n;
        int to = rand() % n;
        if (from == to) continue;
        int weight = (rand() % 101) - 50;
        if (weight == 0) weight = -7;
        edges.push_back(vector<int>{from, to, weight});
    }
    return edges;
}

int main() {
    int n = 50;
    srand(time(0));
    ofstream file("output.txt");
    for (int t = 0; t < 10; t++) {
        vector<vector<int>> graph = make_graph(n);
        vector<int> dist = bellman_ford(0, n, graph);
        if (file.is_open()) {
            for (int i = 0; i < graph.size(); i++) {
                file << graph[i][0] << " " << graph[i][1] << " " << graph[i][2] << "\n";
            }
            file << "\n";
            if (dist.size() == 1) {
                file << -1;
            } else {
                for (int i = 0; i < n; i++) {
                    file << dist[i] << " ";
                }
            }
            file << "\n\n\n";
        }
    }
    file.close();
    return 0;
}
