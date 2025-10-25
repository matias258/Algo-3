#include <list>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <cstdio>
#include <algorithm>
#include <bits/stdc++.h>
#include <utility>
#include <math.h>

#include <iostream>
#include <vector>
#include <tuple>
#include <stack>
#include <queue>

using namespace std;

int viaje(int n, int m, vector<int> a, vector<int> b, vector<int> c, vector<int> k, vector<vector<int>> t){
    // Casos Base:
    if (n <= 1){
        return 0;
    }
    if (m == 0){
        return -1;
    }

    // Lista de adyacencia: cada elemento es un par <nodo vecino, tiempo para teletransportarse>
    vector<vector<pair<int,int>>> adj(n);
    for (int i = 0; i < m; i++) {

        int u = a[i] - 1;
        int v = b[i] - 1;
        int w = c[i];

        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    
    //Inicializamos Dijkstra
   
    //Inicializo las distancias desde planeta 0 hasta el resto con valores maximos
    vector<int> pi(n, INT_MAX / 2);
    pi[0] = 0; // punto de partida

    // Marcamos los planetas como no visitados
    vector<bool> visitado(n, false);

    while (true){
        // Elijo el planeta actual con la menor distancia
        int planeta_actual = -1;
        int menor_dist = INT_MAX / 2;
        for (int p = 0; p < n; p++) {
            if (!visitado[p] && pi[p] < menor_dist) {
                menor_dist = pi[p];
                planeta_actual = p;
            }
        }

        // Si no hay planeta alcanzable, corto, voy a tener que devolver -1
        if (planeta_actual == -1 || menor_dist == INT_MAX / 2) break;


        // Visito el planeta
        visitado[planeta_actual] = true;

        // Me ahorro de iterar hasta el final siempre si llego antes a n
        if (planeta_actual == n-1){
            break;  
        }
        
        for (auto [destino, tiempo] : adj[planeta_actual]){
            int tiempo_temp = pi[planeta_actual];

            // Si tiempo_temp está en t[origen], como t[origen] viene ordenada, busco con binary search
            while (binary_search(t[planeta_actual].begin(), t[planeta_actual].end(), tiempo_temp)) {
                tiempo_temp++;
            }
                
            int peso = tiempo_temp + tiempo;

            if (peso < pi[destino]) {
                pi[destino] = peso;
            }
        }
    }

    if (pi[n-1] >= INT_MAX/4){
        // Significa que hicimos break antes de terminar el while, entonces pi[n-1] = inf. No hay solucion.
        return -1;      
    }
    else{
        return pi[n-1];
    }

}


/*
int main(){
    int n, m;
    cin >> n >> m;

    vector<int> a(m), b(m), c(m);

    for (int i = 0; i < m; i++){
        cin >> a[i] >> b[i] >> c[i];
    }

    vector<int> k(n);   // k[i] es el número de viajeros para el Planeta i
    vector<vector<int>> t(n);   // t[i] son los tiempos para el Planeta i

    // k[i] representa un viajero que llega al planeta i
    // Por cada viajero obtenemos un tiempo de llegada tj que depende de k[i]
    // Entonces si k[0] = 3 --> t[0] debe almacenar 3 enteros (un tiempo de llegada para cada viajero)
    
    // Ejemplo: k[0] = 3; t[0] = {1, 2, 4}; Significa:
    // Viajero 0 llega a planeta 0 en tiempo 1
    // Viajero 1 llega a planeta 0 en tiempo 2
    // Viajero 2 llega a planeta 0 en tiempo 4 

    for (int i = 0; i < n; i++){
        cin >> k[i];
        t[i].resize(k[i]);
        for (int j = 0; j < k[i]; j++) {
            cin >> t[i][j]; 
        }
    }

    int res = viaje(n, m, a, b, c, k, t);
    cout << res << endl;

    return 0;
}
*/

int main() {
    // Primer test case (hardcoded)
    cout << "Test Case 1:\n";
    int n1 = 3, m1 = 1;
    vector<int> a1 = {1};
    vector<int> b1 = {2};
    vector<int> c1 = {3};
    vector<int> k1 = {0, 3, 0}; // 0 viajeros en 1, 3 en 2, 0 en 3
    vector<vector<int>> t1 = {{}, {1, 2, 3}, {}}; // 3 tiempos para planeta 2
    int result1 = viaje(n1, m1, a1, b1, c1, k1, t1);
    cout << "Resultado: " << result1 << ", Esperado: -1\n\n";

    // Segundo test case (hardcoded)
    cout << "Test Case 2:\n";
    int n2 = 4, m2 = 6;
    vector<int> a2 = {1, 1, 1, 2, 2, 3};
    vector<int> b2 = {2, 3, 4, 3, 4, 4};
    vector<int> c2 = {2, 3, 9, 5, 6, 3};
    vector<int> k2 = {1, 2, 0, 0}; // 1 viajero en 1, 2 en 2, 0 en 3 y 4
    vector<vector<int>> t2 = {{1}, {2, 3}, {}, {}}; // 1 tiempo para 1, 2 tiempos para 2
    int result2 = viaje(n2, m2, a2, b2, c2, k2, t2);
    cout << "Resultado: " << result2 << ", Esperado: 6\n\n";

    // Tercer test case (hardcoded)
    cout << "Test Case 3:\n";
    int n3 = 4, m3 = 6;
    vector<int> a3 = {1, 1, 1, 2, 2, 3};
    vector<int> b3 = {2, 3, 4, 3, 4, 4};
    vector<int> c3 = {2, 3, 9, 5, 6, 3};
    vector<int> k3 = {0, 1, 2, 0}; // 0 en 1, 1 en 2, 2 en 3, 0 en 4
    vector<vector<int>> t3 = {{}, {1}, {3,4}, {}}; // 1 tiempo para 2, 2 tiempos para 3
    int result3 = viaje(n3, m3, a3, b3, c3, k3, t3);
    cout << "Resultado: " << result3 << ", Esperado: 8\n\n";

    // Caso 4: Grafo desconectado con viajeros
    cout << "Test Case 4:\n";
    int n4 = 4, m4 = 2;
    vector<int> a4 = {2, 3};
    vector<int> b4 = {3, 4};
    vector<int> c4 = {5, 7};
    vector<int> k4 = {0, 0, 1, 1}; // 0 en 1, 0 en 2, 1 en 3, 1 en 4
    vector<vector<int>> t4 = {{}, {}, {1}, {2}}; // 1 tiempo para 3, 1 para 4
    int result4 = viaje(n4, m4, a4, b4, c4, k4, t4);
    cout << "Resultado: " << result4 << ", Esperado: -1\n\n";

    // Caso 5: Ciclo con múltiples viajeros
    cout << "Test Case 5:\n";
    int n5 = 3, m5 = 3;
    vector<int> a5 = {1, 2, 3};
    vector<int> b5 = {2, 3, 1};
    vector<int> c5 = {2, 3, 4};
    vector<int> k5 = {0, 2, 2}; // 0 en 1, 2 en 2, 2 en 3
    vector<vector<int>> t5 = {{}, {1, 2}, {3, 4}}; // 2 tiempos para 2, 2 para 3
    int result5 = viaje(n5, m5, a5, b5, c5, k5, t5);
    cout << "Resultado: " << result5 << ", Esperado: 4\n\n";

    // Caso 6: Máximo número de planetas y aristas
    cout << "Test Case 6:\n";
    int n6 = 10, m6 = 45;
    vector<int> a6 = {1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7, 8, 8, 9};
    vector<int> b6 = {2, 3, 4, 5, 6, 7, 8, 9, 10, 3, 4, 5, 6, 7, 8, 9, 10, 4, 5, 6, 7, 8, 9, 10, 5, 6, 7, 8, 9, 10, 6, 7, 8, 9, 10, 7, 8, 9, 10, 8, 9, 10, 9, 10, 10};
    vector<int> c6 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 1, 2, 3, 4, 1, 2, 3, 1, 2, 1};
    vector<int> k6 = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}; // 1 viajero por planeta
    vector<vector<int>> t6 = {{1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}, {10}}; // 1 tiempo por planeta
    int result6 = viaje(n6, m6, a6, b6, c6, k6, t6);
    cout << "Resultado: " << result6 << ", Esperado: 9\n\n";

    // Caso 7: Tiempos de llegada conflictivos
    cout << "Test Case 7:\n";
    int n7 = 5, m7 = 4;
    vector<int> a7 = {1, 2, 3, 4};
    vector<int> b7 = {2, 3, 4, 5};
    vector<int> c7 = {2, 2, 2, 2};
    vector<int> k7 = {0, 2, 2, 2, 2}; // 0 en 1, 2 en 2, 2 en 3, 2 en 4, 2 en 5
    vector<vector<int>> t7 = {{}, {1, 2}, {3, 4}, {5, 6}, {7, 8}}; // 2 tiempos por planeta 2 a 5
    int result7 = viaje(n7, m7, a7, b7, c7, k7, t7);
    cout << "Resultado: " << result7 << ", Esperado: 9\n\n";

    // Caso 8: Iniciamos ya esperando
    cout << "Test Case 8:\n";
    int n8 = 5, m8 = 4;
    vector<int> a8 = {1, 2, 3, 4};
    vector<int> b8 = {2, 3, 4, 5};
    vector<int> c8 = {2, 2, 2, 2};
    vector<int> k8 = {2, 0, 2, 2, 2}; 
    vector<vector<int>> t8 = {{0,1}, {}, {3, 4}, {5, 6}, {7, 8}};
    int result8 = viaje(n8, m8, a8, b8, c8, k8, t8);
    cout << "Resultado: " << result8 << ", Esperado: 9\n\n";
}







