from reduce import reduce
import pytest

def test_none():
    def f():
        return 0
    assert reduce(f, []) == None

def test_one():
    def f():
        return 0
    assert reduce(f, [1]) == 1
    assert reduce(f, [3]) == 3
    assert reduce(f, ['xs']) == 'xs'
    
def test_two():
    def f(xs,xxs):
        return xs+xxs
    assert reduce(f, [1,2]) == 3
    assert reduce(f, [3,4]) == 7
    assert reduce(f, ['xs','sx']) == 'xssx'

    
def test_three():
    def f(xs,xxs):
        return xs+xxs
    assert reduce(f, [1,2,3]) == 6
    assert reduce(f, [3,4,5]) == 12
    assert reduce(f, ['xs','sx','xs']) == 'xssxxs'
    assert reduce(lambda x, y: x + y, [1,2,3,4,5]) == 15
    assert reduce(lambda x, y: x + y, 'abcdefg')   == 'abcdefg'
    assert reduce(lambda x, y: x * y, [1,2,3,4,5]) == 120

def test_more_mul():
    def f(xs,xxs):
        return xs*xxs
    assert reduce(f, [1,2,3,4]) == 24
    assert reduce(f, [3,4,5]) == 60

