def drykiss(my_list):
    my_min = min(my_list)
    product_a = 1
    product_b = 1
    for i in range(0, 4):
        product_a = product_a * my_list[i]  
    for i in range(1, 5):
        product_b = product_b * my_list[i]
    result = (my_min, product_a, product_b)
    return result

if __name__ == '__main__':

    inputs_list = ['a', 'b', 'c', 'd', 'e']
    my_list = []
    for i in range(len(inputs_list)):
        user_input = int(input(f'Enter {inputs_list[i]}: '))
        my_list.append(user_input)

    
    result = drykiss(my_list)
    print("Minimum: " + str(result[0]))
    print("Product of first 4 numbers: ")
    print(f"  {result[1]}")
    print("Product of last 4 numbers")
    print(f"  {result[2]}")
