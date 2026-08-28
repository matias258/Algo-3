#include <vector>
#include <iostream>
#include <queue>
#include <list>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <cstdio>
using namespace std;
#include <tuple>




tuple<int, int> busqueda(vector<int> a, int l, int r, int maximum, int minimum){
    if (l == r){
        return make_tuple(a[l], a[l]);
    }

    int medio = (l + r) / 2;

    if (maximum < a[medio]){
        maximum = a[medio];
    }
    if (minimum > a[medio]){
        minimum = a[medio];
    }   

    tuple<int, int> a_izq = busqueda(a, l, medio, maximum, minimum);
    tuple<int, int> a_der = busqueda(a, medio + 1, r, maximum, minimum);

    int maximo = std::max(get<0>(a_izq), get<0>(a_der));
    int minimo = std::min(get<1>(a_izq), get<1>(a_der));

    return make_tuple(maximo, minimo);
}

int main() {
    vector<int> valores = {3, 1, 4, 1, 5, 9, 2, 6, 5};
    int l = 0;
    int r = valores.size() - 1;
    int max_inicial = valores[0];
    int min_inicial = valores[0];

    auto resultado = busqueda(valores, l, r, max_inicial, min_inicial);

    cout << "Maximo: " << get<0>(resultado) << endl;
    cout << "Minimo: " << get<1>(resultado) << endl;

    return 0;
}