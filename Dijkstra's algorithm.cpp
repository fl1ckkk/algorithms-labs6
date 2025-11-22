#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 1e9;

struct Edge {
    int to;
    int weight;
};

void dijkstra(int startNode, int n, const vector<vector<Edge>>& adj) {
    vector<int> dist(n + 1, INF);
    vector<int> pred(n + 1, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[startNode] = 0;
    pq.push({0, startNode});

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;

        for (const auto& edge : adj[u]) {
            if (dist[u] + edge.weight < dist[edge.to]) {
                dist[edge.to] = dist[u] + edge.weight;
                pred[edge.to] = u;
                pq.push({dist[edge.to], edge.to});
            }
        }
    }

    cout << "Результати алгоритму Дейкстри (Старт: " << startNode << "):\n";
    cout << "Вершина\tВідстань\tШлях\n";
    for (int i = 1; i <= n; ++i) {
        if (i == startNode) continue;
        cout << i << "\t" << (dist[i] == INF ? "INF" : to_string(dist[i])) << "\t\t";
        
        vector<int> path;
        for (int v = i; v != -1; v = pred[v]) path.push_back(v);
        reverse(path.begin(), path.end());
        
        for (size_t j = 0; j < path.size(); ++j) {
            cout << path[j] << (j < path.size() - 1 ? " -> " : "");
        }
        cout << endl;
    }
}

int main() {
    int n = 8;
    vector<vector<Edge>> adj(n + 1);


    auto addEdge = [&](int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    };

    addEdge(1, 3, 6); addEdge(1, 4, 7); addEdge(1, 6, 8);
    addEdge(3, 6, 3); addEdge(3, 8, 7);
    addEdge(2, 4, 3); addEdge(2, 6, 2); addEdge(2, 5, 4);
    addEdge(4, 5, 9);
    addEdge(6, 8, 3); addEdge(6, 7, 9);
    addEdge(5, 7, 5);

    dijkstra(1, n, adj);

    return 0;
}