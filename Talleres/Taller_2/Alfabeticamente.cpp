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

int alfabeticamente(int n, vector<int> c, vector<string> palabras){
    if ()
}

int main(){
    int n = 3;
    vector<int> c = {100, 200, 300};
    vector<string> palabras = {"abc", "efg", "hij"};

    int res = alfabeticamente(n, c, palabras);
}