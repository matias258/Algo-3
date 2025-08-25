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
vector<int> merge (vector<int> izq, vector<int> der, vector<int> med){
    int izq_sum, der_sum, med_sum = 0;

    for(int i = 0; i < izq.size(); i++){
        izq_sum += izq[i];
    }
    for(int i = 0; i < der.size(); i++){
        der_sum += der[i];
    }
    for(int i = 0; i < med.size(); i++){
        med_sum += med[i];
    }

    if (izq_sum > med_sum && izq_sum > der_sum){
        return izq;
    }
    else if(der_sum > izq_sum && der_sum > med_sum){
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
    if (arr.size() <= 1){
        return arr;
    }
    if (i > j){
        return arr;
    }
    
    int medio = arr.size() / 2;                   // Divide

    for (int k = 0; k <= medio; k++){
        mitad_izq.push_back(arr[k]);
    }
    for (int k = medio + 1; k < arr.size(); k++){
        mitad_der.push_back(arr[k]);
    }
    for (int k = i; k <= j; k++){
        mitad_med.push_back(arr[k]);
    }
    vector<int> maximo = merge(mitad_izq, mitad_der, mitad_med);

    vector<int> max_izq = merge_sort(mitad_izq, 0, mitad_izq.size()-1);            // Conquer
    vector<int> max_der = merge_sort(mitad_der, 0, mitad_der.size()-1);            // Conquer
    vector<int> max_med_1 = merge_sort(mitad_med, i+1, j);          // Conquer
    vector<int> max_med_2 = merge_sort(mitad_med, i, j-1);          // Conquer

    return merge(mitad_izq, mitad_der, mitad_med);      // Combine
}



int main() {
    vector<int> arr = {3, -1, 4, 8, -2, 2, -7, 5};
    vector<int> res = merge_sort(arr, 0, arr.size()-1);
    printf("El resultado obtenido es: ", res);
    return 0;
}