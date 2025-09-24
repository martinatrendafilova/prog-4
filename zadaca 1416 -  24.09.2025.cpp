#include <iostream>
#include <vector>
#include <climits>
using namespace std;

void floyd_warshall(int n, vector<vector<int>>& dist) {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] < INT_MAX && dist[k][j] < INT_MAX) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
}

long long total_cost(int n, const vector<vector<int>>& dist, int penalty) {
    long long cost = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            if (dist[i][j] < INT_MAX)
                cost += dist[i][j];
            else
                cost += penalty;
        }
    }
    return cost;
}

int main() {
    int n, m, penalty;
    cin >> n >> m >> penalty;

    vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
    vector<pair<int,int>> edges;

    for (int i = 0; i < n; i++) dist[i][i] = 0;

    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        a--; b--;
        dist[a][b] = dist[b][a] = w;
        edges.push_back(make_pair(a, b));
    }

    floyd_warshall(n, dist);
    long long base_cost = total_cost(n, dist, penalty);

    long long max_cost = 0;
    for (int i = 0; i < edges.size(); i++) {
        int u = edges[i].first;
        int v = edges[i].second;

        vector<vector<int>> temp = dist;
        temp[u][v] = temp[v][u] = INT_MAX;
        floyd_warshall(n, temp);
        max_cost = max(max_cost, total_cost(n, temp, penalty));
    }

    cout << base_cost << " " << max_cost << "\n";
    return 0;
}
