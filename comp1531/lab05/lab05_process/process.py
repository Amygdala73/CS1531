import json
import operator
import pickle

def process():
    f = open('shapecolour.p', 'rb')
    data = pickle.load(f)
    common_list = []
    common = {"Colour": None,
              "Shape": None,}

    for d in data:
        common_list.append(d['colour']+ ', ' + d['shape'])

    count = 0
    
    for d in common_list:
        if(common_list.count(d)) > count:
            cosh = d.split(', ')
            common = {"Colour": cosh[0],
                      "Shape": cosh[1],}
    process_dict = {common, "rawData" : data,}

    with open("processed.json", "w") as write_file:
        json.dump(process_dict, write_file)


