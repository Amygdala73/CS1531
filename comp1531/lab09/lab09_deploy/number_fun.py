import typing

def multiply_by_two(number: (int, float)):
    number = int(number)
    return number * 2

def print_message(message: str):
    print(message)

def sum_list_of_numbers(numbers: (list, int, float)):
    sl = 0
    for i in range(len(numbers)):
        numbers[i] = int(numbers[i])
        sl += numbers[i]
        i += 1
    return sl

def sum_iterable_of_numbers(numbers: (list, dict, tuple, int, float)):
    si = 0
    if len(numbers) == 1:
        si = int(numbers[0])
    else:
        converted_numbers = [int(i) for i in numbers]
        si = sum(converted_numbers)
    return si

def is_in(needle : (str, int), haystack: (list, str, int)):
    is_in_bool = False
    if needle in haystack:
        is_in_bool = True
    return is_in_bool

def index_of_number(item: int, numbers: (list)):
    if item in numbers:
        return numbers.index(item)
    else:
        return None


