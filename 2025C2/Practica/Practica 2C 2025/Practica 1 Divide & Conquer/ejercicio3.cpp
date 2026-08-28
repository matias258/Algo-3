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
bool IzquierdaDominante(vector<int> arr){
    if (arr.size() <= 1){
        return true;
    }

    int medio = arr.size() / 2;
    int sum_izq = 0;
    int sum_der = 0;
    vector<int>mitad_izq;
    vector<int>mitad_der; 
    for (int k = 0; k < medio; k++){
        mitad_izq.push_back(arr[k]);
        sum_izq += arr[k];
    }
    for (int k = medio; k < arr.size(); k++){
        mitad_der.push_back(arr[k]);
        sum_der += arr[k];
    }

    if (sum_der >= sum_izq){ // No es Izquierda Dominante
        return false;
    }
    return IzquierdaDominante(mitad_izq) && IzquierdaDominante(mitad_der);
}

int main(){
    vector<int> arr1 = {8, 4, 7, 6, 5, 1, 3, 2};     // false -> 0
    vector<int> arr2 = {8, 6, 7, 4, 5, 1, 3, 2};    // true -> 1
    vector<int> arr3 = {1};                         // true -> 1 (caso base tamaño 1)
    vector<int> arr4 = {5, 2};                      // true -> 1 (5 > 2, y ambos subcasos triviales)
    vector<int> arr5 = {2, 5};                      // false -> 0 (2 <= 5)
    vector<int> arr6 = {20, 15, 10, 5, 4, 3, 2, 1}; // true -> 1
    vector<int> arr7 = {1, 2, 3, 4};                // false -> 0 (izquierda 1+2=3 <= derecha 3+4=7)
    vector<int> arr8 = {-1, -2, -3, -4};            // true -> 1
    vector<int> arr9 = {9, 5, 1, 0};                // true -> 1 (14 > 1, y recursivamente también)
    vector<int> arr10 ={50, 40, 30, 20, 10, 9, 8, 7,// true -> 1 (izquierda siempre domina)
                         6, 5, 4, 3, 2, 1, 1, 0};       

    cout << "arr1: " << IzquierdaDominante(arr1) << " (expected 0)" << endl;
    cout << "arr2: " << IzquierdaDominante(arr2) << " (expected 1)" << endl;
    cout << "arr3: " << IzquierdaDominante(arr3) << " (expected 1)" << endl;
    cout << "arr4: " << IzquierdaDominante(arr4) << " (expected 1)" << endl;
    cout << "arr5: " << IzquierdaDominante(arr5) << " (expected 0)" << endl;
    cout << "arr6: " << IzquierdaDominante(arr6) << " (expected 1)" << endl;
    cout << "arr7: " << IzquierdaDominante(arr7) << " (expected 0)" << endl;
    cout << "arr8: " << IzquierdaDominante(arr8) << " (expected 0)" << endl;
    cout << "arr9: " << IzquierdaDominante(arr9) << " (expected 1)" << endl;
    cout << "arr10: " << IzquierdaDominante(arr10) << " (expected 1)" << endl;

    return 0;
}

/*
Calculemos la complejidad:
TEOREMA MAESTRO
------------------------------------------------------
T(n) = { 1              ,si n = 1 }
       { aT(n/c) + f(n) ,si n > 1 }
(1) Si f(n) = O(n^logc(a)-E) para E > 0, entonces T(n) = Tita(n^logc(a))
(2) Si f(n) = Tita(n^logc(a)), entonces T(n) = Tita(n^logc(a)) * log(n))
(3) Si f(n) = Omega(n^logc(a)+E) para E > 0 y af(n/c) < kf(n) para k < 1 y n suficientemente grandes, entonces T(n) = Tita(f(n))       
------------------------------------------------------
1. a = 2, tenemos 2 iteraciones cada vez.
2. c = 2, particionamos el problema en 2 partes. Mitad derecha y mitad izquierda.
3. f(n) = O(n) = Tita(n), pues:
La complejidad de todo lo que no requiere recurrencia: O(n), iteramos la funcion entera en el "for",
La complejidad de mergear: O(1), no mergeamos
--> f(n) = O(n) + O(1) = O(n) = Tita(n), pues iteramos en todos lo casos, mejor, promedio y peor.

Entonces:
T(n) = { 1              ,si n <= 1 }
       { 2T(n/2) + O(n) ,si n > 1 }
Caso 1: No llegamos pues O(n) tiene complejidad mayor que O(n^log2(2)-e) = O(n^-e)
Caso 2: Si llegamos pues O(n) tiene misma complejidad que Tita(n^log2(2)) = Tita(n)
Caso 3: No hace falta, ya que encontramos que f(n) pertenece al Caso 2.

Luego la complejidad del algoritmo encontrado es:
- Tita(n^logc(a) * log(n)) = Tita(n^log2(2) * log(n)) = Tita(n * log(n))
Y además, Tita(n * log(n)) tiene complejidad menor que O(n^2), luego cumplimos con lo pedido.
*/