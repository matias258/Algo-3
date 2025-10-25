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

#include <functional>
#include <queue>
#include <string_view>

using namespace std;

long long viaje(long long n, long long m, vector<long long> a, vector<long long> b, vector<long long> c, vector<long long> k, vector<vector<long long>> t){
    // Casos Base:
    if (n == 2 && m == 0){
        return -1;
    }

    if (m == 0){
        return -1;
    }

    // Lista de adyacencia: cada elemento es un par <nodo vecino, tiempo para teletransportarse>
    // Esto nos permite ser mas eficientes al momento de sumar el tiempo de espera con los visitantes.
    vector<vector<pair<long long,long long>>> l(n);
    for (long long i = 0; i < m; i++) {

        long long u = a[i] - 1;
        long long v = b[i] - 1;
        long long w = c[i];

        l[u].push_back({v, w});
        l[v].push_back({u, w});
    }
    
    //Inicializamos Dijkstra
   
    //Inicializo las distancias desde planeta 0 hasta el resto con valores maximos
    vector<long long> pi(n, INT_MAX / 2);
    pi[0] = 0; // punto de partida

    // Marcamos los planetas como no visitados
    vector<bool> visitado(n, false);


    // Usaremos min-heap (tiempo, planeta)
    priority_queue<
    pair<long long,long long>,                      // tipo de cada elemento -> (tiempo, planeta)
    vector<pair<long long,long long>>,              // se almacenan en un vector long long , long long
    greater<pair<long long,long long>>              // se ordenan de menor a mayor (queremos min-heap)
    > cola;
    cola.push({0, 0});                  // Punto de Partida: distancia inicial con planeta inicial 

    while (cola.empty() == false){
        // Elijo el planeta actual con la menor distancia, 
        long long planeta_actual = cola.top().second;
        long long dist_actual = cola.top().first;
        cola.pop();   // elimino los actuales pues son los que "ya visité"

        
        if (visitado[planeta_actual]) continue;
        visitado[planeta_actual] = true;

        // Me ahorro de iterar hasta el final siempre si llego antes a n
        if (planeta_actual == n-1){
            break;  
        }
        
        for (auto [destino, tiempo] : l[planeta_actual]){
            long long tiempo_temp = pi[planeta_actual];

            // Si tiempo_temp está en t[origen] entonces debo esperar otro segundo
            // como t[origen] viene ordenada, busco con binary search
            while (binary_search(t[planeta_actual].begin(), t[planeta_actual].end(), tiempo_temp)) {
                tiempo_temp++;
            }
                
            long long peso = tiempo_temp + tiempo;

            if (peso < pi[destino]) {
                pi[destino] = peso;
                cola.push({pi[destino], destino});
            }
        }
    }

    if (pi[n-1] >= INT_MAX/3){
        // Significa que hicimos break antes de terminar el while, entonces pi[n-1] = inf. No hay solucion.
        return -1;      
    }
    else{
        return pi[n-1];
    }
}


int main(){
    long long n, m;
    cin >> n >> m;

    vector<long long> a(m), b(m), c(m);

    for (long long i = 0; i < m; i++){
        cin >> a[i] >> b[i] >> c[i];
    }

    vector<long long> k(n);   // k[i] es el número de viajeros para el Planeta i
    vector<vector<long long>> t(n);   // t[i] son los tiempos para el Planeta i

    // k[i] representa un viajero que llega al planeta i
    // Por cada viajero obtenemos un tiempo de llegada tj que depende de k[i]
    // Entonces si k[0] = 3 --> t[0] debe almacenar 3 enteros (un tiempo de llegada para cada viajero)
    
    // Ejemplo: k[0] = 3; t[0] = {1, 2, 4}; Significa:
    // Viajero 0 llega a planeta 0 en tiempo 1
    // Viajero 1 llega a planeta 0 en tiempo 2
    // Viajero 2 llega a planeta 0 en tiempo 4 

    for (long long i = 0; i < n; i++){
        cin >> k[i];
        t[i].resize(k[i]);
        for (long long j = 0; j < k[i]; j++) {
            cin >> t[i][j]; 
        }
    }

    long long res = viaje(n, m, a, b, c, k, t);
    cout << res << endl;

    return 0;
}

/*
int main() {
    // Caso 9: Grafo con desconexión parcial y muchos viajeros
    cout << "Test Case 9:\n";
    long long n9 = 6, m9 = 5;
    vector<long long> a9 = {1, 2, 3, 4, 5};
    vector<long long> b9 = {2, 3, 4, 5, 6};
    vector<long long> c9 = {2, 3, 4, 5, 6};
    vector<long long> k9 = {2, 3, 2, 2, 2, 2}; // 2 en 1, 3 en 2, 2 en 3, 2 en 4, 2 en 5, 2 en 6
    vector<vector<long long>> t9 = {{1, 2}, {3, 4, 5}, {6, 7}, {8, 9}, {10, 11}, {12, 13}}; // 2 tiempos para 1, 3 para 2, 2 para cada uno de 3 a 6
    long long result9 = viaje(n9, m9, a9, b9, c9, k9, t9);
    cout << "Resultado: " << result9 << ", Esperado: 21\n\n";

    // Caso 10: Ciclo completo con conflictos de tiempo
    cout << "Test Case 10:\n";
    long long n10 = 3, m10 = 3;
    vector<long long> a10 = {1, 2, 3};
    vector<long long> b10 = {2, 3, 1};
    vector<long long> c10 = {1, 1, 1};
    vector<long long> k10 = {2, 2, 2}; // 2 en 1, 2 en 2, 2 en 3
    vector<vector<long long>> t10 = {{1, 2}, {3, 4}, {5, 6}}; // 2 tiempos por planeta
    long long result10 = viaje(n10, m10, a10, b10, c10, k10, t10);
    cout << "Resultado: " << result10 << ", Esperado: 1\n\n";

    // Caso 11: Grafo lineal con espera máxima
    cout << "Test Case 11:\n";
    long long n11 = 5, m11 = 4;
    vector<long long> a11 = {1, 2, 3, 4};
    vector<long long> b11 = {2, 3, 4, 5};
    vector<long long> c11 = {2, 2, 2, 2};
    vector<long long> k11 = {1, 1, 1, 1, 1}; // 1 en cada planeta
    vector<vector<long long>> t11 = {{0}, {3}, {6}, {9}, {12}}; // 1 tiempo por planeta
    long long result11 = viaje(n11, m11, a11, b11, c11, k11, t11);
    cout << "Resultado: " << result11 << ", Esperado: 12\n\n";

    // Caso 12: Grafo con nodo aislado y viajeros
    cout << "Test Case 12:\n";
    long long n12 = 4, m12 = 3;
    vector<long long> a12 = {1, 2, 3};
    vector<long long> b12 = {2, 3, 4};
    vector<long long> c12 = {3, 4, 5};
    vector<long long> k12 = {0, 2, 2, 0}; // 0 en 1, 2 en 2, 2 en 3, 0 en 4
    vector<vector<long long>> t12 = {{}, {1, 2}, {3, 4}, {}}; // 2 tiempos para 2, 2 para 3
    long long result12 = viaje(n12, m12, a12, b12, c12, k12, t12);
    cout << "Resultado: " << result12 << ", Esperado: 12\n\n";

    // Caso 13: Viajeros en el planeta 1 en tiempo 0
    cout << "Test Case 13:\n";
    long long n13 = 4, m13 = 3;
    vector<long long> a13 = {1, 2, 3};
    vector<long long> b13 = {2, 3, 4};
    vector<long long> c13 = {2, 2, 2};
    vector<long long> k13 = {1, 0, 0, 0}; // 1 en 1, 0 en 2, 0 en 3, 0 en 4
    vector<vector<long long>> t13 = {{0}, {}, {}, {}}; 
    long long result13 = viaje(n13, m13, a13, b13, c13, k13, t13);
    cout << "Resultado: " << result13 << ", Esperado: 7\n\n";

    // Caso 15: Sin aristas con viajeros en todos los planetas
    cout << "Test Case 15:\n";
    long long n15 = 5, m15 = 0;
    vector<long long> a15 = {};
    vector<long long> b15 = {};
    vector<long long> c15 = {};
    vector<long long> k15 = {1, 1, 1, 1, 1}; // 1 en cada planeta
    vector<vector<long long>> t15 = {{0}, {0}, {0}, {0}, {0}};
    long long result15 = viaje(n15, m15, a15, b15, c15, k15, t15);
    cout << "Resultado: " << result15 << ", Esperado: -1\n\n";

    // Caso 16: Tiempos de viajeros coincidiendo en cada paso
    cout << "Test Case 16:\n";
    long long n16 = 5, m16 = 4;
    vector<long long> a16 = {1, 2, 3, 4};
    vector<long long> b16 = {2, 3, 4, 5};
    vector<long long> c16 = {2, 2, 2, 2};
    vector<long long> k16 = {0, 1, 1, 1, 1}; 
    vector<vector<long long>> t16 = {{}, {2}, {4}, {6}, {8}}; 
    long long result16 = viaje(n16, m16, a16, b16, c16, k16, t16);
    cout << "Resultado: " << result16 << ", Esperado: 9\n\n";

    // Caso 17: Máximo número de aristas con viajeros en tiempo 0
    cout << "Test Case 17:\n";
    long long n17 = 5, m17 = 10;
    vector<long long> a17 = {1, 1, 1, 1, 2, 2, 2, 3, 3, 4};
    vector<long long> b17 = {2, 3, 4, 5, 3, 4, 5, 4, 5, 5};
    vector<long long> c17 = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    vector<long long> k17 = {1, 0, 0, 0, 0}; // 1 en 1, 0 en 2, 0 en 3, 0 en 4, 0 en 5
    vector<vector<long long>> t17 = {{0}, {}, {}, {}, {}}; 
    long long result17 = viaje(n17, m17, a17, b17, c17, k17, t17);
    cout << "Resultado: " << result17 << ", Esperado: 2\n\n";

    cout << "Test Case 18:\n";
    long long n18 = 6, m18 = 6;
    vector<long long> a18 = {1, 2, 4, 1, 3, 5};
    vector<long long> b18 = {2, 4, 6, 3, 5, 6};
    vector<long long> c18 = {10, 15, 1, 2, 11, 5};
    vector<long long> k18 = {2, 0, 4, 0, 5, 3};
    vector<vector<long long>> t18 = {{0,1}, {}, {4,5,6,7}, {}, {19,20,21, 22, 23}, {28, 29, 30}};
    long long result18 = viaje(n18, m18, a18, b18, c18, k18, t18);
    cout << "Resultado: " << result18 << ", Esperado: 28\n\n";
}
*/





