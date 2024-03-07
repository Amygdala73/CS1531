import math

def magic(square):
    
    size = len(square)
    result = None

    for i in square:
        if sum(i) != size * (size**2 +1)//2:
            return 'Not a magic square'
        
    for j in range(size):
        col_sum = 0 
        for row in square:
            col_sum = col_sum + row[j] 
        if col_sum != size * (size**2 +1)//2:
            return 'Not a magic square'
        
    for k in range(size):
        if size != len(set(square[k])):
            return 'Invalid data: missing or repeated number'
        

    sum_r = 0
    sum_l = 0
    for y in range(size):
        sum_r = sum_r + square[i][i]
        sum_l = sum_l + square[size-1-i][i]
        print((size-1-y,y))
        
    if sum_r != size * (size**2 +1)//2 or sum_l != size * (size**2 +1)//2:
        return 'Not a magic square'  
    
    result = 'Magic square'
    return result
