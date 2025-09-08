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
https://codeforces.com/group/yuAAIJ8c1R/contest/629197/problem/B

Tienes un string s de n letras del alfabeto latino. Puedes aplicar la siguiente operación una cantidad arbitraría de veces en el string:

Elige un substring (contiguo) de caracteres iguales y bórralo. Luego concatena las partes resultantes. Por ejemplo, en acccad podemos borrar el rango [1,4) y obtener aad.
Calcula la mínima cantidad de operaciones necesaria para eliminar todo el string s.

Input
La primera línea contiene un entero n=|s| (1≤n≤500).
La segunda línea contiene el string s

Output
Imprime un único entero, la mínima cantidad de operaciones necesaria para borrar s

Ejemplo:
Input:
6
aaabbb

Output: 
2

Input:
10
abccabccab
Output:
6
*/

/*
Pensemos el algoritmo:

Condiciones Iniciales
1. Necesitamos saber el substring que nos resta luego de eliminar repetidos
2. Necesitamos tmb saber cuantas operaciones llevamos
Obtenemos lo siguiente: f(operacion, substring)

Recursion?
Cuando no tenemos que hacer recursion?
Si llegamos al caso base --> |a| == 0, terminamos

Neutros de la operacion
Cuando retornamos los resultados de los casos base, es importante saber qué queremos representar. Estos suelen ser el neutro de la operación que usamos recursivamente. 
En nuestro caso queremos representar la cantidad minima de operaciones necesaria para "borrar" el string a. En ese caso lo que queremos es:
1. Retornar 0 porque ya terminamos de "borrar" todo a.

Firma de la funcion con casos base:
f(operacion, substring) = {0 si |a| = 0}

Definiendo casos recursivos de f
Sabemos que estamos en un momento valido porque ya cubrimos los casos base.
Que estados posibles pueden darse si estamos en un momento i?
1. nos encontramos con un string con x repetidos, x > 1
2. nos encontramos con un string con sólo 1 repetido

Otra forma de ver lo anterior:
1. Si puedo borrar x repetidos -> lo hago
2. Si no, hago recursion hasta que pueda

La funcion nos quedaria:
borrar_substring(operacion + 1, substring) --> Encontramos un substring con todos repetidos (ej "aa")

f(operacion, substring) = {0 si |a| = 0
                          {min(borrar_substring(operacion + 1, substring), f(operacion, substring)) sino

El neutro que utilizaremos para no pisar valores será el Int_Max, pues buscamos la MINIMA cantidad de operaciones. 
*/

//Intentemos implementar un LIS (Longest Increasing Subsequence) estilo de codigo para buscar la mayor # de repetidos seguidos en el string (https://www.youtube.com/watch?v=aPQY__2H3tE&t=837s)
int borrar(int n, string a, int acciones, vector<vector<int>>& memo){
    if (a.size() < 1){
        return acciones;
    }
    if (memo[d][eleccion] != INT_MAX){
        return memo[d][eleccion];
    }

    int l = -1;
    int r = -1;
    int guardo_repes = 1;
    int repetidos = 1;
    
    for (int i = 0; i < a.size(); i++){
        if (a[i] == a[i+1]){
            repetidos++;
        }
        else{
            guardo_repes = repetidos;
            l = i+1 - repetidos;
            r = i;
            repetidos = 1;
        }
    }

    a.erase(a.begin() + l, a.end());
    return borrar(a.size(), a, acciones + 1);
}


int main(){
    
    int n = 10;
    vector<vector<int>> memo(n, vector<int>(n, INT_MAX));
    string a = {"abccabccab"};
    int res = borrar(n, a, 0, memo);
    cout << res;
    return 0; 
}