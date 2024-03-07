from roman import *

def test_roman():
    assert roman('III') == 3
    assert roman("XIX") == 19
    assert roman("XX") == 20
    assert roman('XXI') == 21
    assert roman('CDXCIX') == 499
    assert roman('CMXCIX') == 999
    assert roman('MDCCLXXVI') == 1776
    assert roman('MMXIX') == 2019
