class Solution:
    def exist(self, board: List[List[str]], word: str) -> bool:
        row, column = len(board), len(board[0])
        camino = set()

        # Quiero ir recorriendo r y c hasta llegar al i = tamaño de la palabra
        def dfs(r, c, i):
            # Si i llega al tamaño de la palabra ganamos
            if (i == len(word)):
                return True
            

            # Que posiciones no puedo hacer?
            # 1. Si vuelvo a repetir la posicion
            # 2. Si no tengo mas row disponible
            # 3. Si no tengo mas columna disponible
            # 4. Si la letra elegida no es correcta
            if (
                (r, c) in camino or
                r < 0 or r >= row or
                c < 0 or c >= column or
                board[r][c] != word[i]
            ):
                return False

            camino.add((r, c)) # agrego el camino encontrado
            #Me sigo moviendo
            res = (
                dfs(r+1, c, i+1) or
                dfs(r-1, c, i+1) or
                dfs(r, c+1, i+1) or
                dfs(r, c-1, i+1) 
            )
            camino.remove((r, c)) # Si no encuentro camino elimino y elijo otro

            return res # Me devuelve True si encontró un camino

        # Pero dfs comienza desde 1 camino, por lo que tenemos que iterar toda la tabla y decirle que pruebe con cada letra hasta que el dfs dé True, sino False.
        for r in range(row):
            for c in range(column):
                if dfs(r, c, 0): return True
        return False