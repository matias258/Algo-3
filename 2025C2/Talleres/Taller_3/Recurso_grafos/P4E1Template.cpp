#include <utility>
#include <vector>
#include <iostream>
#include <queue>
using namespace std;

void dfs(int u, vector<vector<int>>& l, vector<bool>& visitado) {
    visitado[u] = true;
    cout << u << " ";  // ejemplo: imprimir el vértice visitado

    for (int v : l[u]) {
        if (!visitado[v]) {
            dfs(v, l, visitado);
        }
    }
}

void bfs(int inicio, vector<vector<int>>& l) {
    int n = l.size();
    vector<bool> visitado(n, false);
    queue<int> q;

    q.push(inicio);
    visitado[inicio] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cout << u << " ";

        for (int v : l[u]) {
            if (!visitado[v]) {
                visitado[v] = true;
                q.push(v);
            }
        }
    }
}


#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool es_bipartito(vector<vector<int>> l) {
    int n = l.size();
    vector<int> color(n, -1); // -1 = no visitado

    for (int i = 0; i < n; i++) {
        if (color[i] != -1) continue; // ya visitado

        color[i] = 0;
        queue<int> q;
        q.push(i);

        while (!q.empty()) {
            int u = q.front(); q.pop();

            for (int v : l[u]) {
                if (color[v] == -1) {
                    color[v] = 1 - color[u]; // alternamos color
                    q.push(v);
                } else if (color[v] == color[u]) {
                    return false; // conflicto: no bipartito
                }
            }
        }
    }

    return true; // si no hubo conflictos
}

typedef pair<int, int> arista;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> l(n);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;

        l[u].push_back(v);
        l[v].push_back(u); 
    }

    if (es_bipartito(l)) {
        cout << "BIPARTITO" << endl;
    } else {
        cout << "NO BIPARTITO" << endl;
    }

    return 0;
}
