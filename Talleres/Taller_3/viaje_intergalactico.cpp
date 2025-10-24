#include <list>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <cstdio>
#include <algorithm>
#include <bits/stdc++.h>
#include <utility>
#include <math.h>

#include <iostream>
#include <vector>
#include <tuple>
#include <stack>
#include <queue>

using namespace std;




int main() {
    // Optimización de I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // 1. Lectura de parámetros n y m
    int n, m;
    if (!(cin >> n >> m)) return 1;

    // 2. Lectura de las m conexiones (a, b, c)
    // Usamos (n+1) para las listas de adyacencia si queremos modelar el grafo, 
    // pero para la impresión de las m líneas basta con vectores de tamaño m.
    vector<int> a(m), b(m), c(m);
    
    for (int i = 0; i < m; i++) {
        // Lee a, b, c. Si el input original solo diera a y b, y no c, 
        // tendrías que cambiar la lógica de lectura aquí.
        if (!(cin >> a[i] >> b[i] >> c[i])) return 1;
    }

    // 3. Lectura de los Viajeros (Restricciones)
    // El problema usa índices base 1 (Planeta 1 a n).
    // Usaremos tamaño n para k y t, donde el Planeta i+1 está en el índice i.
    vector<int> k(n);            // k[i] es el número de viajeros para el Planeta i+1
    vector<vector<int>> t(n);    // t[i] son los tiempos para el Planeta i+1

    for (int i = 0; i < n; i++) {
        // La PRIMERA LECTURA es k[i]
        if (!(cin >> k[i])) return 1; 

        // La siguiente lectura son k[i] tiempos tj
        t[i].resize(k[i]);
        for (int j = 0; j < k[i]; j++) {
            if (!(cin >> t[i][j])) return 1; 
        }
    }

    // --- Generación de la Salida Detallada ---

    cout << "--- Analisis de la Entrada del Problema ---" << endl;
    cout << "------------------------------------------" << endl;

    // A. Parametros Generales
    cout << "A. Parametros Generales:" << endl;
    cout << "   - N (Planetas): " << n << endl;
    cout << "   - M (Portales/Conexiones): " << m << endl;
    cout << endl;

    // B. Conexiones (Portales)
    cout << "B. Conexiones (Portales):" << endl;
    cout << "   ID | Planeta A | Planeta B | Tiempo C (Segundos)" << endl;
    cout << "---------------------------------------------------" << endl;
    for (int i = 0; i < m; i++) {
        cout << "  " << i + 1 << " |     " << a[i] << "     |     " << b[i] << "     |       " << c[i] << endl;
    }
    cout << endl;

    // C. Restricciones de Llegada (Otros Viajeros)
    cout << "C. Restricciones de Llegada (Otros Viajeros):" << endl;
    cout << "   Planeta | k (#Viajeros) | Tiempos de Llegada (t_ij) | Restriccion de Salida (t_ij - 1)" << endl;
    cout << "-------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < n; i++) {
        // Formato de Tiempos de Llegada
        stringstream ss_llegada;
        stringstream ss_salida;
        bool has_restrictions = false;
        
        for (int j = 0; j < k[i]; j++) {
            ss_llegada << t[i][j] << " ";
            ss_salida << t[i][j] - 1 << " ";
            has_restrictions = true;
        }

        cout << "    " << i + 1 << "    |      " << k[i] << "      | " 
             << (has_restrictions ? ss_llegada.str() : "N/A") << (has_restrictions ? "" : " ")
             << " | ";

        if (has_restrictions) {
            cout << "(NO salir en: " << ss_salida.str() << ")";
        } else {
            cout << "Ninguna";
        }
        cout << endl;
    }
    cout << "-------------------------------------------------------------------------------------" << endl;
    
    return 0;
}