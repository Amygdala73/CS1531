from fibonacci import *
import pytest

def test_case_negative():
    with pytest.raises(ValueError):
        fib(-1)

def test_case_one():
    assert fib(1) == [0]


def test_case_zero():
    assert fib(2) == [0,1]

def test_case_three():
    assert fib(3) == [0,1,1]

def test_case_ten():
    assert fib(10) == [0, 1, 1, 2, 3, 5, 8, 13, 21, 34]

def test_case_eleven():
    assert fib(11) == [0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55]

def test_case_twelve():
    assert fib(12) == [0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89]

def test_case_twenty():
    assert fib(20) == [0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144,
                       233, 377, 610, 987, 1597, 2584, 4181]
