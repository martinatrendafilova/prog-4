#include <bits/stdc++.h>
using namespace std;

int bfs(int n, int s, int t, vector<vector<int>> &adj, vector<vector<int>> &cap, vector<int> &par) {
    par.assign(n, -1);
    par[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INT_MAX});

    while (!q.empty()) {
        pair<int, int> cur = q.front(); q.pop();
        int u = cur.first;
        int flow = cur.second;

        for (int i = 0; i < adj[u].size(); ++i) {
            int v = adj[u][i];
            if (par[v] == -1 && cap[u][v] > 0) {
                par[v] = u;
                int newFlow = min(flow, cap[u][v]);
                if (v == t) return newFlow;
                q.push({v, newFlow});
            }
        }
    }
    return 0;
}

int maxFlow(int n, int s, int t, vector<vector<int>> &adj, vector<vector<int>> cap) {
    vector<int> par(n);
    int flow = 0, f;

    while ((f = bfs(n, s, t, adj, cap, par))) {
        flow += f;
        int v = t;
        while (v != s) {
            int u = par[v];
            cap[u][v] -= f;
            cap[v][u] += f;
            v = u;
        }
    }
    return flow;
}

void remove(vector<vector<int>> &adj, int u, int v) {
    vector<int> temp;
    for (int i = 0; i < adj[u].size(); ++i) {
        if (adj[u][i] != v) temp.push_back(adj[u][i]);
    }
    adj[u] = temp;
}

int main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;

    vector<vector<int>> adj(n), cap(n, vector<int>(n, 0)), edges;

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back(v);
        adj[v].push_back(u);
        cap[u][v] = w;
        edges.push_back({u, v, w});
    }

    int minFlow = INT_MAX;
    pair<int, int> kriticno_rebro;

    for (int i = 0; i < edges.size(); ++i) {
        int u = edges[i][0], v = edges[i][1], w = edges[i][2];
        vector<vector<int>> tempCap = cap;
        vector<vector<int>> tempAdj = adj;

        tempCap[u][v] = 0;
        remove(tempAdj, u, v);
        remove(tempAdj, v, u);

        int f = maxFlow(n, s, t, tempAdj, tempCap);
        if (f < minFlow) {
            minFlow = f;
            kriticno_rebro = {u, v};
        }
    }

    cout << minFlow << endl;
    cout << kriticno_rebro.first << " " << kriticno_rebro.second << endl;
    return 0;
}
