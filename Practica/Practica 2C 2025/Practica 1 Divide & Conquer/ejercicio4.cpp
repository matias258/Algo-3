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
Ejercicio 4 (IndiceEspejo) ⋆
Tenemos un arreglo a = [a1, a2, . . . , an] de n enteros distintos (positivos y negativos) en orden estrictamente creciente. Queremos determinar si existe una posicion i tal que a_i = i. Por ejemplo, dado el arreglo a = [−4, −1, 2, 4, 7], i = 4 es esa posicion.
Diseñar un algoritmo dividir y conquistar eficiente (cuya complejidad sea de un orden estrictamente menor
que lineal) que resuelva el problema. Calcule y justifique la complejidad del algoritmo dado.
*/
///////////////////////////////////////////////////////////////////////////////
// Esta no funciono, preguntar si es valido y si cumpliria complejidad
bool indiceEspejo(vector<int> arr, vector<int> indices, int i, int j){
    if (i > j){
        return false;
    }
    int medio = arr.size() / 2;          // medio con respecto al sub_array
    if (indices[medio] == arr[medio]){
        return true;
    }
    if (indices[medio] < arr[medio]){
        vector<int> nuevo_array;
        vector<int> nuevo_indices;
        for (int l = i; l <= medio - 1; l++){
            nuevo_array.push_back(arr[l]);
            nuevo_indices.push_back(indices[l]);
        }
        indiceEspejo(nuevo_array, nuevo_indices, i, medio);
    }
    else{
        vector<int> nuevo_array;
        vector<int> nuevo_indices;
        for (int l = medio; l <= j; l++){
            nuevo_array.push_back(arr[l]);
            nuevo_indices.push_back(indices[l]);
        }
        indiceEspejo(nuevo_array, nuevo_indices, medio, j);
    }
    return false;
}
///////////////////////////////////////////////////////////////////////////////

// Busqueda binaria tradicional con la condicion pedida
bool indiceEspejo2(vector<int> arr, int i, int j){
    if (i > j){
        return false;
    }
    int medio = (i+j)/2;
    if (arr[medio] == medio + 1){
        return true;
    }
    else if (arr[medio] > medio + 1){
        return indiceEspejo2(arr, i, medio - 1);
    }
    else{
        return indiceEspejo2(arr, medio + 1, j);
    }
}

bool EspejitoRebotin(vector<int> arr){
    return indiceEspejo2(arr, 0, arr.size() - 1);
}
///////////////////////////////////////////////////////////////////////////////
/*
Calculemos la complejidad:
a = 1, elegimos el subproblema más útil
c = 2, partimos el problema por la mitad
f(n) = O(1) = Tita(1) = Omega(1), no mergeamos y además el costo de las operaciones fuera de la recurrencia son todas constantes. Como las operaciones se realizan siempre, todos los casos son = O(1)

T(n) = aT(n/2) + f(n) si n > 1; 1 si n <= 1
Caso 1: O(n^log2(1)-e) = O(n^-e) = O(1/n^e), pero f(n) = O(1) es mayor que O(1/n^e), luego Absurdo!
Caso 2: Tita(n^log2(1)) = Tita(1) que es exactamente lo que vale f(n), luego pertenece a Caso 2:
Entonces --> T(n) = Tita(n^log2(a) * log(n)) = Tita(log(n))
La función encontrada tiene complejidad logarítmica. 
*/


int main(){
    // Caso 1: ejemplo tuyo
    vector<int> arr1 = {-4, -1, 3, 5, 7};
    cout << "Test 1: " << EspejitoRebotin(arr1) 
         << " (expected 1)" << endl;  
    // Explicación: arr[2] = 3, índice 3 → fixed point.

    // Caso 2: ningún índice espejo
    vector<int> arr2 = {-5, -2, 0, 1, 4};
    cout << "Test 2: " << EspejitoRebotin(arr2) 
         << " (expected 0)" << endl;  

    // Caso 3: índice espejo en el comienzo
    vector<int> arr3 = {0, 2, 3, 4, 5};
    cout << "Test 3: " << EspejitoRebotin(arr3) 
         << " (expected 1)" << endl;  

    // Caso 4: índice no espejo
    vector<int> arr4 = {-10, -5, 0, 1, 4};
    cout << "Test 4: " << EspejitoRebotin(arr4) 
         << " (expected 0)" << endl;  

    // Caso 5: arreglo con un solo elemento índice no espejo
    vector<int> arr5 = {0};
    cout << "Test 5: " << EspejitoRebotin(arr5) 
         << " (expected 0)" << endl;  

    // Caso 6: arreglo con un solo elemento pero no coincide
    vector<int> arr6 = {2};
    cout << "Test 6: " << EspejitoRebotin(arr6) 
         << " (expected 0)" << endl;  

    // Caso 7: arreglo con números negativos
    vector<int> arr7 = {-3, -2, -1, 3, 5};
    cout << "Test 7: " << EspejitoRebotin(arr7) 
         << " (expected 1)" << endl;  

    // Caso 8: arreglo grande sin índice espejo
    vector<int> arr8 = {-10, -9, -8, -7, -6, -5};
    cout << "Test 8: " << EspejitoRebotin(arr8) 
         << " (expected 0)" << endl;  

    // Caso 9: arreglo con un solo elemento índice espejo
    vector<int> arr9 = {1};
    cout << "Test 9: " << EspejitoRebotin(arr9) 
         << " (expected 1)" << endl;  

    return 0;
}