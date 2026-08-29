#include <vector>
#include <iostream>
#include <queue>
#include <list>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <cstdio>
#include <cassert>
#include <string>
#include <sstream>
using namespace std;

int bfs(vector<pair<int,int>> aristas, int nodo, int indice, int n, vector<int> camino){
    if (indice + 1 >= camino.size()){
        return 1;
    }

    int m = camino[indice + 1];

    for (int i = 0; i < aristas.size(); i++){

        // Si en N(nodo) esta m (el siguiente nodo del camino)
        if (aristas[i] == make_pair(nodo, m) || aristas[i] == make_pair(m, nodo)){
            return bfs(aristas, m, indice + 1, n, camino);
        }
    }

    return 0;
}


int grafo(int n, vector<pair<int,int>> aristas, vector<int> camino){
    if (camino.size() == 0){
        return 0;
    }
    
    vector<int> nodos;
    for (int i = 0; i < n; i++){
        nodos.push_back(i+1);
    } 

    int nodo = camino[0];

    int respuesta = bfs(aristas, nodo, 0, n, camino);

    if (respuesta == 0){
        cout << "No";
    }
    else{
        cout << "Yes";
    }

    return respuesta;
}

/*
int main(){

    int n; // # nodos
    cin >> n;

    vector<pair<int, int>> aristas(n - 1);

    for (int i = 0; i < n - 1; i++){
        int x;
        int y;
        cin >> x >> y;
        aristas[i] = {x, y};
    }

    vector<int> camino(n);
    for (int i = 0; i < n; i++){
        cin >> camino[i];
    }

    int respuesta = grafo(n, aristas, camino);
    return respuesta;
}

*/
int main(){

    // Test 1: ejemplo del enunciado - recorrido BFS válido (esperado: 1)
    int n1 = 4;
    vector<pair<int,int>> aristas1 = {{2,4},{1,2},{1,3}};
    vector<int> camino1 = {1,3,2,4};
    int res1 = grafo(n1, aristas1, camino1);
    cout << "Test 1 (BFS valido, ejemplo enunciado): " << res1 << " | " << (res1 == 1 ? "PASO" : "FALLO") << endl;
    assert(res1 == 1);

    // Test 2: mismo árbol, recorrido inválido (esperado: 0)
    int n2 = 4;
    vector<pair<int,int>> aristas2 = {{2,4},{1,2},{1,3}};
    vector<int> camino2 = {1,4,2,3};
    int res2 = grafo(n2, aristas2, camino2);
    cout << "Test 2 (BFS invalido, ejemplo enunciado): " << res2 << " | " << (res2 == 0 ? "PASO" : "FALLO") << endl;
    assert(res2 == 0);

    // Test 3: árbol de un solo nodo (esperado: 1)
    int n3 = 1;
    vector<pair<int,int>> aristas3 = {};
    vector<int> camino3 = {1};
    int res3 = grafo(n3, aristas3, camino3);
    cout << "Test 3 (nodo unico): " << res3 << " | " << (res3 == 1 ? "PASO" : "FALLO") << endl;
    assert(res3 == 1);

    // Test 4: árbol lineal / cadena, único orden posible (esperado: 1)
    int n4 = 5;
    vector<pair<int,int>> aristas4 = {{1,2},{2,3},{3,4},{4,5}};
    vector<int> camino4 = {1,2,3,4,5};
    int res4 = grafo(n4, aristas4, camino4);
    cout << "Test 4 (cadena lineal): " << res4 << " | " << (res4 == 1 ? "PASO" : "FALLO") << endl;
    assert(res4 == 1);

    // Test 5: árbol estrella, orden de hijos distinto al de las aristas (esperado: 1)
    int n5 = 5;
    vector<pair<int,int>> aristas5 = {{1,2},{1,3},{1,4},{1,5}};
    vector<int> camino5 = {1,4,2,5,3};
    int res5 = grafo(n5, aristas5, camino5);
    cout << "Test 5 (estrella, orden distinto de hijos): " << res5 << " | " << (res5 == 1 ? "PASO" : "FALLO") << endl;
    assert(res5 == 1);

    cout << "\nTodos los tests pasaron correctamente!" << endl;
    return 0;
}
