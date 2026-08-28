#include <vector>
#include <iostream>
#include <queue>
#include <list>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <cstdio>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

/* ------------------------------------------------------------------------------
   C. Cartas

   Hay n jugadores jugando a las cartas. El jugador j tiene un número favorito f_j.
   Hay k cartas en la mesa. La carta i contiene un entero c_i.
   Los jugadores deben distribuir las cartas entre sí, dando k cartas a cada jugador. Finalmente, cada jugador cuenta cuántas cartas
   recibió con su número favorito escrito en ellas. Un jugador j que recibió t cartas con su número favorito f_j, tiene una alegría de h_j = t.
   h_0 = 0.

   Indica la máxima suma posible de las alegrías de los jugadores si se distribuyen las cartas de forma óptima. Notar que los enteros h_j son
   los mismos para todos los jugadores.

   Input
   La primera línea contiene 2 enteros n y k (1 ≤ n ≤ 500, 1 ≤ k ≤ 10). El número de jugadores y la cantidad de cartas que cada jugador va a recibir.
   La segunda línea contiene los n enteros c_j (1 ≤ c_j ≤ 10^9)
   La tercera línea contiene los n enteros f_j (1 ≤ f_j ≤ 10^9)
   La cuarta línea contiene los k enteros h_1, ..., h_k (1 ≤ h_i ≤ 10^9). Se garantiza que h_{t-1} < h_t para 2 ≤ t ≤ k.

   Pista: Piensen el caso donde todos los jugadores tienen el mismo número favorito.

   Output
   Imprime un único entero, la máxima alegría total posible.
   ------------------------------------------------------------------------------ */

vector<int> merge (vector<int>& izq, vector<int>& der){
    vector<int> mergeados;
    int i, j = 0;

    while (i < izq.size() && j < der.size()){
        if (izq[i] < der[j]){
            mergeados.push_back(izq[i]);
            i++;
        }
        else {
            mergeados.push_back(der[j]);
            j++; 
        }
        
    }
    for (int k = i; k < izq.size(); k++){
        mergeados.push_back(izq[k]);
    }
    for (int l = j; l < der.size(); l++){
        mergeados.push_back(der[l]);
    }
    return mergeados;
}


vector<int> merge_sort(vector<int>& arr){
    if (arr.size() <= 1){
        return arr;
    }
    int medio = arr.size() / 2;                   // Divide
    vector<int>mitad_izq;
    vector<int>mitad_der; 
    for (int k = 0; k < medio; k++){
        mitad_izq.push_back(arr[k]);
    }
    for (int k = medio; k < arr.size(); k++){
        mitad_der.push_back(arr[k]);
    }
    mitad_izq = merge_sort(mitad_izq);            // Conquer
    mitad_der = merge_sort(mitad_der);            // Conquer

    return merge(mitad_izq, mitad_der);           // Combine
}  


int cartas(vector<int>& c, vector<int>& f, vector<int>& h, int i, int j, int r){
    if (j == f.size() || i == c.size()){
        return 0;
    }

    int sumar_carta = 0;
    int siguiente_jugador = 0;
    int pasar_carta = 0;

    if (f[j] == c[i] && r < h.size()){
        if (r == 0){
            sumar_carta =  h[r] + cartas(c, f, h, i+1, j, r+1);
        }
        else{
            sumar_carta = h[r] - h[r-1] + cartas(c, f, h, i+1, j, r+1);
        }
        
    }

    pasar_carta = cartas(c, f, h, i+1, j, r);
    siguiente_jugador = cartas(c, f, h, i, j+1, 0);
    
    int res = max(sumar_carta, max(pasar_carta, siguiente_jugador));

    return res;
}

/*
int main(){
    int n, k;
    cin >> n >> k;
    vector<int> c(n * k);
    for (int i = 0; i < n * k; i++) {
        cin >> c[i];
    }
    vector<int> f(n);
    for (int i = 0; i < n; i++) {
        cin >> f[i];
    }
    vector<int> h(k);
    for (int i = 0; i < k; i++) {
        cin >> h[i];
    }

    cout << cartas(n, k, c, f, h, 0, 0, 0) << endl;
    return 0;
}
*/

int main() {
    // Prueba 1: Caso de ejemplo 1 del PDF
    {
        int n = 3, k = 2;
        vector<int> c = {1, 2, 3, 1, 2, 3};
        vector<int> f = {1, 2, 3};
        vector<int> h = {10, 20};
        cout << "Prueba 1 (Ejemplo 1): " << cartas(c, f, h, 0, 0, 0) << " // Esperado: 60" << endl;
    }

    {
        int n = 5, k = 5;
        vector<int> c = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        vector<int> f = {1, 2, 3, 4, 5};
        vector<int> h = {10, 20, 30, 40, 50};
        cout << "Prueba 1.bis (Ejemplo 1): " << cartas(c, f, h, 0, 0, 0) << " // Esperado: 250" << endl;
    }

    // Prueba 2: Caso de ejemplo 2 del PDF
    {
        int n = 2, k = 2;
        vector<int> c = {2, 1, 2, 1};
        vector<int> f = {1, 1};
        vector<int> h = {10, 20};
        cout << "Prueba 2 (Ejemplo 2): " << cartas(c, f, h, 0, 0, 0) << " // Esperado: 20" << endl;
    }

    // Prueba 3: Todos los números favoritos son iguales
    {
        int n = 3, k = 2;
        vector<int> c = {1, 1, 1, 1, 1, 1};
        vector<int> f = {1, 1, 1};
        vector<int> h = {5, 7};
        cout << "Prueba 3 (Todos favoritos iguales): " << cartas(c, f, h, 0, 0, 0) << " // Esperado: 21" << endl;
    }

    // Prueba 4: Sin coincidencias
    {
        int n = 2, k = 1;
        vector<int> c = {1, 2, 3, 4};
        vector<int> f = {5, 6};
        vector<int> h = {10, 20};
        cout << "Prueba 4 (Sin coincidencias): " << cartas(c, f, h, 0, 0, 0) << " // Esperado: 0" << endl;
    }

    // Prueba 5:
    {
        int n = 2, k = 2;
        vector<int> c = {1, 2, 2, 2};
        vector<int> f = {2, 2};
        vector<int> h = {10, 20};
        cout << "Prueba 5: " << cartas(c, f, h, 0, 0, 0) << " // Esperado: 30" << endl;
    }

    // Prueba 6:
    {
        int n = 2, k = 2;
        vector<int> c = {1, 1, 2, 2};
        vector<int> f = {1, 2};
        vector<int> h = {10, 20};
        cout << "Prueba 6: " << cartas(c, f, h, 0, 0, 0) << " // Esperado: 40" << endl;
    }
}





