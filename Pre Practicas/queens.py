"""
Recursively places queens on an n x n chessboard such that no two queens threaten each other.

Parameters:
Q (list): A list where the index represents the row and the value at that index represents the column of the queen.
n (int): The size of the chessboard (n x n).
r (int): The current row being processed.

Behavior:
Prints all valid configurations of queens on the chessboard.
"""
def place_Queens(Q, n, r):
 
    if r == n:
        print(Q)
    else:
        for j in range(1, n+1):
            legal = True
            for i in range (1, r):
                if (Q[i] == j 
                    or Q[i] == j + r - i
                    or Q[i] == j - r + i):
                    legal = False
            if legal:
                Q[r] = j
                place_Queens(Q, n, r+1)

place_Queens([0, 0, 0, 0, 0], 5, 1)

# [0, 4, 1, 3, 5]
# This list likely represents a solution to the N-Queens problem for a 5x5 chessboard.
# Each index is a row, and the value at each index is the column where a queen is placed.
# For example, row 0 has a queen at column 0, row 1 at column 4, and so on.
# No two queens attack each other in this arrangement.