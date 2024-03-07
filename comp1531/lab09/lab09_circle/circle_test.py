from circle import Circle


def test_small():
    c = Circle(3)
    assert(round(c.circumference(), 1) == 18.8)
    assert(round(c.area(), 1) == 28.3)

def test_big():
    c = Circle(1000)
    assert(round(c.circumference(), 1) == 6283.2)
    assert(round(c.area(), 1) == 3141592.7)    
