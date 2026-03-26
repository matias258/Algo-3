#include <vector>
#include <iostream>
#include <queue>
#include <list>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <cstdio>
using namespace std;

int Montaña(vector<int> a, int i, int j){
    if (i >= j){
        return a[i];
    }
    
    int m = i + (j - i) / 2;

    if (a[m] > a[m-1]){
        return Montaña(a, i + m, j);
    }
    if (a[m] < a[m-1]){
        return Montaña(a, i, j - m);
    }
    return -1;
}

int maxMontaña(vector<int> a){
    if (a.size() == 1){
        return a[0];
    }
    
    return Montaña(a, 0, a.size());
}

int main() {
    cout << "=== Tests para maxMontaña ===\n\n";

    // Test 1: Montaña simple
    vector<int> test1 = {1, 3, 5, 7, 5, 3, 1};
    cout << "Test 1: {1, 3, 5, 7, 5, 3, 1}\n";
    cout << "  Resultado: " << maxMontaña(test1) << "  (esperado: 7)\n\n";

    // Test 2: Pico al inicio (casi incrementando)
    vector<int> test2 = {1, 10, 8, 6, 4, 2};
    cout << "Test 2: {1, 10, 8, 6, 4, 2}\n";
    cout << "  Resultado: " << maxMontaña(test2) << "  (esperado: 10)\n\n";

    // Test 3: Pico al final (casi incrementando)
    vector<int> test3 = {1, 2, 4, 6, 8, 10, 1};
    cout << "Test 3: {1, 2, 4, 6, 8, 10, 1}\n";
    cout << "  Resultado: " << maxMontaña(test3) << "  (esperado: 10)\n\n";

    // Test 4: Un solo elemento
    vector<int> test4 = {42};
    cout << "Test 4: {42}\n";
    cout << "  Resultado: " << maxMontaña(test4) << "  (esperado: 42)\n\n";

    // Test 5: Montaña más grande
    vector<int> test5 = {1, 5, 10, 20, 50, 100, 30, 10, 5, 1};
    cout << "Test 5: {1, 5, 10, 20, 50, 100, 30, 10, 5, 1}\n";
    cout << "  Resultado: " << maxMontaña(test5) << "  (esperado: 100)\n\n";

    // Test 6: Pico en posición impar
    vector<int> test6 = {2, 4, 9, 3, 1};
    cout << "Test 6: {2, 4, 9, 3, 1}\n";
    cout << "  Resultado: " << maxMontaña(test6) << "  (esperado: 9)\n\n";

    return 0;
}