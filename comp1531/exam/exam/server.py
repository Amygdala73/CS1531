'''
The flask server wrapper

All endpoints return JSON as output.
All POST requests pass parameters through JSON instead of Form.
'''
from json import dumps
from flask import Flask, request

import brooms, acronym

APP = Flask(__name__)

'''
Endpoint: '/users'
Method: GET
Parameters: ()
Output: { "users": [ ... list of strings ... ] }

Returns a list of all the users as a list of strings.
'''
# Write this endpoint here


'''
Endpoint: '/users'
Method: POST
Parameters: ( name: string )
Output: {}

Adds a user to the room/broom.
'''
# Write the endpoint here


'''
Endpoint: '/message'
Method: GET
Parameters: ()
Output: { "messages": [ { "from" : string, "to" : string, "message" : string } ] }

Returns a list of all the messages sent, who they came from, and who they are going to.
'''
# Write the endpoint here


'''
Endpoint: '/message'
Method: POST
Parameters: (user_from: string, user_to: string, message: string)
Output: {}

Sends a message from user "user_from" to user "user_to". All three parameters are strings.
'''
# Write the endpoint here


if __name__ == '__main__':
    APP.run(debug=True)
