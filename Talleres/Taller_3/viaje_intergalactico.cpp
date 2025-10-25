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
        return INT_MIN / 2;
    }

    // Comenzamos con tiempo 0
    int tiempo = 0;
    
    //Inicializmos Dijkstra
    
    //Inicializo las distancias desde planeta 0 hasta el resto con valores maximos
    vector<int> pi(n, INT_MAX / 2);
    pi[0] = 0; // punto de partida

    //Inicializo los planetas sin visitar, que son los planetas 0,1,2,3,...,n-1
    vector<int> planetas_sin_visitar(n);
    for (int i = 0; i < n; i++) {
        planetas_sin_visitar[i] = i;
    }


    while (!planetas_sin_visitar.empty()){
        // Elijo el planeta actual con la menor distancia
        int planeta_actual = -1;
        int menor_dist = INT_MAX / 2;
        for (int p : planetas_sin_visitar) {
            if (pi[p] < menor_dist) { 
                menor_dist = pi[p];
                planeta_actual = p;
            }
        }

        for (int i = 0; i < a.size(); i++){
            if (a[i] == planeta_actual){
                
                // Relajo fijandome ambas direcciones (los portales permiten viajar en ambos sentidos)
                if (c[i] + pi[a[i]] < pi[b[i]]){
                    pi[b[i]] = c[i] + pi[a[i]];
                }
                else if (c[i] + pi[b[i]] < pi[a[i]]){
                    pi[a[i]] = c[i] + pi[b[i]];
                }
            }
        }
        planetas_sin_visitar.erase( 
            remove(
                planetas_sin_visitar.begin(), planetas_sin_visitar.end(), planeta_actual),
            planetas_sin_visitar.end());

        // Me ahorro de iterar hasta el final siempre si llego antes a n
        if (planeta_actual == n-1){
            break;  // acá ya encontramos la min distancia al destino
        }

    }

    return pi[n - 1];

}

/*
int main() {
    int n = 4, m = 4;
    vector<int> a = {0, 0, 1, 2};
    vector<int> b = {1, 2, 2, 3};
    vector<int> c = {1, 4, 2, 1};
    
    vector<int> k(n, 0); // sin viajeros
    vector<vector<int>> t(n);

    int resultado = viaje(n, m, a, b, c, k, t);

    if (resultado == -1)
        cout << "No hay camino disponible." << endl;
    else
        cout << "Tiempo minimo desde el planeta 0 hasta el planeta " << n-1 << ": " << resultado << endl;

    return 0;
}
*/


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

    return 0;
}
