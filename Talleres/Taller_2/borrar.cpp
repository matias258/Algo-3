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

Funcion matematica de recurrencia:

f(count, s) =   { count                     , si |s| < 1
                { f(count + 1, borrar(s))   , si |s| >= 1

Donde   count       -> int que suma la cantidad de operaciones
        s           -> string en donde vamos a borrar los chars repetidos
        borrar(s)   -> funcion que borra chars de s y devuelve un substring de s sin esos chars

Neutros de la operacion

El neutro que utilizaremos para no pisar valores será el Int_Max, pues buscamos la MINIMA cantidad de operaciones. 
*/

//Intentemos implementar un LIS (Longest Increasing Subsequence) estilo de codigo para buscar la mayor # de repetidos seguidos en el string (https://www.youtube.com/watch?v=aPQY__2H3tE&t=837s)
string borrar(string s){

}

int funcion(int n, string s, int count){
    // Caso base: |s| == 0
    if (s.size() <= 0){
        return count;
    }
    else{
        funcion(n, borrar(s), count + 1);
    }

    // retornamos el minimo entre el count y borrar
    return min(count, funcion(n, borrar(s), count + 1));
    
}



int main(){
    
    
    string a = {"abccabccab"};
    int n = a.size();
    vector<vector<int>> memo(n, vector<int>(n, INT_MAX));
    int res = funcion(n, a, 0);
    cout << res;
    return 0; 
}