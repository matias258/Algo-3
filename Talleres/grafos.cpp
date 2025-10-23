#include <iostream>
#include <vector>
#include <tuple>
#include <stack>
#include <queue>

using namespace std;

void prim(int raiz, vector<vector<pair<int,int>>> G) {
    int n = G.size();
    vector<bool> visitados(n, false);
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;
    vector<tuple<int, int, int>> arbol;

    visitados[raiz] = true;
    for (pair<int,int> arista: G[raiz]) {
        int v = arista.first;
        int costo = arista.second;
        pq.push({costo, raiz, v});
    }


    while (!pq.empty() and arbol.size() <= n) {
        tuple<int, int, int> arista = pq.top();
        int peso = get<0>(arista);
        int u = get<1>(arista);
        int v = get<2>(arista);
        pq.pop();


        if (visitados[v]) {
            continue;
        } else {
            arbol.push_back({u, v, peso});
            visitados[v] = true;
        }

        for (pair<int,int> arista: G[v]) {
            int w = arista.first;
            int costo2 = arista.second;

            if (!visitados[w]) {
                pq.push({costo2, v, w});
            }
        }
    }

    cout << "AGM Prim: ";
    int suma = 0;
    for (int i=0; i < arbol.size(); i++) {
        int coste = get<0>(arbol[i]);
        int u = get<1>(arbol[i]);
        int v = get<2>(arbol[i]);
        cout << "{" << coste << "," << u << "," << v << "}" << " ";
        suma = suma + coste;
    }
    cout << "Coste: " << suma;
    
}

void bfs(int raiz, vector<vector<int>>& G) {
    int n = G.size();
    vector<bool> visitados(n, false);
    vector<int> distancias(n, -1);
    vector<int> recorrido;
    queue<int> Q;


    visitados[raiz] = true;
    distancias[raiz] = 0;
    Q.push(raiz);


    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        recorrido.push_back(u);

        for (int v : G[u]) {
            if (!visitados[v]) {
                visitados[v] = true;
                distancias[v] = distancias[u] + 1;
                Q.push(v);
            }
        }
    }

    cout << "Recorrido BFS: ";

    for (int i=0; i < recorrido.size(); i++) {
        cout << recorrido[i] << " ";
    }

    cout << "\n" << "Distancias BFS: ";

    for (int j=1; j < distancias.size(); j++) {
        cout << distancias[j] << " ";
    }

    cout << endl;
}





void dfs(int raiz, vector<vector<int>>& G) {
    int n = G.size();
    vector<bool> visitados(n, false);
    vector<int> recorrido;
    stack<int> P;


    visitados[raiz] = true;
    P.push(raiz);


    while (!P.empty()) {
        int u = P.top();
        P.pop();
        recorrido.push_back(u);

        for (int v : G[u]) {
            if (!visitados[v]) {
                visitados[v] = true;
                P.push(v);
            }
        }
    }
    
    cout << "Recorrido DFS Iterativo: ";

    for (int i=0; i < recorrido.size(); i++) {
        cout << recorrido[i] << " ";
    }

    cout << endl;
}





void dfs_rec_aux(int nodo, vector<bool>& visitados, vector<int>& recorrido, int& tiempo, vector<pair<int,int>>& tiempos, vector<vector<int>>& G) {

    tiempo = tiempo + 1;
    tiempos[nodo].first = tiempo;
    visitados[nodo] = true;
    recorrido.push_back(nodo);

        for (int v : G[nodo]) {
            if (!visitados[v]) {
                dfs_rec_aux(v, visitados, recorrido, tiempo, tiempos, G);
            }
        }
        tiempo = tiempo+1;
        tiempos[nodo].second = tiempo;



}

// void dfs_rec(int raiz, vector<vector<int>>& G) {
//     int n = G.size();
//     vector<bool> visitados(n, false);
//     vector<int> recorrido;
//     int tiempo = 0;
//     vector<pair<int,int>> tiempos(n);
    
//     dfs_rec_aux(raiz, visitados, recorrido, tiempo, tiempos, G);

//     cout << "Recorrido DFS Recursivo: ";

//     for (int i=0; i < recorrido.size(); i++) {
//         cout << recorrido[i] << " ";
//     }

//     cout << "\n" << "Tiempos DFS Recursivo: ";

//     for (int j=1; j < tiempos.size(); j++) {
//         cout << "(" << tiempos[j].first << ", " << tiempos[j].second << ")" << " ";
//     }

//     cout << endl;
// }

void dfs_rec_conex(int raiz, vector<vector<int>>& G) {
    int n = G.size();
    vector<bool> visitados(n, false);
    vector<int> recorrido;
    int tiempo = 0;
    vector<pair<int,int>> tiempos(n);
    
    dfs_rec_aux(raiz, visitados, recorrido, tiempo, tiempos, G);

    int componentes_conexas = 1;
    bool conexo = true;

    for (int i=1; i < n; i++) {
        if (!visitados[i]) {
            conexo = false;
            componentes_conexas ++;
            dfs_rec_aux(i, visitados, recorrido, tiempo, tiempos, G);
        }
    }

    if (conexo) {
        cout << "¿Es Conexo? Si";
    } else {
        cout << "¿Es Conexo? No ¿Componentes Conexas? " << componentes_conexas;
    }

    cout << "\n" << "Recorrido DFS Recursivo: ";

    for (int i=0; i < recorrido.size(); i++) {
        cout << recorrido[i] << " ";
    }

    cout << "\n" << "Tiempos DFS Recursivo: ";

    for (int j=1; j < tiempos.size(); j++) {
        cout << "(" << tiempos[j].first << ", " << tiempos[j].second << ")" << " ";
    }

    cout << endl;
}








int main() {

    int n = 9;

    vector<vector<int>> lista_ady(n+1);
    vector<vector<int>> matriz_ady(n+1, vector<int>(n+1,0));
    vector<vector<pair<int,int>>> lista_ady_ponderada(n+1);

    vector<pair<int,int>> E = { {1,2}, {1,3}, {2,4}, {2,5}, {4,7}, {3,6}, {5,6}, {8,9} };
    vector<tuple<int,int,int>> E_costos = { {1,2,3}, {1,3,5}, {2,4,2}, {2,5,1}, {4,7,4}, {3,6,5}, {5,6,2}, {8,9,2} };

    for (pair<int,int> arista : E) {
        int u = arista.first;
        int v = arista.second;
        matriz_ady[u][v] = 1;
        matriz_ady[v][u] = 1;
    }

    cout << "Matriz de adyacencia:\n";
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << matriz_ady[i][j] << " ";
        }
        cout << endl;
    }

    for (pair<int,int> arista : E) {
        int u = arista.first;
        int v = arista.second;
        lista_ady[u].push_back(v);
        lista_ady[v].push_back(u);
    }

    cout << "Lista de adyacencia:\n";
    for (int i = 1; i <= n; i++) {
        cout << i << ": ";
        for (int vecino : lista_ady[i]) {
            cout << vecino << " ";
        }
        cout << endl;
    }

    for (tuple<int,int,int> arista : E_costos) {
        int u = get<0>(arista);
        int v = get<1>(arista);
        int c = get<2>(arista);
        pair<int,int> u_a_v = {v, c};
        pair<int,int> v_a_u = {u, c};
        lista_ady_ponderada[u].push_back(u_a_v);
        lista_ady_ponderada[v].push_back(v_a_u);
    }

    cout << "Lista de adyacencia ponderada:\n";
    for (int i = 1; i <= n; i++) {
        cout << i << ": ";
        for (pair<int,int> vecino : lista_ady_ponderada[i]) {
            cout << "{" << get<0>(vecino) << "," << get<1>(vecino) << "}" << " ";
        }
        cout << endl;
    }

    bfs(1,lista_ady);
    dfs(1,lista_ady);
    //dfs_rec(1, lista_ady);
    dfs_rec_conex(1, lista_ady);
    prim(1, lista_ady_ponderada);

    return 0;
}