#include <bits/stdc++.h>
using namespace std;

class Graph
{
    map<int, vector<pair<int, int>>> l;
    map<int, int> nodeHeuristics; // Heuristic value for each node

public:
    void addEdge(int node1, int node2, int cost)
    {
        l[node1].push_back({node2, cost});
        l[node2].push_back({node1, cost}); // For bidirectional edges (optional)
    }

    void setHeuristic(int node, int heuristicValue)
    {
        nodeHeuristics[node] = heuristicValue;
    }

    void A_star_search(int source, int target)
    {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        map<int, int> gCost; // Cost from start node to current node
        map<int, int> fCost; // gCost + heuristic cost
        map<int, int> parent; // To store the parent node for each visited node

        for (auto nodePair : l)
        {
            int node = nodePair.first;
            gCost[node] = INT_MAX;
            fCost[node] = INT_MAX;
            parent[node] = -1;
        }

        pq.push({0, source});
        gCost[source] = 0;
        fCost[source] = heuristic(source, target, 0); // Initial cost is 0

        while (!pq.empty())
        {
            int current = pq.top().second;
            pq.pop();

            cout << "Visiting node " << current << " with heuristic value " << fCost[current] - gCost[current] << endl;

            if (current == target)
            {
                cout << "Target reached!" << endl;
                cout << "Total cost to reach target: " << gCost[target] << endl;
                printPath(parent, target); // Print the path to reach the target
                return;
            }

            for (auto edge : l[current])
            {
                int neighbour = edge.first;
                int edgeCost = edge.second;
                int new_gCost = gCost[current] + edgeCost;

                if (new_gCost < gCost[neighbour])
                {
                    gCost[neighbour] = new_gCost;
                    fCost[neighbour] = heuristic(neighbour, target, gCost[neighbour]) + new_gCost; // Updated the calculation here
                    pq.push({fCost[neighbour], neighbour});
                    parent[neighbour] = current;
                }
            }
        }

        cout << "Target is not reachable!" << endl;
    }

    int heuristic(int node, int target, int currentCost)
    {
        // Use the heuristic value specified for the node
        return nodeHeuristics[node] + currentCost;
    }

    void printPath(map<int, int> &parent, int node)
    {
        vector<int> path;
        while (node != -1)
        {
            path.push_back(node);
            node = parent[node];
        }
        reverse(path.begin(), path.end());

        cout << "Path to reach target: ";
        for (int n : path)
        {
            cout << n << " ";
        }
        cout << endl;
    }
};

int main()
{
    Graph g;

    g.addEdge(0, 1, 75);
    g.addEdge(0, 2, 118);
    g.addEdge(0, 4, 140);
    g.addEdge(4, 5, 99);
    g.addEdge(4, 6, 80);
    g.addEdge(6, 7, 97);
    g.addEdge(7, 8, 101);
    g.addEdge(5, 8, 120);

    int source = 0, target = 8;

    g.setHeuristic(0, 366); // Set heuristic value for node 0
    g.setHeuristic(1, 374);
    g.setHeuristic(2, 329);
    g.setHeuristic(3, 244);
    g.setHeuristic(4, 253);
    g.setHeuristic(5, 178);
    g.setHeuristic(6, 193);
    g.setHeuristic(7, 98);
    g.setHeuristic(8, 0);

    g.A_star_search(source, target);

    return 0;
}
