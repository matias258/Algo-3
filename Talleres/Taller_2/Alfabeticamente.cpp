#include <vector>
#include <iostream>
#include <queue>
#include <list>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <cstdio>
#include <algorithm>
using namespace std;

/*
Link: https://codeforces.com/group/yuAAIJ8c1R/contest/629197/problem/A

Juan tiene n strings de letras minúsculas del alfabeto inglés. 
Quiere ordenarlas alfabéticamente, pero no tiene permitido cambiarlas de lugar. Lo único que puede hacer es dar vuelta algunas de ellas (dar vuelta un string s es leerlo de atrás para adelante). Dos palabras iguales consecutivas se consideran ordenadas. Para dar vuelta el string i tiene que gastar ci unidades de energía. Él quiere minimizar la cantidad de energía que necesita gastar para que las palabras queden en orden alfabético. 

Input:
La primera línea del input contiene un entero n (2≤n≤100.000 ), la cantidad de palabras. 
La siguiente línea contiene los n enteros ci (0≤ci≤109 ). 
Las últimas n líneas contienen cada uno de los strings a ordenar. 
La longitud total de estos strings es menor o igual a 100.000 caracteres. 

Output: 
Si es imposible invertir algunas (posiblemente 0) de las strings para que queden ordenadas alfabéticamente, imprimir -1. 
En caso contrario, imprimir la mínima cantidad de energía que Juan necesita gastar para lograr su objetivo.
*/

bool estan_en_orden(vector<string>& palabras) {
    for (int i = 0; i < palabras.size() - 1; i++) {
        if (palabras[i] > palabras[i + 1]) {
            return false;
        }
    }
    return true;
}

vector<string> merge (vector<string> izq, vector<string> der, vector<int> c){
    vector<string> mergeados;
    vector<string> izq2;
    vector<string> der2;
    int gasto = 0;
    int i, j = 0;
    int x = 0;
    if (estan_en_orden(izq) != true){
        for (int x = izq.size() - 1; x >= 0; x--) {
            izq2.push_back(izq[x]);
        }
        izq = izq2;
        gasto = gasto + c[izq.size() - 1]
    }
    if (estan_en_orden(izq2) != true){
        return -1;
    }

    if (estan_en_orden(der) != true){
        for (int x = der.size() - 1; x >= 0; x--) {
            der2.push_back(der[x]);
        }
        der = der2;
        gasto = gasto + c[izq.size() - 1]
    }
    if (estan_en_orden(der2) != true){
        return -1;
    }
    
    // ahora tengo los 2 strings ordenados alfabeticamente
    // Quiero ver si los puedo unir
    // Para eso quiero ver si puedo concatenarlos y que sigan estando en orden

    if (izq[izq.size() - 1] < der[0]{
        return gasto;
    })
    
    return mergeados;
}

int alfabeticamente(vector<int> c, vector<string> palabras, int gasto, int indice){
    if (palabras.size() <= 1){
        return gasto;
    }
    int medio = palabras.size() / 2;
    vector<string>mitad_izq;
    vector<string>mitad_der; 

    for (int k = 0; k < medio; k++){
        mitad_izq.push_back(palabras[k]);
    }
    for (int k = medio; k < arr.size(); k++){
        mitad_der.push_back(palabras[k]);
    }

    mitad_izq = alfabeticamente(c, mitad_izq, palabras, gasto, medio - 1);            
    mitad_der = alfabeticamente(c, mitad_der, palabras, gasto, medio);            
    
    

    return merge(mitad_izq, mitad_der);
}

int main(){
    int n = 3;
    vector<int> c = {100, 200, 300};
    vector<string> palabras = {"abc", "efg", "hij"};

    int res = alfabeticamente(c, palabras);
}