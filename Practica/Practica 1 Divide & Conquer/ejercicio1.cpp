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
Merge Sort para Python

def merge_sort ( arr ):
    if len ( arr ) <= 1:
        return arr
    medio = len ( arr ) // 2 
    mitad_izq = merge_sort ( arr [: medio ])
    mitad_der = merge_sort ( arr [ medio :])
    return merge ( mitad_izq , mitad_der )

def merge ( izq , der ):
    mergeados = []
    i = j = 0

    while i < len ( izq ) and j < len ( der ):
        if izq [i] < der [j ]:
            mergeados . append ( izq [ i ])
            i += 1
        else :
            mergeados . append ( der [ j ])
            j += 1

    mergeados . extend ( izq [ i :])
    mergeados . extend ( der [ j :])
    return mergeados

*/

vector<int> merge (vector<int> izq, vector<int> der){
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


vector<int> merge_sort(vector<int> arr){
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

int main(){

    vector<int> arr = {1, 6, 2, 2, 8, 433 , 1 , -54};
    vector<int> sorted_arr = merge_sort(arr);

    cout << "The Sorted array elements are: ";
    for (int i = 0; i < sorted_arr.size(); i++) {
        cout << sorted_arr[i] << ' ';
    }
    return 0;
}

/*
Respondamos a las preguntas del enunciado:
1. Identificar qu´e lineas son el divide, cu´ales son el conquer y cu´ales el combine.
2. ¿En cu´antos subproblemas se divide?
3. ¿De qu´e tama˜no son estos subproblemas?
4. ¿Cu´al es el costo de combinar los resultados de los subproblemas?
5. Escribir la funci´on T(n) de manera recursiva.
6. Determinar la complejidad del algoritmo utilizando el Teorema Maestro.

1) 
a. Divide: dividimos el problema por la mitad
int medio = arr.size() / 2;  

b. Conquer: Resuelve los problemas más pequeños recursivamente
mitad_izq = merge_sort(mitad_izq);
mitad_der = merge_sort(mitad_der);

c. Combine: Reordena los problemas más pequeños
return merge(mitad_izq, mitad_der); 

2,3) Se divide en 2 subproblemas de tamaño n/2, mitad_izq y mitad_der

4) El costo de combinar los resultados de los subproblemas es de O(n):
a. La funcion merge recorre cada elemento una sola vez
b. En el peor caso, compara todos los elementos de ambas mitades
c. Total de operaciones: n comparaciones + n inserciones = O(n)

5) Recordemos el Teo Maestro:
T(n) = { 1              ,si n = 1 }
       { aT(n/c) + f(n) ,si n > 1 }
(1) Si f(n) = O(n^logc(a)-E) para E > 0, entonces T(n) = Tita(n^logc(a))
(2) Si f(n) = Tita(n^logc(a)), entonces T(n) = Tita(n^logc(a)) * log(n))
(3) Si f(n) = Omega(n^logc(a)+E) para E > 0 y af(n/c) < kf(n) para k < 1 y n suficientemente grandes, entonces T(n) = Tita(f(n))       

Donde:
a: Numero de subproblemas
c: factor de división 
f(n): Costo de Combinar (Merge)

Veamos para Merge Sort
Tenemos que:
a = 2, tenemos 2 iteraciones cada vez
c = 2, particionamos el problema en 2 partes
f(n) = Tita(n) (Merge) = Tita(n), pues SABEMOS que la combinación es lineal (en cota sup e inf).
                         Si usamos O(n), vamos a tener distintos resultados.

Entonces 
T(n) = { Tita(1)                ,si n <= 1 }
       { 2T(n/2) + Tita(n)      ,si n > 1  }

6. Veamos que dice el Teorema Maestro en este caso:
Como f(n) = Tita(n), entramos en el 2do caso, pues Tita(n) ⊂ Tita(n^log2(2)) = Tita(n)
--> Tita(n) ⊂ Tita(n)
Entonces obtenemos que Merge Sort tiene T(n) = Tita(n^log2(2)) * log(n)) = Tita(n * log(n))
Merge Sort tiene complejidad Tita(nlog(n))
*/