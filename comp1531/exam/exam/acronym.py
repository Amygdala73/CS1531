def acronym_make(inputs):
    if inputs == []:
        raise ValueError("Input can't be empty")
    
    vowels = ['i','o','a','u','e']
    acronym = ""

    outputs = []
    for x in inputs:
        acronym = ''
        x = x.lower()
        x = x.split()
        
        for y in x:
            if y[0] not in vowels:
                acronym += y[0]
        outputs.append(acronym.upper())
        
    len_test = ''.join(outputs)

    if len(len_test) > 10:
        outputs = ['N/A']
    

    return outputs

