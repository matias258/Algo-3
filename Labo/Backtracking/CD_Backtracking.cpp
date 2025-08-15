#include <vector>
#include <iostream>
using std::vector;
using std::cout;

// Solo calcula res (sin podas ni combinaciones)
void CD_sin_podas(int suma, int i) {
    extern int res, k, n;
    extern vector<int> duracion;
    if (i == n) {
        if (suma <= k && suma > res) {
            res = suma;
        }
        return;
    }
    CD_sin_podas(suma + duracion[i], i + 1);
    CD_sin_podas(suma, i + 1);
}

// Calcula res con dos podas simples
void CD_dos_podas(int suma, int i) {
    extern int res, k, n;
    extern vector<int> duracion;
    if (suma > k) return;
    if (suma <= res) return;
    if (i == n) {
        if (suma > res) {
            res = suma;
        }
        return;
    }
    CD_dos_podas(suma + duracion[i], i + 1);
    CD_dos_podas(suma, i + 1);
}

// Versión final con todas las podas y combinación óptima
int res = 0;
vector<int> duracion;
int n;
int k;
vector<int> sol_parcial;
vector<int> sol_optima;

void CD(int suma, int suma_sufijo, int i) {
    if (suma > k) return; // poda 1
    if (suma + suma_sufijo <= res) return; // poda 2 (más fuerte)
    if (i == n) {
        if (suma > res) {
            res = suma;
            sol_optima = sol_parcial;
        }
        return;
    }
    suma_sufijo -= duracion[i];
    // Tomar el elemento actual
    sol_parcial[i] = 1;
    CD(suma + duracion[i], suma_sufijo, i + 1);
    // No tomar el elemento actual
    sol_parcial[i] = 0;
    CD(suma, suma_sufijo, i + 1);
}

int main() {
    duracion = {2, 4, 5};
    k = 6;
    n = duracion.size();
    sol_parcial.assign(n, 0);
    sol_optima.assign(n, 0);

    int suma_total = 0;
    for (int x : duracion) suma_total += x;

    CD(0, suma_total, 0);

    cout << "Respuesta: " << res << "\n";
    cout << "Combinacion: ";
    for (int i = 0; i < n; ++i) {
        if (sol_optima[i]) cout << duracion[i] << " ";
    }
    cout << "\n";
    return 0;
}