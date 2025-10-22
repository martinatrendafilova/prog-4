#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

int n, s, t;
vector<vector<int>> adj;
vector<vector<int>> cap;
vector<vector<int>> flow;
vector<int> level;
vector<int> ptr;

void addEdge(int u, int v, int c) {
    adj[u].push_back(v);
    adj[v].push_back(u);
    cap[u][v] += c;
}

bool bfs() {
    level.assign(n, -1);
    queue<int> q;
    q.push(s);
    level[s] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i];
            if (level[v] == -1 && flow[u][v] < cap[u][v]) {
                level[v] = level[u] + 1;
                q.push(v);
            }
        }
    }
    return level[t] != -1;
}

int dfs(int u, int newFlow) {
    if (newFlow == 0) return 0;
    if (u == t) return newFlow;

    for (int& i = ptr[u]; i < adj[u].size(); i++) {
        int v = adj[u][i];
        if (level[v] != level[u] + 1 || flow[u][v] >= cap[u][v]) continue;

        int tr = dfs(v, min(newFlow, cap[u][v] - flow[u][v]));
        if (tr == 0) continue;

        flow[u][v] += tr;
        flow[v][u] -= tr;
        return tr;
    }
    return 0;
}

int dinic() {
    int totalFlow = 0;
    while (bfs()) {
        ptr.assign(n, 0);
        while (int newFlow = dfs(s, INT_MAX)) {
            totalFlow += newFlow;
        }
    }
    return totalFlow;
}

int main() {
    int m;
    cin >> n >> m >> s >> t;

    adj.resize(n);
    cap.assign(n, vector<int>(n, 0));
    flow.assign(n, vector<int>(n, 0));
    level.resize(n);
    ptr.resize(n);

    for (int i = 0; i < m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        addEdge(u, v, c);
    }

    cout << dinic() << endl;
    return 0;
}
