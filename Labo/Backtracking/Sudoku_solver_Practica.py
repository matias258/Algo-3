
# SUDOKU SOLVER CON BACKTRACKING:
# 1. Inicio: sudoku_solver(0, 0)
# 2. Verifica si ya hay solución y termina si existe.
# 3. Caso base: si i == n, copia el tablero como solución y termina.
# 4. Calcula la siguiente celda (ip, jp).
# 5. Si la celda está vacía:
#    - Obtiene posibles valores.
#    - Para cada valor:
#        - Asigna el valor.
#        - Llama recursivamente.
#        - Si no hay solución, limpia la celda (backtracking).
# 6. Si la celda está ocupada, avanza a la siguiente celda.

def sudoku_solver(i, j):
    global nodos_visitados, solucion, sudoku, n
    nodos_visitados += 1
    if solucion:
        return
    if i == n:
        solucion = [row[:] for row in sudoku]  # Copia la solución
        return
    
    ip = i
    jp = j + 1
    if jp == n:
        ip += 1
        jp = 0

    if sudoku[i][j] == 0:
        s = posibles(i, j)
        for x in s:
            sudoku[i][j] = x
            sudoku_solver(ip, jp)
            if solucion:
                return
            sudoku[i][j] = 0  # Limpia la celda
    else:
        sudoku_solver(ip, jp)

# Casos posibles, en Algo3 la podemos usar ya definida #
def posibles(i, j):
    global sudoku, n
    usados = set()
    # Números usados en la fila
    for col in range(n):
        if sudoku[i][col] != 0:
            usados.add(sudoku[i][col])
    # Números usados en la columna
    for row in range(n):
        if sudoku[row][j] != 0:
            usados.add(sudoku[row][j])
    # Números usados en el bloque 3x3
    bi = (i // 3) * 3   #(//: Division entera)
    bj = (j // 3) * 3
    for row in range(bi, bi + 3):
        for col in range(bj, bj + 3):
            if sudoku[row][col] != 0:
                usados.add(sudoku[row][col])
    # Devuelve los números posibles
    return [num for num in range(1, n + 1) if num not in usados]

################################################################

# Printearlo en la pantalla
def print_grid(grid):
    for row in grid:
        print(" ".join(str(x) for x in row))



if __name__ == "__main__":
    # Inicializa el tablero y variables globales
    sudoku = [
        [3, 0, 6, 5, 0, 8, 4, 0, 0],
        [5, 2, 0, 0, 0, 0, 0, 0, 0],
        [0, 8, 7, 0, 0, 0, 0, 3, 1],
        [0, 0, 3, 0, 1, 0, 0, 8, 0],
        [9, 0, 0, 8, 6, 3, 0, 0, 5],
        [0, 5, 0, 0, 9, 0, 6, 0, 0],
        [1, 3, 0, 0, 0, 0, 2, 5, 0],
        [0, 0, 0, 0, 0, 0, 0, 7, 4],
        [0, 0, 5, 2, 0, 6, 3, 0, 0]
    ]
    n = 9
    nodos_visitados = 0
    solucion = None

    sudoku_solver(0, 0)
    if solucion:
        print_grid(solucion)
    else:
        print("No hay solución")