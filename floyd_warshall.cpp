#include <iostream>
#include <vector>
#include <climits>
using namespace std;

void print_matrix(const vector<vector<int>>& dist) {
    for (int i = 0; i < dist.size(); i++) {
        for (int j = 0; j < dist[i].size(); j++) {
            if (dist[i][j] == INT_MAX) cout << "INF ";
            else cout << dist[i][j] << " ";
        }
        cout << "\n";
    }
}

void floyd_warshall(int n, vector<vector<int>>& dist) {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] < INT_MAX && dist[k][j] < INT_MAX) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
        cout << "\nAfter iteration k = " << k << ":\n";
        print_matrix(dist);
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
    for (int i = 0; i < n; i++) dist[i][i] = 0;

    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        dist[a][b] = w;
    }

    floyd_warshall(n, dist);

    vector<vector<int>> copy = dist;
    floyd_warshall(n, dist);

    if (dist != copy) {
        cout << "Negative cycle detected!\n";
    } else {
        cout << "No negative cycle.\n";
    }

    return 0;
}