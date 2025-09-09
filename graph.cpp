#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n=0, m=0;
    char gt;
    cin >> n >> m;
    cin >> gt;

    vector<vector<int>> adjList(n);
    vector<vector<int>> adjMatrix(n, vector<int>(n, 0));
    
    for (int i = 0; i < m; ++i)
    {
        int from, to;
        cin >> from >> to;

        adjList[from].push_back(to);
        adjMatrix[from][to] = 1;

        if (gt == 'u')
        {
            adjList[to].push_back(from);
            adjMatrix[to][from] = 1;
        }
    }

    cout<<endl;
    cout << "Adjacency List";
    cout<<endl;
    for (int i = 0; i < n; ++i)
    {
        cout << i << ": ";
        for (int j = 0; j < adjList[i].size(); ++j)
        {
            cout << adjList[i][j] << " ";
        }
        cout << endl;
    }
    cout<<endl;
    cout << "Adjacency Matrix";
    cout<<endl;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}