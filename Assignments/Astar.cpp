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
#define ull unsigned long long

#define f first
#define se second
#define lb lower_bound
#define ub upper_bound
#define pb push_back

#define pii pair<int, int>
#define pll pair<long, long>
#define mp(a, b) make_pair(a, b)
#define vi vector<int>
#define vll vector<ll>
#define vii vector<pii>
#define sll set<ll>
#define qll queue<ll>
#define stll stack<ll>
#define Mi map<int, int>
#define mii map<pii, int>
#define alls(a) (a).begin(), (a).end()
#define sz(x) (int)x.size()

#define Size(s) s.length()
#define all(v) (v.begin, v.end)
#define rev(v) reverse(v.begin, v.end)
#define srt(v) sort(v.begin, v.end)

#define F(i, s, e) for (ll i = s; i < e; ++i)
#define rep(i, a, b) for (int i = a; i < b; i++)
#define rem(i, a, b) for (int i = a; i > b; i--)
#define pv(v)             \
    for (ll i : v)        \
        cout << i << " "; \
    cout << endl;

#define max3(a, b, c) max(max((a), (b)), (c))
#define min3(a, b, c) min(min((a), (b)), (c))

#define cin(n) cin >> n
#define cin2(a, b) cin >> a >> b;
#define cin3(a, b, c) cin >> a >> b >> c;
#define printE(str) cout << str << endl
#define print(str) cout << str << endl
#define endl '\n'
#define Y cout << "YES\n"
#define No cout << "NO\n"
#define ye cout << "Yes\n"
#define no cout << "No\n"

#define sp " "
#define enter cout << endl;

#define fast                          \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)

#define foi(i, a, b) for (int i = a; i < b; i++)
#define foI(i, a, b) for (int i = a; i <= b; i++)
#define fol(i, a, b) for (ll i = a; i < b; i++)
#define foL(i, a, b) for (ll i = a; i <= b; i++)

//* char a = 'A';   int num = (int) a;
//* char a = '2';   int num = a-48;
//* char a = '8';   int num = a - '0' ;  (  s[i]-'0' == 8 )

const int MAXN = 100005;
const int INF = 1000000007;
int n, m;
vector<pair<int, int>> adj[MAXN];
int dist[MAXN];
int heuristic[MAXN];
int s, e;

void dijkstra(int start)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // min-heap
    for (int i = 1; i <= n; i++)
        dist[i] = INF;
    dist[start] = 0;
    pq.push({0, start});
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        for (auto v : adj[u])
        {
            int new_dist = dist[u] + v.second;
            if (new_dist < dist[v.first])
            {
                dist[v.first] = new_dist;
                pq.push({new_dist, v.first});
            }
        }
    }
}
void a_star(int start, int goal)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    map<int, int> parent;
    for (int i = 1; i <= n; i++)
    {
        dist[i] = INF;
        heuristic[i] = INF;
    }
    dist[start] = 0;
    pq.push({0, start});
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        if (u == goal)
            break;
        for (auto v : adj[u])
        {
            int new_dist = dist[u] + v.second;
            if (new_dist < dist[v.first])
            {
                dist[v.first] = new_dist;
                heuristic[v.first] = sqrt(pow(v.first - e, 2) + pow(v.second - e, 2)); // Euclidean distance as heuristic
                parent[v.first] = u;
                pq.push({dist[v.first] + heuristic[v.first], v.first});
            }
        }
    }

    vector<int> path;
    int u = goal;
    while (u != start)
    {
        path.push_back(u);
        u = parent[u];
    }
    path.push_back(start);
    reverse(path.begin(), path.end());
    cout << "Shortest path: ";
    for (auto u : path)
        cout << u << " ";
    cout << endl;
}

int main()
{
    fast;
    cin >> n >> m;
    int u, v, w;
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    cin >> s >> e;

    dijkstra(s);
    a_star(s, e);
}
