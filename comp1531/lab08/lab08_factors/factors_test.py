from factors import factors, is_prime
from hypothesis import given, strategies


def test_primes():
    assert list(factors(7)) == [7]
    assert list(factors(23)) == [23]
    assert list(factors(79)) == [79]

def test_odds():
    assert list(factors(8)) == [2,2,2]
    assert list(factors(24)) == [2,2,2,3]
    assert list(factors(46)) == [2,23]
