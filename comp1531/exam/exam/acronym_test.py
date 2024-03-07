from acronym import acronym_make
import pytest

def test_1():
    assert acronym_make(['I am very tired today']) == ['VTT']

def test_2():   
    assert acronym_make(['Why didnt I study for this exam more', 'I dont know']) == ['WDSFTM', 'DK']

def test_3():
    assert acronym_make(['I am an elephant']) == ['']

def test_4():
    assert acronym_make(['we wd we wd we wd we wd we wd we wd we wd wd we wd']) == ['N/A']
    
def test_5():
    with pytest.raises(ValueError):
        acronym_make([])
