from unpickle import most_common
import pytest

def test_correct():
    assert most_common() == {'Colour': 'red', 'Shape': 'pentagon'}
