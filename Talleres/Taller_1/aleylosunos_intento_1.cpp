#include <vector>
#include <iostream>
#include <queue>
#include <list>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <cstdio>
using namespace std;
 
// n = numero
// l, r = rango de la r (osea un i j)
// dado n, vamos a querer descomponerlo en 3 valores:
// 1. n/2; 
// 2. n mod 2; 
// 3. n/2;
// Repetimos con los nuevos valores (1.,2.,3.) hasta obtener 1s y 0s
// Contamos cuantos 1s hay en la última iteración, dentro del rango l r
vector<int> last_row(int n){
    if (n < 2){
        return {n};
    }
 
    int x1 = n/2;
    int x2 = n % 2;
    int x3 = n/2;
 
    vector<int> izq = last_row(x1);
    vector<int> med = last_row(x2);
    vector<int> der = last_row(x3);
 
    vector<int> mergeados;
    
    mergeados.insert(end(mergeados), begin(izq), end(izq)); // concateno izquierda
    mergeados.insert(end(mergeados), begin(med), end(med)); // concateno medio
    mergeados.insert(end(mergeados), begin(der), end(der)); // concateno derecha
 
    return mergeados;
 
}
 
int aleylosuno(int n, int l, int r){
    int sum = 0;
    vector<int> row = last_row(n);
    for (int i = l - 1; i < r; i++){
        sum += row[i];
    }
    return sum;
}
 
int main(){
    int n, l, r;
    cin >> n;
    cin >> l;
    cin >> r;
    cout << aleylosuno(n, l, r);
    return 0;
}