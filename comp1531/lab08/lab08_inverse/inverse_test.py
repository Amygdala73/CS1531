from inverse import inverse
from hypothesis import given, strategies

def test_empty():
    assert inverse({}) == {}

def test_empty_items():
    assert inverse({1: ' ', 2: 'B', 3: 'A'}) == {' ': [1], 'B': [2], 'A': [3]}

def test_case_1():
    assert inverse({1: 'A', 2: 'B', 3: 'A'}) == {'A': [1, 3], 'B': [2]}

