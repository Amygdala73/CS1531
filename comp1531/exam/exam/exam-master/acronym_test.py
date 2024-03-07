from acronym import acronym_make

def test_1():
    assert acronym_make(['I am very tired today']) == ['VTT']
