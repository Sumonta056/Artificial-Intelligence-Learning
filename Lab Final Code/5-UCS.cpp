#include <bits/stdc++.h>
using namespace std;

class Graph
{
    map<int, vector<pair<int, int>>> l;

public:
    void addEdge(int node1, int node2, int cost)
    {
        l[node1].push_back({node2, cost});
        l[node2].push_back({node1, cost}); // For bidirectional edges (optional)
    }

    void uniform_cost_search(int source, int target)
    {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        map<int, int> distance;
        map<int, int> parent;

        for (auto nodePair : l)
        {
            int node = nodePair.first;
            distance[node] = INT_MAX;
        }

        pq.push({0, source});
        distance[source] = 0;
        parent[source] = -1;

        while (!pq.empty())
        {
            int current = pq.top().second;
            int cost = pq.top().first;
            pq.pop();

            cout << "Visiting node " << current << " with cost " << cost << endl;

            if (current == target)
            {
                vector<int> path;
                while (current != -1)
                {
                    path.push_back(current);
                    current = parent[current];
                }
                reverse(path.begin(), path.end());

                cout << "Shortest path to target: ";
                for (int node : path)
                {
                    cout << node << " ";
                }
                cout << endl;
                cout << "Total cost to reach target: " << distance[target] << endl;
                return;
            }

            for (auto edge : l[current])
            {
                int neighbour = edge.first;
                int edgeCost = edge.second;

                if (distance[current] + edgeCost < distance[neighbour])
                {
                    distance[neighbour] = distance[current] + edgeCost;
                    pq.push({distance[neighbour], neighbour});
                    parent[neighbour] = current;
                }
            }
        }

        cout << "Target is not reachable!" << endl;
    }
};

int main()
{
    Graph g;

    g.addEdge(0, 1, 5);
    g.addEdge(0, 2, 2);
    g.addEdge(1, 3, 1);
    g.addEdge(1, 4, 4);
    g.addEdge(2, 5, 1);
    g.addEdge(2, 6, 7);
    g.addEdge(5, 7, 4);
    g.addEdge(5, 8, 5);

    int source = 0, target = 3;

    g.uniform_cost_search(source, target);

    return 0;
}
