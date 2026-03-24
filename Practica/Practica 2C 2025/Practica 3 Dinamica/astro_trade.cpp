#include <vector>
#include <iostream>
#include <queue>
#include <list>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <cstdio>
using namespace std;

/*
Lu se dedica a la compra de asteroides. Sea p ∈ N^n tal que p_i es el precio de un asteroide el i-ésimo día en una secuencia de n días. Lu quiere comprar y vender asteroides durante esos n días de manera tal de obtener la mayor ganancia neta posible.
Debido a las dificultades que existen en el transporte y almacenamiento de asteroides, Lu puede comprar a lo sumo un asteroide cada día, puede vender a lo sumo un asteroide cada día y comienza sin asteroides. Además, el Ente Regulador Asteroidal impide que Lu venda un asteroide que no haya comprado. Queremos encontrar la máxima ganancia neta que puede obtener Lu respetando las restricciones indicadas. Por ejemplo, si p = (3, 2, 5, 6) el resultado es 6 y si p = (3, 6, 10) el resultado es 7. Notar que en una solución óptima, Lu debe terminar sin asteroides.
*/


/*
1. Encontrar los casos base y los pasos recursivos para calcular la máxima ganancia neta (m.g.n.) que puede obtener Lu.

    Casos Base y Pasos Recursivos
a) Los parametros de la funcion van a ser a: asteroides, d: dias
b) La semantica va a ser:
    astro_trade(a,d) = max ganancia neta que puede obtener Lu si tiene a asteroides al final del dia d.
    astro_trade(0, |p|) = Llamado recursivo que resuelva nuestro problema.

    Casos Base 
a) Si mi dia > n --> terminé el recorrido --> astro_trade es 0
b) Si tenemos mas asteroides que dias --> No vamos a poder vender todos --> Solucion no válida
c) Si vendemos un asteroide cuando no teniamos ninguno --> rompemos la restriccion --> inválido

    Pasos recursivos
a) El maximo entre:
    - astro_trade de finalizar el dia d-1 con a-1 asteroides y comprar uno en el dia d
    - astro_trade de finalizar el dia d-1 con a+1 asteroides y vender uno en el dia d
    - astro_trade de finalizar el dia d-1 con a asteroides y no hacer nada en el dia d

2. Escribir matemáticamente la formulación recursiva enunciada en el primer punto. Dar los valores de los casos base en función de la restricción de que comienza sin asteroides.

Viendo el paso recursivo recien generado podemos escribir matematicamente la formulacion recursiva:
                    {d = 0 --> return 0
                    {a < 0 --> return -inf              // usamos -inf en valores que queremos 
                    {a > d --> return -inf              // que nunca sean seleccionados
astro_trade(a, d) = {else --> return max( astro_trade(a+1, d+1), 
                                          astro_trade(a-1, d+1), 
                                          astro_trade(a, d+1))

3. Indicar qué dato es la respuesta al problema con esa formulación recursiva.
En a ultima llamada recursiva vamos a terminar teniendo 0 asteroides (por enunciado) y en el ultimo dia (es decir p.size())
Por lo que la ultima recursion (y la rta final) sera: astro_trade(0, |p|)
Entonces astro_trade(0, |p|) = max ganancia neta que puede obtener Lu
*/


/*
4. Diseñar un algoritmo de PD top-down que resuelva el problema. Explicar su complejidad temporal y espacial auxiliar. Decidir si se cumple la propiedad de superposición de subproblemas.
*/
int NEG = -1e9;
int astro_trade(int a, int d, vector<int> p){
    if (d == p.size()){
        if (a == 0) return 0;
        else return NEG;
    }
    if (a > p.size() - d || a < 0) return NEG; // inválido
    int nada   = astro_trade(a, d+1, p);
    int compro = NEG;
    if (a < p.size() - d){
        compro = astro_trade(a+1, d+1, p) - p[d];
    }
    int vendo  = NEG;
    if (a > 0){
        vendo = astro_trade(a-1, d+1, p) + p[d];
    }
    // Una vez que vi todos los casos del día d, guardo el más óptimo en memo, repito
    int maximo = max(nada, max(compro, vendo));
    return maximo;
}
/*
Veamos por Dinamica
*/

int Neg = -1e9;
int astro_trade_din(int a, int d, vector<int>& p, vector<vector<int>>& memo) {
    if (d == p.size()){
        if (a == 0) return 0;
        else return Neg;
    }
    if (a > p.size() - d || a < 0) return Neg; // inválido
    if (memo[d][a] != Neg) return memo[d][a];
    int nada   = astro_trade_din(a, d+1, p, memo);
    int compro = Neg;
    if (a < p.size() - d){
        compro = astro_trade_din(a+1, d+1, p, memo) - p[d];
    }
    int vendo  = Neg;
    if (a > 0){
        vendo = astro_trade_din(a-1, d+1, p, memo) + p[d];
    }
    // Una vez que vi todos los casos del día d, guardo el más óptimo en memo, repito
    memo[d][a] = max(nada, max(compro, vendo));
    return memo[d][a];
}

int main(){
    vector<int> precios = {3, 2, 5, 6};
    vector<vector<int>> memo(precios.size()+1, vector<int>(precios.size()+1, Neg));
    int res = astro_trade_din(0, 0, precios, memo);
    int res2 = astro_trade(0, 0, precios);
    cout << res << endl; 
    
    for (int i = 0; i < memo.size(); ++i) {
        for (int j = 0; j < memo[i].size(); ++j) {
            if (memo[i][j] == Neg)
                cout << "N ";
            else
                cout << memo[i][j] << " "; // i is the row (day d), j is the column (asteroids a)
        }
        cout << endl;
    }
    cout << "Por backtracking" << endl;
    cout << res2 << endl;
    return 0;
}

/*
res: 6

Memo:
6 N N N N
4 9 N N N
1 6 11 N N
0 6 N N N
N N N N N

ej: memo[0][0] = 6 
significa que la mayor ganancia desde dia = 0, asteroide = 0 que puedo tener es 6.
Ademas es la ultima ejecucion, es decir que desde aca obtenemos el mejor resultado (pues ya pasamos por todos los otros).

memo[2][2] = 11
significa que la meyor ganancia desde dia = 2, asteroide = 2 que puedo tener es 11
Pero no toma en cuenta los dias anteriores, por lo que no toma en cuenta cuanto nos costó comprarlos.
En este caso -3 y -2, con lo que nos quedaria 11 -5 = 6. Es por eso que nuestro valor max no es 11 sino 6.
*/

/*
Calculemos la complejidad.
Astro_trade normal:
1. Complejidad espacial: n = |p|, el resto usa espacio O(1) --> O(n)
2. Complejidad temporal: Como maximo, 3 llamadas recursivas --> T(n) = 3T(n-1) + O(1) (operaciones ctes)
Entonces:
T(n) = 3T(n-1) = 3(3T(n-2)) = ... = 3^(n-1)
O(n) = 3^n

Ahora las de astro_trade_dinamica:
1. Complejidad espacial: memo = matriz n x n --> O(n^2), el resto a lo sumo es O(n)
Luego O(n^2 + n) = O(n^2)
2. Complejidad temporal: Como memo nos ayuda a calcular en O(1) las recurrencias repetidas, es importante preguntarse lo siguiente --> ¿Cuántos estados únicos hay?
Los días van de 0 a n --> existen n días
Los asteroides van de 0 a n --> existen n asteroides
Luego las combinaciones únicas son n x n --> n^2
Entonces es O(n^2)
Como ademas siempre rellenamos la matriz en peor mejor y caso promedio, entonces 
O(n^2) = Tita(n^2) = Omega(n^2)
Por lo tanto, astro_trade_din es tambien Omega(n^2)
 ----------------------------------------------------------------------
| Algoritmo             |Complejidad Temporal | Complejidad Espacial |
|-----------------------|---------------------|----------------------|
| Backtracking (recurs) |    O(3^n)           |    O(n)              |
| DP Top-Down (memo)    |    Omega(n^2)       |    O(n^2)            |

Luego astro_trade_din es mas rapida en tiempo que astro_trade por backtracking, pues
para todo n > 1, n^2 < 3^n
*/