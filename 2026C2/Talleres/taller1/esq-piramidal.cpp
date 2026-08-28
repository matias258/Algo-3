#include <vector>
#include <iostream>
#include <queue>
#include <list>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <cstdio>
#include <cassert>
using namespace std;


vector<bool> visitado;

int dfs_profundidad(vector<vector<int>>& matriz, int nodo, vector<bool>& visitado, int n){
    
    visitado[nodo] = true;
    int maximo = 0;
    for (int i = 0; i < n; i++){
        if (matriz[nodo][i] == 1){
            if (visitado[i] == false){
                int profundidad = dfs_profundidad(matriz, i, visitado, n);
                if (profundidad > maximo){
                    maximo = profundidad;
                }
            }     
        }         
    }

    return 1 + maximo;
}

// Hagamos el grafo mediante matriz de adyacencia
int grafo(vector<int> revendedores, int n){
    if (revendedores.size() == 0){
        return 0;
    }
    if (revendedores.size() == 1){
        return 1;
    }

    vector<vector<int>> matriz_adyacencia(n, vector<int>(n, 0));
    int nodo = -1;
    vector<bool> visitados(vector<bool>(n, false));

    for (int i = 0; i < n; i++){
        if (revendedores[i] != -1){
            matriz_adyacencia[revendedores[i]- 1][i] = 1;
            matriz_adyacencia[i][revendedores[i] - 1] = 1;
        }
        else{
            nodo = i;
        }
    }

    if (revendedores[nodo] != -1){
        return 0;
    }
    int max_prof = 0;

    for (int i = 0; i < n; i++){
        if (revendedores[i] == -1 && visitados[i] == false){
            int prof = dfs_profundidad(matriz_adyacencia, i, visitados, n);
            if (prof > max_prof){
                max_prof = prof;
            }
        }
    }
    return max_prof;
}



/*

int main(){

    int n; // # de socios vendedores
    cin >> n;

    vector<int> revendedores(n);    // orden de los vendedores

    for (int i = 0; i < n; i++){
        cin >> revendedores[i];
    }

    cout << grafo(revendedores, n);
}

*/
int main() {
    // Test 1: Ejemplo del enunciado (Bosque con 1 raíz y varias ramas)
    // Cadena más larga: 4 -> 3 -> 2 -> 1 (Profundidad = 4)
    int n1 = 6;
    vector<int> t1 = {2, 3, 4, -1, 4, 3};
    int res1 = grafo(t1, n1);
    cout << "Test 1 (Ejemplo enunciado): " << res1 << " | " << (res1 == 4 ? "PASO" : "FALLO") << endl;
    assert(res1 == 4);

    // Test 2: Caso base con N = 1 (Sin superiores)
    int n2 = 1;
    vector<int> t2 = {-1};
    int res2 = grafo(t2, n2);
    cout << "Test 2 (Nodo único): " << res2 << " | " << (res2 == 1 ? "PASO" : "FALLO") << endl;
    assert(res2 == 1);

    // Test 3: Grafo completamente plano (Todos son raíces)
    int n3 = 4;
    vector<int> t3 = {-1, -1, -1, -1};
    int res3 = grafo(t3, n3);
    cout << "Test 3 (Bosque plano / sin superiores): " << res3 << " | " << (res3 == 1 ? "PASO" : "FALLO") << endl;
    assert(res3 == 1);

    // Test 4: Cadena puramente lineal (1 -> 2 -> 3 -> 4 -> 5)
    int n4 = 5;
    vector<int> t4 = {-1, 1, 2, 3, 4};
    int res4 = grafo(t4, n4);
    cout << "Test 4 (Cadena lineal estricta): " << res4 << " | " << (res4 == 5 ? "PASO" : "FALLO") << endl;
    assert(res4 == 5);

    // Test 5: Múltiples árboles desbalanceados (Bosque con 2 componentes)
    int n5 = 5;
    vector<int> t5 = {-1, 1, -1, 3, 4};
    int res5 = grafo(t5, n5);
    cout << "Test 5 (Múltiples árboles desbalanceados): " << res5 << " | " << (res5 == 3 ? "PASO" : "FALLO") << endl;
    assert(res5 == 3);

    // Test 6: Árbol Estrella (1 jefe con 4 subordinados directos)
    int n6 = 5;
    vector<int> t6 = {-1, 1, 1, 1, 1};
    int res6 = grafo(t6, n6);
    cout << "Test 6 (Árbol Estrella): " << res6 << " | " << (res6 == 2 ? "PASO" : "FALLO") << endl;
    assert(res6 == 2);

    // Test 7: Cadenas Paralelas de igual profundidad (Bosque 2x3)
    int n7 = 6;
    vector<int> t7 = {-1, 1, 2, -1, 4, 5};
    int res7 = grafo(t7, n7);
    cout << "Test 7 (Cadenas Paralelas): " << res7 << " | " << (res7 == 3 ? "PASO" : "FALLO") << endl;
    assert(res7 == 3);

    // Test 8: Árbol Binario Completo
    int n8 = 7;
    vector<int> t8 = {-1, 1, 1, 2, 2, 3, 3};
    int res8 = grafo(t8, n8);
    cout << "Test 8 (Arbol Binario Completo): " << res8 << " | " << (res8 == 3 ? "PASO" : "FALLO") << endl;
    assert(res8 == 3);

    // Test 9: Ramas desbalanceadas en la misma raíz
    int n9 = 5;
    vector<int> t9 = {-1, 1, 2, 3, 1};
    int res9 = grafo(t9, n9);
    cout << "Test 9 (Ramas asimetricas): " << res9 << " | " << (res9 == 4 ? "PASO" : "FALLO") << endl;
    assert(res9 == 4);

    // Test 10: caso con múltiples ramas desde la raíz (ver si el pase por valor rompe algo)
    int n10 = 4;
    vector<int> t10 = {4, 4, 2, -1};
    int res10 = grafo(t10, n10);
    cout << "Test 10 (ramas multiples desde raiz): " << res10 << " | " << (res10 == 3 ? "PASO" : "FALLO") << endl;
    assert(res10 == 3);

    // Test 11: caso con multiples raices - respuesta esperada: 3
    int n11 = 5;
    vector<int> t11 = {-1, 1, 2, -1, 4};
    int res11 = grafo(t11, n11);
    cout << "Test (múltiples raíces, root correcto no es el último): "
         << res1 << " | " << (res11 == 3 ? "PASO" : "FALLO") << endl;
    assert(res11 == 3);

    return 0;

}


