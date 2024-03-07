def reduce(f, xs):
    if not xs:    #if xs is [] doesnt work?
        return None
    elif len(xs) == 1:
        return xs[0]
    else:
        return f(reduce(f, xs[:-1]), xs[-1])    
    

if __name__ == '__main__':
    print(reduce(lambda x, y: x + y, [1,2,3,4,5]))
    print(reduce(lambda x, y: x * y, [1,2,3,4,5]))
