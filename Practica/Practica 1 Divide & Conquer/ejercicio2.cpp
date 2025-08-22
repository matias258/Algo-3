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
Dado el algoritmo de busqueda binaria, implementado en el siguiente codigo Python:

def busqueda_binaria ( arr , objetivo , izq =0 , der = len ( arr ) -1):
    if izq > der :
        return False # Elemento no encontrado
    medio = ( izq + der ) // 2
    if arr [ medio ] == objetivo :
        return medio
    elif arr [ medio ] > objetivo :
        return busqueda_binaria ( arr , objetivo , izq , medio - 1)
    else :
        return busqueda_binaria ( arr , objetivo , medio + 1, der )


Intentemos implementarla en C++

*/

// Input: array ordenado
bool busqueda_binaria(vector<int> arr_ordenado, int objetivo, int izq, int der){
    if (izq > der){
        return false;       // Elemento no encontrado
    }
    int medio = (izq + der) / 2;        // Divide

    if (arr_ordenado[medio] == objetivo){
        return true;        // Elemento encontrado
    }
    else if (arr_ordenado[medio] > objetivo){
        return busqueda_binaria(arr_ordenado, objetivo, izq, medio - 1);        // Conquer
    }
    else{
        return busqueda_binaria(arr_ordenado, objetivo, medio + 1, der);        // Conquer
    }
}

bool busqueda(vector<int> arr_ordenado, int objetivo){
    return busqueda_binaria(arr_ordenado, objetivo, 0, arr_ordenado.size() - 1);
}


int main(){
    vector<int> arr_ordenado = {1, 3, 4, 8, 9};
    bool res = busqueda(arr_ordenado, 4);
    if (res == true){
        cout << "Encontramos el valor en el array";
    }
    else{
        cout << "El valor no se encuentra en el array";
    } 
    return 0;
}

/*
1) Identificar qu´e lineas son el divide, cu´ales son el conquer y cu´ales el combine.
a. Divide: 
int medio = (izq + der) / 2; 

b. Conquer:
return busqueda_binaria(arr_ordenado, objetivo, izq, medio - 1);
return busqueda_binaria(arr_ordenado, objetivo, medio + 1, der); 

c. Combine:
No tiene Combine, porque directamente "desechamos" los valores que no nos sirven.

2) ¿En cu´antos subproblemas se divide?
Se divide en 1 subproblema: Elegimos un subarray y "eliminamos" el resto (no le prestamos mas atención)

3) ¿De que tamaño son estos subproblemas?
cada subproblema (o subarray) tiene tamaño n/2, donde n = array.size()

4) ¿Cual es el costo de combinar los resultados de los subproblemas?
Al ser no existente el Combine, el costo podría decirse que es O(1)

5) Escribir la funcion T(n) de manera recursiva.
Sabemos que:
a = 1
c = 2
f(n) = O(1) (El tiempo que tarda en encontrar "medio")

Entonces:
T(n) = { 1 si n <= 1               }
       { 1*T(n/2) + O(1) si n > 1  }

6) Determinar la complejidad del algoritmo utilizando el Teorema Maestro.
Teniendo lo que calculamos en 5) podemos determinar la complejidad del algoritmo:

f(n) = O(1)
Calculemos los 3 casos posibles
Caso 1: O(n^logc(a)-e) = O(n^log2(1)-e) = O(n^-e) para e > 0
Sea e = 1, f(n) = O(1) > O(n^-1), Absurdo! Luego f(n) no pertenece al Caso 1

Caso 2: Tita(n^logc(a)) = Tita(n^log2(1)) = Tita(1)
f(n) = O(1) es <= Tita(1), luego vemos que f(n) cae en el Caso 2.

Caso 3: Omega(n^logc(a)+e) = Omega(n^log2(1)+e) = Omega(n^0+e) = Omega(n^e) para e > 0
Por supuesto, f(n) = O(1) no es <= Omega(n^e), pues sea e = 1, O(1) < Omega(n^1), Absurdo!

Estamos entonces en el caso 2:
f(n) = Tita(1) --> T(n) = Tita(n^logc(a) * log(n)) = Tita(n^log2(1) * log(n)) = Tita(log(n))

Concluimos que la Busqueda Binaria tiene complejidad Tita(log(n))
*/