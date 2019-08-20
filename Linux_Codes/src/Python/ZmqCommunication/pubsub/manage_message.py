import sys, os

sys.path.append(os.path.dirname(os.path.realpath(__file__))+"/../../ProtoOut/")
#print(sys.path)
import process_pb2
import common_pb2
import logging

#message is
def create_message(pubsub_message):
    retMsg = ""
    if pubsub_message.msg_type is process_pb2.pub_sub_message.START_STOP_MSG:
        startstop_message = process_pb2.StartStop_req()
        startstop_message.cmd = pubsub_message.startstop.cmd
        retMsg = startstop_message.SerializeToString()
    
    elif pubsub_message.msg_type is process_pb2.pub_sub_message.THROTTLE_MSG:
        throttle_message = process_pb2.Throttle_req()
        throttle_message.throttleValue = pubsub_message.throttle.throttleValue
        retMsg = throttle_message.SerializeToString()
    
    elif pubsub_message.msg_type is process_pb2.pub_sub_message.STEERING_MSG:
        steering_message = process_pb2.Steering_req()
        steering_message.cmd = steering_message.steering.cmd
        steering_message.angle = pubsub_message.steering.angle
        retMsg = steering_message.SerializeToString()
    
    elif pubsub_message.msg_type is process_pb2.pub_sub_message.BRAKE_MSG:
        brake_message = process_pb2.Brake_req()
        brake_message.brakeValue = pubsub_message.brake.brakeValue
        retMsg = brake_message.SerializeToString()
    
    return retMsg

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

def testFoo():

    test = create_startstop_msg(process_pb2.startstop_enum.START)
    test_pubsub = parse_startstop_msg(test)
    if test_pubsub is not None:
        print("YEES "+str(test_pubsub))
    test = create_startstop_msg(process_pb2.startstop_enum.STOP)
    test_pubsub = parse_startstop_msg(test)
    if test_pubsub is not None:
        print("YEES "+str(test_pubsub))

testFoo()


"""
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
"""