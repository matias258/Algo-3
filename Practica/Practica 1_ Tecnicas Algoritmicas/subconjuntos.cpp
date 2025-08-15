#include <iostream>
#include <vector>
using namespace std ;
/*
Suma de Subconjuntos

Dado un conjunto de números enteros S = s1, s2, . . . , sn y un número objetivo T,
queremos saber si existe un subconjunto de S cuya suma sea exactamente T.
Ejemplo:
S = {3, 34, 4, 12, 5, 2}, T = 9
¿Existe un subconjunto cuya suma sea 9?
Sí: {4, 5} o {3, 2, 4}
Podemos resolverlo probando todas las combinaciones posibles.
*/

/*
1) Estado:
Definimos un estado dp[i][t] como:
¿Es posible formar la suma t usando los primeros i elementos del conjunto?
2) Caso base:
dp[0][0] = true: con 0 elementos, la única suma posible es 0.
dp[0][t] = false para t > 0: no se puede formar ninguna suma positiva sin elementos.
3) Caso recursivo:
O no lo usás, y entonces tu problema es el mismo que (i − 1, t).
O sí lo usás, y entonces debés haber formado previamente (i − 1, t − si).
4) Transición:
Para cada elemento s_i:
Si no lo tomamos: 
dp[i][t] = dp[i − 1][t]
Si lo tomamos y t ≥ s_i: 
dp[i][t] = dp[i − 1][t − s_i]


1 Orden topológico:
Los nodos se pueden ordenar por i y t crecientes.
En el algoritmo iterativo (bottom-up), los visitamos de forma natural en orden
topológico.
2 DAG:
Cada nodo (i, t) depende de:
(i − 1, t) (si no tomamos si)
(i − 1, t − si) (si lo tomamos)
No hay ciclos porque siempre vamos hacia índices y sumas menores.
*/

// Implementación (top-down) en C++:
vector<vector<int>> memo; // −1: no calculado , 0: false , 1: true

bool subset_sum_topdown (const vector <int >& S, int i , int t) {
if(t == 0) return true ;
if(i == 0) return false ;
if(memo[i][t] != 1) return memo[i][t] ;

bool res = subset_sum_topdown(S, i-1, t);
if(t >= S[i-1])
res = res || subset_sum_topdown (S, i - 1 , t - S[i - 1] ) ;
return memo[ i ] [ t ] = res ;
}
/*
int main() {
vector<int> S = {3 , 34, 4, 12, 5, 2} ;
int T = 9;
memo.assign(S.size() + 1 , vector <int>(T + 1, -1));
cout << ( subset_sum_topdown (S, S.size(), T) ? " Si " : "No" )
<<"hay subconjunto con suma " << T << endl;
}
*/

/* Implementacion (bottom up)*/

bool subset_sum(const vector<int>& S, int T) {
	int n = S.size();
	vector<vector<bool>> dp(n + 1, vector<bool>(T + 1, false));
	dp[0][0] = true; // caso base
	for (int i = 1; i <= n; ++i) {
		for (int t = 0; t <= T; ++t) {
			dp[i][t] = dp[i - 1][t]; // no tomar
			if (t >= S[i - 1]) // tomar
				dp[i][t] = dp[i][t] || dp[i - 1][t - S[i - 1]];
		}
	}
	return dp[n][T];
}

int main() {
	vector<int> S = {3, 34, 4, 12, 5, 2};
	int T = 9;
	cout << (subset_sum(S, T) ? "Si " : "No ")
		 << "hay subconjunto con suma " << T << endl;
}
