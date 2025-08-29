#include <vector>
#include <iostream>
#include <queue>
#include <list>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <cstdio>
#include <tuple>
#include <string>
using namespace std;

/*
Carlos tiene un número x que quiere convertir en y. Tiene dos opciones:

1. multiplicar el número actual por 2 (es decir, reemplazar el número x por 2*x);

2. añadir el dígito 1 a la derecha del número actual (es decir, reemplazar el número x por 10⋅x + 1).

Estas operaciones pueden repetirse múltiples veces.
Carlos te pide ayuda para transformar su número x en el número y, usando únicamente las operaciones descritas anteriormente, o encontrar que es imposible.
Tener en cuenta que en esta tarea no es necesario minimizar el número de operaciones. Alcanza con encontrar cualquier manera de transformar x en y.
*/

/*
Input
La primera línea tiene dos enteros positivos "x" e "y"  —> el número que Carlos tiene y el número que desea obtener.

Output
Si no hay forma de obtener y de x, imprimir el string NO.

De lo contrario, imprimir tres líneas. 
1) En la primera línea, escribir el string YES. 
2) La segunda línea debe tener un solo entero k —> la longitud de la secuencia de transformación. 
3) En la tercera línea, imprimir la secuencia de transformaciones x1,x2,…,xk, donde:

x1 debe ser igual a x,
xk debe ser igual a y,
xi debe obtenerse de xi−1 mediante cualquiera de las dos operaciones descritas (1<i≤k).
*/

// Dice si se puede llegar desde "x" a "y"

/*
bool se_puede(int x, int y){
    if (x == y){
        return true;
    }
    if (x > y){
        return false;
    }

    return se_puede(x * 2, y) || se_puede(10*x + 1, y);
}
*/

vector<int> path;
// vector que devuelve la ruta para llegar desde "x" a "y"
vector<int> camino(int x, int y, vector<int> res){
    if (path.size() > 0){
        return path;
    }

    if (x == y){
        res.push_back(x);
        path = res;
        return res;
    }
    if (x > y){
        return {-1};
    }
    
    res.push_back(x);
    vector<int> izq = camino(x*2, y, res);
    vector<int> der = camino(10*x + 1, y, res);

    if (path.size() > 0){
        return path;
    }
    return {-1};
}

int main(){
    int x, y;

    cin >> x;
    cin >> y;

    string resultado_positivo = "YES";
    string resultado_negativo = "NO";
    vector<int> camino_res = camino(x, y, {});
    int camino_size_res = camino(x, y, {}).size();
    //bool bool_res = se_puede(x, y);

    if (camino_size_res > 1){
        cout << resultado_positivo;
        cout << endl;

        cout << camino_size_res;
        cout << endl;

        for (int i = 0; i < camino_res.size(); i++) {
        cout << camino_res[i]<< " ";
        }
    }
    else{
        cout << resultado_negativo;
    }
    return 0;
}

/*
int main(){
    // Caso 1
    path.clear();
    vector<int> res1 = camino(1, 21, {});
    cout << "Camino de 1 a 21: ";
    for (int v : res1) cout << v << " ";
    cout << "   // Expected: 1 2 21" << endl;

    // Caso 2
    path.clear();
    vector<int> res2 = camino(1, 41, {});
    cout << "Camino de 1 a 41: ";
    for (int v : res2) cout << v << " ";
    cout << "   // Expected: 1 4 41" << endl;

    // Caso 3
    path.clear();
    vector<int> res3 = camino(1, 11, {});
    cout << "Camino de 1 a 11: ";
    for (int v : res3) cout << v << " ";
    cout << "   // Expected: 1 11" << endl;

    // Caso 4 (sin camino válido)
    path.clear();
    vector<int> res4 = camino(1, 1621, {});
    cout << "Camino de 1 a 1621: ";
    for (int v : res4) cout << v << " ";
    cout << "   // Expected: 2 4 8 81 162" << endl;

    // Caso 5
    path.clear();
    vector<int> res5 = camino(2, 162, {});
    cout << "Camino de 2 a 162: ";
    for (int v : res5) cout << v << " ";
    cout << "   // Expected: 2 16 162" << endl;

    // Caso 6
    path.clear();
    vector<int> res6 = camino(1, 82, {});
    cout << "Camino de 2 a 162: ";
    for (int v : res6) cout << v << " ";
    cout << "   // Expected: 1 2 4 41 82" << endl;

    // Caso 7
    path.clear();
    vector<int> res7 = camino(2, 45, {});
    cout << "Camino de 2 a 162: ";
    for (int v : res7) cout << v << " ";
    cout << "   // Expected: -1" << endl;


    return 0;
}
*/

/*
main(){
    bool res = se_puede(1, 82);
    cout << "Se puede llegar de 1 a 82? " << res <<"\n";
    
    bool res2 = se_puede(2, 45);
    cout << "Se puede llegar de 2 a 45? " << res2<<"\n";

    vector<int> res3 = camino(1, 82, {});
    cout << "Camino desde 1 a 82: ";
    for (int v : res3) {
        cout << v << " ";
    }
    cout << endl;


    return 0;
}
*/