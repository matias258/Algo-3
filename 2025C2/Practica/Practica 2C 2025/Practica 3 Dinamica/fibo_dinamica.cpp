#include <vector>
#include <iostream>
#include <queue>
#include <list>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <cstdio>
using namespace std;

int fibo(int x){
    if (x == 0){
        return 0;
    }
    if (x == 1){
        return 1;
    }
    return fibo(x-1) + fibo(x-2);
}

// Ahora quiero fibo dinamico
int fibo_din(int x, vector<int>& memo){
    if (x == 0){
        return 0;
    }
    if (x == 1){
        return 1;
    }
    if (memo[x] != -1){
        return memo[x];
    }
    memo[x] = fibo_din(x-1, memo) + fibo_din(x-2, memo);
    return memo[x];

}

int main(){
    int x = 10;

    // Inicializo memoria
    vector<int> memo(x + 1, -1);     // memo tamaño x+1, valores -1

    int res = fibo_din(x, memo);
    cout << res;
}

/* 
Veamos la complejidad temp y espacial:

Temp de Fibonacci Normal:
T(n) = T(n-1) + T(n-2), pero T(n-1) = T(n-2) + T(n-3) y T(n-2) = T(n-3) + T(n-4)
T(n) = 2T(n-2) + 2T(n-3) + T(n-4)
T(n) = 2[T(n-3) + T(n-4)] + 2[T(n-4) + T(n-5)] + T(n-5) + T(n-6)
T(n) = 2T(n-3) + 4T(n-4) + 2T(n-5) + T(n-6)
etc...
Viendo esto y sabiendo ademas que el peor caso es recorrer todo el arbol de largo n, 
vemos que la cota superior es O(2^n)
Y la inferior (recorrer la rama mas corta) es Ω(2^(n/2))

Esp de Fibonacci Normal:
O(1) pues nunca guardamos nada, ni utilizamos algo mas grande que un int, que tiene espacio cuasi nulo.


Temp de Fibonacci Dinamico:
1. Inicializar la memoria -> O(n)
2. Los llamados recursivos que estan guardados en memoria --> O(1)

La complejidad de un algo dinamico es la (# estados) * (costo de resolver internamente el estado)
En nuestro caso es O(n) * O(1) = O(n)

Espacial de Fibonacci Dinamico:
Tamaño de la memoria utilizada --> O(n):

Resumen:
| Algoritmo         | Complejidad Temporal| Complejidad Espacial |
|-------------------|---------------------|----------------------|
| Fibonacci normal  |      O(2^n)         |        O(1)          |
| Fibonacci dinámico|      O(n)           |        O(n)          |
*/

