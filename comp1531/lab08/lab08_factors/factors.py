from math import sqrt
def divisors(n):
    if type(n) is not int or n <= 0:
      	raise ValueError("Invalid input")
    result = {n}
    i = 1
    
    while i < sqrt(n)+1:
        if n % i == 0:
            result.add(i)
            result.add(n//i)
        i += 1
    return result

# You may find this helpful
def is_prime(n):
    return n != 1 and divisors(n) == {1, n}

def factors(n):
    '''
    A function that generates the prime factors of n. For example
    >>> factors(12)
    [2,2,3]

    Params:
      n (int): The operand

    Returns:
      List (int): All the prime factors of n in ascending order.

    Raises:
      ValueError: When n is <= 1.
    '''
    if type(n) is not int or n <= 1:
      	raise ValueError(f"{n} has not prime factor")
    for i in sorted(divisors(n)):
        if n == 1:
            break
        if is_prime(i):
            while n != 1 and n % i == 0:
                yield i
                n = n // i
