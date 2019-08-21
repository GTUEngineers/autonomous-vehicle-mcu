import sys
import os
sys.path.append(os.path.dirname(os.path.realpath(__file__))+"/../../ProtoOut/")
import common_pb2
import process_pb2
# print(sys.path)
# MAY process_pb2 NAME SHORTEN
import logging
logging.basicConfig(filename='parse_create_msg.log', filemode='w', format='%(asctime)s - %(name)s - %(levelname)s - %(message)s')


def create_startstop_msg(cmd):
    pubsub_message = process_pb2.pub_sub()
    pubsub_message.msg_type = process_pb2.pub_sub_message.START_STOP_MSG

    pubsub_message.startstop.cmd = cmd
    return pubsub_message.SerializeToString()


def parse_startstop_msg(msg):
    pubsub_message = process_pb2.pub_sub()
    pubsub_message.ParseFromString(msg)
    if pubsub_message.msg_type is process_pb2.pub_sub_message.START_STOP_MSG:

        return pubsub_message.startstop.cmd
    return None

#Author: Fatih Selim
# Functions that create and parse messages for each type
def create_steering_msg(cmd, angle):
    pubsub_message = process_pb2.pub_sub()
    pubsub_message.msg_type = process_pb2.pub_sub_message.STEERING_MSG

    pubsub_message.steering.cmd = cmd
    pubsub_message.steering.angle = angle
    return pubsub_message.SerializeToString()


def parse_steering_msg(msg):
    pubsub_message = process_pb2.pub_sub()
    pubsub_message.ParseFromString(msg)
    if pubsub_message.msg_type is process_pb2.pub_sub_message.STEERING_MSG:
        return pubsub_message.steering.cmd, pubsub_message.steering.angle
    return None


def create_stateWorking_msg(cmd):
    pubsub_message = process_pb2.pub_sub()
    pubsub_message.msg_type = process_pb2.pub_sub_message.STATE_WORKING_MSG

    pubsub_message.statework.cmd = cmd
    return pubsub_message.SerializeToString()


def parse_stateWorking_msg(msg):
    pubsub_message = process_pb2.pub_sub()
    pubsub_message.ParseFromString(msg)
    if pubsub_message.msg_type is process_pb2.pub_sub_message.STATE_WORKING_MSG:
        return pubsub_message.statework.cmd
    return None


def create_throttle_msg(throttleValue):
    pubsub_message = process_pb2.pub_sub()
    pubsub_message.msg_type = process_pb2.pub_sub_message.THROTTLE_MSG

    pubsub_message.throttle.throttleValue = throttleValue
    return pubsub_message.SerializeToString()


def parse_throttle_msg(msg):
    pubsub_message = process_pb2.pub_sub()
    pubsub_message.ParseFromString(msg)
    if pubsub_message.msg_type is process_pb2.pub_sub_message.THROTTLE_MSG:
        return pubsub_message.throttle.throttleValue
    return None


def create_brake_msg(brakeValue):
    pubsub_message = process_pb2.pub_sub()
    pubsub_message.msg_type = process_pb2.pub_sub_message.BRAKE_MSG

    pubsub_message.brake.brakeValue = brakeValue
    return pubsub_message.SerializeToString()


def parse_brake_msg(msg):
    pubsub_message = process_pb2.pub_sub()
    pubsub_message.ParseFromString(msg)
    if pubsub_message.msg_type is process_pb2.pub_sub_message.BRAKE_MSG:
        return pubsub_message.brake.brakeValue
    return None


def create_HCSR4_msg(distanceVal):
    pubsub_message = process_pb2.pub_sub()
    pubsub_message.msg_type = process_pb2.pub_sub_message.HCSR4_MSG

    pubsub_message.hcsr4_dis.distance = distanceVal
    return pubsub_message.SerializeToString()


def parse_HCSR4_msg(msg):
    pubsub_message = process_pb2.pub_sub()
    pubsub_message.ParseFromString(msg)
    if pubsub_message.msg_type is process_pb2.pub_sub_message.HCSR4_MSG:
        return pubsub_message.hcsr4_dis.distance
    return None


def create_GPS_msg(latitudeVal, longitudeVal):
    pubsub_message = process_pb2.pub_sub()
    pubsub_message.msg_type = process_pb2.pub_sub_message.GPS_MSG

    pubsub_message.location.latitude = latitudeVal
    pubsub_message.location.longitude = longitudeVal
    return pubsub_message.SerializeToString()


def parse_GPS_msg(msg):
    pubsub_message = process_pb2.pub_sub()
    pubsub_message.ParseFromString(msg)
    if pubsub_message.msg_type is process_pb2.pub_sub_message.GPS_MSG:
        return pubsub_message.location.latitude, pubsub_message.location.longitude
    return None


# alternatively a function that parses all message types
def parse_all_type_messages(msg):
    pubsub_message = process_pb2.pub_sub()
    pubsub_message.ParseFromString(msg)

    #handles with message type and returns the parsed data.
    if pubsub_message.msg_type is process_pb2.pub_sub_message.GPS_MSG:
        return pubsub_message.location.latitude, pubsub_message.location.longitude
    
    elif pubsub_message.msg_type is process_pb2.pub_sub_message.HCSR4_MSG:
        return pubsub_message.hcsr4_dis.distance
    
    elif pubsub_message.msg_type is process_pb2.pub_sub_message.BRAKE_MSG:
        return pubsub_message.brake.brakeValue
    
    elif pubsub_message.msg_type is process_pb2.pub_sub_message.THROTTLE_MSG:
        return pubsub_message.throttle.throttleValue
    
    elif pubsub_message.msg_type is process_pb2.pub_sub_message.STATE_WORKING_MSG:
        return pubsub_message.statework.cmd
    
    elif pubsub_message.msg_type is process_pb2.pub_sub_message.STEERING_MSG:
        return pubsub_message.steering.cmd, pubsub_message.steering.angle
    
    elif pubsub_message.msg_type is process_pb2.pub_sub_message.START_STOP_MSG:
        return pubsub_message.startstop.cmd
    
    else:
        logging.warning("Invalid parse type!")
        return None

# End of Fatih

#Author: Tolga
# This method must take message_type as process_pb2.pubsub_message
# val_1 is also must because all message types take at least one parameter
# va_2 is optional according to message type


def create_message(message_type, val_1, val_2=None):

    pubsub_message = process_pb2.pub_sub()

    if message_type == process_pb2.pub_sub_message.START_STOP_MSG:
        pubsub_message.msg_type = process_pb2.pub_sub_message.START_STOP_MSG
        pubsub_message.startstop.cmd = val_1  # val1 is cmd in here

    elif message_type == process_pb2.pub_sub_message.THROTTLE_MSG:
        pubsub_message.msg_type = process_pb2.pub_sub_message.THROTTLE_MSG
        pubsub_message.throttle.throttleValue = val_1  # val1 is throttleVal in here

    elif message_type == process_pb2.pub_sub_message.STEERING_MSG:
        pubsub_message.msg_type = process_pb2.pub_sub_message.STEERING_MSG
        pubsub_message.steering.cmd = val_1  # val1 is cmd in here
        pubsub_message.steering.angle = val_2  # val2 is angle in here

    elif message_type == process_pb2.pub_sub_message.BRAKE_MSG:
        pubsub_message.msg_type = process_pb2.pub_sub_message.BRAKE_MSG
        pubsub_message.brake.brakeValue = val_1  # val1 is brakeValue in here

    elif message_type == process_pb2.pub_sub_message.STATE_WORKING_MSG:
        pubsub_message.msg_type = process_pb2.pub_sub_message.STATE_WORKING_MSG
        pubsub_message.statework.cmd = val_1  # val1 is cmd in here

    elif message_type == process_pb2.pub_sub_message.HSCR4_MSG:
        pubsub_message.msg_type = process_pb2.pub_sub_message.HCSR4_MSG
        pubsub_message.hcsr4_dis.distance = val_1  # val1 is distance in here

    elif message_type == process_pb2.pub_sub_message.GPS_MSG:
        pubsub_message.msg_type = process_pb2.pub_sub_message.GPS_MSG
        pubsub_message.location.latitude = val_1  # val1 is latitude in here
        pubsub_message.location.longitude = val_2  # val1 is longitude in here

    else:
        logging.warning("Invalid message type!")

    return pubsub_message.SerializeToString()
# End of Tolga


def testFoo():

    #test = create_steering_msg(process_pb2.steering_enum.LEFT,120.0)
    #test_pubsub = parse_steering_msg(test)

    #test = create_stateWorking_msg(process_pb2.stateWorking_enum.ERROR)
    #test_pubsub = parse_stateWorking_msg(test)

    #test = create_throttle_msg(20)
    #test_pubsub = parse_throttle_msg(test)

    #test = create_brake_msg(True)
    #test_pubsub = parse_brake_msg(test)

    #test = create_HCSR4_msg(3243.2)
    #test_pubsub = parse_HCSR4_msg(test)

    #test = create_GPS_msg(4/2,2/4)
    #test_pubsub = parse_GPS_msg(test)

    #test = create_startstop_msg(process_pb2.startstop_enum.START)
    #test_pubsub = parse_startstop_msg(test)

    test = create_message(process_pb2.pub_sub_message.STEERING_MSG,
                          process_pb2.steering_enum.RIGHT, 360.0)
    test_pubsub = parse_all_type_messages(test)

    if test_pubsub is not None:
        print("YEES "+str(test_pubsub))
        logging.warning('deneme metni')

    test = create_message(process_pb2.pub_sub_message.START_STOP_MSG, 
                          process_pb2.startstop_enum.STOP)
    test_pubsub = parse_startstop_msg(test)

    if test_pubsub is not None:
        print("YEES "+str(test_pubsub))


testFoo()
