//        ** Sumonta Saha Mridul **                                    SWE - SUST
/*

 *        ######    ##     ##  ##     ##   #######   ##    ##   ########      ###
 !       ##    ##   ##     ##  ###   ###  ##     ##  ###   ##      ##        ## ##
 ?       ##         ##     ##  #### ####  ##     ##  ####  ##      ##       ##   ##
 *        ######    ##     ##  ## ### ##  ##     ##  ## ## ##      ##      ##     ##
 !             ##   ##     ##  ##     ##  ##     ##  ##  ####      ##      #########
 ?       ##    ##   ##     ##  ##     ##  ##     ##  ##   ###      ##      ##     ##
 *        ######     #######   ##     ##   #######   ##    ##      ##      ##     ##

*/
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
    // * change type if needed
    map<int , list<int>> l;

    public:
    void addEdge(int node1 , int node2)
    {
        // * undirected graph
        l[node1].push_back(node2);
        l[node2].push_back(node1);
    }

    void bfs(int source)
    {
        map<int,bool>visited ;  // * map <node , state > visited
                               // * if state = 0 ; node not visited - either visited
                               // * initial all state = 0
        queue <int > q ;

        // * start from source node
        q.push(source) ;              // * pushing source node queue  
        visited[source] = true;       // * marking the source node visited

        // * traversal graph from source 
        while( !q.empty())
        {
            int currNode = q.front();  // * set current node
            q.pop();                    // * delete the node from queue

            cout << currNode << sp ;

            for(int neighbour : l[currNode])    // * find the neighbours of current node
            {
                if(visited[neighbour] == false) // * check the neighbour is already visited or not :if visited nothing to do
                {
                    q.push(neighbour);           // * if not visited push to queue
                    visited[neighbour] = true ;  // * mark the node visited
                }
            }
            // * traverse like this untill the node visited
        }

    }
};
    

int main()
{
    fast;

    ll node , edge ;
    cin >> node >> edge ;
   
    Graph g;
    
    // * take graph edges
    for(ll i = 0 ; i < edge ;i++)
    {
        ll x , y ; // * x = node1 , y = node2
        cin >> x >> y ;

        g.addEdge(x,y);
    }

    // * start BFS(start node)
    g.bfs(0);    
    
}
/*
6 6
0 1
0 3
1 2
2 3
3 4
4 5



5 4
0 1
0 2
1 3
1 4


0 1 2 3 4 
*/

