#include <vector>
#include <iostream>
#include <queue>
#include <list>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <cstdio>
using namespace std;

/*
Se tienen dos arreglos de n naturales A y B:
• A está ordenado de manera creciente
• B está ordenado de manera decreciente
• Ningún valor aparece más de una vez en el mismo arreglo
Para cada posición i consideramos la diferencia absoluta entre los
valores de ambos arreglos |A[i] − B[i]|. Se desea buscar el mínimo
valor posible de dicha cuenta.
Ejemplo:
• A = [1, 2, 3, 4] y B = [6, 4, 2, 1]
• Diferencias: |1 − 6| = 5, |2 − 4| = 2, |3 − 2| = 1, |4 − 1| = 3
• Resultado: 1
Objetivo: Implementar minDif con complejidad O(log n)
*/

// INCONPLETO
int dif_min(vector<int> a, vector<int> b, int izq, int der){
    if (izq > der){
        return valor_min;
    }

    int mid1 = (izq + (der - izq)) / 3;
    int mid2 = (der - (der - izq)) / 3;
    int dif1 = abs(a[mid1] - b[mid1]);
    int dif2 = abs(a[mid2] - b[mid2]);


    if (dif1 < dif2){
        return dif_min(a, b, mid1, der);    // me desplazo a la izquierda
    }

    else{
        return dif_min(a, b, izq, mid2);    // me desplazo a la derecha
    }
}


int main(){
    vector<int> a = {1, 2, 3, 4};
    vector<int> b = {6, 4, 2, 1};
    int res = dif_min(a, b, 0, a.size()-1);
    cout << res;
    return 0;
}