from src.data_store import data_store
from src.error import AccessError, InputError
from src.helper import get_data

def notifications_v1(auth_user_id):
    """
    Return the user's most recent 20 notifications, ordered from most recent to 
    least recent.   
    Arguments:
        auth_user_id (int)  - The ID of the valid user.
    Return Value:
        Returns {notifications} 
    """

    store = get_data()
    
    log_history = store['log_history']
    notifications = []
    log_history.reverse()
    for notif in log_history[0:20]:
        # finds the user who requested notifications
        if auth_user_id == notif['u_id']:
            notif_message = create_notification_message(notif)
            notification = {
                'channel_id': notif['channel_id'],
                'dm_id': notif['dm_id'],
                'notification_message': notif_message
            }
            notifications.append(notification)
            
    return notifications

def create_notification_message(notif):
    if notif['notif_type'] == 'channel_invite' or notif['notif_type'] == 'dm_create':
        return(f"added to a channel/DM:{notif['handle_str']} added you to {notif['channel/dm_name']}")
    elif notif['notif_type'] == 'message_react':
        return(f"reacted message:{notif['handle_str']} reacted to your message in {notif['channel/dm_name']}")
    return(f"tagged:{notif['handle_str']} tagged you in {notif['channel/dm_name']}: {notif['notif_type']}")

