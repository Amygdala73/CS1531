from dictionary import construct_dict

def test_sample():
    l1 = ['a', 'b', 'c']
    l2 = [1, 2, 3]
    assert(construct_dict(l1, l2) == {'a': 1, 'b': 2, 'c': 3})