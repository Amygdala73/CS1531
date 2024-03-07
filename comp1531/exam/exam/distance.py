def longest_distance(elements):
    dist = 0
    for x in elements:
        later = elements[elements.index(x)+1:]
        print(later)
        for y in later:
            if y == x:
                print(elements.index(y))
                temp = elements.index(y) - elements.index(x)
                if temp > dist:
                    dist = temp
    return dist
