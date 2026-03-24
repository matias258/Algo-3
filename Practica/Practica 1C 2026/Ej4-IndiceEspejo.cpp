#include <vector>
#include <iostream>
#include <queue>
#include <list>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <cstdio>
using namespace std;

bool IndiceEspejo(vector<int> a, int i, int j){
    if (i > j){
        return false;
    }

    int medio = i + (j - i) / 2;
    int indiceProblema = medio + 1;
    if (a[medio] == indiceProblema){
        return true;
    }
    else if (a[medio] < indiceProblema)
    {
        return IndiceEspejo(a, medio + 1, j);
    }
    else{
        return IndiceEspejo(a, i, medio - 1);
    }
    
}

bool EspejitoRebotin(vector<int> a){
    if (a.empty()) return false;
    return IndiceEspejo(a, 0, a.size());
}



int main() {
    // --- TESTS ORIGINALES AJUSTADOS A ÍNDICE 1 ---
    
    // Caso 1: Ejemplo del enunciado (arr[3] = 4 es el error en tu comentario, 
    // pero si arr = [-4, -1, 2, 4, 7], entonces arr[3] es 4, que es i=4)
    // Usamos el del enunciado: [-4, -1, 2, 4, 7] -> i=4 es 4.
    vector<int> arr1 = {-4, -1, 2, 4, 7}; 
    cout << "Test 1: " << EspejitoRebotin(arr1) << " (expected 1)" << endl;  

    // Caso 2: Ningún índice espejo
    vector<int> arr2 = {-5, -2, 0, 1, 4};
    cout << "Test 2: " << EspejitoRebotin(arr2) << " (expected 0)" << endl;  

    // Caso 3: Índice espejo en el comienzo (arr[0] = 1 -> i=1)
    vector<int> arr3 = {1, 3, 4, 5, 6};
    cout << "Test 3: " << EspejitoRebotin(arr3) << " (expected 1)" << endl;  

    // Caso 4: Valores crecen pero nunca alcanzan al índice
    vector<int> arr4 = {-10, -5, 0, 1, 2};
    cout << "Test 4: " << EspejitoRebotin(arr4) << " (expected 0)" << endl;  

    // Caso 5: Un solo elemento que coincide (i=1, arr[0]=1)
    vector<int> arr5 = {1};
    cout << "Test 5: " << EspejitoRebotin(arr5) << " (expected 1)" << endl;  

    // Caso 6: Un solo elemento que NO coincide
    vector<int> arr6 = {2};
    cout << "Test 6: " << EspejitoRebotin(arr6) << " (expected 0)" << endl;  

    // Caso 7: Todo negativo
    vector<int> arr7 = {-3, -2, -1};
    cout << "Test 7: " << EspejitoRebotin(arr7) << " (expected 0)" << endl;  

    // Caso 8: Arreglo grande sin índice espejo
    vector<int> arr8 = {-10, -9, -8, -7, -6, -5};
    cout << "Test 8: " << EspejitoRebotin(arr8) << " (expected 0)" << endl;  

    // Caso 9: Espejo justo después de negativos (arr[2]=3 -> i=3)
    vector<int> arr9 = {-2, 0, 3, 5, 8};
    cout << "Test 9: " << EspejitoRebotin(arr9) << " (expected 1)" << endl;  


    // --- 5 TESTS NUEVOS (AJUSTADOS A ÍNDICE 1) ---

    // Caso 10: Índice espejo en la última posición (n=5, arr[4]=5 -> i=5)
    vector<int> arr10 = {-2, 0, 1, 2, 5};
    cout << "Test 10: " << EspejitoRebotin(arr10) << " (expected 1)" << endl; 

    // Caso 11: Todos los valores son mucho mayores al índice
    vector<int> arr11 = {10, 11, 12, 13, 14};
    cout << "Test 11: " << EspejitoRebotin(arr11) << " (expected 0)" << endl; 

    // Caso 12: Espejo en posición par (arr[3]=4 -> i=4)
    vector<int> arr12 = {-5, -3, -1, 4}; 
    cout << "Test 12: " << EspejitoRebotin(arr12) << " (expected 1)" << endl; 

    // Caso 13: Arreglo vacío
    vector<int> arr13 = {};
    cout << "Test 13: " << EspejitoRebotin(arr13) << " (expected 0)" << endl; 

    // Caso 14: Arreglo largo, espejo en la mitad (arr[4]=5 -> i=5)
    vector<int> arr14 = {-10, -5, -2, 0, 5, 8, 10, 12, 15}; 
    cout << "Test 14: " << EspejitoRebotin(arr14) << " (expected 1)" << endl; 

    return 0;
}