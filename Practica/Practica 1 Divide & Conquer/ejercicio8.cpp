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
Ejercicio 8 (MaximaSubsecuencia) ⋆
Dada una secuencia de n enteros, se desea encontrar el maximo valor que se puede obtener sumando elementos contiguos. Diseñar un algoritmo basado en la tecnica de dividir y conquistar que resuelva el problema en O(n log n). Por ejemplo, para la secuencia [3, -1, 4, 8, -2, 2, -7, 5], este valor es 14, que se obtiene de la subsecuencia [3, -1, 4, 8].
*/

// Anda como el orto
vector<int> merge (vector<int> izq, int max_izq, vector<int> der, int max_der, vector<int> med, int max_med){

    if (max_izq > max_med && max_izq > max_der){
        return izq;
    }
    else if(max_der > max_izq && max_der > max_med){
        return der;
    }
    else{
        return med;
    }  
}


vector<int> merge_sort(vector<int> arr, int i, int j){
    vector<int>mitad_izq;
    vector<int>mitad_der; 
    vector<int> mitad_med;
    int max_izq, max_der, max_med = 0;
    if (arr.size() <= 1){
        return arr;
    }
    
    int medio = arr.size() / 2;                   // Divide

    for (int k = 0; k < medio; k++){
        mitad_izq.push_back(arr[k]);
        max_izq += arr[k];
    }
    for (int k = medio; k < arr.size(); k++){
        mitad_der.push_back(arr[k]);
        max_der += arr[k];
    }
    for (int k = i; k <= j; k++){
        mitad_med.push_back(arr[k]);
        max_med += arr[k];
    }
    mitad_izq = merge_sort(mitad_izq, i, j);            // Conquer
    mitad_der = merge_sort(mitad_der, i, j);            // Conquer
    mitad_med = merge_sort(mitad_med, i+1, j);          // Conquer
    mitad_med = merge_sort(mitad_med, i, j-1);          // Conquer

    return merge(mitad_izq, max_izq, mitad_der, max_der, mitad_med,max_med);           // Combine
}



int main() {
    vector<int> arr = {3, -1, 4, 8, -2, 2, -7, 5};
    vector<int> res = merge_sort(arr, 0, arr.size()-1);
    printf("El resultado obtenido es: ", res);
    return 0;
}