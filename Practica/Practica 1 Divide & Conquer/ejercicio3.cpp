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
Ejercicio 3 (IzquierdaDominante) ⋆

Escriba un algoritmo con dividir y conquistar que determine si un arreglo de tamaño potencia de 2 es mas
a la izquierda, donde “mas a la izquierda” significa que:
- La suma de los elementos de la mitad izquierda superan los de la mitad derecha.
- Cada una de las mitades es a su vez “mas a la izquierda”.
Por ejemplo, el arreglo [8, 6, 7, 4, 5, 1, 3, 2] es “mas a la izquierda”, pero [8, 4, 7, 6, 5, 1, 3, 2] no lo es.
Intente que su soluci´on aproveche la t´ecnica de modo que la complejidad del algoritmo sea estrictamente
menor a O(n^2).
*/

// Funciona mal, capaz convertir bool merge a vector merge y pasar algun dato de que es o no es izqDominante
bool merge(vector<int> arr_izq, vector<int> arr_der){
    bool mergeados = true;
    int i, j = 0;
    while (i < arr_izq.size() && j < arr_der.size()){
        int sum_izq = 0;
        int sum_der = 0;
        for (i = 0; i < arr_izq.size() - 1; i++){
            sum_izq += arr_izq[i];
        }
        for (i = 0; i < arr_der.size() - 1; i++){
            sum_der += arr_der[i];
        }

        if (sum_izq < sum_der){
            mergeados = mergeados || true;
        }
        else {
            mergeados = mergeados || false;
        }
    }   
    return mergeados;
}

bool IzquierdaDominante(vector<int> arr){
    if (arr.size() <= 1){
        return true;
    }

    int medio = arr.size() / 2;
    vector<int>mitad_izq;
    vector<int>mitad_der; 
    for (int k = 0; k < medio; k++){
        mitad_izq.push_back(arr[k]);
    }
    for (int k = medio; k < arr.size(); k++){
        mitad_der.push_back(arr[k]);
    }
    IzquierdaDominante(mitad_izq);            // Conquer
    IzquierdaDominante(mitad_der);            // Conquer
    return merge(mitad_izq, mitad_der);       // Combine
}

int main(){
    vector<int> arr = {8, 4, 7, 6, 5, 1, 3, 2};
    bool res = IzquierdaDominante(arr);
    if (res == true){
        cout << "Es Izquierda Dominante";
    }
    else{
        cout << "No es Izquierda Dominante";
    } 
    return 0;
}