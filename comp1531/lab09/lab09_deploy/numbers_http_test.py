import requests
import pytest
from number_fun import *
from numbers_test import *

url = 'http://weizhe-diao.alwaysdata.net/'

def test_multiply_by_two_http():
    input_param = {
        'number': 2
    }
    response = requests.get(f'{url}/multiply/by/two', params = input_param)
    assert response.status_code == 200
    assert response.json() == 4

def test_print_message_http():
    text = 'COMP1531 is legit my favourite course ever'
    response = requests.get(f'{url}/print/message', params = {'message':text})
    assert response.status_code == 200

def test_sum_list_of_numbers_http():
    response = requests.get(f'{url}/sum/list/of/numbers',  params={ 'numbers' : [1,2,3,4] })
    assert response.status_code == 200
    assert response.json() == 10

    response = requests.get(f'{url}/sum/list/of/numbers', params={ 'numbers' : [] })
    assert response.status_code == 200
    assert response.json() == 0

def test_sum_iterable_of_numbers_http():
    response = requests.get(f'{url}/sum/iterable/of/numbers', params={ 'numbers' : tuple([1,2,3,4]) })
    assert response.status_code == 200
    assert response.json() == 10

    response = requests.get(f'{url}/sum/iterable/of/numbers', params={ 'numbers' : tuple([1,2,3,4,5]) })
    assert response.status_code == 200
    assert response.json() == 15

    response = requests.get(f'{url}/sum/iterable/of/numbers', params={ 'numbers' : tuple([1,10,100,1000]) })
    assert response.status_code == 200
    assert response.json() == 1111

def test_is_in_http():
    response = requests.get(f'{url}/is_in',  params={
        'needle': 1,
        'haystack' : tuple([1,2,3,4,5])
    })

    assert response.status_code == 200
    assert response.json() == True

    response = requests.get(f'{url}/is_in',  params={
        'needle': '6',
        'haystack' : [1,2,3,4,5]
    })

    assert response.status_code == 200
    assert response.json() == False

    response = requests.get(f'{url}/is_in',  params={
        'needle': 'a',
        'haystack' : tuple(['a','b','c'])
    })

    assert response.status_code == 200
    assert response.json() == True

def test_index_of_number_http():
    response = requests.get(f'{url}/index_of_number',  params={
        'item': 1,
        'numbers' : tuple([1,2,3,4,5])
    })

    assert response.status_code == 200
    assert response.json() == 0

    response = requests.get(f'{url}/index_of_number',  params={
        'item': 6,
        'numbers' : tuple([1,2,3,4,5])
    })

    assert response.status_code == 200
    assert response.json() == None


