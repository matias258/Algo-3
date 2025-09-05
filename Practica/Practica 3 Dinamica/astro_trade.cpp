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



5. Formalmente, el problema consiste en determinar el máximo g = Sum(i=1, n, xipi) para un vector 
x = (x_1, . . . , x_n) tal que: x_i ∈ {−1, 0, 1} para todo 1 ≤ i ≤ n y Sum(i=1, j, x_i <= 0) para todo 
1 ≤ j ≤ n. Demostrar que la formulación recursiva es correcta.
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


int astro_trade(int a, int d, vector<int> p){
    if (d == p.size()){     // Terminé el recorrido 
        return 0;
    }
    if (a > p.size() - d || a < 0){    // tengo mas asteroides que dias --> no es solucion
        return -1e9;     // tengo -1 asteroides? wtf hermano --> no es solucion
    }

    int compro = astro_trade(a+1, d+1, p) - p[d];
    int vendo = astro_trade(a-1, d+1, p) + p[d];
    int nada = astro_trade(a, d+1, p);

    return max(compro, max(vendo, nada));
    
}

int astro_trade_dinamica(int a, int d, vector<int> p, vector<int>& memo){
    
}


/*
astro_trade(0, 0, {3, 2, 5, 6}) devuelve 9 cuando deberia volver 6
Por que pasa esto?
Porque el programa se "olvida" que vendió en cierto día y combina mal los resultados parciales
Para combatir esto, es necesario implementar memoizacion, una memoria que se acuerde de estas operaciones
*/

int main(){
    vector<int> precios = {3, 2, 5, 6};
    vector<int> memo(precios.size(), 0);
    int res = astro_trade(0, 0, precios);
    cout << res;
    return 0;
}