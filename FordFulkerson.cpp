#include <bits/stdc++.h>
using namespace std;

int bfs(int n, int s, int t, vector<vector<int>> &adjList, vector<vector<int>> &c, vector<int> &p) {
    for (int i = 0; i < n; i++) p[i] = -1;
    p[s] = -2;
    queue<pair<int,int>> q;
    q.push(make_pair(s, INT_MAX));

    while (!q.empty()) {
        pair<int,int> cur = q.front();
        q.pop();
        int u = cur.first;
        int flow = cur.second;

        for (int i = 0; i < adjList[u].size(); i++) {
            int v = adjList[u][i];
            if (p[v] == -1 && c[u][v] > 0) {
                p[v] = u;
                int newFlow = min(flow, c[u][v]);
                if (v == t) return newFlow;
                q.push(make_pair(v, newFlow));
            }
        }
    }
    return 0;
}

int fordFulkerson(int n, int s, int t, vector<vector<int>> &adjList, vector<vector<int>> c) {
    vector<int> p(n);
    int totalFlow = 0;
    int newFlow;

    while ((newFlow = bfs(n, s, t, adjList, c, p))) {
        totalFlow += newFlow;

        vector<int> path;
        int v = t;
        while (v != s) {
            path.push_back(v);
            int u = p[v];
            c[u][v] -= newFlow;
            c[v][u] += newFlow;
            v = u;
        }
        path.push_back(s);
        reverse(path.begin(), path.end());

        for (int i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i < path.size() - 1) cout << " -> ";
        }
        cout << endl;

        cout << "Promeneti kapaciteti:\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (c[i][j] > 0)
                    cout << i << " -> " << j << " : " << c[i][j] << endl;
            }
        }
        cout << endl;
    }

    return totalFlow;
}

int main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    vector<vector<int>> adjList(n);
    vector<vector<int>> c(n, vector<int>(n, 0));

    for (int i = 0; i < m; i++) {
        int u, v, cap;
        cin >> u >> v >> cap;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
        c[u][v] = cap;
    }

    cout << "Vkupen max flow: " << fordFulkerson(n, s, t, adjList, c) << endl;
    return 0;
}