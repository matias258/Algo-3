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
------------------------------------------------------------
Problema: MaxiSubconjunto
------------------------------------------------------------

Dada una matriz simétrica M de n × n números naturales y un 
número k, queremos encontrar un subconjunto I de {1,...,n} 
con |I| = k que maximice:

        ∑ M[i][j]   con i, j ∈ I

Ejemplo:
---------
Si k = 3 y

    M = ( 0  10  10  1
          -   0   5  2
          -   -   0  1
          -   -   -  0 ),

entonces I = {1, 2, 3} es una solución óptima.

Tareas:
--------
a) Diseñar un algoritmo de backtracking para resolver el problema,
   indicando claramente:
   - cómo se codifica una solución candidata,
   - cuáles soluciones son válidas y qué valor tienen,
   - qué es una solución parcial y cómo se extiende cada una.

maximoSubconjunto 
Toma una matriz M, los indices i, j, un numero k = I.size()
Devuelve un conjunto I de tamaño k que maximiza Sum(i,j∈I, M_ij)

Pensemos primero una funcion recursiva:
                            {   si i, j = n-1 --> 0
maximoSubconj(M, i, j, k) = {   si i, j < n-1 --> maximoSubconj(M, i, j, k)
                            {

                    { valor de S    , si i > n y faltan = 0
f(i, faltan, S) =   { -inf          , si i > n y faltan != 0
                    { max(f(i+1, faltan, S), f(i+1, faltan-1, S u {i})) , si i <= n

b) Calcular la complejidad temporal y espacial del algoritmo.

c) Proponer una poda por optimalidad y mostrar que es correcta.
------------------------------------------------------------
*/
