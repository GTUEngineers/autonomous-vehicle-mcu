import process_pb2
import common_pb2
import logging

retCode = 0


def parse_message(message):
    pub_sub = process_pb2.pub_sub()
    if pub_sub.msg_type == process_pb2.pub_sub_message.STATE_WORKING_MSG:
        print("")
    elif pub_sub.msg_type == pub_sub_message.HCSR4_MSG:
        print("")
    elif pub_sub_message == pub_sub_message.GPS_MSG:
        print("")
    else:
        logging.critical("INVALID INCOMING MESSAGE!")
