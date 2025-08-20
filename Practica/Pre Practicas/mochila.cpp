#include <iostream>
#include <vector>
using namespace std ;

/*
Mochila Knapsack

Dado un conjunto de n objetos, cada uno con:
un peso w_i
un valor v_i
Y una capacidad total de mochila W, queremos seleccionar un subconjunto de objetos tal
que:
la suma de los pesos no supere W.
y la suma de los valores sea máxima.
No se pueden fraccionar los objetos (por eso es binario).
Se puede resolver por fuerza bruta con 2^n combinaciones posibles.
*/

/*
1. Estado:
Definimos un estado dp[i][w] como:
El valor maximo usando los primeros i objetos y peso w

2. Caso Base:
dp[0][w] = 0: con 0 objetos el valor es nulo.

3. Caso Recursivo:
En cada estado (i, w):
a. O no tomas el objeto i, y tu mejor valor es el mismo que antes:
dp[i][w] = dp[i-1][w]
b. O sí lo tomas (entra en la mochila):
dp[i][w] = dp[i-1][w-w_i] + v_i

Entonces: Nos quedamos con el max entre los dos.
dp[i][w] = max(dp[i-1][w], dp[i-1][w-w_i]+v_i)

4. Transicion:
Igual al caso recursivo

5. Orden Topologico:
Procesar i de menor a mayor, w de menor a mayor

6. DAG (Cadena de dependencias, 0->1->2->...->n):
(i, w) depende de (i-1, w) y (i-1, w-w_i)
*/

// vector<int>& v = el valor de cada objeto
// vector<int>& w = el peso de cada objeto
// int i = el índice del objeto v que estamos mirando en esa iteración
// int W = el peso máximo que no debemos sobrepasar

// Implementacion top down

//memo: almacena los resultados de subproblemas ya resueltos
vector<vector<int>> memo;
int mochila_topdown(vector<int>& v, vector<int>& w, int i, int W){
    // Si i == 0, me quede sin objetos
    // Si W == 0, me quede sin peso extra que cargar
    if (i == 0 || W == 0){
        return 0;
    }
    // Si memo actual != -1, 
    if(memo[i][W] != -1){
        return memo[i][W];
    }
    int res = mochila_topdown(v, w, i-1, W); // No tomar el objeto
    if (w[i-1] <= W){       // Tomar el objeto
        res = max(res, mochila_topdown(v, w, i-1, W - w[i-1]) + v[i-1]);
    }
    return memo[i][W] = res;
}

int main() {
    // Valores de los objetos
    vector<int> valores = {60, 100, 120};
    // Pesos de los objetos
    vector<int> pesos = {10, 20, 30};
    // Capacidad máxima de la mochila
    int capacidad = 50;
    // Número de objetos
    int n = valores.size();
    // Inicializar la memoización con -1
    memo = vector<vector<int>>(n + 1, vector<int>(capacidad + 1, -1));

    int resultado = mochila_topdown(valores, pesos, n, capacidad);
    cout << "El valor máximo que se puede obtener es: " << resultado << endl;

    return 0;
}


// Implementacion bottom up


