from list_exercises import reverse_list, minimum, sum_list, average, maximum

def test_reverse():
    l = ["how", "are", "you"]
    reverse_list(l)
    assert l == ["you", "are", "how"]

def test_min_positive():
    assert minimum([1, 2, 3, 10]) == 1

def test_sum_positive():
    assert sum_list([7, 7, 7]) == 21
    
'''At least two more assert statements'''
    
    
def test_average_postive():
    assert average([7, 7, 7])== 7

def test_max_positive():
    assert maximum([1, 2, 3, 10]) == 10
