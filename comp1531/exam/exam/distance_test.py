from distance import longest_distance
import pytest


def test_sample():
    assert(longest_distance([1,2,3,2,4]) == 2)
