import re
import os
from src.dm import dm_create_v1, dm_details_v1
from src.helper import get_data, check_valid_token,\
     decode_jwt,save_database_updates, datetime_to_unix_time_stamp, \
     seek_target_channel_and_errors
from src.channel import channel_details_v1, channel_messages_v1
from src.channels import channels_list_v1
from src.dm import dm_list_v1, dm_details_v1
from src.data_store import data_store
from src.error import InputError, AccessError
import threading
import time

def message_send_v1(token, channel_id, message):
    '''
    Send a message from the authorised user to the channel specified
    by channel_id. Note: Each message should have its own unique ID,
    i.e. no messages should share an ID with another message, even if
    that other message is in a different channel.
    Assumption: returning type message_id is dict contains integer message
    id
    Arguments:
        token - Used to identify the user
        channel_id - Refers to the channel where message will be sent 
        message - The message needs to be send
    Exceptions:
        InputError - channel_id does not refer to a valid channel
        InputError - the length of message is smaller than 1 or bigger than 1000
        AccessError - channel_id is valid and the authorised user is not a
                      member of the channel
         Return Value:
         Return a dictionary containing the message id              
    '''
    is_member = False
    valid_channel = False
    
    # Fetch data
    if(len(message)<1 or len(message)>1000):
        raise InputError("Error: message too long or too short")

    db_store = get_data()
        
    #Get authorised user id 
    auth_user_id = decode_jwt(token)['u_id']
            
    #Check channel_id is valid
    #Also check if the authorised user is not a member of the channel

    for chan in db_store['channels']:
        if chan['channel_id'] == channel_id:
            target_channel = chan
            valid_channel = True
    if valid_channel == False:
        raise InputError("channel_id does not refer to a valid channel")
            
    for user in target_channel['all_members']:
        if user['u_id'] == auth_user_id:
            # Check if authorised user is a member of the channel
            is_member = True 
            break               
   
    if is_member == False:
        raise AccessError("Authorised user is not a member of the channel")
   
    message_id = db_store['message_index']
    db_store['message_index']+=1
    
    # creates the unix time_stamp
    timestamp = datetime_to_unix_time_stamp()

    message = {
        'message_id': message_id,
        'u_id': auth_user_id,
        'message': message,
        'channel_id': channel_id,
        'time_created': timestamp,
        'is_pinned': False,
        'reacts': [
            {
                'react_id': 1,
                'u_ids': [],
                'is_this_user_reacted': False
            }
        ],
    }
    
    for user in db_store['users']:
        if user['u_id'] == auth_user_id:
            targer_user = user
    targer_user['user_stats']['messages_sent']+=1
    
    target_channel['messages'].append(message)  
    save_database_updates(db_store)

    return {
        'message_id': message_id,
        'time_created': timestamp
    }

def message_edit_v1(token, message_id, new_message):
    '''
    Given a message, update its text with new text.
    If the new message is an empty string, the message is deleted.
    Arguments:
        token - Used to identify the user
        message_id - Refers to the message will be edited
        message - The message needs to be send
    Exceptions:
        InputError - message_id does not refer to a valid message within
                     a channel /DM that the authorised user has joined
        InputError - the length of message is bigger than 1000
        AccessError - the message was not sent by the authorised user making t
                      his request, and the authorised user has owner permissions
                      in the channel/DM
         Return Value:
             N/A        
    '''
    # Fetch data
    auth_request = False
    has_owner_permission = False
    valid_channel_message = False
    valid_dm = False
    if len(new_message)>1000:
        raise InputError("Error: message too long")
    
    elif len(new_message)<1:
        message_remove_v1(token, message_id)
        return None

    db_store = get_data()
        
    #Get authorised user id 
    auth_user_id = decode_jwt(token)['u_id']
            
    #Check message_id is valid
    #Also check if the authorised user is not an owner member of the channel
    for user in db_store['users']:
        if user['u_id'] == auth_user_id:
            targer_user = user
            
    for channel in db_store['channels']:
        for message in channel['messages']:
            if message['message_id'] == message_id:
                valid_channel_message = True
                if message['u_id'] == auth_user_id:
                    auth_request = True
                for users in channel['owner_members']:
                    if auth_user_id == users['u_id']:
                        has_owner_permission = True
                if targer_user['permission_id'] == 1:
                    has_owner_permission = True
                if has_owner_permission == False and auth_request == False:
                    raise AccessError("Authorised user does not have owner permisson \
                          of the channel or the message was not sent by the \
                          authorised user making this request")
    if valid_channel_message and auth_request:
        for channel in db_store['channels']:
            for msg in channel['messages']:
                if msg['message_id'] == message_id:
                    msg['message'] = new_message
                    save_database_updates(db_store)
 
    for dm in db_store['dms']:
        for message in dm['messages']:
            if message['message_id'] == message_id:
                valid_dm = True
                dm_id = message['dm_id']
                dm_owner = dm_details_v1(auth_user_id, dm_id)['members'][0]
                if message['u_id'] == auth_user_id:
                    auth_request = True
                elif dm_owner['u_id'] == auth_user_id:
                    auth_request = True     

    if valid_dm and not auth_request:
        raise AccessError("Authorised user does not have owner permisson \
                          of the channel or the message was not sent by the \
                          authorised user making this request")
    
    if valid_dm and auth_request:
        for dm in db_store['dms']:
            for message in dm['messages']:
                if message['message_id'] == message_id:
                    message['message'] = new_message
                    save_database_updates(db_store)
                    
    if valid_dm == False and valid_channel_message == False:
        raise InputError("Error: message_id oes not refer to a valid message within \
                         a channel /DM that the authorised user has joined")   

def message_remove_v1(token, message_id):
    '''
    Given a message_id for a message, this message is removed from
    the channel/DM.
    Assumption: A meesage can not be removed twice.
    Arguments:
        token - Used to identify the user
        message_id - Refers to the message will be removed
    Exceptions:
        InputError - message_id does not refer to a valid message within
                     a channel /DM that the authorised user has joined
        AccessError - the message was not sent by the authorised user making t
                      his request, and the authorised user has owner permissions
                      in the channel/DM
         Return Value:
             N/A        
    '''
    # Fetch data
    auth_request = False
    has_owner_permission = False
    valid_channel_message = False
    valid_dm = False

    db_store = get_data()
        
    #Get authorised user id 
    auth_user_id = decode_jwt(token)['u_id']
            
    #Check message_id is valid
    #Also check if the authorised user is not an owner member of the channel
    for user in db_store['users']:
        if user['u_id'] == auth_user_id:
            targer_user = user
            
    #Remove channel messages       
    for channel in db_store['channels']:
        for message in channel['messages']:
            if message['message_id'] == message_id:
                valid_channel_message = True
                if message['u_id'] == auth_user_id:
                    auth_request = True        
                for users in channel['owner_members']:
                    if auth_user_id == users['u_id']:
                        has_owner_permission = True
                if targer_user['permission_id'] == 1:
                    has_owner_permission = True
                if has_owner_permission == False and auth_request == False:
                    raise AccessError("Authorised user does not have owner permisson \
                          of the channel or the message was not sent by the \
                          authorised user making this request")
                
    if valid_channel_message and auth_request:
        for channel in db_store['channels']:
            for message in channel['messages']:
                if message['message_id'] == message_id:
                    channel['messages'].remove(message)
                    targer_user['user_stats']['messages_sent']-=1  
                    save_database_updates(db_store)
        
    #Remove dm messages
    for dm in db_store['dms']:
        for message in dm['messages']:
            if message['message_id'] == message_id:
                dm_id = message['dm_id']
                dm_owner = dm_details_v1(auth_user_id, dm_id)['members'][0]
                valid_dm = True
                if message['u_id'] == auth_user_id:
                    auth_request = True
                elif dm_owner['u_id'] == auth_user_id:
                    auth_request = True
                if valid_dm == True and auth_request == False:
                    raise AccessError("Authorised user does not have owner permisson \
                          of the channel or the message was not sent by the \
                          authorised user making this request")
                
    if valid_dm and auth_request:
        for dm in db_store['dms']:
            for message in dm['messages']:
                if message['message_id'] == message_id:
                    dm['messages'].remove(message)
                    targer_user['user_stats']['messages_sent']-=1  
                    save_database_updates(db_store)               

    if valid_dm == False and valid_channel_message == False:
        raise InputError("Error: message_id oes not refer to a valid message within \
                         a channel /DM that the authorised user has joined")
                
    
def message_senddm_v1(token, dm_id, message):
    '''
    Send a message from authorised_user to the DM specified by dm_id.
    Arguments:
        token - Used to identify the user
        dm_id - Used to identify the dm will be sent 
        message - The dm needs to be send
    Exceptions:
    InputError - the length of message is smaller than 1 or bigger than 1000
    AccessError - dm_id is valid and the authorised user is not a
                      member of the DM
         Return Value:
         Return a dictionary containing the message id of the dm message     
    '''
    # Fetch data
    if(len(message)<1 or len(message)>1000):
        raise InputError("Error: message too long or too short")

    db_store = get_data()
    #Get authorised user id 
    auth_user_id = decode_jwt(token)['u_id']

    #Check if dm_id is not valid
    dm_details_v1(auth_user_id, dm_id) #This will check if user or dm_id is not valid    
    
    for dm in db_store['dms']:
        if dm['dm_id'] == dm_id:
            target_dm = dm
   
    message_id = db_store['message_index']
    db_store['message_index']+=1

    # creates the unix time_stamp
    timestamp = datetime_to_unix_time_stamp()
    
    dm_message = {
        'message_id': message_id,
        'u_id': auth_user_id,
        'message': message,
        'dm_id':dm_id,
        'time_created': timestamp,
        'is_pinned': False,
        'reacts': [
            {
                'react_id': 1,
                'u_ids': [],
                'is_this_user_reacted': False
            }
        ],
    }
    for user in db_store['users']:
        if user['u_id'] == auth_user_id:
            targer_user = user
    targer_user['user_stats']['messages_sent']+=1
    
    target_dm['messages'].append(dm_message)
    save_database_updates(db_store)
       
    return {
        'message_id': message_id,
    }

def message_send_later_dm_v1(token, dm_id, message, time_sent):
    '''
    Send a message from the authorised user to the channel specified
    by dm_id automatically at a specified time in the future.
    Note: Each message should have its own unique ID,
    i.e. no messages should share an ID with another message, even if
    that other message is in a different channel.
    Assumption: returning type message_id is dict contains integer message
    id
    Arguments:
        token - Used to identify the user
        dm_id - Refers to the channel where message will be sent 
        message - The message needs to be send
        time spent - 
    Exceptions:
        InputError - dm_id does not refer to a valid channel
        InputError - the length of message is smaller than 1 or bigger than 1000
        InputError - when time_sent is in the past
        AccessError - dm_id is valid and the authorised user is not a
                      member of the channel
         Return Value:
         Return a dictionary containing the message id              
    '''
    # Fetch data
    if(len(message)<1 or len(message)>1000):
        raise InputError("Error: message too long or too short")

    db_store = get_data()
    #Get authorised user id 
    auth_user_id = decode_jwt(token)['u_id']  

    #Check if dm_id or user_id is not valid
    dm_details_v1(auth_user_id, dm_id) #This will check if user or dm_id is not valid
    
    for dm in db_store['dms']:
        if dm['dm_id'] == dm_id:
            target_dm = dm
    if time_sent < time.time():
        raise InputError(description="Error, time_sent is a time in the past")

    message_id = db_store['message_index']
    db_store['message_index']+=1
    
    message = {
        'message_id': message_id,
        'u_id': auth_user_id,
        'message': message,
        'dm_id': dm_id,
        'time_created': time_sent,
        'is_pinned': False,
        'reacts': [
            {
                'react_id': 1,
                'u_ids': [],
                'is_this_user_reacted': False
            }
        ],
    }
   
    time_diff = time_sent - time.time()

    param = [target_dm, db_store, message]
    delayed_msg = threading.Timer(time_diff , delayed_dm_message, param)
    delayed_msg.start()

    for user in db_store['users']:
        if user['u_id'] == auth_user_id:
            targer_user = user
    targer_user['user_stats']['messages_sent']+=1
    
    return {
        'message_id': message_id,
    }

def delayed_dm_message(target_dm, db_store, message):
    target_dm['messages'].append(message)
    db_store['messages'].append(message)
    save_database_updates(db_store)

def message_send_later_v1(token, channel_id, message, time_sent):
    '''
    Send a message from the authorised user to the channel specified
    by channel_id automatically at a specified time in the future.
    Note: Each message should have its own unique ID,
    i.e. no messages should share an ID with another message, even if
    that other message is in a different channel.
    Assumption: returning type message_id is dict contains integer message
    id
    Arguments:
        token - Used to identify the user
        channel_id - Refers to the channel where message will be sent 
        message - The message needs to be send
        time spent - 
    Exceptions:
        InputError - channel_id does not refer to a valid channel
        InputError - the length of message is smaller than 1 or bigger than 1000
        InputError - when time_sent is in the past
        AccessError - channel_id is valid and the authorised user is not a
                      member of the channel
         Return Value:
         Return a dictionary containing the message id              
    '''
    is_member = False
    valid_channel = False
    
    # Fetch data
    if(len(message)<1 or len(message)>1000):
        raise InputError("Error: message too long or too short")

    db_store = get_data()
        
    #Get authorised user id 
    auth_user_id = decode_jwt(token)['u_id']
            
    #Check channel_id is valid
    #Also check if the authorised user is not a member of the channel

    for chan in db_store['channels']:
        if chan['channel_id'] == channel_id:
            target_channel = chan
            valid_channel = True
    if valid_channel == False:
        raise InputError("channel_id does not refer to a valid channel")
            
    for user in target_channel['all_members']:
        if user['u_id'] == auth_user_id:
            # Check if authorised user is a member of the channel
            is_member = True 
            break               
   
    if is_member == False:
        raise AccessError("Authorised user is not a member of the channel")
   
    if time_sent < time.time():
        raise InputError(description="Error, time_sent is a time in the past")

    message_id = db_store['message_index']
    db_store['message_index']+=1
    
    message = {
        'message_id': message_id,
        'u_id': auth_user_id,
        'message': message,
        'channel_id': channel_id,
        'time_created': time_sent,
        'is_pinned': False,
        'reacts': [
            {
                'react_id': 1,
                'u_ids': [],
                'is_this_user_reacted': False
            }
        ],
    }
   
    time_diff = time_sent - time.time()

    param = [target_channel, db_store, message]
    delayed_msg = threading.Timer(time_diff , delayed_message, param)
    delayed_msg.start()

    for user in db_store['users']:
        if user['u_id'] == auth_user_id:
            targer_user = user
    targer_user['user_stats']['messages_sent']+=1
    
    return {
        'message_id': message_id,
    }

def delayed_message(target_channel, db_store, message):
    target_channel['messages'].append(message)
    db_store['messages'].append(message)
    save_database_updates(db_store)

def message_pin_v1(token, message_id):
    '''
    A function that pins a message within a channel or dm given
    that the user pinning the message has owner permissions in
    that channel/dm.
    
    Arguments:
        token - token of member with owner permission in the channel/dm
        message_id - id of the message to be pinned
    
    Exceptions:
        InputError  - message_id is not a valid message within a channel/dm the
                      user has joined
        InputError  - the message is already pinned
        AccessError - user does not have owner permissions in the channel/dm
    
    Return Value:
        Nothing is returned
    '''
    store = get_data()

    u_id = decode_jwt(token)['u_id']

    if store['message_index'] <= message_id:
        raise InputError(description="Error: message_id does not refer to a valid message")

    for user in store['users']:
        if user['u_id'] == u_id:
            targer_user = user
    
    in_channel_dm = False
    is_pinned = False
    owner_permission = False

    #Checking in channels       
    for channel in store['channels']:
        for message in channel['messages']:
            if message['message_id'] == message_id:
                if message['is_pinned']:
                    is_pinned = True
                for users in channel['all_members']:
                    if u_id == users['u_id']:
                        in_channel_dm = True
                        if targer_user['permission_id'] == 1:
                            owner_permission = True
                for users in channel['owner_members']:
                    if u_id == users['u_id']:
                        owner_permission = True
                

                if not in_channel_dm:
                    raise InputError(description="Authorised user is not a member of the channel")

                if not owner_permission:
                    raise AccessError(description="Authorised user does not have owner permissions")

                if is_pinned:
                    raise InputError(description="Message is already pinned")
    
    # Pinning in channel  
    if in_channel_dm and owner_permission:
        for channel in store['channels']:
            for message in channel['messages']:
                if message['message_id'] == message_id:
                    message['is_pinned'] = True
                    save_database_updates(store)

    in_channel_dm = False
    owner_permission = False

    #Checking in dms
    for dm in store['dms']:
        for message in dm['messages']:
            if message['message_id'] == message_id:
                if message['is_pinned']:
                    is_pinned = True
                if u_id == dm['auth_user_id']:
                    owner_permission = True
                for user in dm['u_ids']:
                    if u_id == user:
                        in_channel_dm = True

                if not in_channel_dm:
                    raise InputError(description="Authorised user is not a member of the dm")

                if not owner_permission:
                    raise AccessError(description="Authorised user does not have owner permissions")

                if is_pinned:
                    raise InputError(description="Message is already pinned")
                
    # Pinning in dm
    if in_channel_dm and owner_permission:
        for dm in store['dms']:
            for message in dm['messages']:
                if message['message_id'] == message_id:
                    message['is_pinned'] = True
                    save_database_updates(store)

    return {}

def message_unpin_v1(token, message_id):
    '''
    A function that unpins a message within a channel or dm given
    that the user unpinning the message has owner permissions in
    that channel/dm.
    
    Arguments:
        token - token of member with owner permission in the channel/dm
        message_id - id of the message to be unpinned
    
    Exceptions:
        InputError  - message_id is not a valid message within a channel/dm the
                      user has joined
        InputError  - the message is not pinned
        AccessError - user does not have owner permissions in the channel/dm
    
    Return Value:
        Nothing is returned
    '''
    store = get_data()

    u_id = decode_jwt(token)['u_id']

    if store['message_index'] <= message_id:
        raise InputError(description="Error: message_id does not refer to a valid message")

    for user in store['users']:
        if user['u_id'] == u_id:
            targer_user = user
    
    in_channel_dm = False
    is_pinned = False
    owner_permission = False

    # Checking in channels       
    for channel in store['channels']:
        for message in channel['messages']:
            if message['message_id'] == message_id:
                if message['is_pinned']:
                    is_pinned = True
                for users in channel['all_members']:
                    if u_id == users['u_id']:
                        in_channel_dm = True
                        if targer_user['permission_id'] == 1:
                            owner_permission = True
                for users in channel['owner_members']:
                    if u_id == users['u_id']:
                        owner_permission = True
                

                if not in_channel_dm:
                    raise InputError(description="Authorised user is not a member of the channel")

                if not owner_permission:
                    raise AccessError(description="Authorised user does not have owner permissions")

                if not is_pinned:
                    raise InputError(description="Message is already unpinned")
    
    # Unpinning in channel  
    if in_channel_dm and owner_permission:
        for channel in store['channels']:
            for message in channel['messages']:
                if message['message_id'] == message_id:
                    message['is_pinned'] = False
                    save_database_updates(store)

    in_channel_dm = False
    owner_permission = False

    #Checking in dms
    for dm in store['dms']:
        for message in dm['messages']:
            if message['message_id'] == message_id:
                if message['is_pinned']:
                    is_pinned = True
                if u_id == dm['auth_user_id']:
                    owner_permission = True
                for user in dm['u_ids']:
                    if u_id == user:
                        in_channel_dm = True

                if not in_channel_dm:
                    raise InputError(description="Authorised user is not a member of the dm")

                if not owner_permission:
                    raise AccessError(description="Authorised user does not have owner permissions")

                if not is_pinned:
                    raise InputError(description="Message is already unpinned")
                
    # Pinning in dm
    if in_channel_dm and owner_permission:
        for dm in store['dms']:
            for message in dm['messages']:
                if message['message_id'] == message_id:
                    message['is_pinned'] = False
                    save_database_updates(store)

    return {}

def message_react_v1(token, message_id, react_id):
    '''
    A function that reacts to a message within a channel or dm given
    that the user reacting is in that channel/dm.
    
    Arguments:
        token      - token of member in the channel/dm
        message_id - id of the message to be reacted to
        react_id   - reaction to be used for the message
    
    Exceptions:
        InputError  - message_id is not a valid message within a channel/dm the
                      user has joined
        InputError  - react_id is invalid
        InputError  - user has already used the same react on the message
    
    Return Value:
        Nothing is returned
    '''
    store = get_data()

    u_id = decode_jwt(token)['u_id']

    if store['message_index'] <= message_id:
        raise InputError(description="Error: message_id does not refer to a valid message")

    if react_id != 1:
        raise InputError(description="Error: react_id is invalid")
    
    in_channel_dm = False
    reacted = False
    
    # Checking in channels       
    for channel in store['channels']:
        for message in channel['messages']:
            if message['message_id'] == message_id:
                for users in channel['all_members']:
                    if u_id == users['u_id']:
                        in_channel_dm = True
                    for user_id in message['reacts'][react_id - 1]['u_ids']:
                        if u_id == user_id:
                            reacted = True                

                if not in_channel_dm:
                    raise InputError(description="Authorised user is not a member of the channel")

                if reacted:
                    raise InputError(description="Message is already reacted to")
    
    # Reacting to message in channel  
    if in_channel_dm:
        for channel in store['channels']:
            for message in channel['messages']:
                if message['message_id'] == message_id:
                    message['reacts'][react_id - 1]['u_ids'].append(u_id)
                    save_database_updates(store)
                    
    in_channel_dm = False
    
    # Checking in dms       
    for dm in store['dms']:
        for message in dm['messages']:
            if message['message_id'] == message_id:
                for user in dm['u_ids']:
                    if u_id == user:
                        in_channel_dm = True
                    for user_id in message['reacts'][react_id - 1]['u_ids']:
                        if u_id == user_id:
                            reacted = True                

                if not in_channel_dm:
                    raise InputError(description="Authorised user is not a member of the dm")

                if reacted:
                    raise InputError(description="Message is already reacted to")
    
    # Reacting to message in dms  
    if in_channel_dm:
        for dm in store['dms']:
            for message in dm['messages']:
                if message['message_id'] == message_id:
                    message['reacts'][react_id - 1]['u_ids'].append(u_id)
                    save_database_updates(store)
                    
    return {}

def message_unreact_v1(token, message_id, react_id):
    '''
    A function that unreacts to a message within a channel or dm given
    that the user unreacting is in that channel/dm.
    
    Arguments:
        token      - token of member in the channel/dm
        message_id - id of the message to be unreacted to
        react_id   - reaction to be unreacted for the message
    
    Exceptions:
        InputError  - message_id is not a valid message within a channel/dm the
                      user has joined
        InputError  - react_id is invalid
        InputError  - user hasn't used the same react on the message
    
    Return Value:
        Nothing is returned
    '''
    store = get_data()

    u_id = decode_jwt(token)['u_id']

    if store['message_index'] <= message_id:
        raise InputError(description="Error: message_id does not refer to a valid message")

    if react_id != 1:
        raise InputError(description="Error: react_id is invalid")
    
    in_channel_dm = False
    reacted = False
    
    # Checking in channels       
    for channel in store['channels']:
        for message in channel['messages']:
            if message['message_id'] == message_id:
                for users in channel['all_members']:
                    if u_id == users['u_id']:
                        in_channel_dm = True
                    for user_id in message['reacts'][react_id - 1]['u_ids']:
                        if u_id == user_id:
                            reacted = True                

                if not in_channel_dm:
                    raise InputError(description="Authorised user is not a member of the channel")

                if not reacted:
                    raise InputError(description="Message is not reacted to")
    
    # Reacting to message in channel  
    if in_channel_dm:
        for channel in store['channels']:
            for message in channel['messages']:
                if message['message_id'] == message_id:
                    message['reacts'][react_id - 1]['u_ids'].remove(u_id)
                    save_database_updates(store)
                    
    in_channel_dm = False
    
    # Checking in dms       
    for dm in store['dms']:
        for message in dm['messages']:
            if message['message_id'] == message_id:
                for user in dm['u_ids']:
                    if u_id == user:
                        in_channel_dm = True
                    for user_id in message['reacts'][react_id - 1]['u_ids']:
                        if u_id == user_id:
                            reacted = True                

                if not in_channel_dm:
                    raise InputError(description="Authorised user is not a member of the dm")

                if not reacted:
                    raise InputError(description="Message is not reacted to")
    
    # Reacting to message in dms  
    if in_channel_dm:
        for dm in store['dms']:
            for message in dm['messages']:
                if message['message_id'] == message_id:
                    message['reacts'][react_id - 1]['u_ids'].remove(u_id)
                    save_database_updates(store)
                    
    return {}

def message_share_v1(token, og_message_id, message, channel_id, dm_id):
    '''
    '''
    if channel_id != -1 and dm_id != -1:
        raise InputError(description="Neither channel_id nor dm_id are -1")
    if channel_id == -1 and dm_id == -1:
        raise InputError(description="No forwarding direction")
    
    is_source_member = False
    is_sharing_member = False
    valid_channel_message = False
    valid_dm_message = False

    if len(message)>1000:
        raise InputError("Error: message too long")

    db_store = get_data()
        
    #Get authorised user id 
    auth_user_id = decode_jwt(token)['u_id']
    
    #Check message_id is valid
    #Also check if the authorised user is not an owner member of the channel

    if dm_id == -1: # Share message from a DM to a channel
        target_channel = seek_target_channel_and_errors(db_store, auth_user_id, channel_id)
        for dm in db_store['dms']:  
            for message in dm['messages']:
                if message['message_id'] == og_message_id:
                    source_dm = dm
                    source_dm_msg = message
                    valid_dm_message = True
            if not valid_dm_message:
                raise InputError(description="No such dm message")
            #source_dm_id = source_dm['dm_id']
            for u_id in source_dm['u_ids']:
                if u_id == auth_user_id:
                    is_source_member = True
            if not is_source_member:
                raise InputError(description="User is not a member of the source DM")
            
        for user in target_channel['all_members']:
            if user['u_id'] == auth_user_id:
                is_sharing_member = True
        if not is_sharing_member:
            raise AccessError(description="User is not a member of target channel")
                
        og_message = source_dm_msg['message']
        print('og_message: ',og_message)
        print('message: ', message)
        shared_message = "Forwarded message: \n" + \
                         message['message'] + '\n"""\n' + "Original message: \n" + \
                         og_message + '\n"""\n'
        shared_message_id = message_send_v1(token, channel_id, shared_message)
        return {
            'shared_message_id': shared_message_id,
            }

    elif channel_id == -1: # Share message from a channel to a DM
        dm_details_v1(auth_user_id, dm_id)
        for channel in db_store['channels']:  
            for message in channel['messages']:
                if message['message_id'] == og_message_id:
                    source_channel = channel
                    source_channel_msg = message
                    valid_channel_message = True
            if not valid_channel_message:
                raise InputError(description="No such channel message")
            #source_channel_id = source_channel['channel_id']
            for user in source_channel['all_members']:
                if user['u_id']== auth_user_id:
                    is_source_member = True
            if not is_source_member:
                raise InputError(description="User is not a member of the source channel")
        for dm in db_store['dms']:
            if dm['dm_id'] == dm_id:
                target_dm = dm
        for u_id in target_dm['u_ids']:
            if u_id == auth_user_id:
                is_sharing_member = True
        if not is_sharing_member:
            raise AccessError(description="User is not a member of target channel")
        og_message = source_channel_msg['message']
        print('og_message: ',og_message)
        print('message: ', message)
        shared_message = "Forwarded message: \n" + \
                         message['message'] + '\n"""\n' + "Original message: \n" + \
                         og_message + '\n"""\n'
        shared_message_id = message_senddm_v1(token, dm_id, shared_message)
        return {
            'shared_message_id': shared_message_id,
            }
                
        


