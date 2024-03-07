fib_list =[]
fib_list.append(0)
fib_list.append(1)  
for i in range(2,10):
    fib_list.append(fib_list[i-1]+fib_list[i-2])

        
def fib(n):
    if n < 1:
        raise ValueError ("Invalid input")
    if n <= len(fib_list):
        return fib_list[0:n]
    elif n > len(fib_list):
        print(n)   
        for i in range(len(fib_list),n):
            fib_list.append(fib_list[i-1]+fib_list[i-2])
        return fib_list[0:n]


