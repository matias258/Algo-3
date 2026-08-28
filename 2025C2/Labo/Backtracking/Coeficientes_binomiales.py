# Coeficientes Binomiales:
# C(n, k) = {
#     1                  si k = 0
#     1                  si k = n
#     C(n-1, k-1) + C(n-1, k)   cc
# }

# Queremos escribir una funcion que me calcule ese numero combinatorio

# La manera en la que lo hariamos para Algebra seria esta
def C(n, k):
    if k > n:
        return 0

    elif k == 0 or k == n: 
        return 1

    return C(n-1, k-1) + C(n-1, k)

# Cada nodo representa una llamada recursiva C(n, k)
# 
# Ejemplo para C(4, 2):
# 
#             C(4,2)
#            /      \
#        C(3,1)    C(3,2)
#       /     \    /     \
#   C(2,0) C(2,1) C(2,1) C(2,2) --> Vemos que hay 2 veces C(2,1)
#    |      / \    / \     |
#    1  C(1,0) C(1,1) C(1,0) C(1,1) 1 --> Tambien con C(1,1), C(1,0)
#        |     |    |     |
#        1     1    1     1
#
# Las hojas del árbol son los casos base donde k == 0 o k == n, y retornan 1.
# El valor final es la suma de todos los caminos válidos según la fórmula recursiva.
# Esta forma es recontra ineficiente
# Por suerte nosotros sabemos Backtracking, hagamoslo mejor:

# Y si vamos guardando los resultados?
# Vamos a guardarlos en una matriz

def C_backtracking(n, k):
    if k > n or n < 0 or k < 0:
        return 0
        print("k must be smaller than n")

    # grid con k columnas y n filas
    # donde tiene C(n,k) en su posicion grid[n][k]
    grid = [[0 for _ in range(k + 1)] for _ in range(n + 1)]
    grid[0][0] = 1    # Pues C(0,0) = 1

    if grid[n-1][k-1] != 0:
        if grid[n-1][k] != 0:
            return grid[n-1][k-1] + grid[n-1][k]
        else:
            return grid[n-1][k-1]
        
    elif k == 0 or k == n: 
        return 1
    
    else:
        grid[n][k] = C_backtracking(n-1, k-1) + C_backtracking(n-1, k)
    
    C_backtracking(n-1, k-1) + C_backtracking(n-1, k)

def run_tests():
    tests = [
        (0, 0, 1),
        (1, 0, 1),
        (1, 1, 1),
        (2, 1, 2),
        (3, 2, 3),
        (4, 2, 6),
        (5, 3, 10),
        (6, 2, 15),
        (10, 5, 252),
        (5, 0, 1),
        (5, 5, 1),
        (5, -1, 0),
        (3, 4, 0),
        (-1, 0, 0),
    ]

    for n, k, expected in tests:
        result = C_backtracking(n, k)
        assert result == expected, f"Error en C_backtracking({n}, {k}): esperado {expected}, pero se obtuvo {result}"
    
    print("✅ Todos los tests pasaron correctamente.")

# Ejecutar los tests
run_tests()