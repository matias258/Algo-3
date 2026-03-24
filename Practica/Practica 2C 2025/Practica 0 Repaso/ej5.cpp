#include <cmath>
#include <iostream>

using namespace std;
/*
La poblaci´on de gatos en un dep´osito tiene la propiedad de que el n´umero de gatos en un a˜no es
igual a la suma del n´umero de gatos de los dos a˜nos anteriores. Si en el primer a˜no (empezando
a contar desde 1) hab´ıa un solo gato, y en el segundo dos (suponiendo ello posible!), probar que
el n´umero de gatos en el a˜no n es:
sqrt(1/5) * (((1+sqrt(5))/2)^(n+1) - ((1-sqrt(5))/2)^(n+1)))
*/

/*
Caso Base:
El n de gatos en el año 1 es 1
El n de gatos en el año 2 es 2

Recursion:
El n de gatos en el año 3 es 1 + 2 = 3
El n de gatos en el año 4 es 3 + 2 = 5
El n de gatos en el año 5 es 5 + 3 = 8
etc..
El n de gatos en el año n es f(n-1) + f(n-2)

Veamos por Induccion:
Caso Base:
P(3) -> sqrt(1/5) * (((1+sqrt(5))/2)^(3+1) - ((1-sqrt(5))/2)^(3+1))) = = 3
*/

int gatos_fibonacci(int n){
    if (n == 1) return 1;
    if (n == 2) return 2;
    int n1 = 1;
    int n2 = 2;
    int n3 = 0;
    for (int i = 3; i <= n; i++){
        n3 = n1 + n2;
        n1 = n2;
        n2 = n3;
    }
    return n3;
}

int gatos_fibonacci_ecuacion(int n){
    double a = 1 / sqrt(5);
    double x1 = pow((1+sqrt(5))/2,n+1);
    double x2 = pow((1-sqrt(5))/2,n+1);

    double res = a * (x1-x2);
    return round(res);
}


int main() {
    int n;
    cout << "Ingrese el año n: ";
    cin >> n;
    cout << "Cantidad de gatos en el año " << n << " (recursivo): " << gatos_fibonacci(n) << endl;
    cout << "Cantidad de gatos en el año " << n << " (ecuacion cerrada): " << gatos_fibonacci_ecuacion(n) << endl;
    return 0;
}