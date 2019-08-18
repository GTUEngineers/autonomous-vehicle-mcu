#!/usr/bin/python3

import zmq
from combase import ComBase
import time

class Publisher(ComBase):
    def __init__(self, is_server):
        ComBase.__init__(self, zmq.PUB, is_server)
        
    def publish(self, topic, msg):
        self.socket.send_multipart([topic.encode("UTF-8"), msg.encode("UTF-8")])

class Subscriber(ComBase):
    def __init__(self, is_server):
        ComBase.__init__(self, zmq.SUB, is_server)
        
        self.poller.register(self.socket, zmq.POLLIN)

    def subscribe(self, topic):
        self.socket.setsockopt(zmq.SUBSCRIBE, topic.encode("UTF-8"))

    def unsubscribe(self, topic):
        self.socket.setsockopt(zmq.UNSUBSCRIBE, topic.encode("UTF-8"))

    def recv(self, timeout = -1):
        socks = dict(self.poller.poll(timeout*1000))
        if self.socket in socks and socks[self.socket] == zmq.POLLIN:
            topic, message = self.socket.recv_multipart()
            
            return topic, message
        return None
