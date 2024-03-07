import pytest
import requests

URL = 'http://127.0.0.1:8080/'

@pytest.fixture

def test_add_name():
    requests.delete(f'{URL}/names/clear')
    requests.post(f"{URL}/name/add", json={ 'name' : 'AAA' })
    requests.post(f"{URL}/name/add", json={ 'name' : 'BBB' })
    requests.post(f"{URL}/name/add", json={ 'name' : 'CCC' })
    payload = requests.get(f"{URL}/names").json()
    assert payload['names'] == [ 'AAA', 'BBB', 'CCC' ]

def test_remove_neme():
    requests.delete(f'{URL}/names/clear')
    requests.post(f"{URL}/name/add", json={ 'name' : 'AAA' })
    requests.post(f"{URL}/name/add", json={ 'name' : 'BBB' })
    requests.post(f"{URL}/name/add", json={ 'name' : 'CCC' })
    requests.delete(f"{URL}/name/remove", json={ 'name' : 'AAA' })
    payload = requests.get(f"{URL}/names").json()
    assert payload['names'] == [ 'BBB', 'CCC' ]

