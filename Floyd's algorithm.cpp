#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

const int INF = 1e9;

void floydWarshall(int n, vector<vector<int>>& dist) {
    // Основний цикл алгоритму Флойда: k - проміжна вершина
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
}

int main() {
    int n = 8;
    vector<vector<int>> dist(n + 1, vector<int>(n + 1, INF));

    // Ініціалізація діагоналі
    for (int i = 1; i <= n; ++i) dist[i][i] = 0;

    // Ініціалізація ребер
    auto addEdge = [&](int u, int v, int w) {
        dist[u][v] = w;
        dist[v][u] = w;
    };

    addEdge(1, 3, 6); addEdge(1, 4, 7); addEdge(1, 6, 8);
    addEdge(3, 6, 3); addEdge(3, 8, 7);
    addEdge(2, 4, 3); addEdge(2, 6, 2); addEdge(2, 5, 4);
    addEdge(4, 5, 9);
    addEdge(6, 8, 3); addEdge(6, 7, 9);
    addEdge(5, 7, 5);

    floydWarshall(n, dist);

    cout << "Матриця найкоротших відстаней (Алгоритм Флойда):\n";
    cout << "   ";
    for(int i=1; i<=n; ++i) cout << setw(4) << i;
    cout << "\n----------------------------------\n";

    for (int i = 1; i <= n; ++i) {
        cout << i << " |";
        for (int j = 1; j <= n; ++j) {
            if (dist[i][j] == INF) cout << setw(4) << "INF";
            else cout << setw(4) << dist[i][j];
        }
        cout << endl;
    }

    return 0;
}