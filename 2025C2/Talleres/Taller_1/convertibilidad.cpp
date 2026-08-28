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



// vector que devuelve la ruta para llegar desde "x" a "y"
vector<int> path;
vector<int> camino(int x, int y, vector<int>& res){
    if (path.size() != 0){
        return path;
    }
    if (x == y){
        res.push_back(x);
        path = res;
        res.pop_back();
        return path;
    }
    
    if (x > y || (x*2 > y && x*10 + 1 > y)){    // x > y o siguiente x > y
        return {-1};
    }

    if (x*2 <= y && x*10 + 1 > y){              // izq <= y pero der > y
        res.push_back(x);
        vector<int> izq = camino(x*2, y, res);
    }

    else{                                       // izq y der <= y, pues si der < y --> izq < y
        res.push_back(x);
        vector<int> der = camino(10*x + 1, y, res);
        vector<int> izq = camino(x*2, y, res);
    }
 
    if (path.size() > 0){
        return path;
    }
    res.pop_back();
    return {-1};
}

vector<int> path_inverso;
vector<int> camino_inversa(int x, int y, vector<int>& res){
    if (path_inverso.size() != 0){
        return path_inverso;
    }

    if (x == y){
        res.insert(res.begin(), y);
        path_inverso = res;
        res.erase(res.begin());
        return path_inverso;
    }
    if (x > y){
        return {-1};
    }

    // "y" es par entonces solo puede venir de y / 2
    if (y % 2 == 0){
        res.insert(res.begin(), y);
        vector<int> izq = camino_inversa(x, y/2, res);
    }

    // "y" termina en 1 (ejemplo 41), solo puede venir de (y-1) / 10
    else if (y % 10 == 1){   
        res.insert(res.begin(), y);
        vector<int> der = camino_inversa(x, (y-1)/10, res);
    }
    // "y" es impar y no termina en 1 (ejemplo 45), entonces es imposible llegar
    else{
        return {-1};
    }

    if (path_inverso.size() != 0){
        return path_inverso;
    }

    res.erase(res.begin());
    return {-1};
}


int main(){

    int x, y;

    cin >> x;
    cin >> y;

    vector<int> res = {};
    string resultado_positivo = "YES";
    string resultado_negativo = "NO";
    vector<int> camino_res = camino_inversa(x, y, res);
    int camino_size_res = camino_res.size();

    if (camino_size_res != 1){
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
void test_case(int x, int y, const string& expected){
    path_inverso.clear();
    vector<int> res = {};
    vector<int> camino_res = camino_inversa(x, y, res);

    if (camino_res.size() != 1){
        cout << "YES\n";
        cout << camino_res.size() << "\n";
        for (int v : camino_res) cout << v << " ";
        cout << " // Expected: " << expected << "\n";
    } else {
        cout << "NO // Expected: " << expected << "\n";
    }
}

int main(){
    // Casos con camino posible
    test_case(1, 21,  "1 2 21");
    test_case(1, 41,  "1 2 4 41");
    test_case(2, 162, "2 16 162");
    test_case(3, 12,  "3 6 12");
    test_case(7, 71,  "7 71");

    // Casos imposibles
    test_case(2, 45,  "-1");
    test_case(1, 12,  "-1");
    test_case(1, 101, "-1");
    test_case(5, 100, "-1");

    return 0;
}
*/


