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
#include <utility>
using namespace std;

int bfs(vector<vector<int>>& lista_ady, int nodo_inicial, vector<int>& camino, int n){

    // cambio
    vector<int> pos_en_camino(n + 1, -1);
    for (int i = 0; i < (int)camino.size(); i++){
        pos_en_camino[camino[i]] = i;
    }

    vector<bool> visitados(lista_ady.size() + 1, false);
    queue<int> cola;
    cola.push(nodo_inicial);
    visitados[nodo_inicial] = true; 
    int indice = 1;
    
    // si la cola tiene nodos, entonces no visitamos a todos los vecinos de todos los nodos todavia
    while(cola.empty() == false){
        //leo el 1er nodo de la cola y lo guardo en mi variable "nodo"
        int nodo = cola.front();
        
        // elimino el 1er nodo de la cola
        cola.pop();

        
        vector<int> vecinos_no_visitados;
        for (int vecino : lista_ady[nodo]){
            if (visitados[vecino] == false){
                vecinos_no_visitados.push_back(vecino);
            }
        }

        int k = vecinos_no_visitados.size();


        for (int vecino : vecinos_no_visitados){
            int p = pos_en_camino[vecino];
            if (p < indice || p >= indice + k){
                return 0; // es decir que el vecino no cae en el bloque esperado
            }
        }

        // Si llegamos aca, es que coinciden 
        for (int i = indice; i < indice + k; i++){
            visitados[camino[i]] = true;
            cola.push(camino[i]);
        }

        indice += k;
    }
    
    if (indice == camino.size()){
        return 1;
    }
    return 0;
}


string grafo(int n, vector<pair<int,int>> aristas, vector<int> camino){
    if (n == 0 || camino.empty()){
        return "No"; 
    }

    if (camino[0] < 1 || camino[0] > n){
        return "No"; 
    }

    if (camino.size() == 1){
        return "Yes";
    }

    if (camino[0] != 1){
        return "No";
    }

    // armo mi lista de adyacencia
    vector<vector<int>> lista(n + 1);

    for (pair<int, int> arista : aristas) {
        int pri = arista.first;
        int segu = arista.second;

        lista[pri].push_back(segu); // nodo1 -> nodo2
        lista[segu].push_back(pri); // nodo2 -> nodo1
    }

  
    int nodo = camino[0];

    int respuesta = bfs(lista, nodo, camino, n);

    if (respuesta == 0){
        return "No";
    }
 
    return "Yes";
}


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

    string respuesta = grafo(n, aristas, camino);
    cout << respuesta << endl;   
    return 0; 
}

/*
int main(){

    // Test 1: ejemplo del enunciado - recorrido BFS válido (esperado: Yes)
    int n1 = 4;
    vector<pair<int,int>> aristas1 = {{2,4},{1,2},{1,3}};
    vector<int> camino1 = {1,3,2,4};
    string res1 = grafo(n1, aristas1, camino1);
    cout << "Test 1 (BFS valido, ejemplo enunciado): " << res1 << " | " << (res1 == "Yes" ? "PASO" : "FALLO") << endl;
    assert(res1 == "Yes");

    // Test 2: mismo árbol, recorrido inválido (esperado: No)
    int n2 = 4;
    vector<pair<int,int>> aristas2 = {{2,4},{1,2},{1,3}};
    vector<int> camino2 = {1,4,2,3};
    string res2 = grafo(n2, aristas2, camino2);
    cout << "Test 2 (BFS invalido, ejemplo enunciado): " << res2 << " | " << (res2 == "No" ? "PASO" : "FALLO") << endl;
    assert(res2 == "No");

    // Test 3: árbol de un solo nodo (esperado: Yes)
    int n3 = 1;
    vector<pair<int,int>> aristas3 = {};
    vector<int> camino3 = {1};
    string res3 = grafo(n3, aristas3, camino3);
    cout << "Test 3 (nodo unico): " << res3 << " | " << (res3 == "Yes" ? "PASO" : "FALLO") << endl;
    assert(res3 == "Yes");

    // Test 4: árbol lineal / cadena, único orden posible (esperado: Yes)
    int n4 = 5;
    vector<pair<int,int>> aristas4 = {{1,2},{2,3},{3,4},{4,5}};
    vector<int> camino4 = {1,2,3,4,5};
    string res4 = grafo(n4, aristas4, camino4);
    cout << "Test 4 (cadena lineal): " << res4 << " | " << (res4 == "Yes" ? "PASO" : "FALLO") << endl;
    assert(res4 == "Yes");

    // Test 5: árbol estrella, orden de hijos distinto al de las aristas (esperado: Yes)
    int n5 = 5;
    vector<pair<int,int>> aristas5 = {{1,2},{1,3},{1,4},{1,5}};
    vector<int> camino5 = {1,4,2,5,3};
    string res5 = grafo(n5, aristas5, camino5);
    cout << "Test 5 (estrella, orden distinto de hijos): " << res5 << " | " << (res5 == "Yes" ? "PASO" : "FALLO") << endl;
    assert(res5 == "Yes");

    cout << "\nTodos los tests pasaron correctamente!" << endl;
    return 0;
}
*/