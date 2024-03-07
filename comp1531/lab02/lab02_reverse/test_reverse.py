'''
Tests for reverse_words()
'''
from reverse import reverse_words

def test_example0():
    assert reverse_words(["Hello World", "I am here"]) == ['World Hello', 'here am I']

def test_example1():
    assert reverse_words(["1 2 3", "4 5 6"]) == ["3 2 1", "6 5 4"]

def test_example2():
    assert reverse_words(['1', '2', '3']) == ['1', '2', '3']

def test_example3():
    assert reverse_words([]) == []

def test_example3():
    assert reverse_words(["a b c"]) == ["c b a"]

def test_example4():
    assert reverse_words(["a 1 b 2 c 3"]) == ["3 c 2 b 1 a"]
