def check_password(password):
    '''
    Takes in a password, and returns a string based on the strength of that password.

    The returned value should be:
    * "Strong password", if at least 12 characters, contains at least one number, at least one uppercase letter, at least one lowercase letter.
    * "Moderate password", if at least 8 characters, contains at least one number.
    * "Poor password", for anything else
    * "Horrible password", if the user enters "password", "iloveyou", or "123456"
    '''
    upper_case = False
    lower_case = False
    is_num = False
    pwl = len(password)

    for i in password:
        if i.isdigit():
            is_num = True
        elif i.isupper():
            upper_case = True
        elif i.islower():
            lower_case = True

    if password == "password" or password == "iloveyou" or password == "123456":
        return "Horrible password"
    
    if pwl>=8 and is_num == True:
        if pwl>=12 and upper_case == True and lower_case == True:
            return "Strong password"
        return "Moderate password"
    return "Poor password"

if __name__ == '__main__':
    print(check_password("ihearttrimesters"))
    # What does this do?
