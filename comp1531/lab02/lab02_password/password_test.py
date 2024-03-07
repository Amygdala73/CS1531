'''
Tests for check_password()
'''
from password import check_password

def test_password_horrible():
    assert check_password("password") == "Horrible password"
    assert check_password("iloveyou") == "Horrible password"
    assert check_password("123456") == "Horrible password"

def test_password_poor():
    assert check_password("aewwwwwwwwwwwwdsd") == "Poor password"
    assert check_password("iLLoveyou") == "Poor password"
    assert check_password("dsdQ2") == "Poor password"

def test_password_moderate():
    assert check_password("01234567") == "Moderate password"
    assert check_password("1LLoveyo") == "Moderate password"

def test_password_strong():
    assert check_password("Aewwww666wwwwdsd") == "Strong password"
    assert check_password("iLLove23!you") == "Strong password"
    assert check_password("dsdQ2rer2752") == "Strong password" 
