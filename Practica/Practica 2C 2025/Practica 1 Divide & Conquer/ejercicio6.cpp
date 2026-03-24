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
Ejercicio 6 (MaximoMontaña)
Un arreglo de enteros se denomina montaña si esta compuesto por una secuencia estrictamente creciente
seguida de una estrictamente decreciente. Dado un arreglo montaña de longitud n, dar un algoritmo que encuentre el maximo del arreglo en complejidad O(log n). Por ejemplo, para un arreglo [−1, 3, 8, 22, 30, 22, 8, 4, 2, 1], el maximo esta en la posicion 4 y vale 30.
*/


int Montaña(vector<int> arr, int i, int j){
    if ( i >= j){
        return arr[i];
    }
    int medio = (i+j) / 2;
    if (arr[medio] > arr[medio + 1] && arr[medio] > arr[medio - 1]){
        return arr[medio];
    }
    else if (arr[medio] < arr[medio + 1]){
        return Montaña(arr, medio + 1, j);
    }
    else {
        return Montaña(arr, i, medio - 1);
    }
}

int maxMontaña(vector<int> arr){
    return Montaña(arr, 0, arr.size()-1);
}

/*
Complejidad:
a = 1, hacemos 1 recursion por iteracion
c = 2, partimos el array por la mitad, luego nos queda n/2, con n = array.size() -> c = 2
f(n) = O(1) = Tita(1) = Omega(1), pues No hay Merge, y la complejidad fuera de la recursion es constante.

Caso 2: f(n) = Tita(1) --> Tita(n^logc(a)) = Tita(n^log2(1)) = Tita(1)
Luego --> T(n) = Tita(n^logc(a) * log(n)) = Tita(log(n))
*/



int main(){
    // Caso 1: Montaña clásica
    vector<int> arr1 = {-1, 3, 8, 22, 30, 22, 8, 4, 2, 1};
    cout << "Test 1: " << maxMontaña(arr1)
         << " (expected 30)" << endl;

    // Caso 2: Montaña más corta
    vector<int> arr2 = {8, 22, 30, 22, 8};
    cout << "Test 2: " << maxMontaña(arr2)
         << " (expected 30)" << endl;

    // Caso 3: Pico al inicio
    vector<int> arr3 = {8, 7, 6, 5, 4};
    cout << "Test 3: " << maxMontaña(arr3)
         << " (expected 8)" << endl;

    // Caso 4: Pico al final
    vector<int> arr4 = {1, 3, 5, 7, 9};
    cout << "Test 4: " << maxMontaña(arr4)
         << " (expected 9)" << endl;

    // Caso 5: Montaña muy pequeña (2 elementos, máximo es 7)
    vector<int> arr5 = {7, 5};
    cout << "Test 5: " << maxMontaña(arr5)
         << " (expected 7)" << endl;

    // Caso 6: Montaña muy pequeña (2 elementos, máximo es 9)
    vector<int> arr6 = {3, 9};
    cout << "Test 6: " << maxMontaña(arr6)
         << " (expected 9)" << endl;

    return 0;
}