#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<int> dijkstra(int start, vector<vector<pair<int, int>>>& graph) {
    int n = graph.size();
    vector<int> dist(n, 10000000); 
    vector<bool> visited(n, false);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;

    dist[start] = 0;
    q.push(make_pair(0, start));

    while (!q.empty()) {
        int currentDist = q.top().first;
        int currentNode = q.top().second;
        q.pop();

        if (visited[currentNode]) continue;
        visited[currentNode] = true;

        for (int i = 0; i < graph[currentNode].size(); i++) {
            int weight = graph[currentNode][i].first;
            int neighbor = graph[currentNode][i].second;

            if (dist[neighbor] > currentDist + weight) {
                dist[neighbor] = currentDist + weight;
                q.push(make_pair(dist[neighbor], neighbor));
            }
        }
    }

    return dist;
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int,int>>> graf(n);

    for(int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        graf[u].push_back({w, v});
        graf[v].push_back({w, u}); 
    }

    vector<int> rez = dijkstra(0, graf);
    for(int i = 0; i < n; i++)
    {
        cout << rez[i] << " ";
    }

    return 0;
}