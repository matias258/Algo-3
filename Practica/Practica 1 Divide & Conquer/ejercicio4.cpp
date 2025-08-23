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
// Bucle infinito
bool indiceEspejo(vector<int> arr, int i, int j){
    if (i >= j){
        return false;
    }
    int medio = arr.size() / 2 + 1;                         // medio con respecto al sub_array
    int medio_completo = medio + i - (arr.size()-1 - j);    // medio con respecto al array completo
    if (medio_completo == arr[medio - 1]){
        return true;
    }
    if (medio_completo < arr[medio - 1]){
        indiceEspejo(arr, i, medio - 1);
    }
    else{
        indiceEspejo(arr, medio - 1, j);
    }
    return false;
}

int main(){
    vector<int> arr = {-4, -1, 2, 4, 7};
    bool res = indiceEspejo(arr, 0, arr.size() - 1);
    cout << res;
    return 0;
}