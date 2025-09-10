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
===========================================================
                EJERCICIO 1 - SumaSubconjuntosBT
===========================================================

En este ejercicio vamos a resolver el problema de suma de 
subconjuntos con la técnica de backtracking. 

Dado un multiconjunto C = {c1, ..., cn} de números naturales 
y un natural k, queremos determinar si existe un subconjunto 
de C cuya sumatoria sea k. Vamos a suponer fuertemente que C 
está ordenado de alguna forma arbitraria pero conocida 
(i.e., C está implementado como la secuencia c1, ..., cn o, 
análogamente, tenemos un iterador de C). 

Las soluciones (candidatas) son los vectores a = (a1, ..., an) 
de valores binarios; el subconjunto de C representado por a 
contiene a ci si y sólo si ai = 1. Luego, a es una solución 
válida cuando Σ(ai * ci) = k. Asimismo, una solución parcial 
es un vector p = (a1, ..., ai) de números binarios con 0 ≤ i ≤ n. 
Si i < n, las soluciones sucesoras de p son p ⊕ 0 y p ⊕ 1, 
donde ⊕ indica la concatenación.

-----------------------------------------------------------
PREGUNTAS
-----------------------------------------------------------

a) Escribir el conjunto de soluciones candidatas para C = {6,12,6} y k = 12.

Soluciones Candidatas: Todas las configuraciones posibles que se pueden formar para el problema.
El espacio completo de búsqueda

{6, 12, 6}, {6}, {12}, {6, 12},  {6, 6}, {12, 6}, {Vacio}

b) Escribir el conjunto de soluciones válidas para C = {6,12,6} y k = 12.

Soluciones Válidas: Todo el espacio de búsqueda que cumple lo pedido en el enunciado.
Es decir los conjuntos cuya suma sea = k.

{6, 6}, {12}

c) Escribir el conjunto de soluciones parciales para C = {6,12,6} y k = 12.

Soluciones Parciales: Configuraciones parciales incompletas que representan un estado intermedio en el proceso de construccion de una solucion valida.

donde ejecutariamos esto: SumaSubconjuntosBT(subArr C, suma, k)

Ejemplo: SumaSubconjuntosBT({6, 6}, 12, 12) -->aca estamos a punto de encontrar una solucion.

d) Dibujar el árbol de backtracking correspondiente al algoritmo descrito 
   arriba para C = {6,12,6} y k = 12, indicando claramente la relación 
   entre las distintas componentes del árbol y los conjuntos de los incisos anteriores.

Paja

e) Sea C la familia de todos los multiconjuntos de números naturales. 
   Considerar la siguiente función recursiva ss: 
   C x N → {V, F} (donde N = {0,1,2,...}, V indica verdadero y F indica falso):

   ss({c1,...,cn}, k) = { 
       k = 0                        si n = 0
       ss({c1,...,cn-1}, k) ∨ ss({c1,...,cn-1}, k - cn)   si n > 0
   }

   Convencerse de que ss(C, k) = V si y sólo si el problema de subconjuntos 
   tiene una solución válida para la entrada C, k.

f) Convencerse de que la siguiente es una implementación recursiva de ss 
   en un lenguaje imperativo y de que retorna la solución para C, k en 
   costo O(|C|k). ¿Cuál es su complejidad?

   1) subset_sum(C, i, j); // implementa ss({c1,...,ci}, j)
   2) Si i = 0, retornar (j = 0)
   3) Si no, retornar subset_sum(C, i - 1, j) ∨ subset_sum(C, i - 1, j - C[i])

g) Dibujar el árbol de llamadas recursivas para la entrada C = {6,12,6} y k = 12, 
   y compararlo con el árbol de backtracking.

h) Considerar la siguiente regla de factibilidad: 
   p = (a1, ..., ai) se puede extender a una solución válida sólo si Σ(aj * cj) ≤ k. 
   Convencerse de que la siguiente implementación incluye la regla de factibilidad:

   1) subset_sum(C, i, j); // implementa ss({c1,...,ci}, j)
   2) Si j < 0, retornar falso  // regla de factibilidad
   3) Si i = 0, retornar (j = 0)
   4) Si no, retornar subset_sum(C, i - 1, j) ∨ subset_sum(C, i - 1, j - C[i])

i) Definir otra regla de factibilidad, mostrando que la misma es correcta; 
   no es necesario implementarla.

j) Modificar la implementación para imprimir el subconjunto de C que suma k, 
   si existe. Ayuda: mantenga un vector con la solución parcial p al que se le 
   agregan y sacan los elementos en cada llamada recursiva; tenga en cuenta 
   de no suponer que este vector se copia en cada llamada recursiva, 
   porque cambia la complejidad.

===========================================================
*/


