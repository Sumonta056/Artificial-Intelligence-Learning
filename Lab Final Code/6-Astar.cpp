#include <bits/stdc++.h>

using namespace std;

class Graph
{
    map<int, vector<pair<int, int>>> l;
    map<int, int> nodeHeuristics;

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
        priority_queue<pair<pair<int, int>, int>, vector<pair<pair<int, int>, int>>, greater<pair<pair<int, int>, int>>> pq;
        map<int, int> gCost; // Cost from start node to current node
        map<int, int> parent; // To store the parent node for each visited node

        for (auto nodePair : l)
        {
            int node = nodePair.first;
            gCost[node] = INT_MAX;
            parent[node] = -1;
        }

        pq.push({{0, heuristic(source, target, 0)}, source}); // Pair of gCost + heuristic
        gCost[source] = 0;

        while (!pq.empty())
        {
            int current = pq.top().second;
            pq.pop();

            cout << "Visiting node " << current <<  " with f-cost " << pq.top().first.second << endl;

            if (current == target)
            {
                cout << "Target reached!" << endl;
                cout << "Total cost to reach target: " << gCost[target] << endl;
                printPath(parent, target);
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
                    pq.push({{new_gCost, heuristic(neighbour, target, new_gCost)}, neighbour});
                    parent[neighbour] = current;
                }
            }
        }

        cout << "Target is not reachable!" << endl;
    }

    int heuristic(int node, int target, int currentCost)
    {
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

    // g.addEdge(0, 1, 75);
    // g.addEdge(0, 2, 118);
    // g.addEdge(0, 4, 140);
    // g.addEdge(2, 3, 111);
    // g.addEdge(4, 5, 99);
    // g.addEdge(4, 6, 80);
    // g.addEdge(6, 7, 97);
    // g.addEdge(7, 8, 101);
    // g.addEdge(5, 8, 211);

    // int source = 0, target = 8;

    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 5, 5);
    g.addEdge(1, 4, 12);
    g.addEdge(2, 4, 10);
    g.addEdge(2, 3, 7);
    g.addEdge(3, 4, 2);
    g.addEdge(4, 6, 5);
    g.addEdge(5, 6, 16);

     int source = 0, target = 6;

    // g.setHeuristic(0, 366);
    // g.setHeuristic(1, 374);
    // g.setHeuristic(2, 329);
    // g.setHeuristic(3, 244);
    // g.setHeuristic(4, 253);
    // g.setHeuristic(5, 178);
    // g.setHeuristic(6, 193);
    // g.setHeuristic(7, 98);
    // g.setHeuristic(8, 0);

     g.setHeuristic(0, 14);
    g.setHeuristic(1, 12);
    g.setHeuristic(2, 11);
    g.setHeuristic(3, 6);
    g.setHeuristic(4, 4);
    g.setHeuristic(5, 11);
    g.setHeuristic(6, 0);
  

    g.A_star_search(source, target);


}
