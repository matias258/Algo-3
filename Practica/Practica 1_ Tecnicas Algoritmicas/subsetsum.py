"""
Let’s consider a more complicated problem, called SS: Given a set X
of positive integers and target integer T, is there a subset of elements in X that
add up to T? Notice that there can be more than one such subset. For example,
if X = {8, 6, 7, 5, 3, 10, 9} and T = 15, the answer is True, because the subsets
{8, 7} and {7, 5, 3} and {6, 9} and {5, 10} all sum to 15. On the other hand, if
X = {11, 6, 5, 1, 7, 13, 12} and T = 15, the answer is False.
"""

def SS(s, T) -> bool:
    if s == [] or T < 0:
        return False
    if T == 0:
        return True
    # Exclude first element or include it
    return SS(s[1:], T) or SS(s[1:], T - s[0])
    # s[1:] Is the set s w/o the 1st element. So its dynamic

print(SS([8, 6, 7, 5, 3, 10, 9], 15))   # True
print(SS([11, 6, 5, 1, 7, 13, 12], 15)) # False


def SS_counter(s, T)->int:
    if s == [] or T < 0:
        return 0
    if T == 0:
        return 1
    # Exclude first element + include it (we want the sum of possibilities that work)
    return SS_counter(s[1:], T) + SS_counter(s[1:], T - s[0])
    # s[1:] Is the set s w/o the 1st element. So its dynamic

print(SS_counter([8, 6, 7, 5, 3, 10, 9], 15))

def SS_results(s, T) -> list[list[int]]:
    if s == [] or T < 0:
        return []
    if T == 0:
        return s
    return SS_results(s[1:], T) or SS_results(s[1:], T - s[0])

print(SS_results([8, 6, 7, 5, 3, 10, 9], 15))