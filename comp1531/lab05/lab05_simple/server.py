from flask import Flask, request
from json import dumps

app = Flask(__name__)
names = []

@app.route('/names', methods=['GET'])
def get_names():
    global names
    return dumps({"names" : names})

@app.route('/name/add', methods=['POST'])
def add_name():
    data = request.get_json()
    names.append(data['name'])

    return dumps({})

@app.route('/name/remove', methods=['DELETE'])
def remove_name():
    name = request.get_json()
    names.remove(name['name'])
    return dumps({})

@app.route('/names/clear', methods=['DELETE'])
def clear():
    names.clear()
    return {}


if __name__ == '__main__':
    app.run(port=8080)
