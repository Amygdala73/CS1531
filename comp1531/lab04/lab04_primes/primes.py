import math

def factors(num):
    '''
    Returns a list containing the prime factors of 'num'. The primes should be
    listed in ascending order.

    For example:
    >>> factors(16)
    [2, 2, 2, 2]
    >>> factors(21)
    [3, 7]
    '''
    if num < 1:
        raise Exception("Invalid input.")
    prime_factors = []
    i = 2
    while i*i <= num:
        if num % i:
            i += 1
        else:
            num //= i
            prime_factors.append(i)
    if num > 1:
        prime_factors.append(num)
    return prime_factors
