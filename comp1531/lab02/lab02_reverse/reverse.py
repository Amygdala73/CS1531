def reverse_words(string_list):
    '''
    Given a list of strings, return a new list where the order of the words is
    reversed
    '''
    reversed = []
    for i in string_list:
        temp = i.split()
        temp.reverse()
        reversed.append(" ".join(temp))
    return reversed


if __name__ == "__main__":
    print(reverse_words(["Hello World", "I am here"]))
    # it should print ['World Hello', 'here am I']
