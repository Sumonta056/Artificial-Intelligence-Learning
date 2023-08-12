#include <bits/stdc++.h>
using namespace std;

class Graph
{
    map<int, vector<int>> l;

public:
    void addEdge(int node1, int node2)
    {
        l[node1].push_back(node2);
    }

    bool dfs_limit(int source, int target, int depth, vector<int> &path, int &iterations)
    {
        iterations++;

        path.push_back(source);

        if (source == target)
            return true;

        if (depth <= 0)
        {
            path.pop_back(); // Backtrack if the depth limit is reached
            return false;
        }

        for (auto neighbour : l[source])
        {
            cout << "Visiting node " << neighbour << " at depth " << depth - 1 << endl;
            if (dfs_limit(neighbour, target, depth - 1, path, iterations))
                return true;
        }

        path.pop_back(); // Backtrack if no path to the target is found
        return false;
    }

    bool iterative_deepening_search(int source, int target, int maxDepth, vector<int> &path, int &iterations)
    {
        for (int depth = 0; depth <= maxDepth; depth++)
        {
            path.clear(); // Clear the path at the beginning of each depth limit iteration
            iterations = 0;

            cout << "Depth Limit: " << depth << endl;
            cout << "Visiting node " << source << " at depth " << depth << endl;
            if (dfs_limit(source, target, depth, path, iterations))
            {
                cout << "Target found within depth " << depth << " in " << iterations << " iterations!" << endl;
                cout << "Path to target:";
                for (int node : path)
                {
                    cout << " " << node;
                }
                cout << endl;
                return true;
            }
            cout << "Target not found within depth " << depth << " in " << iterations << " iterations." << endl;
        }

        return false;
    }
};

int main()
{
    Graph g;

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    g.addEdge(3, 4); // Adding directed edge

    int source = 0, target = 4, maxDepth = 3;
    vector<int> path;
    int iterations;

    g.iterative_deepening_search(source, target, maxDepth, path, iterations);

    return 0;
}


/*
Depth Limit: 0
Visiting node 0 at depth 0
Target not found within depth 0 in 1 iterations.
Depth Limit: 1
Visiting node 0 at depth 1
Visiting node 1 at depth 0
Visiting node 2 at depth 0
Target not found within depth 1 in 3 iterations.
Depth Limit: 2
Visiting node 0 at depth 2
Visiting node 1 at depth 1
Visiting node 3 at depth 0
Visiting node 4 at depth 0
Target found within depth 2 in 4 iterations!
Path to target: 0 1 4
*/