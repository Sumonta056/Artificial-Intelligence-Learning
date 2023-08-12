#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define sp " "
#define enter cout << endl;
#define fast                          \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)

class Graph
{
    map<int, list<int>> l;
    vector<int> traverse;

public:
    void addEdge(int node1, int node2)
    {
        l[node1].push_back(node2);
        l[node2].push_back(node1);
    }

    void dfs_traverse_depth_limited(int currNode, map<int, bool> &visited, int depth, int limit)
    {
        traverse.push_back(currNode);
        visited[currNode] = true;

        if (depth >= limit)
            return;

        for (auto neighbour : l[currNode])
        {
            if (!visited[neighbour])
            {
                dfs_traverse_depth_limited(neighbour, visited, depth + 1, limit);
            }
        }
    }

    void depth_limited_search(int source, int limit)
    {
        map<int, bool> visited;

        for (auto it : l)
        {
            int node = it.first;
            visited[node] = false;
        }

        dfs_traverse_depth_limited(source, visited, 0, limit);

        for (auto node : traverse)
        {
            cout << node << sp;
        }
        enter;
    }
};

int main()
{
    fast;

    ll node, edge;
    cin >> node >> edge;

    Graph g;

    for (ll i = 0; i < edge; i++)
    {
        ll x, y;
        cin >> x >> y;

        g.addEdge(x, y);
    }

    int limit;
    cin >> limit; // Taking limit as input

    g.depth_limited_search(0, limit);

    return 0;
}

/*
5 4
0 1
0 2
1 3
1 4
1


0 1 2


5 4
0 1
0 2
1 3
1 4


0 1 3 4 2
*/