import datetime
from flask import Flask, jsonify, request
from json import dumps
from number_fun import *

APP = Flask(__name__)

@APP.route('/multiply/by/two', methods=['GET'])
def multiply_by_2():
    number = int(request.args.get("number"))
    return dumps(multiply_by_two(number))

@APP.route('/print/message', methods=['GET'])
def print_():
    message = request.args.get("message")
    return dumps(print_message(message))

@APP.route('/sum/list/of/numbers', methods=['GET'])
def sum_list():
    numbers = list(map(int, request.args.getlist('numbers')))
    return dumps(sum_list_of_numbers(numbers))

@APP.route('/sum/iterable/of/numbers', methods=['GET'])
def sum_iterable():
    numbers = list(map(int, request.args.getlist('numbers')))
    return dumps(sum_iterable_of_numbers(numbers))

@APP.route('/is_in', methods=['GET'])
def item_is_in():
    try:
        needle = int(request.args.get("needle"))
        haystack = list(map(int, request.args.getlist('haystack')))
    except:
        needle = request.args.get("needle")
        haystack = request.args.getlist('haystack')       
    return dumps(is_in(needle,haystack))

@APP.route('/index_of_number', methods=['GET'])
def idx_of_number():
    item = request.args.get("item")
    numbers= request.args.getlist("numbers")
    return dumps(index_of_number(item,numbers))

if __name__ == '__main__':
    APP.run(debug=True, port=8081)
