from primes import *
import pytest

def test_zero():
     with pytest.raises(Exception):
         factors(0)

def test_primes():
    assert(factors(2) == [2])
    assert(factors(17) == [17])
    assert(factors(19) == [19])
    assert(factors(29) == [29])
    assert(factors(59) == [59])
    assert(factors(79) == [79])




def test_nonprimes():
    assert(factors(8) == [2, 2, 2])
    assert(factors(70) == [2, 5, 7])
