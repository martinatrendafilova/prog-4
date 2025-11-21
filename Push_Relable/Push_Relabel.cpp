#include <bits/stdc++.h>
using namespace std;

const int INF = 1000000000;

int n;
vector<vector<int>> capacity, flow;
vector<int> height, excess, seen;
queue<int> excess_vertices;

void push(int u, int v) {
    int d = min(excess[u], capacity[u][v] - flow[u][v]);
    if (d > 0 && height[u] == height[v] + 1) {
        flow[u][v] += d;
        flow[v][u] -= d;
        excess[u] -= d;
        excess[v] += d;
        if (excess[v] == d)
            excess_vertices.push(v);
    }
}

void relabel(int u) {
    int d = INF;
    for (int v = 0; v < n; v++)
        if (capacity[u][v] - flow[u][v] > 0)
            d = min(d, height[v]);
    if (d < INF)
        height[u] = d + 1;
}

void discharge(int u) {
    while (excess[u] > 0) {
        if (seen[u] < n) {
            int v = seen[u];
            if (capacity[u][v] - flow[u][v] > 0 && height[u] > height[v])
                push(u, v);
            else
                seen[u]++;
        } else {
            relabel(u);
            seen[u] = 0;
        }
    }
}

int max_flow(int s, int t) {
    height.assign(n, 0);
    flow.assign(n, vector<int>(n, 0));
    excess.assign(n, 0);
    seen.assign(n, 0);

    height[s] = n;
    excess[s] = INF;

    for (int i = 0; i < n; i++) {
        if (i != s && capacity[s][i] > 0) {
            int d = capacity[s][i];
            flow[s][i] = d;
            flow[i][s] = -d;
            excess[i] = d;
            excess[s] -= d;
            excess_vertices.push(i);
        }
    }

    while (!excess_vertices.empty()) {
        int u = excess_vertices.front();
        excess_vertices.pop();
        if (u != s && u != t)
            discharge(u);
    }

    int maxflow = 0;
    for (int i = 0; i < n; i++)
        maxflow += flow[i][t];
    return maxflow;
}

int main() {
    int choice;
    cin >> choice;

    if (choice == 1) {
        n = 50;
        capacity.resize(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (i != j)
                    capacity[i][j] = rand() % 398;
    } else {
        int m;
        cin >> n >> m;
        capacity.resize(n, vector<int>(n, 0));
        for (int i = 0; i < m; i++) {
            int a, b, c;
            cin >> a >> b >> c;
            capacity[a][b] = c;
        }
    }

    int s, t;
    cin >> s >> t;

    cout << max_flow(s, t);
    return 0;
}